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
    int32_t days_;

    accountTtl();

    explicit accountTtl(int32_t days_);

    static const int32_t ID = 1324495492;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class animation final : public Object
{
public:
    int32_t duration_;
    int32_t width_;
    int32_t height_;
    std::string file_name_;
    std::string mime_type_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> animation_;

    animation();

    animation(int32_t duration_, int32_t width_, int32_t height_,
              std::string const &file_name_, std::string const &mime_type_, object_ptr<photoSize> &&thumbnail_,
              object_ptr<file> &&animation_);

    static const int32_t ID = -1723168340;
    int32_t get_id() const final
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

    static const int32_t ID = 344216945;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class audio final : public Object
{
public:
    int32_t duration_;
    std::string title_;
    std::string performer_;
    std::string file_name_;
    std::string mime_type_;
    object_ptr<photoSize> album_cover_thumbnail_;
    object_ptr<file> audio_;

    audio();

    audio(int32_t duration_, std::string const &title_, std::string const &performer_,
          std::string const &file_name_, std::string const &mime_type_,
          object_ptr<photoSize> &&album_cover_thumbnail_, object_ptr<file> &&audio_);

    static const int32_t ID = 383148432;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authenticationCodeInfo final : public Object
{
public:
    object_ptr<AuthenticationCodeType> type_;
    object_ptr<AuthenticationCodeType> next_type_;
    int32_t timeout_;

    authenticationCodeInfo();

    authenticationCodeInfo(object_ptr<AuthenticationCodeType> &&type_,
                           object_ptr<AuthenticationCodeType> &&next_type_, int32_t timeout_);

    static const int32_t ID = 1083930962;
    int32_t get_id() const final
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
    int32_t length_;

    authenticationCodeTypeTelegramMessage();

    explicit authenticationCodeTypeTelegramMessage(int32_t length_);

    static const int32_t ID = 2079628074;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authenticationCodeTypeSms final : public AuthenticationCodeType
{
public:
    int32_t length_;

    authenticationCodeTypeSms();

    explicit authenticationCodeTypeSms(int32_t length_);

    static const int32_t ID = 962650760;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authenticationCodeTypeCall final : public AuthenticationCodeType
{
public:
    int32_t length_;

    authenticationCodeTypeCall();

    explicit authenticationCodeTypeCall(int32_t length_);

    static const int32_t ID = 1636265063;
    int32_t get_id() const final
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

    static const int32_t ID = 1395882402;
    int32_t get_id() const final
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

    static const int32_t ID = 904720988;
    int32_t get_id() const final
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

    static const int32_t ID = 612103496;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateWaitPhoneNumber final : public AuthorizationState
{
public:

    authorizationStateWaitPhoneNumber();

    static const int32_t ID = 306402531;
    int32_t get_id() const final
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

    static const int32_t ID = -483510157;
    int32_t get_id() const final
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

    static const int32_t ID = 187548796;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateReady final : public AuthorizationState
{
public:

    authorizationStateReady();

    static const int32_t ID = -1834871737;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateLoggingOut final : public AuthorizationState
{
public:

    authorizationStateLoggingOut();

    static const int32_t ID = 154449270;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateClosing final : public AuthorizationState
{
public:

    authorizationStateClosing();

    static const int32_t ID = 445855311;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class authorizationStateClosed final : public AuthorizationState
{
public:

    authorizationStateClosed();

    static const int32_t ID = 1526047584;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class basicGroup final : public Object
{
public:
    int32_t id_;
    int32_t member_count_;
    object_ptr<ChatMemberStatus> status_;
    bool everyone_is_administrator_;
    bool is_active_;
    int32_t upgraded_to_supergroup_id_;

    basicGroup();

    basicGroup(int32_t id_, int32_t member_count_, object_ptr<ChatMemberStatus> &&status_,
               bool everyone_is_administrator_, bool is_active_, int32_t upgraded_to_supergroup_id_);

    static const int32_t ID = 1572712718;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class basicGroupFullInfo final : public Object
{
public:
    int32_t creator_user_id_;
    std::vector<object_ptr<chatMember>> members_;
    std::string invite_link_;

    basicGroupFullInfo();

    basicGroupFullInfo(int32_t creator_user_id_, std::vector<object_ptr<chatMember>> &&members_,
                       std::string const &invite_link_);

    static const int32_t ID = 952266076;
    int32_t get_id() const final
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

    static const int32_t ID = -1032140601;
    int32_t get_id() const final
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

    static const int32_t ID = 1296528907;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class call final : public Object
{
public:
    int32_t id_;
    int32_t user_id_;
    bool is_outgoing_;
    object_ptr<CallState> state_;

    call();

    call(int32_t id_, int32_t user_id_, bool is_outgoing_, object_ptr<CallState> &&state_);

    static const int32_t ID = -1837599107;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callConnection final : public Object
{
public:
    int64_t id_;
    std::string ip_;
    std::string ipv6_;
    int32_t port_;
    std::string peer_tag_;

    callConnection();

    callConnection(int64_t id_, std::string const &ip_, std::string const &ipv6_,
                   int32_t port_, std::string const &peer_tag_);

    static const int32_t ID = 1318542714;
    int32_t get_id() const final
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

    static const int32_t ID = -1258917949;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callDiscardReasonMissed final : public CallDiscardReason
{
public:

    callDiscardReasonMissed();

    static const int32_t ID = 1680358012;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callDiscardReasonDeclined final : public CallDiscardReason
{
public:

    callDiscardReasonDeclined();

    static const int32_t ID = -1729926094;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callDiscardReasonDisconnected final : public CallDiscardReason
{
public:

    callDiscardReasonDisconnected();

    static const int32_t ID = -1342872670;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callDiscardReasonHungUp final : public CallDiscardReason
{
public:

    callDiscardReasonHungUp();

    static const int32_t ID = 438216166;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callId final : public Object
{
public:
    int32_t id_;

    callId();

    explicit callId(int32_t id_);

    static const int32_t ID = 65717769;
    int32_t get_id() const final
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
    int32_t min_layer_;
    int32_t max_layer_;

    callProtocol();

    callProtocol(bool udp_p2p_, bool udp_reflector_, int32_t min_layer_, int32_t max_layer_);

    static const int32_t ID = -1042830667;
    int32_t get_id() const final
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

    static const int32_t ID = 1073048620;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callStateExchangingKeys final : public CallState
{
public:

    callStateExchangingKeys();

    static const int32_t ID = -1848149403;
    int32_t get_id() const final
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

    static const int32_t ID = 1518705438;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class callStateHangingUp final : public CallState
{
public:

    callStateHangingUp();

    static const int32_t ID = -2133790038;
    int32_t get_id() const final
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

    static const int32_t ID = -190853167;
    int32_t get_id() const final
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

    static const int32_t ID = -975215467;
    int32_t get_id() const final
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

    static const int32_t ID = 360867933;
    int32_t get_id() const final
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

    static const int32_t ID = -1977729946;
    int32_t get_id() const final
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

    static const int32_t ID = 1303571512;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chat final : public Object
{
public:
    int64_t id_;
    object_ptr<ChatType> type_;
    std::string title_;
    object_ptr<chatPhoto> photo_;
    object_ptr<message> last_message_;
    int64_t order_;
    bool is_pinned_;
    int32_t unread_count_;
    int64_t last_read_inbox_message_id_;
    int64_t last_read_outbox_message_id_;
    int32_t unread_mention_count_;
    object_ptr<notificationSettings> notification_settings_;
    int64_t reply_markup_message_id_;
    object_ptr<draftMessage> draft_message_;
    std::string client_data_;

    chat();

    chat(int64_t id_, object_ptr<ChatType> &&type_, std::string const &title_,
         object_ptr<chatPhoto> &&photo_, object_ptr<message> &&last_message_, int64_t order_,
         bool is_pinned_, int32_t unread_count_, int64_t last_read_inbox_message_id_,
         int64_t last_read_outbox_message_id_, int32_t unread_mention_count_,
         object_ptr<notificationSettings> &&notification_settings_, int64_t reply_markup_message_id_,
         object_ptr<draftMessage> &&draft_message_, std::string const &client_data_);

    static const int32_t ID = -1350155540;
    int32_t get_id() const final
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

    static const int32_t ID = 380122167;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionRecordingVideo final : public ChatAction
{
public:

    chatActionRecordingVideo();

    static const int32_t ID = 216553362;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingVideo final : public ChatAction
{
public:
    int32_t progress_;

    chatActionUploadingVideo();

    explicit chatActionUploadingVideo(int32_t progress_);

    static const int32_t ID = 1234185270;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionRecordingVoiceNote final : public ChatAction
{
public:

    chatActionRecordingVoiceNote();

    static const int32_t ID = -808850058;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingVoiceNote final : public ChatAction
{
public:
    int32_t progress_;

    chatActionUploadingVoiceNote();

    explicit chatActionUploadingVoiceNote(int32_t progress_);

    static const int32_t ID = -613643666;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingPhoto final : public ChatAction
{
public:
    int32_t progress_;

    chatActionUploadingPhoto();

    explicit chatActionUploadingPhoto(int32_t progress_);

    static const int32_t ID = 654240583;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingDocument final : public ChatAction
{
public:
    int32_t progress_;

    chatActionUploadingDocument();

    explicit chatActionUploadingDocument(int32_t progress_);

    static const int32_t ID = 167884362;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionChoosingLocation final : public ChatAction
{
public:

    chatActionChoosingLocation();

    static const int32_t ID = -2017893596;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionChoosingContact final : public ChatAction
{
public:

    chatActionChoosingContact();

    static const int32_t ID = -1222507496;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionStartPlayingGame final : public ChatAction
{
public:

    chatActionStartPlayingGame();

    static const int32_t ID = -865884164;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionRecordingVideoNote final : public ChatAction
{
public:

    chatActionRecordingVideoNote();

    static const int32_t ID = 16523393;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionUploadingVideoNote final : public ChatAction
{
public:
    int32_t progress_;

    chatActionUploadingVideoNote();

    explicit chatActionUploadingVideoNote(int32_t progress_);

    static const int32_t ID = 1172364918;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatActionCancel final : public ChatAction
{
public:

    chatActionCancel();

    static const int32_t ID = 1160523958;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEvent final : public Object
{
public:
    int64_t id_;
    int32_t date_;
    int32_t user_id_;
    object_ptr<ChatEventAction> action_;

    chatEvent();

    chatEvent(int64_t id_, int32_t date_, int32_t user_id_,
              object_ptr<ChatEventAction> &&action_);

    static const int32_t ID = -609912404;
    int32_t get_id() const final
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

    static const int32_t ID = -430967304;
    int32_t get_id() const final
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

    static const int32_t ID = -892974601;
    int32_t get_id() const final
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

    static const int32_t ID = 438742298;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMessageUnpinned final : public ChatEventAction
{
public:

    chatEventMessageUnpinned();

    static const int32_t ID = 2002594849;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberJoined final : public ChatEventAction
{
public:

    chatEventMemberJoined();

    static const int32_t ID = -235468508;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberLeft final : public ChatEventAction
{
public:

    chatEventMemberLeft();

    static const int32_t ID = -948420593;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberInvited final : public ChatEventAction
{
public:
    int32_t user_id_;
    object_ptr<ChatMemberStatus> status_;

    chatEventMemberInvited();

    chatEventMemberInvited(int32_t user_id_, object_ptr<ChatMemberStatus> &&status_);

    static const int32_t ID = -2093688706;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberPromoted final : public ChatEventAction
{
public:
    int32_t user_id_;
    object_ptr<ChatMemberStatus> old_status_;
    object_ptr<ChatMemberStatus> new_status_;

    chatEventMemberPromoted();

    chatEventMemberPromoted(int32_t user_id_, object_ptr<ChatMemberStatus> &&old_status_,
                            object_ptr<ChatMemberStatus> &&new_status_);

    static const int32_t ID = 1887176186;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventMemberRestricted final : public ChatEventAction
{
public:
    int32_t user_id_;
    object_ptr<ChatMemberStatus> old_status_;
    object_ptr<ChatMemberStatus> new_status_;

    chatEventMemberRestricted();

    chatEventMemberRestricted(int32_t user_id_, object_ptr<ChatMemberStatus> &&old_status_,
                              object_ptr<ChatMemberStatus> &&new_status_);

    static const int32_t ID = 584946294;
    int32_t get_id() const final
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

    static const int32_t ID = 1134103250;
    int32_t get_id() const final
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

    static const int32_t ID = 39112478;
    int32_t get_id() const final
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

    static const int32_t ID = 1728558443;
    int32_t get_id() const final
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

    static const int32_t ID = -811572541;
    int32_t get_id() const final
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

    static const int32_t ID = 568706937;
    int32_t get_id() const final
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

    static const int32_t ID = -1313265634;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatEventStickerSetChanged final : public ChatEventAction
{
public:
    int64_t old_sticker_set_id_;
    int64_t new_sticker_set_id_;

    chatEventStickerSetChanged();

    chatEventStickerSetChanged(int64_t old_sticker_set_id_, int64_t new_sticker_set_id_);

    static const int32_t ID = -1243130481;
    int32_t get_id() const final
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

    static const int32_t ID = -1599063019;
    int32_t get_id() const final
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

    static const int32_t ID = 941939684;
    int32_t get_id() const final
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

    static const int32_t ID = -585329664;
    int32_t get_id() const final
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

    static const int32_t ID = -882072492;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatInviteLinkInfo final : public Object
{
public:
    int64_t chat_id_;
    object_ptr<ChatType> type_;
    std::string title_;
    object_ptr<chatPhoto> photo_;
    int32_t member_count_;
    std::vector<int32_t> member_user_ids_;
    bool is_public_;

    chatInviteLinkInfo();

    chatInviteLinkInfo(int64_t chat_id_, object_ptr<ChatType> &&type_, std::string const &title_,
                       object_ptr<chatPhoto> &&photo_, int32_t member_count_,
                       std::vector<int32_t> &&member_user_ids_, bool is_public_);

    static const int32_t ID = -323394424;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMember final : public Object
{
public:
    int32_t user_id_;
    int32_t inviter_user_id_;
    int32_t joined_chat_date_;
    object_ptr<ChatMemberStatus> status_;
    object_ptr<botInfo> bot_info_;

    chatMember();

    chatMember(int32_t user_id_, int32_t inviter_user_id_, int32_t joined_chat_date_,
               object_ptr<ChatMemberStatus> &&status_, object_ptr<botInfo> &&bot_info_);

    static const int32_t ID = -806137076;
    int32_t get_id() const final
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

    static const int32_t ID = 1756320508;
    int32_t get_id() const final
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

    static const int32_t ID = 45106688;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusMember final : public ChatMemberStatus
{
public:

    chatMemberStatusMember();

    static const int32_t ID = 844723285;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusRestricted final : public ChatMemberStatus
{
public:
    bool is_member_;
    int32_t restricted_until_date_;
    bool can_send_messages_;
    bool can_send_media_messages_;
    bool can_send_other_messages_;
    bool can_add_web_page_previews_;

    chatMemberStatusRestricted();

    chatMemberStatusRestricted(bool is_member_, int32_t restricted_until_date_,
                               bool can_send_messages_, bool can_send_media_messages_, bool can_send_other_messages_,
                               bool can_add_web_page_previews_);

    static const int32_t ID = 2068116214;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusLeft final : public ChatMemberStatus
{
public:

    chatMemberStatusLeft();

    static const int32_t ID = -5815259;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMemberStatusBanned final : public ChatMemberStatus
{
public:
    int32_t banned_until_date_;

    chatMemberStatusBanned();

    explicit chatMemberStatusBanned(int32_t banned_until_date_);

    static const int32_t ID = -1653518666;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatMembers final : public Object
{
public:
    int32_t total_count_;
    std::vector<object_ptr<chatMember>> members_;

    chatMembers();

    chatMembers(int32_t total_count_, std::vector<object_ptr<chatMember>> &&members_);

    static const int32_t ID = -497558622;
    int32_t get_id() const final
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

    static const int32_t ID = -217062456;
    int32_t get_id() const final
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

    static const int32_t ID = -510848863;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatReportReasonViolence final : public ChatReportReason
{
public:

    chatReportReasonViolence();

    static const int32_t ID = -1330235395;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatReportReasonPornography final : public ChatReportReason
{
public:

    chatReportReasonPornography();

    static const int32_t ID = 722614385;
    int32_t get_id() const final
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

    static const int32_t ID = 544575454;
    int32_t get_id() const final
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

    static const int32_t ID = -1919240972;
    int32_t get_id() const final
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
    int32_t user_id_;

    chatTypePrivate();

    explicit chatTypePrivate(int32_t user_id_);

    static const int32_t ID = 1700720838;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatTypeBasicGroup final : public ChatType
{
public:
    int32_t basic_group_id_;

    chatTypeBasicGroup();

    explicit chatTypeBasicGroup(int32_t basic_group_id_);

    static const int32_t ID = 21815278;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatTypeSupergroup final : public ChatType
{
public:
    int32_t supergroup_id_;
    bool is_channel_;

    chatTypeSupergroup();

    chatTypeSupergroup(int32_t supergroup_id_, bool is_channel_);

    static const int32_t ID = 955152366;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chatTypeSecret final : public ChatType
{
public:
    int32_t secret_chat_id_;
    int32_t user_id_;

    chatTypeSecret();

    chatTypeSecret(int32_t secret_chat_id_, int32_t user_id_);

    static const int32_t ID = 136722563;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class chats final : public Object
{
public:
    std::vector<int64_t> chat_ids_;

    chats();

    explicit chats(std::vector<int64_t> &&chat_ids_);

    static const int32_t ID = -1687756019;
    int32_t get_id() const final
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

    static const int32_t ID = 1695405912;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectionStateConnectingToProxy final : public ConnectionState
{
public:

    connectionStateConnectingToProxy();

    static const int32_t ID = -93187239;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectionStateConnecting final : public ConnectionState
{
public:

    connectionStateConnecting();

    static const int32_t ID = -1298400670;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectionStateUpdating final : public ConnectionState
{
public:

    connectionStateUpdating();

    static const int32_t ID = -188104009;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class connectionStateReady final : public ConnectionState
{
public:

    connectionStateReady();

    static const int32_t ID = 48608492;
    int32_t get_id() const final
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
    int32_t user_id_;

    contact();

    contact(std::string const &phone_number_, std::string const &first_name_,
            std::string const &last_name_, int32_t user_id_);

    static const int32_t ID = -2035981269;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class count final : public Object
{
public:
    int32_t count_;

    count();

    explicit count(int32_t count_);

    static const int32_t ID = 1295577348;
    int32_t get_id() const final
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

    static const int32_t ID = -2009960452;
    int32_t get_id() const final
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

    static const int32_t ID = 1092220225;
    int32_t get_id() const final
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

    static const int32_t ID = 387541955;
    int32_t get_id() const final
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

    static const int32_t ID = -327676505;
    int32_t get_id() const final
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

    static const int32_t ID = -1410514289;
    int32_t get_id() const final
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

    static const int32_t ID = 1224269900;
    int32_t get_id() const final
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

    static const int32_t ID = -785603759;
    int32_t get_id() const final
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

    static const int32_t ID = -1694507273;
    int32_t get_id() const final
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

    static const int32_t ID = 49584736;
    int32_t get_id() const final
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

    static const int32_t ID = 1782320422;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deviceTokenBlackberryPush final : public DeviceToken
{
public:
    std::string token_;

    deviceTokenBlackberryPush();

    explicit deviceTokenBlackberryPush(std::string const &token_);

    static const int32_t ID = 1159513083;
    int32_t get_id() const final
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

    static const int32_t ID = -1359947213;
    int32_t get_id() const final
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

    static const int32_t ID = -736037786;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class draftMessage final : public Object
{
public:
    int64_t reply_to_message_id_;
    object_ptr<InputMessageContent> input_message_text_;

    draftMessage();

    draftMessage(int64_t reply_to_message_id_,
                 object_ptr<InputMessageContent> &&input_message_text_);

    static const int32_t ID = 1902914742;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class error final : public Object
{
public:
    int32_t code_;
    std::string message_;

    error();

    error(int32_t code_, std::string const &message_);

    static const int32_t ID = -1679978726;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class file final : public Object
{
public:
    int32_t id_;
    int32_t size_;
    int32_t expected_size_;
    object_ptr<localFile> local_;
    object_ptr<remoteFile> remote_;

    file();

    file(int32_t id_, int32_t size_, int32_t expected_size_,
         object_ptr<localFile> &&local_, object_ptr<remoteFile> &&remote_);

    static const int32_t ID = 766337656;
    int32_t get_id() const final
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

    static const int32_t ID = 2003009189;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeAnimation final : public FileType
{
public:

    fileTypeAnimation();

    static const int32_t ID = -290816582;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeAudio final : public FileType
{
public:

    fileTypeAudio();

    static const int32_t ID = -709112160;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeDocument final : public FileType
{
public:

    fileTypeDocument();

    static const int32_t ID = -564722929;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypePhoto final : public FileType
{
public:

    fileTypePhoto();

    static const int32_t ID = -1718914651;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeProfilePhoto final : public FileType
{
public:

    fileTypeProfilePhoto();

    static const int32_t ID = 1795089315;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeSecret final : public FileType
{
public:

    fileTypeSecret();

    static const int32_t ID = -1871899401;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeSticker final : public FileType
{
public:

    fileTypeSticker();

    static const int32_t ID = 475233385;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeThumbnail final : public FileType
{
public:

    fileTypeThumbnail();

    static const int32_t ID = -12443298;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeUnknown final : public FileType
{
public:

    fileTypeUnknown();

    static const int32_t ID = -2011566768;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeVideo final : public FileType
{
public:

    fileTypeVideo();

    static const int32_t ID = 1430816539;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeVideoNote final : public FileType
{
public:

    fileTypeVideoNote();

    static const int32_t ID = -518412385;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeVoiceNote final : public FileType
{
public:

    fileTypeVoiceNote();

    static const int32_t ID = -588681661;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeWallpaper final : public FileType
{
public:

    fileTypeWallpaper();

    static const int32_t ID = 1854930076;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class fileTypeSecretThumbnail final : public FileType
{
public:

    fileTypeSecretThumbnail();

    static const int32_t ID = -1401326026;
    int32_t get_id() const final
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

    static const int32_t ID = -252624564;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class foundMessages final : public Object
{
public:
    std::vector<object_ptr<message>> messages_;
    int64_t next_from_search_id_;

    foundMessages();

    foundMessages(std::vector<object_ptr<message>> &&messages_, int64_t next_from_search_id_);

    static const int32_t ID = 2135623881;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class game final : public Object
{
public:
    int64_t id_;
    std::string short_name_;
    std::string title_;
    object_ptr<formattedText> text_;
    std::string description_;
    object_ptr<photo> photo_;
    object_ptr<animation> animation_;

    game();

    game(int64_t id_, std::string const &short_name_, std::string const &title_,
         object_ptr<formattedText> &&text_, std::string const &description_, object_ptr<photo> &&photo_,
         object_ptr<animation> &&animation_);

    static const int32_t ID = -1565597752;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class gameHighScore final : public Object
{
public:
    int32_t position_;
    int32_t user_id_;
    int32_t score_;

    gameHighScore();

    gameHighScore(int32_t position_, int32_t user_id_, int32_t score_);

    static const int32_t ID = -30778358;
    int32_t get_id() const final
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

    static const int32_t ID = -725770727;
    int32_t get_id() const final
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

    static const int32_t ID = 676798885;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class importedContacts final : public Object
{
public:
    std::vector<int32_t> user_ids_;
    std::vector<int32_t> importer_count_;

    importedContacts();

    importedContacts(std::vector<int32_t> &&user_ids_,
                     std::vector<int32_t> &&importer_count_);

    static const int32_t ID = -741685354;
    int32_t get_id() const final
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

    static const int32_t ID = -372105704;
    int32_t get_id() const final
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

    static const int32_t ID = 1130741420;
    int32_t get_id() const final
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

    static const int32_t ID = -1127515139;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineKeyboardButtonTypeCallbackGame final : public InlineKeyboardButtonType
{
public:

    inlineKeyboardButtonTypeCallbackGame();

    static const int32_t ID = -383429528;
    int32_t get_id() const final
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

    static const int32_t ID = -2035563307;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineKeyboardButtonTypeBuy final : public InlineKeyboardButtonType
{
public:

    inlineKeyboardButtonTypeBuy();

    static const int32_t ID = 1360739440;
    int32_t get_id() const final
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

    static const int32_t ID = -518366710;
    int32_t get_id() const final
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

    static const int32_t ID = 410081985;
    int32_t get_id() const final
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

    static const int32_t ID = -158305341;
    int32_t get_id() const final
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

    static const int32_t ID = -1592932211;
    int32_t get_id() const final
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

    static const int32_t ID = 1706916987;
    int32_t get_id() const final
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

    static const int32_t ID = 2009984267;
    int32_t get_id() const final
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

    static const int32_t ID = 842650360;
    int32_t get_id() const final
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

    static const int32_t ID = -1491268539;
    int32_t get_id() const final
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

    static const int32_t ID = 1848319440;
    int32_t get_id() const final
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

    static const int32_t ID = -1848224245;
    int32_t get_id() const final
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

    static const int32_t ID = -1373158683;
    int32_t get_id() const final
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

    static const int32_t ID = -1897393105;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inlineQueryResults final : public Object
{
public:
    int64_t inline_query_id_;
    std::string next_offset_;
    std::vector<object_ptr<InlineQueryResult>> results_;
    std::string switch_pm_text_;
    std::string switch_pm_parameter_;

    inlineQueryResults();

    inlineQueryResults(int64_t inline_query_id_, std::string const &next_offset_,
                       std::vector<object_ptr<InlineQueryResult>> &&results_, std::string const &switch_pm_text_,
                       std::string const &switch_pm_parameter_);

    static const int32_t ID = 1000709656;
    int32_t get_id() const final
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

    static const int32_t ID = -2034385364;
    int32_t get_id() const final
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

    static const int32_t ID = -829689558;
    int32_t get_id() const final
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

    static const int32_t ID = 1979566832;
    int32_t get_id() const final
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

    static const int32_t ID = -1246570799;
    int32_t get_id() const final
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
    int32_t id_;

    inputFileId();

    explicit inputFileId(int32_t id_);

    static const int32_t ID = 1788906253;
    int32_t get_id() const final
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

    static const int32_t ID = -107574466;
    int32_t get_id() const final
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

    static const int32_t ID = 2056030919;
    int32_t get_id() const final
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
    int32_t expected_size_;

    inputFileGenerated();

    inputFileGenerated(std::string const &original_path_, std::string const &conversion_,
                       int32_t expected_size_);

    static const int32_t ID = -1781351885;
    int32_t get_id() const final
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
    int32_t gif_duration_;
    int32_t gif_width_;
    int32_t gif_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultAnimatedGif();

    inputInlineQueryResultAnimatedGif(std::string const &id_, std::string const &title_,
                                      std::string const &thumbnail_url_, std::string const &gif_url_, int32_t gif_duration_,
                                      int32_t gif_width_, int32_t gif_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                      object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = -891474894;
    int32_t get_id() const final
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
    int32_t mpeg4_duration_;
    int32_t mpeg4_width_;
    int32_t mpeg4_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultAnimatedMpeg4();

    inputInlineQueryResultAnimatedMpeg4(std::string const &id_, std::string const &title_,
                                        std::string const &thumbnail_url_, std::string const &mpeg4_url_, int32_t mpeg4_duration_,
                                        int32_t mpeg4_width_, int32_t mpeg4_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                        object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = -1629529888;
    int32_t get_id() const final
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
    int32_t thumbnail_width_;
    int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultArticle();

    inputInlineQueryResultArticle(std::string const &id_, std::string const &url_, bool hide_url_,
                                  std::string const &title_, std::string const &description_, std::string const &thumbnail_url_,
                                  int32_t thumbnail_width_, int32_t thumbnail_height_,
                                  object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 1973670156;
    int32_t get_id() const final
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
    int32_t audio_duration_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultAudio();

    inputInlineQueryResultAudio(std::string const &id_, std::string const &title_,
                                std::string const &performer_, std::string const &audio_url_, int32_t audio_duration_,
                                object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 1260139988;
    int32_t get_id() const final
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
    int32_t thumbnail_width_;
    int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultContact();

    inputInlineQueryResultContact(std::string const &id_, object_ptr<contact> &&contact_,
                                  std::string const &thumbnail_url_, int32_t thumbnail_width_, int32_t thumbnail_height_,
                                  object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 1846064594;
    int32_t get_id() const final
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
    int32_t thumbnail_width_;
    int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultDocument();

    inputInlineQueryResultDocument(std::string const &id_, std::string const &title_,
                                   std::string const &description_, std::string const &document_url_, std::string const &mime_type_,
                                   std::string const &thumbnail_url_, int32_t thumbnail_width_, int32_t thumbnail_height_,
                                   object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 578801869;
    int32_t get_id() const final
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

    static const int32_t ID = 966074327;
    int32_t get_id() const final
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
    int32_t live_period_;
    std::string title_;
    std::string thumbnail_url_;
    int32_t thumbnail_width_;
    int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultLocation();

    inputInlineQueryResultLocation(std::string const &id_, object_ptr<location> &&location_,
                                   int32_t live_period_, std::string const &title_, std::string const &thumbnail_url_,
                                   int32_t thumbnail_width_, int32_t thumbnail_height_,
                                   object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = -1887650218;
    int32_t get_id() const final
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
    int32_t photo_width_;
    int32_t photo_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultPhoto();

    inputInlineQueryResultPhoto(std::string const &id_, std::string const &title_,
                                std::string const &description_, std::string const &thumbnail_url_, std::string const &photo_url_,
                                int32_t photo_width_, int32_t photo_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = -1123338721;
    int32_t get_id() const final
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
    int32_t sticker_width_;
    int32_t sticker_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultSticker();

    inputInlineQueryResultSticker(std::string const &id_, std::string const &thumbnail_url_,
                                  std::string const &sticker_url_, int32_t sticker_width_, int32_t sticker_height_,
                                  object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 274007129;
    int32_t get_id() const final
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
    int32_t thumbnail_width_;
    int32_t thumbnail_height_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultVenue();

    inputInlineQueryResultVenue(std::string const &id_, object_ptr<venue> &&venue_,
                                std::string const &thumbnail_url_, int32_t thumbnail_width_, int32_t thumbnail_height_,
                                object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 541704509;
    int32_t get_id() const final
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
    int32_t video_width_;
    int32_t video_height_;
    int32_t video_duration_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultVideo();

    inputInlineQueryResultVideo(std::string const &id_, std::string const &title_,
                                std::string const &description_, std::string const &thumbnail_url_, std::string const &video_url_,
                                std::string const &mime_type_, int32_t video_width_, int32_t video_height_,
                                int32_t video_duration_, object_ptr<ReplyMarkup> &&reply_markup_,
                                object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 1724073191;
    int32_t get_id() const final
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
    int32_t voice_note_duration_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    inputInlineQueryResultVoiceNote();

    inputInlineQueryResultVoiceNote(std::string const &id_, std::string const &title_,
                                    std::string const &voice_note_url_, int32_t voice_note_duration_,
                                    object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = -1790072503;
    int32_t get_id() const final
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

    static const int32_t ID = 247050392;
    int32_t get_id() const final
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
    int32_t duration_;
    int32_t width_;
    int32_t height_;
    object_ptr<formattedText> caption_;

    inputMessageAnimation();

    inputMessageAnimation(object_ptr<InputFile> &&animation_, object_ptr<inputThumbnail> &&thumbnail_,
                          int32_t duration_, int32_t width_, int32_t height_,
                          object_ptr<formattedText> &&caption_);

    static const int32_t ID = 926542724;
    int32_t get_id() const final
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
    int32_t duration_;
    std::string title_;
    std::string performer_;
    object_ptr<formattedText> caption_;

    inputMessageAudio();

    inputMessageAudio(object_ptr<InputFile> &&audio_,
                      object_ptr<inputThumbnail> &&album_cover_thumbnail_, int32_t duration_,
                      std::string const &title_, std::string const &performer_, object_ptr<formattedText> &&caption_);

    static const int32_t ID = -626786126;
    int32_t get_id() const final
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

    static const int32_t ID = 937970604;
    int32_t get_id() const final
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
    std::vector<int32_t> added_sticker_file_ids_;
    int32_t width_;
    int32_t height_;
    object_ptr<formattedText> caption_;
    int32_t ttl_;

    inputMessagePhoto();

    inputMessagePhoto(object_ptr<InputFile> &&photo_, object_ptr<inputThumbnail> &&thumbnail_,
                      std::vector<int32_t> &&added_sticker_file_ids_, int32_t width_, int32_t height_,
                      object_ptr<formattedText> &&caption_, int32_t ttl_);

    static const int32_t ID = 1648801584;
    int32_t get_id() const final
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
    int32_t width_;
    int32_t height_;

    inputMessageSticker();

    inputMessageSticker(object_ptr<InputFile> &&sticker_, object_ptr<inputThumbnail> &&thumbnail_,
                        int32_t width_, int32_t height_);

    static const int32_t ID = 740776325;
    int32_t get_id() const final
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
    std::vector<int32_t> added_sticker_file_ids_;
    int32_t duration_;
    int32_t width_;
    int32_t height_;
    object_ptr<formattedText> caption_;
    int32_t ttl_;

    inputMessageVideo();

    inputMessageVideo(object_ptr<InputFile> &&video_, object_ptr<inputThumbnail> &&thumbnail_,
                      std::vector<int32_t> &&added_sticker_file_ids_, int32_t duration_, int32_t width_,
                      int32_t height_, object_ptr<formattedText> &&caption_, int32_t ttl_);

    static const int32_t ID = 502341237;
    int32_t get_id() const final
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
    int32_t duration_;
    int32_t length_;

    inputMessageVideoNote();

    inputMessageVideoNote(object_ptr<InputFile> &&video_note_, object_ptr<inputThumbnail> &&thumbnail_,
                          int32_t duration_, int32_t length_);

    static const int32_t ID = 279108859;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageVoiceNote final : public InputMessageContent
{
public:
    object_ptr<InputFile> voice_note_;
    int32_t duration_;
    std::string waveform_;
    object_ptr<formattedText> caption_;

    inputMessageVoiceNote();

    inputMessageVoiceNote(object_ptr<InputFile> &&voice_note_, int32_t duration_,
                          std::string const &waveform_, object_ptr<formattedText> &&caption_);

    static const int32_t ID = 2136519657;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageLocation final : public InputMessageContent
{
public:
    object_ptr<location> location_;
    int32_t live_period_;

    inputMessageLocation();

    inputMessageLocation(object_ptr<location> &&location_, int32_t live_period_);

    static const int32_t ID = -1624179655;
    int32_t get_id() const final
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

    static const int32_t ID = 1447926269;
    int32_t get_id() const final
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

    static const int32_t ID = -982446849;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageGame final : public InputMessageContent
{
public:
    int32_t bot_user_id_;
    std::string game_short_name_;

    inputMessageGame();

    inputMessageGame(int32_t bot_user_id_, std::string const &game_short_name_);

    static const int32_t ID = -1728000914;
    int32_t get_id() const final
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
    int32_t photo_size_;
    int32_t photo_width_;
    int32_t photo_height_;
    std::string payload_;
    std::string provider_token_;
    std::string provider_data_;
    std::string start_parameter_;

    inputMessageInvoice();

    inputMessageInvoice(object_ptr<invoice> &&invoice_, std::string const &title_,
                        std::string const &description_, std::string const &photo_url_, int32_t photo_size_,
                        int32_t photo_width_, int32_t photo_height_, std::string const &payload_,
                        std::string const &provider_token_, std::string const &provider_data_,
                        std::string const &start_parameter_);

    static const int32_t ID = 1038812175;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputMessageForwarded final : public InputMessageContent
{
public:
    int64_t from_chat_id_;
    int64_t message_id_;
    bool in_game_share_;

    inputMessageForwarded();

    inputMessageForwarded(int64_t from_chat_id_, int64_t message_id_, bool in_game_share_);

    static const int32_t ID = 1561363198;
    int32_t get_id() const final
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

    static const int32_t ID = -1998602205;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class inputThumbnail final : public Object
{
public:
    object_ptr<InputFile> thumbnail_;
    int32_t width_;
    int32_t height_;

    inputThumbnail();

    inputThumbnail(object_ptr<InputFile> &&thumbnail_, int32_t width_, int32_t height_);

    static const int32_t ID = 1582387236;
    int32_t get_id() const final
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

    static const int32_t ID = -368451690;
    int32_t get_id() const final
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

    static const int32_t ID = -2069836172;
    int32_t get_id() const final
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

    static const int32_t ID = -1773037256;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class keyboardButtonTypeRequestPhoneNumber final : public KeyboardButtonType
{
public:

    keyboardButtonTypeRequestPhoneNumber();

    static const int32_t ID = -1529235527;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class keyboardButtonTypeRequestLocation final : public KeyboardButtonType
{
public:

    keyboardButtonTypeRequestLocation();

    static const int32_t ID = -125661955;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class labeledPricePart final : public Object
{
public:
    std::string label_;
    int64_t amount_;

    labeledPricePart();

    labeledPricePart(std::string const &label_, int64_t amount_);

    static const int32_t ID = 552789798;
    int32_t get_id() const final
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

    static const int32_t ID = 951430287;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class linkStateKnowsPhoneNumber final : public LinkState
{
public:

    linkStateKnowsPhoneNumber();

    static const int32_t ID = 380898199;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class linkStateIsContact final : public LinkState
{
public:

    linkStateIsContact();

    static const int32_t ID = -1000499465;
    int32_t get_id() const final
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
    int32_t downloaded_prefix_size_;
    int32_t downloaded_size_;

    localFile();

    localFile(std::string const &path_, bool can_be_downloaded_, bool can_be_deleted_,
              bool is_downloading_active_, bool is_downloading_completed_, int32_t downloaded_prefix_size_,
              int32_t downloaded_size_);

    static const int32_t ID = 847939462;
    int32_t get_id() const final
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

    static const int32_t ID = 749028016;
    int32_t get_id() const final
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

    static const int32_t ID = 1027512005;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class maskPointEyes final : public MaskPoint
{
public:

    maskPointEyes();

    static const int32_t ID = 1748310861;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class maskPointMouth final : public MaskPoint
{
public:

    maskPointMouth();

    static const int32_t ID = 411773406;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class maskPointChin final : public MaskPoint
{
public:

    maskPointChin();

    static const int32_t ID = 534995335;
    int32_t get_id() const final
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

    static const int32_t ID = -2097433026;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class message final : public Object
{
public:
    int64_t id_;
    int32_t sender_user_id_;
    int64_t chat_id_;
    object_ptr<MessageSendingState> sending_state_;
    bool is_outgoing_;
    bool can_be_edited_;
    bool can_be_forwarded_;
    bool can_be_deleted_only_for_self_;
    bool can_be_deleted_for_all_users_;
    bool is_channel_post_;
    bool contains_unread_mention_;
    int32_t date_;
    int32_t edit_date_;
    object_ptr<MessageForwardInfo> forward_info_;
    int64_t reply_to_message_id_;
    int32_t ttl_;
    double ttl_expires_in_;
    int32_t via_bot_user_id_;
    std::string author_signature_;
    int32_t views_;
    int64_t media_album_id_;
    object_ptr<MessageContent> content_;
    object_ptr<ReplyMarkup> reply_markup_;

    message();

    message(int64_t id_, int32_t sender_user_id_, int64_t chat_id_,
            object_ptr<MessageSendingState> &&sending_state_, bool is_outgoing_, bool can_be_edited_,
            bool can_be_forwarded_, bool can_be_deleted_only_for_self_, bool can_be_deleted_for_all_users_,
            bool is_channel_post_, bool contains_unread_mention_, int32_t date_, int32_t edit_date_,
            object_ptr<MessageForwardInfo> &&forward_info_, int64_t reply_to_message_id_,
            int32_t ttl_, double ttl_expires_in_, int32_t via_bot_user_id_,
            std::string const &author_signature_, int32_t views_, int64_t media_album_id_,
            object_ptr<MessageContent> &&content_, object_ptr<ReplyMarkup> &&reply_markup_);

    static const int32_t ID = -675737627;
    int32_t get_id() const final
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

    static const int32_t ID = 1989037971;
    int32_t get_id() const final
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

    messageAnimation();

    messageAnimation(object_ptr<animation> &&animation_, object_ptr<formattedText> &&caption_);

    static const int32_t ID = 251458960;
    int32_t get_id() const final
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

    static const int32_t ID = 276722716;
    int32_t get_id() const final
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

    static const int32_t ID = 596945783;
    int32_t get_id() const final
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

    messagePhoto();

    messagePhoto(object_ptr<photo> &&photo_, object_ptr<formattedText> &&caption_);

    static const int32_t ID = 1740718156;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageExpiredPhoto final : public MessageContent
{
public:

    messageExpiredPhoto();

    static const int32_t ID = -1404641801;
    int32_t get_id() const final
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

    static const int32_t ID = 1779022878;
    int32_t get_id() const final
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

    messageVideo();

    messageVideo(object_ptr<video> &&video_, object_ptr<formattedText> &&caption_);

    static const int32_t ID = -668896935;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageExpiredVideo final : public MessageContent
{
public:

    messageExpiredVideo();

    static const int32_t ID = -1212209981;
    int32_t get_id() const final
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

    messageVideoNote();

    messageVideoNote(object_ptr<videoNote> &&video_note_, bool is_viewed_);

    static const int32_t ID = 283807685;
    int32_t get_id() const final
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

    static const int32_t ID = 527777781;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageLocation final : public MessageContent
{
public:
    object_ptr<location> location_;
    int32_t live_period_;

    messageLocation();

    messageLocation(object_ptr<location> &&location_, int32_t live_period_);

    static const int32_t ID = -1537763861;
    int32_t get_id() const final
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

    static const int32_t ID = -2146492043;
    int32_t get_id() const final
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

    static const int32_t ID = -512684966;
    int32_t get_id() const final
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

    static const int32_t ID = -69441162;
    int32_t get_id() const final
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
    int64_t total_amount_;
    std::string start_parameter_;
    bool is_test_;
    bool need_shipping_address_;
    int64_t receipt_message_id_;

    messageInvoice();

    messageInvoice(std::string const &title_, std::string const &description_,
                   object_ptr<photo> &&photo_, std::string const &currency_, int64_t total_amount_,
                   std::string const &start_parameter_, bool is_test_, bool need_shipping_address_,
                   int64_t receipt_message_id_);

    static const int32_t ID = -1916671476;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageCall final : public MessageContent
{
public:
    object_ptr<CallDiscardReason> discard_reason_;
    int32_t duration_;

    messageCall();

    messageCall(object_ptr<CallDiscardReason> &&discard_reason_, int32_t duration_);

    static const int32_t ID = 366512596;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageBasicGroupChatCreate final : public MessageContent
{
public:
    std::string title_;
    std::vector<int32_t> member_user_ids_;

    messageBasicGroupChatCreate();

    messageBasicGroupChatCreate(std::string const &title_,
                                std::vector<int32_t> &&member_user_ids_);

    static const int32_t ID = 1575377646;
    int32_t get_id() const final
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

    static const int32_t ID = -434325733;
    int32_t get_id() const final
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

    static const int32_t ID = 748272449;
    int32_t get_id() const final
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

    static const int32_t ID = 319630249;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatDeletePhoto final : public MessageContent
{
public:

    messageChatDeletePhoto();

    static const int32_t ID = -184374809;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatAddMembers final : public MessageContent
{
public:
    std::vector<int32_t> member_user_ids_;

    messageChatAddMembers();

    explicit messageChatAddMembers(std::vector<int32_t> &&member_user_ids_);

    static const int32_t ID = 401228326;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatJoinByLink final : public MessageContent
{
public:

    messageChatJoinByLink();

    static const int32_t ID = 1846493311;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatDeleteMember final : public MessageContent
{
public:
    int32_t user_id_;

    messageChatDeleteMember();

    explicit messageChatDeleteMember(int32_t user_id_);

    static const int32_t ID = 1164414043;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatUpgradeTo final : public MessageContent
{
public:
    int32_t supergroup_id_;

    messageChatUpgradeTo();

    explicit messageChatUpgradeTo(int32_t supergroup_id_);

    static const int32_t ID = 1957816681;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatUpgradeFrom final : public MessageContent
{
public:
    std::string title_;
    int32_t basic_group_id_;

    messageChatUpgradeFrom();

    messageChatUpgradeFrom(std::string const &title_, int32_t basic_group_id_);

    static const int32_t ID = 1642272558;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messagePinMessage final : public MessageContent
{
public:
    int64_t message_id_;

    messagePinMessage();

    explicit messagePinMessage(int64_t message_id_);

    static const int32_t ID = 953503801;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageScreenshotTaken final : public MessageContent
{
public:

    messageScreenshotTaken();

    static const int32_t ID = -1564971605;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageChatSetTtl final : public MessageContent
{
public:
    int32_t ttl_;

    messageChatSetTtl();

    explicit messageChatSetTtl(int32_t ttl_);

    static const int32_t ID = 1810060209;
    int32_t get_id() const final
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

    static const int32_t ID = 1435879282;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageGameScore final : public MessageContent
{
public:
    int64_t game_message_id_;
    int64_t game_id_;
    int32_t score_;

    messageGameScore();

    messageGameScore(int64_t game_message_id_, int64_t game_id_, int32_t score_);

    static const int32_t ID = 1344904575;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messagePaymentSuccessful final : public MessageContent
{
public:
    int64_t invoice_message_id_;
    std::string currency_;
    int64_t total_amount_;

    messagePaymentSuccessful();

    messagePaymentSuccessful(int64_t invoice_message_id_, std::string const &currency_,
                             int64_t total_amount_);

    static const int32_t ID = -595962993;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messagePaymentSuccessfulBot final : public MessageContent
{
public:
    int64_t invoice_message_id_;
    std::string currency_;
    int64_t total_amount_;
    std::string invoice_payload_;
    std::string shipping_option_id_;
    object_ptr<orderInfo> order_info_;
    std::string telegram_payment_charge_id_;
    std::string provider_payment_charge_id_;

    messagePaymentSuccessfulBot();

    messagePaymentSuccessfulBot(int64_t invoice_message_id_, std::string const &currency_,
                                int64_t total_amount_, std::string const &invoice_payload_,
                                std::string const &shipping_option_id_, object_ptr<orderInfo> &&order_info_,
                                std::string const &telegram_payment_charge_id_, std::string const &provider_payment_charge_id_);

    static const int32_t ID = -412310696;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageContactRegistered final : public MessageContent
{
public:

    messageContactRegistered();

    static const int32_t ID = -1502020353;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageUnsupported final : public MessageContent
{
public:

    messageUnsupported();

    static const int32_t ID = -1816726139;
    int32_t get_id() const final
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
    int32_t sender_user_id_;
    int32_t date_;
    int64_t forwarded_from_chat_id_;
    int64_t forwarded_from_message_id_;

    messageForwardedFromUser();

    messageForwardedFromUser(int32_t sender_user_id_, int32_t date_,
                             int64_t forwarded_from_chat_id_, int64_t forwarded_from_message_id_);

    static const int32_t ID = 1004332765;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageForwardedPost final : public MessageForwardInfo
{
public:
    int64_t chat_id_;
    std::string author_signature_;
    int32_t date_;
    int64_t message_id_;
    int64_t forwarded_from_chat_id_;
    int64_t forwarded_from_message_id_;

    messageForwardedPost();

    messageForwardedPost(int64_t chat_id_, std::string const &author_signature_,
                         int32_t date_, int64_t message_id_, int64_t forwarded_from_chat_id_,
                         int64_t forwarded_from_message_id_);

    static const int32_t ID = -244050875;
    int32_t get_id() const final
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

    static const int32_t ID = -1381803582;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messageSendingStateFailed final : public MessageSendingState
{
public:

    messageSendingStateFailed();

    static const int32_t ID = -546610323;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class messages final : public Object
{
public:
    int32_t total_count_;
    std::vector<object_ptr<message>> messages_;

    messages();

    messages(int32_t total_count_, std::vector<object_ptr<message>> &&messages_);

    static const int32_t ID = -16498159;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkStatistics final : public Object
{
public:
    int32_t since_date_;
    std::vector<object_ptr<NetworkStatisticsEntry>> entries_;

    networkStatistics();

    networkStatistics(int32_t since_date_,
                      std::vector<object_ptr<NetworkStatisticsEntry>> &&entries_);

    static const int32_t ID = 1615554212;
    int32_t get_id() const final
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
    int64_t sent_bytes_;
    int64_t received_bytes_;

    networkStatisticsEntryFile();

    networkStatisticsEntryFile(object_ptr<FileType> &&file_type_,
                               object_ptr<NetworkType> &&network_type_, int64_t sent_bytes_, int64_t received_bytes_);

    static const int32_t ID = 188452706;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkStatisticsEntryCall final : public NetworkStatisticsEntry
{
public:
    object_ptr<NetworkType> network_type_;
    int64_t sent_bytes_;
    int64_t received_bytes_;
    double duration_;

    networkStatisticsEntryCall();

    networkStatisticsEntryCall(object_ptr<NetworkType> &&network_type_, int64_t sent_bytes_,
                               int64_t received_bytes_, double duration_);

    static const int32_t ID = 737000365;
    int32_t get_id() const final
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

    static const int32_t ID = -1971691759;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkTypeMobile final : public NetworkType
{
public:

    networkTypeMobile();

    static const int32_t ID = 819228239;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkTypeMobileRoaming final : public NetworkType
{
public:

    networkTypeMobileRoaming();

    static const int32_t ID = -1435199760;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkTypeWiFi final : public NetworkType
{
public:

    networkTypeWiFi();

    static const int32_t ID = -633872070;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class networkTypeOther final : public NetworkType
{
public:

    networkTypeOther();

    static const int32_t ID = 1942128539;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class notificationSettings final : public Object
{
public:
    int32_t mute_for_;
    std::string sound_;
    bool show_preview_;

    notificationSettings();

    notificationSettings(int32_t mute_for_, std::string const &sound_, bool show_preview_);

    static const int32_t ID = 1737538681;
    int32_t get_id() const final
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
    int64_t chat_id_;

    notificationSettingsScopeChat();

    explicit notificationSettingsScopeChat(int64_t chat_id_);

    static const int32_t ID = 1855845499;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class notificationSettingsScopePrivateChats final : public NotificationSettingsScope
{
public:

    notificationSettingsScopePrivateChats();

    static const int32_t ID = 937446759;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class notificationSettingsScopeBasicGroupChats final : public NotificationSettingsScope
{
public:

    notificationSettingsScopeBasicGroupChats();

    static const int32_t ID = -1358646601;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class notificationSettingsScopeAllChats final : public NotificationSettingsScope
{
public:

    notificationSettingsScopeAllChats();

    static const int32_t ID = -1345889922;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class ok final : public Object
{
public:

    ok();

    static const int32_t ID = -722616727;
    int32_t get_id() const final
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

    static const int32_t ID = 63135518;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class optionValueEmpty final : public OptionValue
{
public:

    optionValueEmpty();

    static const int32_t ID = 918955155;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class optionValueInteger final : public OptionValue
{
public:
    int32_t value_;

    optionValueInteger();

    explicit optionValueInteger(int32_t value_);

    static const int32_t ID = -1400911104;
    int32_t get_id() const final
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

    static const int32_t ID = 756248212;
    int32_t get_id() const final
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

    static const int32_t ID = -1830611784;
    int32_t get_id() const final
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

    static const int32_t ID = 1629664784;
    int32_t get_id() const final
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

    static const int32_t ID = 264524263;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockAuthorDate final : public PageBlock
{
public:
    object_ptr<RichText> author_;
    int32_t publish_date_;

    pageBlockAuthorDate();

    pageBlockAuthorDate(object_ptr<RichText> &&author_, int32_t publish_date_);

    static const int32_t ID = 1300231184;
    int32_t get_id() const final
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

    static const int32_t ID = 1402854811;
    int32_t get_id() const final
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

    static const int32_t ID = 1263956774;
    int32_t get_id() const final
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

    static const int32_t ID = 1182402406;
    int32_t get_id() const final
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

    static const int32_t ID = -1066346178;
    int32_t get_id() const final
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

    static const int32_t ID = 886429480;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pageBlockDivider final : public PageBlock
{
public:

    pageBlockDivider();

    static const int32_t ID = -618614392;
    int32_t get_id() const final
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

    static const int32_t ID = -837994576;
    int32_t get_id() const final
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

    static const int32_t ID = -1752631674;
    int32_t get_id() const final
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

    static const int32_t ID = -37421406;
    int32_t get_id() const final
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

    static const int32_t ID = -1799498665;
    int32_t get_id() const final
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

    static const int32_t ID = 1639478661;
    int32_t get_id() const final
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

    static const int32_t ID = 1898245855;
    int32_t get_id() const final
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

    static const int32_t ID = -637181825;
    int32_t get_id() const final
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

    static const int32_t ID = 1610373002;
    int32_t get_id() const final
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

    static const int32_t ID = 972174080;
    int32_t get_id() const final
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
    int32_t width_;
    int32_t height_;
    object_ptr<RichText> caption_;
    bool is_full_width_;
    bool allow_scrolling_;

    pageBlockEmbedded();

    pageBlockEmbedded(std::string const &url_, std::string const &html_,
                      object_ptr<photo> &&poster_photo_, int32_t width_, int32_t height_,
                      object_ptr<RichText> &&caption_, bool is_full_width_, bool allow_scrolling_);

    static const int32_t ID = -211257334;
    int32_t get_id() const final
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
    int32_t date_;
    std::vector<object_ptr<PageBlock>> page_blocks_;
    object_ptr<RichText> caption_;

    pageBlockEmbeddedPost();

    pageBlockEmbeddedPost(std::string const &url_, std::string const &author_,
                          object_ptr<photo> &&author_photo_, int32_t date_,
                          std::vector<object_ptr<PageBlock>> &&page_blocks_, object_ptr<RichText> &&caption_);

    static const int32_t ID = 1049948772;
    int32_t get_id() const final
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

    static const int32_t ID = 911142202;
    int32_t get_id() const final
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

    static const int32_t ID = 178557514;
    int32_t get_id() const final
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

    static const int32_t ID = 214606645;
    int32_t get_id() const final
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

    static const int32_t ID = 1483233330;
    int32_t get_id() const final
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

    static const int32_t ID = 1383061922;
    int32_t get_id() const final
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

    static const int32_t ID = -200418230;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class paymentReceipt final : public Object
{
public:
    int32_t date_;
    int32_t payments_provider_user_id_;
    object_ptr<invoice> invoice_;
    object_ptr<orderInfo> order_info_;
    object_ptr<shippingOption> shipping_option_;
    std::string credentials_title_;

    paymentReceipt();

    paymentReceipt(int32_t date_, int32_t payments_provider_user_id_,
                   object_ptr<invoice> &&invoice_, object_ptr<orderInfo> &&order_info_,
                   object_ptr<shippingOption> &&shipping_option_, std::string const &credentials_title_);

    static const int32_t ID = -1171223545;
    int32_t get_id() const final
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

    static const int32_t ID = -804263843;
    int32_t get_id() const final
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

    static const int32_t ID = 1090791032;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class photo final : public Object
{
public:
    int64_t id_;
    bool has_stickers_;
    std::vector<object_ptr<photoSize>> sizes_;

    photo();

    photo(int64_t id_, bool has_stickers_, std::vector<object_ptr<photoSize>> &&sizes_);

    static const int32_t ID = -1949521787;
    int32_t get_id() const final
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
    int32_t width_;
    int32_t height_;

    photoSize();

    photoSize(std::string const &type_, object_ptr<file> &&photo_, int32_t width_,
              int32_t height_);

    static const int32_t ID = 421980227;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class profilePhoto final : public Object
{
public:
    int64_t id_;
    object_ptr<file> small_;
    object_ptr<file> big_;

    profilePhoto();

    profilePhoto(int64_t id_, object_ptr<file> &&small_, object_ptr<file> &&big_);

    static const int32_t ID = 978085937;
    int32_t get_id() const final
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

    static const int32_t ID = 748440246;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class proxySocks5 final : public Proxy
{
public:
    std::string server_;
    int32_t port_;
    std::string username_;
    std::string password_;

    proxySocks5();

    proxySocks5(std::string const &server_, int32_t port_, std::string const &username_,
                std::string const &password_);

    static const int32_t ID = 1456461592;
    int32_t get_id() const final
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

    static const int32_t ID = -679603433;
    int32_t get_id() const final
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

    static const int32_t ID = 1290526187;
    int32_t get_id() const final
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
    int32_t uploaded_size_;

    remoteFile();

    remoteFile(std::string const &id_, bool is_uploading_active_, bool is_uploading_completed_,
               int32_t uploaded_size_);

    static const int32_t ID = 1761289748;
    int32_t get_id() const final
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

    static const int32_t ID = -691252879;
    int32_t get_id() const final
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

    static const int32_t ID = 1039104593;
    int32_t get_id() const final
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

    static const int32_t ID = -992627133;
    int32_t get_id() const final
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

    static const int32_t ID = -619317658;
    int32_t get_id() const final
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

    static const int32_t ID = 482617702;
    int32_t get_id() const final
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

    static const int32_t ID = 1670844268;
    int32_t get_id() const final
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

    static const int32_t ID = 1853354047;
    int32_t get_id() const final
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

    static const int32_t ID = -536019572;
    int32_t get_id() const final
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

    static const int32_t ID = 723413585;
    int32_t get_id() const final
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

    static const int32_t ID = -1271496249;
    int32_t get_id() const final
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

    static const int32_t ID = 1967248447;
    int32_t get_id() const final
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

    static const int32_t ID = 40018679;
    int32_t get_id() const final
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

    static const int32_t ID = 1647457821;
    int32_t get_id() const final
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

    static const int32_t ID = -370273060;
    int32_t get_id() const final
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

    static const int32_t ID = -869395657;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterAnimation final : public SearchMessagesFilter
{
public:

    searchMessagesFilterAnimation();

    static const int32_t ID = -155713339;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterAudio final : public SearchMessagesFilter
{
public:

    searchMessagesFilterAudio();

    static const int32_t ID = 867505275;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterDocument final : public SearchMessagesFilter
{
public:

    searchMessagesFilterDocument();

    static const int32_t ID = 1526331215;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterPhoto final : public SearchMessagesFilter
{
public:

    searchMessagesFilterPhoto();

    static const int32_t ID = 925932293;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterVideo final : public SearchMessagesFilter
{
public:

    searchMessagesFilterVideo();

    static const int32_t ID = 115538222;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterVoiceNote final : public SearchMessagesFilter
{
public:

    searchMessagesFilterVoiceNote();

    static const int32_t ID = 1841439357;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterPhotoAndVideo final : public SearchMessagesFilter
{
public:

    searchMessagesFilterPhotoAndVideo();

    static const int32_t ID = 1352130963;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterUrl final : public SearchMessagesFilter
{
public:

    searchMessagesFilterUrl();

    static const int32_t ID = -1828724341;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterChatPhoto final : public SearchMessagesFilter
{
public:

    searchMessagesFilterChatPhoto();

    static const int32_t ID = -1247751329;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterCall final : public SearchMessagesFilter
{
public:

    searchMessagesFilterCall();

    static const int32_t ID = 1305231012;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterMissedCall final : public SearchMessagesFilter
{
public:

    searchMessagesFilterMissedCall();

    static const int32_t ID = 970663098;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterVideoNote final : public SearchMessagesFilter
{
public:

    searchMessagesFilterVideoNote();

    static const int32_t ID = 564323321;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterVoiceAndVideoNote final : public SearchMessagesFilter
{
public:

    searchMessagesFilterVoiceAndVideoNote();

    static const int32_t ID = 664174819;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterMention final : public SearchMessagesFilter
{
public:

    searchMessagesFilterMention();

    static const int32_t ID = 2001258652;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessagesFilterUnreadMention final : public SearchMessagesFilter
{
public:

    searchMessagesFilterUnreadMention();

    static const int32_t ID = -95769149;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class secretChat final : public Object
{
public:
    int32_t id_;
    int32_t user_id_;
    object_ptr<SecretChatState> state_;
    bool is_outbound_;
    int32_t ttl_;
    std::string key_hash_;
    int32_t layer_;

    secretChat();

    secretChat(int32_t id_, int32_t user_id_, object_ptr<SecretChatState> &&state_,
               bool is_outbound_, int32_t ttl_, std::string const &key_hash_, int32_t layer_);

    static const int32_t ID = 1279231629;
    int32_t get_id() const final
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

    static const int32_t ID = -1637050756;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class secretChatStateReady final : public SecretChatState
{
public:

    secretChatStateReady();

    static const int32_t ID = -1611352087;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class secretChatStateClosed final : public SecretChatState
{
public:

    secretChatStateClosed();

    static const int32_t ID = -1945106707;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class session final : public Object
{
public:
    int64_t id_;
    bool is_current_;
    int32_t api_id_;
    std::string application_name_;
    std::string application_version_;
    bool is_official_application_;
    std::string device_model_;
    std::string platform_;
    std::string system_version_;
    int32_t log_in_date_;
    int32_t last_active_date_;
    std::string ip_;
    std::string country_;
    std::string region_;

    session();

    session(int64_t id_, bool is_current_, int32_t api_id_,
            std::string const &application_name_, std::string const &application_version_,
            bool is_official_application_, std::string const &device_model_, std::string const &platform_,
            std::string const &system_version_, int32_t log_in_date_, int32_t last_active_date_,
            std::string const &ip_, std::string const &country_, std::string const &region_);

    static const int32_t ID = 1715359000;
    int32_t get_id() const final
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

    static const int32_t ID = -463118121;
    int32_t get_id() const final
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

    static const int32_t ID = 565574826;
    int32_t get_id() const final
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

    static const int32_t ID = 1425690001;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sticker final : public Object
{
public:
    int64_t set_id_;
    int32_t width_;
    int32_t height_;
    std::string emoji_;
    bool is_mask_;
    object_ptr<maskPosition> mask_position_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> sticker_;

    sticker();

    sticker(int64_t set_id_, int32_t width_, int32_t height_, std::string const &emoji_,
            bool is_mask_, object_ptr<maskPosition> &&mask_position_, object_ptr<photoSize> &&thumbnail_,
            object_ptr<file> &&sticker_);

    static const int32_t ID = -876442962;
    int32_t get_id() const final
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

    static const int32_t ID = -1781588570;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class stickerSet final : public Object
{
public:
    int64_t id_;
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

    stickerSet(int64_t id_, std::string const &title_, std::string const &name_,
               bool is_installed_, bool is_archived_, bool is_official_, bool is_masks_, bool is_viewed_,
               std::vector<object_ptr<sticker>> &&stickers_, std::vector<object_ptr<stickerEmojis>> &&emojis_);

    static const int32_t ID = 72047469;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class stickerSetInfo final : public Object
{
public:
    int64_t id_;
    std::string title_;
    std::string name_;
    bool is_installed_;
    bool is_archived_;
    bool is_official_;
    bool is_masks_;
    bool is_viewed_;
    int32_t size_;
    std::vector<object_ptr<sticker>> covers_;

    stickerSetInfo();

    stickerSetInfo(int64_t id_, std::string const &title_, std::string const &name_,
                   bool is_installed_, bool is_archived_, bool is_official_, bool is_masks_, bool is_viewed_,
                   int32_t size_, std::vector<object_ptr<sticker>> &&covers_);

    static const int32_t ID = 1469837113;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class stickerSets final : public Object
{
public:
    int32_t total_count_;
    std::vector<object_ptr<stickerSetInfo>> sets_;

    stickerSets();

    stickerSets(int32_t total_count_, std::vector<object_ptr<stickerSetInfo>> &&sets_);

    static const int32_t ID = -1883828812;
    int32_t get_id() const final
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

    static const int32_t ID = 1974859260;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class storageStatistics final : public Object
{
public:
    int64_t size_;
    int32_t count_;
    std::vector<object_ptr<storageStatisticsByChat>> by_chat_;

    storageStatistics();

    storageStatistics(int64_t size_, int32_t count_,
                      std::vector<object_ptr<storageStatisticsByChat>> &&by_chat_);

    static const int32_t ID = 217237013;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class storageStatisticsByChat final : public Object
{
public:
    int64_t chat_id_;
    int64_t size_;
    int32_t count_;
    std::vector<object_ptr<storageStatisticsByFileType>> by_file_type_;

    storageStatisticsByChat();

    storageStatisticsByChat(int64_t chat_id_, int64_t size_, int32_t count_,
                            std::vector<object_ptr<storageStatisticsByFileType>> &&by_file_type_);

    static const int32_t ID = 635434531;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class storageStatisticsByFileType final : public Object
{
public:
    object_ptr<FileType> file_type_;
    int64_t size_;
    int32_t count_;

    storageStatisticsByFileType();

    storageStatisticsByFileType(object_ptr<FileType> &&file_type_, int64_t size_,
                                int32_t count_);

    static const int32_t ID = 714012840;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class storageStatisticsFast final : public Object
{
public:
    int64_t files_size_;
    int32_t file_count_;
    int64_t database_size_;

    storageStatisticsFast();

    storageStatisticsFast(int64_t files_size_, int32_t file_count_,
                          int64_t database_size_);

    static const int32_t ID = -2005401007;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroup final : public Object
{
public:
    int32_t id_;
    std::string username_;
    int32_t date_;
    object_ptr<ChatMemberStatus> status_;
    int32_t member_count_;
    bool anyone_can_invite_;
    bool sign_messages_;
    bool is_channel_;
    bool is_verified_;
    std::string restriction_reason_;

    supergroup();

    supergroup(int32_t id_, std::string const &username_, int32_t date_,
               object_ptr<ChatMemberStatus> &&status_, int32_t member_count_, bool anyone_can_invite_,
               bool sign_messages_, bool is_channel_, bool is_verified_, std::string const &restriction_reason_);

    static const int32_t ID = -1737513476;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupFullInfo final : public Object
{
public:
    std::string description_;
    int32_t member_count_;
    int32_t administrator_count_;
    int32_t restricted_count_;
    int32_t banned_count_;
    bool can_get_members_;
    bool can_set_username_;
    bool can_set_sticker_set_;
    bool is_all_history_available_;
    int64_t sticker_set_id_;
    std::string invite_link_;
    int64_t pinned_message_id_;
    int32_t upgraded_from_basic_group_id_;
    int64_t upgraded_from_max_message_id_;

    supergroupFullInfo();

    supergroupFullInfo(std::string const &description_, int32_t member_count_,
                       int32_t administrator_count_, int32_t restricted_count_, int32_t banned_count_,
                       bool can_get_members_, bool can_set_username_, bool can_set_sticker_set_,
                       bool is_all_history_available_, int64_t sticker_set_id_, std::string const &invite_link_,
                       int64_t pinned_message_id_, int32_t upgraded_from_basic_group_id_,
                       int64_t upgraded_from_max_message_id_);

    static const int32_t ID = -1482349223;
    int32_t get_id() const final
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

    static const int32_t ID = 1178199509;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupMembersFilterAdministrators final : public SupergroupMembersFilter
{
public:

    supergroupMembersFilterAdministrators();

    static const int32_t ID = -2097380265;
    int32_t get_id() const final
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

    static const int32_t ID = -1696358469;
    int32_t get_id() const final
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

    static const int32_t ID = -1107800034;
    int32_t get_id() const final
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

    static const int32_t ID = -1210621683;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class supergroupMembersFilterBots final : public SupergroupMembersFilter
{
public:

    supergroupMembersFilterBots();

    static const int32_t ID = 492138918;
    int32_t get_id() const final
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

    static const int32_t ID = -1140786622;
    int32_t get_id() const final
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
    int32_t user_id_;

    tMeUrlTypeUser();

    explicit tMeUrlTypeUser(int32_t user_id_);

    static const int32_t ID = -1198700130;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class tMeUrlTypeSupergroup final : public TMeUrlType
{
public:
    int64_t supergroup_id_;

    tMeUrlTypeSupergroup();

    explicit tMeUrlTypeSupergroup(int64_t supergroup_id_);

    static const int32_t ID = -1353369944;
    int32_t get_id() const final
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

    static const int32_t ID = 313907785;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class tMeUrlTypeStickerSet final : public TMeUrlType
{
public:
    int64_t sticker_set_id_;

    tMeUrlTypeStickerSet();

    explicit tMeUrlTypeStickerSet(int64_t sticker_set_id_);

    static const int32_t ID = 1602473196;
    int32_t get_id() const final
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

    static const int32_t ID = -1130595098;
    int32_t get_id() const final
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
    int32_t api_id_;
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
                    bool use_message_database_, bool use_secret_chats_, int32_t api_id_,
                    std::string const &api_hash_, std::string const &system_language_code_,
                    std::string const &device_model_, std::string const &system_version_,
                    std::string const &application_version_, bool enable_storage_optimizer_, bool ignore_file_names_);

    static const int32_t ID = -761520773;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class temporaryPasswordState final : public Object
{
public:
    bool has_password_;
    int32_t valid_for_;

    temporaryPasswordState();

    temporaryPasswordState(bool has_password_, int32_t valid_for_);

    static const int32_t ID = 939837410;
    int32_t get_id() const final
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

    static const int32_t ID = -1541225250;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testInt final : public Object
{
public:
    int32_t value_;

    testInt();

    explicit testInt(int32_t value_);

    static const int32_t ID = -574804983;
    int32_t get_id() const final
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

    static const int32_t ID = -27891572;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testVectorInt final : public Object
{
public:
    std::vector<int32_t> value_;

    testVectorInt();

    explicit testVectorInt(std::vector<int32_t> &&value_);

    static const int32_t ID = 593682027;
    int32_t get_id() const final
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

    static const int32_t ID = 125891546;
    int32_t get_id() const final
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

    static const int32_t ID = 79339995;
    int32_t get_id() const final
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

    static const int32_t ID = 80780537;
    int32_t get_id() const final
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

    static const int32_t ID = 578181272;
    int32_t get_id() const final
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

    static const int32_t ID = -933199172;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntity final : public Object
{
public:
    int32_t offset_;
    int32_t length_;
    object_ptr<TextEntityType> type_;

    textEntity();

    textEntity(int32_t offset_, int32_t length_, object_ptr<TextEntityType> &&type_);

    static const int32_t ID = -1951688280;
    int32_t get_id() const final
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

    static const int32_t ID = 934535013;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeHashtag final : public TextEntityType
{
public:

    textEntityTypeHashtag();

    static const int32_t ID = -1023958307;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeBotCommand final : public TextEntityType
{
public:

    textEntityTypeBotCommand();

    static const int32_t ID = -1150997581;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeUrl final : public TextEntityType
{
public:

    textEntityTypeUrl();

    static const int32_t ID = -1312762756;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeEmailAddress final : public TextEntityType
{
public:

    textEntityTypeEmailAddress();

    static const int32_t ID = 1425545249;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeBold final : public TextEntityType
{
public:

    textEntityTypeBold();

    static const int32_t ID = -1128210000;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeItalic final : public TextEntityType
{
public:

    textEntityTypeItalic();

    static const int32_t ID = -118253987;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeCode final : public TextEntityType
{
public:

    textEntityTypeCode();

    static const int32_t ID = -974534326;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypePre final : public TextEntityType
{
public:

    textEntityTypePre();

    static const int32_t ID = 1648958606;
    int32_t get_id() const final
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

    static const int32_t ID = -945325397;
    int32_t get_id() const final
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

    static const int32_t ID = 445719651;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textEntityTypeMentionName final : public TextEntityType
{
public:
    int32_t user_id_;

    textEntityTypeMentionName();

    explicit textEntityTypeMentionName(int32_t user_id_);

    static const int32_t ID = -791517091;
    int32_t get_id() const final
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

    static const int32_t ID = 969225580;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class textParseModeHTML final : public TextParseMode
{
public:

    textParseModeHTML();

    static const int32_t ID = 1660208627;
    int32_t get_id() const final
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

    static const int32_t ID = 1026706816;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryBots final : public TopChatCategory
{
public:

    topChatCategoryBots();

    static const int32_t ID = -1577129195;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryGroups final : public TopChatCategory
{
public:

    topChatCategoryGroups();

    static const int32_t ID = 1530056846;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryChannels final : public TopChatCategory
{
public:

    topChatCategoryChannels();

    static const int32_t ID = -500825885;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryInlineBots final : public TopChatCategory
{
public:

    topChatCategoryInlineBots();

    static const int32_t ID = 377023356;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class topChatCategoryCalls final : public TopChatCategory
{
public:

    topChatCategoryCalls();

    static const int32_t ID = 356208861;
    int32_t get_id() const final
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

    static const int32_t ID = 1622347490;
    int32_t get_id() const final
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

    static const int32_t ID = 238944219;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageSendAcknowledged final : public Update
{
public:
    int64_t chat_id_;
    int64_t message_id_;

    updateMessageSendAcknowledged();

    updateMessageSendAcknowledged(int64_t chat_id_, int64_t message_id_);

    static const int32_t ID = 1302843961;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageSendSucceeded final : public Update
{
public:
    object_ptr<message> message_;
    int64_t old_message_id_;

    updateMessageSendSucceeded();

    updateMessageSendSucceeded(object_ptr<message> &&message_, int64_t old_message_id_);

    static const int32_t ID = 1815715197;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageSendFailed final : public Update
{
public:
    object_ptr<message> message_;
    int64_t old_message_id_;
    int32_t error_code_;
    std::string error_message_;

    updateMessageSendFailed();

    updateMessageSendFailed(object_ptr<message> &&message_, int64_t old_message_id_,
                            int32_t error_code_, std::string const &error_message_);

    static const int32_t ID = -1032335779;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageContent final : public Update
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    object_ptr<MessageContent> new_content_;

    updateMessageContent();

    updateMessageContent(int64_t chat_id_, int64_t message_id_,
                         object_ptr<MessageContent> &&new_content_);

    static const int32_t ID = 506903332;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageEdited final : public Update
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    int32_t edit_date_;
    object_ptr<ReplyMarkup> reply_markup_;

    updateMessageEdited();

    updateMessageEdited(int64_t chat_id_, int64_t message_id_, int32_t edit_date_,
                        object_ptr<ReplyMarkup> &&reply_markup_);

    static const int32_t ID = -559545626;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageViews final : public Update
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    int32_t views_;

    updateMessageViews();

    updateMessageViews(int64_t chat_id_, int64_t message_id_, int32_t views_);

    static const int32_t ID = -1854131125;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageContentOpened final : public Update
{
public:
    int64_t chat_id_;
    int64_t message_id_;

    updateMessageContentOpened();

    updateMessageContentOpened(int64_t chat_id_, int64_t message_id_);

    static const int32_t ID = -1520523131;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateMessageMentionRead final : public Update
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    int32_t unread_mention_count_;

    updateMessageMentionRead();

    updateMessageMentionRead(int64_t chat_id_, int64_t message_id_,
                             int32_t unread_mention_count_);

    static const int32_t ID = -252228282;
    int32_t get_id() const final
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

    static const int32_t ID = 2075757773;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatTitle final : public Update
{
public:
    int64_t chat_id_;
    std::string title_;

    updateChatTitle();

    updateChatTitle(int64_t chat_id_, std::string const &title_);

    static const int32_t ID = -175405660;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatPhoto final : public Update
{
public:
    int64_t chat_id_;
    object_ptr<chatPhoto> photo_;

    updateChatPhoto();

    updateChatPhoto(int64_t chat_id_, object_ptr<chatPhoto> &&photo_);

    static const int32_t ID = -209353966;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatLastMessage final : public Update
{
public:
    int64_t chat_id_;
    object_ptr<message> last_message_;
    int64_t order_;

    updateChatLastMessage();

    updateChatLastMessage(int64_t chat_id_, object_ptr<message> &&last_message_,
                          int64_t order_);

    static const int32_t ID = 580348828;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatOrder final : public Update
{
public:
    int64_t chat_id_;
    int64_t order_;

    updateChatOrder();

    updateChatOrder(int64_t chat_id_, int64_t order_);

    static const int32_t ID = -1601888026;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatIsPinned final : public Update
{
public:
    int64_t chat_id_;
    bool is_pinned_;
    int64_t order_;

    updateChatIsPinned();

    updateChatIsPinned(int64_t chat_id_, bool is_pinned_, int64_t order_);

    static const int32_t ID = 488876260;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatReadInbox final : public Update
{
public:
    int64_t chat_id_;
    int64_t last_read_inbox_message_id_;
    int32_t unread_count_;

    updateChatReadInbox();

    updateChatReadInbox(int64_t chat_id_, int64_t last_read_inbox_message_id_,
                        int32_t unread_count_);

    static const int32_t ID = -797952281;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatReadOutbox final : public Update
{
public:
    int64_t chat_id_;
    int64_t last_read_outbox_message_id_;

    updateChatReadOutbox();

    updateChatReadOutbox(int64_t chat_id_, int64_t last_read_outbox_message_id_);

    static const int32_t ID = 708334213;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatUnreadMentionCount final : public Update
{
public:
    int64_t chat_id_;
    int32_t unread_mention_count_;

    updateChatUnreadMentionCount();

    updateChatUnreadMentionCount(int64_t chat_id_, int32_t unread_mention_count_);

    static const int32_t ID = -2131461348;
    int32_t get_id() const final
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

    static const int32_t ID = -1767306883;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatReplyMarkup final : public Update
{
public:
    int64_t chat_id_;
    int64_t reply_markup_message_id_;

    updateChatReplyMarkup();

    updateChatReplyMarkup(int64_t chat_id_, int64_t reply_markup_message_id_);

    static const int32_t ID = 1309386144;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateChatDraftMessage final : public Update
{
public:
    int64_t chat_id_;
    object_ptr<draftMessage> draft_message_;
    int64_t order_;

    updateChatDraftMessage();

    updateChatDraftMessage(int64_t chat_id_, object_ptr<draftMessage> &&draft_message_,
                           int64_t order_);

    static const int32_t ID = -1436617498;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateDeleteMessages final : public Update
{
public:
    int64_t chat_id_;
    std::vector<int64_t> message_ids_;
    bool is_permanent_;
    bool from_cache_;

    updateDeleteMessages();

    updateDeleteMessages(int64_t chat_id_, std::vector<int64_t> &&message_ids_,
                         bool is_permanent_, bool from_cache_);

    static const int32_t ID = 1669252686;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUserChatAction final : public Update
{
public:
    int64_t chat_id_;
    int32_t user_id_;
    object_ptr<ChatAction> action_;

    updateUserChatAction();

    updateUserChatAction(int64_t chat_id_, int32_t user_id_,
                         object_ptr<ChatAction> &&action_);

    static const int32_t ID = 1444133514;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUserStatus final : public Update
{
public:
    int32_t user_id_;
    object_ptr<UserStatus> status_;

    updateUserStatus();

    updateUserStatus(int32_t user_id_, object_ptr<UserStatus> &&status_);

    static const int32_t ID = -1443545195;
    int32_t get_id() const final
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

    static const int32_t ID = 1183394041;
    int32_t get_id() const final
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

    static const int32_t ID = -1003239581;
    int32_t get_id() const final
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

    static const int32_t ID = -76782300;
    int32_t get_id() const final
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

    static const int32_t ID = -1666903253;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateUserFullInfo final : public Update
{
public:
    int32_t user_id_;
    object_ptr<userFullInfo> user_full_info_;

    updateUserFullInfo();

    updateUserFullInfo(int32_t user_id_, object_ptr<userFullInfo> &&user_full_info_);

    static const int32_t ID = 222103874;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateBasicGroupFullInfo final : public Update
{
public:
    int32_t basic_group_id_;
    object_ptr<basicGroupFullInfo> basic_group_full_info_;

    updateBasicGroupFullInfo();

    updateBasicGroupFullInfo(int32_t basic_group_id_,
                             object_ptr<basicGroupFullInfo> &&basic_group_full_info_);

    static const int32_t ID = 924030531;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateSupergroupFullInfo final : public Update
{
public:
    int32_t supergroup_id_;
    object_ptr<supergroupFullInfo> supergroup_full_info_;

    updateSupergroupFullInfo();

    updateSupergroupFullInfo(int32_t supergroup_id_,
                             object_ptr<supergroupFullInfo> &&supergroup_full_info_);

    static const int32_t ID = 1288828758;
    int32_t get_id() const final
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

    static const int32_t ID = 1318622637;
    int32_t get_id() const final
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

    static const int32_t ID = 114132831;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateFileGenerationStart final : public Update
{
public:
    int64_t generation_id_;
    std::string original_path_;
    std::string destination_path_;
    std::string conversion_;

    updateFileGenerationStart();

    updateFileGenerationStart(int64_t generation_id_, std::string const &original_path_,
                              std::string const &destination_path_, std::string const &conversion_);

    static const int32_t ID = 216817388;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateFileGenerationStop final : public Update
{
public:
    int64_t generation_id_;

    updateFileGenerationStop();

    explicit updateFileGenerationStop(int64_t generation_id_);

    static const int32_t ID = -1894449685;
    int32_t get_id() const final
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

    static const int32_t ID = 1337184477;
    int32_t get_id() const final
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

    static const int32_t ID = -912960778;
    int32_t get_id() const final
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

    static const int32_t ID = 900822020;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateInstalledStickerSets final : public Update
{
public:
    bool is_masks_;
    std::vector<int64_t> sticker_set_ids_;

    updateInstalledStickerSets();

    updateInstalledStickerSets(bool is_masks_, std::vector<int64_t> &&sticker_set_ids_);

    static const int32_t ID = 1125575977;
    int32_t get_id() const final
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

    static const int32_t ID = 450714593;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateRecentStickers final : public Update
{
public:
    bool is_attached_;
    std::vector<int32_t> sticker_ids_;

    updateRecentStickers();

    updateRecentStickers(bool is_attached_, std::vector<int32_t> &&sticker_ids_);

    static const int32_t ID = 1906403540;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateFavoriteStickers final : public Update
{
public:
    std::vector<int32_t> sticker_ids_;

    updateFavoriteStickers();

    explicit updateFavoriteStickers(std::vector<int32_t> &&sticker_ids_);

    static const int32_t ID = 1662240999;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateSavedAnimations final : public Update
{
public:
    std::vector<int32_t> animation_ids_;

    updateSavedAnimations();

    explicit updateSavedAnimations(std::vector<int32_t> &&animation_ids_);

    static const int32_t ID = 65563814;
    int32_t get_id() const final
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

    static const int32_t ID = 1469292078;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewInlineQuery final : public Update
{
public:
    int64_t id_;
    int32_t sender_user_id_;
    object_ptr<location> user_location_;
    std::string query_;
    std::string offset_;

    updateNewInlineQuery();

    updateNewInlineQuery(int64_t id_, int32_t sender_user_id_,
                         object_ptr<location> &&user_location_, std::string const &query_, std::string const &offset_);

    static const int32_t ID = 2064730634;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewChosenInlineResult final : public Update
{
public:
    int32_t sender_user_id_;
    object_ptr<location> user_location_;
    std::string query_;
    std::string result_id_;
    std::string inline_message_id_;

    updateNewChosenInlineResult();

    updateNewChosenInlineResult(int32_t sender_user_id_, object_ptr<location> &&user_location_,
                                std::string const &query_, std::string const &result_id_, std::string const &inline_message_id_);

    static const int32_t ID = 527526965;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewCallbackQuery final : public Update
{
public:
    int64_t id_;
    int32_t sender_user_id_;
    int64_t chat_id_;
    int64_t message_id_;
    int64_t chat_instance_;
    object_ptr<CallbackQueryPayload> payload_;

    updateNewCallbackQuery();

    updateNewCallbackQuery(int64_t id_, int32_t sender_user_id_, int64_t chat_id_,
                           int64_t message_id_, int64_t chat_instance_, object_ptr<CallbackQueryPayload> &&payload_);

    static const int32_t ID = -2044226370;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewInlineCallbackQuery final : public Update
{
public:
    int64_t id_;
    int32_t sender_user_id_;
    std::string inline_message_id_;
    int64_t chat_instance_;
    object_ptr<CallbackQueryPayload> payload_;

    updateNewInlineCallbackQuery();

    updateNewInlineCallbackQuery(int64_t id_, int32_t sender_user_id_,
                                 std::string const &inline_message_id_, int64_t chat_instance_,
                                 object_ptr<CallbackQueryPayload> &&payload_);

    static const int32_t ID = -1879154829;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewShippingQuery final : public Update
{
public:
    int64_t id_;
    int32_t sender_user_id_;
    std::string invoice_payload_;
    object_ptr<shippingAddress> shipping_address_;

    updateNewShippingQuery();

    updateNewShippingQuery(int64_t id_, int32_t sender_user_id_,
                           std::string const &invoice_payload_, object_ptr<shippingAddress> &&shipping_address_);

    static const int32_t ID = 1877838488;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewPreCheckoutQuery final : public Update
{
public:
    int64_t id_;
    int32_t sender_user_id_;
    std::string currency_;
    int64_t total_amount_;
    std::string invoice_payload_;
    std::string shipping_option_id_;
    object_ptr<orderInfo> order_info_;

    updateNewPreCheckoutQuery();

    updateNewPreCheckoutQuery(int64_t id_, int32_t sender_user_id_,
                              std::string const &currency_, int64_t total_amount_, std::string const &invoice_payload_,
                              std::string const &shipping_option_id_, object_ptr<orderInfo> &&order_info_);

    static const int32_t ID = 87964006;
    int32_t get_id() const final
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

    static const int32_t ID = 1994222092;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class updateNewCustomQuery final : public Update
{
public:
    int64_t id_;
    std::string data_;
    int32_t timeout_;

    updateNewCustomQuery();

    updateNewCustomQuery(int64_t id_, std::string const &data_, int32_t timeout_);

    static const int32_t ID = -687670874;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class user final : public Object
{
public:
    int32_t id_;
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

    user(int32_t id_, std::string const &first_name_, std::string const &last_name_,
         std::string const &username_, std::string const &phone_number_, object_ptr<UserStatus> &&status_,
         object_ptr<profilePhoto> &&profile_photo_, object_ptr<LinkState> &&outgoing_link_,
         object_ptr<LinkState> &&incoming_link_, bool is_verified_, std::string const &restriction_reason_,
         bool have_access_, object_ptr<UserType> &&type_, std::string const &language_code_);

    static const int32_t ID = -732086407;
    int32_t get_id() const final
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
    int32_t group_in_common_count_;
    object_ptr<botInfo> bot_info_;

    userFullInfo();

    userFullInfo(bool is_blocked_, bool can_be_called_, bool has_private_calls_,
                 std::string const &bio_, std::string const &share_text_, int32_t group_in_common_count_,
                 object_ptr<botInfo> &&bot_info_);

    static const int32_t ID = 1076948004;
    int32_t get_id() const final
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

    static const int32_t ID = 1862829310;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingAllowChatInvites final : public UserPrivacySetting
{
public:

    userPrivacySettingAllowChatInvites();

    static const int32_t ID = 1271668007;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingAllowCalls final : public UserPrivacySetting
{
public:

    userPrivacySettingAllowCalls();

    static const int32_t ID = -906967291;
    int32_t get_id() const final
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

    static const int32_t ID = -1967186881;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleAllowContacts final : public UserPrivacySettingRule
{
public:

    userPrivacySettingRuleAllowContacts();

    static const int32_t ID = -1892733680;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleAllowUsers final : public UserPrivacySettingRule
{
public:
    std::vector<int32_t> user_ids_;

    userPrivacySettingRuleAllowUsers();

    explicit userPrivacySettingRuleAllowUsers(std::vector<int32_t> &&user_ids_);

    static const int32_t ID = 427601278;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleRestrictAll final : public UserPrivacySettingRule
{
public:

    userPrivacySettingRuleRestrictAll();

    static const int32_t ID = -1406495408;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleRestrictContacts final : public UserPrivacySettingRule
{
public:

    userPrivacySettingRuleRestrictContacts();

    static const int32_t ID = 1008389378;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userPrivacySettingRuleRestrictUsers final : public UserPrivacySettingRule
{
public:
    std::vector<int32_t> user_ids_;

    userPrivacySettingRuleRestrictUsers();

    explicit userPrivacySettingRuleRestrictUsers(std::vector<int32_t> &&user_ids_);

    static const int32_t ID = 2119951802;
    int32_t get_id() const final
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

    static const int32_t ID = 322477541;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userProfilePhotos final : public Object
{
public:
    int32_t total_count_;
    std::vector<object_ptr<photo>> photos_;

    userProfilePhotos();

    userProfilePhotos(int32_t total_count_, std::vector<object_ptr<photo>> &&photos_);

    static const int32_t ID = 1388892074;
    int32_t get_id() const final
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

    static const int32_t ID = 164646985;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusOnline final : public UserStatus
{
public:
    int32_t expires_;

    userStatusOnline();

    explicit userStatusOnline(int32_t expires_);

    static const int32_t ID = -1529460876;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusOffline final : public UserStatus
{
public:
    int32_t was_online_;

    userStatusOffline();

    explicit userStatusOffline(int32_t was_online_);

    static const int32_t ID = -759984891;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusRecently final : public UserStatus
{
public:

    userStatusRecently();

    static const int32_t ID = -496024847;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusLastWeek final : public UserStatus
{
public:

    userStatusLastWeek();

    static const int32_t ID = 129960444;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userStatusLastMonth final : public UserStatus
{
public:

    userStatusLastMonth();

    static const int32_t ID = 2011940674;
    int32_t get_id() const final
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

    static const int32_t ID = -598644325;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userTypeDeleted final : public UserType
{
public:

    userTypeDeleted();

    static const int32_t ID = -1807729372;
    int32_t get_id() const final
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

    static const int32_t ID = 1262387765;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class userTypeUnknown final : public UserType
{
public:

    userTypeUnknown();

    static const int32_t ID = -724541123;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class users final : public Object
{
public:
    int32_t total_count_;
    std::vector<int32_t> user_ids_;

    users();

    users(int32_t total_count_, std::vector<int32_t> &&user_ids_);

    static const int32_t ID = 273760088;
    int32_t get_id() const final
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

    static const int32_t ID = 1511451484;
    int32_t get_id() const final
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

    static const int32_t ID = -674687867;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class video final : public Object
{
public:
    int32_t duration_;
    int32_t width_;
    int32_t height_;
    std::string file_name_;
    std::string mime_type_;
    bool has_stickers_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> video_;

    video();

    video(int32_t duration_, int32_t width_, int32_t height_,
          std::string const &file_name_, std::string const &mime_type_, bool has_stickers_,
          object_ptr<photoSize> &&thumbnail_, object_ptr<file> &&video_);

    static const int32_t ID = 1823593727;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class videoNote final : public Object
{
public:
    int32_t duration_;
    int32_t length_;
    object_ptr<photoSize> thumbnail_;
    object_ptr<file> video_;

    videoNote();

    videoNote(int32_t duration_, int32_t length_, object_ptr<photoSize> &&thumbnail_,
              object_ptr<file> &&video_);

    static const int32_t ID = -1177396120;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class voiceNote final : public Object
{
public:
    int32_t duration_;
    std::string waveform_;
    std::string mime_type_;
    object_ptr<file> voice_;

    voiceNote();

    voiceNote(int32_t duration_, std::string const &waveform_, std::string const &mime_type_,
              object_ptr<file> &&voice_);

    static const int32_t ID = -2066012058;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class wallpaper final : public Object
{
public:
    int32_t id_;
    std::vector<object_ptr<photoSize>> sizes_;
    int32_t color_;

    wallpaper();

    wallpaper(int32_t id_, std::vector<object_ptr<photoSize>> &&sizes_, int32_t color_);

    static const int32_t ID = 282771691;
    int32_t get_id() const final
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

    static const int32_t ID = 877926640;
    int32_t get_id() const final
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
    int32_t embed_width_;
    int32_t embed_height_;
    int32_t duration_;
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
            int32_t embed_width_, int32_t embed_height_, int32_t duration_,
            std::string const &author_, object_ptr<animation> &&animation_, object_ptr<audio> &&audio_,
            object_ptr<document> &&document_, object_ptr<sticker> &&sticker_, object_ptr<video> &&video_,
            object_ptr<videoNote> &&video_note_, object_ptr<voiceNote> &&voice_note_, bool has_instant_view_);

    static const int32_t ID = 1465949075;
    int32_t get_id() const final
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

    static const int32_t ID = 1804324850;
    int32_t get_id() const final
    {
        return ID;
    }

    void store(TlStorerToString &s, const char *field_name) const final;
};

class acceptCall final : public Function
{
public:
    int32_t call_id_;
    object_ptr<callProtocol> protocol_;

    acceptCall();

    acceptCall(int32_t call_id_, object_ptr<callProtocol> &&protocol_);

    static const int32_t ID = -646618416;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addChatMember final : public Function
{
public:
    int64_t chat_id_;
    int32_t user_id_;
    int32_t forward_limit_;

    addChatMember();

    addChatMember(int64_t chat_id_, int32_t user_id_, int32_t forward_limit_);

    static const int32_t ID = 1182817962;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addChatMembers final : public Function
{
public:
    int64_t chat_id_;
    std::vector<int32_t> user_ids_;

    addChatMembers();

    addChatMembers(int64_t chat_id_, std::vector<int32_t> &&user_ids_);

    static const int32_t ID = 1234094617;
    int32_t get_id() const final
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

    static const int32_t ID = 324504799;
    int32_t get_id() const final
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

    static const int32_t ID = 1264825305;
    int32_t get_id() const final
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

    static const int32_t ID = -1478109026;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addRecentlyFoundChat final : public Function
{
public:
    int64_t chat_id_;

    addRecentlyFoundChat();

    explicit addRecentlyFoundChat(int64_t chat_id_);

    static const int32_t ID = -1746396787;
    int32_t get_id() const final
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

    static const int32_t ID = -1538525088;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class addStickerToSet final : public Function
{
public:
    int32_t user_id_;
    std::string name_;
    object_ptr<inputSticker> sticker_;

    addStickerToSet();

    addStickerToSet(int32_t user_id_, std::string const &name_,
                    object_ptr<inputSticker> &&sticker_);

    static const int32_t ID = 1422402800;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSet>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerCallbackQuery final : public Function
{
public:
    int64_t callback_query_id_;
    std::string text_;
    bool show_alert_;
    std::string url_;
    int32_t cache_time_;

    answerCallbackQuery();

    answerCallbackQuery(int64_t callback_query_id_, std::string const &text_, bool show_alert_,
                        std::string const &url_, int32_t cache_time_);

    static const int32_t ID = -1153028490;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerCustomQuery final : public Function
{
public:
    int64_t custom_query_id_;
    std::string data_;

    answerCustomQuery();

    answerCustomQuery(int64_t custom_query_id_, std::string const &data_);

    static const int32_t ID = -1293603521;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerInlineQuery final : public Function
{
public:
    int64_t inline_query_id_;
    bool is_personal_;
    std::vector<object_ptr<InputInlineQueryResult>> results_;
    int32_t cache_time_;
    std::string next_offset_;
    std::string switch_pm_text_;
    std::string switch_pm_parameter_;

    answerInlineQuery();

    answerInlineQuery(int64_t inline_query_id_, bool is_personal_,
                      std::vector<object_ptr<InputInlineQueryResult>> &&results_, int32_t cache_time_,
                      std::string const &next_offset_, std::string const &switch_pm_text_,
                      std::string const &switch_pm_parameter_);

    static const int32_t ID = 485879477;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerPreCheckoutQuery final : public Function
{
public:
    int64_t pre_checkout_query_id_;
    std::string error_message_;

    answerPreCheckoutQuery();

    answerPreCheckoutQuery(int64_t pre_checkout_query_id_, std::string const &error_message_);

    static const int32_t ID = -1486789653;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class answerShippingQuery final : public Function
{
public:
    int64_t shipping_query_id_;
    std::vector<object_ptr<shippingOption>> shipping_options_;
    std::string error_message_;

    answerShippingQuery();

    answerShippingQuery(int64_t shipping_query_id_,
                        std::vector<object_ptr<shippingOption>> &&shipping_options_, std::string const &error_message_);

    static const int32_t ID = -434601324;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class blockUser final : public Function
{
public:
    int32_t user_id_;

    blockUser();

    explicit blockUser(int32_t user_id_);

    static const int32_t ID = -1239315139;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class cancelDownloadFile final : public Function
{
public:
    int32_t file_id_;
    bool only_if_pending_;

    cancelDownloadFile();

    cancelDownloadFile(int32_t file_id_, bool only_if_pending_);

    static const int32_t ID = -1954524450;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class cancelUploadFile final : public Function
{
public:
    int32_t file_id_;

    cancelUploadFile();

    explicit cancelUploadFile(int32_t file_id_);

    static const int32_t ID = 1623539600;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class changeChatReportSpamState final : public Function
{
public:
    int64_t chat_id_;
    bool is_spam_chat_;

    changeChatReportSpamState();

    changeChatReportSpamState(int64_t chat_id_, bool is_spam_chat_);

    static const int32_t ID = 1768597097;
    int32_t get_id() const final
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

    static const int32_t ID = 1968207955;
    int32_t get_id() const final
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

    static const int32_t ID = -1510625218;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<authenticationCodeInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class changeStickerSet final : public Function
{
public:
    int64_t set_id_;
    bool is_installed_;
    bool is_archived_;

    changeStickerSet();

    changeStickerSet(int64_t set_id_, bool is_installed_, bool is_archived_);

    static const int32_t ID = 449357293;
    int32_t get_id() const final
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

    static const int32_t ID = 639321206;
    int32_t get_id() const final
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

    static const int32_t ID = -707293555;
    int32_t get_id() const final
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

    static const int32_t ID = -2025698400;
    int32_t get_id() const final
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

    static const int32_t ID = -1720278429;
    int32_t get_id() const final
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

    static const int32_t ID = -496940997;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatInviteLinkInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class checkDatabaseEncryptionKey final : public Function
{
public:
    std::string encryption_key_;

    checkDatabaseEncryptionKey();

    explicit checkDatabaseEncryptionKey(std::string const &encryption_key_);

    static const int32_t ID = 1018769307;
    int32_t get_id() const final
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

    static const int32_t ID = 869503298;
    int32_t get_id() const final
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

    static const int32_t ID = -321242684;
    int32_t get_id() const final
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

    static const int32_t ID = -285582542;
    int32_t get_id() const final
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

    static const int32_t ID = -1187782273;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class closeChat final : public Function
{
public:
    int64_t chat_id_;

    closeChat();

    explicit closeChat(int64_t chat_id_);

    static const int32_t ID = 39749353;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class closeSecretChat final : public Function
{
public:
    int32_t secret_chat_id_;

    closeSecretChat();

    explicit closeSecretChat(int32_t secret_chat_id_);

    static const int32_t ID = -471006133;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createBasicGroupChat final : public Function
{
public:
    int32_t basic_group_id_;
    bool force_;

    createBasicGroupChat();

    createBasicGroupChat(int32_t basic_group_id_, bool force_);

    static const int32_t ID = 642492777;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createCall final : public Function
{
public:
    int32_t user_id_;
    object_ptr<callProtocol> protocol_;

    createCall();

    createCall(int32_t user_id_, object_ptr<callProtocol> &&protocol_);

    static const int32_t ID = -1742408159;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<callId>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createNewBasicGroupChat final : public Function
{
public:
    std::vector<int32_t> user_ids_;
    std::string title_;

    createNewBasicGroupChat();

    createNewBasicGroupChat(std::vector<int32_t> &&user_ids_, std::string const &title_);

    static const int32_t ID = 1874532069;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createNewSecretChat final : public Function
{
public:
    int32_t user_id_;

    createNewSecretChat();

    explicit createNewSecretChat(int32_t user_id_);

    static const int32_t ID = 1689344881;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createNewStickerSet final : public Function
{
public:
    int32_t user_id_;
    std::string title_;
    std::string name_;
    bool is_masks_;
    std::vector<object_ptr<inputSticker>> stickers_;

    createNewStickerSet();

    createNewStickerSet(int32_t user_id_, std::string const &title_, std::string const &name_,
                        bool is_masks_, std::vector<object_ptr<inputSticker>> &&stickers_);

    static const int32_t ID = 205093058;
    int32_t get_id() const final
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

    static const int32_t ID = 1284982268;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createPrivateChat final : public Function
{
public:
    int32_t user_id_;
    bool force_;

    createPrivateChat();

    createPrivateChat(int32_t user_id_, bool force_);

    static const int32_t ID = -1807530364;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createSecretChat final : public Function
{
public:
    int32_t secret_chat_id_;

    createSecretChat();

    explicit createSecretChat(int32_t secret_chat_id_);

    static const int32_t ID = 1930285615;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class createSupergroupChat final : public Function
{
public:
    int32_t supergroup_id_;
    bool force_;

    createSupergroupChat();

    createSupergroupChat(int32_t supergroup_id_, bool force_);

    static const int32_t ID = 352742758;
    int32_t get_id() const final
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
    int32_t valid_for_;

    createTemporaryPassword();

    createTemporaryPassword(std::string const &password_, int32_t valid_for_);

    static const int32_t ID = -1626509434;
    int32_t get_id() const final
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

    static const int32_t ID = -1203056508;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteChatHistory final : public Function
{
public:
    int64_t chat_id_;
    bool remove_from_chat_list_;

    deleteChatHistory();

    deleteChatHistory(int64_t chat_id_, bool remove_from_chat_list_);

    static const int32_t ID = -1384632722;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteChatMessagesFromUser final : public Function
{
public:
    int64_t chat_id_;
    int32_t user_id_;

    deleteChatMessagesFromUser();

    deleteChatMessagesFromUser(int64_t chat_id_, int32_t user_id_);

    static const int32_t ID = -1599689199;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteChatReplyMarkup final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;

    deleteChatReplyMarkup();

    deleteChatReplyMarkup(int64_t chat_id_, int64_t message_id_);

    static const int32_t ID = 100637531;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteFile final : public Function
{
public:
    int32_t file_id_;

    deleteFile();

    explicit deleteFile(int32_t file_id_);

    static const int32_t ID = 1807653676;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteMessages final : public Function
{
public:
    int64_t chat_id_;
    std::vector<int64_t> message_ids_;
    bool revoke_;

    deleteMessages();

    deleteMessages(int64_t chat_id_, std::vector<int64_t> &&message_ids_, bool revoke_);

    static const int32_t ID = 1130090173;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteProfilePhoto final : public Function
{
public:
    int64_t profile_photo_id_;

    deleteProfilePhoto();

    explicit deleteProfilePhoto(int64_t profile_photo_id_);

    static const int32_t ID = 1319794625;
    int32_t get_id() const final
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

    static const int32_t ID = 826300114;
    int32_t get_id() const final
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

    static const int32_t ID = 1629058164;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class deleteSupergroup final : public Function
{
public:
    int32_t supergroup_id_;

    deleteSupergroup();

    explicit deleteSupergroup(int32_t supergroup_id_);

    static const int32_t ID = -1999855965;
    int32_t get_id() const final
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

    static const int32_t ID = 685331274;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class discardCall final : public Function
{
public:
    int32_t call_id_;
    bool is_disconnected_;
    int32_t duration_;
    int64_t connection_id_;

    discardCall();

    discardCall(int32_t call_id_, bool is_disconnected_, int32_t duration_,
                int64_t connection_id_);

    static const int32_t ID = -923187372;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class downloadFile final : public Function
{
public:
    int32_t file_id_;
    int32_t priority_;

    downloadFile();

    downloadFile(int32_t file_id_, int32_t priority_);

    static const int32_t ID = 1531851978;
    int32_t get_id() const final
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

    static const int32_t ID = -760985929;
    int32_t get_id() const final
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

    static const int32_t ID = 655046316;
    int32_t get_id() const final
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

    static const int32_t ID = -67565858;
    int32_t get_id() const final
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

    static const int32_t ID = -855457307;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editMessageCaption final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<formattedText> caption_;

    editMessageCaption();

    editMessageCaption(int64_t chat_id_, int64_t message_id_,
                       object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<formattedText> &&caption_);

    static const int32_t ID = 1154677038;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editMessageLiveLocation final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<location> location_;

    editMessageLiveLocation();

    editMessageLiveLocation(int64_t chat_id_, int64_t message_id_,
                            object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<location> &&location_);

    static const int32_t ID = -1146772745;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editMessageReplyMarkup final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    object_ptr<ReplyMarkup> reply_markup_;

    editMessageReplyMarkup();

    editMessageReplyMarkup(int64_t chat_id_, int64_t message_id_,
                           object_ptr<ReplyMarkup> &&reply_markup_);

    static const int32_t ID = 332127881;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class editMessageText final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    editMessageText();

    editMessageText(int64_t chat_id_, int64_t message_id_,
                    object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 196272567;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class finishFileGeneration final : public Function
{
public:
    int64_t generation_id_;
    object_ptr<error> error_;

    finishFileGeneration();

    finishFileGeneration(int64_t generation_id_, object_ptr<error> &&error_);

    static const int32_t ID = -1055060835;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class forwardMessages final : public Function
{
public:
    int64_t chat_id_;
    int64_t from_chat_id_;
    std::vector<int64_t> message_ids_;
    bool disable_notification_;
    bool from_background_;
    bool as_album_;

    forwardMessages();

    forwardMessages(int64_t chat_id_, int64_t from_chat_id_,
                    std::vector<int64_t> &&message_ids_, bool disable_notification_, bool from_background_,
                    bool as_album_);

    static const int32_t ID = -537573308;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class generateChatInviteLink final : public Function
{
public:
    int64_t chat_id_;

    generateChatInviteLink();

    explicit generateChatInviteLink(int64_t chat_id_);

    static const int32_t ID = 1945532500;
    int32_t get_id() const final
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

    static const int32_t ID = -443905161;
    int32_t get_id() const final
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

    static const int32_t ID = -1425459567;
    int32_t get_id() const final
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

    static const int32_t ID = 1119710526;
    int32_t get_id() const final
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
    int64_t offset_sticker_set_id_;
    int32_t limit_;

    getArchivedStickerSets();

    getArchivedStickerSets(bool is_masks_, int64_t offset_sticker_set_id_, int32_t limit_);

    static const int32_t ID = 1996943238;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSets>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getAttachedStickerSets final : public Function
{
public:
    int32_t file_id_;

    getAttachedStickerSets();

    explicit getAttachedStickerSets(int32_t file_id_);

    static const int32_t ID = 1302172429;
    int32_t get_id() const final
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

    static const int32_t ID = 1949154877;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<AuthorizationState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getBasicGroup final : public Function
{
public:
    int32_t basic_group_id_;

    getBasicGroup();

    explicit getBasicGroup(int32_t basic_group_id_);

    static const int32_t ID = 561775568;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<basicGroup>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getBasicGroupFullInfo final : public Function
{
public:
    int32_t basic_group_id_;

    getBasicGroupFullInfo();

    explicit getBasicGroupFullInfo(int32_t basic_group_id_);

    static const int32_t ID = 1770517905;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<basicGroupFullInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getBlockedUsers final : public Function
{
public:
    int32_t offset_;
    int32_t limit_;

    getBlockedUsers();

    getBlockedUsers(int32_t offset_, int32_t limit_);

    static const int32_t ID = -742912777;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<users>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getCallbackQueryAnswer final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    object_ptr<CallbackQueryPayload> payload_;

    getCallbackQueryAnswer();

    getCallbackQueryAnswer(int64_t chat_id_, int64_t message_id_,
                           object_ptr<CallbackQueryPayload> &&payload_);

    static const int32_t ID = 116357727;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<callbackQueryAnswer>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChat final : public Function
{
public:
    int64_t chat_id_;

    getChat();

    explicit getChat(int64_t chat_id_);

    static const int32_t ID = 1866601536;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chat>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatAdministrators final : public Function
{
public:
    int64_t chat_id_;

    getChatAdministrators();

    explicit getChatAdministrators(int64_t chat_id_);

    static const int32_t ID = 508231041;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<users>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatEventLog final : public Function
{
public:
    int64_t chat_id_;
    std::string query_;
    int64_t from_event_id_;
    int32_t limit_;
    object_ptr<chatEventLogFilters> filters_;
    std::vector<int32_t> user_ids_;

    getChatEventLog();

    getChatEventLog(int64_t chat_id_, std::string const &query_, int64_t from_event_id_,
                    int32_t limit_, object_ptr<chatEventLogFilters> &&filters_,
                    std::vector<int32_t> &&user_ids_);

    static const int32_t ID = 206900967;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatEvents>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatHistory final : public Function
{
public:
    int64_t chat_id_;
    int64_t from_message_id_;
    int32_t offset_;
    int32_t limit_;
    bool only_local_;

    getChatHistory();

    getChatHistory(int64_t chat_id_, int64_t from_message_id_, int32_t offset_,
                   int32_t limit_, bool only_local_);

    static const int32_t ID = -799960451;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatMember final : public Function
{
public:
    int64_t chat_id_;
    int32_t user_id_;

    getChatMember();

    getChatMember(int64_t chat_id_, int32_t user_id_);

    static const int32_t ID = 677085892;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatMember>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatMessageByDate final : public Function
{
public:
    int64_t chat_id_;
    int32_t date_;

    getChatMessageByDate();

    getChatMessageByDate(int64_t chat_id_, int32_t date_);

    static const int32_t ID = -729083933;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChatReportSpamState final : public Function
{
public:
    int64_t chat_id_;

    getChatReportSpamState();

    explicit getChatReportSpamState(int64_t chat_id_);

    static const int32_t ID = -748866856;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatReportSpamState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getChats final : public Function
{
public:
    int64_t offset_order_;
    int64_t offset_chat_id_;
    int32_t limit_;

    getChats();

    getChats(int64_t offset_order_, int64_t offset_chat_id_, int32_t limit_);

    static const int32_t ID = -2121381601;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getCreatedPublicChats final : public Function
{
public:

    getCreatedPublicChats();

    static const int32_t ID = 1609082914;
    int32_t get_id() const final
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

    static const int32_t ID = -338964672;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getFile final : public Function
{
public:
    int32_t file_id_;

    getFile();

    explicit getFile(int32_t file_id_);

    static const int32_t ID = 1553923406;
    int32_t get_id() const final
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

    static const int32_t ID = -106055372;
    int32_t get_id() const final
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

    static const int32_t ID = -2073879671;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<text>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getGameHighScores final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    int32_t user_id_;

    getGameHighScores();

    getGameHighScores(int64_t chat_id_, int64_t message_id_, int32_t user_id_);

    static const int32_t ID = 1920923753;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<gameHighScores>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getGroupsInCommon final : public Function
{
public:
    int32_t user_id_;
    int64_t offset_chat_id_;
    int32_t limit_;

    getGroupsInCommon();

    getGroupsInCommon(int32_t user_id_, int64_t offset_chat_id_, int32_t limit_);

    static const int32_t ID = -23238689;
    int32_t get_id() const final
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

    static const int32_t ID = -656336346;
    int32_t get_id() const final
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
    int32_t user_id_;

    getInlineGameHighScores();

    getInlineGameHighScores(std::string const &inline_message_id_, int32_t user_id_);

    static const int32_t ID = -1833445800;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<gameHighScores>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getInlineQueryResults final : public Function
{
public:
    int32_t bot_user_id_;
    int64_t chat_id_;
    object_ptr<location> user_location_;
    std::string query_;
    std::string offset_;

    getInlineQueryResults();

    getInlineQueryResults(int32_t bot_user_id_, int64_t chat_id_,
                          object_ptr<location> &&user_location_, std::string const &query_, std::string const &offset_);

    static const int32_t ID = -1182511172;
    int32_t get_id() const final
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

    static const int32_t ID = 1214523749;
    int32_t get_id() const final
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

    static const int32_t ID = 794573512;
    int32_t get_id() const final
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

    static const int32_t ID = -191516033;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<user>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getMessage final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;

    getMessage();

    getMessage(int64_t chat_id_, int64_t message_id_);

    static const int32_t ID = -1821196160;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getMessages final : public Function
{
public:
    int64_t chat_id_;
    std::vector<int64_t> message_ids_;

    getMessages();

    getMessages(int64_t chat_id_, std::vector<int64_t> &&message_ids_);

    static const int32_t ID = 425299338;
    int32_t get_id() const final
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

    static const int32_t ID = -986228706;
    int32_t get_id() const final
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

    static const int32_t ID = 907144391;
    int32_t get_id() const final
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

    static const int32_t ID = -1572495746;
    int32_t get_id() const final
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

    static const int32_t ID = -174752904;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<passwordState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getPaymentForm final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;

    getPaymentForm();

    getPaymentForm(int64_t chat_id_, int64_t message_id_);

    static const int32_t ID = -2146950882;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<paymentForm>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getPaymentReceipt final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;

    getPaymentReceipt();

    getPaymentReceipt(int64_t chat_id_, int64_t message_id_);

    static const int32_t ID = 1013758294;
    int32_t get_id() const final
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

    static const int32_t ID = 1389343170;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<Proxy>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getPublicMessageLink final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    bool for_album_;

    getPublicMessageLink();

    getPublicMessageLink(int64_t chat_id_, int64_t message_id_, bool for_album_);

    static const int32_t ID = -374642839;
    int32_t get_id() const final
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

    static const int32_t ID = 1437823548;
    int32_t get_id() const final
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

    static const int32_t ID = -579622241;
    int32_t get_id() const final
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

    static const int32_t ID = 806754961;
    int32_t get_id() const final
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

    static const int32_t ID = -1594770947;
    int32_t get_id() const final
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

    static const int32_t ID = 2137204530;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<file>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSavedAnimations final : public Function
{
public:

    getSavedAnimations();

    static const int32_t ID = 7051032;
    int32_t get_id() const final
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

    static const int32_t ID = -1152016675;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<orderInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSecretChat final : public Function
{
public:
    int32_t secret_chat_id_;

    getSecretChat();

    explicit getSecretChat(int32_t secret_chat_id_);

    static const int32_t ID = 40599169;
    int32_t get_id() const final
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

    static const int32_t ID = 95352475;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerEmojis>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getStickerSet final : public Function
{
public:
    int64_t set_id_;

    getStickerSet();

    explicit getStickerSet(int64_t set_id_);

    static const int32_t ID = 1052318659;
    int32_t get_id() const final
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
    int32_t limit_;

    getStickers();

    getStickers(std::string const &emoji_, int32_t limit_);

    static const int32_t ID = -1594919556;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getStorageStatistics final : public Function
{
public:
    int32_t chat_limit_;

    getStorageStatistics();

    explicit getStorageStatistics(int32_t chat_limit_);

    static const int32_t ID = -853193929;
    int32_t get_id() const final
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

    static const int32_t ID = 61368066;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<storageStatisticsFast>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSupergroup final : public Function
{
public:
    int32_t supergroup_id_;

    getSupergroup();

    explicit getSupergroup(int32_t supergroup_id_);

    static const int32_t ID = -2063063706;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<supergroup>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSupergroupFullInfo final : public Function
{
public:
    int32_t supergroup_id_;

    getSupergroupFullInfo();

    explicit getSupergroupFullInfo(int32_t supergroup_id_);

    static const int32_t ID = -1150331262;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<supergroupFullInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getSupergroupMembers final : public Function
{
public:
    int32_t supergroup_id_;
    object_ptr<SupergroupMembersFilter> filter_;
    int32_t offset_;
    int32_t limit_;

    getSupergroupMembers();

    getSupergroupMembers(int32_t supergroup_id_, object_ptr<SupergroupMembersFilter> &&filter_,
                         int32_t offset_, int32_t limit_);

    static const int32_t ID = 1427643098;
    int32_t get_id() const final
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

    static const int32_t ID = -1733497700;
    int32_t get_id() const final
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

    static const int32_t ID = -12670830;
    int32_t get_id() const final
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

    static const int32_t ID = 1835034646;
    int32_t get_id() const final
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

    static const int32_t ID = -341490693;
    int32_t get_id() const final
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
    int32_t limit_;

    getTopChats();

    getTopChats(object_ptr<TopChatCategory> &&category_, int32_t limit_);

    static const int32_t ID = -388410847;
    int32_t get_id() const final
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

    static const int32_t ID = -1729129957;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSets>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getUser final : public Function
{
public:
    int32_t user_id_;

    getUser();

    explicit getUser(int32_t user_id_);

    static const int32_t ID = -47586017;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<user>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getUserFullInfo final : public Function
{
public:
    int32_t user_id_;

    getUserFullInfo();

    explicit getUserFullInfo(int32_t user_id_);

    static const int32_t ID = -655443263;
    int32_t get_id() const final
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

    static const int32_t ID = -2077223311;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<userPrivacySettingRules>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getUserProfilePhotos final : public Function
{
public:
    int32_t user_id_;
    int32_t offset_;
    int32_t limit_;

    getUserProfilePhotos();

    getUserProfilePhotos(int32_t user_id_, int32_t offset_, int32_t limit_);

    static const int32_t ID = -2062927433;
    int32_t get_id() const final
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

    static const int32_t ID = 2097518555;
    int32_t get_id() const final
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

    static const int32_t ID = -1962649975;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<webPageInstantView>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class getWebPagePreview final : public Function
{
public:
    std::string message_text_;

    getWebPagePreview();

    explicit getWebPagePreview(std::string const &message_text_);

    static const int32_t ID = 1322216444;
    int32_t get_id() const final
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

    static const int32_t ID = -215132767;
    int32_t get_id() const final
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

    static const int32_t ID = 1034753911;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class logOut final : public Function
{
public:

    logOut();

    static const int32_t ID = -1581923301;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class openChat final : public Function
{
public:
    int64_t chat_id_;

    openChat();

    explicit openChat(int64_t chat_id_);

    static const int32_t ID = -323371509;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class openMessageContent final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;

    openMessageContent();

    openMessageContent(int64_t chat_id_, int64_t message_id_);

    static const int32_t ID = -739088005;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class optimizeStorage final : public Function
{
public:
    int64_t size_;
    int32_t ttl_;
    int32_t count_;
    int32_t immunity_delay_;
    std::vector<object_ptr<FileType>> file_types_;
    std::vector<int64_t> chat_ids_;
    std::vector<int64_t> exclude_chat_ids_;
    int32_t chat_limit_;

    optimizeStorage();

    optimizeStorage(int64_t size_, int32_t ttl_, int32_t count_,
                    int32_t immunity_delay_, std::vector<object_ptr<FileType>> &&file_types_,
                    std::vector<int64_t> &&chat_ids_, std::vector<int64_t> &&exclude_chat_ids_,
                    int32_t chat_limit_);

    static const int32_t ID = 980397489;
    int32_t get_id() const final
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

    static const int32_t ID = -1709194593;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<formattedText>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class pinSupergroupMessage final : public Function
{
public:
    int32_t supergroup_id_;
    int64_t message_id_;
    bool disable_notification_;

    pinSupergroupMessage();

    pinSupergroupMessage(int32_t supergroup_id_, int64_t message_id_,
                         bool disable_notification_);

    static const int32_t ID = 1141187557;
    int32_t get_id() const final
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

    static const int32_t ID = -1806562997;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class readAllChatMentions final : public Function
{
public:
    int64_t chat_id_;

    readAllChatMentions();

    explicit readAllChatMentions(int64_t chat_id_);

    static const int32_t ID = 1357558453;
    int32_t get_id() const final
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

    static const int32_t ID = 787436412;
    int32_t get_id() const final
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

    static const int32_t ID = 1660185903;
    int32_t get_id() const final
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
    std::vector<int32_t> other_user_ids_;

    registerDevice();

    registerDevice(object_ptr<DeviceToken> &&device_token_,
                   std::vector<int32_t> &&other_user_ids_);

    static const int32_t ID = -413637293;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeContacts final : public Function
{
public:
    std::vector<int32_t> user_ids_;

    removeContacts();

    explicit removeContacts(std::vector<int32_t> &&user_ids_);

    static const int32_t ID = -615510759;
    int32_t get_id() const final
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

    static const int32_t ID = 1152945264;
    int32_t get_id() const final
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

    static const int32_t ID = -1013735260;
    int32_t get_id() const final
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

    static const int32_t ID = 1246577677;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class removeRecentlyFoundChat final : public Function
{
public:
    int64_t chat_id_;

    removeRecentlyFoundChat();

    explicit removeRecentlyFoundChat(int64_t chat_id_);

    static const int32_t ID = 717340444;
    int32_t get_id() const final
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

    static const int32_t ID = -495605479;
    int32_t get_id() const final
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

    static const int32_t ID = 1642196644;
    int32_t get_id() const final
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
    int64_t chat_id_;

    removeTopChat();

    removeTopChat(object_ptr<TopChatCategory> &&category_, int64_t chat_id_);

    static const int32_t ID = -1907876267;
    int32_t get_id() const final
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
    std::vector<int64_t> sticker_set_ids_;

    reorderInstalledStickerSets();

    reorderInstalledStickerSets(bool is_masks_, std::vector<int64_t> &&sticker_set_ids_);

    static const int32_t ID = 1114537563;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class reportChat final : public Function
{
public:
    int64_t chat_id_;
    object_ptr<ChatReportReason> reason_;

    reportChat();

    reportChat(int64_t chat_id_, object_ptr<ChatReportReason> &&reason_);

    static const int32_t ID = 737809476;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class reportSupergroupSpam final : public Function
{
public:
    int32_t supergroup_id_;
    int32_t user_id_;
    std::vector<int64_t> message_ids_;

    reportSupergroupSpam();

    reportSupergroupSpam(int32_t supergroup_id_, int32_t user_id_,
                         std::vector<int64_t> &&message_ids_);

    static const int32_t ID = -2125451498;
    int32_t get_id() const final
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

    static const int32_t ID = 1393896118;
    int32_t get_id() const final
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

    static const int32_t ID = 1989252384;
    int32_t get_id() const final
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

    static const int32_t ID = -814377191;
    int32_t get_id() const final
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

    static const int32_t ID = -786772060;
    int32_t get_id() const final
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

    static const int32_t ID = -174020359;
    int32_t get_id() const final
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

    static const int32_t ID = 1646452102;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchCallMessages final : public Function
{
public:
    int64_t from_message_id_;
    int32_t limit_;
    bool only_missed_;

    searchCallMessages();

    searchCallMessages(int64_t from_message_id_, int32_t limit_, bool only_missed_);

    static const int32_t ID = -1077230820;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchChatMembers final : public Function
{
public:
    int64_t chat_id_;
    std::string query_;
    int32_t limit_;

    searchChatMembers();

    searchChatMembers(int64_t chat_id_, std::string const &query_, int32_t limit_);

    static const int32_t ID = -1538035890;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chatMembers>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchChatMessages final : public Function
{
public:
    int64_t chat_id_;
    std::string query_;
    int32_t sender_user_id_;
    int64_t from_message_id_;
    int32_t offset_;
    int32_t limit_;
    object_ptr<SearchMessagesFilter> filter_;

    searchChatMessages();

    searchChatMessages(int64_t chat_id_, std::string const &query_, int32_t sender_user_id_,
                       int64_t from_message_id_, int32_t offset_, int32_t limit_,
                       object_ptr<SearchMessagesFilter> &&filter_);

    static const int32_t ID = -1528846671;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchChatRecentLocationMessages final : public Function
{
public:
    int64_t chat_id_;
    int32_t limit_;

    searchChatRecentLocationMessages();

    searchChatRecentLocationMessages(int64_t chat_id_, int32_t limit_);

    static const int32_t ID = 950238950;
    int32_t get_id() const final
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
    int32_t limit_;

    searchChats();

    searchChats(std::string const &query_, int32_t limit_);

    static const int32_t ID = -1879787060;
    int32_t get_id() const final
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
    int32_t limit_;

    searchChatsOnServer();

    searchChatsOnServer(std::string const &query_, int32_t limit_);

    static const int32_t ID = -1158402188;
    int32_t get_id() const final
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
    int32_t limit_;

    searchContacts();

    searchContacts(std::string const &query_, int32_t limit_);

    static const int32_t ID = -1794690715;
    int32_t get_id() const final
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
    int32_t limit_;

    searchHashtags();

    searchHashtags(std::string const &prefix_, int32_t limit_);

    static const int32_t ID = 1043637617;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<hashtags>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchMessages final : public Function
{
public:
    std::string query_;
    int32_t offset_date_;
    int64_t offset_chat_id_;
    int64_t offset_message_id_;
    int32_t limit_;

    searchMessages();

    searchMessages(std::string const &query_, int32_t offset_date_, int64_t offset_chat_id_,
                   int64_t offset_message_id_, int32_t limit_);

    static const int32_t ID = 1579305146;
    int32_t get_id() const final
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

    static const int32_t ID = 857135533;
    int32_t get_id() const final
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

    static const int32_t ID = 970385337;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<chats>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class searchSecretMessages final : public Function
{
public:
    int64_t chat_id_;
    std::string query_;
    int64_t from_search_id_;
    int32_t limit_;
    object_ptr<SearchMessagesFilter> filter_;

    searchSecretMessages();

    searchSecretMessages(int64_t chat_id_, std::string const &query_, int64_t from_search_id_,
                         int32_t limit_, object_ptr<SearchMessagesFilter> &&filter_);

    static const int32_t ID = -1670627915;
    int32_t get_id() const final
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

    static const int32_t ID = 1157930222;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<stickerSet>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendBotStartMessage final : public Function
{
public:
    int32_t bot_user_id_;
    int64_t chat_id_;
    std::string parameter_;

    sendBotStartMessage();

    sendBotStartMessage(int32_t bot_user_id_, int64_t chat_id_,
                        std::string const &parameter_);

    static const int32_t ID = 1112181339;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendCallDebugInformation final : public Function
{
public:
    int32_t call_id_;
    std::string debug_information_;

    sendCallDebugInformation();

    sendCallDebugInformation(int32_t call_id_, std::string const &debug_information_);

    static const int32_t ID = 2019243839;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendCallRating final : public Function
{
public:
    int32_t call_id_;
    int32_t rating_;
    std::string comment_;

    sendCallRating();

    sendCallRating(int32_t call_id_, int32_t rating_, std::string const &comment_);

    static const int32_t ID = 243075146;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendChatAction final : public Function
{
public:
    int64_t chat_id_;
    object_ptr<ChatAction> action_;

    sendChatAction();

    sendChatAction(int64_t chat_id_, object_ptr<ChatAction> &&action_);

    static const int32_t ID = -841357536;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendChatScreenshotTakenNotification final : public Function
{
public:
    int64_t chat_id_;

    sendChatScreenshotTakenNotification();

    explicit sendChatScreenshotTakenNotification(int64_t chat_id_);

    static const int32_t ID = 448399457;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendChatSetTtlMessage final : public Function
{
public:
    int64_t chat_id_;
    int32_t ttl_;

    sendChatSetTtlMessage();

    sendChatSetTtlMessage(int64_t chat_id_, int32_t ttl_);

    static const int32_t ID = 1432535564;
    int32_t get_id() const final
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

    static const int32_t ID = 285045153;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<customRequestResult>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendInlineQueryResultMessage final : public Function
{
public:
    int64_t chat_id_;
    int64_t reply_to_message_id_;
    bool disable_notification_;
    bool from_background_;
    int64_t query_id_;
    std::string result_id_;

    sendInlineQueryResultMessage();

    sendInlineQueryResultMessage(int64_t chat_id_, int64_t reply_to_message_id_,
                                 bool disable_notification_, bool from_background_, int64_t query_id_,
                                 std::string const &result_id_);

    static const int32_t ID = -643910868;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendMessage final : public Function
{
public:
    int64_t chat_id_;
    int64_t reply_to_message_id_;
    bool disable_notification_;
    bool from_background_;
    object_ptr<ReplyMarkup> reply_markup_;
    object_ptr<InputMessageContent> input_message_content_;

    sendMessage();

    sendMessage(int64_t chat_id_, int64_t reply_to_message_id_, bool disable_notification_,
                bool from_background_, object_ptr<ReplyMarkup> &&reply_markup_,
                object_ptr<InputMessageContent> &&input_message_content_);

    static const int32_t ID = 1694632114;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<message>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendMessageAlbum final : public Function
{
public:
    int64_t chat_id_;
    int64_t reply_to_message_id_;
    bool disable_notification_;
    bool from_background_;
    std::vector<object_ptr<InputMessageContent>> input_message_contents_;

    sendMessageAlbum();

    sendMessageAlbum(int64_t chat_id_, int64_t reply_to_message_id_,
                     bool disable_notification_, bool from_background_,
                     std::vector<object_ptr<InputMessageContent>> &&input_message_contents_);

    static const int32_t ID = -291823014;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<messages>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class sendPaymentForm final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    std::string order_info_id_;
    std::string shipping_option_id_;
    object_ptr<InputCredentials> credentials_;

    sendPaymentForm();

    sendPaymentForm(int64_t chat_id_, int64_t message_id_, std::string const &order_info_id_,
                    std::string const &shipping_option_id_, object_ptr<InputCredentials> &&credentials_);

    static const int32_t ID = 591581572;
    int32_t get_id() const final
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

    static const int32_t ID = 701389032;
    int32_t get_id() const final
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

    static const int32_t ID = -873497067;
    int32_t get_id() const final
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

    static const int32_t ID = -856055465;
    int32_t get_id() const final
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

    static const int32_t ID = -1619582124;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setBotUpdatesStatus final : public Function
{
public:
    int32_t pending_update_count_;
    std::string error_message_;

    setBotUpdatesStatus();

    setBotUpdatesStatus(int32_t pending_update_count_, std::string const &error_message_);

    static const int32_t ID = -1154926191;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatClientData final : public Function
{
public:
    int64_t chat_id_;
    std::string client_data_;

    setChatClientData();

    setChatClientData(int64_t chat_id_, std::string const &client_data_);

    static const int32_t ID = -827119811;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatDraftMessage final : public Function
{
public:
    int64_t chat_id_;
    object_ptr<draftMessage> draft_message_;

    setChatDraftMessage();

    setChatDraftMessage(int64_t chat_id_, object_ptr<draftMessage> &&draft_message_);

    static const int32_t ID = -588175579;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatMemberStatus final : public Function
{
public:
    int64_t chat_id_;
    int32_t user_id_;
    object_ptr<ChatMemberStatus> status_;

    setChatMemberStatus();

    setChatMemberStatus(int64_t chat_id_, int32_t user_id_,
                        object_ptr<ChatMemberStatus> &&status_);

    static const int32_t ID = -1754439241;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatPhoto final : public Function
{
public:
    int64_t chat_id_;
    object_ptr<InputFile> photo_;

    setChatPhoto();

    setChatPhoto(int64_t chat_id_, object_ptr<InputFile> &&photo_);

    static const int32_t ID = 132244217;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setChatTitle final : public Function
{
public:
    int64_t chat_id_;
    std::string title_;

    setChatTitle();

    setChatTitle(int64_t chat_id_, std::string const &title_);

    static const int32_t ID = 164282047;
    int32_t get_id() const final
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

    static const int32_t ID = -1204599371;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setFileGenerationProgress final : public Function
{
public:
    int64_t generation_id_;
    int32_t expected_size_;
    int32_t local_prefix_size_;

    setFileGenerationProgress();

    setFileGenerationProgress(int64_t generation_id_, int32_t expected_size_,
                              int32_t local_prefix_size_);

    static const int32_t ID = -540459953;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setGameScore final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    bool edit_message_;
    int32_t user_id_;
    int32_t score_;
    bool force_;

    setGameScore();

    setGameScore(int64_t chat_id_, int64_t message_id_, bool edit_message_,
                 int32_t user_id_, int32_t score_, bool force_);

    static const int32_t ID = -1768307069;
    int32_t get_id() const final
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
    int32_t user_id_;
    int32_t score_;
    bool force_;

    setInlineGameScore();

    setInlineGameScore(std::string const &inline_message_id_, bool edit_message_, int32_t user_id_,
                       int32_t score_, bool force_);

    static const int32_t ID = 758435487;
    int32_t get_id() const final
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

    static const int32_t ID = 1711693584;
    int32_t get_id() const final
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

    static const int32_t ID = -701635234;
    int32_t get_id() const final
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

    static const int32_t ID = -134430483;
    int32_t get_id() const final
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

    static const int32_t ID = 2114670322;
    int32_t get_id() const final
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

    static const int32_t ID = -1193589027;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<passwordState>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setPinnedChats final : public Function
{
public:
    std::vector<int64_t> chat_ids_;

    setPinnedChats();

    explicit setPinnedChats(std::vector<int64_t> &&chat_ids_);

    static const int32_t ID = -1369665719;
    int32_t get_id() const final
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

    static const int32_t ID = 1594734550;
    int32_t get_id() const final
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

    static const int32_t ID = -656782179;
    int32_t get_id() const final
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

    static const int32_t ID = -1981836385;
    int32_t get_id() const final
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
    int32_t position_;

    setStickerPositionInSet();

    setStickerPositionInSet(object_ptr<InputFile> &&sticker_, int32_t position_);

    static const int32_t ID = 2075281185;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setSupergroupDescription final : public Function
{
public:
    int32_t supergroup_id_;
    std::string description_;

    setSupergroupDescription();

    setSupergroupDescription(int32_t supergroup_id_, std::string const &description_);

    static const int32_t ID = 227623488;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setSupergroupStickerSet final : public Function
{
public:
    int32_t supergroup_id_;
    int64_t sticker_set_id_;

    setSupergroupStickerSet();

    setSupergroupStickerSet(int32_t supergroup_id_, int64_t sticker_set_id_);

    static const int32_t ID = -295782298;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class setSupergroupUsername final : public Function
{
public:
    int32_t supergroup_id_;
    std::string username_;

    setSupergroupUsername();

    setSupergroupUsername(int32_t supergroup_id_, std::string const &username_);

    static const int32_t ID = -1428333122;
    int32_t get_id() const final
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

    static const int32_t ID = -1912557997;
    int32_t get_id() const final
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

    static const int32_t ID = -473812741;
    int32_t get_id() const final
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

    static const int32_t ID = 439901214;
    int32_t get_id() const final
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

    static const int32_t ID = 1874485523;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class terminateSession final : public Function
{
public:
    int64_t session_id_;

    terminateSession();

    explicit terminateSession(int64_t session_id_);

    static const int32_t ID = -407385812;
    int32_t get_id() const final
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

    static const int32_t ID = -736011607;
    int32_t get_id() const final
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

    static const int32_t ID = -627291626;
    int32_t get_id() const final
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

    static const int32_t ID = -1732818385;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<testString>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testCallVectorInt final : public Function
{
public:
    std::vector<int32_t> x_;

    testCallVectorInt();

    explicit testCallVectorInt(std::vector<int32_t> &&x_);

    static const int32_t ID = -2137277793;
    int32_t get_id() const final
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

    static const int32_t ID = 1825428218;
    int32_t get_id() const final
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

    static const int32_t ID = -408600900;
    int32_t get_id() const final
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

    static const int32_t ID = 1527666429;
    int32_t get_id() const final
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

    static const int32_t ID = 1747084069;
    int32_t get_id() const final
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

    static const int32_t ID = -1343998901;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class testSquareInt final : public Function
{
public:
    int32_t x_;

    testSquareInt();

    explicit testSquareInt(int32_t x_);

    static const int32_t ID = -60135024;
    int32_t get_id() const final
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

    static const int32_t ID = 528842186;
    int32_t get_id() const final
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

    static const int32_t ID = 717094686;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<Update>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleBasicGroupAdministrators final : public Function
{
public:
    int32_t basic_group_id_;
    bool everyone_is_administrator_;

    toggleBasicGroupAdministrators();

    toggleBasicGroupAdministrators(int32_t basic_group_id_, bool everyone_is_administrator_);

    static const int32_t ID = -591395611;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleChatIsPinned final : public Function
{
public:
    int64_t chat_id_;
    bool is_pinned_;

    toggleChatIsPinned();

    toggleChatIsPinned(int64_t chat_id_, bool is_pinned_);

    static const int32_t ID = -1166802621;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleSupergroupInvites final : public Function
{
public:
    int32_t supergroup_id_;
    bool anyone_can_invite_;

    toggleSupergroupInvites();

    toggleSupergroupInvites(int32_t supergroup_id_, bool anyone_can_invite_);

    static const int32_t ID = -797384141;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleSupergroupIsAllHistoryAvailable final : public Function
{
public:
    int32_t supergroup_id_;
    bool is_all_history_available_;

    toggleSupergroupIsAllHistoryAvailable();

    toggleSupergroupIsAllHistoryAvailable(int32_t supergroup_id_, bool is_all_history_available_);

    static const int32_t ID = 1701526555;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class toggleSupergroupSignMessages final : public Function
{
public:
    int32_t supergroup_id_;
    bool sign_messages_;

    toggleSupergroupSignMessages();

    toggleSupergroupSignMessages(int32_t supergroup_id_, bool sign_messages_);

    static const int32_t ID = -558196581;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class unblockUser final : public Function
{
public:
    int32_t user_id_;

    unblockUser();

    explicit unblockUser(int32_t user_id_);

    static const int32_t ID = -307286367;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class unpinSupergroupMessage final : public Function
{
public:
    int32_t supergroup_id_;

    unpinSupergroupMessage();

    explicit unpinSupergroupMessage(int32_t supergroup_id_);

    static const int32_t ID = -1987029530;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class upgradeBasicGroupChatToSupergroupChat final : public Function
{
public:
    int64_t chat_id_;

    upgradeBasicGroupChatToSupergroupChat();

    explicit upgradeBasicGroupChatToSupergroupChat(int64_t chat_id_);

    static const int32_t ID = 300488122;
    int32_t get_id() const final
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
    int32_t priority_;

    uploadFile();

    uploadFile(object_ptr<InputFile> &&file_, object_ptr<FileType> &&file_type_,
               int32_t priority_);

    static const int32_t ID = -745597786;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<file>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class uploadStickerFile final : public Function
{
public:
    int32_t user_id_;
    object_ptr<InputFile> png_sticker_;

    uploadStickerFile();

    uploadStickerFile(int32_t user_id_, object_ptr<InputFile> &&png_sticker_);

    static const int32_t ID = 1134087551;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<file>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class validateOrderInfo final : public Function
{
public:
    int64_t chat_id_;
    int64_t message_id_;
    object_ptr<orderInfo> order_info_;
    bool allow_save_;

    validateOrderInfo();

    validateOrderInfo(int64_t chat_id_, int64_t message_id_,
                      object_ptr<orderInfo> &&order_info_, bool allow_save_);

    static const int32_t ID = 9480644;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<validatedOrderInfo>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class viewMessages final : public Function
{
public:
    int64_t chat_id_;
    std::vector<int64_t> message_ids_;
    bool force_read_;

    viewMessages();

    viewMessages(int64_t chat_id_, std::vector<int64_t> &&message_ids_, bool force_read_);

    static const int32_t ID = -1925784915;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

class viewTrendingStickerSets final : public Function
{
public:
    std::vector<int64_t> sticker_set_ids_;

    viewTrendingStickerSets();

    explicit viewTrendingStickerSets(std::vector<int64_t> &&sticker_set_ids_);

    static const int32_t ID = -952416520;
    int32_t get_id() const final
    {
        return ID;
    }

    using ReturnType = object_ptr<ok>;

    void store(TlStorerToString &s, const char *field_name) const final;
};

}// namespace tdlibQt
#endif // TDAPI_HPP
