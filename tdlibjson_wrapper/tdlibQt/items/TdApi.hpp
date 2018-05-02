#ifndef TDAPI_HPP
#define TDAPI_HPP
#pragma once


#include <QString>
#include <stdint.h>
#include <string.h>
#include <memory>
#include "TdLibDependencies.hpp"

namespace tdlibQt {
using int32 = qint32;
using int64 = qint64;


using UInt128 = UInt<128>;
using UInt256 = UInt<256>;

//class TlStorerToString
//{
//    std::string result;
//    int shift = 0;

//    void store_field_begin(const char *name)
//    {
//        for (int i = 0; i < shift; i++) {
//            result += ' ';
//        }
//        if (name && name[0]) {
//            result += name;
//            result += " = ";
//        }
//    }
//    void store_field_end()
//    {
//        result += "\n";
//    }
//    void store_long(qint64 value)
//    {
//        result += QString::number(value).toStdString();
//    }
//    void store_binary(Slice data)
//    {
//        static const char *hex = "0123456789ABCDEF";

//        result.append("{ ");
//        for (auto c : data) {
//            unsigned char byte = c;
//            result += hex[byte >> 4];
//            result += hex[byte & 15];
//            result += ' ';
//        }
//        result.append("}");
//    }

//public:
//    TlStorerToString() = default;
//    TlStorerToString(const TlStorerToString &other) = delete;
//    TlStorerToString &operator=(const TlStorerToString &other) = delete;

//    void store_field(const char *name, bool value)
//    {
//        store_field_begin(name);
//        result += (value ? "true" : "false");
//        store_field_end();
//    }

//    void store_field(const char *name, qint32 value)
//    {
//        store_field(name, static_cast<int64>(value));
//    }

//    void store_field(const char *name, qint64 value)
//    {
//        store_field_begin(name);
//        store_long(value);
//        store_field_end();
//    }

//    void store_field(const char *name, double value)
//    {
//        store_field_begin(name);
//        result += QString::number(value).toStdString();
//        store_field_end();
//    }

//    void store_field(const char *name, const char *value)
//    {
//        store_field_begin(name);
//        result += value;
//        store_field_end();
//    }

//    void store_field(const char *name, const std::string &value)
//    {
//        store_field_begin(name);
//        result += '"';
//        result.append(value.data(), value.size());
//        result += '"';
//        store_field_end();
//    }

//    template <class T>
//    void store_field(const char *name, const T &value)
//    {
//        store_field_begin(name);
//        result.append(value.data(), value.size());
//        store_field_end();
//    }

//    template <class BytesT>
//    void store_bytes_field(const char *name, const BytesT &value)
//    {
//        static const char *hex = "0123456789ABCDEF";

//        store_field_begin(name);
//        result.append("bytes { ");
//        for (size_t i = 0; i < value.size(); i++) {
//            int b = value[static_cast<int>(i)] & 0xff;
//            result += hex[b >> 4];
//            result += hex[b & 15];
//            result += ' ';
//        }
//        result.append("}");
//        store_field_end();
//    }

//    void store_field(const char *name, const UInt128 &value)
//    {
//        store_field_begin(name);
//        store_binary(Slice(reinterpret_cast<const unsigned char *>(&value), sizeof(value)));
//        store_field_end();
//    }

//    void store_field(const char *name, const UInt256 &value)
//    {
//        store_field_begin(name);
//        store_binary(Slice(reinterpret_cast<const unsigned char *>(&value), sizeof(value)));
//        store_field_end();
//    }

//    void store_class_begin(const char *field_name, const char *class_name)
//    {
//        store_field_begin(field_name);
//        result += class_name;
//        result += " {\n";
//        shift += 2;
//    }

//    void store_class_end()
//    {
//        shift -= 2;
//        for (int i = 0; i < shift; i++) {
//            result += ' ';
//        }
//        result += "}\n";
////        CHECK(shift >= 0);
//    }

//    std::string str() const
//    {
//        return result;
//    }
//};

class TlInterface
{
public:
    virtual int32_t get_id() const = 0;
    virtual void store(TlStorerToString &s, const char *field_name) const = 0;
    TlInterface() = default;
    TlInterface(const TlInterface &) = delete;
    TlInterface &operator=(const TlInterface &) = delete;
    TlInterface(TlInterface &&) = default;
    TlInterface &operator=(TlInterface &&) = default;
    virtual ~TlInterface() = default;
};

using BaseObject = TlInterface;

template <class Type>
using object_ptr = QSharedPointer<Type>;

template <class Type, class... Args>
object_ptr<Type> make_object(Args &&... args)
{
    return object_ptr<Type>(new Type(std::forward<Args>(args)...));
}

template <class ToType, class FromType>
object_ptr<ToType> move_object_as(FromType &&from)
{
    return object_ptr<ToType>(static_cast<ToType *>(from.release()));
}

std::string to_string(const BaseObject &value);

template <class T>
std::string to_string(const object_ptr<T> &value)
{
    if (value == nullptr) {
        return "null";
    }

    return to_string(*value);
}

class accountTtl;

class animation;

class animations;

class audio;

class authenticationCodeInfo;

class AuthenticationCodeType;

class AuthorizationState;

class basicGroup;

class basicGroupFullInfo;

class botCommand;

class botInfo;

class call;

class callConnection;

class CallDiscardReason;

class callId;

class callProtocol;

class CallState;

class callbackQueryAnswer;

class CallbackQueryPayload;

class chat;

class ChatAction;

class chatEvent;

class ChatEventAction;

class chatEventLogFilters;

class chatEvents;

class chatInviteLink;

class chatInviteLinkInfo;

class chatMember;

class ChatMemberStatus;

class chatMembers;

class chatPhoto;

class ChatReportReason;

class chatReportSpamState;

class ChatType;

class chats;

class CheckChatUsernameResult;

class connectedWebsite;

class connectedWebsites;

class ConnectionState;

class contact;

class count;

class customRequestResult;

class DeviceToken;

class document;

class draftMessage;

class error;

class file;

class FileType;

class formattedText;

class foundMessages;

class game;

class gameHighScore;

class gameHighScores;

class hashtags;

class importedContacts;

class inlineKeyboardButton;

class InlineKeyboardButtonType;

class InlineQueryResult;

class inlineQueryResults;

class InputCredentials;

class InputFile;

class InputInlineQueryResult;

class InputMessageContent;

class inputSticker;

class inputThumbnail;

class invoice;

class keyboardButton;

class KeyboardButtonType;

class labeledPricePart;

class LinkState;

class localFile;

class location;

class MaskPoint;

class maskPosition;

class message;

class MessageContent;

class MessageForwardInfo;

class MessageSendingState;

class messages;

class networkStatistics;

class NetworkStatisticsEntry;

class NetworkType;

class notificationSettings;

class NotificationSettingsScope;

class ok;

class OptionValue;

class orderInfo;

class PageBlock;

class passwordRecoveryInfo;

class passwordState;

class paymentForm;

class paymentReceipt;

class paymentResult;

class paymentsProviderStripe;

class photo;

class photoSize;

class profilePhoto;

class Proxy;

class publicMessageLink;

class recoveryEmailAddress;

class remoteFile;

class ReplyMarkup;

class RichText;

class savedCredentials;

class SearchMessagesFilter;

class secretChat;

class SecretChatState;

class session;

class sessions;

class shippingAddress;

class shippingOption;

class sticker;

class stickerEmojis;

class stickerSet;

class stickerSetInfo;

class stickerSets;

class stickers;

class storageStatistics;

class storageStatisticsByChat;

class storageStatisticsByFileType;

class storageStatisticsFast;

class supergroup;

class supergroupFullInfo;

class SupergroupMembersFilter;

class tMeUrl;

class TMeUrlType;

class tMeUrls;

class tdlibParameters;

class temporaryPasswordState;

class testBytes;

class testInt;

class testString;

class testVectorInt;

class testVectorIntObject;

class testVectorString;

class testVectorStringObject;

class text;

class textEntities;

class textEntity;

class TextEntityType;

class TextParseMode;

class TopChatCategory;

class Update;

class user;

class userFullInfo;

class UserPrivacySetting;

class UserPrivacySettingRule;

class userPrivacySettingRules;

class userProfilePhotos;

class UserStatus;

class UserType;

class users;

class validatedOrderInfo;

class venue;

class video;

class videoNote;

class voiceNote;

class wallpaper;

class wallpapers;

class webPage;

class webPageInstantView;

class Object;

class Object: public TlInterface
{
public:
};

class Function: public TlInterface
{
public:
};

class accountTtl final : public Object
{
public:
    std::int32_t days_;

    accountTtl();

    explicit accountTtl(std::int32_t days_);

