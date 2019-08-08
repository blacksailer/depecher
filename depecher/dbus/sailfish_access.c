/*
 *  Connection Manager
 *
 *  Copyright (C) 2019 Jolla Ltd. All rights reserved.
 *  Contact: David Llewellyn-Jones <david.llewellyn-jones@jolla.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define CONNMAN_API_SUBJECT_TO_CHANGE
#include <dbusaccess_peer.h>
#include <dbusaccess_policy.h>

#include <gutil_idlepool.h>
#include <gutil_log.h>

#define CONNMAN_BUS DA_BUS_SESSION
#define COMMON_GROUP "Common"
#define DEFAULT_POLICY "DefaultAccess"
#define DEFAULT_INTF_POLICY "*"



enum depecher_method {
    OPEN_CONVERSATION,
    SHOW_APP,
    DEFAULT_METHOD_COUNT,
    GET_CHAT_LIST = DEFAULT_METHOD_COUNT,
    SEND_MEDIA,
    SEND_VCARD,
    SHARE_METHOD_COUNT,
    DEPECHER_METHOD_COUNT = SHARE_METHOD_COUNT
};
enum auth_da_access {
    AUTH_DENY,
    AUTH_ALLOW,
    AUTH_DONT_CARE
};
G_STATIC_ASSERT((DA_ACCESS)AUTH_DENY == DA_ACCESS_DENY);
G_STATIC_ASSERT((DA_ACCESS)AUTH_ALLOW == DA_ACCESS_ALLOW);


enum depecher_intf {
    DEFAULT_INTF,
    SHARE_INTF,
    DEPECHER_INTF_COUNT
};
static const char * depecher_method_names[DEPECHER_METHOD_COUNT] = {
    "openConversation",
    "showApp",
    "getChatList",
    "sendVCard",
    "sendMedia"
};
static const char * depecher_interface_names[DEPECHER_INTF_COUNT] = {
    "org.blacksailer.depecher",
    "org.blacksailer.depecher.share"
};
const char *depecher_intf_name(enum depecher_intf intf)
{
    switch (intf) {
    case DEFAULT_INTF:
        return depecher_interface_names[(int)intf];
    case SHARE_INTF:
        return depecher_interface_names[(int)intf];
    default:
        return NULL;
    }
}

GPtrArray *active_policy;

const char *sailfish_access_config_file = "/etc/depecher/depecher-dbus-access.conf";
static const char *default_access_policy = DA_POLICY_VERSION "; "
    "* = deny; "
    "group(privileged) = allow";

/*
 * Configuration is loaded from /etc/connman/vpn-dbus-access.conf
 * If configuration is missing, default access rules are used.
 * Syntax goes like this:
 *
 * [Common]
 * DefaultAccess = <default rules for all controlled interfaces/methods>
 *
 * [InterfaceX]
 * * = <default access rules for all methods in this interface>
 * MethodY = <access rule for this method>
 */

static void sailfish_access_policy_free(gpointer user_data)
{
    da_policy_unref((DAPolicy *)user_data);
}
static enum depecher_intf depecher_intf_from_method(enum depecher_method method)
{
    enum depecher_intf  intf = SHARE_INTF;

    if (method < DEFAULT_METHOD_COUNT)
        intf = DEFAULT_INTF;

    return intf;
}

static const char *depecher_method_name(enum depecher_method method)
{
    if ((method >= 0) && (method < DEPECHER_METHOD_COUNT))
        return depecher_method_names[method];

    return NULL;
}


static void sailfish_access_load_config_intf(GKeyFile *config,
                         DAPolicy *default_policy)
{
    int i;
    GPtrArray *default_policies = g_ptr_array_new_with_free_func(
                sailfish_access_policy_free);

    /* Load the default policy for each interface */
    for (i = 0; i < DEPECHER_INTF_COUNT; i++) {
        DAPolicy *default_intf_policy = NULL;
        const char *group = depecher_intf_name((depecher_intf)i);
        char *spec = g_key_file_get_string(config, group,
                           DEFAULT_INTF_POLICY, NULL);
        qDebug("Parsing default %s rule \"%s\"",
            group, spec);
        /* Parse the default policy for this interface */
        if (spec) {
            default_intf_policy = da_policy_new(spec);
            if (!default_intf_policy)
                qDebug("Failed to parse default %s rule \"%s\"",
                    group, spec);

            g_free(spec);
        }

        if (!default_intf_policy)
            default_intf_policy = da_policy_ref(default_policy);
        g_ptr_array_add(default_policies, default_intf_policy);
    }

    /* Parse individual policies for each method */
    for (i = 0; i < DEPECHER_METHOD_COUNT; i++) {
        DAPolicy *policy = NULL;
        const char *method = depecher_method_name((depecher_method)i);
        enum depecher_intf intf = depecher_intf_from_method((depecher_method)i);
        const char *group = depecher_intf_name(intf);
        char *spec = g_key_file_get_string(config, group, method, NULL);
        qDebug(" rule \"%s\"", spec);

        if (spec) {
            policy = da_policy_new(spec);
            if (!policy)
                qDebug("Failed to parse %s.%s rule \"%s\"",
                            group, method, spec);

            g_free(spec);
        }

        if (!policy)
            policy = da_policy_ref(static_cast<DAPolicy*>(g_ptr_array_index(
                               default_policies, intf)));

        g_ptr_array_add(active_policy, policy);
    }

    g_ptr_array_free(default_policies, TRUE);
}

static void sailfish_access_load_config()
{
    GKeyFile *config = g_key_file_new();
    char *default_policy_spec;
    DAPolicy *default_policy;

    /*
     * Try to load config file, in case of error just make sure
     * that it config is empty.
     */
    if (g_file_test(sailfish_access_config_file, G_FILE_TEST_IS_REGULAR)) {
        if (g_key_file_load_from_file(config,
                    sailfish_access_config_file,
                    G_KEY_FILE_NONE, NULL)) {
            qDebug("Loading D-Bus access rules from %s",
                        sailfish_access_config_file);
        } else {
            g_key_file_unref(config);
            config = g_key_file_new();
        }
    }

    default_policy_spec = g_key_file_get_string(config, COMMON_GROUP,
                            DEFAULT_POLICY, NULL);
    default_policy = da_policy_new(default_policy_spec);
    if (!default_policy) {
        qDebug("Failed to parse common default D-Bus policy \"%s\"",
            default_policy_spec);
        default_policy = da_policy_new(default_access_policy);
        if (!default_policy)
            qDebug("Failed to parse fallback default D-Bus policy "
                "\"%s\"", default_access_policy);
    }

    sailfish_access_load_config_intf(config, default_policy);

    da_policy_unref(default_policy);
    g_free(default_policy_spec);
    g_key_file_unref(config);
}

static enum auth_da_access sailfish_access_policy_check(const char *sender,
                        enum depecher_method method,
                        const char *arg)
{
    if (active_policy && method >= 0 && method < active_policy->len) {
        DAPeer *peer = da_peer_get(CONNMAN_BUS, sender);
        if (peer)
            return (auth_da_access)da_policy_check(
                        static_cast<DAPolicy*>(g_ptr_array_index(active_policy, method)),
                       &peer->cred, 0, arg, (da_access)AUTH_DENY);
        else
            /*
             * Deny access to unknown peers. Those are
             * already gone from the bus and won't be
             * able to receive our reply anyway.
             */
            return AUTH_DENY;
    }
    return AUTH_DONT_CARE;
}

/*
 * Local Variables:
 * mode: C
 * c-basic-offset: 8
 * indent-tabs-mode: t
 * End:
 */