    static const std::int32_t ID = 1324495492;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class animation final : public Object
{
public:
    std::int32_t duration_;
    std::int32_t width_;
    std::int32_t height_;
    std::string file_name_;
    std::string mime_type_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> animation_;

    animation();

    animation(std::int32_t duration_, std::int32_t width_, std::int32_t height_,
              std::string const &file_name_, std::string const &mime_type_, object_ptr<photoSize> &&thumbnail_,
              object_ptr<file> &&animation_);

    static const std::int32_t ID = -1723168340;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class animations final : public Object
{
public:
    std::vector<object_ptr<animation>> animations_;

    animations();

    explicit animations(std::vector<object_ptr<animation>> &&animations_);

    static const std::int32_t ID = 344216945;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class audio final : public Object
{
public:
    std::int32_t duration_;
    std::string title_;
    std::string performer_;
    std::string file_name_;
    std::string mime_type_;
    object_ptr<photoSize> album_cover_thumbnail_;
    object_ptr<file> audio_;

    audio();

    audio(std::int32_t duration_, std::string const &title_, std::string const &performer_,
          std::string const &file_name_, std::string const &mime_type_,
          object_ptr<photoSize> &&album_cover_thumbnail_, object_ptr<file> &&audio_);

    static const std::int32_t ID = 383148432;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authenticationCodeInfo final : public Object
{
public:
    std::string phone_number_;
    object_ptr<AuthenticationCodeType> type_;
    object_ptr<AuthenticationCodeType> next_type_;
    std::int32_t timeout_;

    authenticationCodeInfo();

    authenticationCodeInfo(std::string const &phone_number_, object_ptr<AuthenticationCodeType> &&type_,
                           object_ptr<AuthenticationCodeType> &&next_type_, std::int32_t timeout_);

    static const std::int32_t ID = -860345416;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class AuthenticationCodeType: public Object
{
public:
};

class authenticationCodeTypeTelegramMessage final : public AuthenticationCodeType
{
public:
    std::int32_t length_;

    authenticationCodeTypeTelegramMessage();

    explicit authenticationCodeTypeTelegramMessage(std::int32_t length_);

    static const std::int32_t ID = 2079628074;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authenticationCodeTypeSms final : public AuthenticationCodeType
{
public:
    std::int32_t length_;

    authenticationCodeTypeSms();

    explicit authenticationCodeTypeSms(std::int32_t length_);

    static const std::int32_t ID = 962650760;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authenticationCodeTypeCall final : public AuthenticationCodeType
{
public:
    std::int32_t length_;

    authenticationCodeTypeCall();

    explicit authenticationCodeTypeCall(std::int32_t length_);

    static const std::int32_t ID = 1636265063;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authenticationCodeTypeFlashCall final : public AuthenticationCodeType
{
public:
    std::string pattern_;

    authenticationCodeTypeFlashCall();

    explicit authenticationCodeTypeFlashCall(std::string const &pattern_);

    static const std::int32_t ID = 1395882402;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class AuthorizationState: public Object
{
public:
};

class authorizationStateWaitTdlibParameters final : public AuthorizationState
{
public:

    authorizationStateWaitTdlibParameters();

    static const std::int32_t ID = 904720988;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateWaitEncryptionKey final : public AuthorizationState
{
public:
    bool is_encrypted_;

    authorizationStateWaitEncryptionKey();

    explicit authorizationStateWaitEncryptionKey(bool is_encrypted_);

    static const std::int32_t ID = 612103496;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateWaitPhoneNumber final : public AuthorizationState
{
public:

    authorizationStateWaitPhoneNumber();

    static const std::int32_t ID = 306402531;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateWaitCode final : public AuthorizationState
{
public:
    bool is_registered_;
    object_ptr<authenticationCodeInfo> code_info_;

    authorizationStateWaitCode();

    authorizationStateWaitCode(bool is_registered_, object_ptr<authenticationCodeInfo> &&code_info_);

    static const std::int32_t ID = -483510157;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateWaitPassword final : public AuthorizationState
{
public:
    std::string password_hint_;
    bool has_recovery_email_address_;
    std::string recovery_email_address_pattern_;

    authorizationStateWaitPassword();

    authorizationStateWaitPassword(std::string const &password_hint_, bool has_recovery_email_address_,
                                   std::string const &recovery_email_address_pattern_);

    static const std::int32_t ID = 187548796;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateReady final : public AuthorizationState
{
public:

    authorizationStateReady();

    static const std::int32_t ID = -1834871737;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateLoggingOut final : public AuthorizationState
{
public:

    authorizationStateLoggingOut();

    static const std::int32_t ID = 154449270;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateClosing final : public AuthorizationState
{
public:

    authorizationStateClosing();

    static const std::int32_t ID = 445855311;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateClosed final : public AuthorizationState
{
public:

    authorizationStateClosed();

    static const std::int32_t ID = 1526047584;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class basicGroup final : public Object
{
public:
    std::int32_t id_;
    std::int32_t member_count_;
    object_ptr<ChatMemberStatus> status_;
    bool everyone_is_administrator_;
    bool is_active_;
    std::int32_t upgraded_to_supergroup_id_;

    basicGroup();

    basicGroup(std::int32_t id_, std::int32_t member_count_, object_ptr<ChatMemberStatus> &&status_,
               bool everyone_is_administrator_, bool is_active_, std::int32_t upgraded_to_supergroup_id_);

    static const std::int32_t ID = 1572712718;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class basicGroupFullInfo final : public Object
{
public:
    std::int32_t creator_user_id_;
    std::vector<object_ptr<chatMember>> members_;
    std::string invite_link_;

    basicGroupFullInfo();

    basicGroupFullInfo(std::int32_t creator_user_id_, std::vector<object_ptr<chatMember>> &&members_,
                       std::string const &invite_link_);

    static const std::int32_t ID = 952266076;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class botCommand final : public Object
{
public:
    std::string command_;
    std::string description_;

    botCommand();

    botCommand(std::string const &command_, std::string const &description_);

    static const std::int32_t ID = -1032140601;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class botInfo final : public Object
{
public:
    std::string description_;
    std::vector<object_ptr<botCommand>> commands_;

    botInfo();

    botInfo(std::string const &description_, std::vector<object_ptr<botCommand>> &&commands_);

    static const std::int32_t ID = 1296528907;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class call final : public Object
{
public:
    std::int32_t id_;
    std::int32_t user_id_;
    bool is_outgoing_;
    object_ptr<CallState> state_;

    call();

    call(std::int32_t id_, std::int32_t user_id_, bool is_outgoing_, object_ptr<CallState> &&state_);

    static const std::int32_t ID = -1837599107;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callConnection final : public Object
{
public:
    std::int64_t id_;
    std::string ip_;
    std::string ipv6_;
    std::int32_t port_;
    std::string peer_tag_;

    callConnection();

    callConnection(std::int64_t id_, std::string const &ip_, std::string const &ipv6_,
                   std::int32_t port_, std::string const &peer_tag_);

    static const std::int32_t ID = 1318542714;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class CallDiscardReason: public Object
{
public:
};

class callDiscardReasonEmpty final : public CallDiscardReason
{
public:

    callDiscardReasonEmpty();

    static const std::int32_t ID = -1258917949;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callDiscardReasonMissed final : public CallDiscardReason
{
public:

    callDiscardReasonMissed();

    static const std::int32_t ID = 1680358012;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callDiscardReasonDeclined final : public CallDiscardReason
{
public:

    callDiscardReasonDeclined();

    static const std::int32_t ID = -1729926094;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callDiscardReasonDisconnected final : public CallDiscardReason
{
public:

    callDiscardReasonDisconnected();

    static const std::int32_t ID = -1342872670;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callDiscardReasonHungUp final : public CallDiscardReason
{
public:

    callDiscardReasonHungUp();

    static const std::int32_t ID = 438216166;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callId final : public Object
{
public:
    std::int32_t id_;

    callId();

    explicit callId(std::int32_t id_);

    static const std::int32_t ID = 65717769;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callProtocol final : public Object
{
public:
    bool udp_p2p_;
    bool udp_reflector_;
    std::int32_t min_layer_;
    std::int32_t max_layer_;

    callProtocol();

    callProtocol(bool udp_p2p_, bool udp_reflector_, std::int32_t min_layer_, std::int32_t max_layer_);

    static const std::int32_t ID = -1042830667;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class CallState: public Object
{
public:
};

class callStatePending final : public CallState
{
public:
    bool is_created_;
    bool is_received_;

    callStatePending();

    callStatePending(bool is_created_, bool is_received_);

    static const std::int32_t ID = 1073048620;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callStateExchangingKeys final : public CallState
{
public:

    callStateExchangingKeys();

    static const std::int32_t ID = -1848149403;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callStateReady final : public CallState
{
public:
    object_ptr<callProtocol> protocol_;
    std::vector<object_ptr<callConnection>> connections_;
    std::string config_;
    std::string encryption_key_;
    std::vector<std::string> emojis_;

    callStateReady();

    callStateReady(object_ptr<callProtocol> &&protocol_,
                   std::vector<object_ptr<callConnection>> &&connections_, std::string const &config_,
                   std::string const &encryption_key_, std::vector<std::string> &&emojis_);

    static const std::int32_t ID = 1518705438;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callStateHangingUp final : public CallState
{
public:

    callStateHangingUp();

    static const std::int32_t ID = -2133790038;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callStateDiscarded final : public CallState
{
public:
    object_ptr<CallDiscardReason> reason_;
    bool need_rating_;
    bool need_debug_information_;

    callStateDiscarded();

    callStateDiscarded(object_ptr<CallDiscardReason> &&reason_, bool need_rating_,
                       bool need_debug_information_);

    static const std::int32_t ID = -190853167;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callStateError final : public CallState
{
public:
    object_ptr<error> error_;

    callStateError();

    explicit callStateError(object_ptr<error> &&error_);

    static const std::int32_t ID = -975215467;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callbackQueryAnswer final : public Object
{
public:
    std::string text_;
    bool show_alert_;
    std::string url_;

    callbackQueryAnswer();

    callbackQueryAnswer(std::string const &text_, bool show_alert_, std::string const &url_);

    static const std::int32_t ID = 360867933;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class CallbackQueryPayload: public Object
{
public:
};

class callbackQueryPayloadData final : public CallbackQueryPayload
{
public:
    std::string data_;

    callbackQueryPayloadData();

    explicit callbackQueryPayloadData(std::string const &data_);

    static const std::int32_t ID = -1977729946;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callbackQueryPayloadGame final : public CallbackQueryPayload
{
public:
    std::string game_short_name_;

    callbackQueryPayloadGame();

    explicit callbackQueryPayloadGame(std::string const &game_short_name_);

    static const std::int32_t ID = 1303571512;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chat final : public Object
{
public:
    std::int64_t id_;
    object_ptr<ChatType> type_;
    std::string title_;
    object_ptr<chatPhoto> photo_;
    object_ptr<message> last_message_;
    std::int64_t order_;
    bool is_pinned_;
    bool can_be_reported_;
    std::int32_t unread_count_;
    std::int64_t last_read_inbox_message_id_;
    std::int64_t last_read_outbox_message_id_;
    std::int32_t unread_mention_count_;
    object_ptr<notificationSettings> notification_settings_;
    std::int64_t reply_markup_message_id_;
    object_ptr<draftMessage> draft_message_;
    std::string client_data_;

    chat();

    chat(std::int64_t id_, object_ptr<ChatType> &&type_, std::string const &title_,
         object_ptr<chatPhoto> &&photo_, object_ptr<message> &&last_message_, std::int64_t order_,
         bool is_pinned_, bool can_be_reported_, std::int32_t unread_count_,
         std::int64_t last_read_inbox_message_id_, std::int64_t last_read_outbox_message_id_,
         std::int32_t unread_mention_count_, object_ptr<notificationSettings> &&notification_settings_,
         std::int64_t reply_markup_message_id_, object_ptr<draftMessage> &&draft_message_,
         std::string const &client_data_);

    static const std::int32_t ID = -1599984597;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ChatAction: public Object
{
public:
};

class chatActionTyping final : public ChatAction
{
public:

    chatActionTyping();

    static const std::int32_t ID = 380122167;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionRecordingVideo final : public ChatAction
{
public:

    chatActionRecordingVideo();

    static const std::int32_t ID = 216553362;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingVideo final : public ChatAction
{
public:
    std::int32_t progress_;

    chatActionUploadingVideo();

    explicit chatActionUploadingVideo(std::int32_t progress_);

    static const std::int32_t ID = 1234185270;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionRecordingVoiceNote final : public ChatAction
{
public:

    chatActionRecordingVoiceNote();

    static const std::int32_t ID = -808850058;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingVoiceNote final : public ChatAction
{
public:
    std::int32_t progress_;

    chatActionUploadingVoiceNote();

    explicit chatActionUploadingVoiceNote(std::int32_t progress_);

    static const std::int32_t ID = -613643666;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingPhoto final : public ChatAction
{
public:
    std::int32_t progress_;

    chatActionUploadingPhoto();

    explicit chatActionUploadingPhoto(std::int32_t progress_);

    static const std::int32_t ID = 654240583;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingDocument final : public ChatAction
{
public:
    std::int32_t progress_;

    chatActionUploadingDocument();

    explicit chatActionUploadingDocument(std::int32_t progress_);

    static const std::int32_t ID = 167884362;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionChoosingLocation final : public ChatAction
{
public:

    chatActionChoosingLocation();

    static const std::int32_t ID = -2017893596;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionChoosingContact final : public ChatAction
{
public:

    chatActionChoosingContact();

    static const std::int32_t ID = -1222507496;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionStartPlayingGame final : public ChatAction
{
public:

    chatActionStartPlayingGame();

    static const std::int32_t ID = -865884164;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionRecordingVideoNote final : public ChatAction
{
public:

    chatActionRecordingVideoNote();

    static const std::int32_t ID = 16523393;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingVideoNote final : public ChatAction
{
public:
    std::int32_t progress_;

    chatActionUploadingVideoNote();

    explicit chatActionUploadingVideoNote(std::int32_t progress_);

    static const std::int32_t ID = 1172364918;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionCancel final : public ChatAction
{
public:

    chatActionCancel();

    static const std::int32_t ID = 1160523958;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEvent final : public Object
{
public:
    std::int64_t id_;
    std::int32_t date_;
    std::int32_t user_id_;
    object_ptr<ChatEventAction> action_;

    chatEvent();

    chatEvent(std::int64_t id_, std::int32_t date_, std::int32_t user_id_,
              object_ptr<ChatEventAction> &&action_);

    static const std::int32_t ID = -609912404;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ChatEventAction: public Object
{
public:
};

class chatEventMessageEdited final : public ChatEventAction
{
public:
    object_ptr<message> old_message_;
    object_ptr<message> new_message_;

    chatEventMessageEdited();

    chatEventMessageEdited(object_ptr<message> &&old_message_, object_ptr<message> &&new_message_);

    static const std::int32_t ID = -430967304;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMessageDeleted final : public ChatEventAction
{
public:
    object_ptr<message> message_;

    chatEventMessageDeleted();

    explicit chatEventMessageDeleted(object_ptr<message> &&message_);

    static const std::int32_t ID = -892974601;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMessagePinned final : public ChatEventAction
{
public:
    object_ptr<message> message_;

    chatEventMessagePinned();

    explicit chatEventMessagePinned(object_ptr<message> &&message_);

    static const std::int32_t ID = 438742298;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMessageUnpinned final : public ChatEventAction
{
public:

    chatEventMessageUnpinned();

    static const std::int32_t ID = 2002594849;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberJoined final : public ChatEventAction
{
public:

    chatEventMemberJoined();

    static const std::int32_t ID = -235468508;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberLeft final : public ChatEventAction
{
public:

    chatEventMemberLeft();

    static const std::int32_t ID = -948420593;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberInvited final : public ChatEventAction
{
public:
    std::int32_t user_id_;
    object_ptr<ChatMemberStatus> status_;

    chatEventMemberInvited();

    chatEventMemberInvited(std::int32_t user_id_, object_ptr<ChatMemberStatus> &&status_);

    static const std::int32_t ID = -2093688706;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberPromoted final : public ChatEventAction
{
public:
    std::int32_t user_id_;
    object_ptr<ChatMemberStatus> old_status_;
    object_ptr<ChatMemberStatus> new_status_;

    chatEventMemberPromoted();

    chatEventMemberPromoted(std::int32_t user_id_, object_ptr<ChatMemberStatus> &&old_status_,
                            object_ptr<ChatMemberStatus> &&new_status_);

    static const std::int32_t ID = 1887176186;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberRestricted final : public ChatEventAction
{
public:
    std::int32_t user_id_;
    object_ptr<ChatMemberStatus> old_status_;
    object_ptr<ChatMemberStatus> new_status_;

    chatEventMemberRestricted();

    chatEventMemberRestricted(std::int32_t user_id_, object_ptr<ChatMemberStatus> &&old_status_,
                              object_ptr<ChatMemberStatus> &&new_status_);

    static const std::int32_t ID = 584946294;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventTitleChanged final : public ChatEventAction
{
public:
    std::string old_title_;
    std::string new_title_;

    chatEventTitleChanged();

    chatEventTitleChanged(std::string const &old_title_, std::string const &new_title_);

    static const std::int32_t ID = 1134103250;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventDescriptionChanged final : public ChatEventAction
{
public:
    std::string old_description_;
    std::string new_description_;

    chatEventDescriptionChanged();

    chatEventDescriptionChanged(std::string const &old_description_,
                                std::string const &new_description_);

    static const std::int32_t ID = 39112478;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventUsernameChanged final : public ChatEventAction
{
public:
    std::string old_username_;
    std::string new_username_;

    chatEventUsernameChanged();

    chatEventUsernameChanged(std::string const &old_username_, std::string const &new_username_);

    static const std::int32_t ID = 1728558443;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventPhotoChanged final : public ChatEventAction
{
public:
    object_ptr<chatPhoto> old_photo_;
    object_ptr<chatPhoto> new_photo_;

    chatEventPhotoChanged();

    chatEventPhotoChanged(object_ptr<chatPhoto> &&old_photo_, object_ptr<chatPhoto> &&new_photo_);

    static const std::int32_t ID = -811572541;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventInvitesToggled final : public ChatEventAction
{
public:
    bool anyone_can_invite_;

    chatEventInvitesToggled();

    explicit chatEventInvitesToggled(bool anyone_can_invite_);

    static const std::int32_t ID = 568706937;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventSignMessagesToggled final : public ChatEventAction
{
public:
    bool sign_messages_;

    chatEventSignMessagesToggled();

    explicit chatEventSignMessagesToggled(bool sign_messages_);

    static const std::int32_t ID = -1313265634;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventStickerSetChanged final : public ChatEventAction
{
public:
    std::int64_t old_sticker_set_id_;
    std::int64_t new_sticker_set_id_;

    chatEventStickerSetChanged();

    chatEventStickerSetChanged(std::int64_t old_sticker_set_id_, std::int64_t new_sticker_set_id_);

    static const std::int32_t ID = -1243130481;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventIsAllHistoryAvailableToggled final : public ChatEventAction
{
public:
    bool is_all_history_available_;

    chatEventIsAllHistoryAvailableToggled();

    explicit chatEventIsAllHistoryAvailableToggled(bool is_all_history_available_);

    static const std::int32_t ID = -1599063019;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventLogFilters final : public Object
{
public:
    bool message_edits_;
    bool message_deletions_;
    bool message_pins_;
    bool member_joins_;
    bool member_leaves_;
    bool member_invites_;
    bool member_promotions_;
    bool member_restrictions_;
    bool info_changes_;
    bool setting_changes_;

    chatEventLogFilters();

    chatEventLogFilters(bool message_edits_, bool message_deletions_, bool message_pins_,
                        bool member_joins_, bool member_leaves_, bool member_invites_, bool member_promotions_,
                        bool member_restrictions_, bool info_changes_, bool setting_changes_);

    static const std::int32_t ID = 941939684;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEvents final : public Object
{
public:
    std::vector<object_ptr<chatEvent>> events_;

    chatEvents();

    explicit chatEvents(std::vector<object_ptr<chatEvent>> &&events_);

    static const std::int32_t ID = -585329664;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatInviteLink final : public Object
{
public:
    std::string invite_link_;

    chatInviteLink();

    explicit chatInviteLink(std::string const &invite_link_);

    static const std::int32_t ID = -882072492;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatInviteLinkInfo final : public Object
{
public:
    std::int64_t chat_id_;
    object_ptr<ChatType> type_;
    std::string title_;
    object_ptr<chatPhoto> photo_;
    std::int32_t member_count_;
    std::vector<std::int32_t> member_user_ids_;
    bool is_public_;

    chatInviteLinkInfo();

    chatInviteLinkInfo(std::int64_t chat_id_, object_ptr<ChatType> &&type_, std::string const &title_,
                       object_ptr<chatPhoto> &&photo_, std::int32_t member_count_,
                       std::vector<std::int32_t> &&member_user_ids_, bool is_public_);

    static const std::int32_t ID = -323394424;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMember final : public Object
{
public:
    std::int32_t user_id_;
    std::int32_t inviter_user_id_;
    std::int32_t joined_chat_date_;
    object_ptr<ChatMemberStatus> status_;
    object_ptr<botInfo> bot_info_;

    chatMember();

    chatMember(std::int32_t user_id_, std::int32_t inviter_user_id_, std::int32_t joined_chat_date_,
               object_ptr<ChatMemberStatus> &&status_, object_ptr<botInfo> &&bot_info_);

    static const std::int32_t ID = -806137076;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ChatMemberStatus: public Object
{
public:
};

class chatMemberStatusCreator final : public ChatMemberStatus
{
public:
    bool is_member_;

    chatMemberStatusCreator();

    explicit chatMemberStatusCreator(bool is_member_);

    static const std::int32_t ID = 1756320508;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusAdministrator final : public ChatMemberStatus
{
public:
    bool can_be_edited_;
    bool can_change_info_;
    bool can_post_messages_;
    bool can_edit_messages_;
    bool can_delete_messages_;
    bool can_invite_users_;
    bool can_restrict_members_;
    bool can_pin_messages_;
    bool can_promote_members_;

    chatMemberStatusAdministrator();

    chatMemberStatusAdministrator(bool can_be_edited_, bool can_change_info_, bool can_post_messages_,
                                  bool can_edit_messages_, bool can_delete_messages_, bool can_invite_users_,
                                  bool can_restrict_members_, bool can_pin_messages_, bool can_promote_members_);

    static const std::int32_t ID = 45106688;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusMember final : public ChatMemberStatus
{
public:

    chatMemberStatusMember();

    static const std::int32_t ID = 844723285;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusRestricted final : public ChatMemberStatus
{
public:
    bool is_member_;
    std::int32_t restricted_until_date_;
    bool can_send_messages_;
    bool can_send_media_messages_;
    bool can_send_other_messages_;
    bool can_add_web_page_previews_;

    chatMemberStatusRestricted();

    chatMemberStatusRestricted(bool is_member_, std::int32_t restricted_until_date_,
                               bool can_send_messages_, bool can_send_media_messages_, bool can_send_other_messages_,
                               bool can_add_web_page_previews_);

    static const std::int32_t ID = 2068116214;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusLeft final : public ChatMemberStatus
{
public:

    chatMemberStatusLeft();

    static const std::int32_t ID = -5815259;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusBanned final : public ChatMemberStatus
{
public:
    std::int32_t banned_until_date_;

    chatMemberStatusBanned();

    explicit chatMemberStatusBanned(std::int32_t banned_until_date_);

    static const std::int32_t ID = -1653518666;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMembers final : public Object
{
public:
    std::int32_t total_count_;
    std::vector<object_ptr<chatMember>> members_;

    chatMembers();

    chatMembers(std::int32_t total_count_, std::vector<object_ptr<chatMember>> &&members_);

    static const std::int32_t ID = -497558622;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatPhoto final : public Object
{
public:
    object_ptr<file> small_;
    object_ptr<file> big_;

    chatPhoto();

    chatPhoto(object_ptr<file> &&small_, object_ptr<file> &&big_);

    static const std::int32_t ID = -217062456;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ChatReportReason: public Object
{
public:
};

class chatReportReasonSpam final : public ChatReportReason
{
public:

    chatReportReasonSpam();

    static const std::int32_t ID = -510848863;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatReportReasonViolence final : public ChatReportReason
{
public:

    chatReportReasonViolence();

    static const std::int32_t ID = -1330235395;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatReportReasonPornography final : public ChatReportReason
{
public:

    chatReportReasonPornography();

    static const std::int32_t ID = 722614385;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatReportReasonCustom final : public ChatReportReason
{
public:
    std::string text_;

    chatReportReasonCustom();

    explicit chatReportReasonCustom(std::string const &text_);

    static const std::int32_t ID = 544575454;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatReportSpamState final : public Object
{
public:
    bool can_report_spam_;

    chatReportSpamState();

    explicit chatReportSpamState(bool can_report_spam_);

    static const std::int32_t ID = -1919240972;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ChatType: public Object
{
public:
};

class chatTypePrivate final : public ChatType
{
public:
    std::int32_t user_id_;

    chatTypePrivate();

    explicit chatTypePrivate(std::int32_t user_id_);

    static const std::int32_t ID = 1700720838;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatTypeBasicGroup final : public ChatType
{
public:
    std::int32_t basic_group_id_;

    chatTypeBasicGroup();

    explicit chatTypeBasicGroup(std::int32_t basic_group_id_);

    static const std::int32_t ID = 21815278;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatTypeSupergroup final : public ChatType
{
public:
    std::int32_t supergroup_id_;
    bool is_channel_;

    chatTypeSupergroup();

    chatTypeSupergroup(std::int32_t supergroup_id_, bool is_channel_);

    static const std::int32_t ID = 955152366;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatTypeSecret final : public ChatType
{
public:
    std::int32_t secret_chat_id_;
    std::int32_t user_id_;

    chatTypeSecret();

    chatTypeSecret(std::int32_t secret_chat_id_, std::int32_t user_id_);

    static const std::int32_t ID = 136722563;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chats final : public Object
{
public:
    std::vector<std::int64_t> chat_ids_;

    chats();

    explicit chats(std::vector<std::int64_t> &&chat_ids_);

    static const std::int32_t ID = -1687756019;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class CheckChatUsernameResult: public Object
{
public:
};

class checkChatUsernameResultOk final : public CheckChatUsernameResult
{
public:

    checkChatUsernameResultOk();

    static const std::int32_t ID = -1498956964;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkChatUsernameResultUsernameInvalid final : public CheckChatUsernameResult
{
public:

    checkChatUsernameResultUsernameInvalid();

    static const std::int32_t ID = -636979370;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkChatUsernameResultUsernameOccupied final : public CheckChatUsernameResult
{
public:

    checkChatUsernameResultUsernameOccupied();

    static const std::int32_t ID = 1320892201;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkChatUsernameResultPublicChatsTooMuch final : public CheckChatUsernameResult
{
public:

    checkChatUsernameResultPublicChatsTooMuch();

    static const std::int32_t ID = 858247741;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkChatUsernameResultPublicGroupsUnavailable final : public CheckChatUsernameResult
{
public:

    checkChatUsernameResultPublicGroupsUnavailable();

    static const std::int32_t ID = -51833641;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectedWebsite final : public Object
{
public:
    std::int64_t id_;
    std::string domain_name_;
    std::int32_t bot_user_id_;
    std::string browser_;
    std::string platform_;
    std::int32_t log_in_date_;
    std::int32_t last_active_date_;
    std::string ip_;
    std::string location_;

    connectedWebsite();

    connectedWebsite(std::int64_t id_, std::string const &domain_name_, std::int32_t bot_user_id_,
                     std::string const &browser_, std::string const &platform_, std::int32_t log_in_date_,
                     std::int32_t last_active_date_, std::string const &ip_, std::string const &location_);

    static const std::int32_t ID = -1538986855;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectedWebsites final : public Object
{
public:
    std::vector<object_ptr<connectedWebsite>> websites_;

    connectedWebsites();

    explicit connectedWebsites(std::vector<object_ptr<connectedWebsite>> &&websites_);

    static const std::int32_t ID = -1727949694;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ConnectionState: public Object
{
public:
};

class connectionStateWaitingForNetwork final : public ConnectionState
{
public:

    connectionStateWaitingForNetwork();

    static const std::int32_t ID = 1695405912;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectionStateConnectingToProxy final : public ConnectionState
{
public:

    connectionStateConnectingToProxy();

    static const std::int32_t ID = -93187239;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectionStateConnecting final : public ConnectionState
{
public:

    connectionStateConnecting();

    static const std::int32_t ID = -1298400670;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectionStateUpdating final : public ConnectionState
{
public:

    connectionStateUpdating();

    static const std::int32_t ID = -188104009;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectionStateReady final : public ConnectionState
{
public:

    connectionStateReady();

    static const std::int32_t ID = 48608492;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class contact final : public Object
{
public:
    std::string phone_number_;
    std::string first_name_;
    std::string last_name_;
    std::int32_t user_id_;

    contact();

    contact(std::string const &phone_number_, std::string const &first_name_,
            std::string const &last_name_, std::int32_t user_id_);

    static const std::int32_t ID = -2035981269;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class count final : public Object
{
public:
    std::int32_t count_;

    count();

    explicit count(std::int32_t count_);

    static const std::int32_t ID = 1295577348;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class customRequestResult final : public Object
{
public:
    std::string result_;

    customRequestResult();

    explicit customRequestResult(std::string const &result_);

    static const std::int32_t ID = -2009960452;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class DeviceToken: public Object
{
public:
};

class deviceTokenGoogleCloudMessaging final : public DeviceToken
{
public:
    std::string token_;

    deviceTokenGoogleCloudMessaging();

    explicit deviceTokenGoogleCloudMessaging(std::string const &token_);

    static const std::int32_t ID = 1092220225;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenApplePush final : public DeviceToken
{
public:
    std::string device_token_;
    bool is_app_sandbox_;

    deviceTokenApplePush();

    deviceTokenApplePush(std::string const &device_token_, bool is_app_sandbox_);

    static const std::int32_t ID = 387541955;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenApplePushVoIP final : public DeviceToken
{
public:
    std::string device_token_;
    bool is_app_sandbox_;

    deviceTokenApplePushVoIP();

    deviceTokenApplePushVoIP(std::string const &device_token_, bool is_app_sandbox_);

    static const std::int32_t ID = -327676505;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenWindowsPush final : public DeviceToken
{
public:
    std::string access_token_;

    deviceTokenWindowsPush();

    explicit deviceTokenWindowsPush(std::string const &access_token_);

    static const std::int32_t ID = -1410514289;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenMicrosoftPush final : public DeviceToken
{
public:
    std::string channel_uri_;

    deviceTokenMicrosoftPush();

    explicit deviceTokenMicrosoftPush(std::string const &channel_uri_);

    static const std::int32_t ID = 1224269900;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenMicrosoftPushVoIP final : public DeviceToken
{
public:
    std::string channel_uri_;

    deviceTokenMicrosoftPushVoIP();

    explicit deviceTokenMicrosoftPushVoIP(std::string const &channel_uri_);

    static const std::int32_t ID = -785603759;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenWebPush final : public DeviceToken
{
public:
    std::string endpoint_;
    std::string p256dh_base64url_;
    std::string auth_base64url_;

    deviceTokenWebPush();

    deviceTokenWebPush(std::string const &endpoint_, std::string const &p256dh_base64url_,
                       std::string const &auth_base64url_);

    static const std::int32_t ID = -1694507273;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenSimplePush final : public DeviceToken
{
public:
    std::string endpoint_;

    deviceTokenSimplePush();

    explicit deviceTokenSimplePush(std::string const &endpoint_);

    static const std::int32_t ID = 49584736;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenUbuntuPush final : public DeviceToken
{
public:
    std::string token_;

    deviceTokenUbuntuPush();

    explicit deviceTokenUbuntuPush(std::string const &token_);

    static const std::int32_t ID = 1782320422;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenBlackBerryPush final : public DeviceToken
{
public:
    std::string token_;

    deviceTokenBlackBerryPush();

    explicit deviceTokenBlackBerryPush(std::string const &token_);

    static const std::int32_t ID = 1559167234;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenTizenPush final : public DeviceToken
{
public:
    std::string reg_id_;

    deviceTokenTizenPush();

    explicit deviceTokenTizenPush(std::string const &reg_id_);

    static const std::int32_t ID = -1359947213;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class document final : public Object
{
public:
    std::string file_name_;
    std::string mime_type_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> document_;

    document();

    document(std::string const &file_name_, std::string const &mime_type_,
             object_ptr<photoSize> &&thumbnail_, object_ptr<file> &&document_);

    static const std::int32_t ID = -736037786;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class draftMessage final : public Object
{
public:
    std::int64_t reply_to_message_id_;
    object_ptr<InputMessageContent> input_message_text_;

    draftMessage();

    draftMessage(std::int64_t reply_to_message_id_,
                 object_ptr<InputMessageContent> &&input_message_text_);

    static const std::int32_t ID = 1902914742;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class error final : public Object
{
public:
    std::int32_t code_;
    std::string message_;

    error();

    error(std::int32_t code_, std::string const &message_);

    static const std::int32_t ID = -1679978726;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class file final : public Object
{
public:
    std::int32_t id_;
    std::int32_t size_;
    std::int32_t expected_size_;
    object_ptr<localFile> local_;
    object_ptr<remoteFile> remote_;

    file();

    file(std::int32_t id_, std::int32_t size_, std::int32_t expected_size_,
         object_ptr<localFile> &&local_, object_ptr<remoteFile> &&remote_);

    static const std::int32_t ID = 766337656;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class FileType: public Object
{
public:
};

class fileTypeNone final : public FileType
{
public:

    fileTypeNone();

    static const std::int32_t ID = 2003009189;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeAnimation final : public FileType
{
public:

    fileTypeAnimation();

    static const std::int32_t ID = -290816582;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeAudio final : public FileType
{
public:

    fileTypeAudio();

    static const std::int32_t ID = -709112160;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeDocument final : public FileType
{
public:

    fileTypeDocument();

    static const std::int32_t ID = -564722929;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypePhoto final : public FileType
{
public:

    fileTypePhoto();

    static const std::int32_t ID = -1718914651;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeProfilePhoto final : public FileType
{
public:

    fileTypeProfilePhoto();

    static const std::int32_t ID = 1795089315;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeSecret final : public FileType
{
public:

    fileTypeSecret();

    static const std::int32_t ID = -1871899401;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeSticker final : public FileType
{
public:

    fileTypeSticker();

    static const std::int32_t ID = 475233385;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeThumbnail final : public FileType
{
public:

    fileTypeThumbnail();

    static const std::int32_t ID = -12443298;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeUnknown final : public FileType
{
public:

    fileTypeUnknown();

    static const std::int32_t ID = -2011566768;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeVideo final : public FileType
{
public:

    fileTypeVideo();

    static const std::int32_t ID = 1430816539;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeVideoNote final : public FileType
{
public:

    fileTypeVideoNote();

    static const std::int32_t ID = -518412385;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeVoiceNote final : public FileType
{
public:

    fileTypeVoiceNote();

    static const std::int32_t ID = -588681661;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeWallpaper final : public FileType
{
public:

    fileTypeWallpaper();

    static const std::int32_t ID = 1854930076;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeSecretThumbnail final : public FileType
{
public:

    fileTypeSecretThumbnail();

    static const std::int32_t ID = -1401326026;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class formattedText final : public Object
{
public:
    std::string text_;
    std::vector<object_ptr<textEntity>> entities_;

    formattedText();

    formattedText(std::string const &text_, std::vector<object_ptr<textEntity>> &&entities_);

    static const std::int32_t ID = -252624564;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class foundMessages final : public Object
{
public:
    std::vector<object_ptr<message>> messages_;
    std::int64_t next_from_search_id_;

    foundMessages();

    foundMessages(std::vector<object_ptr<message>> &&messages_, std::int64_t next_from_search_id_);

    static const std::int32_t ID = 2135623881;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class game final : public Object
{
public:
    std::int64_t id_;
    std::string short_name_;
    std::string title_;
    object_ptr<formattedText> text_;
    std::string description_;
    object_ptr<photo> photo_;
    object_ptr<animation> animation_;

    game();

    game(std::int64_t id_, std::string const &short_name_, std::string const &title_,
         object_ptr<formattedText> &&text_, std::string const &description_, object_ptr<photo> &&photo_,
         object_ptr<animation> &&animation_);

    static const std::int32_t ID = -1565597752;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class gameHighScore final : public Object
{
public:
    std::int32_t position_;
    std::int32_t user_id_;
    std::int32_t score_;

    gameHighScore();

    gameHighScore(std::int32_t position_, std::int32_t user_id_, std::int32_t score_);

    static const std::int32_t ID = -30778358;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class gameHighScores final : public Object
{
public:
    std::vector<object_ptr<gameHighScore>> scores_;

    gameHighScores();

    explicit gameHighScores(std::vector<object_ptr<gameHighScore>> &&scores_);

    static const std::int32_t ID = -725770727;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class hashtags final : public Object
{
public:
    std::vector<std::string> hashtags_;

    hashtags();

    explicit hashtags(std::vector<std::string> &&hashtags_);

    static const std::int32_t ID = 676798885;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class importedContacts final : public Object
{
public:
    std::vector<std::int32_t> user_ids_;
    std::vector<std::int32_t> importer_count_;

    importedContacts();

    importedContacts(std::vector<std::int32_t> &&user_ids_,
                     std::vector<std::int32_t> &&importer_count_);

    static const std::int32_t ID = -741685354;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineKeyboardButton final : public Object
{
public:
    std::string text_;
    object_ptr<InlineKeyboardButtonType> type_;

    inlineKeyboardButton();

    inlineKeyboardButton(std::string const &text_, object_ptr<InlineKeyboardButtonType> &&type_);

    static const std::int32_t ID = -372105704;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class InlineKeyboardButtonType: public Object
{
public:
};

class inlineKeyboardButtonTypeUrl final : public InlineKeyboardButtonType
{
public:
    std::string url_;

    inlineKeyboardButtonTypeUrl();

    explicit inlineKeyboardButtonTypeUrl(std::string const &url_);

    static const std::int32_t ID = 1130741420;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineKeyboardButtonTypeCallback final : public InlineKeyboardButtonType
{
public:
    std::string data_;

    inlineKeyboardButtonTypeCallback();

    explicit inlineKeyboardButtonTypeCallback(std::string const &data_);

    static const std::int32_t ID = -1127515139;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineKeyboardButtonTypeCallbackGame final : public InlineKeyboardButtonType
{
public:

    inlineKeyboardButtonTypeCallbackGame();

    static const std::int32_t ID = -383429528;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineKeyboardButtonTypeSwitchInline final : public InlineKeyboardButtonType
{
public:
    std::string query_;
    bool in_current_chat_;

    inlineKeyboardButtonTypeSwitchInline();

    inlineKeyboardButtonTypeSwitchInline(std::string const &query_, bool in_current_chat_);

    static const std::int32_t ID = -2035563307;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineKeyboardButtonTypeBuy final : public InlineKeyboardButtonType
{
public:

    inlineKeyboardButtonTypeBuy();

    static const std::int32_t ID = 1360739440;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class InlineQueryResult: public Object
{
public:
};

class inlineQueryResultArticle final : public InlineQueryResult
{
public:
    std::string id_;
    std::string url_;
    bool hide_url_;
    std::string title_;
    std::string description_;
    object_ptr<photoSize> thumbnail_;

    inlineQueryResultArticle();

    inlineQueryResultArticle(std::string const &id_, std::string const &url_, bool hide_url_,
                             std::string const &title_, std::string const &description_, object_ptr<photoSize> &&thumbnail_);

    static const std::int32_t ID = -518366710;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultContact final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<contact> contact_;
    object_ptr<photoSize> thumbnail_;

    inlineQueryResultContact();

    inlineQueryResultContact(std::string const &id_, object_ptr<contact> &&contact_,
                             object_ptr<photoSize> &&thumbnail_);

    static const std::int32_t ID = 410081985;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultLocation final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<location> location_;
    std::string title_;
    object_ptr<photoSize> thumbnail_;

    inlineQueryResultLocation();

    inlineQueryResultLocation(std::string const &id_, object_ptr<location> &&location_,
                              std::string const &title_, object_ptr<photoSize> &&thumbnail_);

    static const std::int32_t ID = -158305341;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultVenue final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<venue> venue_;
    object_ptr<photoSize> thumbnail_;

    inlineQueryResultVenue();

    inlineQueryResultVenue(std::string const &id_, object_ptr<venue> &&venue_,
                           object_ptr<photoSize> &&thumbnail_);

    static const std::int32_t ID = -1592932211;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultGame final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<game> game_;

    inlineQueryResultGame();

    inlineQueryResultGame(std::string const &id_, object_ptr<game> &&game_);

    static const std::int32_t ID = 1706916987;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultAnimation final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<animation> animation_;
    std::string title_;

    inlineQueryResultAnimation();

    inlineQueryResultAnimation(std::string const &id_, object_ptr<animation> &&animation_,
                               std::string const &title_);

    static const std::int32_t ID = 2009984267;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultAudio final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<audio> audio_;

    inlineQueryResultAudio();

    inlineQueryResultAudio(std::string const &id_, object_ptr<audio> &&audio_);

    static const std::int32_t ID = 842650360;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultDocument final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<document> document_;
    std::string title_;
    std::string description_;

    inlineQueryResultDocument();

    inlineQueryResultDocument(std::string const &id_, object_ptr<document> &&document_,
                              std::string const &title_, std::string const &description_);

    static const std::int32_t ID = -1491268539;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultPhoto final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<photo> photo_;
    std::string title_;
    std::string description_;

    inlineQueryResultPhoto();

    inlineQueryResultPhoto(std::string const &id_, object_ptr<photo> &&photo_,
                           std::string const &title_, std::string const &description_);

    static const std::int32_t ID = 1848319440;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultSticker final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<sticker> sticker_;

    inlineQueryResultSticker();

    inlineQueryResultSticker(std::string const &id_, object_ptr<sticker> &&sticker_);

    static const std::int32_t ID = -1848224245;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultVideo final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<video> video_;
    std::string title_;
    std::string description_;

    inlineQueryResultVideo();

    inlineQueryResultVideo(std::string const &id_, object_ptr<video> &&video_,
                           std::string const &title_, std::string const &description_);

    static const std::int32_t ID = -1373158683;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResultVoiceNote final : public InlineQueryResult
{
public:
    std::string id_;
    object_ptr<voiceNote> voice_note_;
    std::string title_;

    inlineQueryResultVoiceNote();

    inlineQueryResultVoiceNote(std::string const &id_, object_ptr<voiceNote> &&voice_note_,
                               std::string const &title_);

    static const std::int32_t ID = -1897393105;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResults final : public Object
{
public:
    std::int64_t inline_query_id_;
    std::string next_offset_;
    std::vector<object_ptr<InlineQueryResult>> results_;
    std::string switch_pm_text_;
    std::string switch_pm_parameter_;

    inlineQueryResults();

    inlineQueryResults(std::int64_t inline_query_id_, std::string const &next_offset_,
                       std::vector<object_ptr<InlineQueryResult>> &&results_, std::string const &switch_pm_text_,
                       std::string const &switch_pm_parameter_);

    static const std::int32_t ID = 1000709656;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class InputCredentials: public Object
{
public:
};

class inputCredentialsSaved final : public InputCredentials
{
public:
    std::string saved_credentials_id_;

    inputCredentialsSaved();

    explicit inputCredentialsSaved(std::string const &saved_credentials_id_);

    static const std::int32_t ID = -2034385364;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputCredentialsNew final : public InputCredentials
{
public:
    std::string data_;
    bool allow_save_;

    inputCredentialsNew();

    inputCredentialsNew(std::string const &data_, bool allow_save_);

    static const std::int32_t ID = -829689558;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputCredentialsAndroidPay final : public InputCredentials
{
public:
    std::string data_;

    inputCredentialsAndroidPay();

    explicit inputCredentialsAndroidPay(std::string const &data_);

    static const std::int32_t ID = 1979566832;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputCredentialsApplePay final : public InputCredentials
{
public:
    std::string data_;

    inputCredentialsApplePay();

    explicit inputCredentialsApplePay(std::string const &data_);

    static const std::int32_t ID = -1246570799;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class InputFile: public Object
{
public:
};

class inputFileId final : public InputFile
{
public:
    std::int32_t id_;

    inputFileId();

    explicit inputFileId(std::int32_t id_);

    static const std::int32_t ID = 1788906253;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputFileRemote final : public InputFile
{
public:
    std::string id_;

    inputFileRemote();

    explicit inputFileRemote(std::string const &id_);

    static const std::int32_t ID = -107574466;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputFileLocal final : public InputFile
{
public:
    std::string path_;

    inputFileLocal();

    explicit inputFileLocal(std::string const &path_);

    static const std::int32_t ID = 2056030919;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputFileGenerated final : public InputFile
{
public:
    std::string original_path_;
    std::string conversion_;
    std::int32_t expected_size_;

    inputFileGenerated();

    inputFileGenerated(std::string const &original_path_, std::string const &conversion_,
                       std::int32_t expected_size_);

    static const std::int32_t ID = -1781351885;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class InputInlineQueryResult: public Object
{
public:
};

class inputInlineQueryResultAnimatedGif final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string title_;
    std::string thumbnail_url_;
    std::string gif_url_;
    std::int32_t gif_duration_;
    std::int32_t gif_width_;
    std::int32_t gif_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultAnimatedGif();

    inputInlineQueryResultAnimatedGif(std::string const &id_, std::string const &title_,
                                      std::string const &thumbnail_url_, std::string const &gif_url_, std::int32_t gif_duration_,
                                      std::int32_t gif_width_, std::int32_t gif_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                      object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = -891474894;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultAnimatedMpeg4 final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string title_;
    std::string thumbnail_url_;
    std::string mpeg4_url_;
    std::int32_t mpeg4_duration_;
    std::int32_t mpeg4_width_;
    std::int32_t mpeg4_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultAnimatedMpeg4();

    inputInlineQueryResultAnimatedMpeg4(std::string const &id_, std::string const &title_,
                                        std::string const &thumbnail_url_, std::string const &mpeg4_url_, std::int32_t mpeg4_duration_,
                                        std::int32_t mpeg4_width_, std::int32_t mpeg4_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                        object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = -1629529888;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultArticle final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string url_;
    bool hide_url_;
    std::string title_;
    std::string description_;
    std::string thumbnail_url_;
    std::int32_t thumbnail_width_;
    std::int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultArticle();

    inputInlineQueryResultArticle(std::string const &id_, std::string const &url_, bool hide_url_,
                                  std::string const &title_, std::string const &description_, std::string const &thumbnail_url_,
                                  std::int32_t thumbnail_width_, std::int32_t thumbnail_height_,
                                  object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 1973670156;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultAudio final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string title_;
    std::string performer_;
    std::string audio_url_;
    std::int32_t audio_duration_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultAudio();

    inputInlineQueryResultAudio(std::string const &id_, std::string const &title_,
                                std::string const &performer_, std::string const &audio_url_, std::int32_t audio_duration_,
                                object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 1260139988;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultContact final : public InputInlineQueryResult
{
public:
    std::string id_;
    object_ptr<contact> contact_;
    std::string thumbnail_url_;
    std::int32_t thumbnail_width_;
    std::int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultContact();

    inputInlineQueryResultContact(std::string const &id_, object_ptr<contact> &&contact_,
                                  std::string const &thumbnail_url_, std::int32_t thumbnail_width_, std::int32_t thumbnail_height_,
                                  object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 1846064594;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultDocument final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string title_;
    std::string description_;
    std::string document_url_;
    std::string mime_type_;
    std::string thumbnail_url_;
    std::int32_t thumbnail_width_;
    std::int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultDocument();

    inputInlineQueryResultDocument(std::string const &id_, std::string const &title_,
                                   std::string const &description_, std::string const &document_url_, std::string const &mime_type_,
                                   std::string const &thumbnail_url_, std::int32_t thumbnail_width_, std::int32_t thumbnail_height_,
                                   object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 578801869;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultGame final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string game_short_name_;
    object_ptr<ReplyMarkup> reply_markup_;

    inputInlineQueryResultGame();

    inputInlineQueryResultGame(std::string const &id_, std::string const &game_short_name_,
                               object_ptr<ReplyMarkup> &&reply_markup_);

    static const std::int32_t ID = 966074327;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultLocation final : public InputInlineQueryResult
{
public:
    std::string id_;
    object_ptr<location> location_;
    std::int32_t live_period_;
    std::string title_;
    std::string thumbnail_url_;
    std::int32_t thumbnail_width_;
    std::int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultLocation();

    inputInlineQueryResultLocation(std::string const &id_, object_ptr<location> &&location_,
                                   std::int32_t live_period_, std::string const &title_, std::string const &thumbnail_url_,
                                   std::int32_t thumbnail_width_, std::int32_t thumbnail_height_,
                                   object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = -1887650218;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultPhoto final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string title_;
    std::string description_;
    std::string thumbnail_url_;
    std::string photo_url_;
    std::int32_t photo_width_;
    std::int32_t photo_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultPhoto();

    inputInlineQueryResultPhoto(std::string const &id_, std::string const &title_,
                                std::string const &description_, std::string const &thumbnail_url_, std::string const &photo_url_,
                                std::int32_t photo_width_, std::int32_t photo_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = -1123338721;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultSticker final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string thumbnail_url_;
    std::string sticker_url_;
    std::int32_t sticker_width_;
    std::int32_t sticker_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultSticker();

    inputInlineQueryResultSticker(std::string const &id_, std::string const &thumbnail_url_,
                                  std::string const &sticker_url_, std::int32_t sticker_width_, std::int32_t sticker_height_,
                                  object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 274007129;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultVenue final : public InputInlineQueryResult
{
public:
    std::string id_;
    object_ptr<venue> venue_;
    std::string thumbnail_url_;
    std::int32_t thumbnail_width_;
    std::int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultVenue();

    inputInlineQueryResultVenue(std::string const &id_, object_ptr<venue> &&venue_,
                                std::string const &thumbnail_url_, std::int32_t thumbnail_width_, std::int32_t thumbnail_height_,
                                object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 541704509;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultVideo final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string title_;
    std::string description_;
    std::string thumbnail_url_;
    std::string video_url_;
    std::string mime_type_;
    std::int32_t video_width_;
    std::int32_t video_height_;
    std::int32_t video_duration_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultVideo();

    inputInlineQueryResultVideo(std::string const &id_, std::string const &title_,
                                std::string const &description_, std::string const &thumbnail_url_, std::string const &video_url_,
                                std::string const &mime_type_, std::int32_t video_width_, std::int32_t video_height_,
                                std::int32_t video_duration_, object_ptr<ReplyMarkup> &&reply_markup_,
                                object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 1724073191;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputInlineQueryResultVoiceNote final : public InputInlineQueryResult
{
public:
    std::string id_;
    std::string title_;
    std::string voice_note_url_;
    std::int32_t voice_note_duration_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultVoiceNote();

    inputInlineQueryResultVoiceNote(std::string const &id_, std::string const &title_,
                                    std::string const &voice_note_url_, std::int32_t voice_note_duration_,
                                    object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = -1790072503;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class InputMessageContent: public Object
{
public:
};

class inputMessageText final : public InputMessageContent
{
public:
    object_ptr<formattedText> text_;
    bool disable_web_page_preview_;
    bool clear_draft_;

    inputMessageText();

    inputMessageText(object_ptr<formattedText> &&text_, bool disable_web_page_preview_,
                     bool clear_draft_);

    static const std::int32_t ID = 247050392;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageAnimation final : public InputMessageContent
{
public:
    object_ptr<InputFile> animation_;
    object_ptr<inputThumbnail> thumbnail_;
    std::int32_t duration_;
    std::int32_t width_;
    std::int32_t height_;
    object_ptr<formattedText> caption_;

    inputMessageAnimation();

    inputMessageAnimation(object_ptr<InputFile> &&animation_, object_ptr<inputThumbnail> &&thumbnail_,
                          std::int32_t duration_, std::int32_t width_, std::int32_t height_,
                          object_ptr<formattedText> &&caption_);

    static const std::int32_t ID = 926542724;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageAudio final : public InputMessageContent
{
public:
    object_ptr<InputFile> audio_;
    object_ptr<inputThumbnail> album_cover_thumbnail_;
    std::int32_t duration_;
    std::string title_;
    std::string performer_;
    object_ptr<formattedText> caption_;

    inputMessageAudio();

    inputMessageAudio(object_ptr<InputFile> &&audio_,
                      object_ptr<inputThumbnail> &&album_cover_thumbnail_, std::int32_t duration_,
                      std::string const &title_, std::string const &performer_, object_ptr<formattedText> &&caption_);

    static const std::int32_t ID = -626786126;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageDocument final : public InputMessageContent
{
public:
    object_ptr<InputFile> document_;
    object_ptr<inputThumbnail> thumbnail_;
    object_ptr<formattedText> caption_;

    inputMessageDocument();

    inputMessageDocument(object_ptr<InputFile> &&document_, object_ptr<inputThumbnail> &&thumbnail_,
                         object_ptr<formattedText> &&caption_);

    static const std::int32_t ID = 937970604;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessagePhoto final : public InputMessageContent
{
public:
    object_ptr<InputFile> photo_;
    object_ptr<inputThumbnail> thumbnail_;
    std::vector<std::int32_t> added_sticker_file_ids_;
    std::int32_t width_;
    std::int32_t height_;
    object_ptr<formattedText> caption_;
    std::int32_t ttl_;

    inputMessagePhoto();

    inputMessagePhoto(object_ptr<InputFile> &&photo_, object_ptr<inputThumbnail> &&thumbnail_,
                      std::vector<std::int32_t> &&added_sticker_file_ids_, std::int32_t width_, std::int32_t height_,
                      object_ptr<formattedText> &&caption_, std::int32_t ttl_);

    static const std::int32_t ID = 1648801584;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageSticker final : public InputMessageContent
{
public:
    object_ptr<InputFile> sticker_;
    object_ptr<inputThumbnail> thumbnail_;
    std::int32_t width_;
    std::int32_t height_;

    inputMessageSticker();

    inputMessageSticker(object_ptr<InputFile> &&sticker_, object_ptr<inputThumbnail> &&thumbnail_,
                        std::int32_t width_, std::int32_t height_);

    static const std::int32_t ID = 740776325;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageVideo final : public InputMessageContent
{
public:
    object_ptr<InputFile> video_;
    object_ptr<inputThumbnail> thumbnail_;
    std::vector<std::int32_t> added_sticker_file_ids_;
    std::int32_t duration_;
    std::int32_t width_;
    std::int32_t height_;
    bool supports_streaming_;
    object_ptr<formattedText> caption_;
    std::int32_t ttl_;

    inputMessageVideo();

    inputMessageVideo(object_ptr<InputFile> &&video_, object_ptr<inputThumbnail> &&thumbnail_,
                      std::vector<std::int32_t> &&added_sticker_file_ids_, std::int32_t duration_, std::int32_t width_,
                      std::int32_t height_, bool supports_streaming_, object_ptr<formattedText> &&caption_,
                      std::int32_t ttl_);

    static const std::int32_t ID = -2108486755;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageVideoNote final : public InputMessageContent
{
public:
    object_ptr<InputFile> video_note_;
    object_ptr<inputThumbnail> thumbnail_;
    std::int32_t duration_;
    std::int32_t length_;

    inputMessageVideoNote();

    inputMessageVideoNote(object_ptr<InputFile> &&video_note_, object_ptr<inputThumbnail> &&thumbnail_,
                          std::int32_t duration_, std::int32_t length_);

    static const std::int32_t ID = 279108859;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageVoiceNote final : public InputMessageContent
{
public:
    object_ptr<InputFile> voice_note_;
    std::int32_t duration_;
    std::string waveform_;
    object_ptr<formattedText> caption_;

    inputMessageVoiceNote();

    inputMessageVoiceNote(object_ptr<InputFile> &&voice_note_, std::int32_t duration_,
                          std::string const &waveform_, object_ptr<formattedText> &&caption_);

    static const std::int32_t ID = 2136519657;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageLocation final : public InputMessageContent
{
public:
    object_ptr<location> location_;
    std::int32_t live_period_;

    inputMessageLocation();

    inputMessageLocation(object_ptr<location> &&location_, std::int32_t live_period_);

    static const std::int32_t ID = -1624179655;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageVenue final : public InputMessageContent
{
public:
    object_ptr<venue> venue_;

    inputMessageVenue();

    explicit inputMessageVenue(object_ptr<venue> &&venue_);

    static const std::int32_t ID = 1447926269;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageContact final : public InputMessageContent
{
public:
    object_ptr<contact> contact_;

    inputMessageContact();

    explicit inputMessageContact(object_ptr<contact> &&contact_);

    static const std::int32_t ID = -982446849;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageGame final : public InputMessageContent
{
public:
    std::int32_t bot_user_id_;
    std::string game_short_name_;

    inputMessageGame();

    inputMessageGame(std::int32_t bot_user_id_, std::string const &game_short_name_);

    static const std::int32_t ID = -1728000914;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageInvoice final : public InputMessageContent
{
public:
    object_ptr<invoice> invoice_;
    std::string title_;
    std::string description_;
    std::string photo_url_;
    std::int32_t photo_size_;
    std::int32_t photo_width_;
    std::int32_t photo_height_;
    std::string payload_;
    std::string provider_token_;
    std::string provider_data_;
    std::string start_parameter_;

    inputMessageInvoice();

    inputMessageInvoice(object_ptr<invoice> &&invoice_, std::string const &title_,
                        std::string const &description_, std::string const &photo_url_, std::int32_t photo_size_,
                        std::int32_t photo_width_, std::int32_t photo_height_, std::string const &payload_,
                        std::string const &provider_token_, std::string const &provider_data_,
                        std::string const &start_parameter_);

    static const std::int32_t ID = 1038812175;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageForwarded final : public InputMessageContent
{
public:
    std::int64_t from_chat_id_;
    std::int64_t message_id_;
    bool in_game_share_;

    inputMessageForwarded();

    inputMessageForwarded(std::int64_t from_chat_id_, std::int64_t message_id_, bool in_game_share_);

    static const std::int32_t ID = 1561363198;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputSticker final : public Object
{
public:
    object_ptr<InputFile> png_sticker_;
    std::string emojis_;
    object_ptr<maskPosition> mask_position_;

    inputSticker();

    inputSticker(object_ptr<InputFile> &&png_sticker_, std::string const &emojis_,
                 object_ptr<maskPosition> &&mask_position_);

    static const std::int32_t ID = -1998602205;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputThumbnail final : public Object
{
public:
    object_ptr<InputFile> thumbnail_;
    std::int32_t width_;
    std::int32_t height_;

    inputThumbnail();

    inputThumbnail(object_ptr<InputFile> &&thumbnail_, std::int32_t width_, std::int32_t height_);

    static const std::int32_t ID = 1582387236;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class invoice final : public Object
{
public:
    std::string currency_;
    std::vector<object_ptr<labeledPricePart>> price_parts_;
    bool is_test_;
    bool need_name_;
    bool need_phone_number_;
    bool need_email_address_;
    bool need_shipping_address_;
    bool send_phone_number_to_provider_;
    bool send_email_address_to_provider_;
    bool is_flexible_;

    invoice();

    invoice(std::string const &currency_, std::vector<object_ptr<labeledPricePart>> &&price_parts_,
            bool is_test_, bool need_name_, bool need_phone_number_, bool need_email_address_,
            bool need_shipping_address_, bool send_phone_number_to_provider_,
            bool send_email_address_to_provider_, bool is_flexible_);

    static const std::int32_t ID = -368451690;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class keyboardButton final : public Object
{
public:
    std::string text_;
    object_ptr<KeyboardButtonType> type_;

    keyboardButton();

    keyboardButton(std::string const &text_, object_ptr<KeyboardButtonType> &&type_);

    static const std::int32_t ID = -2069836172;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class KeyboardButtonType: public Object
{
public:
};

class keyboardButtonTypeText final : public KeyboardButtonType
{
public:

    keyboardButtonTypeText();

    static const std::int32_t ID = -1773037256;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class keyboardButtonTypeRequestPhoneNumber final : public KeyboardButtonType
{
public:

    keyboardButtonTypeRequestPhoneNumber();

    static const std::int32_t ID = -1529235527;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class keyboardButtonTypeRequestLocation final : public KeyboardButtonType
{
public:

    keyboardButtonTypeRequestLocation();

    static const std::int32_t ID = -125661955;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class labeledPricePart final : public Object
{
public:
    std::string label_;
    std::int64_t amount_;

    labeledPricePart();

    labeledPricePart(std::string const &label_, std::int64_t amount_);

    static const std::int32_t ID = 552789798;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class LinkState: public Object
{
public:
};

class linkStateNone final : public LinkState
{
public:

    linkStateNone();

    static const std::int32_t ID = 951430287;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class linkStateKnowsPhoneNumber final : public LinkState
{
public:

    linkStateKnowsPhoneNumber();

    static const std::int32_t ID = 380898199;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class linkStateIsContact final : public LinkState
{
public:

    linkStateIsContact();

    static const std::int32_t ID = -1000499465;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class localFile final : public Object
{
public:
    std::string path_;
    bool can_be_downloaded_;
    bool can_be_deleted_;
    bool is_downloading_active_;
    bool is_downloading_completed_;
    std::int32_t downloaded_prefix_size_;
    std::int32_t downloaded_size_;

    localFile();

    localFile(std::string const &path_, bool can_be_downloaded_, bool can_be_deleted_,
              bool is_downloading_active_, bool is_downloading_completed_, std::int32_t downloaded_prefix_size_,
              std::int32_t downloaded_size_);

    static const std::int32_t ID = 847939462;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class location final : public Object
{
public:
    double latitude_;
    double longitude_;

    location();

    location(double latitude_, double longitude_);

    static const std::int32_t ID = 749028016;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class MaskPoint: public Object
{
public:
};

class maskPointForehead final : public MaskPoint
{
public:

    maskPointForehead();

    static const std::int32_t ID = 1027512005;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class maskPointEyes final : public MaskPoint
{
public:

    maskPointEyes();

    static const std::int32_t ID = 1748310861;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class maskPointMouth final : public MaskPoint
{
public:

    maskPointMouth();

    static const std::int32_t ID = 411773406;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class maskPointChin final : public MaskPoint
{
public:

    maskPointChin();

    static const std::int32_t ID = 534995335;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class maskPosition final : public Object
{
public:
    object_ptr<MaskPoint> point_;
    double x_shift_;
    double y_shift_;
    double scale_;

    maskPosition();

    maskPosition(object_ptr<MaskPoint> &&point_, double x_shift_, double y_shift_, double scale_);

    static const std::int32_t ID = -2097433026;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class message final : public Object
{
public:
    std::int64_t id_;
    std::int32_t sender_user_id_;
    std::int64_t chat_id_;
    object_ptr<MessageSendingState> sending_state_;
    bool is_outgoing_;
    bool can_be_edited_;
    bool can_be_forwarded_;
    bool can_be_deleted_only_for_self_;
    bool can_be_deleted_for_all_users_;
    bool is_channel_post_;
    bool contains_unread_mention_;
    std::int32_t date_;
    std::int32_t edit_date_;
    object_ptr<MessageForwardInfo> forward_info_;
    std::int64_t reply_to_message_id_;
    std::int32_t ttl_;
    double ttl_expires_in_;
    std::int32_t via_bot_user_id_;
    std::string author_signature_;
    std::int32_t views_;
    std::int64_t media_album_id_;
    object_ptr<MessageContent> content_;
    object_ptr<ReplyMarkup> reply_markup_;

    message();

    message(std::int64_t id_, std::int32_t sender_user_id_, std::int64_t chat_id_,
            object_ptr<MessageSendingState> &&sending_state_, bool is_outgoing_, bool can_be_edited_,
            bool can_be_forwarded_, bool can_be_deleted_only_for_self_, bool can_be_deleted_for_all_users_,
            bool is_channel_post_, bool contains_unread_mention_, std::int32_t date_, std::int32_t edit_date_,
            object_ptr<MessageForwardInfo> &&forward_info_, std::int64_t reply_to_message_id_,
            std::int32_t ttl_, double ttl_expires_in_, std::int32_t via_bot_user_id_,
            std::string const &author_signature_, std::int32_t views_, std::int64_t media_album_id_,
            object_ptr<MessageContent> &&content_, object_ptr<ReplyMarkup> &&reply_markup_);

    static const std::int32_t ID = -675737627;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class MessageContent: public Object
{
public:
};

class messageText final : public MessageContent
{
public:
    object_ptr<formattedText> text_;
    object_ptr<webPage> web_page_;

    messageText();

    messageText(object_ptr<formattedText> &&text_, object_ptr<webPage> &&web_page_);

    static const std::int32_t ID = 1989037971;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageAnimation final : public MessageContent
{
public:
    object_ptr<animation> animation_;
    object_ptr<formattedText> caption_;
    bool is_secret_;

    messageAnimation();

    messageAnimation(object_ptr<animation> &&animation_, object_ptr<formattedText> &&caption_,
                     bool is_secret_);

    static const std::int32_t ID = 1306939396;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageAudio final : public MessageContent
{
public:
    object_ptr<audio> audio_;
    object_ptr<formattedText> caption_;

    messageAudio();

    messageAudio(object_ptr<audio> &&audio_, object_ptr<formattedText> &&caption_);

    static const std::int32_t ID = 276722716;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageDocument final : public MessageContent
{
public:
    object_ptr<document> document_;
    object_ptr<formattedText> caption_;

    messageDocument();

    messageDocument(object_ptr<document> &&document_, object_ptr<formattedText> &&caption_);

    static const std::int32_t ID = 596945783;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messagePhoto final : public MessageContent
{
public:
    object_ptr<photo> photo_;
    object_ptr<formattedText> caption_;
    bool is_secret_;

    messagePhoto();

    messagePhoto(object_ptr<photo> &&photo_, object_ptr<formattedText> &&caption_, bool is_secret_);

    static const std::int32_t ID = -1851395174;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageExpiredPhoto final : public MessageContent
{
public:

    messageExpiredPhoto();

    static const std::int32_t ID = -1404641801;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageSticker final : public MessageContent
{
public:
    object_ptr<sticker> sticker_;

    messageSticker();

    explicit messageSticker(object_ptr<sticker> &&sticker_);

    static const std::int32_t ID = 1779022878;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageVideo final : public MessageContent
{
public:
    object_ptr<video> video_;
    object_ptr<formattedText> caption_;
    bool is_secret_;

    messageVideo();

    messageVideo(object_ptr<video> &&video_, object_ptr<formattedText> &&caption_, bool is_secret_);

    static const std::int32_t ID = 2021281344;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageExpiredVideo final : public MessageContent
{
public:

    messageExpiredVideo();

    static const std::int32_t ID = -1212209981;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageVideoNote final : public MessageContent
{
public:
    object_ptr<videoNote> video_note_;
    bool is_viewed_;
    bool is_secret_;

    messageVideoNote();

    messageVideoNote(object_ptr<videoNote> &&video_note_, bool is_viewed_, bool is_secret_);

    static const std::int32_t ID = 963323014;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageVoiceNote final : public MessageContent
{
public:
    object_ptr<voiceNote> voice_note_;
    object_ptr<formattedText> caption_;
    bool is_listened_;

    messageVoiceNote();

    messageVoiceNote(object_ptr<voiceNote> &&voice_note_, object_ptr<formattedText> &&caption_,
                     bool is_listened_);

    static const std::int32_t ID = 527777781;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageLocation final : public MessageContent
{
public:
    object_ptr<location> location_;
    std::int32_t live_period_;
    std::int32_t expires_in_;

    messageLocation();

    messageLocation(object_ptr<location> &&location_, std::int32_t live_period_,
                    std::int32_t expires_in_);

    static const std::int32_t ID = -1301887786;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageVenue final : public MessageContent
{
public:
    object_ptr<venue> venue_;

    messageVenue();

    explicit messageVenue(object_ptr<venue> &&venue_);

    static const std::int32_t ID = -2146492043;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageContact final : public MessageContent
{
public:
    object_ptr<contact> contact_;

    messageContact();

    explicit messageContact(object_ptr<contact> &&contact_);

    static const std::int32_t ID = -512684966;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageGame final : public MessageContent
{
public:
    object_ptr<game> game_;

    messageGame();

    explicit messageGame(object_ptr<game> &&game_);

    static const std::int32_t ID = -69441162;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageInvoice final : public MessageContent
{
public:
    std::string title_;
    std::string description_;
    object_ptr<photo> photo_;
    std::string currency_;
    std::int64_t total_amount_;
    std::string start_parameter_;
    bool is_test_;
    bool need_shipping_address_;
    std::int64_t receipt_message_id_;

    messageInvoice();

    messageInvoice(std::string const &title_, std::string const &description_,
                   object_ptr<photo> &&photo_, std::string const &currency_, std::int64_t total_amount_,
                   std::string const &start_parameter_, bool is_test_, bool need_shipping_address_,
                   std::int64_t receipt_message_id_);

    static const std::int32_t ID = -1916671476;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageCall final : public MessageContent
{
public:
    object_ptr<CallDiscardReason> discard_reason_;
    std::int32_t duration_;

    messageCall();

    messageCall(object_ptr<CallDiscardReason> &&discard_reason_, std::int32_t duration_);

    static const std::int32_t ID = 366512596;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageBasicGroupChatCreate final : public MessageContent
{
public:
    std::string title_;
    std::vector<std::int32_t> member_user_ids_;

    messageBasicGroupChatCreate();

    messageBasicGroupChatCreate(std::string const &title_,
                                std::vector<std::int32_t> &&member_user_ids_);

    static const std::int32_t ID = 1575377646;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageSupergroupChatCreate final : public MessageContent
{
public:
    std::string title_;

    messageSupergroupChatCreate();

    explicit messageSupergroupChatCreate(std::string const &title_);

    static const std::int32_t ID = -434325733;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatChangeTitle final : public MessageContent
{
public:
    std::string title_;

    messageChatChangeTitle();

    explicit messageChatChangeTitle(std::string const &title_);

    static const std::int32_t ID = 748272449;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatChangePhoto final : public MessageContent
{
public:
    object_ptr<photo> photo_;

    messageChatChangePhoto();

    explicit messageChatChangePhoto(object_ptr<photo> &&photo_);

    static const std::int32_t ID = 319630249;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatDeletePhoto final : public MessageContent
{
public:

    messageChatDeletePhoto();

    static const std::int32_t ID = -184374809;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatAddMembers final : public MessageContent
{
public:
    std::vector<std::int32_t> member_user_ids_;

    messageChatAddMembers();

    explicit messageChatAddMembers(std::vector<std::int32_t> &&member_user_ids_);

    static const std::int32_t ID = 401228326;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatJoinByLink final : public MessageContent
{
public:

    messageChatJoinByLink();

    static const std::int32_t ID = 1846493311;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatDeleteMember final : public MessageContent
{
public:
    std::int32_t user_id_;

    messageChatDeleteMember();

    explicit messageChatDeleteMember(std::int32_t user_id_);

    static const std::int32_t ID = 1164414043;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatUpgradeTo final : public MessageContent
{
public:
    std::int32_t supergroup_id_;

    messageChatUpgradeTo();

    explicit messageChatUpgradeTo(std::int32_t supergroup_id_);

    static const std::int32_t ID = 1957816681;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatUpgradeFrom final : public MessageContent
{
public:
    std::string title_;
    std::int32_t basic_group_id_;

    messageChatUpgradeFrom();

    messageChatUpgradeFrom(std::string const &title_, std::int32_t basic_group_id_);

    static const std::int32_t ID = 1642272558;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messagePinMessage final : public MessageContent
{
public:
    std::int64_t message_id_;

    messagePinMessage();

    explicit messagePinMessage(std::int64_t message_id_);

    static const std::int32_t ID = 953503801;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageScreenshotTaken final : public MessageContent
{
public:

    messageScreenshotTaken();

    static const std::int32_t ID = -1564971605;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatSetTtl final : public MessageContent
{
public:
    std::int32_t ttl_;

    messageChatSetTtl();

    explicit messageChatSetTtl(std::int32_t ttl_);

    static const std::int32_t ID = 1810060209;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageCustomServiceAction final : public MessageContent
{
public:
    std::string text_;

    messageCustomServiceAction();

    explicit messageCustomServiceAction(std::string const &text_);

    static const std::int32_t ID = 1435879282;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageGameScore final : public MessageContent
{
public:
    std::int64_t game_message_id_;
    std::int64_t game_id_;
    std::int32_t score_;

    messageGameScore();

    messageGameScore(std::int64_t game_message_id_, std::int64_t game_id_, std::int32_t score_);

    static const std::int32_t ID = 1344904575;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messagePaymentSuccessful final : public MessageContent
{
public:
    std::int64_t invoice_message_id_;
    std::string currency_;
    std::int64_t total_amount_;

    messagePaymentSuccessful();

    messagePaymentSuccessful(std::int64_t invoice_message_id_, std::string const &currency_,
                             std::int64_t total_amount_);

    static const std::int32_t ID = -595962993;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messagePaymentSuccessfulBot final : public MessageContent
{
public:
    std::int64_t invoice_message_id_;
    std::string currency_;
    std::int64_t total_amount_;
    std::string invoice_payload_;
    std::string shipping_option_id_;
    object_ptr<orderInfo> order_info_;
    std::string telegram_payment_charge_id_;
    std::string provider_payment_charge_id_;

    messagePaymentSuccessfulBot();

    messagePaymentSuccessfulBot(std::int64_t invoice_message_id_, std::string const &currency_,
                                std::int64_t total_amount_, std::string const &invoice_payload_,
                                std::string const &shipping_option_id_, object_ptr<orderInfo> &&order_info_,
                                std::string const &telegram_payment_charge_id_, std::string const &provider_payment_charge_id_);

    static const std::int32_t ID = -412310696;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageContactRegistered final : public MessageContent
{
public:

    messageContactRegistered();

    static const std::int32_t ID = -1502020353;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageWebsiteConnected final : public MessageContent
{
public:
    std::string domain_name_;

    messageWebsiteConnected();

    explicit messageWebsiteConnected(std::string const &domain_name_);

    static const std::int32_t ID = -1074551800;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageUnsupported final : public MessageContent
{
public:

    messageUnsupported();

    static const std::int32_t ID = -1816726139;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class MessageForwardInfo: public Object
{
public:
};

class messageForwardedFromUser final : public MessageForwardInfo
{
public:
    std::int32_t sender_user_id_;
    std::int32_t date_;
    std::int64_t forwarded_from_chat_id_;
    std::int64_t forwarded_from_message_id_;

    messageForwardedFromUser();

    messageForwardedFromUser(std::int32_t sender_user_id_, std::int32_t date_,
                             std::int64_t forwarded_from_chat_id_, std::int64_t forwarded_from_message_id_);

    static const std::int32_t ID = 1004332765;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageForwardedPost final : public MessageForwardInfo
{
public:
    std::int64_t chat_id_;
    std::string author_signature_;
    std::int32_t date_;
    std::int64_t message_id_;
    std::int64_t forwarded_from_chat_id_;
    std::int64_t forwarded_from_message_id_;

    messageForwardedPost();

    messageForwardedPost(std::int64_t chat_id_, std::string const &author_signature_,
                         std::int32_t date_, std::int64_t message_id_, std::int64_t forwarded_from_chat_id_,
                         std::int64_t forwarded_from_message_id_);

    static const std::int32_t ID = -244050875;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class MessageSendingState: public Object
{
public:
};

class messageSendingStatePending final : public MessageSendingState
{
public:

    messageSendingStatePending();

    static const std::int32_t ID = -1381803582;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageSendingStateFailed final : public MessageSendingState
{
public:

    messageSendingStateFailed();

    static const std::int32_t ID = -546610323;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messages final : public Object
{
public:
    std::int32_t total_count_;
    std::vector<object_ptr<message>> messages_;

    messages();

    messages(std::int32_t total_count_, std::vector<object_ptr<message>> &&messages_);

    static const std::int32_t ID = -16498159;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkStatistics final : public Object
{
public:
    std::int32_t since_date_;
    std::vector<object_ptr<NetworkStatisticsEntry>> entries_;

    networkStatistics();

    networkStatistics(std::int32_t since_date_,
                      std::vector<object_ptr<NetworkStatisticsEntry>> &&entries_);

    static const std::int32_t ID = 1615554212;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class NetworkStatisticsEntry: public Object
{
public:
};

class networkStatisticsEntryFile final : public NetworkStatisticsEntry
{
public:
    object_ptr<FileType> file_type_;
    object_ptr<NetworkType> network_type_;
    std::int64_t sent_bytes_;
    std::int64_t received_bytes_;

    networkStatisticsEntryFile();

    networkStatisticsEntryFile(object_ptr<FileType> &&file_type_,
                               object_ptr<NetworkType> &&network_type_, std::int64_t sent_bytes_, std::int64_t received_bytes_);

    static const std::int32_t ID = 188452706;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkStatisticsEntryCall final : public NetworkStatisticsEntry
{
public:
    object_ptr<NetworkType> network_type_;
    std::int64_t sent_bytes_;
    std::int64_t received_bytes_;
    double duration_;

    networkStatisticsEntryCall();

    networkStatisticsEntryCall(object_ptr<NetworkType> &&network_type_, std::int64_t sent_bytes_,
                               std::int64_t received_bytes_, double duration_);

    static const std::int32_t ID = 737000365;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class NetworkType: public Object
{
public:
};

class networkTypeNone final : public NetworkType
{
public:

    networkTypeNone();

    static const std::int32_t ID = -1971691759;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkTypeMobile final : public NetworkType
{
public:

    networkTypeMobile();

    static const std::int32_t ID = 819228239;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkTypeMobileRoaming final : public NetworkType
{
public:

    networkTypeMobileRoaming();

    static const std::int32_t ID = -1435199760;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkTypeWiFi final : public NetworkType
{
public:

    networkTypeWiFi();

    static const std::int32_t ID = -633872070;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkTypeOther final : public NetworkType
{
public:

    networkTypeOther();

    static const std::int32_t ID = 1942128539;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class notificationSettings final : public Object
{
public:
    std::int32_t mute_for_;
    std::string sound_;
    bool show_preview_;

    notificationSettings();

    notificationSettings(std::int32_t mute_for_, std::string const &sound_, bool show_preview_);

    static const std::int32_t ID = 1737538681;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class NotificationSettingsScope: public Object
{
public:
};

class notificationSettingsScopeChat final : public NotificationSettingsScope
{
public:
    std::int64_t chat_id_;

    notificationSettingsScopeChat();

    explicit notificationSettingsScopeChat(std::int64_t chat_id_);

    static const std::int32_t ID = 1855845499;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class notificationSettingsScopePrivateChats final : public NotificationSettingsScope
{
public:

    notificationSettingsScopePrivateChats();

    static const std::int32_t ID = 937446759;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class notificationSettingsScopeBasicGroupChats final : public NotificationSettingsScope
{
public:

    notificationSettingsScopeBasicGroupChats();

    static const std::int32_t ID = -1358646601;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class notificationSettingsScopeAllChats final : public NotificationSettingsScope
{
public:

    notificationSettingsScopeAllChats();

    static const std::int32_t ID = -1345889922;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ok final : public Object
{
public:

    ok();

    static const std::int32_t ID = -722616727;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class OptionValue: public Object
{
public:
};

class optionValueBoolean final : public OptionValue
{
public:
    bool value_;

    optionValueBoolean();

    explicit optionValueBoolean(bool value_);

    static const std::int32_t ID = 63135518;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class optionValueEmpty final : public OptionValue
{
public:

    optionValueEmpty();

    static const std::int32_t ID = 918955155;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class optionValueInteger final : public OptionValue
{
public:
    std::int32_t value_;

    optionValueInteger();

    explicit optionValueInteger(std::int32_t value_);

    static const std::int32_t ID = -1400911104;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class optionValueString final : public OptionValue
{
public:
    std::string value_;

    optionValueString();

    explicit optionValueString(std::string const &value_);

    static const std::int32_t ID = 756248212;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class orderInfo final : public Object
{
public:
    std::string name_;
    std::string phone_number_;
    std::string email_address_;
    object_ptr<shippingAddress> shipping_address_;

    orderInfo();

    orderInfo(std::string const &name_, std::string const &phone_number_,
              std::string const &email_address_, object_ptr<shippingAddress> &&shipping_address_);

    static const std::int32_t ID = -1830611784;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class PageBlock: public Object
{
public:
};

class pageBlockTitle final : public PageBlock
{
public:
    object_ptr<RichText> title_;

    pageBlockTitle();

    explicit pageBlockTitle(object_ptr<RichText> &&title_);

    static const std::int32_t ID = 1629664784;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockSubtitle final : public PageBlock
{
public:
    object_ptr<RichText> subtitle_;

    pageBlockSubtitle();

    explicit pageBlockSubtitle(object_ptr<RichText> &&subtitle_);

    static const std::int32_t ID = 264524263;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockAuthorDate final : public PageBlock
{
public:
    object_ptr<RichText> author_;
    std::int32_t publish_date_;

    pageBlockAuthorDate();

    pageBlockAuthorDate(object_ptr<RichText> &&author_, std::int32_t publish_date_);

    static const std::int32_t ID = 1300231184;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockHeader final : public PageBlock
{
public:
    object_ptr<RichText> header_;

    pageBlockHeader();

    explicit pageBlockHeader(object_ptr<RichText> &&header_);

    static const std::int32_t ID = 1402854811;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockSubheader final : public PageBlock
{
public:
    object_ptr<RichText> subheader_;

    pageBlockSubheader();

    explicit pageBlockSubheader(object_ptr<RichText> &&subheader_);

    static const std::int32_t ID = 1263956774;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockParagraph final : public PageBlock
{
public:
    object_ptr<RichText> text_;

    pageBlockParagraph();

    explicit pageBlockParagraph(object_ptr<RichText> &&text_);

    static const std::int32_t ID = 1182402406;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockPreformatted final : public PageBlock
{
public:
    object_ptr<RichText> text_;
    std::string language_;

    pageBlockPreformatted();

    pageBlockPreformatted(object_ptr<RichText> &&text_, std::string const &language_);

    static const std::int32_t ID = -1066346178;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockFooter final : public PageBlock
{
public:
    object_ptr<RichText> footer_;

    pageBlockFooter();

    explicit pageBlockFooter(object_ptr<RichText> &&footer_);

    static const std::int32_t ID = 886429480;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockDivider final : public PageBlock
{
public:

    pageBlockDivider();

    static const std::int32_t ID = -618614392;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockAnchor final : public PageBlock
{
public:
    std::string name_;

    pageBlockAnchor();

    explicit pageBlockAnchor(std::string const &name_);

    static const std::int32_t ID = -837994576;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockList final : public PageBlock
{
public:
    std::vector<object_ptr<RichText>> items_;
    bool is_ordered_;

    pageBlockList();

    pageBlockList(std::vector<object_ptr<RichText>> &&items_, bool is_ordered_);

    static const std::int32_t ID = -1752631674;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockBlockQuote final : public PageBlock
{
public:
    object_ptr<RichText> text_;
    object_ptr<RichText> caption_;

    pageBlockBlockQuote();

    pageBlockBlockQuote(object_ptr<RichText> &&text_, object_ptr<RichText> &&caption_);

    static const std::int32_t ID = -37421406;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockPullQuote final : public PageBlock
{
public:
    object_ptr<RichText> text_;
    object_ptr<RichText> caption_;

    pageBlockPullQuote();

    pageBlockPullQuote(object_ptr<RichText> &&text_, object_ptr<RichText> &&caption_);

    static const std::int32_t ID = -1799498665;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockAnimation final : public PageBlock
{
public:
    object_ptr<animation> animation_;
    object_ptr<RichText> caption_;
    bool need_autoplay_;

    pageBlockAnimation();

    pageBlockAnimation(object_ptr<animation> &&animation_, object_ptr<RichText> &&caption_,
                       bool need_autoplay_);

    static const std::int32_t ID = 1639478661;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockAudio final : public PageBlock
{
public:
    object_ptr<audio> audio_;
    object_ptr<RichText> caption_;

    pageBlockAudio();

    pageBlockAudio(object_ptr<audio> &&audio_, object_ptr<RichText> &&caption_);

    static const std::int32_t ID = 1898245855;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockPhoto final : public PageBlock
{
public:
    object_ptr<photo> photo_;
    object_ptr<RichText> caption_;

    pageBlockPhoto();

    pageBlockPhoto(object_ptr<photo> &&photo_, object_ptr<RichText> &&caption_);

    static const std::int32_t ID = -637181825;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockVideo final : public PageBlock
{
public:
    object_ptr<video> video_;
    object_ptr<RichText> caption_;
    bool need_autoplay_;
    bool is_looped_;

    pageBlockVideo();

    pageBlockVideo(object_ptr<video> &&video_, object_ptr<RichText> &&caption_, bool need_autoplay_,
                   bool is_looped_);

    static const std::int32_t ID = 1610373002;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockCover final : public PageBlock
{
public:
    object_ptr<PageBlock> cover_;

    pageBlockCover();

    explicit pageBlockCover(object_ptr<PageBlock> &&cover_);

    static const std::int32_t ID = 972174080;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockEmbedded final : public PageBlock
{
public:
    std::string url_;
    std::string html_;
    object_ptr<photo> poster_photo_;
    std::int32_t width_;
    std::int32_t height_;
    object_ptr<RichText> caption_;
    bool is_full_width_;
    bool allow_scrolling_;

    pageBlockEmbedded();

    pageBlockEmbedded(std::string const &url_, std::string const &html_,
                      object_ptr<photo> &&poster_photo_, std::int32_t width_, std::int32_t height_,
                      object_ptr<RichText> &&caption_, bool is_full_width_, bool allow_scrolling_);

    static const std::int32_t ID = -211257334;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockEmbeddedPost final : public PageBlock
{
public:
    std::string url_;
    std::string author_;
    object_ptr<photo> author_photo_;
    std::int32_t date_;
    std::vector<object_ptr<PageBlock>> page_blocks_;
    object_ptr<RichText> caption_;

    pageBlockEmbeddedPost();

    pageBlockEmbeddedPost(std::string const &url_, std::string const &author_,
                          object_ptr<photo> &&author_photo_, std::int32_t date_,
                          std::vector<object_ptr<PageBlock>> &&page_blocks_, object_ptr<RichText> &&caption_);

    static const std::int32_t ID = 1049948772;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockCollage final : public PageBlock
{
public:
    std::vector<object_ptr<PageBlock>> page_blocks_;
    object_ptr<RichText> caption_;

    pageBlockCollage();

    pageBlockCollage(std::vector<object_ptr<PageBlock>> &&page_blocks_,
                     object_ptr<RichText> &&caption_);

    static const std::int32_t ID = 911142202;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockSlideshow final : public PageBlock
{
public:
    std::vector<object_ptr<PageBlock>> page_blocks_;
    object_ptr<RichText> caption_;

    pageBlockSlideshow();

    pageBlockSlideshow(std::vector<object_ptr<PageBlock>> &&page_blocks_,
                       object_ptr<RichText> &&caption_);

    static const std::int32_t ID = 178557514;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockChatLink final : public PageBlock
{
public:
    std::string title_;
    object_ptr<chatPhoto> photo_;
    std::string username_;

    pageBlockChatLink();

    pageBlockChatLink(std::string const &title_, object_ptr<chatPhoto> &&photo_,
                      std::string const &username_);

    static const std::int32_t ID = 214606645;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class passwordRecoveryInfo final : public Object
{
public:
    std::string recovery_email_address_pattern_;

    passwordRecoveryInfo();

    explicit passwordRecoveryInfo(std::string const &recovery_email_address_pattern_);

    static const std::int32_t ID = 1483233330;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class passwordState final : public Object
{
public:
    bool has_password_;
    std::string password_hint_;
    bool has_recovery_email_address_;
    std::string unconfirmed_recovery_email_address_pattern_;

    passwordState();

    passwordState(bool has_password_, std::string const &password_hint_,
                  bool has_recovery_email_address_, std::string const &unconfirmed_recovery_email_address_pattern_);

    static const std::int32_t ID = 1383061922;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class paymentForm final : public Object
{
public:
    object_ptr<invoice> invoice_;
    std::string url_;
    object_ptr<paymentsProviderStripe> payments_provider_;
    object_ptr<orderInfo> saved_order_info_;
    object_ptr<savedCredentials> saved_credentials_;
    bool can_save_credentials_;
    bool need_password_;

    paymentForm();

    paymentForm(object_ptr<invoice> &&invoice_, std::string const &url_,
                object_ptr<paymentsProviderStripe> &&payments_provider_, object_ptr<orderInfo> &&saved_order_info_,
                object_ptr<savedCredentials> &&saved_credentials_, bool can_save_credentials_, bool need_password_);

    static const std::int32_t ID = -200418230;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class paymentReceipt final : public Object
{
public:
    std::int32_t date_;
    std::int32_t payments_provider_user_id_;
    object_ptr<invoice> invoice_;
    object_ptr<orderInfo> order_info_;
    object_ptr<shippingOption> shipping_option_;
    std::string credentials_title_;

    paymentReceipt();

    paymentReceipt(std::int32_t date_, std::int32_t payments_provider_user_id_,
                   object_ptr<invoice> &&invoice_, object_ptr<orderInfo> &&order_info_,
                   object_ptr<shippingOption> &&shipping_option_, std::string const &credentials_title_);

    static const std::int32_t ID = -1171223545;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class paymentResult final : public Object
{
public:
    bool success_;
    std::string verification_url_;

    paymentResult();

    paymentResult(bool success_, std::string const &verification_url_);

    static const std::int32_t ID = -804263843;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class paymentsProviderStripe final : public Object
{
public:
    std::string publishable_key_;
    bool need_country_;
    bool need_postal_code_;
    bool need_cardholder_name_;

    paymentsProviderStripe();

    paymentsProviderStripe(std::string const &publishable_key_, bool need_country_,
                           bool need_postal_code_, bool need_cardholder_name_);

    static const std::int32_t ID = 1090791032;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class photo final : public Object
{
public:
    std::int64_t id_;
    bool has_stickers_;
    std::vector<object_ptr<photoSize>> sizes_;

    photo();

    photo(std::int64_t id_, bool has_stickers_, std::vector<object_ptr<photoSize>> &&sizes_);

    static const std::int32_t ID = -1949521787;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class photoSize final : public Object
{
public:
    std::string type_;
    object_ptr<file> photo_;
    std::int32_t width_;
    std::int32_t height_;

    photoSize();

    photoSize(std::string const &type_, object_ptr<file> &&photo_, std::int32_t width_,
              std::int32_t height_);

    static const std::int32_t ID = 421980227;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class profilePhoto final : public Object
{
public:
    std::int64_t id_;
    object_ptr<file> small_;
    object_ptr<file> big_;

    profilePhoto();

    profilePhoto(std::int64_t id_, object_ptr<file> &&small_, object_ptr<file> &&big_);

    static const std::int32_t ID = 978085937;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class Proxy: public Object
{
public:
};

class proxyEmpty final : public Proxy
{
public:

    proxyEmpty();

    static const std::int32_t ID = 748440246;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class proxySocks5 final : public Proxy
{
public:
    std::string server_;
    std::int32_t port_;
    std::string username_;
    std::string password_;

    proxySocks5();

    proxySocks5(std::string const &server_, std::int32_t port_, std::string const &username_,
                std::string const &password_);

    static const std::int32_t ID = 1456461592;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class publicMessageLink final : public Object
{
public:
    std::string link_;
    std::string html_;

    publicMessageLink();

    publicMessageLink(std::string const &link_, std::string const &html_);

    static const std::int32_t ID = -679603433;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class recoveryEmailAddress final : public Object
{
public:
    std::string recovery_email_address_;

    recoveryEmailAddress();

    explicit recoveryEmailAddress(std::string const &recovery_email_address_);

    static const std::int32_t ID = 1290526187;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class remoteFile final : public Object
{
public:
    std::string id_;
    bool is_uploading_active_;
    bool is_uploading_completed_;
    std::int32_t uploaded_size_;

    remoteFile();

    remoteFile(std::string const &id_, bool is_uploading_active_, bool is_uploading_completed_,
               std::int32_t uploaded_size_);

    static const std::int32_t ID = 1761289748;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ReplyMarkup: public Object
{
public:
};

class replyMarkupRemoveKeyboard final : public ReplyMarkup
{
public:
    bool is_personal_;

    replyMarkupRemoveKeyboard();

    explicit replyMarkupRemoveKeyboard(bool is_personal_);

    static const std::int32_t ID = -691252879;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class replyMarkupForceReply final : public ReplyMarkup
{
public:
    bool is_personal_;

    replyMarkupForceReply();

    explicit replyMarkupForceReply(bool is_personal_);

    static const std::int32_t ID = 1039104593;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class replyMarkupShowKeyboard final : public ReplyMarkup
{
public:
    std::vector<std::vector<object_ptr<keyboardButton>>> rows_;
    bool resize_keyboard_;
    bool one_time_;
    bool is_personal_;

    replyMarkupShowKeyboard();

    replyMarkupShowKeyboard(std::vector<std::vector<object_ptr<keyboardButton>>> &&rows_,
                            bool resize_keyboard_, bool one_time_, bool is_personal_);

    static const std::int32_t ID = -992627133;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class replyMarkupInlineKeyboard final : public ReplyMarkup
{
public:
    std::vector<std::vector<object_ptr<inlineKeyboardButton>>> rows_;

    replyMarkupInlineKeyboard();

    explicit replyMarkupInlineKeyboard(std::vector<std::vector<object_ptr<inlineKeyboardButton>>>
                                       &&rows_);

    static const std::int32_t ID = -619317658;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class RichText: public Object
{
public:
};

class richTextPlain final : public RichText
{
public:
    std::string text_;

    richTextPlain();

    explicit richTextPlain(std::string const &text_);

    static const std::int32_t ID = 482617702;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class richTextBold final : public RichText
{
public:
    object_ptr<RichText> text_;

    richTextBold();

    explicit richTextBold(object_ptr<RichText> &&text_);

    static const std::int32_t ID = 1670844268;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class richTextItalic final : public RichText
{
public:
    object_ptr<RichText> text_;

    richTextItalic();

    explicit richTextItalic(object_ptr<RichText> &&text_);

    static const std::int32_t ID = 1853354047;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class richTextUnderline final : public RichText
{
public:
    object_ptr<RichText> text_;

    richTextUnderline();

    explicit richTextUnderline(object_ptr<RichText> &&text_);

    static const std::int32_t ID = -536019572;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class richTextStrikethrough final : public RichText
{
public:
    object_ptr<RichText> text_;

    richTextStrikethrough();

    explicit richTextStrikethrough(object_ptr<RichText> &&text_);

    static const std::int32_t ID = 723413585;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class richTextFixed final : public RichText
{
public:
    object_ptr<RichText> text_;

    richTextFixed();

    explicit richTextFixed(object_ptr<RichText> &&text_);

    static const std::int32_t ID = -1271496249;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class richTextUrl final : public RichText
{
public:
    object_ptr<RichText> text_;
    std::string url_;

    richTextUrl();

    richTextUrl(object_ptr<RichText> &&text_, std::string const &url_);

    static const std::int32_t ID = 1967248447;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class richTextEmailAddress final : public RichText
{
public:
    object_ptr<RichText> text_;
    std::string email_address_;

    richTextEmailAddress();

    richTextEmailAddress(object_ptr<RichText> &&text_, std::string const &email_address_);

    static const std::int32_t ID = 40018679;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class richTexts final : public RichText
{
public:
    std::vector<object_ptr<RichText>> texts_;

    richTexts();

    explicit richTexts(std::vector<object_ptr<RichText>> &&texts_);

    static const std::int32_t ID = 1647457821;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class savedCredentials final : public Object
{
public:
    std::string id_;
    std::string title_;

    savedCredentials();

    savedCredentials(std::string const &id_, std::string const &title_);

    static const std::int32_t ID = -370273060;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class SearchMessagesFilter: public Object
{
public:
};

class searchMessagesFilterEmpty final : public SearchMessagesFilter
{
public:

    searchMessagesFilterEmpty();

    static const std::int32_t ID = -869395657;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterAnimation final : public SearchMessagesFilter
{
public:

    searchMessagesFilterAnimation();

    static const std::int32_t ID = -155713339;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterAudio final : public SearchMessagesFilter
{
public:

    searchMessagesFilterAudio();

    static const std::int32_t ID = 867505275;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterDocument final : public SearchMessagesFilter
{
public:

    searchMessagesFilterDocument();

    static const std::int32_t ID = 1526331215;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterPhoto final : public SearchMessagesFilter
{
public:

    searchMessagesFilterPhoto();

    static const std::int32_t ID = 925932293;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterVideo final : public SearchMessagesFilter
{
public:

    searchMessagesFilterVideo();

    static const std::int32_t ID = 115538222;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterVoiceNote final : public SearchMessagesFilter
{
public:

    searchMessagesFilterVoiceNote();

    static const std::int32_t ID = 1841439357;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterPhotoAndVideo final : public SearchMessagesFilter
{
public:

    searchMessagesFilterPhotoAndVideo();

    static const std::int32_t ID = 1352130963;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterUrl final : public SearchMessagesFilter
{
public:

    searchMessagesFilterUrl();

    static const std::int32_t ID = -1828724341;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterChatPhoto final : public SearchMessagesFilter
{
public:

    searchMessagesFilterChatPhoto();

    static const std::int32_t ID = -1247751329;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterCall final : public SearchMessagesFilter
{
public:

    searchMessagesFilterCall();

    static const std::int32_t ID = 1305231012;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterMissedCall final : public SearchMessagesFilter
{
public:

    searchMessagesFilterMissedCall();

    static const std::int32_t ID = 970663098;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterVideoNote final : public SearchMessagesFilter
{
public:

    searchMessagesFilterVideoNote();

    static const std::int32_t ID = 564323321;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterVoiceAndVideoNote final : public SearchMessagesFilter
{
public:

    searchMessagesFilterVoiceAndVideoNote();

    static const std::int32_t ID = 664174819;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterMention final : public SearchMessagesFilter
{
public:

    searchMessagesFilterMention();

    static const std::int32_t ID = 2001258652;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterUnreadMention final : public SearchMessagesFilter
{
public:

    searchMessagesFilterUnreadMention();

    static const std::int32_t ID = -95769149;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class secretChat final : public Object
{
public:
    std::int32_t id_;
    std::int32_t user_id_;
    object_ptr<SecretChatState> state_;
    bool is_outbound_;
    std::int32_t ttl_;
    std::string key_hash_;
    std::int32_t layer_;

    secretChat();

    secretChat(std::int32_t id_, std::int32_t user_id_, object_ptr<SecretChatState> &&state_,
               bool is_outbound_, std::int32_t ttl_, std::string const &key_hash_, std::int32_t layer_);

    static const std::int32_t ID = 1279231629;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class SecretChatState: public Object
{
public:
};

class secretChatStatePending final : public SecretChatState
{
public:

    secretChatStatePending();

    static const std::int32_t ID = -1637050756;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class secretChatStateReady final : public SecretChatState
{
public:

    secretChatStateReady();

    static const std::int32_t ID = -1611352087;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class secretChatStateClosed final : public SecretChatState
{
public:

    secretChatStateClosed();

    static const std::int32_t ID = -1945106707;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class session final : public Object
{
public:
    std::int64_t id_;
    bool is_current_;
    std::int32_t api_id_;
    std::string application_name_;
    std::string application_version_;
    bool is_official_application_;
    std::string device_model_;
    std::string platform_;
    std::string system_version_;
    std::int32_t log_in_date_;
    std::int32_t last_active_date_;
    std::string ip_;
    std::string country_;
    std::string region_;

    session();

    session(std::int64_t id_, bool is_current_, std::int32_t api_id_,
            std::string const &application_name_, std::string const &application_version_,
            bool is_official_application_, std::string const &device_model_, std::string const &platform_,
            std::string const &system_version_, std::int32_t log_in_date_, std::int32_t last_active_date_,
            std::string const &ip_, std::string const &country_, std::string const &region_);

    static const std::int32_t ID = 1715359000;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sessions final : public Object
{
public:
    std::vector<object_ptr<session>> sessions_;

    sessions();

    explicit sessions(std::vector<object_ptr<session>> &&sessions_);

    static const std::int32_t ID = -463118121;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class shippingAddress final : public Object
{
public:
    std::string country_code_;
    std::string state_;
    std::string city_;
    std::string street_line1_;
    std::string street_line2_;
    std::string postal_code_;

    shippingAddress();

    shippingAddress(std::string const &country_code_, std::string const &state_,
                    std::string const &city_, std::string const &street_line1_, std::string const &street_line2_,
                    std::string const &postal_code_);

    static const std::int32_t ID = 565574826;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class shippingOption final : public Object
{
public:
    std::string id_;
    std::string title_;
    std::vector<object_ptr<labeledPricePart>> price_parts_;

    shippingOption();

    shippingOption(std::string const &id_, std::string const &title_,
                   std::vector<object_ptr<labeledPricePart>> &&price_parts_);

    static const std::int32_t ID = 1425690001;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sticker final : public Object
{
public:
    std::int64_t set_id_;
    std::int32_t width_;
    std::int32_t height_;
    std::string emoji_;
    bool is_mask_;
    object_ptr<maskPosition> mask_position_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> sticker_;

    sticker();

    sticker(std::int64_t set_id_, std::int32_t width_, std::int32_t height_, std::string const &emoji_,
            bool is_mask_, object_ptr<maskPosition> &&mask_position_, object_ptr<photoSize> &&thumbnail_,
            object_ptr<file> &&sticker_);

    static const std::int32_t ID = -876442962;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class stickerEmojis final : public Object
{
public:
    std::vector<std::string> emojis_;

    stickerEmojis();

    explicit stickerEmojis(std::vector<std::string> &&emojis_);

    static const std::int32_t ID = -1781588570;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class stickerSet final : public Object
{
public:
    std::int64_t id_;
    std::string title_;
    std::string name_;
    bool is_installed_;
    bool is_archived_;
    bool is_official_;
    bool is_masks_;
    bool is_viewed_;
    std::vector<object_ptr<sticker>> stickers_;
    std::vector<object_ptr<stickerEmojis>> emojis_;

    stickerSet();

    stickerSet(std::int64_t id_, std::string const &title_, std::string const &name_,
               bool is_installed_, bool is_archived_, bool is_official_, bool is_masks_, bool is_viewed_,
               std::vector<object_ptr<sticker>> &&stickers_, std::vector<object_ptr<stickerEmojis>> &&emojis_);

    static const std::int32_t ID = 72047469;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class stickerSetInfo final : public Object
{
public:
    std::int64_t id_;
    std::string title_;
    std::string name_;
    bool is_installed_;
    bool is_archived_;
    bool is_official_;
    bool is_masks_;
    bool is_viewed_;
    std::int32_t size_;
    std::vector<object_ptr<sticker>> covers_;

    stickerSetInfo();

    stickerSetInfo(std::int64_t id_, std::string const &title_, std::string const &name_,
                   bool is_installed_, bool is_archived_, bool is_official_, bool is_masks_, bool is_viewed_,
                   std::int32_t size_, std::vector<object_ptr<sticker>> &&covers_);

    static const std::int32_t ID = 1469837113;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class stickerSets final : public Object
{
public:
    std::int32_t total_count_;
    std::vector<object_ptr<stickerSetInfo>> sets_;

    stickerSets();

    stickerSets(std::int32_t total_count_, std::vector<object_ptr<stickerSetInfo>> &&sets_);

    static const std::int32_t ID = -1883828812;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class stickers final : public Object
{
public:
    std::vector<object_ptr<sticker>> stickers_;

    stickers();

    explicit stickers(std::vector<object_ptr<sticker>> &&stickers_);

    static const std::int32_t ID = 1974859260;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class storageStatistics final : public Object
{
public:
    std::int64_t size_;
    std::int32_t count_;
    std::vector<object_ptr<storageStatisticsByChat>> by_chat_;

    storageStatistics();

    storageStatistics(std::int64_t size_, std::int32_t count_,
                      std::vector<object_ptr<storageStatisticsByChat>> &&by_chat_);

    static const std::int32_t ID = 217237013;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class storageStatisticsByChat final : public Object
{
public:
    std::int64_t chat_id_;
    std::int64_t size_;
    std::int32_t count_;
    std::vector<object_ptr<storageStatisticsByFileType>> by_file_type_;

    storageStatisticsByChat();

    storageStatisticsByChat(std::int64_t chat_id_, std::int64_t size_, std::int32_t count_,
                            std::vector<object_ptr<storageStatisticsByFileType>> &&by_file_type_);

    static const std::int32_t ID = 635434531;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class storageStatisticsByFileType final : public Object
{
public:
    object_ptr<FileType> file_type_;
    std::int64_t size_;
    std::int32_t count_;

    storageStatisticsByFileType();

    storageStatisticsByFileType(object_ptr<FileType> &&file_type_, std::int64_t size_,
                                std::int32_t count_);

    static const std::int32_t ID = 714012840;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class storageStatisticsFast final : public Object
{
public:
    std::int64_t files_size_;
    std::int32_t file_count_;
    std::int64_t database_size_;

    storageStatisticsFast();

    storageStatisticsFast(std::int64_t files_size_, std::int32_t file_count_,
                          std::int64_t database_size_);

    static const std::int32_t ID = -2005401007;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroup final : public Object
{
public:
    std::int32_t id_;
    std::string username_;
    std::int32_t date_;
    object_ptr<ChatMemberStatus> status_;
    std::int32_t member_count_;
    bool anyone_can_invite_;
    bool sign_messages_;
    bool is_channel_;
    bool is_verified_;
    std::string restriction_reason_;

    supergroup();

    supergroup(std::int32_t id_, std::string const &username_, std::int32_t date_,
               object_ptr<ChatMemberStatus> &&status_, std::int32_t member_count_, bool anyone_can_invite_,
               bool sign_messages_, bool is_channel_, bool is_verified_, std::string const &restriction_reason_);

    static const std::int32_t ID = -1737513476;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupFullInfo final : public Object
{
public:
    std::string description_;
    std::int32_t member_count_;
    std::int32_t administrator_count_;
    std::int32_t restricted_count_;
    std::int32_t banned_count_;
    bool can_get_members_;
    bool can_set_username_;
    bool can_set_sticker_set_;
    bool is_all_history_available_;
    std::int64_t sticker_set_id_;
    std::string invite_link_;
    std::int64_t pinned_message_id_;
    std::int32_t upgraded_from_basic_group_id_;
    std::int64_t upgraded_from_max_message_id_;

    supergroupFullInfo();

    supergroupFullInfo(std::string const &description_, std::int32_t member_count_,
                       std::int32_t administrator_count_, std::int32_t restricted_count_, std::int32_t banned_count_,
                       bool can_get_members_, bool can_set_username_, bool can_set_sticker_set_,
                       bool is_all_history_available_, std::int64_t sticker_set_id_, std::string const &invite_link_,
                       std::int64_t pinned_message_id_, std::int32_t upgraded_from_basic_group_id_,
                       std::int64_t upgraded_from_max_message_id_);

    static const std::int32_t ID = -1482349223;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class SupergroupMembersFilter: public Object
{
public:
};

class supergroupMembersFilterRecent final : public SupergroupMembersFilter
{
public:

    supergroupMembersFilterRecent();

    static const std::int32_t ID = 1178199509;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupMembersFilterAdministrators final : public SupergroupMembersFilter
{
public:

    supergroupMembersFilterAdministrators();

    static const std::int32_t ID = -2097380265;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupMembersFilterSearch final : public SupergroupMembersFilter
{
public:
    std::string query_;

    supergroupMembersFilterSearch();

    explicit supergroupMembersFilterSearch(std::string const &query_);

    static const std::int32_t ID = -1696358469;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupMembersFilterRestricted final : public SupergroupMembersFilter
{
public:
    std::string query_;

    supergroupMembersFilterRestricted();

    explicit supergroupMembersFilterRestricted(std::string const &query_);

    static const std::int32_t ID = -1107800034;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupMembersFilterBanned final : public SupergroupMembersFilter
{
public:
    std::string query_;

    supergroupMembersFilterBanned();

    explicit supergroupMembersFilterBanned(std::string const &query_);

    static const std::int32_t ID = -1210621683;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupMembersFilterBots final : public SupergroupMembersFilter
{
public:

    supergroupMembersFilterBots();

    static const std::int32_t ID = 492138918;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class tMeUrl final : public Object
{
public:
    std::string url_;
    object_ptr<TMeUrlType> type_;

    tMeUrl();

    tMeUrl(std::string const &url_, object_ptr<TMeUrlType> &&type_);

    static const std::int32_t ID = -1140786622;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class TMeUrlType: public Object
{
public:
};

class tMeUrlTypeUser final : public TMeUrlType
{
public:
    std::int32_t user_id_;

    tMeUrlTypeUser();

    explicit tMeUrlTypeUser(std::int32_t user_id_);

    static const std::int32_t ID = -1198700130;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class tMeUrlTypeSupergroup final : public TMeUrlType
{
public:
    std::int64_t supergroup_id_;

    tMeUrlTypeSupergroup();

    explicit tMeUrlTypeSupergroup(std::int64_t supergroup_id_);

    static const std::int32_t ID = -1353369944;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class tMeUrlTypeChatInvite final : public TMeUrlType
{
public:
    object_ptr<chatInviteLinkInfo> info_;

    tMeUrlTypeChatInvite();

    explicit tMeUrlTypeChatInvite(object_ptr<chatInviteLinkInfo> &&info_);

    static const std::int32_t ID = 313907785;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class tMeUrlTypeStickerSet final : public TMeUrlType
{
public:
    std::int64_t sticker_set_id_;

    tMeUrlTypeStickerSet();

    explicit tMeUrlTypeStickerSet(std::int64_t sticker_set_id_);

    static const std::int32_t ID = 1602473196;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class tMeUrls final : public Object
{
public:
    std::vector<object_ptr<tMeUrl>> urls_;

    tMeUrls();

    explicit tMeUrls(std::vector<object_ptr<tMeUrl>> &&urls_);

    static const std::int32_t ID = -1130595098;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class tdlibParameters final : public Object
{
public:
    bool use_test_dc_;
    std::string database_directory_;
    std::string files_directory_;
    bool use_file_database_;
    bool use_chat_info_database_;
    bool use_message_database_;
    bool use_secret_chats_;
    std::int32_t api_id_;
    std::string api_hash_;
    std::string system_language_code_;
    std::string device_model_;
    std::string system_version_;
    std::string application_version_;
    bool enable_storage_optimizer_;
    bool ignore_file_names_;

    tdlibParameters();

    tdlibParameters(bool use_test_dc_, std::string const &database_directory_,
                    std::string const &files_directory_, bool use_file_database_, bool use_chat_info_database_,
                    bool use_message_database_, bool use_secret_chats_, std::int32_t api_id_,
                    std::string const &api_hash_, std::string const &system_language_code_,
                    std::string const &device_model_, std::string const &system_version_,
                    std::string const &application_version_, bool enable_storage_optimizer_, bool ignore_file_names_);

    static const std::int32_t ID = -761520773;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class temporaryPasswordState final : public Object
{
public:
    bool has_password_;
    std::int32_t valid_for_;

    temporaryPasswordState();

    temporaryPasswordState(bool has_password_, std::int32_t valid_for_);

    static const std::int32_t ID = 939837410;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testBytes final : public Object
{
public:
    std::string value_;

    testBytes();

    explicit testBytes(std::string const &value_);

    static const std::int32_t ID = -1541225250;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testInt final : public Object
{
public:
    std::int32_t value_;

    testInt();

    explicit testInt(std::int32_t value_);

    static const std::int32_t ID = -574804983;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testString final : public Object
{
public:
    std::string value_;

    testString();

    explicit testString(std::string const &value_);

    static const std::int32_t ID = -27891572;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testVectorInt final : public Object
{
public:
    std::vector<std::int32_t> value_;

    testVectorInt();

    explicit testVectorInt(std::vector<std::int32_t> &&value_);

    static const std::int32_t ID = 593682027;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testVectorIntObject final : public Object
{
public:
    std::vector<object_ptr<testInt>> value_;

    testVectorIntObject();

    explicit testVectorIntObject(std::vector<object_ptr<testInt>> &&value_);

    static const std::int32_t ID = 125891546;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testVectorString final : public Object
{
public:
    std::vector<std::string> value_;

    testVectorString();

    explicit testVectorString(std::vector<std::string> &&value_);

    static const std::int32_t ID = 79339995;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testVectorStringObject final : public Object
{
public:
    std::vector<object_ptr<testString>> value_;

    testVectorStringObject();

    explicit testVectorStringObject(std::vector<object_ptr<testString>> &&value_);

    static const std::int32_t ID = 80780537;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class text final : public Object
{
public:
    std::string text_;

    text();

    explicit text(std::string const &text_);

    static const std::int32_t ID = 578181272;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntities final : public Object
{
public:
    std::vector<object_ptr<textEntity>> entities_;

    textEntities();

    explicit textEntities(std::vector<object_ptr<textEntity>> &&entities_);

    static const std::int32_t ID = -933199172;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntity final : public Object
{
public:
    std::int32_t offset_;
    std::int32_t length_;
    object_ptr<TextEntityType> type_;

    textEntity();

    textEntity(std::int32_t offset_, std::int32_t length_, object_ptr<TextEntityType> &&type_);

    static const std::int32_t ID = -1951688280;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class TextEntityType: public Object
{
public:
};

class textEntityTypeMention final : public TextEntityType
{
public:

    textEntityTypeMention();

    static const std::int32_t ID = 934535013;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeHashtag final : public TextEntityType
{
public:

    textEntityTypeHashtag();

    static const std::int32_t ID = -1023958307;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeCashtag final : public TextEntityType
{
public:

    textEntityTypeCashtag();

    static const std::int32_t ID = 1222915915;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeBotCommand final : public TextEntityType
{
public:

    textEntityTypeBotCommand();

    static const std::int32_t ID = -1150997581;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeUrl final : public TextEntityType
{
public:

    textEntityTypeUrl();

    static const std::int32_t ID = -1312762756;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeEmailAddress final : public TextEntityType
{
public:

    textEntityTypeEmailAddress();

    static const std::int32_t ID = 1425545249;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeBold final : public TextEntityType
{
public:

    textEntityTypeBold();

    static const std::int32_t ID = -1128210000;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeItalic final : public TextEntityType
{
public:

    textEntityTypeItalic();

    static const std::int32_t ID = -118253987;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeCode final : public TextEntityType
{
public:

    textEntityTypeCode();

    static const std::int32_t ID = -974534326;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypePre final : public TextEntityType
{
public:

    textEntityTypePre();

    static const std::int32_t ID = 1648958606;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypePreCode final : public TextEntityType
{
public:
    std::string language_;

    textEntityTypePreCode();

    explicit textEntityTypePreCode(std::string const &language_);

    static const std::int32_t ID = -945325397;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeTextUrl final : public TextEntityType
{
public:
    std::string url_;

    textEntityTypeTextUrl();

    explicit textEntityTypeTextUrl(std::string const &url_);

    static const std::int32_t ID = 445719651;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeMentionName final : public TextEntityType
{
public:
    std::int32_t user_id_;

    textEntityTypeMentionName();

    explicit textEntityTypeMentionName(std::int32_t user_id_);

    static const std::int32_t ID = -791517091;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypePhoneNumber final : public TextEntityType
{
public:

    textEntityTypePhoneNumber();

    static const std::int32_t ID = -1160140246;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class TextParseMode: public Object
{
public:
};

class textParseModeMarkdown final : public TextParseMode
{
public:

    textParseModeMarkdown();

    static const std::int32_t ID = 969225580;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textParseModeHTML final : public TextParseMode
{
public:

    textParseModeHTML();

    static const std::int32_t ID = 1660208627;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class TopChatCategory: public Object
{
public:
};

class topChatCategoryUsers final : public TopChatCategory
{
public:

    topChatCategoryUsers();

    static const std::int32_t ID = 1026706816;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryBots final : public TopChatCategory
{
public:

    topChatCategoryBots();

    static const std::int32_t ID = -1577129195;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryGroups final : public TopChatCategory
{
public:

    topChatCategoryGroups();

    static const std::int32_t ID = 1530056846;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryChannels final : public TopChatCategory
{
public:

    topChatCategoryChannels();

    static const std::int32_t ID = -500825885;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryInlineBots final : public TopChatCategory
{
public:

    topChatCategoryInlineBots();

    static const std::int32_t ID = 377023356;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryCalls final : public TopChatCategory
{
public:

    topChatCategoryCalls();

    static const std::int32_t ID = 356208861;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class Update: public Object
{
public:
};

class updateAuthorizationState final : public Update
{
public:
    object_ptr<AuthorizationState> authorization_state_;

    updateAuthorizationState();

    explicit updateAuthorizationState(object_ptr<AuthorizationState> &&authorization_state_);

    static const std::int32_t ID = 1622347490;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewMessage final : public Update
{
public:
    object_ptr<message> message_;
    bool disable_notification_;
    bool contains_mention_;

    updateNewMessage();

    updateNewMessage(object_ptr<message> &&message_, bool disable_notification_,
                     bool contains_mention_);

    static const std::int32_t ID = 238944219;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageSendAcknowledged final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;

    updateMessageSendAcknowledged();

    updateMessageSendAcknowledged(std::int64_t chat_id_, std::int64_t message_id_);

    static const std::int32_t ID = 1302843961;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageSendSucceeded final : public Update
{
public:
    object_ptr<message> message_;
    std::int64_t old_message_id_;

    updateMessageSendSucceeded();

    updateMessageSendSucceeded(object_ptr<message> &&message_, std::int64_t old_message_id_);

    static const std::int32_t ID = 1815715197;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageSendFailed final : public Update
{
public:
    object_ptr<message> message_;
    std::int64_t old_message_id_;
    std::int32_t error_code_;
    std::string error_message_;

    updateMessageSendFailed();

    updateMessageSendFailed(object_ptr<message> &&message_, std::int64_t old_message_id_,
                            std::int32_t error_code_, std::string const &error_message_);

    static const std::int32_t ID = -1032335779;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageContent final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    object_ptr<MessageContent> new_content_;

    updateMessageContent();

    updateMessageContent(std::int64_t chat_id_, std::int64_t message_id_,
                         object_ptr<MessageContent> &&new_content_);

    static const std::int32_t ID = 506903332;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageEdited final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    std::int32_t edit_date_;
    object_ptr<ReplyMarkup> reply_markup_;

    updateMessageEdited();

    updateMessageEdited(std::int64_t chat_id_, std::int64_t message_id_, std::int32_t edit_date_,
                        object_ptr<ReplyMarkup> &&reply_markup_);

    static const std::int32_t ID = -559545626;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageViews final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    std::int32_t views_;

    updateMessageViews();

    updateMessageViews(std::int64_t chat_id_, std::int64_t message_id_, std::int32_t views_);

    static const std::int32_t ID = -1854131125;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageContentOpened final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;

    updateMessageContentOpened();

    updateMessageContentOpened(std::int64_t chat_id_, std::int64_t message_id_);

    static const std::int32_t ID = -1520523131;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageMentionRead final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    std::int32_t unread_mention_count_;

    updateMessageMentionRead();

    updateMessageMentionRead(std::int64_t chat_id_, std::int64_t message_id_,
                             std::int32_t unread_mention_count_);

    static const std::int32_t ID = -252228282;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewChat final : public Update
{
public:
    object_ptr<chat> chat_;

    updateNewChat();

    explicit updateNewChat(object_ptr<chat> &&chat_);

    static const std::int32_t ID = 2075757773;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatTitle final : public Update
{
public:
    std::int64_t chat_id_;
    std::string title_;

    updateChatTitle();

    updateChatTitle(std::int64_t chat_id_, std::string const &title_);

    static const std::int32_t ID = -175405660;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatPhoto final : public Update
{
public:
    std::int64_t chat_id_;
    object_ptr<chatPhoto> photo_;

    updateChatPhoto();

    updateChatPhoto(std::int64_t chat_id_, object_ptr<chatPhoto> &&photo_);

    static const std::int32_t ID = -209353966;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatLastMessage final : public Update
{
public:
    std::int64_t chat_id_;
    object_ptr<message> last_message_;
    std::int64_t order_;

    updateChatLastMessage();

    updateChatLastMessage(std::int64_t chat_id_, object_ptr<message> &&last_message_,
                          std::int64_t order_);

    static const std::int32_t ID = 580348828;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatOrder final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t order_;

    updateChatOrder();

    updateChatOrder(std::int64_t chat_id_, std::int64_t order_);

    static const std::int32_t ID = -1601888026;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatIsPinned final : public Update
{
public:
    std::int64_t chat_id_;
    bool is_pinned_;
    std::int64_t order_;

    updateChatIsPinned();

    updateChatIsPinned(std::int64_t chat_id_, bool is_pinned_, std::int64_t order_);

    static const std::int32_t ID = 488876260;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatReadInbox final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t last_read_inbox_message_id_;
    std::int32_t unread_count_;

    updateChatReadInbox();

    updateChatReadInbox(std::int64_t chat_id_, std::int64_t last_read_inbox_message_id_,
                        std::int32_t unread_count_);

    static const std::int32_t ID = -797952281;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatReadOutbox final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t last_read_outbox_message_id_;

    updateChatReadOutbox();

    updateChatReadOutbox(std::int64_t chat_id_, std::int64_t last_read_outbox_message_id_);

    static const std::int32_t ID = 708334213;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatUnreadMentionCount final : public Update
{
public:
    std::int64_t chat_id_;
    std::int32_t unread_mention_count_;

    updateChatUnreadMentionCount();

    updateChatUnreadMentionCount(std::int64_t chat_id_, std::int32_t unread_mention_count_);

    static const std::int32_t ID = -2131461348;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNotificationSettings final : public Update
{
public:
    object_ptr<NotificationSettingsScope> scope_;
    object_ptr<notificationSettings> notification_settings_;

    updateNotificationSettings();

    updateNotificationSettings(object_ptr<NotificationSettingsScope> &&scope_,
                               object_ptr<notificationSettings> &&notification_settings_);

    static const std::int32_t ID = -1767306883;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatReplyMarkup final : public Update
{
public:
    std::int64_t chat_id_;
    std::int64_t reply_markup_message_id_;

    updateChatReplyMarkup();

    updateChatReplyMarkup(std::int64_t chat_id_, std::int64_t reply_markup_message_id_);

    static const std::int32_t ID = 1309386144;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatDraftMessage final : public Update
{
public:
    std::int64_t chat_id_;
    object_ptr<draftMessage> draft_message_;
    std::int64_t order_;

    updateChatDraftMessage();

    updateChatDraftMessage(std::int64_t chat_id_, object_ptr<draftMessage> &&draft_message_,
                           std::int64_t order_);

    static const std::int32_t ID = -1436617498;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateDeleteMessages final : public Update
{
public:
    std::int64_t chat_id_;
    std::vector<std::int64_t> message_ids_;
    bool is_permanent_;
    bool from_cache_;

    updateDeleteMessages();

    updateDeleteMessages(std::int64_t chat_id_, std::vector<std::int64_t> &&message_ids_,
                         bool is_permanent_, bool from_cache_);

    static const std::int32_t ID = 1669252686;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUserChatAction final : public Update
{
public:
    std::int64_t chat_id_;
    std::int32_t user_id_;
    object_ptr<ChatAction> action_;

    updateUserChatAction();

    updateUserChatAction(std::int64_t chat_id_, std::int32_t user_id_,
                         object_ptr<ChatAction> &&action_);

    static const std::int32_t ID = 1444133514;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUserStatus final : public Update
{
public:
    std::int32_t user_id_;
    object_ptr<UserStatus> status_;

    updateUserStatus();

    updateUserStatus(std::int32_t user_id_, object_ptr<UserStatus> &&status_);

    static const std::int32_t ID = -1443545195;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUser final : public Update
{
public:
    object_ptr<user> user_;

    updateUser();

    explicit updateUser(object_ptr<user> &&user_);

    static const std::int32_t ID = 1183394041;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateBasicGroup final : public Update
{
public:
    object_ptr<basicGroup> basic_group_;

    updateBasicGroup();

    explicit updateBasicGroup(object_ptr<basicGroup> &&basic_group_);

    static const std::int32_t ID = -1003239581;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateSupergroup final : public Update
{
public:
    object_ptr<supergroup> supergroup_;

    updateSupergroup();

    explicit updateSupergroup(object_ptr<supergroup> &&supergroup_);

    static const std::int32_t ID = -76782300;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateSecretChat final : public Update
{
public:
    object_ptr<secretChat> secret_chat_;

    updateSecretChat();

    explicit updateSecretChat(object_ptr<secretChat> &&secret_chat_);

    static const std::int32_t ID = -1666903253;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUserFullInfo final : public Update
{
public:
    std::int32_t user_id_;
    object_ptr<userFullInfo> user_full_info_;

    updateUserFullInfo();

    updateUserFullInfo(std::int32_t user_id_, object_ptr<userFullInfo> &&user_full_info_);

    static const std::int32_t ID = 222103874;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateBasicGroupFullInfo final : public Update
{
public:
    std::int32_t basic_group_id_;
    object_ptr<basicGroupFullInfo> basic_group_full_info_;

    updateBasicGroupFullInfo();

    updateBasicGroupFullInfo(std::int32_t basic_group_id_,
                             object_ptr<basicGroupFullInfo> &&basic_group_full_info_);

    static const std::int32_t ID = 924030531;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateSupergroupFullInfo final : public Update
{
public:
    std::int32_t supergroup_id_;
    object_ptr<supergroupFullInfo> supergroup_full_info_;

    updateSupergroupFullInfo();

    updateSupergroupFullInfo(std::int32_t supergroup_id_,
                             object_ptr<supergroupFullInfo> &&supergroup_full_info_);

    static const std::int32_t ID = 1288828758;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateServiceNotification final : public Update
{
public:
    std::string type_;
    object_ptr<MessageContent> content_;

    updateServiceNotification();

    updateServiceNotification(std::string const &type_, object_ptr<MessageContent> &&content_);

    static const std::int32_t ID = 1318622637;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateFile final : public Update
{
public:
    object_ptr<file> file_;

    updateFile();

    explicit updateFile(object_ptr<file> &&file_);

    static const std::int32_t ID = 114132831;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateFileGenerationStart final : public Update
{
public:
    std::int64_t generation_id_;
    std::string original_path_;
    std::string destination_path_;
    std::string conversion_;

    updateFileGenerationStart();

    updateFileGenerationStart(std::int64_t generation_id_, std::string const &original_path_,
                              std::string const &destination_path_, std::string const &conversion_);

    static const std::int32_t ID = 216817388;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateFileGenerationStop final : public Update
{
public:
    std::int64_t generation_id_;

    updateFileGenerationStop();

    explicit updateFileGenerationStop(std::int64_t generation_id_);

    static const std::int32_t ID = -1894449685;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateCall final : public Update
{
public:
    object_ptr<call> call_;

    updateCall();

    explicit updateCall(object_ptr<call> &&call_);

    static const std::int32_t ID = 1337184477;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUserPrivacySettingRules final : public Update
{
public:
    object_ptr<UserPrivacySetting> setting_;
    object_ptr<userPrivacySettingRules> rules_;

    updateUserPrivacySettingRules();

    updateUserPrivacySettingRules(object_ptr<UserPrivacySetting> &&setting_,
                                  object_ptr<userPrivacySettingRules> &&rules_);

    static const std::int32_t ID = -912960778;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUnreadMessageCount final : public Update
{
public:
    std::int32_t unread_count_;
    std::int32_t unread_unmuted_count_;

    updateUnreadMessageCount();

    updateUnreadMessageCount(std::int32_t unread_count_, std::int32_t unread_unmuted_count_);

    static const std::int32_t ID = -824420376;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateOption final : public Update
{
public:
    std::string name_;
    object_ptr<OptionValue> value_;

    updateOption();

    updateOption(std::string const &name_, object_ptr<OptionValue> &&value_);

    static const std::int32_t ID = 900822020;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateInstalledStickerSets final : public Update
{
public:
    bool is_masks_;
    std::vector<std::int64_t> sticker_set_ids_;

    updateInstalledStickerSets();

    updateInstalledStickerSets(bool is_masks_, std::vector<std::int64_t> &&sticker_set_ids_);

    static const std::int32_t ID = 1125575977;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateTrendingStickerSets final : public Update
{
public:
    object_ptr<stickerSets> sticker_sets_;

    updateTrendingStickerSets();

    explicit updateTrendingStickerSets(object_ptr<stickerSets> &&sticker_sets_);

    static const std::int32_t ID = 450714593;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateRecentStickers final : public Update
{
public:
    bool is_attached_;
    std::vector<std::int32_t> sticker_ids_;

    updateRecentStickers();

    updateRecentStickers(bool is_attached_, std::vector<std::int32_t> &&sticker_ids_);

    static const std::int32_t ID = 1906403540;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateFavoriteStickers final : public Update
{
public:
    std::vector<std::int32_t> sticker_ids_;

    updateFavoriteStickers();

    explicit updateFavoriteStickers(std::vector<std::int32_t> &&sticker_ids_);

    static const std::int32_t ID = 1662240999;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateSavedAnimations final : public Update
{
public:
    std::vector<std::int32_t> animation_ids_;

    updateSavedAnimations();

    explicit updateSavedAnimations(std::vector<std::int32_t> &&animation_ids_);

    static const std::int32_t ID = 65563814;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateConnectionState final : public Update
{
public:
    object_ptr<ConnectionState> state_;

    updateConnectionState();

    explicit updateConnectionState(object_ptr<ConnectionState> &&state_);

    static const std::int32_t ID = 1469292078;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewInlineQuery final : public Update
{
public:
    std::int64_t id_;
    std::int32_t sender_user_id_;
    object_ptr<location> user_location_;
    std::string query_;
    std::string offset_;

    updateNewInlineQuery();

    updateNewInlineQuery(std::int64_t id_, std::int32_t sender_user_id_,
                         object_ptr<location> &&user_location_, std::string const &query_, std::string const &offset_);

    static const std::int32_t ID = 2064730634;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewChosenInlineResult final : public Update
{
public:
    std::int32_t sender_user_id_;
    object_ptr<location> user_location_;
    std::string query_;
    std::string result_id_;
    std::string inline_message_id_;

    updateNewChosenInlineResult();

    updateNewChosenInlineResult(std::int32_t sender_user_id_, object_ptr<location> &&user_location_,
                                std::string const &query_, std::string const &result_id_, std::string const &inline_message_id_);

    static const std::int32_t ID = 527526965;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewCallbackQuery final : public Update
{
public:
    std::int64_t id_;
    std::int32_t sender_user_id_;
    std::int64_t chat_id_;
    std::int64_t message_id_;
    std::int64_t chat_instance_;
    object_ptr<CallbackQueryPayload> payload_;

    updateNewCallbackQuery();

    updateNewCallbackQuery(std::int64_t id_, std::int32_t sender_user_id_, std::int64_t chat_id_,
                           std::int64_t message_id_, std::int64_t chat_instance_, object_ptr<CallbackQueryPayload> &&payload_);

    static const std::int32_t ID = -2044226370;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewInlineCallbackQuery final : public Update
{
public:
    std::int64_t id_;
    std::int32_t sender_user_id_;
    std::string inline_message_id_;
    std::int64_t chat_instance_;
    object_ptr<CallbackQueryPayload> payload_;

    updateNewInlineCallbackQuery();

    updateNewInlineCallbackQuery(std::int64_t id_, std::int32_t sender_user_id_,
                                 std::string const &inline_message_id_, std::int64_t chat_instance_,
                                 object_ptr<CallbackQueryPayload> &&payload_);

    static const std::int32_t ID = -1879154829;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewShippingQuery final : public Update
{
public:
    std::int64_t id_;
    std::int32_t sender_user_id_;
    std::string invoice_payload_;
    object_ptr<shippingAddress> shipping_address_;

    updateNewShippingQuery();

    updateNewShippingQuery(std::int64_t id_, std::int32_t sender_user_id_,
                           std::string const &invoice_payload_, object_ptr<shippingAddress> &&shipping_address_);

    static const std::int32_t ID = 1877838488;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewPreCheckoutQuery final : public Update
{
public:
    std::int64_t id_;
    std::int32_t sender_user_id_;
    std::string currency_;
    std::int64_t total_amount_;
    std::string invoice_payload_;
    std::string shipping_option_id_;
    object_ptr<orderInfo> order_info_;

    updateNewPreCheckoutQuery();

    updateNewPreCheckoutQuery(std::int64_t id_, std::int32_t sender_user_id_,
                              std::string const &currency_, std::int64_t total_amount_, std::string const &invoice_payload_,
                              std::string const &shipping_option_id_, object_ptr<orderInfo> &&order_info_);

    static const std::int32_t ID = 87964006;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewCustomEvent final : public Update
{
public:
    std::string event_;

    updateNewCustomEvent();

    explicit updateNewCustomEvent(std::string const &event_);

    static const std::int32_t ID = 1994222092;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewCustomQuery final : public Update
{
public:
    std::int64_t id_;
    std::string data_;
    std::int32_t timeout_;

    updateNewCustomQuery();

    updateNewCustomQuery(std::int64_t id_, std::string const &data_, std::int32_t timeout_);

    static const std::int32_t ID = -687670874;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class user final : public Object
{
public:
    std::int32_t id_;
    std::string first_name_;
    std::string last_name_;
    std::string username_;
    std::string phone_number_;
    object_ptr<UserStatus> status_;
    object_ptr<profilePhoto> profile_photo_;
    object_ptr<LinkState> outgoing_link_;
    object_ptr<LinkState> incoming_link_;
    bool is_verified_;
    std::string restriction_reason_;
    bool have_access_;
    object_ptr<UserType> type_;
    std::string language_code_;

    user();

    user(std::int32_t id_, std::string const &first_name_, std::string const &last_name_,
         std::string const &username_, std::string const &phone_number_, object_ptr<UserStatus> &&status_,
         object_ptr<profilePhoto> &&profile_photo_, object_ptr<LinkState> &&outgoing_link_,
         object_ptr<LinkState> &&incoming_link_, bool is_verified_, std::string const &restriction_reason_,
         bool have_access_, object_ptr<UserType> &&type_, std::string const &language_code_);

    static const std::int32_t ID = -732086407;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userFullInfo final : public Object
{
public:
    bool is_blocked_;
    bool can_be_called_;
    bool has_private_calls_;
    std::string bio_;
    std::string share_text_;
    std::int32_t group_in_common_count_;
    object_ptr<botInfo> bot_info_;

    userFullInfo();

    userFullInfo(bool is_blocked_, bool can_be_called_, bool has_private_calls_,
                 std::string const &bio_, std::string const &share_text_, std::int32_t group_in_common_count_,
                 object_ptr<botInfo> &&bot_info_);

    static const std::int32_t ID = 1076948004;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class UserPrivacySetting: public Object
{
public:
};

class userPrivacySettingShowStatus final : public UserPrivacySetting
{
public:

    userPrivacySettingShowStatus();

    static const std::int32_t ID = 1862829310;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingAllowChatInvites final : public UserPrivacySetting
{
public:

    userPrivacySettingAllowChatInvites();

    static const std::int32_t ID = 1271668007;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingAllowCalls final : public UserPrivacySetting
{
public:

    userPrivacySettingAllowCalls();

    static const std::int32_t ID = -906967291;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class UserPrivacySettingRule: public Object
{
public:
};

class userPrivacySettingRuleAllowAll final : public UserPrivacySettingRule
{
public:

    userPrivacySettingRuleAllowAll();

    static const std::int32_t ID = -1967186881;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleAllowContacts final : public UserPrivacySettingRule
{
public:

    userPrivacySettingRuleAllowContacts();

    static const std::int32_t ID = -1892733680;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleAllowUsers final : public UserPrivacySettingRule
{
public:
    std::vector<std::int32_t> user_ids_;

    userPrivacySettingRuleAllowUsers();

    explicit userPrivacySettingRuleAllowUsers(std::vector<std::int32_t> &&user_ids_);

    static const std::int32_t ID = 427601278;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleRestrictAll final : public UserPrivacySettingRule
{
public:

    userPrivacySettingRuleRestrictAll();

    static const std::int32_t ID = -1406495408;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleRestrictContacts final : public UserPrivacySettingRule
{
public:

    userPrivacySettingRuleRestrictContacts();

    static const std::int32_t ID = 1008389378;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleRestrictUsers final : public UserPrivacySettingRule
{
public:
    std::vector<std::int32_t> user_ids_;

    userPrivacySettingRuleRestrictUsers();

    explicit userPrivacySettingRuleRestrictUsers(std::vector<std::int32_t> &&user_ids_);

    static const std::int32_t ID = 2119951802;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRules final : public Object
{
public:
    std::vector<object_ptr<UserPrivacySettingRule>> rules_;

    userPrivacySettingRules();

    explicit userPrivacySettingRules(std::vector<object_ptr<UserPrivacySettingRule>> &&rules_);

    static const std::int32_t ID = 322477541;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userProfilePhotos final : public Object
{
public:
    std::int32_t total_count_;
    std::vector<object_ptr<photo>> photos_;

    userProfilePhotos();

    userProfilePhotos(std::int32_t total_count_, std::vector<object_ptr<photo>> &&photos_);

    static const std::int32_t ID = 1388892074;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class UserStatus: public Object
{
public:
};

class userStatusEmpty final : public UserStatus
{
public:

    userStatusEmpty();

    static const std::int32_t ID = 164646985;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusOnline final : public UserStatus
{
public:
    std::int32_t expires_;

    userStatusOnline();

    explicit userStatusOnline(std::int32_t expires_);

    static const std::int32_t ID = -1529460876;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusOffline final : public UserStatus
{
public:
    std::int32_t was_online_;

    userStatusOffline();

    explicit userStatusOffline(std::int32_t was_online_);

    static const std::int32_t ID = -759984891;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusRecently final : public UserStatus
{
public:

    userStatusRecently();

    static const std::int32_t ID = -496024847;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusLastWeek final : public UserStatus
{
public:

    userStatusLastWeek();

    static const std::int32_t ID = 129960444;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusLastMonth final : public UserStatus
{
public:

    userStatusLastMonth();

    static const std::int32_t ID = 2011940674;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class UserType: public Object
{
public:
};

class userTypeRegular final : public UserType
{
public:

    userTypeRegular();

    static const std::int32_t ID = -598644325;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userTypeDeleted final : public UserType
{
public:

    userTypeDeleted();

    static const std::int32_t ID = -1807729372;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userTypeBot final : public UserType
{
public:
    bool can_join_groups_;
    bool can_read_all_group_messages_;
    bool is_inline_;
    std::string inline_query_placeholder_;
    bool need_location_;

    userTypeBot();

    userTypeBot(bool can_join_groups_, bool can_read_all_group_messages_, bool is_inline_,
                std::string const &inline_query_placeholder_, bool need_location_);

    static const std::int32_t ID = 1262387765;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userTypeUnknown final : public UserType
{
public:

    userTypeUnknown();

    static const std::int32_t ID = -724541123;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class users final : public Object
{
public:
    std::int32_t total_count_;
    std::vector<std::int32_t> user_ids_;

    users();

    users(std::int32_t total_count_, std::vector<std::int32_t> &&user_ids_);

    static const std::int32_t ID = 273760088;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class validatedOrderInfo final : public Object
{
public:
    std::string order_info_id_;
    std::vector<object_ptr<shippingOption>> shipping_options_;

    validatedOrderInfo();

    validatedOrderInfo(std::string const &order_info_id_,
                       std::vector<object_ptr<shippingOption>> &&shipping_options_);

    static const std::int32_t ID = 1511451484;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class venue final : public Object
{
public:
    object_ptr<location> location_;
    std::string title_;
    std::string address_;
    std::string provider_;
    std::string id_;

    venue();

    venue(object_ptr<location> &&location_, std::string const &title_, std::string const &address_,
          std::string const &provider_, std::string const &id_);

    static const std::int32_t ID = -674687867;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class video final : public Object
{
public:
    std::int32_t duration_;
    std::int32_t width_;
    std::int32_t height_;
    std::string file_name_;
    std::string mime_type_;
    bool has_stickers_;
    bool supports_streaming_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> video_;

    video();

    video(std::int32_t duration_, std::int32_t width_, std::int32_t height_,
          std::string const &file_name_, std::string const &mime_type_, bool has_stickers_,
          bool supports_streaming_, object_ptr<photoSize> &&thumbnail_, object_ptr<file> &&video_);

    static const std::int32_t ID = -437410347;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class videoNote final : public Object
{
public:
    std::int32_t duration_;
    std::int32_t length_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> video_;

    videoNote();

    videoNote(std::int32_t duration_, std::int32_t length_, object_ptr<photoSize> &&thumbnail_,
              object_ptr<file> &&video_);

    static const std::int32_t ID = -1177396120;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class voiceNote final : public Object
{
public:
    std::int32_t duration_;
    std::string waveform_;
    std::string mime_type_;
    object_ptr<file> voice_;

    voiceNote();

    voiceNote(std::int32_t duration_, std::string const &waveform_, std::string const &mime_type_,
              object_ptr<file> &&voice_);

    static const std::int32_t ID = -2066012058;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class wallpaper final : public Object
{
public:
    std::int32_t id_;
    std::vector<object_ptr<photoSize>> sizes_;
    std::int32_t color_;

    wallpaper();

    wallpaper(std::int32_t id_, std::vector<object_ptr<photoSize>> &&sizes_, std::int32_t color_);

    static const std::int32_t ID = 282771691;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class wallpapers final : public Object
{
public:
    std::vector<object_ptr<wallpaper>> wallpapers_;

    wallpapers();

    explicit wallpapers(std::vector<object_ptr<wallpaper>> &&wallpapers_);

    static const std::int32_t ID = 877926640;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class webPage final : public Object
{
public:
    std::string url_;
    std::string display_url_;
    std::string type_;
    std::string site_name_;
    std::string title_;
    std::string description_;
    object_ptr<photo> photo_;
    std::string embed_url_;
    std::string embed_type_;
    std::int32_t embed_width_;
    std::int32_t embed_height_;
    std::int32_t duration_;
    std::string author_;
    object_ptr<animation> animation_;
    object_ptr<audio> audio_;
    object_ptr<document> document_;
    object_ptr<sticker> sticker_;
    object_ptr<video> video_;
    object_ptr<videoNote> video_note_;
    object_ptr<voiceNote> voice_note_;
    bool has_instant_view_;

    webPage();

    webPage(std::string const &url_, std::string const &display_url_, std::string const &type_,
            std::string const &site_name_, std::string const &title_, std::string const &description_,
            object_ptr<photo> &&photo_, std::string const &embed_url_, std::string const &embed_type_,
            std::int32_t embed_width_, std::int32_t embed_height_, std::int32_t duration_,
            std::string const &author_, object_ptr<animation> &&animation_, object_ptr<audio> &&audio_,
            object_ptr<document> &&document_, object_ptr<sticker> &&sticker_, object_ptr<video> &&video_,
            object_ptr<videoNote> &&video_note_, object_ptr<voiceNote> &&voice_note_, bool has_instant_view_);

    static const std::int32_t ID = 1465949075;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class webPageInstantView final : public Object
{
public:
    std::vector<object_ptr<PageBlock>> page_blocks_;
    bool is_full_;

    webPageInstantView();

    webPageInstantView(std::vector<object_ptr<PageBlock>> &&page_blocks_, bool is_full_);

    static const std::int32_t ID = 1804324850;
    std::int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class acceptCall final : public Function
{
public:
    std::int32_t call_id_;
    object_ptr<callProtocol> protocol_;

    acceptCall();

    acceptCall(std::int32_t call_id_, object_ptr<callProtocol> &&protocol_);

    static const std::int32_t ID = -646618416;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addChatMember final : public Function
{
public:
    std::int64_t chat_id_;
    std::int32_t user_id_;
    std::int32_t forward_limit_;

    addChatMember();

    addChatMember(std::int64_t chat_id_, std::int32_t user_id_, std::int32_t forward_limit_);

    static const std::int32_t ID = 1182817962;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addChatMembers final : public Function
{
public:
    std::int64_t chat_id_;
    std::vector<std::int32_t> user_ids_;

    addChatMembers();

    addChatMembers(std::int64_t chat_id_, std::vector<std::int32_t> &&user_ids_);

    static const std::int32_t ID = 1234094617;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addFavoriteSticker final : public Function
{
public:
    object_ptr<InputFile> sticker_;

    addFavoriteSticker();

    explicit addFavoriteSticker(object_ptr<InputFile> &&sticker_);

    static const std::int32_t ID = 324504799;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addNetworkStatistics final : public Function
{
public:
    object_ptr<NetworkStatisticsEntry> entry_;

    addNetworkStatistics();

    explicit addNetworkStatistics(object_ptr<NetworkStatisticsEntry> &&entry_);

    static const std::int32_t ID = 1264825305;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addRecentSticker final : public Function
{
public:
    bool is_attached_;
    object_ptr<InputFile> sticker_;

    addRecentSticker();

    addRecentSticker(bool is_attached_, object_ptr<InputFile> &&sticker_);

    static const std::int32_t ID = -1478109026;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addRecentlyFoundChat final : public Function
{
public:
    std::int64_t chat_id_;

    addRecentlyFoundChat();

    explicit addRecentlyFoundChat(std::int64_t chat_id_);

    static const std::int32_t ID = -1746396787;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addSavedAnimation final : public Function
{
public:
    object_ptr<InputFile> animation_;

    addSavedAnimation();

    explicit addSavedAnimation(object_ptr<InputFile> &&animation_);

    static const std::int32_t ID = -1538525088;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addStickerToSet final : public Function
{
public:
    std::int32_t user_id_;
    std::string name_;
    object_ptr<inputSticker> sticker_;

    addStickerToSet();

    addStickerToSet(std::int32_t user_id_, std::string const &name_,
                    object_ptr<inputSticker> &&sticker_);

    static const std::int32_t ID = 1422402800;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSet>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerCallbackQuery final : public Function
{
public:
    std::int64_t callback_query_id_;
    std::string text_;
    bool show_alert_;
    std::string url_;
    std::int32_t cache_time_;

    answerCallbackQuery();

    answerCallbackQuery(std::int64_t callback_query_id_, std::string const &text_, bool show_alert_,
                        std::string const &url_, std::int32_t cache_time_);

    static const std::int32_t ID = -1153028490;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerCustomQuery final : public Function
{
public:
    std::int64_t custom_query_id_;
    std::string data_;

    answerCustomQuery();

    answerCustomQuery(std::int64_t custom_query_id_, std::string const &data_);

    static const std::int32_t ID = -1293603521;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerInlineQuery final : public Function
{
public:
    std::int64_t inline_query_id_;
    bool is_personal_;
    std::vector<object_ptr<InputInlineQueryResult>> results_;
    std::int32_t cache_time_;
    std::string next_offset_;
    std::string switch_pm_text_;
    std::string switch_pm_parameter_;

    answerInlineQuery();

    answerInlineQuery(std::int64_t inline_query_id_, bool is_personal_,
                      std::vector<object_ptr<InputInlineQueryResult>> &&results_, std::int32_t cache_time_,
                      std::string const &next_offset_, std::string const &switch_pm_text_,
                      std::string const &switch_pm_parameter_);

    static const std::int32_t ID = 485879477;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerPreCheckoutQuery final : public Function
{
public:
    std::int64_t pre_checkout_query_id_;
    std::string error_message_;

    answerPreCheckoutQuery();

    answerPreCheckoutQuery(std::int64_t pre_checkout_query_id_, std::string const &error_message_);

    static const std::int32_t ID = -1486789653;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerShippingQuery final : public Function
{
public:
    std::int64_t shipping_query_id_;
    std::vector<object_ptr<shippingOption>> shipping_options_;
    std::string error_message_;

    answerShippingQuery();

    answerShippingQuery(std::int64_t shipping_query_id_,
                        std::vector<object_ptr<shippingOption>> &&shipping_options_, std::string const &error_message_);

    static const std::int32_t ID = -434601324;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class blockUser final : public Function
{
public:
    std::int32_t user_id_;

    blockUser();

    explicit blockUser(std::int32_t user_id_);

    static const std::int32_t ID = -1239315139;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class cancelDownloadFile final : public Function
{
public:
    std::int32_t file_id_;
    bool only_if_pending_;

    cancelDownloadFile();

    cancelDownloadFile(std::int32_t file_id_, bool only_if_pending_);

    static const std::int32_t ID = -1954524450;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class cancelUploadFile final : public Function
{
public:
    std::int32_t file_id_;

    cancelUploadFile();

    explicit cancelUploadFile(std::int32_t file_id_);

    static const std::int32_t ID = 1623539600;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class changeChatReportSpamState final : public Function
{
public:
    std::int64_t chat_id_;
    bool is_spam_chat_;

    changeChatReportSpamState();

    changeChatReportSpamState(std::int64_t chat_id_, bool is_spam_chat_);

    static const std::int32_t ID = 1768597097;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class changeImportedContacts final : public Function
{
public:
    std::vector<object_ptr<contact>> contacts_;

    changeImportedContacts();

    explicit changeImportedContacts(std::vector<object_ptr<contact>> &&contacts_);

    static const std::int32_t ID = 1968207955;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<importedContacts>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class changePhoneNumber final : public Function
{
public:
    std::string phone_number_;
    bool allow_flash_call_;
    bool is_current_phone_number_;

    changePhoneNumber();

    changePhoneNumber(std::string const &phone_number_, bool allow_flash_call_,
                      bool is_current_phone_number_);

    static const std::int32_t ID = -1510625218;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<authenticationCodeInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class changeStickerSet final : public Function
{
public:
    std::int64_t set_id_;
    bool is_installed_;
    bool is_archived_;

    changeStickerSet();

    changeStickerSet(std::int64_t set_id_, bool is_installed_, bool is_archived_);

    static const std::int32_t ID = 449357293;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkAuthenticationBotToken final : public Function
{
public:
    std::string token_;

    checkAuthenticationBotToken();

    explicit checkAuthenticationBotToken(std::string const &token_);

    static const std::int32_t ID = 639321206;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkAuthenticationCode final : public Function
{
public:
    std::string code_;
    std::string first_name_;
    std::string last_name_;

    checkAuthenticationCode();

    checkAuthenticationCode(std::string const &code_, std::string const &first_name_,
                            std::string const &last_name_);

    static const std::int32_t ID = -707293555;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkAuthenticationPassword final : public Function
{
public:
    std::string password_;

    checkAuthenticationPassword();

    explicit checkAuthenticationPassword(std::string const &password_);

    static const std::int32_t ID = -2025698400;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkChangePhoneNumberCode final : public Function
{
public:
    std::string code_;

    checkChangePhoneNumberCode();

    explicit checkChangePhoneNumberCode(std::string const &code_);

    static const std::int32_t ID = -1720278429;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkChatInviteLink final : public Function
{
public:
    std::string invite_link_;

    checkChatInviteLink();

    explicit checkChatInviteLink(std::string const &invite_link_);

    static const std::int32_t ID = -496940997;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatInviteLinkInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkChatUsername final : public Function
{
public:
    std::int64_t chat_id_;
    std::string username_;

    checkChatUsername();

    checkChatUsername(std::int64_t chat_id_, std::string const &username_);

    static const std::int32_t ID = -2003506154;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<CheckChatUsernameResult>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkDatabaseEncryptionKey final : public Function
{
public:
    std::string encryption_key_;

    checkDatabaseEncryptionKey();

    explicit checkDatabaseEncryptionKey(std::string const &encryption_key_);

    static const std::int32_t ID = 1018769307;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class clearImportedContacts final : public Function
{
public:

    clearImportedContacts();

    static const std::int32_t ID = 869503298;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class clearRecentStickers final : public Function
{
public:
    bool is_attached_;

    clearRecentStickers();

    explicit clearRecentStickers(bool is_attached_);

    static const std::int32_t ID = -321242684;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class clearRecentlyFoundChats final : public Function
{
public:

    clearRecentlyFoundChats();

    static const std::int32_t ID = -285582542;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class close final : public Function
{
public:

    close();

    static const std::int32_t ID = -1187782273;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class closeChat final : public Function
{
public:
    std::int64_t chat_id_;

    closeChat();

    explicit closeChat(std::int64_t chat_id_);

    static const std::int32_t ID = 39749353;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class closeSecretChat final : public Function
{
public:
    std::int32_t secret_chat_id_;

    closeSecretChat();

    explicit closeSecretChat(std::int32_t secret_chat_id_);

    static const std::int32_t ID = -471006133;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createBasicGroupChat final : public Function
{
public:
    std::int32_t basic_group_id_;
    bool force_;

    createBasicGroupChat();

    createBasicGroupChat(std::int32_t basic_group_id_, bool force_);

    static const std::int32_t ID = 642492777;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createCall final : public Function
{
public:
    std::int32_t user_id_;
    object_ptr<callProtocol> protocol_;

    createCall();

    createCall(std::int32_t user_id_, object_ptr<callProtocol> &&protocol_);

    static const std::int32_t ID = -1742408159;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<callId>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createNewBasicGroupChat final : public Function
{
public:
    std::vector<std::int32_t> user_ids_;
    std::string title_;

    createNewBasicGroupChat();

    createNewBasicGroupChat(std::vector<std::int32_t> &&user_ids_, std::string const &title_);

    static const std::int32_t ID = 1874532069;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createNewSecretChat final : public Function
{
public:
    std::int32_t user_id_;

    createNewSecretChat();

    explicit createNewSecretChat(std::int32_t user_id_);

    static const std::int32_t ID = 1689344881;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createNewStickerSet final : public Function
{
public:
    std::int32_t user_id_;
    std::string title_;
    std::string name_;
    bool is_masks_;
    std::vector<object_ptr<inputSticker>> stickers_;

    createNewStickerSet();

    createNewStickerSet(std::int32_t user_id_, std::string const &title_, std::string const &name_,
                        bool is_masks_, std::vector<object_ptr<inputSticker>> &&stickers_);

    static const std::int32_t ID = 205093058;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSet>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createNewSupergroupChat final : public Function
{
public:
    std::string title_;
    bool is_channel_;
    std::string description_;

    createNewSupergroupChat();

    createNewSupergroupChat(std::string const &title_, bool is_channel_,
                            std::string const &description_);

    static const std::int32_t ID = 1284982268;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createPrivateChat final : public Function
{
public:
    std::int32_t user_id_;
    bool force_;

    createPrivateChat();

    createPrivateChat(std::int32_t user_id_, bool force_);

    static const std::int32_t ID = -1807530364;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createSecretChat final : public Function
{
public:
    std::int32_t secret_chat_id_;

    createSecretChat();

    explicit createSecretChat(std::int32_t secret_chat_id_);

    static const std::int32_t ID = 1930285615;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createSupergroupChat final : public Function
{
public:
    std::int32_t supergroup_id_;
    bool force_;

    createSupergroupChat();

    createSupergroupChat(std::int32_t supergroup_id_, bool force_);

    static const std::int32_t ID = 352742758;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createTemporaryPassword final : public Function
{
public:
    std::string password_;
    std::int32_t valid_for_;

    createTemporaryPassword();

    createTemporaryPassword(std::string const &password_, std::int32_t valid_for_);

    static const std::int32_t ID = -1626509434;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<temporaryPasswordState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteAccount final : public Function
{
public:
    std::string reason_;

    deleteAccount();

    explicit deleteAccount(std::string const &reason_);

    static const std::int32_t ID = -1203056508;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteChatHistory final : public Function
{
public:
    std::int64_t chat_id_;
    bool remove_from_chat_list_;

    deleteChatHistory();

    deleteChatHistory(std::int64_t chat_id_, bool remove_from_chat_list_);

    static const std::int32_t ID = -1384632722;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteChatMessagesFromUser final : public Function
{
public:
    std::int64_t chat_id_;
    std::int32_t user_id_;

    deleteChatMessagesFromUser();

    deleteChatMessagesFromUser(std::int64_t chat_id_, std::int32_t user_id_);

    static const std::int32_t ID = -1599689199;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteChatReplyMarkup final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;

    deleteChatReplyMarkup();

    deleteChatReplyMarkup(std::int64_t chat_id_, std::int64_t message_id_);

    static const std::int32_t ID = 100637531;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteFile final : public Function
{
public:
    std::int32_t file_id_;

    deleteFile();

    explicit deleteFile(std::int32_t file_id_);

    static const std::int32_t ID = 1807653676;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteMessages final : public Function
{
public:
    std::int64_t chat_id_;
    std::vector<std::int64_t> message_ids_;
    bool revoke_;

    deleteMessages();

    deleteMessages(std::int64_t chat_id_, std::vector<std::int64_t> &&message_ids_, bool revoke_);

    static const std::int32_t ID = 1130090173;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteProfilePhoto final : public Function
{
public:
    std::int64_t profile_photo_id_;

    deleteProfilePhoto();

    explicit deleteProfilePhoto(std::int64_t profile_photo_id_);

    static const std::int32_t ID = 1319794625;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteSavedCredentials final : public Function
{
public:

    deleteSavedCredentials();

    static const std::int32_t ID = 826300114;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteSavedOrderInfo final : public Function
{
public:

    deleteSavedOrderInfo();

    static const std::int32_t ID = 1629058164;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteSupergroup final : public Function
{
public:
    std::int32_t supergroup_id_;

    deleteSupergroup();

    explicit deleteSupergroup(std::int32_t supergroup_id_);

    static const std::int32_t ID = -1999855965;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class destroy final : public Function
{
public:

    destroy();

    static const std::int32_t ID = 685331274;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class discardCall final : public Function
{
public:
    std::int32_t call_id_;
    bool is_disconnected_;
    std::int32_t duration_;
    std::int64_t connection_id_;

    discardCall();

    discardCall(std::int32_t call_id_, bool is_disconnected_, std::int32_t duration_,
                std::int64_t connection_id_);

    static const std::int32_t ID = -923187372;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class disconnectAllWebsites final : public Function
{
public:

    disconnectAllWebsites();

    static const std::int32_t ID = -1082985981;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class disconnectWebsite final : public Function
{
public:
    std::int64_t website_id_;

    disconnectWebsite();

    explicit disconnectWebsite(std::int64_t website_id_);

    static const std::int32_t ID = -778767395;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class downloadFile final : public Function
{
public:
    std::int32_t file_id_;
    std::int32_t priority_;

    downloadFile();

    downloadFile(std::int32_t file_id_, std::int32_t priority_);

    static const std::int32_t ID = 1531851978;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<file>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editInlineMessageCaption final : public Function
{
public:
    std::string inline_message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<formattedText> caption_;

    editInlineMessageCaption();

    editInlineMessageCaption(std::string const &inline_message_id_,
                             object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<formattedText> &&caption_);

    static const std::int32_t ID = -760985929;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editInlineMessageLiveLocation final : public Function
{
public:
    std::string inline_message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<location> location_;

    editInlineMessageLiveLocation();

    editInlineMessageLiveLocation(std::string const &inline_message_id_,
                                  object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<location> &&location_);

    static const std::int32_t ID = 655046316;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editInlineMessageReplyMarkup final : public Function
{
public:
    std::string inline_message_id_;
    object_ptr<ReplyMarkup> reply_markup_;

    editInlineMessageReplyMarkup();

    editInlineMessageReplyMarkup(std::string const &inline_message_id_,
                                 object_ptr<ReplyMarkup> &&reply_markup_);

    static const std::int32_t ID = -67565858;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editInlineMessageText final : public Function
{
public:
    std::string inline_message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    editInlineMessageText();

    editInlineMessageText(std::string const &inline_message_id_,
                          object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = -855457307;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editMessageCaption final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<formattedText> caption_;

    editMessageCaption();

    editMessageCaption(std::int64_t chat_id_, std::int64_t message_id_,
                       object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<formattedText> &&caption_);

    static const std::int32_t ID = 1154677038;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editMessageLiveLocation final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<location> location_;

    editMessageLiveLocation();

    editMessageLiveLocation(std::int64_t chat_id_, std::int64_t message_id_,
                            object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<location> &&location_);

    static const std::int32_t ID = -1146772745;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editMessageReplyMarkup final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    object_ptr<ReplyMarkup> reply_markup_;

    editMessageReplyMarkup();

    editMessageReplyMarkup(std::int64_t chat_id_, std::int64_t message_id_,
                           object_ptr<ReplyMarkup> &&reply_markup_);

    static const std::int32_t ID = 332127881;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editMessageText final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    editMessageText();

    editMessageText(std::int64_t chat_id_, std::int64_t message_id_,
                    object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 196272567;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class finishFileGeneration final : public Function
{
public:
    std::int64_t generation_id_;
    object_ptr<error> error_;

    finishFileGeneration();

    finishFileGeneration(std::int64_t generation_id_, object_ptr<error> &&error_);

    static const std::int32_t ID = -1055060835;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class forwardMessages final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t from_chat_id_;
    std::vector<std::int64_t> message_ids_;
    bool disable_notification_;
    bool from_background_;
    bool as_album_;

    forwardMessages();

    forwardMessages(std::int64_t chat_id_, std::int64_t from_chat_id_,
                    std::vector<std::int64_t> &&message_ids_, bool disable_notification_, bool from_background_,
                    bool as_album_);

    static const std::int32_t ID = -537573308;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class generateChatInviteLink final : public Function
{
public:
    std::int64_t chat_id_;

    generateChatInviteLink();

    explicit generateChatInviteLink(std::int64_t chat_id_);

    static const std::int32_t ID = 1945532500;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatInviteLink>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getAccountTtl final : public Function
{
public:

    getAccountTtl();

    static const std::int32_t ID = -443905161;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<accountTtl>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getActiveLiveLocationMessages final : public Function
{
public:

    getActiveLiveLocationMessages();

    static const std::int32_t ID = -1425459567;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getActiveSessions final : public Function
{
public:

    getActiveSessions();

    static const std::int32_t ID = 1119710526;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<sessions>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getArchivedStickerSets final : public Function
{
public:
    bool is_masks_;
    std::int64_t offset_sticker_set_id_;
    std::int32_t limit_;

    getArchivedStickerSets();

    getArchivedStickerSets(bool is_masks_, std::int64_t offset_sticker_set_id_, std::int32_t limit_);

    static const std::int32_t ID = 1996943238;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSets>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getAttachedStickerSets final : public Function
{
public:
    std::int32_t file_id_;

    getAttachedStickerSets();

    explicit getAttachedStickerSets(std::int32_t file_id_);

    static const std::int32_t ID = 1302172429;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSets>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getAuthorizationState final : public Function
{
public:

    getAuthorizationState();

    static const std::int32_t ID = 1949154877;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<AuthorizationState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getBasicGroup final : public Function
{
public:
    std::int32_t basic_group_id_;

    getBasicGroup();

    explicit getBasicGroup(std::int32_t basic_group_id_);

    static const std::int32_t ID = 561775568;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<basicGroup>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getBasicGroupFullInfo final : public Function
{
public:
    std::int32_t basic_group_id_;

    getBasicGroupFullInfo();

    explicit getBasicGroupFullInfo(std::int32_t basic_group_id_);

    static const std::int32_t ID = 1770517905;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<basicGroupFullInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getBlockedUsers final : public Function
{
public:
    std::int32_t offset_;
    std::int32_t limit_;

    getBlockedUsers();

    getBlockedUsers(std::int32_t offset_, std::int32_t limit_);

    static const std::int32_t ID = -742912777;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<users>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getCallbackQueryAnswer final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    object_ptr<CallbackQueryPayload> payload_;

    getCallbackQueryAnswer();

    getCallbackQueryAnswer(std::int64_t chat_id_, std::int64_t message_id_,
                           object_ptr<CallbackQueryPayload> &&payload_);

    static const std::int32_t ID = 116357727;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<callbackQueryAnswer>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChat final : public Function
{
public:
    std::int64_t chat_id_;

    getChat();

    explicit getChat(std::int64_t chat_id_);

    static const std::int32_t ID = 1866601536;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatAdministrators final : public Function
{
public:
    std::int64_t chat_id_;

    getChatAdministrators();

    explicit getChatAdministrators(std::int64_t chat_id_);

    static const std::int32_t ID = 508231041;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<users>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatEventLog final : public Function
{
public:
    std::int64_t chat_id_;
    std::string query_;
    std::int64_t from_event_id_;
    std::int32_t limit_;
    object_ptr<chatEventLogFilters> filters_;
    std::vector<std::int32_t> user_ids_;

    getChatEventLog();

    getChatEventLog(std::int64_t chat_id_, std::string const &query_, std::int64_t from_event_id_,
                    std::int32_t limit_, object_ptr<chatEventLogFilters> &&filters_,
                    std::vector<std::int32_t> &&user_ids_);

    static const std::int32_t ID = 206900967;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatEvents>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatHistory final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t from_message_id_;
    std::int32_t offset_;
    std::int32_t limit_;
    bool only_local_;

    getChatHistory();

    getChatHistory(std::int64_t chat_id_, std::int64_t from_message_id_, std::int32_t offset_,
                   std::int32_t limit_, bool only_local_);

    static const std::int32_t ID = -799960451;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatMember final : public Function
{
public:
    std::int64_t chat_id_;
    std::int32_t user_id_;

    getChatMember();

    getChatMember(std::int64_t chat_id_, std::int32_t user_id_);

    static const std::int32_t ID = 677085892;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatMember>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatMessageByDate final : public Function
{
public:
    std::int64_t chat_id_;
    std::int32_t date_;

    getChatMessageByDate();

    getChatMessageByDate(std::int64_t chat_id_, std::int32_t date_);

    static const std::int32_t ID = 1062564150;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatPinnedMessage final : public Function
{
public:
    std::int64_t chat_id_;

    getChatPinnedMessage();

    explicit getChatPinnedMessage(std::int64_t chat_id_);

    static const std::int32_t ID = 359865008;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatReportSpamState final : public Function
{
public:
    std::int64_t chat_id_;

    getChatReportSpamState();

    explicit getChatReportSpamState(std::int64_t chat_id_);

    static const std::int32_t ID = -748866856;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatReportSpamState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChats final : public Function
{
public:
    std::int64_t offset_order_;
    std::int64_t offset_chat_id_;
    std::int32_t limit_;

    getChats();

    getChats(std::int64_t offset_order_, std::int64_t offset_chat_id_, std::int32_t limit_);

    static const std::int32_t ID = -2121381601;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getConnectedWebsites final : public Function
{
public:

    getConnectedWebsites();

    static const std::int32_t ID = -170536110;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<connectedWebsites>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getCountryCode final : public Function
{
public:

    getCountryCode();

    static const std::int32_t ID = 1540593906;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<text>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getCreatedPublicChats final : public Function
{
public:

    getCreatedPublicChats();

    static const std::int32_t ID = 1609082914;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getFavoriteStickers final : public Function
{
public:

    getFavoriteStickers();

    static const std::int32_t ID = -338964672;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getFile final : public Function
{
public:
    std::int32_t file_id_;

    getFile();

    explicit getFile(std::int32_t file_id_);

    static const std::int32_t ID = 1553923406;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<file>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getFileExtension final : public Function
{
public:
    std::string mime_type_;

    getFileExtension();

    explicit getFileExtension(std::string const &mime_type_);

    static const std::int32_t ID = -106055372;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<text>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getFileMimeType final : public Function
{
public:
    std::string file_name_;

    getFileMimeType();

    explicit getFileMimeType(std::string const &file_name_);

    static const std::int32_t ID = -2073879671;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<text>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getGameHighScores final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    std::int32_t user_id_;

    getGameHighScores();

    getGameHighScores(std::int64_t chat_id_, std::int64_t message_id_, std::int32_t user_id_);

    static const std::int32_t ID = 1920923753;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<gameHighScores>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getGroupsInCommon final : public Function
{
public:
    std::int32_t user_id_;
    std::int64_t offset_chat_id_;
    std::int32_t limit_;

    getGroupsInCommon();

    getGroupsInCommon(std::int32_t user_id_, std::int64_t offset_chat_id_, std::int32_t limit_);

    static const std::int32_t ID = -23238689;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getImportedContactCount final : public Function
{
public:

    getImportedContactCount();

    static const std::int32_t ID = -656336346;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<count>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getInlineGameHighScores final : public Function
{
public:
    std::string inline_message_id_;
    std::int32_t user_id_;

    getInlineGameHighScores();

    getInlineGameHighScores(std::string const &inline_message_id_, std::int32_t user_id_);

    static const std::int32_t ID = -1833445800;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<gameHighScores>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getInlineQueryResults final : public Function
{
public:
    std::int32_t bot_user_id_;
    std::int64_t chat_id_;
    object_ptr<location> user_location_;
    std::string query_;
    std::string offset_;

    getInlineQueryResults();

    getInlineQueryResults(std::int32_t bot_user_id_, std::int64_t chat_id_,
                          object_ptr<location> &&user_location_, std::string const &query_, std::string const &offset_);

    static const std::int32_t ID = -1182511172;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<inlineQueryResults>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getInstalledStickerSets final : public Function
{
public:
    bool is_masks_;

    getInstalledStickerSets();

    explicit getInstalledStickerSets(bool is_masks_);

    static const std::int32_t ID = 1214523749;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSets>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getInviteText final : public Function
{
public:

    getInviteText();

    static const std::int32_t ID = 794573512;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<text>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getMe final : public Function
{
public:

    getMe();

    static const std::int32_t ID = -191516033;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<user>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getMessage final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;

    getMessage();

    getMessage(std::int64_t chat_id_, std::int64_t message_id_);

    static const std::int32_t ID = -1821196160;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getMessages final : public Function
{
public:
    std::int64_t chat_id_;
    std::vector<std::int64_t> message_ids_;

    getMessages();

    getMessages(std::int64_t chat_id_, std::vector<std::int64_t> &&message_ids_);

    static const std::int32_t ID = 425299338;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getNetworkStatistics final : public Function
{
public:
    bool only_current_;

    getNetworkStatistics();

    explicit getNetworkStatistics(bool only_current_);

    static const std::int32_t ID = -986228706;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<networkStatistics>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getNotificationSettings final : public Function
{
public:
    object_ptr<NotificationSettingsScope> scope_;

    getNotificationSettings();

    explicit getNotificationSettings(object_ptr<NotificationSettingsScope> &&scope_);

    static const std::int32_t ID = 907144391;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<notificationSettings>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getOption final : public Function
{
public:
    std::string name_;

    getOption();

    explicit getOption(std::string const &name_);

    static const std::int32_t ID = -1572495746;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<OptionValue>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getPasswordState final : public Function
{
public:

    getPasswordState();

    static const std::int32_t ID = -174752904;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<passwordState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getPaymentForm final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;

    getPaymentForm();

    getPaymentForm(std::int64_t chat_id_, std::int64_t message_id_);

    static const std::int32_t ID = -2146950882;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<paymentForm>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getPaymentReceipt final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;

    getPaymentReceipt();

    getPaymentReceipt(std::int64_t chat_id_, std::int64_t message_id_);

    static const std::int32_t ID = 1013758294;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<paymentReceipt>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getProxy final : public Function
{
public:

    getProxy();

    static const std::int32_t ID = 1389343170;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<Proxy>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getPublicMessageLink final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    bool for_album_;

    getPublicMessageLink();

    getPublicMessageLink(std::int64_t chat_id_, std::int64_t message_id_, bool for_album_);

    static const std::int32_t ID = -374642839;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<publicMessageLink>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getRecentInlineBots final : public Function
{
public:

    getRecentInlineBots();

    static const std::int32_t ID = 1437823548;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<users>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getRecentStickers final : public Function
{
public:
    bool is_attached_;

    getRecentStickers();

    explicit getRecentStickers(bool is_attached_);

    static const std::int32_t ID = -579622241;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getRecentlyVisitedTMeUrls final : public Function
{
public:
    std::string referrer_;

    getRecentlyVisitedTMeUrls();

    explicit getRecentlyVisitedTMeUrls(std::string const &referrer_);

    static const std::int32_t ID = 806754961;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<tMeUrls>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getRecoveryEmailAddress final : public Function
{
public:
    std::string password_;

    getRecoveryEmailAddress();

    explicit getRecoveryEmailAddress(std::string const &password_);

    static const std::int32_t ID = -1594770947;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<recoveryEmailAddress>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getRemoteFile final : public Function
{
public:
    std::string remote_file_id_;
    object_ptr<FileType> file_type_;

    getRemoteFile();

    getRemoteFile(std::string const &remote_file_id_, object_ptr<FileType> &&file_type_);

    static const std::int32_t ID = 2137204530;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<file>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getRepliedMessage final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;

    getRepliedMessage();

    getRepliedMessage(std::int64_t chat_id_, std::int64_t message_id_);

    static const std::int32_t ID = -641918531;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSavedAnimations final : public Function
{
public:

    getSavedAnimations();

    static const std::int32_t ID = 7051032;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<animations>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSavedOrderInfo final : public Function
{
public:

    getSavedOrderInfo();

    static const std::int32_t ID = -1152016675;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<orderInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSecretChat final : public Function
{
public:
    std::int32_t secret_chat_id_;

    getSecretChat();

    explicit getSecretChat(std::int32_t secret_chat_id_);

    static const std::int32_t ID = 40599169;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<secretChat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getStickerEmojis final : public Function
{
public:
    object_ptr<InputFile> sticker_;

    getStickerEmojis();

    explicit getStickerEmojis(object_ptr<InputFile> &&sticker_);

    static const std::int32_t ID = 95352475;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerEmojis>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getStickerSet final : public Function
{
public:
    std::int64_t set_id_;

    getStickerSet();

    explicit getStickerSet(std::int64_t set_id_);

    static const std::int32_t ID = 1052318659;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSet>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getStickers final : public Function
{
public:
    std::string emoji_;
    std::int32_t limit_;

    getStickers();

    getStickers(std::string const &emoji_, std::int32_t limit_);

    static const std::int32_t ID = -1594919556;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getStorageStatistics final : public Function
{
public:
    std::int32_t chat_limit_;

    getStorageStatistics();

    explicit getStorageStatistics(std::int32_t chat_limit_);

    static const std::int32_t ID = -853193929;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<storageStatistics>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getStorageStatisticsFast final : public Function
{
public:

    getStorageStatisticsFast();

    static const std::int32_t ID = 61368066;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<storageStatisticsFast>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSupergroup final : public Function
{
public:
    std::int32_t supergroup_id_;

    getSupergroup();

    explicit getSupergroup(std::int32_t supergroup_id_);

    static const std::int32_t ID = -2063063706;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<supergroup>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSupergroupFullInfo final : public Function
{
public:
    std::int32_t supergroup_id_;

    getSupergroupFullInfo();

    explicit getSupergroupFullInfo(std::int32_t supergroup_id_);

    static const std::int32_t ID = -1150331262;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<supergroupFullInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSupergroupMembers final : public Function
{
public:
    std::int32_t supergroup_id_;
    object_ptr<SupergroupMembersFilter> filter_;
    std::int32_t offset_;
    std::int32_t limit_;

    getSupergroupMembers();

    getSupergroupMembers(std::int32_t supergroup_id_, object_ptr<SupergroupMembersFilter> &&filter_,
                         std::int32_t offset_, std::int32_t limit_);

    static const std::int32_t ID = 1427643098;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatMembers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSupportUser final : public Function
{
public:

    getSupportUser();

    static const std::int32_t ID = -1733497700;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<user>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getTemporaryPasswordState final : public Function
{
public:

    getTemporaryPasswordState();

    static const std::int32_t ID = -12670830;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<temporaryPasswordState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getTermsOfService final : public Function
{
public:

    getTermsOfService();

    static const std::int32_t ID = 1835034646;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<text>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getTextEntities final : public Function
{
public:
    std::string text_;

    getTextEntities();

    explicit getTextEntities(std::string const &text_);

    static const std::int32_t ID = -341490693;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<textEntities>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getTopChats final : public Function
{
public:
    object_ptr<TopChatCategory> category_;
    std::int32_t limit_;

    getTopChats();

    getTopChats(object_ptr<TopChatCategory> &&category_, std::int32_t limit_);

    static const std::int32_t ID = -388410847;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getTrendingStickerSets final : public Function
{
public:

    getTrendingStickerSets();

    static const std::int32_t ID = -1729129957;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSets>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getUser final : public Function
{
public:
    std::int32_t user_id_;

    getUser();

    explicit getUser(std::int32_t user_id_);

    static const std::int32_t ID = -47586017;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<user>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getUserFullInfo final : public Function
{
public:
    std::int32_t user_id_;

    getUserFullInfo();

    explicit getUserFullInfo(std::int32_t user_id_);

    static const std::int32_t ID = -655443263;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<userFullInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getUserPrivacySettingRules final : public Function
{
public:
    object_ptr<UserPrivacySetting> setting_;

    getUserPrivacySettingRules();

    explicit getUserPrivacySettingRules(object_ptr<UserPrivacySetting> &&setting_);

    static const std::int32_t ID = -2077223311;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<userPrivacySettingRules>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getUserProfilePhotos final : public Function
{
public:
    std::int32_t user_id_;
    std::int32_t offset_;
    std::int32_t limit_;

    getUserProfilePhotos();

    getUserProfilePhotos(std::int32_t user_id_, std::int32_t offset_, std::int32_t limit_);

    static const std::int32_t ID = -2062927433;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<userProfilePhotos>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getWallpapers final : public Function
{
public:

    getWallpapers();

    static const std::int32_t ID = 2097518555;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<wallpapers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getWebPageInstantView final : public Function
{
public:
    std::string url_;
    bool force_full_;

    getWebPageInstantView();

    getWebPageInstantView(std::string const &url_, bool force_full_);

    static const std::int32_t ID = -1962649975;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<webPageInstantView>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getWebPagePreview final : public Function
{
public:
    object_ptr<formattedText> text_;

    getWebPagePreview();

    explicit getWebPagePreview(object_ptr<formattedText> &&text_);

    static const std::int32_t ID = 573441580;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<webPage>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class importContacts final : public Function
{
public:
    std::vector<object_ptr<contact>> contacts_;

    importContacts();

    explicit importContacts(std::vector<object_ptr<contact>> &&contacts_);

    static const std::int32_t ID = -215132767;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<importedContacts>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class joinChatByInviteLink final : public Function
{
public:
    std::string invite_link_;

    joinChatByInviteLink();

    explicit joinChatByInviteLink(std::string const &invite_link_);

    static const std::int32_t ID = -1049973882;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class logOut final : public Function
{
public:

    logOut();

    static const std::int32_t ID = -1581923301;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class openChat final : public Function
{
public:
    std::int64_t chat_id_;

    openChat();

    explicit openChat(std::int64_t chat_id_);

    static const std::int32_t ID = -323371509;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class openMessageContent final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;

    openMessageContent();

    openMessageContent(std::int64_t chat_id_, std::int64_t message_id_);

    static const std::int32_t ID = -739088005;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class optimizeStorage final : public Function
{
public:
    std::int64_t size_;
    std::int32_t ttl_;
    std::int32_t count_;
    std::int32_t immunity_delay_;
    std::vector<object_ptr<FileType>> file_types_;
    std::vector<std::int64_t> chat_ids_;
    std::vector<std::int64_t> exclude_chat_ids_;
    std::int32_t chat_limit_;

    optimizeStorage();

    optimizeStorage(std::int64_t size_, std::int32_t ttl_, std::int32_t count_,
                    std::int32_t immunity_delay_, std::vector<object_ptr<FileType>> &&file_types_,
                    std::vector<std::int64_t> &&chat_ids_, std::vector<std::int64_t> &&exclude_chat_ids_,
                    std::int32_t chat_limit_);

    static const std::int32_t ID = 980397489;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<storageStatistics>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class parseTextEntities final : public Function
{
public:
    std::string text_;
    object_ptr<TextParseMode> parse_mode_;

    parseTextEntities();

    parseTextEntities(std::string const &text_, object_ptr<TextParseMode> &&parse_mode_);

    static const std::int32_t ID = -1709194593;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<formattedText>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pinSupergroupMessage final : public Function
{
public:
    std::int32_t supergroup_id_;
    std::int64_t message_id_;
    bool disable_notification_;

    pinSupergroupMessage();

    pinSupergroupMessage(std::int32_t supergroup_id_, std::int64_t message_id_,
                         bool disable_notification_);

    static const std::int32_t ID = 1141187557;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class processDcUpdate final : public Function
{
public:
    std::string dc_;
    std::string addr_;

    processDcUpdate();

    processDcUpdate(std::string const &dc_, std::string const &addr_);

    static const std::int32_t ID = -1806562997;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class readAllChatMentions final : public Function
{
public:
    std::int64_t chat_id_;

    readAllChatMentions();

    explicit readAllChatMentions(std::int64_t chat_id_);

    static const std::int32_t ID = 1357558453;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class recoverAuthenticationPassword final : public Function
{
public:
    std::string recovery_code_;

    recoverAuthenticationPassword();

    explicit recoverAuthenticationPassword(std::string const &recovery_code_);

    static const std::int32_t ID = 787436412;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class recoverPassword final : public Function
{
public:
    std::string recovery_code_;

    recoverPassword();

    explicit recoverPassword(std::string const &recovery_code_);

    static const std::int32_t ID = 1660185903;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<passwordState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class registerDevice final : public Function
{
public:
    object_ptr<DeviceToken> device_token_;
    std::vector<std::int32_t> other_user_ids_;

    registerDevice();

    registerDevice(object_ptr<DeviceToken> &&device_token_,
                   std::vector<std::int32_t> &&other_user_ids_);

    static const std::int32_t ID = -413637293;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeContacts final : public Function
{
public:
    std::vector<std::int32_t> user_ids_;

    removeContacts();

    explicit removeContacts(std::vector<std::int32_t> &&user_ids_);

    static const std::int32_t ID = -615510759;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeFavoriteSticker final : public Function
{
public:
    object_ptr<InputFile> sticker_;

    removeFavoriteSticker();

    explicit removeFavoriteSticker(object_ptr<InputFile> &&sticker_);

    static const std::int32_t ID = 1152945264;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeRecentHashtag final : public Function
{
public:
    std::string hashtag_;

    removeRecentHashtag();

    explicit removeRecentHashtag(std::string const &hashtag_);

    static const std::int32_t ID = -1013735260;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeRecentSticker final : public Function
{
public:
    bool is_attached_;
    object_ptr<InputFile> sticker_;

    removeRecentSticker();

    removeRecentSticker(bool is_attached_, object_ptr<InputFile> &&sticker_);

    static const std::int32_t ID = 1246577677;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeRecentlyFoundChat final : public Function
{
public:
    std::int64_t chat_id_;

    removeRecentlyFoundChat();

    explicit removeRecentlyFoundChat(std::int64_t chat_id_);

    static const std::int32_t ID = 717340444;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeSavedAnimation final : public Function
{
public:
    object_ptr<InputFile> animation_;

    removeSavedAnimation();

    explicit removeSavedAnimation(object_ptr<InputFile> &&animation_);

    static const std::int32_t ID = -495605479;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeStickerFromSet final : public Function
{
public:
    object_ptr<InputFile> sticker_;

    removeStickerFromSet();

    explicit removeStickerFromSet(object_ptr<InputFile> &&sticker_);

    static const std::int32_t ID = 1642196644;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeTopChat final : public Function
{
public:
    object_ptr<TopChatCategory> category_;
    std::int64_t chat_id_;

    removeTopChat();

    removeTopChat(object_ptr<TopChatCategory> &&category_, std::int64_t chat_id_);

    static const std::int32_t ID = -1907876267;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class reorderInstalledStickerSets final : public Function
{
public:
    bool is_masks_;
    std::vector<std::int64_t> sticker_set_ids_;

    reorderInstalledStickerSets();

    reorderInstalledStickerSets(bool is_masks_, std::vector<std::int64_t> &&sticker_set_ids_);

    static const std::int32_t ID = 1114537563;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class reportChat final : public Function
{
public:
    std::int64_t chat_id_;
    object_ptr<ChatReportReason> reason_;
    std::vector<std::int64_t> message_ids_;

    reportChat();

    reportChat(std::int64_t chat_id_, object_ptr<ChatReportReason> &&reason_,
               std::vector<std::int64_t> &&message_ids_);

    static const std::int32_t ID = -312579772;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class reportSupergroupSpam final : public Function
{
public:
    std::int32_t supergroup_id_;
    std::int32_t user_id_;
    std::vector<std::int64_t> message_ids_;

    reportSupergroupSpam();

    reportSupergroupSpam(std::int32_t supergroup_id_, std::int32_t user_id_,
                         std::vector<std::int64_t> &&message_ids_);

    static const std::int32_t ID = -2125451498;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class requestAuthenticationPasswordRecovery final : public Function
{
public:

    requestAuthenticationPasswordRecovery();

    static const std::int32_t ID = 1393896118;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class requestPasswordRecovery final : public Function
{
public:

    requestPasswordRecovery();

    static const std::int32_t ID = 1989252384;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<passwordRecoveryInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class resendAuthenticationCode final : public Function
{
public:

    resendAuthenticationCode();

    static const std::int32_t ID = -814377191;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class resendChangePhoneNumberCode final : public Function
{
public:

    resendChangePhoneNumberCode();

    static const std::int32_t ID = -786772060;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<authenticationCodeInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class resetAllNotificationSettings final : public Function
{
public:

    resetAllNotificationSettings();

    static const std::int32_t ID = -174020359;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class resetNetworkStatistics final : public Function
{
public:

    resetNetworkStatistics();

    static const std::int32_t ID = 1646452102;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchCallMessages final : public Function
{
public:
    std::int64_t from_message_id_;
    std::int32_t limit_;
    bool only_missed_;

    searchCallMessages();

    searchCallMessages(std::int64_t from_message_id_, std::int32_t limit_, bool only_missed_);

    static const std::int32_t ID = -1077230820;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchChatMembers final : public Function
{
public:
    std::int64_t chat_id_;
    std::string query_;
    std::int32_t limit_;

    searchChatMembers();

    searchChatMembers(std::int64_t chat_id_, std::string const &query_, std::int32_t limit_);

    static const std::int32_t ID = -1538035890;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatMembers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchChatMessages final : public Function
{
public:
    std::int64_t chat_id_;
    std::string query_;
    std::int32_t sender_user_id_;
    std::int64_t from_message_id_;
    std::int32_t offset_;
    std::int32_t limit_;
    object_ptr<SearchMessagesFilter> filter_;

    searchChatMessages();

    searchChatMessages(std::int64_t chat_id_, std::string const &query_, std::int32_t sender_user_id_,
                       std::int64_t from_message_id_, std::int32_t offset_, std::int32_t limit_,
                       object_ptr<SearchMessagesFilter> &&filter_);

    static const std::int32_t ID = -1528846671;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchChatRecentLocationMessages final : public Function
{
public:
    std::int64_t chat_id_;
    std::int32_t limit_;

    searchChatRecentLocationMessages();

    searchChatRecentLocationMessages(std::int64_t chat_id_, std::int32_t limit_);

    static const std::int32_t ID = 950238950;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchChats final : public Function
{
public:
    std::string query_;
    std::int32_t limit_;

    searchChats();

    searchChats(std::string const &query_, std::int32_t limit_);

    static const std::int32_t ID = -1879787060;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchChatsOnServer final : public Function
{
public:
    std::string query_;
    std::int32_t limit_;

    searchChatsOnServer();

    searchChatsOnServer(std::string const &query_, std::int32_t limit_);

    static const std::int32_t ID = -1158402188;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchContacts final : public Function
{
public:
    std::string query_;
    std::int32_t limit_;

    searchContacts();

    searchContacts(std::string const &query_, std::int32_t limit_);

    static const std::int32_t ID = -1794690715;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<users>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchHashtags final : public Function
{
public:
    std::string prefix_;
    std::int32_t limit_;

    searchHashtags();

    searchHashtags(std::string const &prefix_, std::int32_t limit_);

    static const std::int32_t ID = 1043637617;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<hashtags>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchInstalledStickerSets final : public Function
{
public:
    bool is_masks_;
    std::string query_;
    std::int32_t limit_;

    searchInstalledStickerSets();

    searchInstalledStickerSets(bool is_masks_, std::string const &query_, std::int32_t limit_);

    static const std::int32_t ID = 681171344;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSets>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessages final : public Function
{
public:
    std::string query_;
    std::int32_t offset_date_;
    std::int64_t offset_chat_id_;
    std::int64_t offset_message_id_;
    std::int32_t limit_;

    searchMessages();

    searchMessages(std::string const &query_, std::int32_t offset_date_, std::int64_t offset_chat_id_,
                   std::int64_t offset_message_id_, std::int32_t limit_);

    static const std::int32_t ID = 1579305146;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchPublicChat final : public Function
{
public:
    std::string username_;

    searchPublicChat();

    explicit searchPublicChat(std::string const &username_);

    static const std::int32_t ID = 857135533;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchPublicChats final : public Function
{
public:
    std::string query_;

    searchPublicChats();

    explicit searchPublicChats(std::string const &query_);

    static const std::int32_t ID = 970385337;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchSecretMessages final : public Function
{
public:
    std::int64_t chat_id_;
    std::string query_;
    std::int64_t from_search_id_;
    std::int32_t limit_;
    object_ptr<SearchMessagesFilter> filter_;

    searchSecretMessages();

    searchSecretMessages(std::int64_t chat_id_, std::string const &query_, std::int64_t from_search_id_,
                         std::int32_t limit_, object_ptr<SearchMessagesFilter> &&filter_);

    static const std::int32_t ID = -1670627915;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<foundMessages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchStickerSet final : public Function
{
public:
    std::string name_;

    searchStickerSet();

    explicit searchStickerSet(std::string const &name_);

    static const std::int32_t ID = 1157930222;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSet>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchStickerSets final : public Function
{
public:
    std::string query_;

    searchStickerSets();

    explicit searchStickerSets(std::string const &query_);

    static const std::int32_t ID = -1082314629;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSets>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchStickers final : public Function
{
public:
    std::string emoji_;
    std::int32_t limit_;

    searchStickers();

    searchStickers(std::string const &emoji_, std::int32_t limit_);

    static const std::int32_t ID = 1555771203;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendBotStartMessage final : public Function
{
public:
    std::int32_t bot_user_id_;
    std::int64_t chat_id_;
    std::string parameter_;

    sendBotStartMessage();

    sendBotStartMessage(std::int32_t bot_user_id_, std::int64_t chat_id_,
                        std::string const &parameter_);

    static const std::int32_t ID = 1112181339;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendCallDebugInformation final : public Function
{
public:
    std::int32_t call_id_;
    std::string debug_information_;

    sendCallDebugInformation();

    sendCallDebugInformation(std::int32_t call_id_, std::string const &debug_information_);

    static const std::int32_t ID = 2019243839;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendCallRating final : public Function
{
public:
    std::int32_t call_id_;
    std::int32_t rating_;
    std::string comment_;

    sendCallRating();

    sendCallRating(std::int32_t call_id_, std::int32_t rating_, std::string const &comment_);

    static const std::int32_t ID = 243075146;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendChatAction final : public Function
{
public:
    std::int64_t chat_id_;
    object_ptr<ChatAction> action_;

    sendChatAction();

    sendChatAction(std::int64_t chat_id_, object_ptr<ChatAction> &&action_);

    static const std::int32_t ID = -841357536;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendChatScreenshotTakenNotification final : public Function
{
public:
    std::int64_t chat_id_;

    sendChatScreenshotTakenNotification();

    explicit sendChatScreenshotTakenNotification(std::int64_t chat_id_);

    static const std::int32_t ID = 448399457;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendChatSetTtlMessage final : public Function
{
public:
    std::int64_t chat_id_;
    std::int32_t ttl_;

    sendChatSetTtlMessage();

    sendChatSetTtlMessage(std::int64_t chat_id_, std::int32_t ttl_);

    static const std::int32_t ID = 1432535564;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendCustomRequest final : public Function
{
public:
    std::string method_;
    std::string parameters_;

    sendCustomRequest();

    sendCustomRequest(std::string const &method_, std::string const &parameters_);

    static const std::int32_t ID = 285045153;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<customRequestResult>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendInlineQueryResultMessage final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t reply_to_message_id_;
    bool disable_notification_;
    bool from_background_;
    std::int64_t query_id_;
    std::string result_id_;

    sendInlineQueryResultMessage();

    sendInlineQueryResultMessage(std::int64_t chat_id_, std::int64_t reply_to_message_id_,
                                 bool disable_notification_, bool from_background_, std::int64_t query_id_,
                                 std::string const &result_id_);

    static const std::int32_t ID = -643910868;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendMessage final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t reply_to_message_id_;
    bool disable_notification_;
    bool from_background_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    sendMessage();

    sendMessage(std::int64_t chat_id_, std::int64_t reply_to_message_id_, bool disable_notification_,
                bool from_background_, object_ptr<ReplyMarkup> &&reply_markup_,
                object_ptr<InputMessageContent> &&input_message_content_);

    static const std::int32_t ID = 1694632114;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendMessageAlbum final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t reply_to_message_id_;
    bool disable_notification_;
    bool from_background_;
    std::vector<object_ptr<InputMessageContent>> input_message_contents_;

    sendMessageAlbum();

    sendMessageAlbum(std::int64_t chat_id_, std::int64_t reply_to_message_id_,
                     bool disable_notification_, bool from_background_,
                     std::vector<object_ptr<InputMessageContent>> &&input_message_contents_);

    static const std::int32_t ID = -291823014;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendPaymentForm final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    std::string order_info_id_;
    std::string shipping_option_id_;
    object_ptr<InputCredentials> credentials_;

    sendPaymentForm();

    sendPaymentForm(std::int64_t chat_id_, std::int64_t message_id_, std::string const &order_info_id_,
                    std::string const &shipping_option_id_, object_ptr<InputCredentials> &&credentials_);

    static const std::int32_t ID = 591581572;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<paymentResult>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setAccountTtl final : public Function
{
public:
    object_ptr<accountTtl> ttl_;

    setAccountTtl();

    explicit setAccountTtl(object_ptr<accountTtl> &&ttl_);

    static const std::int32_t ID = 701389032;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setAlarm final : public Function
{
public:
    double seconds_;

    setAlarm();

    explicit setAlarm(double seconds_);

    static const std::int32_t ID = -873497067;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setAuthenticationPhoneNumber final : public Function
{
public:
    std::string phone_number_;
    bool allow_flash_call_;
    bool is_current_phone_number_;

    setAuthenticationPhoneNumber();

    setAuthenticationPhoneNumber(std::string const &phone_number_, bool allow_flash_call_,
                                 bool is_current_phone_number_);

    static const std::int32_t ID = -856055465;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setBio final : public Function
{
public:
    std::string bio_;

    setBio();

    explicit setBio(std::string const &bio_);

    static const std::int32_t ID = -1619582124;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setBotUpdatesStatus final : public Function
{
public:
    std::int32_t pending_update_count_;
    std::string error_message_;

    setBotUpdatesStatus();

    setBotUpdatesStatus(std::int32_t pending_update_count_, std::string const &error_message_);

    static const std::int32_t ID = -1154926191;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatClientData final : public Function
{
public:
    std::int64_t chat_id_;
    std::string client_data_;

    setChatClientData();

    setChatClientData(std::int64_t chat_id_, std::string const &client_data_);

    static const std::int32_t ID = -827119811;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatDraftMessage final : public Function
{
public:
    std::int64_t chat_id_;
    object_ptr<draftMessage> draft_message_;

    setChatDraftMessage();

    setChatDraftMessage(std::int64_t chat_id_, object_ptr<draftMessage> &&draft_message_);

    static const std::int32_t ID = -588175579;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatMemberStatus final : public Function
{
public:
    std::int64_t chat_id_;
    std::int32_t user_id_;
    object_ptr<ChatMemberStatus> status_;

    setChatMemberStatus();

    setChatMemberStatus(std::int64_t chat_id_, std::int32_t user_id_,
                        object_ptr<ChatMemberStatus> &&status_);

    static const std::int32_t ID = -1754439241;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatPhoto final : public Function
{
public:
    std::int64_t chat_id_;
    object_ptr<InputFile> photo_;

    setChatPhoto();

    setChatPhoto(std::int64_t chat_id_, object_ptr<InputFile> &&photo_);

    static const std::int32_t ID = 132244217;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatTitle final : public Function
{
public:
    std::int64_t chat_id_;
    std::string title_;

    setChatTitle();

    setChatTitle(std::int64_t chat_id_, std::string const &title_);

    static const std::int32_t ID = 164282047;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setDatabaseEncryptionKey final : public Function
{
public:
    std::string new_encryption_key_;

    setDatabaseEncryptionKey();

    explicit setDatabaseEncryptionKey(std::string const &new_encryption_key_);

    static const std::int32_t ID = -1204599371;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setFileGenerationProgress final : public Function
{
public:
    std::int64_t generation_id_;
    std::int32_t expected_size_;
    std::int32_t local_prefix_size_;

    setFileGenerationProgress();

    setFileGenerationProgress(std::int64_t generation_id_, std::int32_t expected_size_,
                              std::int32_t local_prefix_size_);

    static const std::int32_t ID = -540459953;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setGameScore final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    bool edit_message_;
    std::int32_t user_id_;
    std::int32_t score_;
    bool force_;

    setGameScore();

    setGameScore(std::int64_t chat_id_, std::int64_t message_id_, bool edit_message_,
                 std::int32_t user_id_, std::int32_t score_, bool force_);

    static const std::int32_t ID = -1768307069;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setInlineGameScore final : public Function
{
public:
    std::string inline_message_id_;
    bool edit_message_;
    std::int32_t user_id_;
    std::int32_t score_;
    bool force_;

    setInlineGameScore();

    setInlineGameScore(std::string const &inline_message_id_, bool edit_message_, std::int32_t user_id_,
                       std::int32_t score_, bool force_);

    static const std::int32_t ID = 758435487;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setName final : public Function
{
public:
    std::string first_name_;
    std::string last_name_;

    setName();

    setName(std::string const &first_name_, std::string const &last_name_);

    static const std::int32_t ID = 1711693584;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setNetworkType final : public Function
{
public:
    object_ptr<NetworkType> type_;

    setNetworkType();

    explicit setNetworkType(object_ptr<NetworkType> &&type_);

    static const std::int32_t ID = -701635234;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setNotificationSettings final : public Function
{
public:
    object_ptr<NotificationSettingsScope> scope_;
    object_ptr<notificationSettings> notification_settings_;

    setNotificationSettings();

    setNotificationSettings(object_ptr<NotificationSettingsScope> &&scope_,
                            object_ptr<notificationSettings> &&notification_settings_);

    static const std::int32_t ID = -134430483;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setOption final : public Function
{
public:
    std::string name_;
    object_ptr<OptionValue> value_;

    setOption();

    setOption(std::string const &name_, object_ptr<OptionValue> &&value_);

    static const std::int32_t ID = 2114670322;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setPassword final : public Function
{
public:
    std::string old_password_;
    std::string new_password_;
    std::string new_hint_;
    bool set_recovery_email_address_;
    std::string new_recovery_email_address_;

    setPassword();

    setPassword(std::string const &old_password_, std::string const &new_password_,
                std::string const &new_hint_, bool set_recovery_email_address_,
                std::string const &new_recovery_email_address_);

    static const std::int32_t ID = -1193589027;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<passwordState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setPinnedChats final : public Function
{
public:
    std::vector<std::int64_t> chat_ids_;

    setPinnedChats();

    explicit setPinnedChats(std::vector<std::int64_t> &&chat_ids_);

    static const std::int32_t ID = -1369665719;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setProfilePhoto final : public Function
{
public:
    object_ptr<InputFile> photo_;

    setProfilePhoto();

    explicit setProfilePhoto(object_ptr<InputFile> &&photo_);

    static const std::int32_t ID = 1594734550;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setProxy final : public Function
{
public:
    object_ptr<Proxy> proxy_;

    setProxy();

    explicit setProxy(object_ptr<Proxy> &&proxy_);

    static const std::int32_t ID = -656782179;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setRecoveryEmailAddress final : public Function
{
public:
    std::string password_;
    std::string new_recovery_email_address_;

    setRecoveryEmailAddress();

    setRecoveryEmailAddress(std::string const &password_,
                            std::string const &new_recovery_email_address_);

    static const std::int32_t ID = -1981836385;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<passwordState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setStickerPositionInSet final : public Function
{
public:
    object_ptr<InputFile> sticker_;
    std::int32_t position_;

    setStickerPositionInSet();

    setStickerPositionInSet(object_ptr<InputFile> &&sticker_, std::int32_t position_);

    static const std::int32_t ID = 2075281185;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setSupergroupDescription final : public Function
{
public:
    std::int32_t supergroup_id_;
    std::string description_;

    setSupergroupDescription();

    setSupergroupDescription(std::int32_t supergroup_id_, std::string const &description_);

    static const std::int32_t ID = 227623488;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setSupergroupStickerSet final : public Function
{
public:
    std::int32_t supergroup_id_;
    std::int64_t sticker_set_id_;

    setSupergroupStickerSet();

    setSupergroupStickerSet(std::int32_t supergroup_id_, std::int64_t sticker_set_id_);

    static const std::int32_t ID = -295782298;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setSupergroupUsername final : public Function
{
public:
    std::int32_t supergroup_id_;
    std::string username_;

    setSupergroupUsername();

    setSupergroupUsername(std::int32_t supergroup_id_, std::string const &username_);

    static const std::int32_t ID = -1428333122;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setTdlibParameters final : public Function
{
public:
    object_ptr<tdlibParameters> parameters_;

    setTdlibParameters();

    explicit setTdlibParameters(object_ptr<tdlibParameters> &&parameters_);

    static const std::int32_t ID = -1912557997;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setUserPrivacySettingRules final : public Function
{
public:
    object_ptr<UserPrivacySetting> setting_;
    object_ptr<userPrivacySettingRules> rules_;

    setUserPrivacySettingRules();

    setUserPrivacySettingRules(object_ptr<UserPrivacySetting> &&setting_,
                               object_ptr<userPrivacySettingRules> &&rules_);

    static const std::int32_t ID = -473812741;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setUsername final : public Function
{
public:
    std::string username_;

    setUsername();

    explicit setUsername(std::string const &username_);

    static const std::int32_t ID = 439901214;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class terminateAllOtherSessions final : public Function
{
public:

    terminateAllOtherSessions();

    static const std::int32_t ID = 1874485523;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class terminateSession final : public Function
{
public:
    std::int64_t session_id_;

    terminateSession();

    explicit terminateSession(std::int64_t session_id_);

    static const std::int32_t ID = -407385812;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testCallBytes final : public Function
{
public:
    std::string x_;

    testCallBytes();

    explicit testCallBytes(std::string const &x_);

    static const std::int32_t ID = -736011607;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<testBytes>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testCallEmpty final : public Function
{
public:

    testCallEmpty();

    static const std::int32_t ID = -627291626;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testCallString final : public Function
{
public:
    std::string x_;

    testCallString();

    explicit testCallString(std::string const &x_);

    static const std::int32_t ID = -1732818385;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<testString>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testCallVectorInt final : public Function
{
public:
    std::vector<std::int32_t> x_;

    testCallVectorInt();

    explicit testCallVectorInt(std::vector<std::int32_t> &&x_);

    static const std::int32_t ID = -2137277793;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<testVectorInt>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testCallVectorIntObject final : public Function
{
public:
    std::vector<object_ptr<testInt>> x_;

    testCallVectorIntObject();

    explicit testCallVectorIntObject(std::vector<object_ptr<testInt>> &&x_);

    static const std::int32_t ID = 1825428218;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<testVectorIntObject>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testCallVectorString final : public Function
{
public:
    std::vector<std::string> x_;

    testCallVectorString();

    explicit testCallVectorString(std::vector<std::string> &&x_);

    static const std::int32_t ID = -408600900;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<testVectorString>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testCallVectorStringObject final : public Function
{
public:
    std::vector<object_ptr<testString>> x_;

    testCallVectorStringObject();

    explicit testCallVectorStringObject(std::vector<object_ptr<testString>> &&x_);

    static const std::int32_t ID = 1527666429;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<testVectorStringObject>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testGetDifference final : public Function
{
public:

    testGetDifference();

    static const std::int32_t ID = 1747084069;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testNetwork final : public Function
{
public:

    testNetwork();

    static const std::int32_t ID = -1343998901;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testSquareInt final : public Function
{
public:
    std::int32_t x_;

    testSquareInt();

    explicit testSquareInt(std::int32_t x_);

    static const std::int32_t ID = -60135024;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<testInt>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testUseError final : public Function
{
public:

    testUseError();

    static const std::int32_t ID = 528842186;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<error>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testUseUpdate final : public Function
{
public:

    testUseUpdate();

    static const std::int32_t ID = 717094686;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<Update>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleBasicGroupAdministrators final : public Function
{
public:
    std::int32_t basic_group_id_;
    bool everyone_is_administrator_;

    toggleBasicGroupAdministrators();

    toggleBasicGroupAdministrators(std::int32_t basic_group_id_, bool everyone_is_administrator_);

    static const std::int32_t ID = -591395611;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleChatIsPinned final : public Function
{
public:
    std::int64_t chat_id_;
    bool is_pinned_;

    toggleChatIsPinned();

    toggleChatIsPinned(std::int64_t chat_id_, bool is_pinned_);

    static const std::int32_t ID = -1166802621;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleSupergroupInvites final : public Function
{
public:
    std::int32_t supergroup_id_;
    bool anyone_can_invite_;

    toggleSupergroupInvites();

    toggleSupergroupInvites(std::int32_t supergroup_id_, bool anyone_can_invite_);

    static const std::int32_t ID = -797384141;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleSupergroupIsAllHistoryAvailable final : public Function
{
public:
    std::int32_t supergroup_id_;
    bool is_all_history_available_;

    toggleSupergroupIsAllHistoryAvailable();

    toggleSupergroupIsAllHistoryAvailable(std::int32_t supergroup_id_, bool is_all_history_available_);

    static const std::int32_t ID = 1701526555;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleSupergroupSignMessages final : public Function
{
public:
    std::int32_t supergroup_id_;
    bool sign_messages_;

    toggleSupergroupSignMessages();

    toggleSupergroupSignMessages(std::int32_t supergroup_id_, bool sign_messages_);

    static const std::int32_t ID = -558196581;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class unblockUser final : public Function
{
public:
    std::int32_t user_id_;

    unblockUser();

    explicit unblockUser(std::int32_t user_id_);

    static const std::int32_t ID = -307286367;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class unpinSupergroupMessage final : public Function
{
public:
    std::int32_t supergroup_id_;

    unpinSupergroupMessage();

    explicit unpinSupergroupMessage(std::int32_t supergroup_id_);

    static const std::int32_t ID = -1987029530;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class upgradeBasicGroupChatToSupergroupChat final : public Function
{
public:
    std::int64_t chat_id_;

    upgradeBasicGroupChatToSupergroupChat();

    explicit upgradeBasicGroupChatToSupergroupChat(std::int64_t chat_id_);

    static const std::int32_t ID = 300488122;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class uploadFile final : public Function
{
public:
    object_ptr<InputFile> file_;
    object_ptr<FileType> file_type_;
    std::int32_t priority_;

    uploadFile();

    uploadFile(object_ptr<InputFile> &&file_, object_ptr<FileType> &&file_type_,
               std::int32_t priority_);

    static const std::int32_t ID = -745597786;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<file>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class uploadStickerFile final : public Function
{
public:
    std::int32_t user_id_;
    object_ptr<InputFile> png_sticker_;

    uploadStickerFile();

    uploadStickerFile(std::int32_t user_id_, object_ptr<InputFile> &&png_sticker_);

    static const std::int32_t ID = 1134087551;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<file>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class validateOrderInfo final : public Function
{
public:
    std::int64_t chat_id_;
    std::int64_t message_id_;
    object_ptr<orderInfo> order_info_;
    bool allow_save_;

    validateOrderInfo();

    validateOrderInfo(std::int64_t chat_id_, std::int64_t message_id_,
                      object_ptr<orderInfo> &&order_info_, bool allow_save_);

    static const std::int32_t ID = 9480644;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<validatedOrderInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class viewMessages final : public Function
{
public:
    std::int64_t chat_id_;
    std::vector<std::int64_t> message_ids_;
    bool force_read_;

    viewMessages();

    viewMessages(std::int64_t chat_id_, std::vector<std::int64_t> &&message_ids_, bool force_read_);

    static const std::int32_t ID = -1925784915;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class viewTrendingStickerSets final : public Function
{
public:
    std::vector<std::int64_t> sticker_set_ids_;

    viewTrendingStickerSets();

    explicit viewTrendingStickerSets(std::vector<std::int64_t> &&sticker_set_ids_);

    static const std::int32_t ID = -952416520;
    std::int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

}// namespace tdlibQt
#endif // TDAPI_HPP
