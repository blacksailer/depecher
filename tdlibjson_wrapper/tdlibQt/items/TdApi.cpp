#include "TdApi.hpp"
#define ERROR false
#define LOG_IS_STRIPPED(value) (value)
namespace tdlibQt {
using int32 = qint32;
using int64 = qint64;

bool log_is_stripped_mock(bool value)
{
    return value;
}

std::string to_string(const BaseObject &value)
{
    TlStorerToString storer;
    value.store(storer, "");
    return storer.str();
}

accountTtl::accountTtl()
    : days_()
{}

accountTtl::accountTtl(int32_t days_)
    : days_(days_)
{}

const int32_t accountTtl::ID;

void accountTtl::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "accountTtl");
    s.store_field("days", days_);
    s.store_class_end();
}

animation::animation()
    : duration_()
    , width_()
    , height_()
    , file_name_()
    , mime_type_()
    , thumbnail_()
    , animation_()
{}

animation::animation(int32_t duration_, int32_t width_, int32_t height_,
                     std::string const &file_name_, std::string const &mime_type_, object_ptr<photoSize> &&thumbnail_,
                     object_ptr<file> &&animation_)
    : duration_(duration_)
    , width_(width_)
    , height_(height_)
    , file_name_(std::move(file_name_))
    , mime_type_(std::move(mime_type_))
    , thumbnail_(std::move(thumbnail_))
    , animation_(std::move(animation_))
{}

const int32_t animation::ID;

void animation::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "animation");
    s.store_field("duration", duration_);
    s.store_field("width", width_);
    s.store_field("height", height_);
    s.store_field("file_name", file_name_);
    s.store_field("mime_type", mime_type_);
    if (thumbnail_ == nullptr) {
        s.store_field("thumbnail", "null");
    } else {
        thumbnail_->store(s, "thumbnail");
    }
    if (animation_ == nullptr) {
        s.store_field("animation", "null");
    } else {
        animation_->store(s, "animation");
    }
    s.store_class_end();
}

animations::animations()
    : animations_()
{}

animations::animations(std::vector<object_ptr<animation>> &&animations_)
    : animations_(std::move(animations_))
{}

const int32_t animations::ID;

void animations::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "animations");
    {
        const std::vector<object_ptr<animation>> &v = animations_;
        const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
        const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
        s.store_class_begin("animations", vector_name.c_str());
        for (std::uint32_t i = 0; i < multiplicity; i++) {
            if (v[i] == nullptr) {
                s.store_field("", "null");
            } else {
                v[i]->store(s, "");
            }
        }
        s.store_class_end();
    }
    s.store_class_end();
}

audio::audio()
    : duration_()
    , title_()
    , performer_()
    , file_name_()
    , mime_type_()
    , album_cover_thumbnail_()
    , audio_()
{}

audio::audio(int32_t duration_, std::string const &title_, std::string const &performer_,
             std::string const &file_name_, std::string const &mime_type_,
             object_ptr<photoSize> &&album_cover_thumbnail_, object_ptr<file> &&audio_)
    : duration_(duration_)
    , title_(std::move(title_))
    , performer_(std::move(performer_))
    , file_name_(std::move(file_name_))
    , mime_type_(std::move(mime_type_))
    , album_cover_thumbnail_(std::move(album_cover_thumbnail_))
    , audio_(std::move(audio_))
{}

const int32_t audio::ID;

void audio::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "audio");
    s.store_field("duration", duration_);
    s.store_field("title", title_);
    s.store_field("performer", performer_);
    s.store_field("file_name", file_name_);
    s.store_field("mime_type", mime_type_);
    if (album_cover_thumbnail_ == nullptr) {
        s.store_field("album_cover_thumbnail", "null");
    } else {
        album_cover_thumbnail_->store(s, "album_cover_thumbnail");
    }
    if (audio_ == nullptr) {
        s.store_field("audio", "null");
    } else {
        audio_->store(s, "audio");
    }
    s.store_class_end();
}

authenticationCodeInfo::authenticationCodeInfo()
    : type_()
    , next_type_()
    , timeout_()
{}

authenticationCodeInfo::authenticationCodeInfo(object_ptr<AuthenticationCodeType> &&type_,
                                               object_ptr<AuthenticationCodeType> &&next_type_, int32_t timeout_)
    : type_(std::move(type_))
    , next_type_(std::move(next_type_))
    , timeout_(timeout_)
{}

const int32_t authenticationCodeInfo::ID;

void authenticationCodeInfo::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authenticationCodeInfo");
    if (type_ == nullptr) {
        s.store_field("type", "null");
    } else {
        type_->store(s, "type");
    }
    if (next_type_ == nullptr) {
        s.store_field("next_type", "null");
    } else {
        next_type_->store(s, "next_type");
    }
    s.store_field("timeout", timeout_);
    s.store_class_end();
}

authenticationCodeTypeTelegramMessage::authenticationCodeTypeTelegramMessage()
    : length_()
{}

authenticationCodeTypeTelegramMessage::authenticationCodeTypeTelegramMessage(int32_t length_)
    : length_(length_)
{}

const int32_t authenticationCodeTypeTelegramMessage::ID;

void authenticationCodeTypeTelegramMessage::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    s.store_class_begin(field_name, "authenticationCodeTypeTelegramMessage");
    s.store_field("length", length_);
    s.store_class_end();
}

authenticationCodeTypeSms::authenticationCodeTypeSms()
    : length_()
{}

authenticationCodeTypeSms::authenticationCodeTypeSms(int32_t length_)
    : length_(length_)
{}

const int32_t authenticationCodeTypeSms::ID;

void authenticationCodeTypeSms::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authenticationCodeTypeSms");
    s.store_field("length", length_);
    s.store_class_end();
}

authenticationCodeTypeCall::authenticationCodeTypeCall()
    : length_()
{}

authenticationCodeTypeCall::authenticationCodeTypeCall(int32_t length_)
    : length_(length_)
{}

const int32_t authenticationCodeTypeCall::ID;

void authenticationCodeTypeCall::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authenticationCodeTypeCall");
    s.store_field("length", length_);
    s.store_class_end();
}

authenticationCodeTypeFlashCall::authenticationCodeTypeFlashCall()
    : pattern_()
{}

authenticationCodeTypeFlashCall::authenticationCodeTypeFlashCall(std::string const &pattern_)
    : pattern_(std::move(pattern_))
{}

const int32_t authenticationCodeTypeFlashCall::ID;

void authenticationCodeTypeFlashCall::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authenticationCodeTypeFlashCall");
    s.store_field("pattern", pattern_);
    s.store_class_end();
}

authorizationStateWaitTdlibParameters::authorizationStateWaitTdlibParameters()
{
}

const int32_t authorizationStateWaitTdlibParameters::ID;

void authorizationStateWaitTdlibParameters::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateWaitTdlibParameters");
    s.store_class_end();
}

authorizationStateWaitEncryptionKey::authorizationStateWaitEncryptionKey()
    : is_encrypted_()
{}

authorizationStateWaitEncryptionKey::authorizationStateWaitEncryptionKey(bool is_encrypted_)
    : is_encrypted_(is_encrypted_)
{}

const int32_t authorizationStateWaitEncryptionKey::ID;

void authorizationStateWaitEncryptionKey::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateWaitEncryptionKey");
    s.store_field("is_encrypted", is_encrypted_);
    s.store_class_end();
}

authorizationStateWaitPhoneNumber::authorizationStateWaitPhoneNumber()
{
}

const int32_t authorizationStateWaitPhoneNumber::ID;

void authorizationStateWaitPhoneNumber::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateWaitPhoneNumber");
    s.store_class_end();
}

authorizationStateWaitCode::authorizationStateWaitCode()
    : is_registered_()
    , code_info_()
{}

authorizationStateWaitCode::authorizationStateWaitCode(bool is_registered_,
                                                       object_ptr<authenticationCodeInfo> &&code_info_)
    : is_registered_(is_registered_)
    , code_info_(std::move(code_info_))
{}

const int32_t authorizationStateWaitCode::ID;

void authorizationStateWaitCode::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateWaitCode");
    s.store_field("is_registered", is_registered_);
    if (code_info_ == nullptr) {
        s.store_field("code_info", "null");
    } else {
        code_info_->store(s, "code_info");
    }
    s.store_class_end();
}

authorizationStateWaitPassword::authorizationStateWaitPassword()
    : password_hint_()
    , has_recovery_email_address_()
    , recovery_email_address_pattern_()
{}

authorizationStateWaitPassword::authorizationStateWaitPassword(std::string const &password_hint_,
                                                               bool has_recovery_email_address_, std::string const &recovery_email_address_pattern_)
    : password_hint_(std::move(password_hint_))
    , has_recovery_email_address_(has_recovery_email_address_)
    , recovery_email_address_pattern_(std::move(recovery_email_address_pattern_))
{}

const int32_t authorizationStateWaitPassword::ID;

void authorizationStateWaitPassword::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateWaitPassword");
    s.store_field("password_hint", password_hint_);
    s.store_field("has_recovery_email_address", has_recovery_email_address_);
    s.store_field("recovery_email_address_pattern", recovery_email_address_pattern_);
    s.store_class_end();
}

authorizationStateReady::authorizationStateReady()
{
}

const int32_t authorizationStateReady::ID;

void authorizationStateReady::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateReady");
    s.store_class_end();
}

authorizationStateLoggingOut::authorizationStateLoggingOut()
{
}

const int32_t authorizationStateLoggingOut::ID;

void authorizationStateLoggingOut::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateLoggingOut");
    s.store_class_end();
}

authorizationStateClosing::authorizationStateClosing()
{
}

const int32_t authorizationStateClosing::ID;

void authorizationStateClosing::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateClosing");
    s.store_class_end();
}

authorizationStateClosed::authorizationStateClosed()
{
}

const int32_t authorizationStateClosed::ID;

void authorizationStateClosed::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "authorizationStateClosed");
    s.store_class_end();
}

basicGroup::basicGroup()
    : id_()
    , member_count_()
    , status_()
    , everyone_is_administrator_()
    , is_active_()
    , upgraded_to_supergroup_id_()
{}

basicGroup::basicGroup(int32_t id_, int32_t member_count_,
                       object_ptr<ChatMemberStatus> &&status_, bool everyone_is_administrator_, bool is_active_,
                       int32_t upgraded_to_supergroup_id_)
    : id_(id_)
    , member_count_(member_count_)
    , status_(std::move(status_))
    , everyone_is_administrator_(everyone_is_administrator_)
    , is_active_(is_active_)
    , upgraded_to_supergroup_id_(upgraded_to_supergroup_id_)
{}

const int32_t basicGroup::ID;

void basicGroup::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "basicGroup");
    s.store_field("id", id_);
    s.store_field("member_count", member_count_);
    if (status_ == nullptr) {
        s.store_field("status", "null");
    } else {
        status_->store(s, "status");
    }
    s.store_field("everyone_is_administrator", everyone_is_administrator_);
    s.store_field("is_active", is_active_);
    s.store_field("upgraded_to_supergroup_id", upgraded_to_supergroup_id_);
    s.store_class_end();
}

basicGroupFullInfo::basicGroupFullInfo()
    : creator_user_id_()
    , members_()
    , invite_link_()
{}

basicGroupFullInfo::basicGroupFullInfo(int32_t creator_user_id_,
                                       std::vector<object_ptr<chatMember>> &&members_, std::string const &invite_link_)
    : creator_user_id_(creator_user_id_)
    , members_(std::move(members_))
    , invite_link_(std::move(invite_link_))
{}

const int32_t basicGroupFullInfo::ID;

void basicGroupFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    s.store_class_begin(field_name, "basicGroupFullInfo");
    s.store_field("creator_user_id", creator_user_id_);
    {
        const std::vector<object_ptr<chatMember>> &v = members_;
        const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
        const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
        s.store_class_begin("members", vector_name.c_str());
        for (std::uint32_t i = 0; i < multiplicity; i++) {
            if (v[i] == nullptr) {
                s.store_field("", "null");
            } else {
                v[i]->store(s, "");
            }
        }
        s.store_class_end();
    }
    s.store_field("invite_link", invite_link_);
    s.store_class_end();
}

botCommand::botCommand()
    : command_()
    , description_()
{}

botCommand::botCommand(std::string const &command_, std::string const &description_)
    : command_(std::move(command_))
    , description_(std::move(description_))
{}

const int32_t botCommand::ID;

void botCommand::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "botCommand");
        s.store_field("command", command_);
        s.store_field("description", description_);
        s.store_class_end();
    }
}

botInfo::botInfo()
    : description_()
    , commands_()
{}

botInfo::botInfo(std::string const &description_, std::vector<object_ptr<botCommand>> &&commands_)
    : description_(std::move(description_))
    , commands_(std::move(commands_))
{}

const int32_t botInfo::ID;

void botInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "botInfo");
        s.store_field("description", description_);
        {
            const std::vector<object_ptr<botCommand>> &v = commands_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("commands", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

call::call()
    : id_()
    , user_id_()
    , is_outgoing_()
    , state_()
{}

call::call(int32_t id_, int32_t user_id_, bool is_outgoing_,
           object_ptr<CallState> &&state_)
    : id_(id_)
    , user_id_(user_id_)
    , is_outgoing_(is_outgoing_)
    , state_(std::move(state_))
{}

const int32_t call::ID;

void call::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "call");
        s.store_field("id", id_);
        s.store_field("user_id", user_id_);
        s.store_field("is_outgoing", is_outgoing_);
        if (state_ == nullptr) {
            s.store_field("state", "null");
        } else {
            state_->store(s, "state");
        }
        s.store_class_end();
    }
}

callConnection::callConnection()
    : id_()
    , ip_()
    , ipv6_()
    , port_()
    , peer_tag_()
{}

callConnection::callConnection(std::int64_t id_, std::string const &ip_, std::string const &ipv6_,
                               int32_t port_, std::string const &peer_tag_)
    : id_(id_)
    , ip_(std::move(ip_))
    , ipv6_(std::move(ipv6_))
    , port_(port_)
    , peer_tag_(std::move(peer_tag_))
{}

const int32_t callConnection::ID;

void callConnection::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callConnection");
        s.store_field("id", id_);
        s.store_field("ip", ip_);
        s.store_field("ipv6", ipv6_);
        s.store_field("port", port_);
        s.store_bytes_field("peer_tag", peer_tag_);
        s.store_class_end();
    }
}

callDiscardReasonEmpty::callDiscardReasonEmpty()
{
}

const int32_t callDiscardReasonEmpty::ID;

void callDiscardReasonEmpty::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callDiscardReasonEmpty");
        s.store_class_end();
    }
}

callDiscardReasonMissed::callDiscardReasonMissed()
{
}

const int32_t callDiscardReasonMissed::ID;

void callDiscardReasonMissed::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callDiscardReasonMissed");
        s.store_class_end();
    }
}

callDiscardReasonDeclined::callDiscardReasonDeclined()
{
}

const int32_t callDiscardReasonDeclined::ID;

void callDiscardReasonDeclined::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callDiscardReasonDeclined");
        s.store_class_end();
    }
}

callDiscardReasonDisconnected::callDiscardReasonDisconnected()
{
}

const int32_t callDiscardReasonDisconnected::ID;

void callDiscardReasonDisconnected::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callDiscardReasonDisconnected");
        s.store_class_end();
    }
}

callDiscardReasonHungUp::callDiscardReasonHungUp()
{
}

const int32_t callDiscardReasonHungUp::ID;

void callDiscardReasonHungUp::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callDiscardReasonHungUp");
        s.store_class_end();
    }
}

callId::callId()
    : id_()
{}

callId::callId(int32_t id_)
    : id_(id_)
{}

const int32_t callId::ID;

void callId::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callId");
        s.store_field("id", id_);
        s.store_class_end();
    }
}

callProtocol::callProtocol()
    : udp_p2p_()
    , udp_reflector_()
    , min_layer_()
    , max_layer_()
{}

callProtocol::callProtocol(bool udp_p2p_, bool udp_reflector_, int32_t min_layer_,
                           int32_t max_layer_)
    : udp_p2p_(udp_p2p_)
    , udp_reflector_(udp_reflector_)
    , min_layer_(min_layer_)
    , max_layer_(max_layer_)
{}

const int32_t callProtocol::ID;

void callProtocol::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callProtocol");
        s.store_field("udp_p2p", udp_p2p_);
        s.store_field("udp_reflector", udp_reflector_);
        s.store_field("min_layer", min_layer_);
        s.store_field("max_layer", max_layer_);
        s.store_class_end();
    }
}

callStatePending::callStatePending()
    : is_created_()
    , is_received_()
{}

callStatePending::callStatePending(bool is_created_, bool is_received_)
    : is_created_(is_created_)
    , is_received_(is_received_)
{}

const int32_t callStatePending::ID;

void callStatePending::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callStatePending");
        s.store_field("is_created", is_created_);
        s.store_field("is_received", is_received_);
        s.store_class_end();
    }
}

callStateExchangingKeys::callStateExchangingKeys()
{
}

const int32_t callStateExchangingKeys::ID;

void callStateExchangingKeys::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callStateExchangingKeys");
        s.store_class_end();
    }
}

callStateReady::callStateReady()
    : protocol_()
    , connections_()
    , config_()
    , encryption_key_()
    , emojis_()
{}

callStateReady::callStateReady(object_ptr<callProtocol> &&protocol_,
                               std::vector<object_ptr<callConnection>> &&connections_, std::string const &config_,
                               std::string const &encryption_key_, std::vector<std::string> &&emojis_)
    : protocol_(std::move(protocol_))
    , connections_(std::move(connections_))
    , config_(std::move(config_))
    , encryption_key_(std::move(encryption_key_))
    , emojis_(std::move(emojis_))
{}

const int32_t callStateReady::ID;

void callStateReady::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callStateReady");
        if (protocol_ == nullptr) {
            s.store_field("protocol", "null");
        } else {
            protocol_->store(s, "protocol");
        }
        {
            const std::vector<object_ptr<callConnection>> &v = connections_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("connections", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("config", config_);
        s.store_bytes_field("encryption_key", encryption_key_);
        {
            const std::vector<std::string> &v = emojis_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("emojis", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

callStateHangingUp::callStateHangingUp()
{
}

const int32_t callStateHangingUp::ID;

void callStateHangingUp::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callStateHangingUp");
        s.store_class_end();
    }
}

callStateDiscarded::callStateDiscarded()
    : reason_()
    , need_rating_()
    , need_debug_information_()
{}

callStateDiscarded::callStateDiscarded(object_ptr<CallDiscardReason> &&reason_, bool need_rating_,
                                       bool need_debug_information_)
    : reason_(std::move(reason_))
    , need_rating_(need_rating_)
    , need_debug_information_(need_debug_information_)
{}

const int32_t callStateDiscarded::ID;

void callStateDiscarded::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callStateDiscarded");
        if (reason_ == nullptr) {
            s.store_field("reason", "null");
        } else {
            reason_->store(s, "reason");
        }
        s.store_field("need_rating", need_rating_);
        s.store_field("need_debug_information", need_debug_information_);
        s.store_class_end();
    }
}

callStateError::callStateError()
    : error_()
{}

callStateError::callStateError(object_ptr<error> &&error_)
    : error_(std::move(error_))
{}

const int32_t callStateError::ID;

void callStateError::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callStateError");
        if (error_ == nullptr) {
            s.store_field("error", "null");
        } else {
            error_->store(s, "error");
        }
        s.store_class_end();
    }
}

callbackQueryAnswer::callbackQueryAnswer()
    : text_()
    , show_alert_()
    , url_()
{}

callbackQueryAnswer::callbackQueryAnswer(std::string const &text_, bool show_alert_,
                                         std::string const &url_)
    : text_(std::move(text_))
    , show_alert_(show_alert_)
    , url_(std::move(url_))
{}

const int32_t callbackQueryAnswer::ID;

void callbackQueryAnswer::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callbackQueryAnswer");
        s.store_field("text", text_);
        s.store_field("show_alert", show_alert_);
        s.store_field("url", url_);
        s.store_class_end();
    }
}

callbackQueryPayloadData::callbackQueryPayloadData()
    : data_()
{}

callbackQueryPayloadData::callbackQueryPayloadData(std::string const &data_)
    : data_(std::move(data_))
{}

const int32_t callbackQueryPayloadData::ID;

void callbackQueryPayloadData::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callbackQueryPayloadData");
        s.store_bytes_field("data", data_);
        s.store_class_end();
    }
}

callbackQueryPayloadGame::callbackQueryPayloadGame()
    : game_short_name_()
{}

callbackQueryPayloadGame::callbackQueryPayloadGame(std::string const &game_short_name_)
    : game_short_name_(std::move(game_short_name_))
{}

const int32_t callbackQueryPayloadGame::ID;

void callbackQueryPayloadGame::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "callbackQueryPayloadGame");
        s.store_field("game_short_name", game_short_name_);
        s.store_class_end();
    }
}

chat::chat()
    : id_()
    , type_()
    , title_()
    , photo_()
    , last_message_()
    , order_()
    , is_pinned_()
    , unread_count_()
    , last_read_inbox_message_id_()
    , last_read_outbox_message_id_()
    , unread_mention_count_()
    , notification_settings_()
    , reply_markup_message_id_()
    , draft_message_()
    , client_data_()
{}

chat::chat(std::int64_t id_, object_ptr<ChatType> &&type_, std::string const &title_,
           object_ptr<chatPhoto> &&photo_, object_ptr<message> &&last_message_, std::int64_t order_,
           bool is_pinned_, int32_t unread_count_, std::int64_t last_read_inbox_message_id_,
           std::int64_t last_read_outbox_message_id_, int32_t unread_mention_count_,
           object_ptr<notificationSettings> &&notification_settings_, std::int64_t reply_markup_message_id_,
           object_ptr<draftMessage> &&draft_message_, std::string const &client_data_)
    : id_(id_)
    , type_(std::move(type_))
    , title_(std::move(title_))
    , photo_(std::move(photo_))
    , last_message_(std::move(last_message_))
    , order_(order_)
    , is_pinned_(is_pinned_)
    , unread_count_(unread_count_)
    , last_read_inbox_message_id_(last_read_inbox_message_id_)
    , last_read_outbox_message_id_(last_read_outbox_message_id_)
    , unread_mention_count_(unread_mention_count_)
    , notification_settings_(std::move(notification_settings_))
    , reply_markup_message_id_(reply_markup_message_id_)
    , draft_message_(std::move(draft_message_))
    , client_data_(std::move(client_data_))
{}

const int32_t chat::ID;

void chat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chat");
        s.store_field("id", id_);
        if (type_ == nullptr) {
            s.store_field("type", "null");
        } else {
            type_->store(s, "type");
        }
        s.store_field("title", title_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        if (last_message_ == nullptr) {
            s.store_field("last_message", "null");
        } else {
            last_message_->store(s, "last_message");
        }
        s.store_field("order", order_);
        s.store_field("is_pinned", is_pinned_);
        s.store_field("unread_count", unread_count_);
        s.store_field("last_read_inbox_message_id", last_read_inbox_message_id_);
        s.store_field("last_read_outbox_message_id", last_read_outbox_message_id_);
        s.store_field("unread_mention_count", unread_mention_count_);
        if (notification_settings_ == nullptr) {
            s.store_field("notification_settings", "null");
        } else {
            notification_settings_->store(s, "notification_settings");
        }
        s.store_field("reply_markup_message_id", reply_markup_message_id_);
        if (draft_message_ == nullptr) {
            s.store_field("draft_message", "null");
        } else {
            draft_message_->store(s, "draft_message");
        }
        s.store_field("client_data", client_data_);
        s.store_class_end();
    }
}

chatActionTyping::chatActionTyping()
{
}

const int32_t chatActionTyping::ID;

void chatActionTyping::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionTyping");
        s.store_class_end();
    }
}

chatActionRecordingVideo::chatActionRecordingVideo()
{
}

const int32_t chatActionRecordingVideo::ID;

void chatActionRecordingVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionRecordingVideo");
        s.store_class_end();
    }
}

chatActionUploadingVideo::chatActionUploadingVideo()
    : progress_()
{}

chatActionUploadingVideo::chatActionUploadingVideo(int32_t progress_)
    : progress_(progress_)
{}

const int32_t chatActionUploadingVideo::ID;

void chatActionUploadingVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionUploadingVideo");
        s.store_field("progress", progress_);
        s.store_class_end();
    }
}

chatActionRecordingVoiceNote::chatActionRecordingVoiceNote()
{
}

const int32_t chatActionRecordingVoiceNote::ID;

void chatActionRecordingVoiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionRecordingVoiceNote");
        s.store_class_end();
    }
}

chatActionUploadingVoiceNote::chatActionUploadingVoiceNote()
    : progress_()
{}

chatActionUploadingVoiceNote::chatActionUploadingVoiceNote(int32_t progress_)
    : progress_(progress_)
{}

const int32_t chatActionUploadingVoiceNote::ID;

void chatActionUploadingVoiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionUploadingVoiceNote");
        s.store_field("progress", progress_);
        s.store_class_end();
    }
}

chatActionUploadingPhoto::chatActionUploadingPhoto()
    : progress_()
{}

chatActionUploadingPhoto::chatActionUploadingPhoto(int32_t progress_)
    : progress_(progress_)
{}

const int32_t chatActionUploadingPhoto::ID;

void chatActionUploadingPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionUploadingPhoto");
        s.store_field("progress", progress_);
        s.store_class_end();
    }
}

chatActionUploadingDocument::chatActionUploadingDocument()
    : progress_()
{}

chatActionUploadingDocument::chatActionUploadingDocument(int32_t progress_)
    : progress_(progress_)
{}

const int32_t chatActionUploadingDocument::ID;

void chatActionUploadingDocument::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionUploadingDocument");
        s.store_field("progress", progress_);
        s.store_class_end();
    }
}

chatActionChoosingLocation::chatActionChoosingLocation()
{
}

const int32_t chatActionChoosingLocation::ID;

void chatActionChoosingLocation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionChoosingLocation");
        s.store_class_end();
    }
}

chatActionChoosingContact::chatActionChoosingContact()
{
}

const int32_t chatActionChoosingContact::ID;

void chatActionChoosingContact::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionChoosingContact");
        s.store_class_end();
    }
}

chatActionStartPlayingGame::chatActionStartPlayingGame()
{
}

const int32_t chatActionStartPlayingGame::ID;

void chatActionStartPlayingGame::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionStartPlayingGame");
        s.store_class_end();
    }
}

chatActionRecordingVideoNote::chatActionRecordingVideoNote()
{
}

const int32_t chatActionRecordingVideoNote::ID;

void chatActionRecordingVideoNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionRecordingVideoNote");
        s.store_class_end();
    }
}

chatActionUploadingVideoNote::chatActionUploadingVideoNote()
    : progress_()
{}

chatActionUploadingVideoNote::chatActionUploadingVideoNote(int32_t progress_)
    : progress_(progress_)
{}

const int32_t chatActionUploadingVideoNote::ID;

void chatActionUploadingVideoNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionUploadingVideoNote");
        s.store_field("progress", progress_);
        s.store_class_end();
    }
}

chatActionCancel::chatActionCancel()
{
}

const int32_t chatActionCancel::ID;

void chatActionCancel::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatActionCancel");
        s.store_class_end();
    }
}

chatEvent::chatEvent()
    : id_()
    , date_()
    , user_id_()
    , action_()
{}

chatEvent::chatEvent(std::int64_t id_, int32_t date_, int32_t user_id_,
                     object_ptr<ChatEventAction> &&action_)
    : id_(id_)
    , date_(date_)
    , user_id_(user_id_)
    , action_(std::move(action_))
{}

const int32_t chatEvent::ID;

void chatEvent::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEvent");
        s.store_field("id", id_);
        s.store_field("date", date_);
        s.store_field("user_id", user_id_);
        if (action_ == nullptr) {
            s.store_field("action", "null");
        } else {
            action_->store(s, "action");
        }
        s.store_class_end();
    }
}

chatEventMessageEdited::chatEventMessageEdited()
    : old_message_()
    , new_message_()
{}

chatEventMessageEdited::chatEventMessageEdited(object_ptr<message> &&old_message_,
                                               object_ptr<message> &&new_message_)
    : old_message_(std::move(old_message_))
    , new_message_(std::move(new_message_))
{}

const int32_t chatEventMessageEdited::ID;

void chatEventMessageEdited::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMessageEdited");
        if (old_message_ == nullptr) {
            s.store_field("old_message", "null");
        } else {
            old_message_->store(s, "old_message");
        }
        if (new_message_ == nullptr) {
            s.store_field("new_message", "null");
        } else {
            new_message_->store(s, "new_message");
        }
        s.store_class_end();
    }
}

chatEventMessageDeleted::chatEventMessageDeleted()
    : message_()
{}

chatEventMessageDeleted::chatEventMessageDeleted(object_ptr<message> &&message_)
    : message_(std::move(message_))
{}

const int32_t chatEventMessageDeleted::ID;

void chatEventMessageDeleted::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMessageDeleted");
        if (message_ == nullptr) {
            s.store_field("message", "null");
        } else {
            message_->store(s, "message");
        }
        s.store_class_end();
    }
}

chatEventMessagePinned::chatEventMessagePinned()
    : message_()
{}

chatEventMessagePinned::chatEventMessagePinned(object_ptr<message> &&message_)
    : message_(std::move(message_))
{}

const int32_t chatEventMessagePinned::ID;

void chatEventMessagePinned::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMessagePinned");
        if (message_ == nullptr) {
            s.store_field("message", "null");
        } else {
            message_->store(s, "message");
        }
        s.store_class_end();
    }
}

chatEventMessageUnpinned::chatEventMessageUnpinned()
{
}

const int32_t chatEventMessageUnpinned::ID;

void chatEventMessageUnpinned::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMessageUnpinned");
        s.store_class_end();
    }
}

chatEventMemberJoined::chatEventMemberJoined()
{
}

const int32_t chatEventMemberJoined::ID;

void chatEventMemberJoined::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMemberJoined");
        s.store_class_end();
    }
}

chatEventMemberLeft::chatEventMemberLeft()
{
}

const int32_t chatEventMemberLeft::ID;

void chatEventMemberLeft::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMemberLeft");
        s.store_class_end();
    }
}

chatEventMemberInvited::chatEventMemberInvited()
    : user_id_()
    , status_()
{}

chatEventMemberInvited::chatEventMemberInvited(int32_t user_id_,
                                               object_ptr<ChatMemberStatus> &&status_)
    : user_id_(user_id_)
    , status_(std::move(status_))
{}

const int32_t chatEventMemberInvited::ID;

void chatEventMemberInvited::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMemberInvited");
        s.store_field("user_id", user_id_);
        if (status_ == nullptr) {
            s.store_field("status", "null");
        } else {
            status_->store(s, "status");
        }
        s.store_class_end();
    }
}

chatEventMemberPromoted::chatEventMemberPromoted()
    : user_id_()
    , old_status_()
    , new_status_()
{}

chatEventMemberPromoted::chatEventMemberPromoted(int32_t user_id_,
                                                 object_ptr<ChatMemberStatus> &&old_status_, object_ptr<ChatMemberStatus> &&new_status_)
    : user_id_(user_id_)
    , old_status_(std::move(old_status_))
    , new_status_(std::move(new_status_))
{}

const int32_t chatEventMemberPromoted::ID;

void chatEventMemberPromoted::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMemberPromoted");
        s.store_field("user_id", user_id_);
        if (old_status_ == nullptr) {
            s.store_field("old_status", "null");
        } else {
            old_status_->store(s, "old_status");
        }
        if (new_status_ == nullptr) {
            s.store_field("new_status", "null");
        } else {
            new_status_->store(s, "new_status");
        }
        s.store_class_end();
    }
}

chatEventMemberRestricted::chatEventMemberRestricted()
    : user_id_()
    , old_status_()
    , new_status_()
{}

chatEventMemberRestricted::chatEventMemberRestricted(int32_t user_id_,
                                                     object_ptr<ChatMemberStatus> &&old_status_, object_ptr<ChatMemberStatus> &&new_status_)
    : user_id_(user_id_)
    , old_status_(std::move(old_status_))
    , new_status_(std::move(new_status_))
{}

const int32_t chatEventMemberRestricted::ID;

void chatEventMemberRestricted::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventMemberRestricted");
        s.store_field("user_id", user_id_);
        if (old_status_ == nullptr) {
            s.store_field("old_status", "null");
        } else {
            old_status_->store(s, "old_status");
        }
        if (new_status_ == nullptr) {
            s.store_field("new_status", "null");
        } else {
            new_status_->store(s, "new_status");
        }
        s.store_class_end();
    }
}

chatEventTitleChanged::chatEventTitleChanged()
    : old_title_()
    , new_title_()
{}

chatEventTitleChanged::chatEventTitleChanged(std::string const &old_title_,
                                             std::string const &new_title_)
    : old_title_(std::move(old_title_))
    , new_title_(std::move(new_title_))
{}

const int32_t chatEventTitleChanged::ID;

void chatEventTitleChanged::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventTitleChanged");
        s.store_field("old_title", old_title_);
        s.store_field("new_title", new_title_);
        s.store_class_end();
    }
}

chatEventDescriptionChanged::chatEventDescriptionChanged()
    : old_description_()
    , new_description_()
{}

chatEventDescriptionChanged::chatEventDescriptionChanged(std::string const &old_description_,
                                                         std::string const &new_description_)
    : old_description_(std::move(old_description_))
    , new_description_(std::move(new_description_))
{}

const int32_t chatEventDescriptionChanged::ID;

void chatEventDescriptionChanged::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventDescriptionChanged");
        s.store_field("old_description", old_description_);
        s.store_field("new_description", new_description_);
        s.store_class_end();
    }
}

chatEventUsernameChanged::chatEventUsernameChanged()
    : old_username_()
    , new_username_()
{}

chatEventUsernameChanged::chatEventUsernameChanged(std::string const &old_username_,
                                                   std::string const &new_username_)
    : old_username_(std::move(old_username_))
    , new_username_(std::move(new_username_))
{}

const int32_t chatEventUsernameChanged::ID;

void chatEventUsernameChanged::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventUsernameChanged");
        s.store_field("old_username", old_username_);
        s.store_field("new_username", new_username_);
        s.store_class_end();
    }
}

chatEventPhotoChanged::chatEventPhotoChanged()
    : old_photo_()
    , new_photo_()
{}

chatEventPhotoChanged::chatEventPhotoChanged(object_ptr<chatPhoto> &&old_photo_,
                                             object_ptr<chatPhoto> &&new_photo_)
    : old_photo_(std::move(old_photo_))
    , new_photo_(std::move(new_photo_))
{}

const int32_t chatEventPhotoChanged::ID;

void chatEventPhotoChanged::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventPhotoChanged");
        if (old_photo_ == nullptr) {
            s.store_field("old_photo", "null");
        } else {
            old_photo_->store(s, "old_photo");
        }
        if (new_photo_ == nullptr) {
            s.store_field("new_photo", "null");
        } else {
            new_photo_->store(s, "new_photo");
        }
        s.store_class_end();
    }
}

chatEventInvitesToggled::chatEventInvitesToggled()
    : anyone_can_invite_()
{}

chatEventInvitesToggled::chatEventInvitesToggled(bool anyone_can_invite_)
    : anyone_can_invite_(anyone_can_invite_)
{}

const int32_t chatEventInvitesToggled::ID;

void chatEventInvitesToggled::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventInvitesToggled");
        s.store_field("anyone_can_invite", anyone_can_invite_);
        s.store_class_end();
    }
}

chatEventSignMessagesToggled::chatEventSignMessagesToggled()
    : sign_messages_()
{}

chatEventSignMessagesToggled::chatEventSignMessagesToggled(bool sign_messages_)
    : sign_messages_(sign_messages_)
{}

const int32_t chatEventSignMessagesToggled::ID;

void chatEventSignMessagesToggled::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventSignMessagesToggled");
        s.store_field("sign_messages", sign_messages_);
        s.store_class_end();
    }
}

chatEventStickerSetChanged::chatEventStickerSetChanged()
    : old_sticker_set_id_()
    , new_sticker_set_id_()
{}

chatEventStickerSetChanged::chatEventStickerSetChanged(std::int64_t old_sticker_set_id_,
                                                       std::int64_t new_sticker_set_id_)
    : old_sticker_set_id_(old_sticker_set_id_)
    , new_sticker_set_id_(new_sticker_set_id_)
{}

const int32_t chatEventStickerSetChanged::ID;

void chatEventStickerSetChanged::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventStickerSetChanged");
        s.store_field("old_sticker_set_id", old_sticker_set_id_);
        s.store_field("new_sticker_set_id", new_sticker_set_id_);
        s.store_class_end();
    }
}

chatEventIsAllHistoryAvailableToggled::chatEventIsAllHistoryAvailableToggled()
    : is_all_history_available_()
{}

chatEventIsAllHistoryAvailableToggled::chatEventIsAllHistoryAvailableToggled(
    bool is_all_history_available_)
    : is_all_history_available_(is_all_history_available_)
{}

const int32_t chatEventIsAllHistoryAvailableToggled::ID;

void chatEventIsAllHistoryAvailableToggled::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventIsAllHistoryAvailableToggled");
        s.store_field("is_all_history_available", is_all_history_available_);
        s.store_class_end();
    }
}

chatEventLogFilters::chatEventLogFilters()
    : message_edits_()
    , message_deletions_()
    , message_pins_()
    , member_joins_()
    , member_leaves_()
    , member_invites_()
    , member_promotions_()
    , member_restrictions_()
    , info_changes_()
    , setting_changes_()
{}

chatEventLogFilters::chatEventLogFilters(bool message_edits_, bool message_deletions_,
                                         bool message_pins_, bool member_joins_, bool member_leaves_, bool member_invites_,
                                         bool member_promotions_, bool member_restrictions_, bool info_changes_, bool setting_changes_)
    : message_edits_(message_edits_)
    , message_deletions_(message_deletions_)
    , message_pins_(message_pins_)
    , member_joins_(member_joins_)
    , member_leaves_(member_leaves_)
    , member_invites_(member_invites_)
    , member_promotions_(member_promotions_)
    , member_restrictions_(member_restrictions_)
    , info_changes_(info_changes_)
    , setting_changes_(setting_changes_)
{}

const int32_t chatEventLogFilters::ID;

void chatEventLogFilters::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEventLogFilters");
        s.store_field("message_edits", message_edits_);
        s.store_field("message_deletions", message_deletions_);
        s.store_field("message_pins", message_pins_);
        s.store_field("member_joins", member_joins_);
        s.store_field("member_leaves", member_leaves_);
        s.store_field("member_invites", member_invites_);
        s.store_field("member_promotions", member_promotions_);
        s.store_field("member_restrictions", member_restrictions_);
        s.store_field("info_changes", info_changes_);
        s.store_field("setting_changes", setting_changes_);
        s.store_class_end();
    }
}

chatEvents::chatEvents()
    : events_()
{}

chatEvents::chatEvents(std::vector<object_ptr<chatEvent>> &&events_)
    : events_(std::move(events_))
{}

const int32_t chatEvents::ID;

void chatEvents::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatEvents");
        {
            const std::vector<object_ptr<chatEvent>> &v = events_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("events", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

chatInviteLink::chatInviteLink()
    : invite_link_()
{}

chatInviteLink::chatInviteLink(std::string const &invite_link_)
    : invite_link_(std::move(invite_link_))
{}

const int32_t chatInviteLink::ID;

void chatInviteLink::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatInviteLink");
        s.store_field("invite_link", invite_link_);
        s.store_class_end();
    }
}

chatInviteLinkInfo::chatInviteLinkInfo()
    : chat_id_()
    , type_()
    , title_()
    , photo_()
    , member_count_()
    , member_user_ids_()
    , is_public_()
{}

chatInviteLinkInfo::chatInviteLinkInfo(std::int64_t chat_id_, object_ptr<ChatType> &&type_,
                                       std::string const &title_, object_ptr<chatPhoto> &&photo_, int32_t member_count_,
                                       std::vector<int32_t> &&member_user_ids_, bool is_public_)
    : chat_id_(chat_id_)
    , type_(std::move(type_))
    , title_(std::move(title_))
    , photo_(std::move(photo_))
    , member_count_(member_count_)
    , member_user_ids_(std::move(member_user_ids_))
    , is_public_(is_public_)
{}

const int32_t chatInviteLinkInfo::ID;

void chatInviteLinkInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatInviteLinkInfo");
        s.store_field("chat_id", chat_id_);
        if (type_ == nullptr) {
            s.store_field("type", "null");
        } else {
            type_->store(s, "type");
        }
        s.store_field("title", title_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_field("member_count", member_count_);
        {
            const std::vector<int32_t> &v = member_user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("member_user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("is_public", is_public_);
        s.store_class_end();
    }
}

chatMember::chatMember()
    : user_id_()
    , inviter_user_id_()
    , joined_chat_date_()
    , status_()
    , bot_info_()
{}

chatMember::chatMember(int32_t user_id_, int32_t inviter_user_id_,
                       int32_t joined_chat_date_, object_ptr<ChatMemberStatus> &&status_,
                       object_ptr<botInfo> &&bot_info_)
    : user_id_(user_id_)
    , inviter_user_id_(inviter_user_id_)
    , joined_chat_date_(joined_chat_date_)
    , status_(std::move(status_))
    , bot_info_(std::move(bot_info_))
{}

const int32_t chatMember::ID;

void chatMember::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatMember");
        s.store_field("user_id", user_id_);
        s.store_field("inviter_user_id", inviter_user_id_);
        s.store_field("joined_chat_date", joined_chat_date_);
        if (status_ == nullptr) {
            s.store_field("status", "null");
        } else {
            status_->store(s, "status");
        }
        if (bot_info_ == nullptr) {
            s.store_field("bot_info", "null");
        } else {
            bot_info_->store(s, "bot_info");
        }
        s.store_class_end();
    }
}

chatMemberStatusCreator::chatMemberStatusCreator()
    : is_member_()
{}

chatMemberStatusCreator::chatMemberStatusCreator(bool is_member_)
    : is_member_(is_member_)
{}

const int32_t chatMemberStatusCreator::ID;

void chatMemberStatusCreator::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatMemberStatusCreator");
        s.store_field("is_member", is_member_);
        s.store_class_end();
    }
}

chatMemberStatusAdministrator::chatMemberStatusAdministrator()
    : can_be_edited_()
    , can_change_info_()
    , can_post_messages_()
    , can_edit_messages_()
    , can_delete_messages_()
    , can_invite_users_()
    , can_restrict_members_()
    , can_pin_messages_()
    , can_promote_members_()
{}

chatMemberStatusAdministrator::chatMemberStatusAdministrator(bool can_be_edited_,
                                                             bool can_change_info_, bool can_post_messages_, bool can_edit_messages_, bool can_delete_messages_,
                                                             bool can_invite_users_, bool can_restrict_members_, bool can_pin_messages_,
                                                             bool can_promote_members_)
    : can_be_edited_(can_be_edited_)
    , can_change_info_(can_change_info_)
    , can_post_messages_(can_post_messages_)
    , can_edit_messages_(can_edit_messages_)
    , can_delete_messages_(can_delete_messages_)
    , can_invite_users_(can_invite_users_)
    , can_restrict_members_(can_restrict_members_)
    , can_pin_messages_(can_pin_messages_)
    , can_promote_members_(can_promote_members_)
{}

const int32_t chatMemberStatusAdministrator::ID;

void chatMemberStatusAdministrator::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatMemberStatusAdministrator");
        s.store_field("can_be_edited", can_be_edited_);
        s.store_field("can_change_info", can_change_info_);
        s.store_field("can_post_messages", can_post_messages_);
        s.store_field("can_edit_messages", can_edit_messages_);
        s.store_field("can_delete_messages", can_delete_messages_);
        s.store_field("can_invite_users", can_invite_users_);
        s.store_field("can_restrict_members", can_restrict_members_);
        s.store_field("can_pin_messages", can_pin_messages_);
        s.store_field("can_promote_members", can_promote_members_);
        s.store_class_end();
    }
}

chatMemberStatusMember::chatMemberStatusMember()
{
}

const int32_t chatMemberStatusMember::ID;

void chatMemberStatusMember::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatMemberStatusMember");
        s.store_class_end();
    }
}

chatMemberStatusRestricted::chatMemberStatusRestricted()
    : is_member_()
    , restricted_until_date_()
    , can_send_messages_()
    , can_send_media_messages_()
    , can_send_other_messages_()
    , can_add_web_page_previews_()
{}

chatMemberStatusRestricted::chatMemberStatusRestricted(bool is_member_,
                                                       int32_t restricted_until_date_, bool can_send_messages_, bool can_send_media_messages_,
                                                       bool can_send_other_messages_, bool can_add_web_page_previews_)
    : is_member_(is_member_)
    , restricted_until_date_(restricted_until_date_)
    , can_send_messages_(can_send_messages_)
    , can_send_media_messages_(can_send_media_messages_)
    , can_send_other_messages_(can_send_other_messages_)
    , can_add_web_page_previews_(can_add_web_page_previews_)
{}

const int32_t chatMemberStatusRestricted::ID;

void chatMemberStatusRestricted::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatMemberStatusRestricted");
        s.store_field("is_member", is_member_);
        s.store_field("restricted_until_date", restricted_until_date_);
        s.store_field("can_send_messages", can_send_messages_);
        s.store_field("can_send_media_messages", can_send_media_messages_);
        s.store_field("can_send_other_messages", can_send_other_messages_);
        s.store_field("can_add_web_page_previews", can_add_web_page_previews_);
        s.store_class_end();
    }
}

chatMemberStatusLeft::chatMemberStatusLeft()
{
}

const int32_t chatMemberStatusLeft::ID;

void chatMemberStatusLeft::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatMemberStatusLeft");
        s.store_class_end();
    }
}

chatMemberStatusBanned::chatMemberStatusBanned()
    : banned_until_date_()
{}

chatMemberStatusBanned::chatMemberStatusBanned(int32_t banned_until_date_)
    : banned_until_date_(banned_until_date_)
{}

const int32_t chatMemberStatusBanned::ID;

void chatMemberStatusBanned::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatMemberStatusBanned");
        s.store_field("banned_until_date", banned_until_date_);
        s.store_class_end();
    }
}

chatMembers::chatMembers()
    : total_count_()
    , members_()
{}

chatMembers::chatMembers(int32_t total_count_, std::vector<object_ptr<chatMember>> &&members_)
    : total_count_(total_count_)
    , members_(std::move(members_))
{}

const int32_t chatMembers::ID;

void chatMembers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatMembers");
        s.store_field("total_count", total_count_);
        {
            const std::vector<object_ptr<chatMember>> &v = members_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("members", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

chatPhoto::chatPhoto()
    : small_()
    , big_()
{}

chatPhoto::chatPhoto(object_ptr<file> &&small_, object_ptr<file> &&big_)
    : small_(std::move(small_))
    , big_(std::move(big_))
{}

const int32_t chatPhoto::ID;

void chatPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatPhoto");
        if (small_ == nullptr) {
            s.store_field("small", "null");
        } else {
            small_->store(s, "small");
        }
        if (big_ == nullptr) {
            s.store_field("big", "null");
        } else {
            big_->store(s, "big");
        }
        s.store_class_end();
    }
}

chatReportReasonSpam::chatReportReasonSpam()
{
}

const int32_t chatReportReasonSpam::ID;

void chatReportReasonSpam::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatReportReasonSpam");
        s.store_class_end();
    }
}

chatReportReasonViolence::chatReportReasonViolence()
{
}

const int32_t chatReportReasonViolence::ID;

void chatReportReasonViolence::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatReportReasonViolence");
        s.store_class_end();
    }
}

chatReportReasonPornography::chatReportReasonPornography()
{
}

const int32_t chatReportReasonPornography::ID;

void chatReportReasonPornography::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatReportReasonPornography");
        s.store_class_end();
    }
}

chatReportReasonCustom::chatReportReasonCustom()
    : text_()
{}

chatReportReasonCustom::chatReportReasonCustom(std::string const &text_)
    : text_(std::move(text_))
{}

const int32_t chatReportReasonCustom::ID;

void chatReportReasonCustom::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatReportReasonCustom");
        s.store_field("text", text_);
        s.store_class_end();
    }
}

chatReportSpamState::chatReportSpamState()
    : can_report_spam_()
{}

chatReportSpamState::chatReportSpamState(bool can_report_spam_)
    : can_report_spam_(can_report_spam_)
{}

const int32_t chatReportSpamState::ID;

void chatReportSpamState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatReportSpamState");
        s.store_field("can_report_spam", can_report_spam_);
        s.store_class_end();
    }
}

chatTypePrivate::chatTypePrivate()
    : user_id_()
{}

chatTypePrivate::chatTypePrivate(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t chatTypePrivate::ID;

void chatTypePrivate::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatTypePrivate");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

chatTypeBasicGroup::chatTypeBasicGroup()
    : basic_group_id_()
{}

chatTypeBasicGroup::chatTypeBasicGroup(int32_t basic_group_id_)
    : basic_group_id_(basic_group_id_)
{}

const int32_t chatTypeBasicGroup::ID;

void chatTypeBasicGroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatTypeBasicGroup");
        s.store_field("basic_group_id", basic_group_id_);
        s.store_class_end();
    }
}

chatTypeSupergroup::chatTypeSupergroup()
    : supergroup_id_()
    , is_channel_()
{}

chatTypeSupergroup::chatTypeSupergroup(int32_t supergroup_id_, bool is_channel_)
    : supergroup_id_(supergroup_id_)
    , is_channel_(is_channel_)
{}

const int32_t chatTypeSupergroup::ID;

void chatTypeSupergroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatTypeSupergroup");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("is_channel", is_channel_);
        s.store_class_end();
    }
}

chatTypeSecret::chatTypeSecret()
    : secret_chat_id_()
    , user_id_()
{}

chatTypeSecret::chatTypeSecret(int32_t secret_chat_id_, int32_t user_id_)
    : secret_chat_id_(secret_chat_id_)
    , user_id_(user_id_)
{}

const int32_t chatTypeSecret::ID;

void chatTypeSecret::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chatTypeSecret");
        s.store_field("secret_chat_id", secret_chat_id_);
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

chats::chats()
    : chat_ids_()
{}

chats::chats(std::vector<std::int64_t> &&chat_ids_)
    : chat_ids_(std::move(chat_ids_))
{}

const int32_t chats::ID;

void chats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "chats");
        {
            const std::vector<std::int64_t> &v = chat_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("chat_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

connectionStateWaitingForNetwork::connectionStateWaitingForNetwork()
{
}

const int32_t connectionStateWaitingForNetwork::ID;

void connectionStateWaitingForNetwork::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "connectionStateWaitingForNetwork");
        s.store_class_end();
    }
}

connectionStateConnectingToProxy::connectionStateConnectingToProxy()
{
}

const int32_t connectionStateConnectingToProxy::ID;

void connectionStateConnectingToProxy::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "connectionStateConnectingToProxy");
        s.store_class_end();
    }
}

connectionStateConnecting::connectionStateConnecting()
{
}

const int32_t connectionStateConnecting::ID;

void connectionStateConnecting::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "connectionStateConnecting");
        s.store_class_end();
    }
}

connectionStateUpdating::connectionStateUpdating()
{
}

const int32_t connectionStateUpdating::ID;

void connectionStateUpdating::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "connectionStateUpdating");
        s.store_class_end();
    }
}

connectionStateReady::connectionStateReady()
{
}

const int32_t connectionStateReady::ID;

void connectionStateReady::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "connectionStateReady");
        s.store_class_end();
    }
}

contact::contact()
    : phone_number_()
    , first_name_()
    , last_name_()
    , user_id_()
{}

contact::contact(std::string const &phone_number_, std::string const &first_name_,
                 std::string const &last_name_, int32_t user_id_)
    : phone_number_(std::move(phone_number_))
    , first_name_(std::move(first_name_))
    , last_name_(std::move(last_name_))
    , user_id_(user_id_)
{}

const int32_t contact::ID;

void contact::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "contact");
        s.store_field("phone_number", phone_number_);
        s.store_field("first_name", first_name_);
        s.store_field("last_name", last_name_);
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

count::count()
    : count_()
{}

count::count(int32_t count_)
    : count_(count_)
{}

const int32_t count::ID;

void count::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "count");
        s.store_field("count", count_);
        s.store_class_end();
    }
}

customRequestResult::customRequestResult()
    : result_()
{}

customRequestResult::customRequestResult(std::string const &result_)
    : result_(std::move(result_))
{}

const int32_t customRequestResult::ID;

void customRequestResult::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "customRequestResult");
        s.store_field("result", result_);
        s.store_class_end();
    }
}

deviceTokenGoogleCloudMessaging::deviceTokenGoogleCloudMessaging()
    : token_()
{}

deviceTokenGoogleCloudMessaging::deviceTokenGoogleCloudMessaging(std::string const &token_)
    : token_(std::move(token_))
{}

const int32_t deviceTokenGoogleCloudMessaging::ID;

void deviceTokenGoogleCloudMessaging::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenGoogleCloudMessaging");
        s.store_field("token", token_);
        s.store_class_end();
    }
}

deviceTokenApplePush::deviceTokenApplePush()
    : device_token_()
    , is_app_sandbox_()
{}

deviceTokenApplePush::deviceTokenApplePush(std::string const &device_token_, bool is_app_sandbox_)
    : device_token_(std::move(device_token_))
    , is_app_sandbox_(is_app_sandbox_)
{}

const int32_t deviceTokenApplePush::ID;

void deviceTokenApplePush::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenApplePush");
        s.store_field("device_token", device_token_);
        s.store_field("is_app_sandbox", is_app_sandbox_);
        s.store_class_end();
    }
}

deviceTokenApplePushVoIP::deviceTokenApplePushVoIP()
    : device_token_()
    , is_app_sandbox_()
{}

deviceTokenApplePushVoIP::deviceTokenApplePushVoIP(std::string const &device_token_,
                                                   bool is_app_sandbox_)
    : device_token_(std::move(device_token_))
    , is_app_sandbox_(is_app_sandbox_)
{}

const int32_t deviceTokenApplePushVoIP::ID;

void deviceTokenApplePushVoIP::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenApplePushVoIP");
        s.store_field("device_token", device_token_);
        s.store_field("is_app_sandbox", is_app_sandbox_);
        s.store_class_end();
    }
}

deviceTokenWindowsPush::deviceTokenWindowsPush()
    : access_token_()
{}

deviceTokenWindowsPush::deviceTokenWindowsPush(std::string const &access_token_)
    : access_token_(std::move(access_token_))
{}

const int32_t deviceTokenWindowsPush::ID;

void deviceTokenWindowsPush::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenWindowsPush");
        s.store_field("access_token", access_token_);
        s.store_class_end();
    }
}

deviceTokenMicrosoftPush::deviceTokenMicrosoftPush()
    : channel_uri_()
{}

deviceTokenMicrosoftPush::deviceTokenMicrosoftPush(std::string const &channel_uri_)
    : channel_uri_(std::move(channel_uri_))
{}

const int32_t deviceTokenMicrosoftPush::ID;

void deviceTokenMicrosoftPush::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenMicrosoftPush");
        s.store_field("channel_uri", channel_uri_);
        s.store_class_end();
    }
}

deviceTokenMicrosoftPushVoIP::deviceTokenMicrosoftPushVoIP()
    : channel_uri_()
{}

deviceTokenMicrosoftPushVoIP::deviceTokenMicrosoftPushVoIP(std::string const &channel_uri_)
    : channel_uri_(std::move(channel_uri_))
{}

const int32_t deviceTokenMicrosoftPushVoIP::ID;

void deviceTokenMicrosoftPushVoIP::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenMicrosoftPushVoIP");
        s.store_field("channel_uri", channel_uri_);
        s.store_class_end();
    }
}

deviceTokenWebPush::deviceTokenWebPush()
    : endpoint_()
    , p256dh_base64url_()
    , auth_base64url_()
{}

deviceTokenWebPush::deviceTokenWebPush(std::string const &endpoint_,
                                       std::string const &p256dh_base64url_, std::string const &auth_base64url_)
    : endpoint_(std::move(endpoint_))
    , p256dh_base64url_(std::move(p256dh_base64url_))
    , auth_base64url_(std::move(auth_base64url_))
{}

const int32_t deviceTokenWebPush::ID;

void deviceTokenWebPush::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenWebPush");
        s.store_field("endpoint", endpoint_);
        s.store_field("p256dh_base64url", p256dh_base64url_);
        s.store_field("auth_base64url", auth_base64url_);
        s.store_class_end();
    }
}

deviceTokenSimplePush::deviceTokenSimplePush()
    : endpoint_()
{}

deviceTokenSimplePush::deviceTokenSimplePush(std::string const &endpoint_)
    : endpoint_(std::move(endpoint_))
{}

const int32_t deviceTokenSimplePush::ID;

void deviceTokenSimplePush::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenSimplePush");
        s.store_field("endpoint", endpoint_);
        s.store_class_end();
    }
}

deviceTokenUbuntuPush::deviceTokenUbuntuPush()
    : token_()
{}

deviceTokenUbuntuPush::deviceTokenUbuntuPush(std::string const &token_)
    : token_(std::move(token_))
{}

const int32_t deviceTokenUbuntuPush::ID;

void deviceTokenUbuntuPush::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenUbuntuPush");
        s.store_field("token", token_);
        s.store_class_end();
    }
}

deviceTokenBlackberryPush::deviceTokenBlackberryPush()
    : token_()
{}

deviceTokenBlackberryPush::deviceTokenBlackberryPush(std::string const &token_)
    : token_(std::move(token_))
{}

const int32_t deviceTokenBlackberryPush::ID;

void deviceTokenBlackberryPush::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenBlackberryPush");
        s.store_field("token", token_);
        s.store_class_end();
    }
}

deviceTokenTizenPush::deviceTokenTizenPush()
    : reg_id_()
{}

deviceTokenTizenPush::deviceTokenTizenPush(std::string const &reg_id_)
    : reg_id_(std::move(reg_id_))
{}

const int32_t deviceTokenTizenPush::ID;

void deviceTokenTizenPush::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deviceTokenTizenPush");
        s.store_field("reg_id", reg_id_);
        s.store_class_end();
    }
}

document::document()
    : file_name_()
    , mime_type_()
    , thumbnail_()
    , document_()
{}

document::document(std::string const &file_name_, std::string const &mime_type_,
                   object_ptr<photoSize> &&thumbnail_, object_ptr<file> &&document_)
    : file_name_(std::move(file_name_))
    , mime_type_(std::move(mime_type_))
    , thumbnail_(std::move(thumbnail_))
    , document_(std::move(document_))
{}

const int32_t document::ID;

void document::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "document");
        s.store_field("file_name", file_name_);
        s.store_field("mime_type", mime_type_);
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        if (document_ == nullptr) {
            s.store_field("document", "null");
        } else {
            document_->store(s, "document");
        }
        s.store_class_end();
    }
}

draftMessage::draftMessage()
    : reply_to_message_id_()
    , input_message_text_()
{}

draftMessage::draftMessage(std::int64_t reply_to_message_id_,
                           object_ptr<InputMessageContent> &&input_message_text_)
    : reply_to_message_id_(reply_to_message_id_)
    , input_message_text_(std::move(input_message_text_))
{}

const int32_t draftMessage::ID;

void draftMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "draftMessage");
        s.store_field("reply_to_message_id", reply_to_message_id_);
        if (input_message_text_ == nullptr) {
            s.store_field("input_message_text", "null");
        } else {
            input_message_text_->store(s, "input_message_text");
        }
        s.store_class_end();
    }
}

error::error()
    : code_()
    , message_()
{}

error::error(int32_t code_, std::string const &message_)
    : code_(code_)
    , message_(std::move(message_))
{}

const int32_t error::ID;

void error::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "error");
        s.store_field("code", code_);
        s.store_field("message", message_);
        s.store_class_end();
    }
}

file::file()
    : id_()
    , size_()
    , expected_size_()
    , local_()
    , remote_()
{}

file::file(int32_t id_, int32_t size_, int32_t expected_size_,
           object_ptr<localFile> &&local_, object_ptr<remoteFile> &&remote_)
    : id_(id_)
    , size_(size_)
    , expected_size_(expected_size_)
    , local_(std::move(local_))
    , remote_(std::move(remote_))
{}

const int32_t file::ID;

void file::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "file");
        s.store_field("id", id_);
        s.store_field("size", size_);
        s.store_field("expected_size", expected_size_);
        if (local_ == nullptr) {
            s.store_field("local", "null");
        } else {
            local_->store(s, "local");
        }
        if (remote_ == nullptr) {
            s.store_field("remote", "null");
        } else {
            remote_->store(s, "remote");
        }
        s.store_class_end();
    }
}

fileTypeNone::fileTypeNone()
{
}

const int32_t fileTypeNone::ID;

void fileTypeNone::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeNone");
        s.store_class_end();
    }
}

fileTypeAnimation::fileTypeAnimation()
{
}

const int32_t fileTypeAnimation::ID;

void fileTypeAnimation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeAnimation");
        s.store_class_end();
    }
}

fileTypeAudio::fileTypeAudio()
{
}

const int32_t fileTypeAudio::ID;

void fileTypeAudio::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeAudio");
        s.store_class_end();
    }
}

fileTypeDocument::fileTypeDocument()
{
}

const int32_t fileTypeDocument::ID;

void fileTypeDocument::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeDocument");
        s.store_class_end();
    }
}

fileTypePhoto::fileTypePhoto()
{
}

const int32_t fileTypePhoto::ID;

void fileTypePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypePhoto");
        s.store_class_end();
    }
}

fileTypeProfilePhoto::fileTypeProfilePhoto()
{
}

const int32_t fileTypeProfilePhoto::ID;

void fileTypeProfilePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeProfilePhoto");
        s.store_class_end();
    }
}

fileTypeSecret::fileTypeSecret()
{
}

const int32_t fileTypeSecret::ID;

void fileTypeSecret::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeSecret");
        s.store_class_end();
    }
}

fileTypeSticker::fileTypeSticker()
{
}

const int32_t fileTypeSticker::ID;

void fileTypeSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeSticker");
        s.store_class_end();
    }
}

fileTypeThumbnail::fileTypeThumbnail()
{
}

const int32_t fileTypeThumbnail::ID;

void fileTypeThumbnail::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeThumbnail");
        s.store_class_end();
    }
}

fileTypeUnknown::fileTypeUnknown()
{
}

const int32_t fileTypeUnknown::ID;

void fileTypeUnknown::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeUnknown");
        s.store_class_end();
    }
}

fileTypeVideo::fileTypeVideo()
{
}

const int32_t fileTypeVideo::ID;

void fileTypeVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeVideo");
        s.store_class_end();
    }
}

fileTypeVideoNote::fileTypeVideoNote()
{
}

const int32_t fileTypeVideoNote::ID;

void fileTypeVideoNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeVideoNote");
        s.store_class_end();
    }
}

fileTypeVoiceNote::fileTypeVoiceNote()
{
}

const int32_t fileTypeVoiceNote::ID;

void fileTypeVoiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeVoiceNote");
        s.store_class_end();
    }
}

fileTypeWallpaper::fileTypeWallpaper()
{
}

const int32_t fileTypeWallpaper::ID;

void fileTypeWallpaper::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeWallpaper");
        s.store_class_end();
    }
}

fileTypeSecretThumbnail::fileTypeSecretThumbnail()
{
}

const int32_t fileTypeSecretThumbnail::ID;

void fileTypeSecretThumbnail::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "fileTypeSecretThumbnail");
        s.store_class_end();
    }
}

formattedText::formattedText()
    : text_()
    , entities_()
{}

formattedText::formattedText(std::string const &text_,
                             std::vector<object_ptr<textEntity>> &&entities_)
    : text_(std::move(text_))
    , entities_(std::move(entities_))
{}

const int32_t formattedText::ID;

void formattedText::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "formattedText");
        s.store_field("text", text_);
        {
            const std::vector<object_ptr<textEntity>> &v = entities_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("entities", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

foundMessages::foundMessages()
    : messages_()
    , next_from_search_id_()
{}

foundMessages::foundMessages(std::vector<object_ptr<message>> &&messages_,
                             std::int64_t next_from_search_id_)
    : messages_(std::move(messages_))
    , next_from_search_id_(next_from_search_id_)
{}

const int32_t foundMessages::ID;

void foundMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "foundMessages");
        {
            const std::vector<object_ptr<message>> &v = messages_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("messages", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("next_from_search_id", next_from_search_id_);
        s.store_class_end();
    }
}

game::game()
    : id_()
    , short_name_()
    , title_()
    , text_()
    , description_()
    , photo_()
    , animation_()
{}

game::game(std::int64_t id_, std::string const &short_name_, std::string const &title_,
           object_ptr<formattedText> &&text_, std::string const &description_, object_ptr<photo> &&photo_,
           object_ptr<animation> &&animation_)
    : id_(id_)
    , short_name_(std::move(short_name_))
    , title_(std::move(title_))
    , text_(std::move(text_))
    , description_(std::move(description_))
    , photo_(std::move(photo_))
    , animation_(std::move(animation_))
{}

const int32_t game::ID;

void game::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "game");
        s.store_field("id", id_);
        s.store_field("short_name", short_name_);
        s.store_field("title", title_);
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_field("description", description_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        if (animation_ == nullptr) {
            s.store_field("animation", "null");
        } else {
            animation_->store(s, "animation");
        }
        s.store_class_end();
    }
}

gameHighScore::gameHighScore()
    : position_()
    , user_id_()
    , score_()
{}

gameHighScore::gameHighScore(int32_t position_, int32_t user_id_, int32_t score_)
    : position_(position_)
    , user_id_(user_id_)
    , score_(score_)
{}

const int32_t gameHighScore::ID;

void gameHighScore::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "gameHighScore");
        s.store_field("position", position_);
        s.store_field("user_id", user_id_);
        s.store_field("score", score_);
        s.store_class_end();
    }
}

gameHighScores::gameHighScores()
    : scores_()
{}

gameHighScores::gameHighScores(std::vector<object_ptr<gameHighScore>> &&scores_)
    : scores_(std::move(scores_))
{}

const int32_t gameHighScores::ID;

void gameHighScores::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "gameHighScores");
        {
            const std::vector<object_ptr<gameHighScore>> &v = scores_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("scores", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

hashtags::hashtags()
    : hashtags_()
{}

hashtags::hashtags(std::vector<std::string> &&hashtags_)
    : hashtags_(std::move(hashtags_))
{}

const int32_t hashtags::ID;

void hashtags::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "hashtags");
        {
            const std::vector<std::string> &v = hashtags_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("hashtags", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

importedContacts::importedContacts()
    : user_ids_()
    , importer_count_()
{}

importedContacts::importedContacts(std::vector<int32_t> &&user_ids_,
                                   std::vector<int32_t> &&importer_count_)
    : user_ids_(std::move(user_ids_))
    , importer_count_(std::move(importer_count_))
{}

const int32_t importedContacts::ID;

void importedContacts::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "importedContacts");
        {
            const std::vector<int32_t> &v = user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        {
            const std::vector<int32_t> &v = importer_count_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("importer_count", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

inlineKeyboardButton::inlineKeyboardButton()
    : text_()
    , type_()
{}

inlineKeyboardButton::inlineKeyboardButton(std::string const &text_,
                                           object_ptr<InlineKeyboardButtonType> &&type_)
    : text_(std::move(text_))
    , type_(std::move(type_))
{}

const int32_t inlineKeyboardButton::ID;

void inlineKeyboardButton::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineKeyboardButton");
        s.store_field("text", text_);
        if (type_ == nullptr) {
            s.store_field("type", "null");
        } else {
            type_->store(s, "type");
        }
        s.store_class_end();
    }
}

inlineKeyboardButtonTypeUrl::inlineKeyboardButtonTypeUrl()
    : url_()
{}

inlineKeyboardButtonTypeUrl::inlineKeyboardButtonTypeUrl(std::string const &url_)
    : url_(std::move(url_))
{}

const int32_t inlineKeyboardButtonTypeUrl::ID;

void inlineKeyboardButtonTypeUrl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineKeyboardButtonTypeUrl");
        s.store_field("url", url_);
        s.store_class_end();
    }
}

inlineKeyboardButtonTypeCallback::inlineKeyboardButtonTypeCallback()
    : data_()
{}

inlineKeyboardButtonTypeCallback::inlineKeyboardButtonTypeCallback(std::string const &data_)
    : data_(std::move(data_))
{}

const int32_t inlineKeyboardButtonTypeCallback::ID;

void inlineKeyboardButtonTypeCallback::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineKeyboardButtonTypeCallback");
        s.store_bytes_field("data", data_);
        s.store_class_end();
    }
}

inlineKeyboardButtonTypeCallbackGame::inlineKeyboardButtonTypeCallbackGame()
{
}

const int32_t inlineKeyboardButtonTypeCallbackGame::ID;

void inlineKeyboardButtonTypeCallbackGame::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineKeyboardButtonTypeCallbackGame");
        s.store_class_end();
    }
}

inlineKeyboardButtonTypeSwitchInline::inlineKeyboardButtonTypeSwitchInline()
    : query_()
    , in_current_chat_()
{}

inlineKeyboardButtonTypeSwitchInline::inlineKeyboardButtonTypeSwitchInline(
    std::string const &query_, bool in_current_chat_)
    : query_(std::move(query_))
    , in_current_chat_(in_current_chat_)
{}

const int32_t inlineKeyboardButtonTypeSwitchInline::ID;

void inlineKeyboardButtonTypeSwitchInline::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineKeyboardButtonTypeSwitchInline");
        s.store_field("query", query_);
        s.store_field("in_current_chat", in_current_chat_);
        s.store_class_end();
    }
}

inlineKeyboardButtonTypeBuy::inlineKeyboardButtonTypeBuy()
{
}

const int32_t inlineKeyboardButtonTypeBuy::ID;

void inlineKeyboardButtonTypeBuy::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineKeyboardButtonTypeBuy");
        s.store_class_end();
    }
}

inlineQueryResultArticle::inlineQueryResultArticle()
    : id_()
    , url_()
    , hide_url_()
    , title_()
    , description_()
    , thumbnail_()
{}

inlineQueryResultArticle::inlineQueryResultArticle(std::string const &id_, std::string const &url_,
                                                   bool hide_url_, std::string const &title_, std::string const &description_,
                                                   object_ptr<photoSize> &&thumbnail_)
    : id_(std::move(id_))
    , url_(std::move(url_))
    , hide_url_(hide_url_)
    , title_(std::move(title_))
    , description_(std::move(description_))
    , thumbnail_(std::move(thumbnail_))
{}

const int32_t inlineQueryResultArticle::ID;

void inlineQueryResultArticle::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultArticle");
        s.store_field("id", id_);
        s.store_field("url", url_);
        s.store_field("hide_url", hide_url_);
        s.store_field("title", title_);
        s.store_field("description", description_);
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        s.store_class_end();
    }
}

inlineQueryResultContact::inlineQueryResultContact()
    : id_()
    , contact_()
    , thumbnail_()
{}

inlineQueryResultContact::inlineQueryResultContact(std::string const &id_,
                                                   object_ptr<contact> &&contact_, object_ptr<photoSize> &&thumbnail_)
    : id_(std::move(id_))
    , contact_(std::move(contact_))
    , thumbnail_(std::move(thumbnail_))
{}

const int32_t inlineQueryResultContact::ID;

void inlineQueryResultContact::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultContact");
        s.store_field("id", id_);
        if (contact_ == nullptr) {
            s.store_field("contact", "null");
        } else {
            contact_->store(s, "contact");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        s.store_class_end();
    }
}

inlineQueryResultLocation::inlineQueryResultLocation()
    : id_()
    , location_()
    , title_()
    , thumbnail_()
{}

inlineQueryResultLocation::inlineQueryResultLocation(std::string const &id_,
                                                     object_ptr<location> &&location_, std::string const &title_, object_ptr<photoSize> &&thumbnail_)
    : id_(std::move(id_))
    , location_(std::move(location_))
    , title_(std::move(title_))
    , thumbnail_(std::move(thumbnail_))
{}

const int32_t inlineQueryResultLocation::ID;

void inlineQueryResultLocation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultLocation");
        s.store_field("id", id_);
        if (location_ == nullptr) {
            s.store_field("location", "null");
        } else {
            location_->store(s, "location");
        }
        s.store_field("title", title_);
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        s.store_class_end();
    }
}

inlineQueryResultVenue::inlineQueryResultVenue()
    : id_()
    , venue_()
    , thumbnail_()
{}

inlineQueryResultVenue::inlineQueryResultVenue(std::string const &id_, object_ptr<venue> &&venue_,
                                               object_ptr<photoSize> &&thumbnail_)
    : id_(std::move(id_))
    , venue_(std::move(venue_))
    , thumbnail_(std::move(thumbnail_))
{}

const int32_t inlineQueryResultVenue::ID;

void inlineQueryResultVenue::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultVenue");
        s.store_field("id", id_);
        if (venue_ == nullptr) {
            s.store_field("venue", "null");
        } else {
            venue_->store(s, "venue");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        s.store_class_end();
    }
}

inlineQueryResultGame::inlineQueryResultGame()
    : id_()
    , game_()
{}

inlineQueryResultGame::inlineQueryResultGame(std::string const &id_, object_ptr<game> &&game_)
    : id_(std::move(id_))
    , game_(std::move(game_))
{}

const int32_t inlineQueryResultGame::ID;

void inlineQueryResultGame::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultGame");
        s.store_field("id", id_);
        if (game_ == nullptr) {
            s.store_field("game", "null");
        } else {
            game_->store(s, "game");
        }
        s.store_class_end();
    }
}

inlineQueryResultAnimation::inlineQueryResultAnimation()
    : id_()
    , animation_()
    , title_()
{}

inlineQueryResultAnimation::inlineQueryResultAnimation(std::string const &id_,
                                                       object_ptr<animation> &&animation_, std::string const &title_)
    : id_(std::move(id_))
    , animation_(std::move(animation_))
    , title_(std::move(title_))
{}

const int32_t inlineQueryResultAnimation::ID;

void inlineQueryResultAnimation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultAnimation");
        s.store_field("id", id_);
        if (animation_ == nullptr) {
            s.store_field("animation", "null");
        } else {
            animation_->store(s, "animation");
        }
        s.store_field("title", title_);
        s.store_class_end();
    }
}

inlineQueryResultAudio::inlineQueryResultAudio()
    : id_()
    , audio_()
{}

inlineQueryResultAudio::inlineQueryResultAudio(std::string const &id_, object_ptr<audio> &&audio_)
    : id_(std::move(id_))
    , audio_(std::move(audio_))
{}

const int32_t inlineQueryResultAudio::ID;

void inlineQueryResultAudio::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultAudio");
        s.store_field("id", id_);
        if (audio_ == nullptr) {
            s.store_field("audio", "null");
        } else {
            audio_->store(s, "audio");
        }
        s.store_class_end();
    }
}

inlineQueryResultDocument::inlineQueryResultDocument()
    : id_()
    , document_()
    , title_()
    , description_()
{}

inlineQueryResultDocument::inlineQueryResultDocument(std::string const &id_,
                                                     object_ptr<document> &&document_, std::string const &title_, std::string const &description_)
    : id_(std::move(id_))
    , document_(std::move(document_))
    , title_(std::move(title_))
    , description_(std::move(description_))
{}

const int32_t inlineQueryResultDocument::ID;

void inlineQueryResultDocument::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultDocument");
        s.store_field("id", id_);
        if (document_ == nullptr) {
            s.store_field("document", "null");
        } else {
            document_->store(s, "document");
        }
        s.store_field("title", title_);
        s.store_field("description", description_);
        s.store_class_end();
    }
}

inlineQueryResultPhoto::inlineQueryResultPhoto()
    : id_()
    , photo_()
    , title_()
    , description_()
{}

inlineQueryResultPhoto::inlineQueryResultPhoto(std::string const &id_, object_ptr<photo> &&photo_,
                                               std::string const &title_, std::string const &description_)
    : id_(std::move(id_))
    , photo_(std::move(photo_))
    , title_(std::move(title_))
    , description_(std::move(description_))
{}

const int32_t inlineQueryResultPhoto::ID;

void inlineQueryResultPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultPhoto");
        s.store_field("id", id_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_field("title", title_);
        s.store_field("description", description_);
        s.store_class_end();
    }
}

inlineQueryResultSticker::inlineQueryResultSticker()
    : id_()
    , sticker_()
{}

inlineQueryResultSticker::inlineQueryResultSticker(std::string const &id_,
                                                   object_ptr<sticker> &&sticker_)
    : id_(std::move(id_))
    , sticker_(std::move(sticker_))
{}

const int32_t inlineQueryResultSticker::ID;

void inlineQueryResultSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultSticker");
        s.store_field("id", id_);
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

inlineQueryResultVideo::inlineQueryResultVideo()
    : id_()
    , video_()
    , title_()
    , description_()
{}

inlineQueryResultVideo::inlineQueryResultVideo(std::string const &id_, object_ptr<video> &&video_,
                                               std::string const &title_, std::string const &description_)
    : id_(std::move(id_))
    , video_(std::move(video_))
    , title_(std::move(title_))
    , description_(std::move(description_))
{}

const int32_t inlineQueryResultVideo::ID;

void inlineQueryResultVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultVideo");
        s.store_field("id", id_);
        if (video_ == nullptr) {
            s.store_field("video", "null");
        } else {
            video_->store(s, "video");
        }
        s.store_field("title", title_);
        s.store_field("description", description_);
        s.store_class_end();
    }
}

inlineQueryResultVoiceNote::inlineQueryResultVoiceNote()
    : id_()
    , voice_note_()
    , title_()
{}

inlineQueryResultVoiceNote::inlineQueryResultVoiceNote(std::string const &id_,
                                                       object_ptr<voiceNote> &&voice_note_, std::string const &title_)
    : id_(std::move(id_))
    , voice_note_(std::move(voice_note_))
    , title_(std::move(title_))
{}

const int32_t inlineQueryResultVoiceNote::ID;

void inlineQueryResultVoiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResultVoiceNote");
        s.store_field("id", id_);
        if (voice_note_ == nullptr) {
            s.store_field("voice_note", "null");
        } else {
            voice_note_->store(s, "voice_note");
        }
        s.store_field("title", title_);
        s.store_class_end();
    }
}

inlineQueryResults::inlineQueryResults()
    : inline_query_id_()
    , next_offset_()
    , results_()
    , switch_pm_text_()
    , switch_pm_parameter_()
{}

inlineQueryResults::inlineQueryResults(std::int64_t inline_query_id_,
                                       std::string const &next_offset_, std::vector<object_ptr<InlineQueryResult>> &&results_,
                                       std::string const &switch_pm_text_, std::string const &switch_pm_parameter_)
    : inline_query_id_(inline_query_id_)
    , next_offset_(std::move(next_offset_))
    , results_(std::move(results_))
    , switch_pm_text_(std::move(switch_pm_text_))
    , switch_pm_parameter_(std::move(switch_pm_parameter_))
{}

const int32_t inlineQueryResults::ID;

void inlineQueryResults::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inlineQueryResults");
        s.store_field("inline_query_id", inline_query_id_);
        s.store_field("next_offset", next_offset_);
        {
            const std::vector<object_ptr<InlineQueryResult>> &v = results_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("results", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("switch_pm_text", switch_pm_text_);
        s.store_field("switch_pm_parameter", switch_pm_parameter_);
        s.store_class_end();
    }
}

inputCredentialsSaved::inputCredentialsSaved()
    : saved_credentials_id_()
{}

inputCredentialsSaved::inputCredentialsSaved(std::string const &saved_credentials_id_)
    : saved_credentials_id_(std::move(saved_credentials_id_))
{}

const int32_t inputCredentialsSaved::ID;

void inputCredentialsSaved::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputCredentialsSaved");
        s.store_field("saved_credentials_id", saved_credentials_id_);
        s.store_class_end();
    }
}

inputCredentialsNew::inputCredentialsNew()
    : data_()
    , allow_save_()
{}

inputCredentialsNew::inputCredentialsNew(std::string const &data_, bool allow_save_)
    : data_(std::move(data_))
    , allow_save_(allow_save_)
{}

const int32_t inputCredentialsNew::ID;

void inputCredentialsNew::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputCredentialsNew");
        s.store_field("data", data_);
        s.store_field("allow_save", allow_save_);
        s.store_class_end();
    }
}

inputCredentialsAndroidPay::inputCredentialsAndroidPay()
    : data_()
{}

inputCredentialsAndroidPay::inputCredentialsAndroidPay(std::string const &data_)
    : data_(std::move(data_))
{}

const int32_t inputCredentialsAndroidPay::ID;

void inputCredentialsAndroidPay::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputCredentialsAndroidPay");
        s.store_field("data", data_);
        s.store_class_end();
    }
}

inputCredentialsApplePay::inputCredentialsApplePay()
    : data_()
{}

inputCredentialsApplePay::inputCredentialsApplePay(std::string const &data_)
    : data_(std::move(data_))
{}

const int32_t inputCredentialsApplePay::ID;

void inputCredentialsApplePay::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputCredentialsApplePay");
        s.store_field("data", data_);
        s.store_class_end();
    }
}

inputFileId::inputFileId()
    : id_()
{}

inputFileId::inputFileId(int32_t id_)
    : id_(id_)
{}

const int32_t inputFileId::ID;

void inputFileId::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputFileId");
        s.store_field("id", id_);
        s.store_class_end();
    }
}

inputFileRemote::inputFileRemote()
    : id_()
{}

inputFileRemote::inputFileRemote(std::string const &id_)
    : id_(std::move(id_))
{}

const int32_t inputFileRemote::ID;

void inputFileRemote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputFileRemote");
        s.store_field("id", id_);
        s.store_class_end();
    }
}

inputFileLocal::inputFileLocal()
    : path_()
{}

inputFileLocal::inputFileLocal(std::string const &path_)
    : path_(std::move(path_))
{}

const int32_t inputFileLocal::ID;

void inputFileLocal::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputFileLocal");
        s.store_field("path", path_);
        s.store_class_end();
    }
}

inputFileGenerated::inputFileGenerated()
    : original_path_()
    , conversion_()
    , expected_size_()
{}

inputFileGenerated::inputFileGenerated(std::string const &original_path_,
                                       std::string const &conversion_, int32_t expected_size_)
    : original_path_(std::move(original_path_))
    , conversion_(std::move(conversion_))
    , expected_size_(expected_size_)
{}

const int32_t inputFileGenerated::ID;

void inputFileGenerated::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputFileGenerated");
        s.store_field("original_path", original_path_);
        s.store_field("conversion", conversion_);
        s.store_field("expected_size", expected_size_);
        s.store_class_end();
    }
}

inputInlineQueryResultAnimatedGif::inputInlineQueryResultAnimatedGif()
    : id_()
    , title_()
    , thumbnail_url_()
    , gif_url_()
    , gif_duration_()
    , gif_width_()
    , gif_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultAnimatedGif::inputInlineQueryResultAnimatedGif(std::string const &id_,
                                                                     std::string const &title_, std::string const &thumbnail_url_, std::string const &gif_url_,
                                                                     int32_t gif_duration_, int32_t gif_width_, int32_t gif_height_,
                                                                     object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , title_(std::move(title_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , gif_url_(std::move(gif_url_))
    , gif_duration_(gif_duration_)
    , gif_width_(gif_width_)
    , gif_height_(gif_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultAnimatedGif::ID;

void inputInlineQueryResultAnimatedGif::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultAnimatedGif");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("gif_url", gif_url_);
        s.store_field("gif_duration", gif_duration_);
        s.store_field("gif_width", gif_width_);
        s.store_field("gif_height", gif_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultAnimatedMpeg4::inputInlineQueryResultAnimatedMpeg4()
    : id_()
    , title_()
    , thumbnail_url_()
    , mpeg4_url_()
    , mpeg4_duration_()
    , mpeg4_width_()
    , mpeg4_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultAnimatedMpeg4::inputInlineQueryResultAnimatedMpeg4(std::string const &id_,
                                                                         std::string const &title_, std::string const &thumbnail_url_, std::string const &mpeg4_url_,
                                                                         int32_t mpeg4_duration_, int32_t mpeg4_width_, int32_t mpeg4_height_,
                                                                         object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , title_(std::move(title_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , mpeg4_url_(std::move(mpeg4_url_))
    , mpeg4_duration_(mpeg4_duration_)
    , mpeg4_width_(mpeg4_width_)
    , mpeg4_height_(mpeg4_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultAnimatedMpeg4::ID;

void inputInlineQueryResultAnimatedMpeg4::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultAnimatedMpeg4");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("mpeg4_url", mpeg4_url_);
        s.store_field("mpeg4_duration", mpeg4_duration_);
        s.store_field("mpeg4_width", mpeg4_width_);
        s.store_field("mpeg4_height", mpeg4_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultArticle::inputInlineQueryResultArticle()
    : id_()
    , url_()
    , hide_url_()
    , title_()
    , description_()
    , thumbnail_url_()
    , thumbnail_width_()
    , thumbnail_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultArticle::inputInlineQueryResultArticle(std::string const &id_,
                                                             std::string const &url_, bool hide_url_, std::string const &title_, std::string const &description_,
                                                             std::string const &thumbnail_url_, int32_t thumbnail_width_, int32_t thumbnail_height_,
                                                             object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , url_(std::move(url_))
    , hide_url_(hide_url_)
    , title_(std::move(title_))
    , description_(std::move(description_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , thumbnail_width_(thumbnail_width_)
    , thumbnail_height_(thumbnail_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultArticle::ID;

void inputInlineQueryResultArticle::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultArticle");
        s.store_field("id", id_);
        s.store_field("url", url_);
        s.store_field("hide_url", hide_url_);
        s.store_field("title", title_);
        s.store_field("description", description_);
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("thumbnail_width", thumbnail_width_);
        s.store_field("thumbnail_height", thumbnail_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultAudio::inputInlineQueryResultAudio()
    : id_()
    , title_()
    , performer_()
    , audio_url_()
    , audio_duration_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultAudio::inputInlineQueryResultAudio(std::string const &id_,
                                                         std::string const &title_, std::string const &performer_, std::string const &audio_url_,
                                                         int32_t audio_duration_, object_ptr<ReplyMarkup> &&reply_markup_,
                                                         object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , title_(std::move(title_))
    , performer_(std::move(performer_))
    , audio_url_(std::move(audio_url_))
    , audio_duration_(audio_duration_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultAudio::ID;

void inputInlineQueryResultAudio::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultAudio");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("performer", performer_);
        s.store_field("audio_url", audio_url_);
        s.store_field("audio_duration", audio_duration_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultContact::inputInlineQueryResultContact()
    : id_()
    , contact_()
    , thumbnail_url_()
    , thumbnail_width_()
    , thumbnail_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultContact::inputInlineQueryResultContact(std::string const &id_,
                                                             object_ptr<contact> &&contact_, std::string const &thumbnail_url_, int32_t thumbnail_width_,
                                                             int32_t thumbnail_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                                             object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , contact_(std::move(contact_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , thumbnail_width_(thumbnail_width_)
    , thumbnail_height_(thumbnail_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultContact::ID;

void inputInlineQueryResultContact::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultContact");
        s.store_field("id", id_);
        if (contact_ == nullptr) {
            s.store_field("contact", "null");
        } else {
            contact_->store(s, "contact");
        }
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("thumbnail_width", thumbnail_width_);
        s.store_field("thumbnail_height", thumbnail_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultDocument::inputInlineQueryResultDocument()
    : id_()
    , title_()
    , description_()
    , document_url_()
    , mime_type_()
    , thumbnail_url_()
    , thumbnail_width_()
    , thumbnail_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultDocument::inputInlineQueryResultDocument(std::string const &id_,
                                                               std::string const &title_, std::string const &description_, std::string const &document_url_,
                                                               std::string const &mime_type_, std::string const &thumbnail_url_, int32_t thumbnail_width_,
                                                               int32_t thumbnail_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                                               object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , title_(std::move(title_))
    , description_(std::move(description_))
    , document_url_(std::move(document_url_))
    , mime_type_(std::move(mime_type_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , thumbnail_width_(thumbnail_width_)
    , thumbnail_height_(thumbnail_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultDocument::ID;

void inputInlineQueryResultDocument::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultDocument");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("description", description_);
        s.store_field("document_url", document_url_);
        s.store_field("mime_type", mime_type_);
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("thumbnail_width", thumbnail_width_);
        s.store_field("thumbnail_height", thumbnail_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultGame::inputInlineQueryResultGame()
    : id_()
    , game_short_name_()
    , reply_markup_()
{}

inputInlineQueryResultGame::inputInlineQueryResultGame(std::string const &id_,
                                                       std::string const &game_short_name_, object_ptr<ReplyMarkup> &&reply_markup_)
    : id_(std::move(id_))
    , game_short_name_(std::move(game_short_name_))
    , reply_markup_(std::move(reply_markup_))
{}

const int32_t inputInlineQueryResultGame::ID;

void inputInlineQueryResultGame::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultGame");
        s.store_field("id", id_);
        s.store_field("game_short_name", game_short_name_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultLocation::inputInlineQueryResultLocation()
    : id_()
    , location_()
    , live_period_()
    , title_()
    , thumbnail_url_()
    , thumbnail_width_()
    , thumbnail_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultLocation::inputInlineQueryResultLocation(std::string const &id_,
                                                               object_ptr<location> &&location_, int32_t live_period_, std::string const &title_,
                                                               std::string const &thumbnail_url_, int32_t thumbnail_width_, int32_t thumbnail_height_,
                                                               object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , location_(std::move(location_))
    , live_period_(live_period_)
    , title_(std::move(title_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , thumbnail_width_(thumbnail_width_)
    , thumbnail_height_(thumbnail_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultLocation::ID;

void inputInlineQueryResultLocation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultLocation");
        s.store_field("id", id_);
        if (location_ == nullptr) {
            s.store_field("location", "null");
        } else {
            location_->store(s, "location");
        }
        s.store_field("live_period", live_period_);
        s.store_field("title", title_);
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("thumbnail_width", thumbnail_width_);
        s.store_field("thumbnail_height", thumbnail_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultPhoto::inputInlineQueryResultPhoto()
    : id_()
    , title_()
    , description_()
    , thumbnail_url_()
    , photo_url_()
    , photo_width_()
    , photo_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultPhoto::inputInlineQueryResultPhoto(std::string const &id_,
                                                         std::string const &title_, std::string const &description_, std::string const &thumbnail_url_,
                                                         std::string const &photo_url_, int32_t photo_width_, int32_t photo_height_,
                                                         object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , title_(std::move(title_))
    , description_(std::move(description_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , photo_url_(std::move(photo_url_))
    , photo_width_(photo_width_)
    , photo_height_(photo_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultPhoto::ID;

void inputInlineQueryResultPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultPhoto");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("description", description_);
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("photo_url", photo_url_);
        s.store_field("photo_width", photo_width_);
        s.store_field("photo_height", photo_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultSticker::inputInlineQueryResultSticker()
    : id_()
    , thumbnail_url_()
    , sticker_url_()
    , sticker_width_()
    , sticker_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultSticker::inputInlineQueryResultSticker(std::string const &id_,
                                                             std::string const &thumbnail_url_, std::string const &sticker_url_, int32_t sticker_width_,
                                                             int32_t sticker_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                                             object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , sticker_url_(std::move(sticker_url_))
    , sticker_width_(sticker_width_)
    , sticker_height_(sticker_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultSticker::ID;

void inputInlineQueryResultSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultSticker");
        s.store_field("id", id_);
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("sticker_url", sticker_url_);
        s.store_field("sticker_width", sticker_width_);
        s.store_field("sticker_height", sticker_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultVenue::inputInlineQueryResultVenue()
    : id_()
    , venue_()
    , thumbnail_url_()
    , thumbnail_width_()
    , thumbnail_height_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultVenue::inputInlineQueryResultVenue(std::string const &id_,
                                                         object_ptr<venue> &&venue_, std::string const &thumbnail_url_, int32_t thumbnail_width_,
                                                         int32_t thumbnail_height_, object_ptr<ReplyMarkup> &&reply_markup_,
                                                         object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , venue_(std::move(venue_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , thumbnail_width_(thumbnail_width_)
    , thumbnail_height_(thumbnail_height_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultVenue::ID;

void inputInlineQueryResultVenue::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultVenue");
        s.store_field("id", id_);
        if (venue_ == nullptr) {
            s.store_field("venue", "null");
        } else {
            venue_->store(s, "venue");
        }
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("thumbnail_width", thumbnail_width_);
        s.store_field("thumbnail_height", thumbnail_height_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultVideo::inputInlineQueryResultVideo()
    : id_()
    , title_()
    , description_()
    , thumbnail_url_()
    , video_url_()
    , mime_type_()
    , video_width_()
    , video_height_()
    , video_duration_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultVideo::inputInlineQueryResultVideo(std::string const &id_,
                                                         std::string const &title_, std::string const &description_, std::string const &thumbnail_url_,
                                                         std::string const &video_url_, std::string const &mime_type_, int32_t video_width_,
                                                         int32_t video_height_, int32_t video_duration_, object_ptr<ReplyMarkup> &&reply_markup_,
                                                         object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , title_(std::move(title_))
    , description_(std::move(description_))
    , thumbnail_url_(std::move(thumbnail_url_))
    , video_url_(std::move(video_url_))
    , mime_type_(std::move(mime_type_))
    , video_width_(video_width_)
    , video_height_(video_height_)
    , video_duration_(video_duration_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultVideo::ID;

void inputInlineQueryResultVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultVideo");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("description", description_);
        s.store_field("thumbnail_url", thumbnail_url_);
        s.store_field("video_url", video_url_);
        s.store_field("mime_type", mime_type_);
        s.store_field("video_width", video_width_);
        s.store_field("video_height", video_height_);
        s.store_field("video_duration", video_duration_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputInlineQueryResultVoiceNote::inputInlineQueryResultVoiceNote()
    : id_()
    , title_()
    , voice_note_url_()
    , voice_note_duration_()
    , reply_markup_()
    , input_message_content_()
{}

inputInlineQueryResultVoiceNote::inputInlineQueryResultVoiceNote(std::string const &id_,
                                                                 std::string const &title_, std::string const &voice_note_url_, int32_t voice_note_duration_,
                                                                 object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_)
    : id_(std::move(id_))
    , title_(std::move(title_))
    , voice_note_url_(std::move(voice_note_url_))
    , voice_note_duration_(voice_note_duration_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t inputInlineQueryResultVoiceNote::ID;

void inputInlineQueryResultVoiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputInlineQueryResultVoiceNote");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("voice_note_url", voice_note_url_);
        s.store_field("voice_note_duration", voice_note_duration_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

inputMessageText::inputMessageText()
    : text_()
    , disable_web_page_preview_()
    , clear_draft_()
{}

inputMessageText::inputMessageText(object_ptr<formattedText> &&text_,
                                   bool disable_web_page_preview_, bool clear_draft_)
    : text_(std::move(text_))
    , disable_web_page_preview_(disable_web_page_preview_)
    , clear_draft_(clear_draft_)
{}

const int32_t inputMessageText::ID;

void inputMessageText::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageText");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_field("disable_web_page_preview", disable_web_page_preview_);
        s.store_field("clear_draft", clear_draft_);
        s.store_class_end();
    }
}

inputMessageAnimation::inputMessageAnimation()
    : animation_()
    , thumbnail_()
    , duration_()
    , width_()
    , height_()
    , caption_()
{}

inputMessageAnimation::inputMessageAnimation(object_ptr<InputFile> &&animation_,
                                             object_ptr<inputThumbnail> &&thumbnail_, int32_t duration_, int32_t width_,
                                             int32_t height_, object_ptr<formattedText> &&caption_)
    : animation_(std::move(animation_))
    , thumbnail_(std::move(thumbnail_))
    , duration_(duration_)
    , width_(width_)
    , height_(height_)
    , caption_(std::move(caption_))
{}

const int32_t inputMessageAnimation::ID;

void inputMessageAnimation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageAnimation");
        if (animation_ == nullptr) {
            s.store_field("animation", "null");
        } else {
            animation_->store(s, "animation");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        s.store_field("duration", duration_);
        s.store_field("width", width_);
        s.store_field("height", height_);
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

inputMessageAudio::inputMessageAudio()
    : audio_()
    , album_cover_thumbnail_()
    , duration_()
    , title_()
    , performer_()
    , caption_()
{}

inputMessageAudio::inputMessageAudio(object_ptr<InputFile> &&audio_,
                                     object_ptr<inputThumbnail> &&album_cover_thumbnail_, int32_t duration_,
                                     std::string const &title_, std::string const &performer_, object_ptr<formattedText> &&caption_)
    : audio_(std::move(audio_))
    , album_cover_thumbnail_(std::move(album_cover_thumbnail_))
    , duration_(duration_)
    , title_(std::move(title_))
    , performer_(std::move(performer_))
    , caption_(std::move(caption_))
{}

const int32_t inputMessageAudio::ID;

void inputMessageAudio::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageAudio");
        if (audio_ == nullptr) {
            s.store_field("audio", "null");
        } else {
            audio_->store(s, "audio");
        }
        if (album_cover_thumbnail_ == nullptr) {
            s.store_field("album_cover_thumbnail", "null");
        } else {
            album_cover_thumbnail_->store(s, "album_cover_thumbnail");
        }
        s.store_field("duration", duration_);
        s.store_field("title", title_);
        s.store_field("performer", performer_);
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

inputMessageDocument::inputMessageDocument()
    : document_()
    , thumbnail_()
    , caption_()
{}

inputMessageDocument::inputMessageDocument(object_ptr<InputFile> &&document_,
                                           object_ptr<inputThumbnail> &&thumbnail_, object_ptr<formattedText> &&caption_)
    : document_(std::move(document_))
    , thumbnail_(std::move(thumbnail_))
    , caption_(std::move(caption_))
{}

const int32_t inputMessageDocument::ID;

void inputMessageDocument::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageDocument");
        if (document_ == nullptr) {
            s.store_field("document", "null");
        } else {
            document_->store(s, "document");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

inputMessagePhoto::inputMessagePhoto()
    : photo_()
    , thumbnail_()
    , added_sticker_file_ids_()
    , width_()
    , height_()
    , caption_()
    , ttl_()
{}

inputMessagePhoto::inputMessagePhoto(object_ptr<InputFile> &&photo_,
                                     object_ptr<inputThumbnail> &&thumbnail_, std::vector<int32_t> &&added_sticker_file_ids_,
                                     int32_t width_, int32_t height_, object_ptr<formattedText> &&caption_, int32_t ttl_)
    : photo_(std::move(photo_))
    , thumbnail_(std::move(thumbnail_))
    , added_sticker_file_ids_(std::move(added_sticker_file_ids_))
    , width_(width_)
    , height_(height_)
    , caption_(std::move(caption_))
    , ttl_(ttl_)
{}

const int32_t inputMessagePhoto::ID;

void inputMessagePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessagePhoto");
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        {
            const std::vector<int32_t> &v = added_sticker_file_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("added_sticker_file_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("width", width_);
        s.store_field("height", height_);
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_field("ttl", ttl_);
        s.store_class_end();
    }
}

inputMessageSticker::inputMessageSticker()
    : sticker_()
    , thumbnail_()
    , width_()
    , height_()
{}

inputMessageSticker::inputMessageSticker(object_ptr<InputFile> &&sticker_,
                                         object_ptr<inputThumbnail> &&thumbnail_, int32_t width_, int32_t height_)
    : sticker_(std::move(sticker_))
    , thumbnail_(std::move(thumbnail_))
    , width_(width_)
    , height_(height_)
{}

const int32_t inputMessageSticker::ID;

void inputMessageSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageSticker");
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        s.store_field("width", width_);
        s.store_field("height", height_);
        s.store_class_end();
    }
}

inputMessageVideo::inputMessageVideo()
    : video_()
    , thumbnail_()
    , added_sticker_file_ids_()
    , duration_()
    , width_()
    , height_()
    , caption_()
    , ttl_()
{}

inputMessageVideo::inputMessageVideo(object_ptr<InputFile> &&video_,
                                     object_ptr<inputThumbnail> &&thumbnail_, std::vector<int32_t> &&added_sticker_file_ids_,
                                     int32_t duration_, int32_t width_, int32_t height_,
                                     object_ptr<formattedText> &&caption_, int32_t ttl_)
    : video_(std::move(video_))
    , thumbnail_(std::move(thumbnail_))
    , added_sticker_file_ids_(std::move(added_sticker_file_ids_))
    , duration_(duration_)
    , width_(width_)
    , height_(height_)
    , caption_(std::move(caption_))
    , ttl_(ttl_)
{}

const int32_t inputMessageVideo::ID;

void inputMessageVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageVideo");
        if (video_ == nullptr) {
            s.store_field("video", "null");
        } else {
            video_->store(s, "video");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        {
            const std::vector<int32_t> &v = added_sticker_file_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("added_sticker_file_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("duration", duration_);
        s.store_field("width", width_);
        s.store_field("height", height_);
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_field("ttl", ttl_);
        s.store_class_end();
    }
}

inputMessageVideoNote::inputMessageVideoNote()
    : video_note_()
    , thumbnail_()
    , duration_()
    , length_()
{}

inputMessageVideoNote::inputMessageVideoNote(object_ptr<InputFile> &&video_note_,
                                             object_ptr<inputThumbnail> &&thumbnail_, int32_t duration_, int32_t length_)
    : video_note_(std::move(video_note_))
    , thumbnail_(std::move(thumbnail_))
    , duration_(duration_)
    , length_(length_)
{}

const int32_t inputMessageVideoNote::ID;

void inputMessageVideoNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageVideoNote");
        if (video_note_ == nullptr) {
            s.store_field("video_note", "null");
        } else {
            video_note_->store(s, "video_note");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        s.store_field("duration", duration_);
        s.store_field("length", length_);
        s.store_class_end();
    }
}

inputMessageVoiceNote::inputMessageVoiceNote()
    : voice_note_()
    , duration_()
    , waveform_()
    , caption_()
{}

inputMessageVoiceNote::inputMessageVoiceNote(object_ptr<InputFile> &&voice_note_,
                                             int32_t duration_, std::string const &waveform_, object_ptr<formattedText> &&caption_)
    : voice_note_(std::move(voice_note_))
    , duration_(duration_)
    , waveform_(std::move(waveform_))
    , caption_(std::move(caption_))
{}

const int32_t inputMessageVoiceNote::ID;

void inputMessageVoiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageVoiceNote");
        if (voice_note_ == nullptr) {
            s.store_field("voice_note", "null");
        } else {
            voice_note_->store(s, "voice_note");
        }
        s.store_field("duration", duration_);
        s.store_bytes_field("waveform", waveform_);
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

inputMessageLocation::inputMessageLocation()
    : location_()
    , live_period_()
{}

inputMessageLocation::inputMessageLocation(object_ptr<location> &&location_,
                                           int32_t live_period_)
    : location_(std::move(location_))
    , live_period_(live_period_)
{}

const int32_t inputMessageLocation::ID;

void inputMessageLocation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageLocation");
        if (location_ == nullptr) {
            s.store_field("location", "null");
        } else {
            location_->store(s, "location");
        }
        s.store_field("live_period", live_period_);
        s.store_class_end();
    }
}

inputMessageVenue::inputMessageVenue()
    : venue_()
{}

inputMessageVenue::inputMessageVenue(object_ptr<venue> &&venue_)
    : venue_(std::move(venue_))
{}

const int32_t inputMessageVenue::ID;

void inputMessageVenue::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageVenue");
        if (venue_ == nullptr) {
            s.store_field("venue", "null");
        } else {
            venue_->store(s, "venue");
        }
        s.store_class_end();
    }
}

inputMessageContact::inputMessageContact()
    : contact_()
{}

inputMessageContact::inputMessageContact(object_ptr<contact> &&contact_)
    : contact_(std::move(contact_))
{}

const int32_t inputMessageContact::ID;

void inputMessageContact::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageContact");
        if (contact_ == nullptr) {
            s.store_field("contact", "null");
        } else {
            contact_->store(s, "contact");
        }
        s.store_class_end();
    }
}

inputMessageGame::inputMessageGame()
    : bot_user_id_()
    , game_short_name_()
{}

inputMessageGame::inputMessageGame(int32_t bot_user_id_, std::string const &game_short_name_)
    : bot_user_id_(bot_user_id_)
    , game_short_name_(std::move(game_short_name_))
{}

const int32_t inputMessageGame::ID;

void inputMessageGame::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageGame");
        s.store_field("bot_user_id", bot_user_id_);
        s.store_field("game_short_name", game_short_name_);
        s.store_class_end();
    }
}

inputMessageInvoice::inputMessageInvoice()
    : invoice_()
    , title_()
    , description_()
    , photo_url_()
    , photo_size_()
    , photo_width_()
    , photo_height_()
    , payload_()
    , provider_token_()
    , provider_data_()
    , start_parameter_()
{}

inputMessageInvoice::inputMessageInvoice(object_ptr<invoice> &&invoice_, std::string const &title_,
                                         std::string const &description_, std::string const &photo_url_, int32_t photo_size_,
                                         int32_t photo_width_, int32_t photo_height_, std::string const &payload_,
                                         std::string const &provider_token_, std::string const &provider_data_,
                                         std::string const &start_parameter_)
    : invoice_(std::move(invoice_))
    , title_(std::move(title_))
    , description_(std::move(description_))
    , photo_url_(std::move(photo_url_))
    , photo_size_(photo_size_)
    , photo_width_(photo_width_)
    , photo_height_(photo_height_)
    , payload_(std::move(payload_))
    , provider_token_(std::move(provider_token_))
    , provider_data_(std::move(provider_data_))
    , start_parameter_(std::move(start_parameter_))
{}

const int32_t inputMessageInvoice::ID;

void inputMessageInvoice::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageInvoice");
        if (invoice_ == nullptr) {
            s.store_field("invoice", "null");
        } else {
            invoice_->store(s, "invoice");
        }
        s.store_field("title", title_);
        s.store_field("description", description_);
        s.store_field("photo_url", photo_url_);
        s.store_field("photo_size", photo_size_);
        s.store_field("photo_width", photo_width_);
        s.store_field("photo_height", photo_height_);
        s.store_bytes_field("payload", payload_);
        s.store_field("provider_token", provider_token_);
        s.store_field("provider_data", provider_data_);
        s.store_field("start_parameter", start_parameter_);
        s.store_class_end();
    }
}

inputMessageForwarded::inputMessageForwarded()
    : from_chat_id_()
    , message_id_()
    , in_game_share_()
{}

inputMessageForwarded::inputMessageForwarded(std::int64_t from_chat_id_, std::int64_t message_id_,
                                             bool in_game_share_)
    : from_chat_id_(from_chat_id_)
    , message_id_(message_id_)
    , in_game_share_(in_game_share_)
{}

const int32_t inputMessageForwarded::ID;

void inputMessageForwarded::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputMessageForwarded");
        s.store_field("from_chat_id", from_chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("in_game_share", in_game_share_);
        s.store_class_end();
    }
}

inputSticker::inputSticker()
    : png_sticker_()
    , emojis_()
    , mask_position_()
{}

inputSticker::inputSticker(object_ptr<InputFile> &&png_sticker_, std::string const &emojis_,
                           object_ptr<maskPosition> &&mask_position_)
    : png_sticker_(std::move(png_sticker_))
    , emojis_(std::move(emojis_))
    , mask_position_(std::move(mask_position_))
{}

const int32_t inputSticker::ID;

void inputSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputSticker");
        if (png_sticker_ == nullptr) {
            s.store_field("png_sticker", "null");
        } else {
            png_sticker_->store(s, "png_sticker");
        }
        s.store_field("emojis", emojis_);
        if (mask_position_ == nullptr) {
            s.store_field("mask_position", "null");
        } else {
            mask_position_->store(s, "mask_position");
        }
        s.store_class_end();
    }
}

inputThumbnail::inputThumbnail()
    : thumbnail_()
    , width_()
    , height_()
{}

inputThumbnail::inputThumbnail(object_ptr<InputFile> &&thumbnail_, int32_t width_,
                               int32_t height_)
    : thumbnail_(std::move(thumbnail_))
    , width_(width_)
    , height_(height_)
{}

const int32_t inputThumbnail::ID;

void inputThumbnail::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "inputThumbnail");
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        s.store_field("width", width_);
        s.store_field("height", height_);
        s.store_class_end();
    }
}

invoice::invoice()
    : currency_()
    , price_parts_()
    , is_test_()
    , need_name_()
    , need_phone_number_()
    , need_email_address_()
    , need_shipping_address_()
    , send_phone_number_to_provider_()
    , send_email_address_to_provider_()
    , is_flexible_()
{}

invoice::invoice(std::string const &currency_,
                 std::vector<object_ptr<labeledPricePart>> &&price_parts_, bool is_test_, bool need_name_,
                 bool need_phone_number_, bool need_email_address_, bool need_shipping_address_,
                 bool send_phone_number_to_provider_, bool send_email_address_to_provider_, bool is_flexible_)
    : currency_(std::move(currency_))
    , price_parts_(std::move(price_parts_))
    , is_test_(is_test_)
    , need_name_(need_name_)
    , need_phone_number_(need_phone_number_)
    , need_email_address_(need_email_address_)
    , need_shipping_address_(need_shipping_address_)
    , send_phone_number_to_provider_(send_phone_number_to_provider_)
    , send_email_address_to_provider_(send_email_address_to_provider_)
    , is_flexible_(is_flexible_)
{}

const int32_t invoice::ID;

void invoice::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "invoice");
        s.store_field("currency", currency_);
        {
            const std::vector<object_ptr<labeledPricePart>> &v = price_parts_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("price_parts", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("is_test", is_test_);
        s.store_field("need_name", need_name_);
        s.store_field("need_phone_number", need_phone_number_);
        s.store_field("need_email_address", need_email_address_);
        s.store_field("need_shipping_address", need_shipping_address_);
        s.store_field("send_phone_number_to_provider", send_phone_number_to_provider_);
        s.store_field("send_email_address_to_provider", send_email_address_to_provider_);
        s.store_field("is_flexible", is_flexible_);
        s.store_class_end();
    }
}

keyboardButton::keyboardButton()
    : text_()
    , type_()
{}

keyboardButton::keyboardButton(std::string const &text_, object_ptr<KeyboardButtonType> &&type_)
    : text_(std::move(text_))
    , type_(std::move(type_))
{}

const int32_t keyboardButton::ID;

void keyboardButton::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "keyboardButton");
        s.store_field("text", text_);
        if (type_ == nullptr) {
            s.store_field("type", "null");
        } else {
            type_->store(s, "type");
        }
        s.store_class_end();
    }
}

keyboardButtonTypeText::keyboardButtonTypeText()
{
}

const int32_t keyboardButtonTypeText::ID;

void keyboardButtonTypeText::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "keyboardButtonTypeText");
        s.store_class_end();
    }
}

keyboardButtonTypeRequestPhoneNumber::keyboardButtonTypeRequestPhoneNumber()
{
}

const int32_t keyboardButtonTypeRequestPhoneNumber::ID;

void keyboardButtonTypeRequestPhoneNumber::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "keyboardButtonTypeRequestPhoneNumber");
        s.store_class_end();
    }
}

keyboardButtonTypeRequestLocation::keyboardButtonTypeRequestLocation()
{
}

const int32_t keyboardButtonTypeRequestLocation::ID;

void keyboardButtonTypeRequestLocation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "keyboardButtonTypeRequestLocation");
        s.store_class_end();
    }
}

labeledPricePart::labeledPricePart()
    : label_()
    , amount_()
{}

labeledPricePart::labeledPricePart(std::string const &label_, std::int64_t amount_)
    : label_(std::move(label_))
    , amount_(amount_)
{}

const int32_t labeledPricePart::ID;

void labeledPricePart::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "labeledPricePart");
        s.store_field("label", label_);
        s.store_field("amount", amount_);
        s.store_class_end();
    }
}

linkStateNone::linkStateNone()
{
}

const int32_t linkStateNone::ID;

void linkStateNone::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "linkStateNone");
        s.store_class_end();
    }
}

linkStateKnowsPhoneNumber::linkStateKnowsPhoneNumber()
{
}

const int32_t linkStateKnowsPhoneNumber::ID;

void linkStateKnowsPhoneNumber::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "linkStateKnowsPhoneNumber");
        s.store_class_end();
    }
}

linkStateIsContact::linkStateIsContact()
{
}

const int32_t linkStateIsContact::ID;

void linkStateIsContact::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "linkStateIsContact");
        s.store_class_end();
    }
}

localFile::localFile()
    : path_()
    , can_be_downloaded_()
    , can_be_deleted_()
    , is_downloading_active_()
    , is_downloading_completed_()
    , downloaded_prefix_size_()
    , downloaded_size_()
{}

localFile::localFile(std::string const &path_, bool can_be_downloaded_, bool can_be_deleted_,
                     bool is_downloading_active_, bool is_downloading_completed_, int32_t downloaded_prefix_size_,
                     int32_t downloaded_size_)
    : path_(std::move(path_))
    , can_be_downloaded_(can_be_downloaded_)
    , can_be_deleted_(can_be_deleted_)
    , is_downloading_active_(is_downloading_active_)
    , is_downloading_completed_(is_downloading_completed_)
    , downloaded_prefix_size_(downloaded_prefix_size_)
    , downloaded_size_(downloaded_size_)
{}

const int32_t localFile::ID;

void localFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "localFile");
        s.store_field("path", path_);
        s.store_field("can_be_downloaded", can_be_downloaded_);
        s.store_field("can_be_deleted", can_be_deleted_);
        s.store_field("is_downloading_active", is_downloading_active_);
        s.store_field("is_downloading_completed", is_downloading_completed_);
        s.store_field("downloaded_prefix_size", downloaded_prefix_size_);
        s.store_field("downloaded_size", downloaded_size_);
        s.store_class_end();
    }
}

location::location()
    : latitude_()
    , longitude_()
{}

location::location(double latitude_, double longitude_)
    : latitude_(latitude_)
    , longitude_(longitude_)
{}

const int32_t location::ID;

void location::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "location");
        s.store_field("latitude", latitude_);
        s.store_field("longitude", longitude_);
        s.store_class_end();
    }
}

maskPointForehead::maskPointForehead()
{
}

const int32_t maskPointForehead::ID;

void maskPointForehead::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "maskPointForehead");
        s.store_class_end();
    }
}

maskPointEyes::maskPointEyes()
{
}

const int32_t maskPointEyes::ID;

void maskPointEyes::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "maskPointEyes");
        s.store_class_end();
    }
}

maskPointMouth::maskPointMouth()
{
}

const int32_t maskPointMouth::ID;

void maskPointMouth::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "maskPointMouth");
        s.store_class_end();
    }
}

maskPointChin::maskPointChin()
{
}

const int32_t maskPointChin::ID;

void maskPointChin::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "maskPointChin");
        s.store_class_end();
    }
}

maskPosition::maskPosition()
    : point_()
    , x_shift_()
    , y_shift_()
    , scale_()
{}

maskPosition::maskPosition(object_ptr<MaskPoint> &&point_, double x_shift_, double y_shift_,
                           double scale_)
    : point_(std::move(point_))
    , x_shift_(x_shift_)
    , y_shift_(y_shift_)
    , scale_(scale_)
{}

const int32_t maskPosition::ID;

void maskPosition::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "maskPosition");
        if (point_ == nullptr) {
            s.store_field("point", "null");
        } else {
            point_->store(s, "point");
        }
        s.store_field("x_shift", x_shift_);
        s.store_field("y_shift", y_shift_);
        s.store_field("scale", scale_);
        s.store_class_end();
    }
}

message::message()
    : id_()
    , sender_user_id_()
    , chat_id_()
    , sending_state_()
    , is_outgoing_()
    , can_be_edited_()
    , can_be_forwarded_()
    , can_be_deleted_only_for_self_()
    , can_be_deleted_for_all_users_()
    , is_channel_post_()
    , contains_unread_mention_()
    , date_()
    , edit_date_()
    , forward_info_()
    , reply_to_message_id_()
    , ttl_()
    , ttl_expires_in_()
    , via_bot_user_id_()
    , author_signature_()
    , views_()
    , media_album_id_()
    , content_()
    , reply_markup_()
{}

message::message(std::int64_t id_, int32_t sender_user_id_, std::int64_t chat_id_,
                 object_ptr<MessageSendingState> &&sending_state_, bool is_outgoing_, bool can_be_edited_,
                 bool can_be_forwarded_, bool can_be_deleted_only_for_self_, bool can_be_deleted_for_all_users_,
                 bool is_channel_post_, bool contains_unread_mention_, int32_t date_, int32_t edit_date_,
                 object_ptr<MessageForwardInfo> &&forward_info_, std::int64_t reply_to_message_id_,
                 int32_t ttl_, double ttl_expires_in_, int32_t via_bot_user_id_,
                 std::string const &author_signature_, int32_t views_, std::int64_t media_album_id_,
                 object_ptr<MessageContent> &&content_, object_ptr<ReplyMarkup> &&reply_markup_)
    : id_(id_)
    , sender_user_id_(sender_user_id_)
    , chat_id_(chat_id_)
    , sending_state_(std::move(sending_state_))
    , is_outgoing_(is_outgoing_)
    , can_be_edited_(can_be_edited_)
    , can_be_forwarded_(can_be_forwarded_)
    , can_be_deleted_only_for_self_(can_be_deleted_only_for_self_)
    , can_be_deleted_for_all_users_(can_be_deleted_for_all_users_)
    , is_channel_post_(is_channel_post_)
    , contains_unread_mention_(contains_unread_mention_)
    , date_(date_)
    , edit_date_(edit_date_)
    , forward_info_(std::move(forward_info_))
    , reply_to_message_id_(reply_to_message_id_)
    , ttl_(ttl_)
    , ttl_expires_in_(ttl_expires_in_)
    , via_bot_user_id_(via_bot_user_id_)
    , author_signature_(std::move(author_signature_))
    , views_(views_)
    , media_album_id_(media_album_id_)
    , content_(std::move(content_))
    , reply_markup_(std::move(reply_markup_))
{}

const int32_t message::ID;

void message::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "message");
        s.store_field("id", id_);
        s.store_field("sender_user_id", sender_user_id_);
        s.store_field("chat_id", chat_id_);
        if (sending_state_ == nullptr) {
            s.store_field("sending_state", "null");
        } else {
            sending_state_->store(s, "sending_state");
        }
        s.store_field("is_outgoing", is_outgoing_);
        s.store_field("can_be_edited", can_be_edited_);
        s.store_field("can_be_forwarded", can_be_forwarded_);
        s.store_field("can_be_deleted_only_for_self", can_be_deleted_only_for_self_);
        s.store_field("can_be_deleted_for_all_users", can_be_deleted_for_all_users_);
        s.store_field("is_channel_post", is_channel_post_);
        s.store_field("contains_unread_mention", contains_unread_mention_);
        s.store_field("date", date_);
        s.store_field("edit_date", edit_date_);
        if (forward_info_ == nullptr) {
            s.store_field("forward_info", "null");
        } else {
            forward_info_->store(s, "forward_info");
        }
        s.store_field("reply_to_message_id", reply_to_message_id_);
        s.store_field("ttl", ttl_);
        s.store_field("ttl_expires_in", ttl_expires_in_);
        s.store_field("via_bot_user_id", via_bot_user_id_);
        s.store_field("author_signature", author_signature_);
        s.store_field("views", views_);
        s.store_field("media_album_id", media_album_id_);
        if (content_ == nullptr) {
            s.store_field("content", "null");
        } else {
            content_->store(s, "content");
        }
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        s.store_class_end();
    }
}

messageText::messageText()
    : text_()
    , web_page_()
{}

messageText::messageText(object_ptr<formattedText> &&text_, object_ptr<webPage> &&web_page_)
    : text_(std::move(text_))
    , web_page_(std::move(web_page_))
{}

const int32_t messageText::ID;

void messageText::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageText");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        if (web_page_ == nullptr) {
            s.store_field("web_page", "null");
        } else {
            web_page_->store(s, "web_page");
        }
        s.store_class_end();
    }
}

messageAnimation::messageAnimation()
    : animation_()
    , caption_()
{}

messageAnimation::messageAnimation(object_ptr<animation> &&animation_,
                                   object_ptr<formattedText> &&caption_)
    : animation_(std::move(animation_))
    , caption_(std::move(caption_))
{}

const int32_t messageAnimation::ID;

void messageAnimation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageAnimation");
        if (animation_ == nullptr) {
            s.store_field("animation", "null");
        } else {
            animation_->store(s, "animation");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

messageAudio::messageAudio()
    : audio_()
    , caption_()
{}

messageAudio::messageAudio(object_ptr<audio> &&audio_, object_ptr<formattedText> &&caption_)
    : audio_(std::move(audio_))
    , caption_(std::move(caption_))
{}

const int32_t messageAudio::ID;

void messageAudio::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageAudio");
        if (audio_ == nullptr) {
            s.store_field("audio", "null");
        } else {
            audio_->store(s, "audio");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

messageDocument::messageDocument()
    : document_()
    , caption_()
{}

messageDocument::messageDocument(object_ptr<document> &&document_,
                                 object_ptr<formattedText> &&caption_)
    : document_(std::move(document_))
    , caption_(std::move(caption_))
{}

const int32_t messageDocument::ID;

void messageDocument::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageDocument");
        if (document_ == nullptr) {
            s.store_field("document", "null");
        } else {
            document_->store(s, "document");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

messagePhoto::messagePhoto()
    : photo_()
    , caption_()
{}

messagePhoto::messagePhoto(object_ptr<photo> &&photo_, object_ptr<formattedText> &&caption_)
    : photo_(std::move(photo_))
    , caption_(std::move(caption_))
{}

const int32_t messagePhoto::ID;

void messagePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messagePhoto");
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

messageExpiredPhoto::messageExpiredPhoto()
{
}

const int32_t messageExpiredPhoto::ID;

void messageExpiredPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageExpiredPhoto");
        s.store_class_end();
    }
}

messageSticker::messageSticker()
    : sticker_()
{}

messageSticker::messageSticker(object_ptr<sticker> &&sticker_)
    : sticker_(std::move(sticker_))
{}

const int32_t messageSticker::ID;

void messageSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageSticker");
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

messageVideo::messageVideo()
    : video_()
    , caption_()
{}

messageVideo::messageVideo(object_ptr<video> &&video_, object_ptr<formattedText> &&caption_)
    : video_(std::move(video_))
    , caption_(std::move(caption_))
{}

const int32_t messageVideo::ID;

void messageVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageVideo");
        if (video_ == nullptr) {
            s.store_field("video", "null");
        } else {
            video_->store(s, "video");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

messageExpiredVideo::messageExpiredVideo()
{
}

const int32_t messageExpiredVideo::ID;

void messageExpiredVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageExpiredVideo");
        s.store_class_end();
    }
}

messageVideoNote::messageVideoNote()
    : video_note_()
    , is_viewed_()
{}

messageVideoNote::messageVideoNote(object_ptr<videoNote> &&video_note_, bool is_viewed_)
    : video_note_(std::move(video_note_))
    , is_viewed_(is_viewed_)
{}

const int32_t messageVideoNote::ID;

void messageVideoNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageVideoNote");
        if (video_note_ == nullptr) {
            s.store_field("video_note", "null");
        } else {
            video_note_->store(s, "video_note");
        }
        s.store_field("is_viewed", is_viewed_);
        s.store_class_end();
    }
}

messageVoiceNote::messageVoiceNote()
    : voice_note_()
    , caption_()
    , is_listened_()
{}

messageVoiceNote::messageVoiceNote(object_ptr<voiceNote> &&voice_note_,
                                   object_ptr<formattedText> &&caption_, bool is_listened_)
    : voice_note_(std::move(voice_note_))
    , caption_(std::move(caption_))
    , is_listened_(is_listened_)
{}

const int32_t messageVoiceNote::ID;

void messageVoiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageVoiceNote");
        if (voice_note_ == nullptr) {
            s.store_field("voice_note", "null");
        } else {
            voice_note_->store(s, "voice_note");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_field("is_listened", is_listened_);
        s.store_class_end();
    }
}

messageLocation::messageLocation()
    : location_()
    , live_period_()
{}

messageLocation::messageLocation(object_ptr<location> &&location_, int32_t live_period_)
    : location_(std::move(location_))
    , live_period_(live_period_)
{}

const int32_t messageLocation::ID;

void messageLocation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageLocation");
        if (location_ == nullptr) {
            s.store_field("location", "null");
        } else {
            location_->store(s, "location");
        }
        s.store_field("live_period", live_period_);
        s.store_class_end();
    }
}

messageVenue::messageVenue()
    : venue_()
{}

messageVenue::messageVenue(object_ptr<venue> &&venue_)
    : venue_(std::move(venue_))
{}

const int32_t messageVenue::ID;

void messageVenue::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageVenue");
        if (venue_ == nullptr) {
            s.store_field("venue", "null");
        } else {
            venue_->store(s, "venue");
        }
        s.store_class_end();
    }
}

messageContact::messageContact()
    : contact_()
{}

messageContact::messageContact(object_ptr<contact> &&contact_)
    : contact_(std::move(contact_))
{}

const int32_t messageContact::ID;

void messageContact::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageContact");
        if (contact_ == nullptr) {
            s.store_field("contact", "null");
        } else {
            contact_->store(s, "contact");
        }
        s.store_class_end();
    }
}

messageGame::messageGame()
    : game_()
{}

messageGame::messageGame(object_ptr<game> &&game_)
    : game_(std::move(game_))
{}

const int32_t messageGame::ID;

void messageGame::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageGame");
        if (game_ == nullptr) {
            s.store_field("game", "null");
        } else {
            game_->store(s, "game");
        }
        s.store_class_end();
    }
}

messageInvoice::messageInvoice()
    : title_()
    , description_()
    , photo_()
    , currency_()
    , total_amount_()
    , start_parameter_()
    , is_test_()
    , need_shipping_address_()
    , receipt_message_id_()
{}

messageInvoice::messageInvoice(std::string const &title_, std::string const &description_,
                               object_ptr<photo> &&photo_, std::string const &currency_, std::int64_t total_amount_,
                               std::string const &start_parameter_, bool is_test_, bool need_shipping_address_,
                               std::int64_t receipt_message_id_)
    : title_(std::move(title_))
    , description_(std::move(description_))
    , photo_(std::move(photo_))
    , currency_(std::move(currency_))
    , total_amount_(total_amount_)
    , start_parameter_(std::move(start_parameter_))
    , is_test_(is_test_)
    , need_shipping_address_(need_shipping_address_)
    , receipt_message_id_(receipt_message_id_)
{}

const int32_t messageInvoice::ID;

void messageInvoice::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageInvoice");
        s.store_field("title", title_);
        s.store_field("description", description_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_field("currency", currency_);
        s.store_field("total_amount", total_amount_);
        s.store_field("start_parameter", start_parameter_);
        s.store_field("is_test", is_test_);
        s.store_field("need_shipping_address", need_shipping_address_);
        s.store_field("receipt_message_id", receipt_message_id_);
        s.store_class_end();
    }
}

messageCall::messageCall()
    : discard_reason_()
    , duration_()
{}

messageCall::messageCall(object_ptr<CallDiscardReason> &&discard_reason_, int32_t duration_)
    : discard_reason_(std::move(discard_reason_))
    , duration_(duration_)
{}

const int32_t messageCall::ID;

void messageCall::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageCall");
        if (discard_reason_ == nullptr) {
            s.store_field("discard_reason", "null");
        } else {
            discard_reason_->store(s, "discard_reason");
        }
        s.store_field("duration", duration_);
        s.store_class_end();
    }
}

messageBasicGroupChatCreate::messageBasicGroupChatCreate()
    : title_()
    , member_user_ids_()
{}

messageBasicGroupChatCreate::messageBasicGroupChatCreate(std::string const &title_,
                                                         std::vector<int32_t> &&member_user_ids_)
    : title_(std::move(title_))
    , member_user_ids_(std::move(member_user_ids_))
{}

const int32_t messageBasicGroupChatCreate::ID;

void messageBasicGroupChatCreate::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageBasicGroupChatCreate");
        s.store_field("title", title_);
        {
            const std::vector<int32_t> &v = member_user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("member_user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

messageSupergroupChatCreate::messageSupergroupChatCreate()
    : title_()
{}

messageSupergroupChatCreate::messageSupergroupChatCreate(std::string const &title_)
    : title_(std::move(title_))
{}

const int32_t messageSupergroupChatCreate::ID;

void messageSupergroupChatCreate::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageSupergroupChatCreate");
        s.store_field("title", title_);
        s.store_class_end();
    }
}

messageChatChangeTitle::messageChatChangeTitle()
    : title_()
{}

messageChatChangeTitle::messageChatChangeTitle(std::string const &title_)
    : title_(std::move(title_))
{}

const int32_t messageChatChangeTitle::ID;

void messageChatChangeTitle::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatChangeTitle");
        s.store_field("title", title_);
        s.store_class_end();
    }
}

messageChatChangePhoto::messageChatChangePhoto()
    : photo_()
{}

messageChatChangePhoto::messageChatChangePhoto(object_ptr<photo> &&photo_)
    : photo_(std::move(photo_))
{}

const int32_t messageChatChangePhoto::ID;

void messageChatChangePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatChangePhoto");
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_class_end();
    }
}

messageChatDeletePhoto::messageChatDeletePhoto()
{
}

const int32_t messageChatDeletePhoto::ID;

void messageChatDeletePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatDeletePhoto");
        s.store_class_end();
    }
}

messageChatAddMembers::messageChatAddMembers()
    : member_user_ids_()
{}

messageChatAddMembers::messageChatAddMembers(std::vector<int32_t> &&member_user_ids_)
    : member_user_ids_(std::move(member_user_ids_))
{}

const int32_t messageChatAddMembers::ID;

void messageChatAddMembers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatAddMembers");
        {
            const std::vector<int32_t> &v = member_user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("member_user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

messageChatJoinByLink::messageChatJoinByLink()
{
}

const int32_t messageChatJoinByLink::ID;

void messageChatJoinByLink::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatJoinByLink");
        s.store_class_end();
    }
}

messageChatDeleteMember::messageChatDeleteMember()
    : user_id_()
{}

messageChatDeleteMember::messageChatDeleteMember(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t messageChatDeleteMember::ID;

void messageChatDeleteMember::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatDeleteMember");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

messageChatUpgradeTo::messageChatUpgradeTo()
    : supergroup_id_()
{}

messageChatUpgradeTo::messageChatUpgradeTo(int32_t supergroup_id_)
    : supergroup_id_(supergroup_id_)
{}

const int32_t messageChatUpgradeTo::ID;

void messageChatUpgradeTo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatUpgradeTo");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_class_end();
    }
}

messageChatUpgradeFrom::messageChatUpgradeFrom()
    : title_()
    , basic_group_id_()
{}

messageChatUpgradeFrom::messageChatUpgradeFrom(std::string const &title_,
                                               int32_t basic_group_id_)
    : title_(std::move(title_))
    , basic_group_id_(basic_group_id_)
{}

const int32_t messageChatUpgradeFrom::ID;

void messageChatUpgradeFrom::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatUpgradeFrom");
        s.store_field("title", title_);
        s.store_field("basic_group_id", basic_group_id_);
        s.store_class_end();
    }
}

messagePinMessage::messagePinMessage()
    : message_id_()
{}

messagePinMessage::messagePinMessage(std::int64_t message_id_)
    : message_id_(message_id_)
{}

const int32_t messagePinMessage::ID;

void messagePinMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messagePinMessage");
        s.store_field("message_id", message_id_);
        s.store_class_end();
    }
}

messageScreenshotTaken::messageScreenshotTaken()
{
}

const int32_t messageScreenshotTaken::ID;

void messageScreenshotTaken::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageScreenshotTaken");
        s.store_class_end();
    }
}

messageChatSetTtl::messageChatSetTtl()
    : ttl_()
{}

messageChatSetTtl::messageChatSetTtl(int32_t ttl_)
    : ttl_(ttl_)
{}

const int32_t messageChatSetTtl::ID;

void messageChatSetTtl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageChatSetTtl");
        s.store_field("ttl", ttl_);
        s.store_class_end();
    }
}

messageCustomServiceAction::messageCustomServiceAction()
    : text_()
{}

messageCustomServiceAction::messageCustomServiceAction(std::string const &text_)
    : text_(std::move(text_))
{}

const int32_t messageCustomServiceAction::ID;

void messageCustomServiceAction::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageCustomServiceAction");
        s.store_field("text", text_);
        s.store_class_end();
    }
}

messageGameScore::messageGameScore()
    : game_message_id_()
    , game_id_()
    , score_()
{}

messageGameScore::messageGameScore(std::int64_t game_message_id_, std::int64_t game_id_,
                                   int32_t score_)
    : game_message_id_(game_message_id_)
    , game_id_(game_id_)
    , score_(score_)
{}

const int32_t messageGameScore::ID;

void messageGameScore::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageGameScore");
        s.store_field("game_message_id", game_message_id_);
        s.store_field("game_id", game_id_);
        s.store_field("score", score_);
        s.store_class_end();
    }
}

messagePaymentSuccessful::messagePaymentSuccessful()
    : invoice_message_id_()
    , currency_()
    , total_amount_()
{}

messagePaymentSuccessful::messagePaymentSuccessful(std::int64_t invoice_message_id_,
                                                   std::string const &currency_, std::int64_t total_amount_)
    : invoice_message_id_(invoice_message_id_)
    , currency_(std::move(currency_))
    , total_amount_(total_amount_)
{}

const int32_t messagePaymentSuccessful::ID;

void messagePaymentSuccessful::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messagePaymentSuccessful");
        s.store_field("invoice_message_id", invoice_message_id_);
        s.store_field("currency", currency_);
        s.store_field("total_amount", total_amount_);
        s.store_class_end();
    }
}

messagePaymentSuccessfulBot::messagePaymentSuccessfulBot()
    : invoice_message_id_()
    , currency_()
    , total_amount_()
    , invoice_payload_()
    , shipping_option_id_()
    , order_info_()
    , telegram_payment_charge_id_()
    , provider_payment_charge_id_()
{}

messagePaymentSuccessfulBot::messagePaymentSuccessfulBot(std::int64_t invoice_message_id_,
                                                         std::string const &currency_, std::int64_t total_amount_, std::string const &invoice_payload_,
                                                         std::string const &shipping_option_id_, object_ptr<orderInfo> &&order_info_,
                                                         std::string const &telegram_payment_charge_id_, std::string const &provider_payment_charge_id_)
    : invoice_message_id_(invoice_message_id_)
    , currency_(std::move(currency_))
    , total_amount_(total_amount_)
    , invoice_payload_(std::move(invoice_payload_))
    , shipping_option_id_(std::move(shipping_option_id_))
    , order_info_(std::move(order_info_))
    , telegram_payment_charge_id_(std::move(telegram_payment_charge_id_))
    , provider_payment_charge_id_(std::move(provider_payment_charge_id_))
{}

const int32_t messagePaymentSuccessfulBot::ID;

void messagePaymentSuccessfulBot::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messagePaymentSuccessfulBot");
        s.store_field("invoice_message_id", invoice_message_id_);
        s.store_field("currency", currency_);
        s.store_field("total_amount", total_amount_);
        s.store_bytes_field("invoice_payload", invoice_payload_);
        s.store_field("shipping_option_id", shipping_option_id_);
        if (order_info_ == nullptr) {
            s.store_field("order_info", "null");
        } else {
            order_info_->store(s, "order_info");
        }
        s.store_field("telegram_payment_charge_id", telegram_payment_charge_id_);
        s.store_field("provider_payment_charge_id", provider_payment_charge_id_);
        s.store_class_end();
    }
}

messageContactRegistered::messageContactRegistered()
{
}

const int32_t messageContactRegistered::ID;

void messageContactRegistered::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageContactRegistered");
        s.store_class_end();
    }
}

messageUnsupported::messageUnsupported()
{
}

const int32_t messageUnsupported::ID;

void messageUnsupported::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageUnsupported");
        s.store_class_end();
    }
}

messageForwardedFromUser::messageForwardedFromUser()
    : sender_user_id_()
    , date_()
    , forwarded_from_chat_id_()
    , forwarded_from_message_id_()
{}

messageForwardedFromUser::messageForwardedFromUser(int32_t sender_user_id_, int32_t date_,
                                                   std::int64_t forwarded_from_chat_id_, std::int64_t forwarded_from_message_id_)
    : sender_user_id_(sender_user_id_)
    , date_(date_)
    , forwarded_from_chat_id_(forwarded_from_chat_id_)
    , forwarded_from_message_id_(forwarded_from_message_id_)
{}

const int32_t messageForwardedFromUser::ID;

void messageForwardedFromUser::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageForwardedFromUser");
        s.store_field("sender_user_id", sender_user_id_);
        s.store_field("date", date_);
        s.store_field("forwarded_from_chat_id", forwarded_from_chat_id_);
        s.store_field("forwarded_from_message_id", forwarded_from_message_id_);
        s.store_class_end();
    }
}

messageForwardedPost::messageForwardedPost()
    : chat_id_()
    , author_signature_()
    , date_()
    , message_id_()
    , forwarded_from_chat_id_()
    , forwarded_from_message_id_()
{}

messageForwardedPost::messageForwardedPost(std::int64_t chat_id_,
                                           std::string const &author_signature_, int32_t date_, std::int64_t message_id_,
                                           std::int64_t forwarded_from_chat_id_, std::int64_t forwarded_from_message_id_)
    : chat_id_(chat_id_)
    , author_signature_(std::move(author_signature_))
    , date_(date_)
    , message_id_(message_id_)
    , forwarded_from_chat_id_(forwarded_from_chat_id_)
    , forwarded_from_message_id_(forwarded_from_message_id_)
{}

const int32_t messageForwardedPost::ID;

void messageForwardedPost::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageForwardedPost");
        s.store_field("chat_id", chat_id_);
        s.store_field("author_signature", author_signature_);
        s.store_field("date", date_);
        s.store_field("message_id", message_id_);
        s.store_field("forwarded_from_chat_id", forwarded_from_chat_id_);
        s.store_field("forwarded_from_message_id", forwarded_from_message_id_);
        s.store_class_end();
    }
}

messageSendingStatePending::messageSendingStatePending()
{
}

const int32_t messageSendingStatePending::ID;

void messageSendingStatePending::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageSendingStatePending");
        s.store_class_end();
    }
}

messageSendingStateFailed::messageSendingStateFailed()
{
}

const int32_t messageSendingStateFailed::ID;

void messageSendingStateFailed::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messageSendingStateFailed");
        s.store_class_end();
    }
}

messages::messages()
    : total_count_()
    , messages_()
{}

messages::messages(int32_t total_count_, std::vector<object_ptr<message>> &&messages_)
    : total_count_(total_count_)
    , messages_(std::move(messages_))
{}

const int32_t messages::ID;

void messages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "messages");
        s.store_field("total_count", total_count_);
        {
            const std::vector<object_ptr<message>> &v = messages_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("messages", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

networkStatistics::networkStatistics()
    : since_date_()
    , entries_()
{}

networkStatistics::networkStatistics(int32_t since_date_,
                                     std::vector<object_ptr<NetworkStatisticsEntry>> &&entries_)
    : since_date_(since_date_)
    , entries_(std::move(entries_))
{}

const int32_t networkStatistics::ID;

void networkStatistics::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "networkStatistics");
        s.store_field("since_date", since_date_);
        {
            const std::vector<object_ptr<NetworkStatisticsEntry>> &v = entries_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("entries", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

networkStatisticsEntryFile::networkStatisticsEntryFile()
    : file_type_()
    , network_type_()
    , sent_bytes_()
    , received_bytes_()
{}

networkStatisticsEntryFile::networkStatisticsEntryFile(object_ptr<FileType> &&file_type_,
                                                       object_ptr<NetworkType> &&network_type_, std::int64_t sent_bytes_, std::int64_t received_bytes_)
    : file_type_(std::move(file_type_))
    , network_type_(std::move(network_type_))
    , sent_bytes_(sent_bytes_)
    , received_bytes_(received_bytes_)
{}

const int32_t networkStatisticsEntryFile::ID;

void networkStatisticsEntryFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "networkStatisticsEntryFile");
        if (file_type_ == nullptr) {
            s.store_field("file_type", "null");
        } else {
            file_type_->store(s, "file_type");
        }
        if (network_type_ == nullptr) {
            s.store_field("network_type", "null");
        } else {
            network_type_->store(s, "network_type");
        }
        s.store_field("sent_bytes", sent_bytes_);
        s.store_field("received_bytes", received_bytes_);
        s.store_class_end();
    }
}

networkStatisticsEntryCall::networkStatisticsEntryCall()
    : network_type_()
    , sent_bytes_()
    , received_bytes_()
    , duration_()
{}

networkStatisticsEntryCall::networkStatisticsEntryCall(object_ptr<NetworkType> &&network_type_,
                                                       std::int64_t sent_bytes_, std::int64_t received_bytes_, double duration_)
    : network_type_(std::move(network_type_))
    , sent_bytes_(sent_bytes_)
    , received_bytes_(received_bytes_)
    , duration_(duration_)
{}

const int32_t networkStatisticsEntryCall::ID;

void networkStatisticsEntryCall::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "networkStatisticsEntryCall");
        if (network_type_ == nullptr) {
            s.store_field("network_type", "null");
        } else {
            network_type_->store(s, "network_type");
        }
        s.store_field("sent_bytes", sent_bytes_);
        s.store_field("received_bytes", received_bytes_);
        s.store_field("duration", duration_);
        s.store_class_end();
    }
}

networkTypeNone::networkTypeNone()
{
}

const int32_t networkTypeNone::ID;

void networkTypeNone::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "networkTypeNone");
        s.store_class_end();
    }
}

networkTypeMobile::networkTypeMobile()
{
}

const int32_t networkTypeMobile::ID;

void networkTypeMobile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "networkTypeMobile");
        s.store_class_end();
    }
}

networkTypeMobileRoaming::networkTypeMobileRoaming()
{
}

const int32_t networkTypeMobileRoaming::ID;

void networkTypeMobileRoaming::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "networkTypeMobileRoaming");
        s.store_class_end();
    }
}

networkTypeWiFi::networkTypeWiFi()
{
}

const int32_t networkTypeWiFi::ID;

void networkTypeWiFi::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "networkTypeWiFi");
        s.store_class_end();
    }
}

networkTypeOther::networkTypeOther()
{
}

const int32_t networkTypeOther::ID;

void networkTypeOther::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "networkTypeOther");
        s.store_class_end();
    }
}

notificationSettings::notificationSettings()
    : mute_for_()
    , sound_()
    , show_preview_()
{}

notificationSettings::notificationSettings(int32_t mute_for_, std::string const &sound_,
                                           bool show_preview_)
    : mute_for_(mute_for_)
    , sound_(std::move(sound_))
    , show_preview_(show_preview_)
{}

const int32_t notificationSettings::ID;

void notificationSettings::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "notificationSettings");
        s.store_field("mute_for", mute_for_);
        s.store_field("sound", sound_);
        s.store_field("show_preview", show_preview_);
        s.store_class_end();
    }
}

notificationSettingsScopeChat::notificationSettingsScopeChat()
    : chat_id_()
{}

notificationSettingsScopeChat::notificationSettingsScopeChat(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t notificationSettingsScopeChat::ID;

void notificationSettingsScopeChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "notificationSettingsScopeChat");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

notificationSettingsScopePrivateChats::notificationSettingsScopePrivateChats()
{
}

const int32_t notificationSettingsScopePrivateChats::ID;

void notificationSettingsScopePrivateChats::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "notificationSettingsScopePrivateChats");
        s.store_class_end();
    }
}

notificationSettingsScopeBasicGroupChats::notificationSettingsScopeBasicGroupChats()
{
}

const int32_t notificationSettingsScopeBasicGroupChats::ID;

void notificationSettingsScopeBasicGroupChats::store(TlStorerToString &s,
                                                     const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "notificationSettingsScopeBasicGroupChats");
        s.store_class_end();
    }
}

notificationSettingsScopeAllChats::notificationSettingsScopeAllChats()
{
}

const int32_t notificationSettingsScopeAllChats::ID;

void notificationSettingsScopeAllChats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "notificationSettingsScopeAllChats");
        s.store_class_end();
    }
}

ok::ok()
{
}

const int32_t ok::ID;

void ok::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "ok");
        s.store_class_end();
    }
}

optionValueBoolean::optionValueBoolean()
    : value_()
{}

optionValueBoolean::optionValueBoolean(bool value_)
    : value_(value_)
{}

const int32_t optionValueBoolean::ID;

void optionValueBoolean::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "optionValueBoolean");
        s.store_field("value", value_);
        s.store_class_end();
    }
}

optionValueEmpty::optionValueEmpty()
{
}

const int32_t optionValueEmpty::ID;

void optionValueEmpty::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "optionValueEmpty");
        s.store_class_end();
    }
}

optionValueInteger::optionValueInteger()
    : value_()
{}

optionValueInteger::optionValueInteger(int32_t value_)
    : value_(value_)
{}

const int32_t optionValueInteger::ID;

void optionValueInteger::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "optionValueInteger");
        s.store_field("value", value_);
        s.store_class_end();
    }
}

optionValueString::optionValueString()
    : value_()
{}

optionValueString::optionValueString(std::string const &value_)
    : value_(std::move(value_))
{}

const int32_t optionValueString::ID;

void optionValueString::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "optionValueString");
        s.store_field("value", value_);
        s.store_class_end();
    }
}

orderInfo::orderInfo()
    : name_()
    , phone_number_()
    , email_address_()
    , shipping_address_()
{}

orderInfo::orderInfo(std::string const &name_, std::string const &phone_number_,
                     std::string const &email_address_, object_ptr<shippingAddress> &&shipping_address_)
    : name_(std::move(name_))
    , phone_number_(std::move(phone_number_))
    , email_address_(std::move(email_address_))
    , shipping_address_(std::move(shipping_address_))
{}

const int32_t orderInfo::ID;

void orderInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "orderInfo");
        s.store_field("name", name_);
        s.store_field("phone_number", phone_number_);
        s.store_field("email_address", email_address_);
        if (shipping_address_ == nullptr) {
            s.store_field("shipping_address", "null");
        } else {
            shipping_address_->store(s, "shipping_address");
        }
        s.store_class_end();
    }
}

pageBlockTitle::pageBlockTitle()
    : title_()
{}

pageBlockTitle::pageBlockTitle(object_ptr<RichText> &&title_)
    : title_(std::move(title_))
{}

const int32_t pageBlockTitle::ID;

void pageBlockTitle::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockTitle");
        if (title_ == nullptr) {
            s.store_field("title", "null");
        } else {
            title_->store(s, "title");
        }
        s.store_class_end();
    }
}

pageBlockSubtitle::pageBlockSubtitle()
    : subtitle_()
{}

pageBlockSubtitle::pageBlockSubtitle(object_ptr<RichText> &&subtitle_)
    : subtitle_(std::move(subtitle_))
{}

const int32_t pageBlockSubtitle::ID;

void pageBlockSubtitle::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockSubtitle");
        if (subtitle_ == nullptr) {
            s.store_field("subtitle", "null");
        } else {
            subtitle_->store(s, "subtitle");
        }
        s.store_class_end();
    }
}

pageBlockAuthorDate::pageBlockAuthorDate()
    : author_()
    , publish_date_()
{}

pageBlockAuthorDate::pageBlockAuthorDate(object_ptr<RichText> &&author_, int32_t publish_date_)
    : author_(std::move(author_))
    , publish_date_(publish_date_)
{}

const int32_t pageBlockAuthorDate::ID;

void pageBlockAuthorDate::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockAuthorDate");
        if (author_ == nullptr) {
            s.store_field("author", "null");
        } else {
            author_->store(s, "author");
        }
        s.store_field("publish_date", publish_date_);
        s.store_class_end();
    }
}

pageBlockHeader::pageBlockHeader()
    : header_()
{}

pageBlockHeader::pageBlockHeader(object_ptr<RichText> &&header_)
    : header_(std::move(header_))
{}

const int32_t pageBlockHeader::ID;

void pageBlockHeader::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockHeader");
        if (header_ == nullptr) {
            s.store_field("header", "null");
        } else {
            header_->store(s, "header");
        }
        s.store_class_end();
    }
}

pageBlockSubheader::pageBlockSubheader()
    : subheader_()
{}

pageBlockSubheader::pageBlockSubheader(object_ptr<RichText> &&subheader_)
    : subheader_(std::move(subheader_))
{}

const int32_t pageBlockSubheader::ID;

void pageBlockSubheader::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockSubheader");
        if (subheader_ == nullptr) {
            s.store_field("subheader", "null");
        } else {
            subheader_->store(s, "subheader");
        }
        s.store_class_end();
    }
}

pageBlockParagraph::pageBlockParagraph()
    : text_()
{}

pageBlockParagraph::pageBlockParagraph(object_ptr<RichText> &&text_)
    : text_(std::move(text_))
{}

const int32_t pageBlockParagraph::ID;

void pageBlockParagraph::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockParagraph");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_class_end();
    }
}

pageBlockPreformatted::pageBlockPreformatted()
    : text_()
    , language_()
{}

pageBlockPreformatted::pageBlockPreformatted(object_ptr<RichText> &&text_,
                                             std::string const &language_)
    : text_(std::move(text_))
    , language_(std::move(language_))
{}

const int32_t pageBlockPreformatted::ID;

void pageBlockPreformatted::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockPreformatted");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_field("language", language_);
        s.store_class_end();
    }
}

pageBlockFooter::pageBlockFooter()
    : footer_()
{}

pageBlockFooter::pageBlockFooter(object_ptr<RichText> &&footer_)
    : footer_(std::move(footer_))
{}

const int32_t pageBlockFooter::ID;

void pageBlockFooter::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockFooter");
        if (footer_ == nullptr) {
            s.store_field("footer", "null");
        } else {
            footer_->store(s, "footer");
        }
        s.store_class_end();
    }
}

pageBlockDivider::pageBlockDivider()
{
}

const int32_t pageBlockDivider::ID;

void pageBlockDivider::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockDivider");
        s.store_class_end();
    }
}

pageBlockAnchor::pageBlockAnchor()
    : name_()
{}

pageBlockAnchor::pageBlockAnchor(std::string const &name_)
    : name_(std::move(name_))
{}

const int32_t pageBlockAnchor::ID;

void pageBlockAnchor::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockAnchor");
        s.store_field("name", name_);
        s.store_class_end();
    }
}

pageBlockList::pageBlockList()
    : items_()
    , is_ordered_()
{}

pageBlockList::pageBlockList(std::vector<object_ptr<RichText>> &&items_, bool is_ordered_)
    : items_(std::move(items_))
    , is_ordered_(is_ordered_)
{}

const int32_t pageBlockList::ID;

void pageBlockList::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockList");
        {
            const std::vector<object_ptr<RichText>> &v = items_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("items", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("is_ordered", is_ordered_);
        s.store_class_end();
    }
}

pageBlockBlockQuote::pageBlockBlockQuote()
    : text_()
    , caption_()
{}

pageBlockBlockQuote::pageBlockBlockQuote(object_ptr<RichText> &&text_,
                                         object_ptr<RichText> &&caption_)
    : text_(std::move(text_))
    , caption_(std::move(caption_))
{}

const int32_t pageBlockBlockQuote::ID;

void pageBlockBlockQuote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockBlockQuote");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

pageBlockPullQuote::pageBlockPullQuote()
    : text_()
    , caption_()
{}

pageBlockPullQuote::pageBlockPullQuote(object_ptr<RichText> &&text_,
                                       object_ptr<RichText> &&caption_)
    : text_(std::move(text_))
    , caption_(std::move(caption_))
{}

const int32_t pageBlockPullQuote::ID;

void pageBlockPullQuote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockPullQuote");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

pageBlockAnimation::pageBlockAnimation()
    : animation_()
    , caption_()
    , need_autoplay_()
{}

pageBlockAnimation::pageBlockAnimation(object_ptr<animation> &&animation_,
                                       object_ptr<RichText> &&caption_, bool need_autoplay_)
    : animation_(std::move(animation_))
    , caption_(std::move(caption_))
    , need_autoplay_(need_autoplay_)
{}

const int32_t pageBlockAnimation::ID;

void pageBlockAnimation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockAnimation");
        if (animation_ == nullptr) {
            s.store_field("animation", "null");
        } else {
            animation_->store(s, "animation");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_field("need_autoplay", need_autoplay_);
        s.store_class_end();
    }
}

pageBlockAudio::pageBlockAudio()
    : audio_()
    , caption_()
{}

pageBlockAudio::pageBlockAudio(object_ptr<audio> &&audio_, object_ptr<RichText> &&caption_)
    : audio_(std::move(audio_))
    , caption_(std::move(caption_))
{}

const int32_t pageBlockAudio::ID;

void pageBlockAudio::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockAudio");
        if (audio_ == nullptr) {
            s.store_field("audio", "null");
        } else {
            audio_->store(s, "audio");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

pageBlockPhoto::pageBlockPhoto()
    : photo_()
    , caption_()
{}

pageBlockPhoto::pageBlockPhoto(object_ptr<photo> &&photo_, object_ptr<RichText> &&caption_)
    : photo_(std::move(photo_))
    , caption_(std::move(caption_))
{}

const int32_t pageBlockPhoto::ID;

void pageBlockPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockPhoto");
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

pageBlockVideo::pageBlockVideo()
    : video_()
    , caption_()
    , need_autoplay_()
    , is_looped_()
{}

pageBlockVideo::pageBlockVideo(object_ptr<video> &&video_, object_ptr<RichText> &&caption_,
                               bool need_autoplay_, bool is_looped_)
    : video_(std::move(video_))
    , caption_(std::move(caption_))
    , need_autoplay_(need_autoplay_)
    , is_looped_(is_looped_)
{}

const int32_t pageBlockVideo::ID;

void pageBlockVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockVideo");
        if (video_ == nullptr) {
            s.store_field("video", "null");
        } else {
            video_->store(s, "video");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_field("need_autoplay", need_autoplay_);
        s.store_field("is_looped", is_looped_);
        s.store_class_end();
    }
}

pageBlockCover::pageBlockCover()
    : cover_()
{}

pageBlockCover::pageBlockCover(object_ptr<PageBlock> &&cover_)
    : cover_(std::move(cover_))
{}

const int32_t pageBlockCover::ID;

void pageBlockCover::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockCover");
        if (cover_ == nullptr) {
            s.store_field("cover", "null");
        } else {
            cover_->store(s, "cover");
        }
        s.store_class_end();
    }
}

pageBlockEmbedded::pageBlockEmbedded()
    : url_()
    , html_()
    , poster_photo_()
    , width_()
    , height_()
    , caption_()
    , is_full_width_()
    , allow_scrolling_()
{}

pageBlockEmbedded::pageBlockEmbedded(std::string const &url_, std::string const &html_,
                                     object_ptr<photo> &&poster_photo_, int32_t width_, int32_t height_,
                                     object_ptr<RichText> &&caption_, bool is_full_width_, bool allow_scrolling_)
    : url_(std::move(url_))
    , html_(std::move(html_))
    , poster_photo_(std::move(poster_photo_))
    , width_(width_)
    , height_(height_)
    , caption_(std::move(caption_))
    , is_full_width_(is_full_width_)
    , allow_scrolling_(allow_scrolling_)
{}

const int32_t pageBlockEmbedded::ID;

void pageBlockEmbedded::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockEmbedded");
        s.store_field("url", url_);
        s.store_field("html", html_);
        if (poster_photo_ == nullptr) {
            s.store_field("poster_photo", "null");
        } else {
            poster_photo_->store(s, "poster_photo");
        }
        s.store_field("width", width_);
        s.store_field("height", height_);
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_field("is_full_width", is_full_width_);
        s.store_field("allow_scrolling", allow_scrolling_);
        s.store_class_end();
    }
}

pageBlockEmbeddedPost::pageBlockEmbeddedPost()
    : url_()
    , author_()
    , author_photo_()
    , date_()
    , page_blocks_()
    , caption_()
{}

pageBlockEmbeddedPost::pageBlockEmbeddedPost(std::string const &url_, std::string const &author_,
                                             object_ptr<photo> &&author_photo_, int32_t date_,
                                             std::vector<object_ptr<PageBlock>> &&page_blocks_, object_ptr<RichText> &&caption_)
    : url_(std::move(url_))
    , author_(std::move(author_))
    , author_photo_(std::move(author_photo_))
    , date_(date_)
    , page_blocks_(std::move(page_blocks_))
    , caption_(std::move(caption_))
{}

const int32_t pageBlockEmbeddedPost::ID;

void pageBlockEmbeddedPost::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockEmbeddedPost");
        s.store_field("url", url_);
        s.store_field("author", author_);
        if (author_photo_ == nullptr) {
            s.store_field("author_photo", "null");
        } else {
            author_photo_->store(s, "author_photo");
        }
        s.store_field("date", date_);
        {
            const std::vector<object_ptr<PageBlock>> &v = page_blocks_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("page_blocks", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

pageBlockCollage::pageBlockCollage()
    : page_blocks_()
    , caption_()
{}

pageBlockCollage::pageBlockCollage(std::vector<object_ptr<PageBlock>> &&page_blocks_,
                                   object_ptr<RichText> &&caption_)
    : page_blocks_(std::move(page_blocks_))
    , caption_(std::move(caption_))
{}

const int32_t pageBlockCollage::ID;

void pageBlockCollage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockCollage");
        {
            const std::vector<object_ptr<PageBlock>> &v = page_blocks_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("page_blocks", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

pageBlockSlideshow::pageBlockSlideshow()
    : page_blocks_()
    , caption_()
{}

pageBlockSlideshow::pageBlockSlideshow(std::vector<object_ptr<PageBlock>> &&page_blocks_,
                                       object_ptr<RichText> &&caption_)
    : page_blocks_(std::move(page_blocks_))
    , caption_(std::move(caption_))
{}

const int32_t pageBlockSlideshow::ID;

void pageBlockSlideshow::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockSlideshow");
        {
            const std::vector<object_ptr<PageBlock>> &v = page_blocks_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("page_blocks", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

pageBlockChatLink::pageBlockChatLink()
    : title_()
    , photo_()
    , username_()
{}

pageBlockChatLink::pageBlockChatLink(std::string const &title_, object_ptr<chatPhoto> &&photo_,
                                     std::string const &username_)
    : title_(std::move(title_))
    , photo_(std::move(photo_))
    , username_(std::move(username_))
{}

const int32_t pageBlockChatLink::ID;

void pageBlockChatLink::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pageBlockChatLink");
        s.store_field("title", title_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_field("username", username_);
        s.store_class_end();
    }
}

passwordRecoveryInfo::passwordRecoveryInfo()
    : recovery_email_address_pattern_()
{}

passwordRecoveryInfo::passwordRecoveryInfo(std::string const &recovery_email_address_pattern_)
    : recovery_email_address_pattern_(std::move(recovery_email_address_pattern_))
{}

const int32_t passwordRecoveryInfo::ID;

void passwordRecoveryInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "passwordRecoveryInfo");
        s.store_field("recovery_email_address_pattern", recovery_email_address_pattern_);
        s.store_class_end();
    }
}

passwordState::passwordState()
    : has_password_()
    , password_hint_()
    , has_recovery_email_address_()
    , unconfirmed_recovery_email_address_pattern_()
{}

passwordState::passwordState(bool has_password_, std::string const &password_hint_,
                             bool has_recovery_email_address_, std::string const &unconfirmed_recovery_email_address_pattern_)
    : has_password_(has_password_)
    , password_hint_(std::move(password_hint_))
    , has_recovery_email_address_(has_recovery_email_address_)
    , unconfirmed_recovery_email_address_pattern_(std::move(
                                                      unconfirmed_recovery_email_address_pattern_))
{}

const int32_t passwordState::ID;

void passwordState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "passwordState");
        s.store_field("has_password", has_password_);
        s.store_field("password_hint", password_hint_);
        s.store_field("has_recovery_email_address", has_recovery_email_address_);
        s.store_field("unconfirmed_recovery_email_address_pattern",
                      unconfirmed_recovery_email_address_pattern_);
        s.store_class_end();
    }
}

paymentForm::paymentForm()
    : invoice_()
    , url_()
    , payments_provider_()
    , saved_order_info_()
    , saved_credentials_()
    , can_save_credentials_()
    , need_password_()
{}

paymentForm::paymentForm(object_ptr<invoice> &&invoice_, std::string const &url_,
                         object_ptr<paymentsProviderStripe> &&payments_provider_, object_ptr<orderInfo> &&saved_order_info_,
                         object_ptr<savedCredentials> &&saved_credentials_, bool can_save_credentials_, bool need_password_)
    : invoice_(std::move(invoice_))
    , url_(std::move(url_))
    , payments_provider_(std::move(payments_provider_))
    , saved_order_info_(std::move(saved_order_info_))
    , saved_credentials_(std::move(saved_credentials_))
    , can_save_credentials_(can_save_credentials_)
    , need_password_(need_password_)
{}

const int32_t paymentForm::ID;

void paymentForm::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "paymentForm");
        if (invoice_ == nullptr) {
            s.store_field("invoice", "null");
        } else {
            invoice_->store(s, "invoice");
        }
        s.store_field("url", url_);
        if (payments_provider_ == nullptr) {
            s.store_field("payments_provider", "null");
        } else {
            payments_provider_->store(s, "payments_provider");
        }
        if (saved_order_info_ == nullptr) {
            s.store_field("saved_order_info", "null");
        } else {
            saved_order_info_->store(s, "saved_order_info");
        }
        if (saved_credentials_ == nullptr) {
            s.store_field("saved_credentials", "null");
        } else {
            saved_credentials_->store(s, "saved_credentials");
        }
        s.store_field("can_save_credentials", can_save_credentials_);
        s.store_field("need_password", need_password_);
        s.store_class_end();
    }
}

paymentReceipt::paymentReceipt()
    : date_()
    , payments_provider_user_id_()
    , invoice_()
    , order_info_()
    , shipping_option_()
    , credentials_title_()
{}

paymentReceipt::paymentReceipt(int32_t date_, int32_t payments_provider_user_id_,
                               object_ptr<invoice> &&invoice_, object_ptr<orderInfo> &&order_info_,
                               object_ptr<shippingOption> &&shipping_option_, std::string const &credentials_title_)
    : date_(date_)
    , payments_provider_user_id_(payments_provider_user_id_)
    , invoice_(std::move(invoice_))
    , order_info_(std::move(order_info_))
    , shipping_option_(std::move(shipping_option_))
    , credentials_title_(std::move(credentials_title_))
{}

const int32_t paymentReceipt::ID;

void paymentReceipt::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "paymentReceipt");
        s.store_field("date", date_);
        s.store_field("payments_provider_user_id", payments_provider_user_id_);
        if (invoice_ == nullptr) {
            s.store_field("invoice", "null");
        } else {
            invoice_->store(s, "invoice");
        }
        if (order_info_ == nullptr) {
            s.store_field("order_info", "null");
        } else {
            order_info_->store(s, "order_info");
        }
        if (shipping_option_ == nullptr) {
            s.store_field("shipping_option", "null");
        } else {
            shipping_option_->store(s, "shipping_option");
        }
        s.store_field("credentials_title", credentials_title_);
        s.store_class_end();
    }
}

paymentResult::paymentResult()
    : success_()
    , verification_url_()
{}

paymentResult::paymentResult(bool success_, std::string const &verification_url_)
    : success_(success_)
    , verification_url_(std::move(verification_url_))
{}

const int32_t paymentResult::ID;

void paymentResult::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "paymentResult");
        s.store_field("success", success_);
        s.store_field("verification_url", verification_url_);
        s.store_class_end();
    }
}

paymentsProviderStripe::paymentsProviderStripe()
    : publishable_key_()
    , need_country_()
    , need_postal_code_()
    , need_cardholder_name_()
{}

paymentsProviderStripe::paymentsProviderStripe(std::string const &publishable_key_,
                                               bool need_country_, bool need_postal_code_, bool need_cardholder_name_)
    : publishable_key_(std::move(publishable_key_))
    , need_country_(need_country_)
    , need_postal_code_(need_postal_code_)
    , need_cardholder_name_(need_cardholder_name_)
{}

const int32_t paymentsProviderStripe::ID;

void paymentsProviderStripe::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "paymentsProviderStripe");
        s.store_field("publishable_key", publishable_key_);
        s.store_field("need_country", need_country_);
        s.store_field("need_postal_code", need_postal_code_);
        s.store_field("need_cardholder_name", need_cardholder_name_);
        s.store_class_end();
    }
}

photo::photo()
    : id_()
    , has_stickers_()
    , sizes_()
{}

photo::photo(std::int64_t id_, bool has_stickers_, std::vector<object_ptr<photoSize>> &&sizes_)
    : id_(id_)
    , has_stickers_(has_stickers_)
    , sizes_(std::move(sizes_))
{}

const int32_t photo::ID;

void photo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "photo");
        s.store_field("id", id_);
        s.store_field("has_stickers", has_stickers_);
        {
            const std::vector<object_ptr<photoSize>> &v = sizes_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sizes", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

photoSize::photoSize()
    : type_()
    , photo_()
    , width_()
    , height_()
{}

photoSize::photoSize(std::string const &type_, object_ptr<file> &&photo_, int32_t width_,
                     int32_t height_)
    : type_(std::move(type_))
    , photo_(std::move(photo_))
    , width_(width_)
    , height_(height_)
{}

const int32_t photoSize::ID;

void photoSize::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "photoSize");
        s.store_field("type", type_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_field("width", width_);
        s.store_field("height", height_);
        s.store_class_end();
    }
}

profilePhoto::profilePhoto()
    : id_()
    , small_()
    , big_()
{}

profilePhoto::profilePhoto(std::int64_t id_, object_ptr<file> &&small_, object_ptr<file> &&big_)
    : id_(id_)
    , small_(std::move(small_))
    , big_(std::move(big_))
{}

const int32_t profilePhoto::ID;

void profilePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "profilePhoto");
        s.store_field("id", id_);
        if (small_ == nullptr) {
            s.store_field("small", "null");
        } else {
            small_->store(s, "small");
        }
        if (big_ == nullptr) {
            s.store_field("big", "null");
        } else {
            big_->store(s, "big");
        }
        s.store_class_end();
    }
}

proxyEmpty::proxyEmpty()
{
}

const int32_t proxyEmpty::ID;

void proxyEmpty::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "proxyEmpty");
        s.store_class_end();
    }
}

proxySocks5::proxySocks5()
    : server_()
    , port_()
    , username_()
    , password_()
{}

proxySocks5::proxySocks5(std::string const &server_, int32_t port_,
                         std::string const &username_, std::string const &password_)
    : server_(std::move(server_))
    , port_(port_)
    , username_(std::move(username_))
    , password_(std::move(password_))
{}

const int32_t proxySocks5::ID;

void proxySocks5::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "proxySocks5");
        s.store_field("server", server_);
        s.store_field("port", port_);
        s.store_field("username", username_);
        s.store_field("password", password_);
        s.store_class_end();
    }
}

publicMessageLink::publicMessageLink()
    : link_()
    , html_()
{}

publicMessageLink::publicMessageLink(std::string const &link_, std::string const &html_)
    : link_(std::move(link_))
    , html_(std::move(html_))
{}

const int32_t publicMessageLink::ID;

void publicMessageLink::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "publicMessageLink");
        s.store_field("link", link_);
        s.store_field("html", html_);
        s.store_class_end();
    }
}

recoveryEmailAddress::recoveryEmailAddress()
    : recovery_email_address_()
{}

recoveryEmailAddress::recoveryEmailAddress(std::string const &recovery_email_address_)
    : recovery_email_address_(std::move(recovery_email_address_))
{}

const int32_t recoveryEmailAddress::ID;

void recoveryEmailAddress::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "recoveryEmailAddress");
        s.store_field("recovery_email_address", recovery_email_address_);
        s.store_class_end();
    }
}

remoteFile::remoteFile()
    : id_()
    , is_uploading_active_()
    , is_uploading_completed_()
    , uploaded_size_()
{}

remoteFile::remoteFile(std::string const &id_, bool is_uploading_active_,
                       bool is_uploading_completed_, int32_t uploaded_size_)
    : id_(std::move(id_))
    , is_uploading_active_(is_uploading_active_)
    , is_uploading_completed_(is_uploading_completed_)
    , uploaded_size_(uploaded_size_)
{}

const int32_t remoteFile::ID;

void remoteFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "remoteFile");
        s.store_field("id", id_);
        s.store_field("is_uploading_active", is_uploading_active_);
        s.store_field("is_uploading_completed", is_uploading_completed_);
        s.store_field("uploaded_size", uploaded_size_);
        s.store_class_end();
    }
}

replyMarkupRemoveKeyboard::replyMarkupRemoveKeyboard()
    : is_personal_()
{}

replyMarkupRemoveKeyboard::replyMarkupRemoveKeyboard(bool is_personal_)
    : is_personal_(is_personal_)
{}

const int32_t replyMarkupRemoveKeyboard::ID;

void replyMarkupRemoveKeyboard::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "replyMarkupRemoveKeyboard");
        s.store_field("is_personal", is_personal_);
        s.store_class_end();
    }
}

replyMarkupForceReply::replyMarkupForceReply()
    : is_personal_()
{}

replyMarkupForceReply::replyMarkupForceReply(bool is_personal_)
    : is_personal_(is_personal_)
{}

const int32_t replyMarkupForceReply::ID;

void replyMarkupForceReply::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "replyMarkupForceReply");
        s.store_field("is_personal", is_personal_);
        s.store_class_end();
    }
}

replyMarkupShowKeyboard::replyMarkupShowKeyboard()
    : rows_()
    , resize_keyboard_()
    , one_time_()
    , is_personal_()
{}

replyMarkupShowKeyboard::replyMarkupShowKeyboard(
    std::vector<std::vector<object_ptr<keyboardButton>>> &&rows_, bool resize_keyboard_, bool one_time_,
    bool is_personal_)
    : rows_(std::move(rows_))
    , resize_keyboard_(resize_keyboard_)
    , one_time_(one_time_)
    , is_personal_(is_personal_)
{}

const int32_t replyMarkupShowKeyboard::ID;

void replyMarkupShowKeyboard::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "replyMarkupShowKeyboard");
        {
            const std::vector<std::vector<object_ptr<keyboardButton>>> &v = rows_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("rows", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                {
                    const std::vector<object_ptr<keyboardButton>> &v2 = v[i];
                    const std::uint32_t multiplicity2 = static_cast<std::uint32_t>(v2.size());
                    const auto vector_name2 = "vector[" + std::to_string(multiplicity2) + "]";
                    s.store_class_begin("", vector_name2.c_str());
                    for (std::uint32_t i2 = 0; i2 < multiplicity2; i2++) {
                        if (v2[i2] == nullptr) {
                            s.store_field("", "null");
                        } else {
                            v2[i2]->store(s, "");
                        }
                    }
                    s.store_class_end();
                }
            }
            s.store_class_end();
        }
        s.store_field("resize_keyboard", resize_keyboard_);
        s.store_field("one_time", one_time_);
        s.store_field("is_personal", is_personal_);
        s.store_class_end();
    }
}

replyMarkupInlineKeyboard::replyMarkupInlineKeyboard()
    : rows_()
{}

replyMarkupInlineKeyboard::replyMarkupInlineKeyboard(
    std::vector<std::vector<object_ptr<inlineKeyboardButton>>> &&rows_)
    : rows_(std::move(rows_))
{}

const int32_t replyMarkupInlineKeyboard::ID;

void replyMarkupInlineKeyboard::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "replyMarkupInlineKeyboard");
        {
            const std::vector<std::vector<object_ptr<inlineKeyboardButton>>> &v = rows_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("rows", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                {
                    const std::vector<object_ptr<inlineKeyboardButton>> &v2 = v[i];
                    const std::uint32_t multiplicity2 = static_cast<std::uint32_t>(v2.size());
                    const auto vector_name2 = "vector[" + std::to_string(multiplicity2) + "]";
                    s.store_class_begin("", vector_name2.c_str());
                    for (std::uint32_t i2 = 0; i2 < multiplicity2; i2++) {
                        if (v2[i2] == nullptr) {
                            s.store_field("", "null");
                        } else {
                            v2[i2]->store(s, "");
                        }
                    }
                    s.store_class_end();
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

richTextPlain::richTextPlain()
    : text_()
{}

richTextPlain::richTextPlain(std::string const &text_)
    : text_(std::move(text_))
{}

const int32_t richTextPlain::ID;

void richTextPlain::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTextPlain");
        s.store_field("text", text_);
        s.store_class_end();
    }
}

richTextBold::richTextBold()
    : text_()
{}

richTextBold::richTextBold(object_ptr<RichText> &&text_)
    : text_(std::move(text_))
{}

const int32_t richTextBold::ID;

void richTextBold::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTextBold");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_class_end();
    }
}

richTextItalic::richTextItalic()
    : text_()
{}

richTextItalic::richTextItalic(object_ptr<RichText> &&text_)
    : text_(std::move(text_))
{}

const int32_t richTextItalic::ID;

void richTextItalic::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTextItalic");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_class_end();
    }
}

richTextUnderline::richTextUnderline()
    : text_()
{}

richTextUnderline::richTextUnderline(object_ptr<RichText> &&text_)
    : text_(std::move(text_))
{}

const int32_t richTextUnderline::ID;

void richTextUnderline::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTextUnderline");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_class_end();
    }
}

richTextStrikethrough::richTextStrikethrough()
    : text_()
{}

richTextStrikethrough::richTextStrikethrough(object_ptr<RichText> &&text_)
    : text_(std::move(text_))
{}

const int32_t richTextStrikethrough::ID;

void richTextStrikethrough::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTextStrikethrough");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_class_end();
    }
}

richTextFixed::richTextFixed()
    : text_()
{}

richTextFixed::richTextFixed(object_ptr<RichText> &&text_)
    : text_(std::move(text_))
{}

const int32_t richTextFixed::ID;

void richTextFixed::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTextFixed");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_class_end();
    }
}

richTextUrl::richTextUrl()
    : text_()
    , url_()
{}

richTextUrl::richTextUrl(object_ptr<RichText> &&text_, std::string const &url_)
    : text_(std::move(text_))
    , url_(std::move(url_))
{}

const int32_t richTextUrl::ID;

void richTextUrl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTextUrl");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_field("url", url_);
        s.store_class_end();
    }
}

richTextEmailAddress::richTextEmailAddress()
    : text_()
    , email_address_()
{}

richTextEmailAddress::richTextEmailAddress(object_ptr<RichText> &&text_,
                                           std::string const &email_address_)
    : text_(std::move(text_))
    , email_address_(std::move(email_address_))
{}

const int32_t richTextEmailAddress::ID;

void richTextEmailAddress::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTextEmailAddress");
        if (text_ == nullptr) {
            s.store_field("text", "null");
        } else {
            text_->store(s, "text");
        }
        s.store_field("email_address", email_address_);
        s.store_class_end();
    }
}

richTexts::richTexts()
    : texts_()
{}

richTexts::richTexts(std::vector<object_ptr<RichText>> &&texts_)
    : texts_(std::move(texts_))
{}

const int32_t richTexts::ID;

void richTexts::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "richTexts");
        {
            const std::vector<object_ptr<RichText>> &v = texts_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("texts", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

savedCredentials::savedCredentials()
    : id_()
    , title_()
{}

savedCredentials::savedCredentials(std::string const &id_, std::string const &title_)
    : id_(std::move(id_))
    , title_(std::move(title_))
{}

const int32_t savedCredentials::ID;

void savedCredentials::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "savedCredentials");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_class_end();
    }
}

searchMessagesFilterEmpty::searchMessagesFilterEmpty()
{
}

const int32_t searchMessagesFilterEmpty::ID;

void searchMessagesFilterEmpty::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterEmpty");
        s.store_class_end();
    }
}

searchMessagesFilterAnimation::searchMessagesFilterAnimation()
{
}

const int32_t searchMessagesFilterAnimation::ID;

void searchMessagesFilterAnimation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterAnimation");
        s.store_class_end();
    }
}

searchMessagesFilterAudio::searchMessagesFilterAudio()
{
}

const int32_t searchMessagesFilterAudio::ID;

void searchMessagesFilterAudio::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterAudio");
        s.store_class_end();
    }
}

searchMessagesFilterDocument::searchMessagesFilterDocument()
{
}

const int32_t searchMessagesFilterDocument::ID;

void searchMessagesFilterDocument::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterDocument");
        s.store_class_end();
    }
}

searchMessagesFilterPhoto::searchMessagesFilterPhoto()
{
}

const int32_t searchMessagesFilterPhoto::ID;

void searchMessagesFilterPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterPhoto");
        s.store_class_end();
    }
}

searchMessagesFilterVideo::searchMessagesFilterVideo()
{
}

const int32_t searchMessagesFilterVideo::ID;

void searchMessagesFilterVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterVideo");
        s.store_class_end();
    }
}

searchMessagesFilterVoiceNote::searchMessagesFilterVoiceNote()
{
}

const int32_t searchMessagesFilterVoiceNote::ID;

void searchMessagesFilterVoiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterVoiceNote");
        s.store_class_end();
    }
}

searchMessagesFilterPhotoAndVideo::searchMessagesFilterPhotoAndVideo()
{
}

const int32_t searchMessagesFilterPhotoAndVideo::ID;

void searchMessagesFilterPhotoAndVideo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterPhotoAndVideo");
        s.store_class_end();
    }
}

searchMessagesFilterUrl::searchMessagesFilterUrl()
{
}

const int32_t searchMessagesFilterUrl::ID;

void searchMessagesFilterUrl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterUrl");
        s.store_class_end();
    }
}

searchMessagesFilterChatPhoto::searchMessagesFilterChatPhoto()
{
}

const int32_t searchMessagesFilterChatPhoto::ID;

void searchMessagesFilterChatPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterChatPhoto");
        s.store_class_end();
    }
}

searchMessagesFilterCall::searchMessagesFilterCall()
{
}

const int32_t searchMessagesFilterCall::ID;

void searchMessagesFilterCall::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterCall");
        s.store_class_end();
    }
}

searchMessagesFilterMissedCall::searchMessagesFilterMissedCall()
{
}

const int32_t searchMessagesFilterMissedCall::ID;

void searchMessagesFilterMissedCall::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterMissedCall");
        s.store_class_end();
    }
}

searchMessagesFilterVideoNote::searchMessagesFilterVideoNote()
{
}

const int32_t searchMessagesFilterVideoNote::ID;

void searchMessagesFilterVideoNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterVideoNote");
        s.store_class_end();
    }
}

searchMessagesFilterVoiceAndVideoNote::searchMessagesFilterVoiceAndVideoNote()
{
}

const int32_t searchMessagesFilterVoiceAndVideoNote::ID;

void searchMessagesFilterVoiceAndVideoNote::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterVoiceAndVideoNote");
        s.store_class_end();
    }
}

searchMessagesFilterMention::searchMessagesFilterMention()
{
}

const int32_t searchMessagesFilterMention::ID;

void searchMessagesFilterMention::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterMention");
        s.store_class_end();
    }
}

searchMessagesFilterUnreadMention::searchMessagesFilterUnreadMention()
{
}

const int32_t searchMessagesFilterUnreadMention::ID;

void searchMessagesFilterUnreadMention::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessagesFilterUnreadMention");
        s.store_class_end();
    }
}

secretChat::secretChat()
    : id_()
    , user_id_()
    , state_()
    , is_outbound_()
    , ttl_()
    , key_hash_()
    , layer_()
{}

secretChat::secretChat(int32_t id_, int32_t user_id_,
                       object_ptr<SecretChatState> &&state_, bool is_outbound_, int32_t ttl_,
                       std::string const &key_hash_, int32_t layer_)
    : id_(id_)
    , user_id_(user_id_)
    , state_(std::move(state_))
    , is_outbound_(is_outbound_)
    , ttl_(ttl_)
    , key_hash_(std::move(key_hash_))
    , layer_(layer_)
{}

const int32_t secretChat::ID;

void secretChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "secretChat");
        s.store_field("id", id_);
        s.store_field("user_id", user_id_);
        if (state_ == nullptr) {
            s.store_field("state", "null");
        } else {
            state_->store(s, "state");
        }
        s.store_field("is_outbound", is_outbound_);
        s.store_field("ttl", ttl_);
        s.store_bytes_field("key_hash", key_hash_);
        s.store_field("layer", layer_);
        s.store_class_end();
    }
}

secretChatStatePending::secretChatStatePending()
{
}

const int32_t secretChatStatePending::ID;

void secretChatStatePending::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "secretChatStatePending");
        s.store_class_end();
    }
}

secretChatStateReady::secretChatStateReady()
{
}

const int32_t secretChatStateReady::ID;

void secretChatStateReady::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "secretChatStateReady");
        s.store_class_end();
    }
}

secretChatStateClosed::secretChatStateClosed()
{
}

const int32_t secretChatStateClosed::ID;

void secretChatStateClosed::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "secretChatStateClosed");
        s.store_class_end();
    }
}

session::session()
    : id_()
    , is_current_()
    , api_id_()
    , application_name_()
    , application_version_()
    , is_official_application_()
    , device_model_()
    , platform_()
    , system_version_()
    , log_in_date_()
    , last_active_date_()
    , ip_()
    , country_()
    , region_()
{}

session::session(std::int64_t id_, bool is_current_, int32_t api_id_,
                 std::string const &application_name_, std::string const &application_version_,
                 bool is_official_application_, std::string const &device_model_, std::string const &platform_,
                 std::string const &system_version_, int32_t log_in_date_, int32_t last_active_date_,
                 std::string const &ip_, std::string const &country_, std::string const &region_)
    : id_(id_)
    , is_current_(is_current_)
    , api_id_(api_id_)
    , application_name_(std::move(application_name_))
    , application_version_(std::move(application_version_))
    , is_official_application_(is_official_application_)
    , device_model_(std::move(device_model_))
    , platform_(std::move(platform_))
    , system_version_(std::move(system_version_))
    , log_in_date_(log_in_date_)
    , last_active_date_(last_active_date_)
    , ip_(std::move(ip_))
    , country_(std::move(country_))
    , region_(std::move(region_))
{}

const int32_t session::ID;

void session::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "session");
        s.store_field("id", id_);
        s.store_field("is_current", is_current_);
        s.store_field("api_id", api_id_);
        s.store_field("application_name", application_name_);
        s.store_field("application_version", application_version_);
        s.store_field("is_official_application", is_official_application_);
        s.store_field("device_model", device_model_);
        s.store_field("platform", platform_);
        s.store_field("system_version", system_version_);
        s.store_field("log_in_date", log_in_date_);
        s.store_field("last_active_date", last_active_date_);
        s.store_field("ip", ip_);
        s.store_field("country", country_);
        s.store_field("region", region_);
        s.store_class_end();
    }
}

sessions::sessions()
    : sessions_()
{}

sessions::sessions(std::vector<object_ptr<session>> &&sessions_)
    : sessions_(std::move(sessions_))
{}

const int32_t sessions::ID;

void sessions::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sessions");
        {
            const std::vector<object_ptr<session>> &v = sessions_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sessions", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

shippingAddress::shippingAddress()
    : country_code_()
    , state_()
    , city_()
    , street_line1_()
    , street_line2_()
    , postal_code_()
{}

shippingAddress::shippingAddress(std::string const &country_code_, std::string const &state_,
                                 std::string const &city_, std::string const &street_line1_, std::string const &street_line2_,
                                 std::string const &postal_code_)
    : country_code_(std::move(country_code_))
    , state_(std::move(state_))
    , city_(std::move(city_))
    , street_line1_(std::move(street_line1_))
    , street_line2_(std::move(street_line2_))
    , postal_code_(std::move(postal_code_))
{}

const int32_t shippingAddress::ID;

void shippingAddress::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "shippingAddress");
        s.store_field("country_code", country_code_);
        s.store_field("state", state_);
        s.store_field("city", city_);
        s.store_field("street_line1", street_line1_);
        s.store_field("street_line2", street_line2_);
        s.store_field("postal_code", postal_code_);
        s.store_class_end();
    }
}

shippingOption::shippingOption()
    : id_()
    , title_()
    , price_parts_()
{}

shippingOption::shippingOption(std::string const &id_, std::string const &title_,
                               std::vector<object_ptr<labeledPricePart>> &&price_parts_)
    : id_(std::move(id_))
    , title_(std::move(title_))
    , price_parts_(std::move(price_parts_))
{}

const int32_t shippingOption::ID;

void shippingOption::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "shippingOption");
        s.store_field("id", id_);
        s.store_field("title", title_);
        {
            const std::vector<object_ptr<labeledPricePart>> &v = price_parts_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("price_parts", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

sticker::sticker()
    : set_id_()
    , width_()
    , height_()
    , emoji_()
    , is_mask_()
    , mask_position_()
    , thumbnail_()
    , sticker_()
{}

sticker::sticker(std::int64_t set_id_, int32_t width_, int32_t height_,
                 std::string const &emoji_, bool is_mask_, object_ptr<maskPosition> &&mask_position_,
                 object_ptr<photoSize> &&thumbnail_, object_ptr<file> &&sticker_)
    : set_id_(set_id_)
    , width_(width_)
    , height_(height_)
    , emoji_(std::move(emoji_))
    , is_mask_(is_mask_)
    , mask_position_(std::move(mask_position_))
    , thumbnail_(std::move(thumbnail_))
    , sticker_(std::move(sticker_))
{}

const int32_t sticker::ID;

void sticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sticker");
        s.store_field("set_id", set_id_);
        s.store_field("width", width_);
        s.store_field("height", height_);
        s.store_field("emoji", emoji_);
        s.store_field("is_mask", is_mask_);
        if (mask_position_ == nullptr) {
            s.store_field("mask_position", "null");
        } else {
            mask_position_->store(s, "mask_position");
        }
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

stickerEmojis::stickerEmojis()
    : emojis_()
{}

stickerEmojis::stickerEmojis(std::vector<std::string> &&emojis_)
    : emojis_(std::move(emojis_))
{}

const int32_t stickerEmojis::ID;

void stickerEmojis::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "stickerEmojis");
        {
            const std::vector<std::string> &v = emojis_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("emojis", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

stickerSet::stickerSet()
    : id_()
    , title_()
    , name_()
    , is_installed_()
    , is_archived_()
    , is_official_()
    , is_masks_()
    , is_viewed_()
    , stickers_()
    , emojis_()
{}

stickerSet::stickerSet(std::int64_t id_, std::string const &title_, std::string const &name_,
                       bool is_installed_, bool is_archived_, bool is_official_, bool is_masks_, bool is_viewed_,
                       std::vector<object_ptr<sticker>> &&stickers_, std::vector<object_ptr<stickerEmojis>> &&emojis_)
    : id_(id_)
    , title_(std::move(title_))
    , name_(std::move(name_))
    , is_installed_(is_installed_)
    , is_archived_(is_archived_)
    , is_official_(is_official_)
    , is_masks_(is_masks_)
    , is_viewed_(is_viewed_)
    , stickers_(std::move(stickers_))
    , emojis_(std::move(emojis_))
{}

const int32_t stickerSet::ID;

void stickerSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "stickerSet");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("name", name_);
        s.store_field("is_installed", is_installed_);
        s.store_field("is_archived", is_archived_);
        s.store_field("is_official", is_official_);
        s.store_field("is_masks", is_masks_);
        s.store_field("is_viewed", is_viewed_);
        {
            const std::vector<object_ptr<sticker>> &v = stickers_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("stickers", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        {
            const std::vector<object_ptr<stickerEmojis>> &v = emojis_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("emojis", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

stickerSetInfo::stickerSetInfo()
    : id_()
    , title_()
    , name_()
    , is_installed_()
    , is_archived_()
    , is_official_()
    , is_masks_()
    , is_viewed_()
    , size_()
    , covers_()
{}

stickerSetInfo::stickerSetInfo(std::int64_t id_, std::string const &title_,
                               std::string const &name_, bool is_installed_, bool is_archived_, bool is_official_, bool is_masks_,
                               bool is_viewed_, int32_t size_, std::vector<object_ptr<sticker>> &&covers_)
    : id_(id_)
    , title_(std::move(title_))
    , name_(std::move(name_))
    , is_installed_(is_installed_)
    , is_archived_(is_archived_)
    , is_official_(is_official_)
    , is_masks_(is_masks_)
    , is_viewed_(is_viewed_)
    , size_(size_)
    , covers_(std::move(covers_))
{}

const int32_t stickerSetInfo::ID;

void stickerSetInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "stickerSetInfo");
        s.store_field("id", id_);
        s.store_field("title", title_);
        s.store_field("name", name_);
        s.store_field("is_installed", is_installed_);
        s.store_field("is_archived", is_archived_);
        s.store_field("is_official", is_official_);
        s.store_field("is_masks", is_masks_);
        s.store_field("is_viewed", is_viewed_);
        s.store_field("size", size_);
        {
            const std::vector<object_ptr<sticker>> &v = covers_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("covers", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

stickerSets::stickerSets()
    : total_count_()
    , sets_()
{}

stickerSets::stickerSets(int32_t total_count_, std::vector<object_ptr<stickerSetInfo>> &&sets_)
    : total_count_(total_count_)
    , sets_(std::move(sets_))
{}

const int32_t stickerSets::ID;

void stickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "stickerSets");
        s.store_field("total_count", total_count_);
        {
            const std::vector<object_ptr<stickerSetInfo>> &v = sets_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sets", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

stickers::stickers()
    : stickers_()
{}

stickers::stickers(std::vector<object_ptr<sticker>> &&stickers_)
    : stickers_(std::move(stickers_))
{}

const int32_t stickers::ID;

void stickers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "stickers");
        {
            const std::vector<object_ptr<sticker>> &v = stickers_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("stickers", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

storageStatistics::storageStatistics()
    : size_()
    , count_()
    , by_chat_()
{}

storageStatistics::storageStatistics(std::int64_t size_, int32_t count_,
                                     std::vector<object_ptr<storageStatisticsByChat>> &&by_chat_)
    : size_(size_)
    , count_(count_)
    , by_chat_(std::move(by_chat_))
{}

const int32_t storageStatistics::ID;

void storageStatistics::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "storageStatistics");
        s.store_field("size", size_);
        s.store_field("count", count_);
        {
            const std::vector<object_ptr<storageStatisticsByChat>> &v = by_chat_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("by_chat", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

storageStatisticsByChat::storageStatisticsByChat()
    : chat_id_()
    , size_()
    , count_()
    , by_file_type_()
{}

storageStatisticsByChat::storageStatisticsByChat(std::int64_t chat_id_, std::int64_t size_,
                                                 int32_t count_, std::vector<object_ptr<storageStatisticsByFileType>> &&by_file_type_)
    : chat_id_(chat_id_)
    , size_(size_)
    , count_(count_)
    , by_file_type_(std::move(by_file_type_))
{}

const int32_t storageStatisticsByChat::ID;

void storageStatisticsByChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "storageStatisticsByChat");
        s.store_field("chat_id", chat_id_);
        s.store_field("size", size_);
        s.store_field("count", count_);
        {
            const std::vector<object_ptr<storageStatisticsByFileType>> &v = by_file_type_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("by_file_type", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

storageStatisticsByFileType::storageStatisticsByFileType()
    : file_type_()
    , size_()
    , count_()
{}

storageStatisticsByFileType::storageStatisticsByFileType(object_ptr<FileType> &&file_type_,
                                                         std::int64_t size_, int32_t count_)
    : file_type_(std::move(file_type_))
    , size_(size_)
    , count_(count_)
{}

const int32_t storageStatisticsByFileType::ID;

void storageStatisticsByFileType::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "storageStatisticsByFileType");
        if (file_type_ == nullptr) {
            s.store_field("file_type", "null");
        } else {
            file_type_->store(s, "file_type");
        }
        s.store_field("size", size_);
        s.store_field("count", count_);
        s.store_class_end();
    }
}

storageStatisticsFast::storageStatisticsFast()
    : files_size_()
    , file_count_()
    , database_size_()
{}

storageStatisticsFast::storageStatisticsFast(std::int64_t files_size_, int32_t file_count_,
                                             std::int64_t database_size_)
    : files_size_(files_size_)
    , file_count_(file_count_)
    , database_size_(database_size_)
{}

const int32_t storageStatisticsFast::ID;

void storageStatisticsFast::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "storageStatisticsFast");
        s.store_field("files_size", files_size_);
        s.store_field("file_count", file_count_);
        s.store_field("database_size", database_size_);
        s.store_class_end();
    }
}

supergroup::supergroup()
    : id_()
    , username_()
    , date_()
    , status_()
    , member_count_()
    , anyone_can_invite_()
    , sign_messages_()
    , is_channel_()
    , is_verified_()
    , restriction_reason_()
{}

supergroup::supergroup(int32_t id_, std::string const &username_, int32_t date_,
                       object_ptr<ChatMemberStatus> &&status_, int32_t member_count_, bool anyone_can_invite_,
                       bool sign_messages_, bool is_channel_, bool is_verified_, std::string const &restriction_reason_)
    : id_(id_)
    , username_(std::move(username_))
    , date_(date_)
    , status_(std::move(status_))
    , member_count_(member_count_)
    , anyone_can_invite_(anyone_can_invite_)
    , sign_messages_(sign_messages_)
    , is_channel_(is_channel_)
    , is_verified_(is_verified_)
    , restriction_reason_(std::move(restriction_reason_))
{}

const int32_t supergroup::ID;

void supergroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "supergroup");
        s.store_field("id", id_);
        s.store_field("username", username_);
        s.store_field("date", date_);
        if (status_ == nullptr) {
            s.store_field("status", "null");
        } else {
            status_->store(s, "status");
        }
        s.store_field("member_count", member_count_);
        s.store_field("anyone_can_invite", anyone_can_invite_);
        s.store_field("sign_messages", sign_messages_);
        s.store_field("is_channel", is_channel_);
        s.store_field("is_verified", is_verified_);
        s.store_field("restriction_reason", restriction_reason_);
        s.store_class_end();
    }
}

supergroupFullInfo::supergroupFullInfo()
    : description_()
    , member_count_()
    , administrator_count_()
    , restricted_count_()
    , banned_count_()
    , can_get_members_()
    , can_set_username_()
    , can_set_sticker_set_()
    , is_all_history_available_()
    , sticker_set_id_()
    , invite_link_()
    , pinned_message_id_()
    , upgraded_from_basic_group_id_()
    , upgraded_from_max_message_id_()
{}

supergroupFullInfo::supergroupFullInfo(std::string const &description_, int32_t member_count_,
                                       int32_t administrator_count_, int32_t restricted_count_, int32_t banned_count_,
                                       bool can_get_members_, bool can_set_username_, bool can_set_sticker_set_,
                                       bool is_all_history_available_, std::int64_t sticker_set_id_, std::string const &invite_link_,
                                       std::int64_t pinned_message_id_, int32_t upgraded_from_basic_group_id_,
                                       std::int64_t upgraded_from_max_message_id_)
    : description_(std::move(description_))
    , member_count_(member_count_)
    , administrator_count_(administrator_count_)
    , restricted_count_(restricted_count_)
    , banned_count_(banned_count_)
    , can_get_members_(can_get_members_)
    , can_set_username_(can_set_username_)
    , can_set_sticker_set_(can_set_sticker_set_)
    , is_all_history_available_(is_all_history_available_)
    , sticker_set_id_(sticker_set_id_)
    , invite_link_(std::move(invite_link_))
    , pinned_message_id_(pinned_message_id_)
    , upgraded_from_basic_group_id_(upgraded_from_basic_group_id_)
    , upgraded_from_max_message_id_(upgraded_from_max_message_id_)
{}

const int32_t supergroupFullInfo::ID;

void supergroupFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "supergroupFullInfo");
        s.store_field("description", description_);
        s.store_field("member_count", member_count_);
        s.store_field("administrator_count", administrator_count_);
        s.store_field("restricted_count", restricted_count_);
        s.store_field("banned_count", banned_count_);
        s.store_field("can_get_members", can_get_members_);
        s.store_field("can_set_username", can_set_username_);
        s.store_field("can_set_sticker_set", can_set_sticker_set_);
        s.store_field("is_all_history_available", is_all_history_available_);
        s.store_field("sticker_set_id", sticker_set_id_);
        s.store_field("invite_link", invite_link_);
        s.store_field("pinned_message_id", pinned_message_id_);
        s.store_field("upgraded_from_basic_group_id", upgraded_from_basic_group_id_);
        s.store_field("upgraded_from_max_message_id", upgraded_from_max_message_id_);
        s.store_class_end();
    }
}

supergroupMembersFilterRecent::supergroupMembersFilterRecent()
{
}

const int32_t supergroupMembersFilterRecent::ID;

void supergroupMembersFilterRecent::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "supergroupMembersFilterRecent");
        s.store_class_end();
    }
}

supergroupMembersFilterAdministrators::supergroupMembersFilterAdministrators()
{
}

const int32_t supergroupMembersFilterAdministrators::ID;

void supergroupMembersFilterAdministrators::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "supergroupMembersFilterAdministrators");
        s.store_class_end();
    }
}

supergroupMembersFilterSearch::supergroupMembersFilterSearch()
    : query_()
{}

supergroupMembersFilterSearch::supergroupMembersFilterSearch(std::string const &query_)
    : query_(std::move(query_))
{}

const int32_t supergroupMembersFilterSearch::ID;

void supergroupMembersFilterSearch::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "supergroupMembersFilterSearch");
        s.store_field("query", query_);
        s.store_class_end();
    }
}

supergroupMembersFilterRestricted::supergroupMembersFilterRestricted()
    : query_()
{}

supergroupMembersFilterRestricted::supergroupMembersFilterRestricted(std::string const &query_)
    : query_(std::move(query_))
{}

const int32_t supergroupMembersFilterRestricted::ID;

void supergroupMembersFilterRestricted::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "supergroupMembersFilterRestricted");
        s.store_field("query", query_);
        s.store_class_end();
    }
}

supergroupMembersFilterBanned::supergroupMembersFilterBanned()
    : query_()
{}

supergroupMembersFilterBanned::supergroupMembersFilterBanned(std::string const &query_)
    : query_(std::move(query_))
{}

const int32_t supergroupMembersFilterBanned::ID;

void supergroupMembersFilterBanned::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "supergroupMembersFilterBanned");
        s.store_field("query", query_);
        s.store_class_end();
    }
}

supergroupMembersFilterBots::supergroupMembersFilterBots()
{
}

const int32_t supergroupMembersFilterBots::ID;

void supergroupMembersFilterBots::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "supergroupMembersFilterBots");
        s.store_class_end();
    }
}

tMeUrl::tMeUrl()
    : url_()
    , type_()
{}

tMeUrl::tMeUrl(std::string const &url_, object_ptr<TMeUrlType> &&type_)
    : url_(std::move(url_))
    , type_(std::move(type_))
{}

const int32_t tMeUrl::ID;

void tMeUrl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "tMeUrl");
        s.store_field("url", url_);
        if (type_ == nullptr) {
            s.store_field("type", "null");
        } else {
            type_->store(s, "type");
        }
        s.store_class_end();
    }
}

tMeUrlTypeUser::tMeUrlTypeUser()
    : user_id_()
{}

tMeUrlTypeUser::tMeUrlTypeUser(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t tMeUrlTypeUser::ID;

void tMeUrlTypeUser::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "tMeUrlTypeUser");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

tMeUrlTypeSupergroup::tMeUrlTypeSupergroup()
    : supergroup_id_()
{}

tMeUrlTypeSupergroup::tMeUrlTypeSupergroup(std::int64_t supergroup_id_)
    : supergroup_id_(supergroup_id_)
{}

const int32_t tMeUrlTypeSupergroup::ID;

void tMeUrlTypeSupergroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "tMeUrlTypeSupergroup");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_class_end();
    }
}

tMeUrlTypeChatInvite::tMeUrlTypeChatInvite()
    : info_()
{}

tMeUrlTypeChatInvite::tMeUrlTypeChatInvite(object_ptr<chatInviteLinkInfo> &&info_)
    : info_(std::move(info_))
{}

const int32_t tMeUrlTypeChatInvite::ID;

void tMeUrlTypeChatInvite::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "tMeUrlTypeChatInvite");
        if (info_ == nullptr) {
            s.store_field("info", "null");
        } else {
            info_->store(s, "info");
        }
        s.store_class_end();
    }
}

tMeUrlTypeStickerSet::tMeUrlTypeStickerSet()
    : sticker_set_id_()
{}

tMeUrlTypeStickerSet::tMeUrlTypeStickerSet(std::int64_t sticker_set_id_)
    : sticker_set_id_(sticker_set_id_)
{}

const int32_t tMeUrlTypeStickerSet::ID;

void tMeUrlTypeStickerSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "tMeUrlTypeStickerSet");
        s.store_field("sticker_set_id", sticker_set_id_);
        s.store_class_end();
    }
}

tMeUrls::tMeUrls()
    : urls_()
{}

tMeUrls::tMeUrls(std::vector<object_ptr<tMeUrl>> &&urls_)
    : urls_(std::move(urls_))
{}

const int32_t tMeUrls::ID;

void tMeUrls::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "tMeUrls");
        {
            const std::vector<object_ptr<tMeUrl>> &v = urls_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("urls", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

tdlibParameters::tdlibParameters()
    : use_test_dc_()
    , database_directory_()
    , files_directory_()
    , use_file_database_()
    , use_chat_info_database_()
    , use_message_database_()
    , use_secret_chats_()
    , api_id_()
    , api_hash_()
    , system_language_code_()
    , device_model_()
    , system_version_()
    , application_version_()
    , enable_storage_optimizer_()
    , ignore_file_names_()
{}

tdlibParameters::tdlibParameters(bool use_test_dc_, std::string const &database_directory_,
                                 std::string const &files_directory_, bool use_file_database_, bool use_chat_info_database_,
                                 bool use_message_database_, bool use_secret_chats_, int32_t api_id_,
                                 std::string const &api_hash_, std::string const &system_language_code_,
                                 std::string const &device_model_, std::string const &system_version_,
                                 std::string const &application_version_, bool enable_storage_optimizer_, bool ignore_file_names_)
    : use_test_dc_(use_test_dc_)
    , database_directory_(std::move(database_directory_))
    , files_directory_(std::move(files_directory_))
    , use_file_database_(use_file_database_)
    , use_chat_info_database_(use_chat_info_database_)
    , use_message_database_(use_message_database_)
    , use_secret_chats_(use_secret_chats_)
    , api_id_(api_id_)
    , api_hash_(std::move(api_hash_))
    , system_language_code_(std::move(system_language_code_))
    , device_model_(std::move(device_model_))
    , system_version_(std::move(system_version_))
    , application_version_(std::move(application_version_))
    , enable_storage_optimizer_(enable_storage_optimizer_)
    , ignore_file_names_(ignore_file_names_)
{}

const int32_t tdlibParameters::ID;

void tdlibParameters::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "tdlibParameters");
        s.store_field("use_test_dc", use_test_dc_);
        s.store_field("database_directory", database_directory_);
        s.store_field("files_directory", files_directory_);
        s.store_field("use_file_database", use_file_database_);
        s.store_field("use_chat_info_database", use_chat_info_database_);
        s.store_field("use_message_database", use_message_database_);
        s.store_field("use_secret_chats", use_secret_chats_);
        s.store_field("api_id", api_id_);
        s.store_field("api_hash", api_hash_);
        s.store_field("system_language_code", system_language_code_);
        s.store_field("device_model", device_model_);
        s.store_field("system_version", system_version_);
        s.store_field("application_version", application_version_);
        s.store_field("enable_storage_optimizer", enable_storage_optimizer_);
        s.store_field("ignore_file_names", ignore_file_names_);
        s.store_class_end();
    }
}

temporaryPasswordState::temporaryPasswordState()
    : has_password_()
    , valid_for_()
{}

temporaryPasswordState::temporaryPasswordState(bool has_password_, int32_t valid_for_)
    : has_password_(has_password_)
    , valid_for_(valid_for_)
{}

const int32_t temporaryPasswordState::ID;

void temporaryPasswordState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "temporaryPasswordState");
        s.store_field("has_password", has_password_);
        s.store_field("valid_for", valid_for_);
        s.store_class_end();
    }
}

testBytes::testBytes()
    : value_()
{}

testBytes::testBytes(std::string const &value_)
    : value_(std::move(value_))
{}

const int32_t testBytes::ID;

void testBytes::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testBytes");
        s.store_bytes_field("value", value_);
        s.store_class_end();
    }
}

testInt::testInt()
    : value_()
{}

testInt::testInt(int32_t value_)
    : value_(value_)
{}

const int32_t testInt::ID;

void testInt::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testInt");
        s.store_field("value", value_);
        s.store_class_end();
    }
}

testString::testString()
    : value_()
{}

testString::testString(std::string const &value_)
    : value_(std::move(value_))
{}

const int32_t testString::ID;

void testString::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testString");
        s.store_field("value", value_);
        s.store_class_end();
    }
}

testVectorInt::testVectorInt()
    : value_()
{}

testVectorInt::testVectorInt(std::vector<int32_t> &&value_)
    : value_(std::move(value_))
{}

const int32_t testVectorInt::ID;

void testVectorInt::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testVectorInt");
        {
            const std::vector<int32_t> &v = value_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("value", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

testVectorIntObject::testVectorIntObject()
    : value_()
{}

testVectorIntObject::testVectorIntObject(std::vector<object_ptr<testInt>> &&value_)
    : value_(std::move(value_))
{}

const int32_t testVectorIntObject::ID;

void testVectorIntObject::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testVectorIntObject");
        {
            const std::vector<object_ptr<testInt>> &v = value_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("value", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

testVectorString::testVectorString()
    : value_()
{}

testVectorString::testVectorString(std::vector<std::string> &&value_)
    : value_(std::move(value_))
{}

const int32_t testVectorString::ID;

void testVectorString::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testVectorString");
        {
            const std::vector<std::string> &v = value_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("value", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

testVectorStringObject::testVectorStringObject()
    : value_()
{}

testVectorStringObject::testVectorStringObject(std::vector<object_ptr<testString>> &&value_)
    : value_(std::move(value_))
{}

const int32_t testVectorStringObject::ID;

void testVectorStringObject::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testVectorStringObject");
        {
            const std::vector<object_ptr<testString>> &v = value_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("value", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

text::text()
    : text_()
{}

text::text(std::string const &text_)
    : text_(std::move(text_))
{}

const int32_t text::ID;

void text::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "text");
        s.store_field("text", text_);
        s.store_class_end();
    }
}

textEntities::textEntities()
    : entities_()
{}

textEntities::textEntities(std::vector<object_ptr<textEntity>> &&entities_)
    : entities_(std::move(entities_))
{}

const int32_t textEntities::ID;

void textEntities::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntities");
        {
            const std::vector<object_ptr<textEntity>> &v = entities_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("entities", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

textEntity::textEntity()
    : offset_()
    , length_()
    , type_()
{}

textEntity::textEntity(int32_t offset_, int32_t length_,
                       object_ptr<TextEntityType> &&type_)
    : offset_(offset_)
    , length_(length_)
    , type_(std::move(type_))
{}

const int32_t textEntity::ID;

void textEntity::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntity");
        s.store_field("offset", offset_);
        s.store_field("length", length_);
        if (type_ == nullptr) {
            s.store_field("type", "null");
        } else {
            type_->store(s, "type");
        }
        s.store_class_end();
    }
}

textEntityTypeMention::textEntityTypeMention()
{
}

const int32_t textEntityTypeMention::ID;

void textEntityTypeMention::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeMention");
        s.store_class_end();
    }
}

textEntityTypeHashtag::textEntityTypeHashtag()
{
}

const int32_t textEntityTypeHashtag::ID;

void textEntityTypeHashtag::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeHashtag");
        s.store_class_end();
    }
}

textEntityTypeBotCommand::textEntityTypeBotCommand()
{
}

const int32_t textEntityTypeBotCommand::ID;

void textEntityTypeBotCommand::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeBotCommand");
        s.store_class_end();
    }
}

textEntityTypeUrl::textEntityTypeUrl()
{
}

const int32_t textEntityTypeUrl::ID;

void textEntityTypeUrl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeUrl");
        s.store_class_end();
    }
}

textEntityTypeEmailAddress::textEntityTypeEmailAddress()
{
}

const int32_t textEntityTypeEmailAddress::ID;

void textEntityTypeEmailAddress::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeEmailAddress");
        s.store_class_end();
    }
}

textEntityTypeBold::textEntityTypeBold()
{
}

const int32_t textEntityTypeBold::ID;

void textEntityTypeBold::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeBold");
        s.store_class_end();
    }
}

textEntityTypeItalic::textEntityTypeItalic()
{
}

const int32_t textEntityTypeItalic::ID;

void textEntityTypeItalic::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeItalic");
        s.store_class_end();
    }
}

textEntityTypeCode::textEntityTypeCode()
{
}

const int32_t textEntityTypeCode::ID;

void textEntityTypeCode::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeCode");
        s.store_class_end();
    }
}

textEntityTypePre::textEntityTypePre()
{
}

const int32_t textEntityTypePre::ID;

void textEntityTypePre::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypePre");
        s.store_class_end();
    }
}

textEntityTypePreCode::textEntityTypePreCode()
    : language_()
{}

textEntityTypePreCode::textEntityTypePreCode(std::string const &language_)
    : language_(std::move(language_))
{}

const int32_t textEntityTypePreCode::ID;

void textEntityTypePreCode::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypePreCode");
        s.store_field("language", language_);
        s.store_class_end();
    }
}

textEntityTypeTextUrl::textEntityTypeTextUrl()
    : url_()
{}

textEntityTypeTextUrl::textEntityTypeTextUrl(std::string const &url_)
    : url_(std::move(url_))
{}

const int32_t textEntityTypeTextUrl::ID;

void textEntityTypeTextUrl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeTextUrl");
        s.store_field("url", url_);
        s.store_class_end();
    }
}

textEntityTypeMentionName::textEntityTypeMentionName()
    : user_id_()
{}

textEntityTypeMentionName::textEntityTypeMentionName(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t textEntityTypeMentionName::ID;

void textEntityTypeMentionName::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textEntityTypeMentionName");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

textParseModeMarkdown::textParseModeMarkdown()
{
}

const int32_t textParseModeMarkdown::ID;

void textParseModeMarkdown::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textParseModeMarkdown");
        s.store_class_end();
    }
}

textParseModeHTML::textParseModeHTML()
{
}

const int32_t textParseModeHTML::ID;

void textParseModeHTML::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "textParseModeHTML");
        s.store_class_end();
    }
}

topChatCategoryUsers::topChatCategoryUsers()
{
}

const int32_t topChatCategoryUsers::ID;

void topChatCategoryUsers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "topChatCategoryUsers");
        s.store_class_end();
    }
}

topChatCategoryBots::topChatCategoryBots()
{
}

const int32_t topChatCategoryBots::ID;

void topChatCategoryBots::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "topChatCategoryBots");
        s.store_class_end();
    }
}

topChatCategoryGroups::topChatCategoryGroups()
{
}

const int32_t topChatCategoryGroups::ID;

void topChatCategoryGroups::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "topChatCategoryGroups");
        s.store_class_end();
    }
}

topChatCategoryChannels::topChatCategoryChannels()
{
}

const int32_t topChatCategoryChannels::ID;

void topChatCategoryChannels::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "topChatCategoryChannels");
        s.store_class_end();
    }
}

topChatCategoryInlineBots::topChatCategoryInlineBots()
{
}

const int32_t topChatCategoryInlineBots::ID;

void topChatCategoryInlineBots::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "topChatCategoryInlineBots");
        s.store_class_end();
    }
}

topChatCategoryCalls::topChatCategoryCalls()
{
}

const int32_t topChatCategoryCalls::ID;

void topChatCategoryCalls::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "topChatCategoryCalls");
        s.store_class_end();
    }
}

updateAuthorizationState::updateAuthorizationState()
    : authorization_state_()
{}

updateAuthorizationState::updateAuthorizationState(object_ptr<AuthorizationState>
                                                   &&authorization_state_)
    : authorization_state_(std::move(authorization_state_))
{}

const int32_t updateAuthorizationState::ID;

void updateAuthorizationState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateAuthorizationState");
        if (authorization_state_ == nullptr) {
            s.store_field("authorization_state", "null");
        } else {
            authorization_state_->store(s, "authorization_state");
        }
        s.store_class_end();
    }
}

updateNewMessage::updateNewMessage()
    : message_()
    , disable_notification_()
    , contains_mention_()
{}

updateNewMessage::updateNewMessage(object_ptr<message> &&message_, bool disable_notification_,
                                   bool contains_mention_)
    : message_(std::move(message_))
    , disable_notification_(disable_notification_)
    , contains_mention_(contains_mention_)
{}

const int32_t updateNewMessage::ID;

void updateNewMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewMessage");
        if (message_ == nullptr) {
            s.store_field("message", "null");
        } else {
            message_->store(s, "message");
        }
        s.store_field("disable_notification", disable_notification_);
        s.store_field("contains_mention", contains_mention_);
        s.store_class_end();
    }
}

updateMessageSendAcknowledged::updateMessageSendAcknowledged()
    : chat_id_()
    , message_id_()
{}

updateMessageSendAcknowledged::updateMessageSendAcknowledged(std::int64_t chat_id_,
                                                             std::int64_t message_id_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
{}

const int32_t updateMessageSendAcknowledged::ID;

void updateMessageSendAcknowledged::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateMessageSendAcknowledged");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_class_end();
    }
}

updateMessageSendSucceeded::updateMessageSendSucceeded()
    : message_()
    , old_message_id_()
{}

updateMessageSendSucceeded::updateMessageSendSucceeded(object_ptr<message> &&message_,
                                                       std::int64_t old_message_id_)
    : message_(std::move(message_))
    , old_message_id_(old_message_id_)
{}

const int32_t updateMessageSendSucceeded::ID;

void updateMessageSendSucceeded::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateMessageSendSucceeded");
        if (message_ == nullptr) {
            s.store_field("message", "null");
        } else {
            message_->store(s, "message");
        }
        s.store_field("old_message_id", old_message_id_);
        s.store_class_end();
    }
}

updateMessageSendFailed::updateMessageSendFailed()
    : message_()
    , old_message_id_()
    , error_code_()
    , error_message_()
{}

updateMessageSendFailed::updateMessageSendFailed(object_ptr<message> &&message_,
                                                 std::int64_t old_message_id_, int32_t error_code_, std::string const &error_message_)
    : message_(std::move(message_))
    , old_message_id_(old_message_id_)
    , error_code_(error_code_)
    , error_message_(std::move(error_message_))
{}

const int32_t updateMessageSendFailed::ID;

void updateMessageSendFailed::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateMessageSendFailed");
        if (message_ == nullptr) {
            s.store_field("message", "null");
        } else {
            message_->store(s, "message");
        }
        s.store_field("old_message_id", old_message_id_);
        s.store_field("error_code", error_code_);
        s.store_field("error_message", error_message_);
        s.store_class_end();
    }
}

updateMessageContent::updateMessageContent()
    : chat_id_()
    , message_id_()
    , new_content_()
{}

updateMessageContent::updateMessageContent(std::int64_t chat_id_, std::int64_t message_id_,
                                           object_ptr<MessageContent> &&new_content_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , new_content_(std::move(new_content_))
{}

const int32_t updateMessageContent::ID;

void updateMessageContent::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateMessageContent");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        if (new_content_ == nullptr) {
            s.store_field("new_content", "null");
        } else {
            new_content_->store(s, "new_content");
        }
        s.store_class_end();
    }
}

updateMessageEdited::updateMessageEdited()
    : chat_id_()
    , message_id_()
    , edit_date_()
    , reply_markup_()
{}

updateMessageEdited::updateMessageEdited(std::int64_t chat_id_, std::int64_t message_id_,
                                         int32_t edit_date_, object_ptr<ReplyMarkup> &&reply_markup_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , edit_date_(edit_date_)
    , reply_markup_(std::move(reply_markup_))
{}

const int32_t updateMessageEdited::ID;

void updateMessageEdited::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateMessageEdited");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("edit_date", edit_date_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        s.store_class_end();
    }
}

updateMessageViews::updateMessageViews()
    : chat_id_()
    , message_id_()
    , views_()
{}

updateMessageViews::updateMessageViews(std::int64_t chat_id_, std::int64_t message_id_,
                                       int32_t views_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , views_(views_)
{}

const int32_t updateMessageViews::ID;

void updateMessageViews::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateMessageViews");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("views", views_);
        s.store_class_end();
    }
}

updateMessageContentOpened::updateMessageContentOpened()
    : chat_id_()
    , message_id_()
{}

updateMessageContentOpened::updateMessageContentOpened(std::int64_t chat_id_,
                                                       std::int64_t message_id_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
{}

const int32_t updateMessageContentOpened::ID;

void updateMessageContentOpened::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateMessageContentOpened");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_class_end();
    }
}

updateMessageMentionRead::updateMessageMentionRead()
    : chat_id_()
    , message_id_()
    , unread_mention_count_()
{}

updateMessageMentionRead::updateMessageMentionRead(std::int64_t chat_id_, std::int64_t message_id_,
                                                   int32_t unread_mention_count_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , unread_mention_count_(unread_mention_count_)
{}

const int32_t updateMessageMentionRead::ID;

void updateMessageMentionRead::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateMessageMentionRead");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("unread_mention_count", unread_mention_count_);
        s.store_class_end();
    }
}

updateNewChat::updateNewChat()
    : chat_()
{}

updateNewChat::updateNewChat(object_ptr<chat> &&chat_)
    : chat_(std::move(chat_))
{}

const int32_t updateNewChat::ID;

void updateNewChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewChat");
        if (chat_ == nullptr) {
            s.store_field("chat", "null");
        } else {
            chat_->store(s, "chat");
        }
        s.store_class_end();
    }
}

updateChatTitle::updateChatTitle()
    : chat_id_()
    , title_()
{}

updateChatTitle::updateChatTitle(std::int64_t chat_id_, std::string const &title_)
    : chat_id_(chat_id_)
    , title_(std::move(title_))
{}

const int32_t updateChatTitle::ID;

void updateChatTitle::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatTitle");
        s.store_field("chat_id", chat_id_);
        s.store_field("title", title_);
        s.store_class_end();
    }
}

updateChatPhoto::updateChatPhoto()
    : chat_id_()
    , photo_()
{}

updateChatPhoto::updateChatPhoto(std::int64_t chat_id_, object_ptr<chatPhoto> &&photo_)
    : chat_id_(chat_id_)
    , photo_(std::move(photo_))
{}

const int32_t updateChatPhoto::ID;

void updateChatPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatPhoto");
        s.store_field("chat_id", chat_id_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_class_end();
    }
}

updateChatLastMessage::updateChatLastMessage()
    : chat_id_()
    , last_message_()
    , order_()
{}

updateChatLastMessage::updateChatLastMessage(std::int64_t chat_id_,
                                             object_ptr<message> &&last_message_, std::int64_t order_)
    : chat_id_(chat_id_)
    , last_message_(std::move(last_message_))
    , order_(order_)
{}

const int32_t updateChatLastMessage::ID;

void updateChatLastMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatLastMessage");
        s.store_field("chat_id", chat_id_);
        if (last_message_ == nullptr) {
            s.store_field("last_message", "null");
        } else {
            last_message_->store(s, "last_message");
        }
        s.store_field("order", order_);
        s.store_class_end();
    }
}

updateChatOrder::updateChatOrder()
    : chat_id_()
    , order_()
{}

updateChatOrder::updateChatOrder(std::int64_t chat_id_, std::int64_t order_)
    : chat_id_(chat_id_)
    , order_(order_)
{}

const int32_t updateChatOrder::ID;

void updateChatOrder::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatOrder");
        s.store_field("chat_id", chat_id_);
        s.store_field("order", order_);
        s.store_class_end();
    }
}

updateChatIsPinned::updateChatIsPinned()
    : chat_id_()
    , is_pinned_()
    , order_()
{}

updateChatIsPinned::updateChatIsPinned(std::int64_t chat_id_, bool is_pinned_, std::int64_t order_)
    : chat_id_(chat_id_)
    , is_pinned_(is_pinned_)
    , order_(order_)
{}

const int32_t updateChatIsPinned::ID;

void updateChatIsPinned::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatIsPinned");
        s.store_field("chat_id", chat_id_);
        s.store_field("is_pinned", is_pinned_);
        s.store_field("order", order_);
        s.store_class_end();
    }
}

updateChatReadInbox::updateChatReadInbox()
    : chat_id_()
    , last_read_inbox_message_id_()
    , unread_count_()
{}

updateChatReadInbox::updateChatReadInbox(std::int64_t chat_id_,
                                         std::int64_t last_read_inbox_message_id_, int32_t unread_count_)
    : chat_id_(chat_id_)
    , last_read_inbox_message_id_(last_read_inbox_message_id_)
    , unread_count_(unread_count_)
{}

const int32_t updateChatReadInbox::ID;

void updateChatReadInbox::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatReadInbox");
        s.store_field("chat_id", chat_id_);
        s.store_field("last_read_inbox_message_id", last_read_inbox_message_id_);
        s.store_field("unread_count", unread_count_);
        s.store_class_end();
    }
}

updateChatReadOutbox::updateChatReadOutbox()
    : chat_id_()
    , last_read_outbox_message_id_()
{}

updateChatReadOutbox::updateChatReadOutbox(std::int64_t chat_id_,
                                           std::int64_t last_read_outbox_message_id_)
    : chat_id_(chat_id_)
    , last_read_outbox_message_id_(last_read_outbox_message_id_)
{}

const int32_t updateChatReadOutbox::ID;

void updateChatReadOutbox::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatReadOutbox");
        s.store_field("chat_id", chat_id_);
        s.store_field("last_read_outbox_message_id", last_read_outbox_message_id_);
        s.store_class_end();
    }
}

updateChatUnreadMentionCount::updateChatUnreadMentionCount()
    : chat_id_()
    , unread_mention_count_()
{}

updateChatUnreadMentionCount::updateChatUnreadMentionCount(std::int64_t chat_id_,
                                                           int32_t unread_mention_count_)
    : chat_id_(chat_id_)
    , unread_mention_count_(unread_mention_count_)
{}

const int32_t updateChatUnreadMentionCount::ID;

void updateChatUnreadMentionCount::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatUnreadMentionCount");
        s.store_field("chat_id", chat_id_);
        s.store_field("unread_mention_count", unread_mention_count_);
        s.store_class_end();
    }
}

updateNotificationSettings::updateNotificationSettings()
    : scope_()
    , notification_settings_()
{}

updateNotificationSettings::updateNotificationSettings(object_ptr<NotificationSettingsScope>
                                                       &&scope_, object_ptr<notificationSettings> &&notification_settings_)
    : scope_(std::move(scope_))
    , notification_settings_(std::move(notification_settings_))
{}

const int32_t updateNotificationSettings::ID;

void updateNotificationSettings::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNotificationSettings");
        if (scope_ == nullptr) {
            s.store_field("scope", "null");
        } else {
            scope_->store(s, "scope");
        }
        if (notification_settings_ == nullptr) {
            s.store_field("notification_settings", "null");
        } else {
            notification_settings_->store(s, "notification_settings");
        }
        s.store_class_end();
    }
}

updateChatReplyMarkup::updateChatReplyMarkup()
    : chat_id_()
    , reply_markup_message_id_()
{}

updateChatReplyMarkup::updateChatReplyMarkup(std::int64_t chat_id_,
                                             std::int64_t reply_markup_message_id_)
    : chat_id_(chat_id_)
    , reply_markup_message_id_(reply_markup_message_id_)
{}

const int32_t updateChatReplyMarkup::ID;

void updateChatReplyMarkup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatReplyMarkup");
        s.store_field("chat_id", chat_id_);
        s.store_field("reply_markup_message_id", reply_markup_message_id_);
        s.store_class_end();
    }
}

updateChatDraftMessage::updateChatDraftMessage()
    : chat_id_()
    , draft_message_()
    , order_()
{}

updateChatDraftMessage::updateChatDraftMessage(std::int64_t chat_id_,
                                               object_ptr<draftMessage> &&draft_message_, std::int64_t order_)
    : chat_id_(chat_id_)
    , draft_message_(std::move(draft_message_))
    , order_(order_)
{}

const int32_t updateChatDraftMessage::ID;

void updateChatDraftMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateChatDraftMessage");
        s.store_field("chat_id", chat_id_);
        if (draft_message_ == nullptr) {
            s.store_field("draft_message", "null");
        } else {
            draft_message_->store(s, "draft_message");
        }
        s.store_field("order", order_);
        s.store_class_end();
    }
}

updateDeleteMessages::updateDeleteMessages()
    : chat_id_()
    , message_ids_()
    , is_permanent_()
    , from_cache_()
{}

updateDeleteMessages::updateDeleteMessages(std::int64_t chat_id_,
                                           std::vector<std::int64_t> &&message_ids_, bool is_permanent_, bool from_cache_)
    : chat_id_(chat_id_)
    , message_ids_(std::move(message_ids_))
    , is_permanent_(is_permanent_)
    , from_cache_(from_cache_)
{}

const int32_t updateDeleteMessages::ID;

void updateDeleteMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateDeleteMessages");
        s.store_field("chat_id", chat_id_);
        {
            const std::vector<std::int64_t> &v = message_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("message_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("is_permanent", is_permanent_);
        s.store_field("from_cache", from_cache_);
        s.store_class_end();
    }
}

updateUserChatAction::updateUserChatAction()
    : chat_id_()
    , user_id_()
    , action_()
{}

updateUserChatAction::updateUserChatAction(std::int64_t chat_id_, int32_t user_id_,
                                           object_ptr<ChatAction> &&action_)
    : chat_id_(chat_id_)
    , user_id_(user_id_)
    , action_(std::move(action_))
{}

const int32_t updateUserChatAction::ID;

void updateUserChatAction::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateUserChatAction");
        s.store_field("chat_id", chat_id_);
        s.store_field("user_id", user_id_);
        if (action_ == nullptr) {
            s.store_field("action", "null");
        } else {
            action_->store(s, "action");
        }
        s.store_class_end();
    }
}

updateUserStatus::updateUserStatus()
    : user_id_()
    , status_()
{}

updateUserStatus::updateUserStatus(int32_t user_id_, object_ptr<UserStatus> &&status_)
    : user_id_(user_id_)
    , status_(std::move(status_))
{}

const int32_t updateUserStatus::ID;

void updateUserStatus::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateUserStatus");
        s.store_field("user_id", user_id_);
        if (status_ == nullptr) {
            s.store_field("status", "null");
        } else {
            status_->store(s, "status");
        }
        s.store_class_end();
    }
}

updateUser::updateUser()
    : user_()
{}

updateUser::updateUser(object_ptr<user> &&user_)
    : user_(std::move(user_))
{}

const int32_t updateUser::ID;

void updateUser::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateUser");
        if (user_ == nullptr) {
            s.store_field("user", "null");
        } else {
            user_->store(s, "user");
        }
        s.store_class_end();
    }
}

updateBasicGroup::updateBasicGroup()
    : basic_group_()
{}

updateBasicGroup::updateBasicGroup(object_ptr<basicGroup> &&basic_group_)
    : basic_group_(std::move(basic_group_))
{}

const int32_t updateBasicGroup::ID;

void updateBasicGroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateBasicGroup");
        if (basic_group_ == nullptr) {
            s.store_field("basic_group", "null");
        } else {
            basic_group_->store(s, "basic_group");
        }
        s.store_class_end();
    }
}

updateSupergroup::updateSupergroup()
    : supergroup_()
{}

updateSupergroup::updateSupergroup(object_ptr<supergroup> &&supergroup_)
    : supergroup_(std::move(supergroup_))
{}

const int32_t updateSupergroup::ID;

void updateSupergroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateSupergroup");
        if (supergroup_ == nullptr) {
            s.store_field("supergroup", "null");
        } else {
            supergroup_->store(s, "supergroup");
        }
        s.store_class_end();
    }
}

updateSecretChat::updateSecretChat()
    : secret_chat_()
{}

updateSecretChat::updateSecretChat(object_ptr<secretChat> &&secret_chat_)
    : secret_chat_(std::move(secret_chat_))
{}

const int32_t updateSecretChat::ID;

void updateSecretChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateSecretChat");
        if (secret_chat_ == nullptr) {
            s.store_field("secret_chat", "null");
        } else {
            secret_chat_->store(s, "secret_chat");
        }
        s.store_class_end();
    }
}

updateUserFullInfo::updateUserFullInfo()
    : user_id_()
    , user_full_info_()
{}

updateUserFullInfo::updateUserFullInfo(int32_t user_id_,
                                       object_ptr<userFullInfo> &&user_full_info_)
    : user_id_(user_id_)
    , user_full_info_(std::move(user_full_info_))
{}

const int32_t updateUserFullInfo::ID;

void updateUserFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateUserFullInfo");
        s.store_field("user_id", user_id_);
        if (user_full_info_ == nullptr) {
            s.store_field("user_full_info", "null");
        } else {
            user_full_info_->store(s, "user_full_info");
        }
        s.store_class_end();
    }
}

updateBasicGroupFullInfo::updateBasicGroupFullInfo()
    : basic_group_id_()
    , basic_group_full_info_()
{}

updateBasicGroupFullInfo::updateBasicGroupFullInfo(int32_t basic_group_id_,
                                                   object_ptr<basicGroupFullInfo> &&basic_group_full_info_)
    : basic_group_id_(basic_group_id_)
    , basic_group_full_info_(std::move(basic_group_full_info_))
{}

const int32_t updateBasicGroupFullInfo::ID;

void updateBasicGroupFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateBasicGroupFullInfo");
        s.store_field("basic_group_id", basic_group_id_);
        if (basic_group_full_info_ == nullptr) {
            s.store_field("basic_group_full_info", "null");
        } else {
            basic_group_full_info_->store(s, "basic_group_full_info");
        }
        s.store_class_end();
    }
}

updateSupergroupFullInfo::updateSupergroupFullInfo()
    : supergroup_id_()
    , supergroup_full_info_()
{}

updateSupergroupFullInfo::updateSupergroupFullInfo(int32_t supergroup_id_,
                                                   object_ptr<supergroupFullInfo> &&supergroup_full_info_)
    : supergroup_id_(supergroup_id_)
    , supergroup_full_info_(std::move(supergroup_full_info_))
{}

const int32_t updateSupergroupFullInfo::ID;

void updateSupergroupFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateSupergroupFullInfo");
        s.store_field("supergroup_id", supergroup_id_);
        if (supergroup_full_info_ == nullptr) {
            s.store_field("supergroup_full_info", "null");
        } else {
            supergroup_full_info_->store(s, "supergroup_full_info");
        }
        s.store_class_end();
    }
}

updateServiceNotification::updateServiceNotification()
    : type_()
    , content_()
{}

updateServiceNotification::updateServiceNotification(std::string const &type_,
                                                     object_ptr<MessageContent> &&content_)
    : type_(std::move(type_))
    , content_(std::move(content_))
{}

const int32_t updateServiceNotification::ID;

void updateServiceNotification::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateServiceNotification");
        s.store_field("type", type_);
        if (content_ == nullptr) {
            s.store_field("content", "null");
        } else {
            content_->store(s, "content");
        }
        s.store_class_end();
    }
}

updateFile::updateFile()
    : file_()
{}

updateFile::updateFile(object_ptr<file> &&file_)
    : file_(std::move(file_))
{}

const int32_t updateFile::ID;

void updateFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateFile");
        if (file_ == nullptr) {
            s.store_field("file", "null");
        } else {
            file_->store(s, "file");
        }
        s.store_class_end();
    }
}

updateFileGenerationStart::updateFileGenerationStart()
    : generation_id_()
    , original_path_()
    , destination_path_()
    , conversion_()
{}

updateFileGenerationStart::updateFileGenerationStart(std::int64_t generation_id_,
                                                     std::string const &original_path_, std::string const &destination_path_,
                                                     std::string const &conversion_)
    : generation_id_(generation_id_)
    , original_path_(std::move(original_path_))
    , destination_path_(std::move(destination_path_))
    , conversion_(std::move(conversion_))
{}

const int32_t updateFileGenerationStart::ID;

void updateFileGenerationStart::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateFileGenerationStart");
        s.store_field("generation_id", generation_id_);
        s.store_field("original_path", original_path_);
        s.store_field("destination_path", destination_path_);
        s.store_field("conversion", conversion_);
        s.store_class_end();
    }
}

updateFileGenerationStop::updateFileGenerationStop()
    : generation_id_()
{}

updateFileGenerationStop::updateFileGenerationStop(std::int64_t generation_id_)
    : generation_id_(generation_id_)
{}

const int32_t updateFileGenerationStop::ID;

void updateFileGenerationStop::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateFileGenerationStop");
        s.store_field("generation_id", generation_id_);
        s.store_class_end();
    }
}

updateCall::updateCall()
    : call_()
{}

updateCall::updateCall(object_ptr<call> &&call_)
    : call_(std::move(call_))
{}

const int32_t updateCall::ID;

void updateCall::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateCall");
        if (call_ == nullptr) {
            s.store_field("call", "null");
        } else {
            call_->store(s, "call");
        }
        s.store_class_end();
    }
}

updateUserPrivacySettingRules::updateUserPrivacySettingRules()
    : setting_()
    , rules_()
{}

updateUserPrivacySettingRules::updateUserPrivacySettingRules(object_ptr<UserPrivacySetting>
                                                             &&setting_, object_ptr<userPrivacySettingRules> &&rules_)
    : setting_(std::move(setting_))
    , rules_(std::move(rules_))
{}

const int32_t updateUserPrivacySettingRules::ID;

void updateUserPrivacySettingRules::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateUserPrivacySettingRules");
        if (setting_ == nullptr) {
            s.store_field("setting", "null");
        } else {
            setting_->store(s, "setting");
        }
        if (rules_ == nullptr) {
            s.store_field("rules", "null");
        } else {
            rules_->store(s, "rules");
        }
        s.store_class_end();
    }
}

updateOption::updateOption()
    : name_()
    , value_()
{}

updateOption::updateOption(std::string const &name_, object_ptr<OptionValue> &&value_)
    : name_(std::move(name_))
    , value_(std::move(value_))
{}

const int32_t updateOption::ID;

void updateOption::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateOption");
        s.store_field("name", name_);
        if (value_ == nullptr) {
            s.store_field("value", "null");
        } else {
            value_->store(s, "value");
        }
        s.store_class_end();
    }
}

updateInstalledStickerSets::updateInstalledStickerSets()
    : is_masks_()
    , sticker_set_ids_()
{}

updateInstalledStickerSets::updateInstalledStickerSets(bool is_masks_,
                                                       std::vector<std::int64_t> &&sticker_set_ids_)
    : is_masks_(is_masks_)
    , sticker_set_ids_(std::move(sticker_set_ids_))
{}

const int32_t updateInstalledStickerSets::ID;

void updateInstalledStickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateInstalledStickerSets");
        s.store_field("is_masks", is_masks_);
        {
            const std::vector<std::int64_t> &v = sticker_set_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sticker_set_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

updateTrendingStickerSets::updateTrendingStickerSets()
    : sticker_sets_()
{}

updateTrendingStickerSets::updateTrendingStickerSets(object_ptr<stickerSets> &&sticker_sets_)
    : sticker_sets_(std::move(sticker_sets_))
{}

const int32_t updateTrendingStickerSets::ID;

void updateTrendingStickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateTrendingStickerSets");
        if (sticker_sets_ == nullptr) {
            s.store_field("sticker_sets", "null");
        } else {
            sticker_sets_->store(s, "sticker_sets");
        }
        s.store_class_end();
    }
}

updateRecentStickers::updateRecentStickers()
    : is_attached_()
    , sticker_ids_()
{}

updateRecentStickers::updateRecentStickers(bool is_attached_,
                                           std::vector<int32_t> &&sticker_ids_)
    : is_attached_(is_attached_)
    , sticker_ids_(std::move(sticker_ids_))
{}

const int32_t updateRecentStickers::ID;

void updateRecentStickers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateRecentStickers");
        s.store_field("is_attached", is_attached_);
        {
            const std::vector<int32_t> &v = sticker_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sticker_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

updateFavoriteStickers::updateFavoriteStickers()
    : sticker_ids_()
{}

updateFavoriteStickers::updateFavoriteStickers(std::vector<int32_t> &&sticker_ids_)
    : sticker_ids_(std::move(sticker_ids_))
{}

const int32_t updateFavoriteStickers::ID;

void updateFavoriteStickers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateFavoriteStickers");
        {
            const std::vector<int32_t> &v = sticker_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sticker_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

updateSavedAnimations::updateSavedAnimations()
    : animation_ids_()
{}

updateSavedAnimations::updateSavedAnimations(std::vector<int32_t> &&animation_ids_)
    : animation_ids_(std::move(animation_ids_))
{}

const int32_t updateSavedAnimations::ID;

void updateSavedAnimations::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateSavedAnimations");
        {
            const std::vector<int32_t> &v = animation_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("animation_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

updateConnectionState::updateConnectionState()
    : state_()
{}

updateConnectionState::updateConnectionState(object_ptr<ConnectionState> &&state_)
    : state_(std::move(state_))
{}

const int32_t updateConnectionState::ID;

void updateConnectionState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateConnectionState");
        if (state_ == nullptr) {
            s.store_field("state", "null");
        } else {
            state_->store(s, "state");
        }
        s.store_class_end();
    }
}

updateNewInlineQuery::updateNewInlineQuery()
    : id_()
    , sender_user_id_()
    , user_location_()
    , query_()
    , offset_()
{}

updateNewInlineQuery::updateNewInlineQuery(std::int64_t id_, int32_t sender_user_id_,
                                           object_ptr<location> &&user_location_, std::string const &query_, std::string const &offset_)
    : id_(id_)
    , sender_user_id_(sender_user_id_)
    , user_location_(std::move(user_location_))
    , query_(std::move(query_))
    , offset_(std::move(offset_))
{}

const int32_t updateNewInlineQuery::ID;

void updateNewInlineQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewInlineQuery");
        s.store_field("id", id_);
        s.store_field("sender_user_id", sender_user_id_);
        if (user_location_ == nullptr) {
            s.store_field("user_location", "null");
        } else {
            user_location_->store(s, "user_location");
        }
        s.store_field("query", query_);
        s.store_field("offset", offset_);
        s.store_class_end();
    }
}

updateNewChosenInlineResult::updateNewChosenInlineResult()
    : sender_user_id_()
    , user_location_()
    , query_()
    , result_id_()
    , inline_message_id_()
{}

updateNewChosenInlineResult::updateNewChosenInlineResult(int32_t sender_user_id_,
                                                         object_ptr<location> &&user_location_, std::string const &query_, std::string const &result_id_,
                                                         std::string const &inline_message_id_)
    : sender_user_id_(sender_user_id_)
    , user_location_(std::move(user_location_))
    , query_(std::move(query_))
    , result_id_(std::move(result_id_))
    , inline_message_id_(std::move(inline_message_id_))
{}

const int32_t updateNewChosenInlineResult::ID;

void updateNewChosenInlineResult::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewChosenInlineResult");
        s.store_field("sender_user_id", sender_user_id_);
        if (user_location_ == nullptr) {
            s.store_field("user_location", "null");
        } else {
            user_location_->store(s, "user_location");
        }
        s.store_field("query", query_);
        s.store_field("result_id", result_id_);
        s.store_field("inline_message_id", inline_message_id_);
        s.store_class_end();
    }
}

updateNewCallbackQuery::updateNewCallbackQuery()
    : id_()
    , sender_user_id_()
    , chat_id_()
    , message_id_()
    , chat_instance_()
    , payload_()
{}

updateNewCallbackQuery::updateNewCallbackQuery(std::int64_t id_, int32_t sender_user_id_,
                                               std::int64_t chat_id_, std::int64_t message_id_, std::int64_t chat_instance_,
                                               object_ptr<CallbackQueryPayload> &&payload_)
    : id_(id_)
    , sender_user_id_(sender_user_id_)
    , chat_id_(chat_id_)
    , message_id_(message_id_)
    , chat_instance_(chat_instance_)
    , payload_(std::move(payload_))
{}

const int32_t updateNewCallbackQuery::ID;

void updateNewCallbackQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewCallbackQuery");
        s.store_field("id", id_);
        s.store_field("sender_user_id", sender_user_id_);
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("chat_instance", chat_instance_);
        if (payload_ == nullptr) {
            s.store_field("payload", "null");
        } else {
            payload_->store(s, "payload");
        }
        s.store_class_end();
    }
}

updateNewInlineCallbackQuery::updateNewInlineCallbackQuery()
    : id_()
    , sender_user_id_()
    , inline_message_id_()
    , chat_instance_()
    , payload_()
{}

updateNewInlineCallbackQuery::updateNewInlineCallbackQuery(std::int64_t id_,
                                                           int32_t sender_user_id_, std::string const &inline_message_id_, std::int64_t chat_instance_,
                                                           object_ptr<CallbackQueryPayload> &&payload_)
    : id_(id_)
    , sender_user_id_(sender_user_id_)
    , inline_message_id_(std::move(inline_message_id_))
    , chat_instance_(chat_instance_)
    , payload_(std::move(payload_))
{}

const int32_t updateNewInlineCallbackQuery::ID;

void updateNewInlineCallbackQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewInlineCallbackQuery");
        s.store_field("id", id_);
        s.store_field("sender_user_id", sender_user_id_);
        s.store_field("inline_message_id", inline_message_id_);
        s.store_field("chat_instance", chat_instance_);
        if (payload_ == nullptr) {
            s.store_field("payload", "null");
        } else {
            payload_->store(s, "payload");
        }
        s.store_class_end();
    }
}

updateNewShippingQuery::updateNewShippingQuery()
    : id_()
    , sender_user_id_()
    , invoice_payload_()
    , shipping_address_()
{}

updateNewShippingQuery::updateNewShippingQuery(std::int64_t id_, int32_t sender_user_id_,
                                               std::string const &invoice_payload_, object_ptr<shippingAddress> &&shipping_address_)
    : id_(id_)
    , sender_user_id_(sender_user_id_)
    , invoice_payload_(std::move(invoice_payload_))
    , shipping_address_(std::move(shipping_address_))
{}

const int32_t updateNewShippingQuery::ID;

void updateNewShippingQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewShippingQuery");
        s.store_field("id", id_);
        s.store_field("sender_user_id", sender_user_id_);
        s.store_field("invoice_payload", invoice_payload_);
        if (shipping_address_ == nullptr) {
            s.store_field("shipping_address", "null");
        } else {
            shipping_address_->store(s, "shipping_address");
        }
        s.store_class_end();
    }
}

updateNewPreCheckoutQuery::updateNewPreCheckoutQuery()
    : id_()
    , sender_user_id_()
    , currency_()
    , total_amount_()
    , invoice_payload_()
    , shipping_option_id_()
    , order_info_()
{}

updateNewPreCheckoutQuery::updateNewPreCheckoutQuery(std::int64_t id_, int32_t sender_user_id_,
                                                     std::string const &currency_, std::int64_t total_amount_, std::string const &invoice_payload_,
                                                     std::string const &shipping_option_id_, object_ptr<orderInfo> &&order_info_)
    : id_(id_)
    , sender_user_id_(sender_user_id_)
    , currency_(std::move(currency_))
    , total_amount_(total_amount_)
    , invoice_payload_(std::move(invoice_payload_))
    , shipping_option_id_(std::move(shipping_option_id_))
    , order_info_(std::move(order_info_))
{}

const int32_t updateNewPreCheckoutQuery::ID;

void updateNewPreCheckoutQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewPreCheckoutQuery");
        s.store_field("id", id_);
        s.store_field("sender_user_id", sender_user_id_);
        s.store_field("currency", currency_);
        s.store_field("total_amount", total_amount_);
        s.store_bytes_field("invoice_payload", invoice_payload_);
        s.store_field("shipping_option_id", shipping_option_id_);
        if (order_info_ == nullptr) {
            s.store_field("order_info", "null");
        } else {
            order_info_->store(s, "order_info");
        }
        s.store_class_end();
    }
}

updateNewCustomEvent::updateNewCustomEvent()
    : event_()
{}

updateNewCustomEvent::updateNewCustomEvent(std::string const &event_)
    : event_(std::move(event_))
{}

const int32_t updateNewCustomEvent::ID;

void updateNewCustomEvent::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewCustomEvent");
        s.store_field("event", event_);
        s.store_class_end();
    }
}

updateNewCustomQuery::updateNewCustomQuery()
    : id_()
    , data_()
    , timeout_()
{}

updateNewCustomQuery::updateNewCustomQuery(std::int64_t id_, std::string const &data_,
                                           int32_t timeout_)
    : id_(id_)
    , data_(std::move(data_))
    , timeout_(timeout_)
{}

const int32_t updateNewCustomQuery::ID;

void updateNewCustomQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "updateNewCustomQuery");
        s.store_field("id", id_);
        s.store_field("data", data_);
        s.store_field("timeout", timeout_);
        s.store_class_end();
    }
}

user::user()
    : id_()
    , first_name_()
    , last_name_()
    , username_()
    , phone_number_()
    , status_()
    , profile_photo_()
    , outgoing_link_()
    , incoming_link_()
    , is_verified_()
    , restriction_reason_()
    , have_access_()
    , type_()
    , language_code_()
{}

user::user(int32_t id_, std::string const &first_name_, std::string const &last_name_,
           std::string const &username_, std::string const &phone_number_, object_ptr<UserStatus> &&status_,
           object_ptr<profilePhoto> &&profile_photo_, object_ptr<LinkState> &&outgoing_link_,
           object_ptr<LinkState> &&incoming_link_, bool is_verified_, std::string const &restriction_reason_,
           bool have_access_, object_ptr<UserType> &&type_, std::string const &language_code_)
    : id_(id_)
    , first_name_(std::move(first_name_))
    , last_name_(std::move(last_name_))
    , username_(std::move(username_))
    , phone_number_(std::move(phone_number_))
    , status_(std::move(status_))
    , profile_photo_(std::move(profile_photo_))
    , outgoing_link_(std::move(outgoing_link_))
    , incoming_link_(std::move(incoming_link_))
    , is_verified_(is_verified_)
    , restriction_reason_(std::move(restriction_reason_))
    , have_access_(have_access_)
    , type_(std::move(type_))
    , language_code_(std::move(language_code_))
{}

const int32_t user::ID;

void user::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "user");
        s.store_field("id", id_);
        s.store_field("first_name", first_name_);
        s.store_field("last_name", last_name_);
        s.store_field("username", username_);
        s.store_field("phone_number", phone_number_);
        if (status_ == nullptr) {
            s.store_field("status", "null");
        } else {
            status_->store(s, "status");
        }
        if (profile_photo_ == nullptr) {
            s.store_field("profile_photo", "null");
        } else {
            profile_photo_->store(s, "profile_photo");
        }
        if (outgoing_link_ == nullptr) {
            s.store_field("outgoing_link", "null");
        } else {
            outgoing_link_->store(s, "outgoing_link");
        }
        if (incoming_link_ == nullptr) {
            s.store_field("incoming_link", "null");
        } else {
            incoming_link_->store(s, "incoming_link");
        }
        s.store_field("is_verified", is_verified_);
        s.store_field("restriction_reason", restriction_reason_);
        s.store_field("have_access", have_access_);
        if (type_ == nullptr) {
            s.store_field("type", "null");
        } else {
            type_->store(s, "type");
        }
        s.store_field("language_code", language_code_);
        s.store_class_end();
    }
}

userFullInfo::userFullInfo()
    : is_blocked_()
    , can_be_called_()
    , has_private_calls_()
    , bio_()
    , share_text_()
    , group_in_common_count_()
    , bot_info_()
{}

userFullInfo::userFullInfo(bool is_blocked_, bool can_be_called_, bool has_private_calls_,
                           std::string const &bio_, std::string const &share_text_, int32_t group_in_common_count_,
                           object_ptr<botInfo> &&bot_info_)
    : is_blocked_(is_blocked_)
    , can_be_called_(can_be_called_)
    , has_private_calls_(has_private_calls_)
    , bio_(std::move(bio_))
    , share_text_(std::move(share_text_))
    , group_in_common_count_(group_in_common_count_)
    , bot_info_(std::move(bot_info_))
{}

const int32_t userFullInfo::ID;

void userFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userFullInfo");
        s.store_field("is_blocked", is_blocked_);
        s.store_field("can_be_called", can_be_called_);
        s.store_field("has_private_calls", has_private_calls_);
        s.store_field("bio", bio_);
        s.store_field("share_text", share_text_);
        s.store_field("group_in_common_count", group_in_common_count_);
        if (bot_info_ == nullptr) {
            s.store_field("bot_info", "null");
        } else {
            bot_info_->store(s, "bot_info");
        }
        s.store_class_end();
    }
}

userPrivacySettingShowStatus::userPrivacySettingShowStatus()
{
}

const int32_t userPrivacySettingShowStatus::ID;

void userPrivacySettingShowStatus::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingShowStatus");
        s.store_class_end();
    }
}

userPrivacySettingAllowChatInvites::userPrivacySettingAllowChatInvites()
{
}

const int32_t userPrivacySettingAllowChatInvites::ID;

void userPrivacySettingAllowChatInvites::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingAllowChatInvites");
        s.store_class_end();
    }
}

userPrivacySettingAllowCalls::userPrivacySettingAllowCalls()
{
}

const int32_t userPrivacySettingAllowCalls::ID;

void userPrivacySettingAllowCalls::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingAllowCalls");
        s.store_class_end();
    }
}

userPrivacySettingRuleAllowAll::userPrivacySettingRuleAllowAll()
{
}

const int32_t userPrivacySettingRuleAllowAll::ID;

void userPrivacySettingRuleAllowAll::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingRuleAllowAll");
        s.store_class_end();
    }
}

userPrivacySettingRuleAllowContacts::userPrivacySettingRuleAllowContacts()
{
}

const int32_t userPrivacySettingRuleAllowContacts::ID;

void userPrivacySettingRuleAllowContacts::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingRuleAllowContacts");
        s.store_class_end();
    }
}

userPrivacySettingRuleAllowUsers::userPrivacySettingRuleAllowUsers()
    : user_ids_()
{}

userPrivacySettingRuleAllowUsers::userPrivacySettingRuleAllowUsers(std::vector<int32_t>
                                                                   &&user_ids_)
    : user_ids_(std::move(user_ids_))
{}

const int32_t userPrivacySettingRuleAllowUsers::ID;

void userPrivacySettingRuleAllowUsers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingRuleAllowUsers");
        {
            const std::vector<int32_t> &v = user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

userPrivacySettingRuleRestrictAll::userPrivacySettingRuleRestrictAll()
{
}

const int32_t userPrivacySettingRuleRestrictAll::ID;

void userPrivacySettingRuleRestrictAll::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingRuleRestrictAll");
        s.store_class_end();
    }
}

userPrivacySettingRuleRestrictContacts::userPrivacySettingRuleRestrictContacts()
{
}

const int32_t userPrivacySettingRuleRestrictContacts::ID;

void userPrivacySettingRuleRestrictContacts::store(TlStorerToString &s,
                                                   const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingRuleRestrictContacts");
        s.store_class_end();
    }
}

userPrivacySettingRuleRestrictUsers::userPrivacySettingRuleRestrictUsers()
    : user_ids_()
{}

userPrivacySettingRuleRestrictUsers::userPrivacySettingRuleRestrictUsers(
    std::vector<int32_t> &&user_ids_)
    : user_ids_(std::move(user_ids_))
{}

const int32_t userPrivacySettingRuleRestrictUsers::ID;

void userPrivacySettingRuleRestrictUsers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingRuleRestrictUsers");
        {
            const std::vector<int32_t> &v = user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

userPrivacySettingRules::userPrivacySettingRules()
    : rules_()
{}

userPrivacySettingRules::userPrivacySettingRules(std::vector<object_ptr<UserPrivacySettingRule>>
                                                 &&rules_)
    : rules_(std::move(rules_))
{}

const int32_t userPrivacySettingRules::ID;

void userPrivacySettingRules::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userPrivacySettingRules");
        {
            const std::vector<object_ptr<UserPrivacySettingRule>> &v = rules_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("rules", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

userProfilePhotos::userProfilePhotos()
    : total_count_()
    , photos_()
{}

userProfilePhotos::userProfilePhotos(int32_t total_count_,
                                     std::vector<object_ptr<photo>> &&photos_)
    : total_count_(total_count_)
    , photos_(std::move(photos_))
{}

const int32_t userProfilePhotos::ID;

void userProfilePhotos::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userProfilePhotos");
        s.store_field("total_count", total_count_);
        {
            const std::vector<object_ptr<photo>> &v = photos_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("photos", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

userStatusEmpty::userStatusEmpty()
{
}

const int32_t userStatusEmpty::ID;

void userStatusEmpty::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userStatusEmpty");
        s.store_class_end();
    }
}

userStatusOnline::userStatusOnline()
    : expires_()
{}

userStatusOnline::userStatusOnline(int32_t expires_)
    : expires_(expires_)
{}

const int32_t userStatusOnline::ID;

void userStatusOnline::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userStatusOnline");
        s.store_field("expires", expires_);
        s.store_class_end();
    }
}

userStatusOffline::userStatusOffline()
    : was_online_()
{}

userStatusOffline::userStatusOffline(int32_t was_online_)
    : was_online_(was_online_)
{}

const int32_t userStatusOffline::ID;

void userStatusOffline::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userStatusOffline");
        s.store_field("was_online", was_online_);
        s.store_class_end();
    }
}

userStatusRecently::userStatusRecently()
{
}

const int32_t userStatusRecently::ID;

void userStatusRecently::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userStatusRecently");
        s.store_class_end();
    }
}

userStatusLastWeek::userStatusLastWeek()
{
}

const int32_t userStatusLastWeek::ID;

void userStatusLastWeek::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userStatusLastWeek");
        s.store_class_end();
    }
}

userStatusLastMonth::userStatusLastMonth()
{
}

const int32_t userStatusLastMonth::ID;

void userStatusLastMonth::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userStatusLastMonth");
        s.store_class_end();
    }
}

userTypeRegular::userTypeRegular()
{
}

const int32_t userTypeRegular::ID;

void userTypeRegular::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userTypeRegular");
        s.store_class_end();
    }
}

userTypeDeleted::userTypeDeleted()
{
}

const int32_t userTypeDeleted::ID;

void userTypeDeleted::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userTypeDeleted");
        s.store_class_end();
    }
}

userTypeBot::userTypeBot()
    : can_join_groups_()
    , can_read_all_group_messages_()
    , is_inline_()
    , inline_query_placeholder_()
    , need_location_()
{}

userTypeBot::userTypeBot(bool can_join_groups_, bool can_read_all_group_messages_, bool is_inline_,
                         std::string const &inline_query_placeholder_, bool need_location_)
    : can_join_groups_(can_join_groups_)
    , can_read_all_group_messages_(can_read_all_group_messages_)
    , is_inline_(is_inline_)
    , inline_query_placeholder_(std::move(inline_query_placeholder_))
    , need_location_(need_location_)
{}

const int32_t userTypeBot::ID;

void userTypeBot::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userTypeBot");
        s.store_field("can_join_groups", can_join_groups_);
        s.store_field("can_read_all_group_messages", can_read_all_group_messages_);
        s.store_field("is_inline", is_inline_);
        s.store_field("inline_query_placeholder", inline_query_placeholder_);
        s.store_field("need_location", need_location_);
        s.store_class_end();
    }
}

userTypeUnknown::userTypeUnknown()
{
}

const int32_t userTypeUnknown::ID;

void userTypeUnknown::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "userTypeUnknown");
        s.store_class_end();
    }
}

users::users()
    : total_count_()
    , user_ids_()
{}

users::users(int32_t total_count_, std::vector<int32_t> &&user_ids_)
    : total_count_(total_count_)
    , user_ids_(std::move(user_ids_))
{}

const int32_t users::ID;

void users::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "users");
        s.store_field("total_count", total_count_);
        {
            const std::vector<int32_t> &v = user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

validatedOrderInfo::validatedOrderInfo()
    : order_info_id_()
    , shipping_options_()
{}

validatedOrderInfo::validatedOrderInfo(std::string const &order_info_id_,
                                       std::vector<object_ptr<shippingOption>> &&shipping_options_)
    : order_info_id_(std::move(order_info_id_))
    , shipping_options_(std::move(shipping_options_))
{}

const int32_t validatedOrderInfo::ID;

void validatedOrderInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "validatedOrderInfo");
        s.store_field("order_info_id", order_info_id_);
        {
            const std::vector<object_ptr<shippingOption>> &v = shipping_options_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("shipping_options", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

venue::venue()
    : location_()
    , title_()
    , address_()
    , provider_()
    , id_()
{}

venue::venue(object_ptr<location> &&location_, std::string const &title_,
             std::string const &address_, std::string const &provider_, std::string const &id_)
    : location_(std::move(location_))
    , title_(std::move(title_))
    , address_(std::move(address_))
    , provider_(std::move(provider_))
    , id_(std::move(id_))
{}

const int32_t venue::ID;

void venue::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "venue");
        if (location_ == nullptr) {
            s.store_field("location", "null");
        } else {
            location_->store(s, "location");
        }
        s.store_field("title", title_);
        s.store_field("address", address_);
        s.store_field("provider", provider_);
        s.store_field("id", id_);
        s.store_class_end();
    }
}

video::video()
    : duration_()
    , width_()
    , height_()
    , file_name_()
    , mime_type_()
    , has_stickers_()
    , thumbnail_()
    , video_()
{}

video::video(int32_t duration_, int32_t width_, int32_t height_,
             std::string const &file_name_, std::string const &mime_type_, bool has_stickers_,
             object_ptr<photoSize> &&thumbnail_, object_ptr<file> &&video_)
    : duration_(duration_)
    , width_(width_)
    , height_(height_)
    , file_name_(std::move(file_name_))
    , mime_type_(std::move(mime_type_))
    , has_stickers_(has_stickers_)
    , thumbnail_(std::move(thumbnail_))
    , video_(std::move(video_))
{}

const int32_t video::ID;

void video::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "video");
        s.store_field("duration", duration_);
        s.store_field("width", width_);
        s.store_field("height", height_);
        s.store_field("file_name", file_name_);
        s.store_field("mime_type", mime_type_);
        s.store_field("has_stickers", has_stickers_);
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        if (video_ == nullptr) {
            s.store_field("video", "null");
        } else {
            video_->store(s, "video");
        }
        s.store_class_end();
    }
}

videoNote::videoNote()
    : duration_()
    , length_()
    , thumbnail_()
    , video_()
{}

videoNote::videoNote(int32_t duration_, int32_t length_,
                     object_ptr<photoSize> &&thumbnail_, object_ptr<file> &&video_)
    : duration_(duration_)
    , length_(length_)
    , thumbnail_(std::move(thumbnail_))
    , video_(std::move(video_))
{}

const int32_t videoNote::ID;

void videoNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "videoNote");
        s.store_field("duration", duration_);
        s.store_field("length", length_);
        if (thumbnail_ == nullptr) {
            s.store_field("thumbnail", "null");
        } else {
            thumbnail_->store(s, "thumbnail");
        }
        if (video_ == nullptr) {
            s.store_field("video", "null");
        } else {
            video_->store(s, "video");
        }
        s.store_class_end();
    }
}

voiceNote::voiceNote()
    : duration_()
    , waveform_()
    , mime_type_()
    , voice_()
{}

voiceNote::voiceNote(int32_t duration_, std::string const &waveform_,
                     std::string const &mime_type_, object_ptr<file> &&voice_)
    : duration_(duration_)
    , waveform_(std::move(waveform_))
    , mime_type_(std::move(mime_type_))
    , voice_(std::move(voice_))
{}

const int32_t voiceNote::ID;

void voiceNote::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "voiceNote");
        s.store_field("duration", duration_);
        s.store_bytes_field("waveform", waveform_);
        s.store_field("mime_type", mime_type_);
        if (voice_ == nullptr) {
            s.store_field("voice", "null");
        } else {
            voice_->store(s, "voice");
        }
        s.store_class_end();
    }
}

wallpaper::wallpaper()
    : id_()
    , sizes_()
    , color_()
{}

wallpaper::wallpaper(int32_t id_, std::vector<object_ptr<photoSize>> &&sizes_,
                     int32_t color_)
    : id_(id_)
    , sizes_(std::move(sizes_))
    , color_(color_)
{}

const int32_t wallpaper::ID;

void wallpaper::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "wallpaper");
        s.store_field("id", id_);
        {
            const std::vector<object_ptr<photoSize>> &v = sizes_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sizes", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("color", color_);
        s.store_class_end();
    }
}

wallpapers::wallpapers()
    : wallpapers_()
{}

wallpapers::wallpapers(std::vector<object_ptr<wallpaper>> &&wallpapers_)
    : wallpapers_(std::move(wallpapers_))
{}

const int32_t wallpapers::ID;

void wallpapers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "wallpapers");
        {
            const std::vector<object_ptr<wallpaper>> &v = wallpapers_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("wallpapers", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

webPage::webPage()
    : url_()
    , display_url_()
    , type_()
    , site_name_()
    , title_()
    , description_()
    , photo_()
    , embed_url_()
    , embed_type_()
    , embed_width_()
    , embed_height_()
    , duration_()
    , author_()
    , animation_()
    , audio_()
    , document_()
    , sticker_()
    , video_()
    , video_note_()
    , voice_note_()
    , has_instant_view_()
{}

webPage::webPage(std::string const &url_, std::string const &display_url_, std::string const &type_,
                 std::string const &site_name_, std::string const &title_, std::string const &description_,
                 object_ptr<photo> &&photo_, std::string const &embed_url_, std::string const &embed_type_,
                 int32_t embed_width_, int32_t embed_height_, int32_t duration_,
                 std::string const &author_, object_ptr<animation> &&animation_, object_ptr<audio> &&audio_,
                 object_ptr<document> &&document_, object_ptr<sticker> &&sticker_, object_ptr<video> &&video_,
                 object_ptr<videoNote> &&video_note_, object_ptr<voiceNote> &&voice_note_, bool has_instant_view_)
    : url_(std::move(url_))
    , display_url_(std::move(display_url_))
    , type_(std::move(type_))
    , site_name_(std::move(site_name_))
    , title_(std::move(title_))
    , description_(std::move(description_))
    , photo_(std::move(photo_))
    , embed_url_(std::move(embed_url_))
    , embed_type_(std::move(embed_type_))
    , embed_width_(embed_width_)
    , embed_height_(embed_height_)
    , duration_(duration_)
    , author_(std::move(author_))
    , animation_(std::move(animation_))
    , audio_(std::move(audio_))
    , document_(std::move(document_))
    , sticker_(std::move(sticker_))
    , video_(std::move(video_))
    , video_note_(std::move(video_note_))
    , voice_note_(std::move(voice_note_))
    , has_instant_view_(has_instant_view_)
{}

const int32_t webPage::ID;

void webPage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "webPage");
        s.store_field("url", url_);
        s.store_field("display_url", display_url_);
        s.store_field("type", type_);
        s.store_field("site_name", site_name_);
        s.store_field("title", title_);
        s.store_field("description", description_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_field("embed_url", embed_url_);
        s.store_field("embed_type", embed_type_);
        s.store_field("embed_width", embed_width_);
        s.store_field("embed_height", embed_height_);
        s.store_field("duration", duration_);
        s.store_field("author", author_);
        if (animation_ == nullptr) {
            s.store_field("animation", "null");
        } else {
            animation_->store(s, "animation");
        }
        if (audio_ == nullptr) {
            s.store_field("audio", "null");
        } else {
            audio_->store(s, "audio");
        }
        if (document_ == nullptr) {
            s.store_field("document", "null");
        } else {
            document_->store(s, "document");
        }
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        if (video_ == nullptr) {
            s.store_field("video", "null");
        } else {
            video_->store(s, "video");
        }
        if (video_note_ == nullptr) {
            s.store_field("video_note", "null");
        } else {
            video_note_->store(s, "video_note");
        }
        if (voice_note_ == nullptr) {
            s.store_field("voice_note", "null");
        } else {
            voice_note_->store(s, "voice_note");
        }
        s.store_field("has_instant_view", has_instant_view_);
        s.store_class_end();
    }
}

webPageInstantView::webPageInstantView()
    : page_blocks_()
    , is_full_()
{}

webPageInstantView::webPageInstantView(std::vector<object_ptr<PageBlock>> &&page_blocks_,
                                       bool is_full_)
    : page_blocks_(std::move(page_blocks_))
    , is_full_(is_full_)
{}

const int32_t webPageInstantView::ID;

void webPageInstantView::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "webPageInstantView");
        {
            const std::vector<object_ptr<PageBlock>> &v = page_blocks_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("page_blocks", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("is_full", is_full_);
        s.store_class_end();
    }
}

acceptCall::acceptCall()
    : call_id_()
    , protocol_()
{}

acceptCall::acceptCall(int32_t call_id_, object_ptr<callProtocol> &&protocol_)
    : call_id_(call_id_)
    , protocol_(std::move(protocol_))
{}

const int32_t acceptCall::ID;

void acceptCall::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "acceptCall");
        s.store_field("call_id", call_id_);
        if (protocol_ == nullptr) {
            s.store_field("protocol", "null");
        } else {
            protocol_->store(s, "protocol");
        }
        s.store_class_end();
    }
}

addChatMember::addChatMember()
    : chat_id_()
    , user_id_()
    , forward_limit_()
{}

addChatMember::addChatMember(std::int64_t chat_id_, int32_t user_id_,
                             int32_t forward_limit_)
    : chat_id_(chat_id_)
    , user_id_(user_id_)
    , forward_limit_(forward_limit_)
{}

const int32_t addChatMember::ID;

void addChatMember::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "addChatMember");
        s.store_field("chat_id", chat_id_);
        s.store_field("user_id", user_id_);
        s.store_field("forward_limit", forward_limit_);
        s.store_class_end();
    }
}

addChatMembers::addChatMembers()
    : chat_id_()
    , user_ids_()
{}

addChatMembers::addChatMembers(std::int64_t chat_id_, std::vector<int32_t> &&user_ids_)
    : chat_id_(chat_id_)
    , user_ids_(std::move(user_ids_))
{}

const int32_t addChatMembers::ID;

void addChatMembers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "addChatMembers");
        s.store_field("chat_id", chat_id_);
        {
            const std::vector<int32_t> &v = user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

addFavoriteSticker::addFavoriteSticker()
    : sticker_()
{}

addFavoriteSticker::addFavoriteSticker(object_ptr<InputFile> &&sticker_)
    : sticker_(std::move(sticker_))
{}

const int32_t addFavoriteSticker::ID;

void addFavoriteSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "addFavoriteSticker");
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

addNetworkStatistics::addNetworkStatistics()
    : entry_()
{}

addNetworkStatistics::addNetworkStatistics(object_ptr<NetworkStatisticsEntry> &&entry_)
    : entry_(std::move(entry_))
{}

const int32_t addNetworkStatistics::ID;

void addNetworkStatistics::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "addNetworkStatistics");
        if (entry_ == nullptr) {
            s.store_field("entry", "null");
        } else {
            entry_->store(s, "entry");
        }
        s.store_class_end();
    }
}

addRecentSticker::addRecentSticker()
    : is_attached_()
    , sticker_()
{}

addRecentSticker::addRecentSticker(bool is_attached_, object_ptr<InputFile> &&sticker_)
    : is_attached_(is_attached_)
    , sticker_(std::move(sticker_))
{}

const int32_t addRecentSticker::ID;

void addRecentSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "addRecentSticker");
        s.store_field("is_attached", is_attached_);
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

addRecentlyFoundChat::addRecentlyFoundChat()
    : chat_id_()
{}

addRecentlyFoundChat::addRecentlyFoundChat(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t addRecentlyFoundChat::ID;

void addRecentlyFoundChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "addRecentlyFoundChat");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

addSavedAnimation::addSavedAnimation()
    : animation_()
{}

addSavedAnimation::addSavedAnimation(object_ptr<InputFile> &&animation_)
    : animation_(std::move(animation_))
{}

const int32_t addSavedAnimation::ID;

void addSavedAnimation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "addSavedAnimation");
        if (animation_ == nullptr) {
            s.store_field("animation", "null");
        } else {
            animation_->store(s, "animation");
        }
        s.store_class_end();
    }
}

addStickerToSet::addStickerToSet()
    : user_id_()
    , name_()
    , sticker_()
{}

addStickerToSet::addStickerToSet(int32_t user_id_, std::string const &name_,
                                 object_ptr<inputSticker> &&sticker_)
    : user_id_(user_id_)
    , name_(std::move(name_))
    , sticker_(std::move(sticker_))
{}

const int32_t addStickerToSet::ID;

void addStickerToSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "addStickerToSet");
        s.store_field("user_id", user_id_);
        s.store_field("name", name_);
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

answerCallbackQuery::answerCallbackQuery()
    : callback_query_id_()
    , text_()
    , show_alert_()
    , url_()
    , cache_time_()
{}

answerCallbackQuery::answerCallbackQuery(std::int64_t callback_query_id_, std::string const &text_,
                                         bool show_alert_, std::string const &url_, int32_t cache_time_)
    : callback_query_id_(callback_query_id_)
    , text_(std::move(text_))
    , show_alert_(show_alert_)
    , url_(std::move(url_))
    , cache_time_(cache_time_)
{}

const int32_t answerCallbackQuery::ID;

void answerCallbackQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "answerCallbackQuery");
        s.store_field("callback_query_id", callback_query_id_);
        s.store_field("text", text_);
        s.store_field("show_alert", show_alert_);
        s.store_field("url", url_);
        s.store_field("cache_time", cache_time_);
        s.store_class_end();
    }
}

answerCustomQuery::answerCustomQuery()
    : custom_query_id_()
    , data_()
{}

answerCustomQuery::answerCustomQuery(std::int64_t custom_query_id_, std::string const &data_)
    : custom_query_id_(custom_query_id_)
    , data_(std::move(data_))
{}

const int32_t answerCustomQuery::ID;

void answerCustomQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "answerCustomQuery");
        s.store_field("custom_query_id", custom_query_id_);
        s.store_field("data", data_);
        s.store_class_end();
    }
}

answerInlineQuery::answerInlineQuery()
    : inline_query_id_()
    , is_personal_()
    , results_()
    , cache_time_()
    , next_offset_()
    , switch_pm_text_()
    , switch_pm_parameter_()
{}

answerInlineQuery::answerInlineQuery(std::int64_t inline_query_id_, bool is_personal_,
                                     std::vector<object_ptr<InputInlineQueryResult>> &&results_, int32_t cache_time_,
                                     std::string const &next_offset_, std::string const &switch_pm_text_,
                                     std::string const &switch_pm_parameter_)
    : inline_query_id_(inline_query_id_)
    , is_personal_(is_personal_)
    , results_(std::move(results_))
    , cache_time_(cache_time_)
    , next_offset_(std::move(next_offset_))
    , switch_pm_text_(std::move(switch_pm_text_))
    , switch_pm_parameter_(std::move(switch_pm_parameter_))
{}

const int32_t answerInlineQuery::ID;

void answerInlineQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "answerInlineQuery");
        s.store_field("inline_query_id", inline_query_id_);
        s.store_field("is_personal", is_personal_);
        {
            const std::vector<object_ptr<InputInlineQueryResult>> &v = results_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("results", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("cache_time", cache_time_);
        s.store_field("next_offset", next_offset_);
        s.store_field("switch_pm_text", switch_pm_text_);
        s.store_field("switch_pm_parameter", switch_pm_parameter_);
        s.store_class_end();
    }
}

answerPreCheckoutQuery::answerPreCheckoutQuery()
    : pre_checkout_query_id_()
    , error_message_()
{}

answerPreCheckoutQuery::answerPreCheckoutQuery(std::int64_t pre_checkout_query_id_,
                                               std::string const &error_message_)
    : pre_checkout_query_id_(pre_checkout_query_id_)
    , error_message_(std::move(error_message_))
{}

const int32_t answerPreCheckoutQuery::ID;

void answerPreCheckoutQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "answerPreCheckoutQuery");
        s.store_field("pre_checkout_query_id", pre_checkout_query_id_);
        s.store_field("error_message", error_message_);
        s.store_class_end();
    }
}

answerShippingQuery::answerShippingQuery()
    : shipping_query_id_()
    , shipping_options_()
    , error_message_()
{}

answerShippingQuery::answerShippingQuery(std::int64_t shipping_query_id_,
                                         std::vector<object_ptr<shippingOption>> &&shipping_options_, std::string const &error_message_)
    : shipping_query_id_(shipping_query_id_)
    , shipping_options_(std::move(shipping_options_))
    , error_message_(std::move(error_message_))
{}

const int32_t answerShippingQuery::ID;

void answerShippingQuery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "answerShippingQuery");
        s.store_field("shipping_query_id", shipping_query_id_);
        {
            const std::vector<object_ptr<shippingOption>> &v = shipping_options_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("shipping_options", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_field("error_message", error_message_);
        s.store_class_end();
    }
}

blockUser::blockUser()
    : user_id_()
{}

blockUser::blockUser(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t blockUser::ID;

void blockUser::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "blockUser");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

cancelDownloadFile::cancelDownloadFile()
    : file_id_()
    , only_if_pending_()
{}

cancelDownloadFile::cancelDownloadFile(int32_t file_id_, bool only_if_pending_)
    : file_id_(file_id_)
    , only_if_pending_(only_if_pending_)
{}

const int32_t cancelDownloadFile::ID;

void cancelDownloadFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "cancelDownloadFile");
        s.store_field("file_id", file_id_);
        s.store_field("only_if_pending", only_if_pending_);
        s.store_class_end();
    }
}

cancelUploadFile::cancelUploadFile()
    : file_id_()
{}

cancelUploadFile::cancelUploadFile(int32_t file_id_)
    : file_id_(file_id_)
{}

const int32_t cancelUploadFile::ID;

void cancelUploadFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "cancelUploadFile");
        s.store_field("file_id", file_id_);
        s.store_class_end();
    }
}

changeChatReportSpamState::changeChatReportSpamState()
    : chat_id_()
    , is_spam_chat_()
{}

changeChatReportSpamState::changeChatReportSpamState(std::int64_t chat_id_, bool is_spam_chat_)
    : chat_id_(chat_id_)
    , is_spam_chat_(is_spam_chat_)
{}

const int32_t changeChatReportSpamState::ID;

void changeChatReportSpamState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "changeChatReportSpamState");
        s.store_field("chat_id", chat_id_);
        s.store_field("is_spam_chat", is_spam_chat_);
        s.store_class_end();
    }
}

changeImportedContacts::changeImportedContacts()
    : contacts_()
{}

changeImportedContacts::changeImportedContacts(std::vector<object_ptr<contact>> &&contacts_)
    : contacts_(std::move(contacts_))
{}

const int32_t changeImportedContacts::ID;

void changeImportedContacts::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "changeImportedContacts");
        {
            const std::vector<object_ptr<contact>> &v = contacts_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("contacts", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

changePhoneNumber::changePhoneNumber()
    : phone_number_()
    , allow_flash_call_()
    , is_current_phone_number_()
{}

changePhoneNumber::changePhoneNumber(std::string const &phone_number_, bool allow_flash_call_,
                                     bool is_current_phone_number_)
    : phone_number_(std::move(phone_number_))
    , allow_flash_call_(allow_flash_call_)
    , is_current_phone_number_(is_current_phone_number_)
{}

const int32_t changePhoneNumber::ID;

void changePhoneNumber::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "changePhoneNumber");
        s.store_field("phone_number", phone_number_);
        s.store_field("allow_flash_call", allow_flash_call_);
        s.store_field("is_current_phone_number", is_current_phone_number_);
        s.store_class_end();
    }
}

changeStickerSet::changeStickerSet()
    : set_id_()
    , is_installed_()
    , is_archived_()
{}

changeStickerSet::changeStickerSet(std::int64_t set_id_, bool is_installed_, bool is_archived_)
    : set_id_(set_id_)
    , is_installed_(is_installed_)
    , is_archived_(is_archived_)
{}

const int32_t changeStickerSet::ID;

void changeStickerSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "changeStickerSet");
        s.store_field("set_id", set_id_);
        s.store_field("is_installed", is_installed_);
        s.store_field("is_archived", is_archived_);
        s.store_class_end();
    }
}

checkAuthenticationBotToken::checkAuthenticationBotToken()
    : token_()
{}

checkAuthenticationBotToken::checkAuthenticationBotToken(std::string const &token_)
    : token_(std::move(token_))
{}

const int32_t checkAuthenticationBotToken::ID;

void checkAuthenticationBotToken::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "checkAuthenticationBotToken");
        s.store_field("token", token_);
        s.store_class_end();
    }
}

checkAuthenticationCode::checkAuthenticationCode()
    : code_()
    , first_name_()
    , last_name_()
{}

checkAuthenticationCode::checkAuthenticationCode(std::string const &code_,
                                                 std::string const &first_name_, std::string const &last_name_)
    : code_(std::move(code_))
    , first_name_(std::move(first_name_))
    , last_name_(std::move(last_name_))
{}

const int32_t checkAuthenticationCode::ID;

void checkAuthenticationCode::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "checkAuthenticationCode");
        s.store_field("code", code_);
        s.store_field("first_name", first_name_);
        s.store_field("last_name", last_name_);
        s.store_class_end();
    }
}

checkAuthenticationPassword::checkAuthenticationPassword()
    : password_()
{}

checkAuthenticationPassword::checkAuthenticationPassword(std::string const &password_)
    : password_(std::move(password_))
{}

const int32_t checkAuthenticationPassword::ID;

void checkAuthenticationPassword::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "checkAuthenticationPassword");
        s.store_field("password", password_);
        s.store_class_end();
    }
}

checkChangePhoneNumberCode::checkChangePhoneNumberCode()
    : code_()
{}

checkChangePhoneNumberCode::checkChangePhoneNumberCode(std::string const &code_)
    : code_(std::move(code_))
{}

const int32_t checkChangePhoneNumberCode::ID;

void checkChangePhoneNumberCode::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "checkChangePhoneNumberCode");
        s.store_field("code", code_);
        s.store_class_end();
    }
}

checkChatInviteLink::checkChatInviteLink()
    : invite_link_()
{}

checkChatInviteLink::checkChatInviteLink(std::string const &invite_link_)
    : invite_link_(std::move(invite_link_))
{}

const int32_t checkChatInviteLink::ID;

void checkChatInviteLink::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "checkChatInviteLink");
        s.store_field("invite_link", invite_link_);
        s.store_class_end();
    }
}

checkDatabaseEncryptionKey::checkDatabaseEncryptionKey()
    : encryption_key_()
{}

checkDatabaseEncryptionKey::checkDatabaseEncryptionKey(std::string const &encryption_key_)
    : encryption_key_(std::move(encryption_key_))
{}

const int32_t checkDatabaseEncryptionKey::ID;

void checkDatabaseEncryptionKey::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "checkDatabaseEncryptionKey");
        s.store_bytes_field("encryption_key", encryption_key_);
        s.store_class_end();
    }
}

clearImportedContacts::clearImportedContacts()
{
}

const int32_t clearImportedContacts::ID;

void clearImportedContacts::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "clearImportedContacts");
        s.store_class_end();
    }
}

clearRecentStickers::clearRecentStickers()
    : is_attached_()
{}

clearRecentStickers::clearRecentStickers(bool is_attached_)
    : is_attached_(is_attached_)
{}

const int32_t clearRecentStickers::ID;

void clearRecentStickers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "clearRecentStickers");
        s.store_field("is_attached", is_attached_);
        s.store_class_end();
    }
}

clearRecentlyFoundChats::clearRecentlyFoundChats()
{
}

const int32_t clearRecentlyFoundChats::ID;

void clearRecentlyFoundChats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "clearRecentlyFoundChats");
        s.store_class_end();
    }
}

close::close()
{
}

const int32_t close::ID;

void close::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "close");
        s.store_class_end();
    }
}

closeChat::closeChat()
    : chat_id_()
{}

closeChat::closeChat(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t closeChat::ID;

void closeChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "closeChat");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

closeSecretChat::closeSecretChat()
    : secret_chat_id_()
{}

closeSecretChat::closeSecretChat(int32_t secret_chat_id_)
    : secret_chat_id_(secret_chat_id_)
{}

const int32_t closeSecretChat::ID;

void closeSecretChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "closeSecretChat");
        s.store_field("secret_chat_id", secret_chat_id_);
        s.store_class_end();
    }
}

createBasicGroupChat::createBasicGroupChat()
    : basic_group_id_()
    , force_()
{}

createBasicGroupChat::createBasicGroupChat(int32_t basic_group_id_, bool force_)
    : basic_group_id_(basic_group_id_)
    , force_(force_)
{}

const int32_t createBasicGroupChat::ID;

void createBasicGroupChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createBasicGroupChat");
        s.store_field("basic_group_id", basic_group_id_);
        s.store_field("force", force_);
        s.store_class_end();
    }
}

createCall::createCall()
    : user_id_()
    , protocol_()
{}

createCall::createCall(int32_t user_id_, object_ptr<callProtocol> &&protocol_)
    : user_id_(user_id_)
    , protocol_(std::move(protocol_))
{}

const int32_t createCall::ID;

void createCall::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createCall");
        s.store_field("user_id", user_id_);
        if (protocol_ == nullptr) {
            s.store_field("protocol", "null");
        } else {
            protocol_->store(s, "protocol");
        }
        s.store_class_end();
    }
}

createNewBasicGroupChat::createNewBasicGroupChat()
    : user_ids_()
    , title_()
{}

createNewBasicGroupChat::createNewBasicGroupChat(std::vector<int32_t> &&user_ids_,
                                                 std::string const &title_)
    : user_ids_(std::move(user_ids_))
    , title_(std::move(title_))
{}

const int32_t createNewBasicGroupChat::ID;

void createNewBasicGroupChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createNewBasicGroupChat");
        {
            const std::vector<int32_t> &v = user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("title", title_);
        s.store_class_end();
    }
}

createNewSecretChat::createNewSecretChat()
    : user_id_()
{}

createNewSecretChat::createNewSecretChat(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t createNewSecretChat::ID;

void createNewSecretChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createNewSecretChat");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

createNewStickerSet::createNewStickerSet()
    : user_id_()
    , title_()
    , name_()
    , is_masks_()
    , stickers_()
{}

createNewStickerSet::createNewStickerSet(int32_t user_id_, std::string const &title_,
                                         std::string const &name_, bool is_masks_, std::vector<object_ptr<inputSticker>> &&stickers_)
    : user_id_(user_id_)
    , title_(std::move(title_))
    , name_(std::move(name_))
    , is_masks_(is_masks_)
    , stickers_(std::move(stickers_))
{}

const int32_t createNewStickerSet::ID;

void createNewStickerSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createNewStickerSet");
        s.store_field("user_id", user_id_);
        s.store_field("title", title_);
        s.store_field("name", name_);
        s.store_field("is_masks", is_masks_);
        {
            const std::vector<object_ptr<inputSticker>> &v = stickers_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("stickers", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

createNewSupergroupChat::createNewSupergroupChat()
    : title_()
    , is_channel_()
    , description_()
{}

createNewSupergroupChat::createNewSupergroupChat(std::string const &title_, bool is_channel_,
                                                 std::string const &description_)
    : title_(std::move(title_))
    , is_channel_(is_channel_)
    , description_(std::move(description_))
{}

const int32_t createNewSupergroupChat::ID;

void createNewSupergroupChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createNewSupergroupChat");
        s.store_field("title", title_);
        s.store_field("is_channel", is_channel_);
        s.store_field("description", description_);
        s.store_class_end();
    }
}

createPrivateChat::createPrivateChat()
    : user_id_()
    , force_()
{}

createPrivateChat::createPrivateChat(int32_t user_id_, bool force_)
    : user_id_(user_id_)
    , force_(force_)
{}

const int32_t createPrivateChat::ID;

void createPrivateChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createPrivateChat");
        s.store_field("user_id", user_id_);
        s.store_field("force", force_);
        s.store_class_end();
    }
}

createSecretChat::createSecretChat()
    : secret_chat_id_()
{}

createSecretChat::createSecretChat(int32_t secret_chat_id_)
    : secret_chat_id_(secret_chat_id_)
{}

const int32_t createSecretChat::ID;

void createSecretChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createSecretChat");
        s.store_field("secret_chat_id", secret_chat_id_);
        s.store_class_end();
    }
}

createSupergroupChat::createSupergroupChat()
    : supergroup_id_()
    , force_()
{}

createSupergroupChat::createSupergroupChat(int32_t supergroup_id_, bool force_)
    : supergroup_id_(supergroup_id_)
    , force_(force_)
{}

const int32_t createSupergroupChat::ID;

void createSupergroupChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createSupergroupChat");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("force", force_);
        s.store_class_end();
    }
}

createTemporaryPassword::createTemporaryPassword()
    : password_()
    , valid_for_()
{}

createTemporaryPassword::createTemporaryPassword(std::string const &password_,
                                                 int32_t valid_for_)
    : password_(std::move(password_))
    , valid_for_(valid_for_)
{}

const int32_t createTemporaryPassword::ID;

void createTemporaryPassword::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "createTemporaryPassword");
        s.store_field("password", password_);
        s.store_field("valid_for", valid_for_);
        s.store_class_end();
    }
}

deleteAccount::deleteAccount()
    : reason_()
{}

deleteAccount::deleteAccount(std::string const &reason_)
    : reason_(std::move(reason_))
{}

const int32_t deleteAccount::ID;

void deleteAccount::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteAccount");
        s.store_field("reason", reason_);
        s.store_class_end();
    }
}

deleteChatHistory::deleteChatHistory()
    : chat_id_()
    , remove_from_chat_list_()
{}

deleteChatHistory::deleteChatHistory(std::int64_t chat_id_, bool remove_from_chat_list_)
    : chat_id_(chat_id_)
    , remove_from_chat_list_(remove_from_chat_list_)
{}

const int32_t deleteChatHistory::ID;

void deleteChatHistory::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteChatHistory");
        s.store_field("chat_id", chat_id_);
        s.store_field("remove_from_chat_list", remove_from_chat_list_);
        s.store_class_end();
    }
}

deleteChatMessagesFromUser::deleteChatMessagesFromUser()
    : chat_id_()
    , user_id_()
{}

deleteChatMessagesFromUser::deleteChatMessagesFromUser(std::int64_t chat_id_, int32_t user_id_)
    : chat_id_(chat_id_)
    , user_id_(user_id_)
{}

const int32_t deleteChatMessagesFromUser::ID;

void deleteChatMessagesFromUser::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteChatMessagesFromUser");
        s.store_field("chat_id", chat_id_);
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

deleteChatReplyMarkup::deleteChatReplyMarkup()
    : chat_id_()
    , message_id_()
{}

deleteChatReplyMarkup::deleteChatReplyMarkup(std::int64_t chat_id_, std::int64_t message_id_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
{}

const int32_t deleteChatReplyMarkup::ID;

void deleteChatReplyMarkup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteChatReplyMarkup");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_class_end();
    }
}

deleteFile::deleteFile()
    : file_id_()
{}

deleteFile::deleteFile(int32_t file_id_)
    : file_id_(file_id_)
{}

const int32_t deleteFile::ID;

void deleteFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteFile");
        s.store_field("file_id", file_id_);
        s.store_class_end();
    }
}

deleteMessages::deleteMessages()
    : chat_id_()
    , message_ids_()
    , revoke_()
{}

deleteMessages::deleteMessages(std::int64_t chat_id_, std::vector<std::int64_t> &&message_ids_,
                               bool revoke_)
    : chat_id_(chat_id_)
    , message_ids_(std::move(message_ids_))
    , revoke_(revoke_)
{}

const int32_t deleteMessages::ID;

void deleteMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteMessages");
        s.store_field("chat_id", chat_id_);
        {
            const std::vector<std::int64_t> &v = message_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("message_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("revoke", revoke_);
        s.store_class_end();
    }
}

deleteProfilePhoto::deleteProfilePhoto()
    : profile_photo_id_()
{}

deleteProfilePhoto::deleteProfilePhoto(std::int64_t profile_photo_id_)
    : profile_photo_id_(profile_photo_id_)
{}

const int32_t deleteProfilePhoto::ID;

void deleteProfilePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteProfilePhoto");
        s.store_field("profile_photo_id", profile_photo_id_);
        s.store_class_end();
    }
}

deleteSavedCredentials::deleteSavedCredentials()
{
}

const int32_t deleteSavedCredentials::ID;

void deleteSavedCredentials::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteSavedCredentials");
        s.store_class_end();
    }
}

deleteSavedOrderInfo::deleteSavedOrderInfo()
{
}

const int32_t deleteSavedOrderInfo::ID;

void deleteSavedOrderInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteSavedOrderInfo");
        s.store_class_end();
    }
}

deleteSupergroup::deleteSupergroup()
    : supergroup_id_()
{}

deleteSupergroup::deleteSupergroup(int32_t supergroup_id_)
    : supergroup_id_(supergroup_id_)
{}

const int32_t deleteSupergroup::ID;

void deleteSupergroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "deleteSupergroup");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_class_end();
    }
}

destroy::destroy()
{
}

const int32_t destroy::ID;

void destroy::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "destroy");
        s.store_class_end();
    }
}

discardCall::discardCall()
    : call_id_()
    , is_disconnected_()
    , duration_()
    , connection_id_()
{}

discardCall::discardCall(int32_t call_id_, bool is_disconnected_, int32_t duration_,
                         std::int64_t connection_id_)
    : call_id_(call_id_)
    , is_disconnected_(is_disconnected_)
    , duration_(duration_)
    , connection_id_(connection_id_)
{}

const int32_t discardCall::ID;

void discardCall::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "discardCall");
        s.store_field("call_id", call_id_);
        s.store_field("is_disconnected", is_disconnected_);
        s.store_field("duration", duration_);
        s.store_field("connection_id", connection_id_);
        s.store_class_end();
    }
}

downloadFile::downloadFile()
    : file_id_()
    , priority_()
{}

downloadFile::downloadFile(int32_t file_id_, int32_t priority_)
    : file_id_(file_id_)
    , priority_(priority_)
{}

const int32_t downloadFile::ID;

void downloadFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "downloadFile");
        s.store_field("file_id", file_id_);
        s.store_field("priority", priority_);
        s.store_class_end();
    }
}

editInlineMessageCaption::editInlineMessageCaption()
    : inline_message_id_()
    , reply_markup_()
    , caption_()
{}

editInlineMessageCaption::editInlineMessageCaption(std::string const &inline_message_id_,
                                                   object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<formattedText> &&caption_)
    : inline_message_id_(std::move(inline_message_id_))
    , reply_markup_(std::move(reply_markup_))
    , caption_(std::move(caption_))
{}

const int32_t editInlineMessageCaption::ID;

void editInlineMessageCaption::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "editInlineMessageCaption");
        s.store_field("inline_message_id", inline_message_id_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

editInlineMessageLiveLocation::editInlineMessageLiveLocation()
    : inline_message_id_()
    , reply_markup_()
    , location_()
{}

editInlineMessageLiveLocation::editInlineMessageLiveLocation(std::string const &inline_message_id_,
                                                             object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<location> &&location_)
    : inline_message_id_(std::move(inline_message_id_))
    , reply_markup_(std::move(reply_markup_))
    , location_(std::move(location_))
{}

const int32_t editInlineMessageLiveLocation::ID;

void editInlineMessageLiveLocation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "editInlineMessageLiveLocation");
        s.store_field("inline_message_id", inline_message_id_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (location_ == nullptr) {
            s.store_field("location", "null");
        } else {
            location_->store(s, "location");
        }
        s.store_class_end();
    }
}

editInlineMessageReplyMarkup::editInlineMessageReplyMarkup()
    : inline_message_id_()
    , reply_markup_()
{}

editInlineMessageReplyMarkup::editInlineMessageReplyMarkup(std::string const &inline_message_id_,
                                                           object_ptr<ReplyMarkup> &&reply_markup_)
    : inline_message_id_(std::move(inline_message_id_))
    , reply_markup_(std::move(reply_markup_))
{}

const int32_t editInlineMessageReplyMarkup::ID;

void editInlineMessageReplyMarkup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "editInlineMessageReplyMarkup");
        s.store_field("inline_message_id", inline_message_id_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        s.store_class_end();
    }
}

editInlineMessageText::editInlineMessageText()
    : inline_message_id_()
    , reply_markup_()
    , input_message_content_()
{}

editInlineMessageText::editInlineMessageText(std::string const &inline_message_id_,
                                             object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_)
    : inline_message_id_(std::move(inline_message_id_))
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t editInlineMessageText::ID;

void editInlineMessageText::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "editInlineMessageText");
        s.store_field("inline_message_id", inline_message_id_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

editMessageCaption::editMessageCaption()
    : chat_id_()
    , message_id_()
    , reply_markup_()
    , caption_()
{}

editMessageCaption::editMessageCaption(std::int64_t chat_id_, std::int64_t message_id_,
                                       object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<formattedText> &&caption_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , reply_markup_(std::move(reply_markup_))
    , caption_(std::move(caption_))
{}

const int32_t editMessageCaption::ID;

void editMessageCaption::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "editMessageCaption");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (caption_ == nullptr) {
            s.store_field("caption", "null");
        } else {
            caption_->store(s, "caption");
        }
        s.store_class_end();
    }
}

editMessageLiveLocation::editMessageLiveLocation()
    : chat_id_()
    , message_id_()
    , reply_markup_()
    , location_()
{}

editMessageLiveLocation::editMessageLiveLocation(std::int64_t chat_id_, std::int64_t message_id_,
                                                 object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<location> &&location_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , reply_markup_(std::move(reply_markup_))
    , location_(std::move(location_))
{}

const int32_t editMessageLiveLocation::ID;

void editMessageLiveLocation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "editMessageLiveLocation");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (location_ == nullptr) {
            s.store_field("location", "null");
        } else {
            location_->store(s, "location");
        }
        s.store_class_end();
    }
}

editMessageReplyMarkup::editMessageReplyMarkup()
    : chat_id_()
    , message_id_()
    , reply_markup_()
{}

editMessageReplyMarkup::editMessageReplyMarkup(std::int64_t chat_id_, std::int64_t message_id_,
                                               object_ptr<ReplyMarkup> &&reply_markup_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , reply_markup_(std::move(reply_markup_))
{}

const int32_t editMessageReplyMarkup::ID;

void editMessageReplyMarkup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "editMessageReplyMarkup");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        s.store_class_end();
    }
}

editMessageText::editMessageText()
    : chat_id_()
    , message_id_()
    , reply_markup_()
    , input_message_content_()
{}

editMessageText::editMessageText(std::int64_t chat_id_, std::int64_t message_id_,
                                 object_ptr<ReplyMarkup> &&reply_markup_, object_ptr<InputMessageContent> &&input_message_content_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t editMessageText::ID;

void editMessageText::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "editMessageText");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

finishFileGeneration::finishFileGeneration()
    : generation_id_()
    , error_()
{}

finishFileGeneration::finishFileGeneration(std::int64_t generation_id_, object_ptr<error> &&error_)
    : generation_id_(generation_id_)
    , error_(std::move(error_))
{}

const int32_t finishFileGeneration::ID;

void finishFileGeneration::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "finishFileGeneration");
        s.store_field("generation_id", generation_id_);
        if (error_ == nullptr) {
            s.store_field("error", "null");
        } else {
            error_->store(s, "error");
        }
        s.store_class_end();
    }
}

forwardMessages::forwardMessages()
    : chat_id_()
    , from_chat_id_()
    , message_ids_()
    , disable_notification_()
    , from_background_()
    , as_album_()
{}

forwardMessages::forwardMessages(std::int64_t chat_id_, std::int64_t from_chat_id_,
                                 std::vector<std::int64_t> &&message_ids_, bool disable_notification_, bool from_background_,
                                 bool as_album_)
    : chat_id_(chat_id_)
    , from_chat_id_(from_chat_id_)
    , message_ids_(std::move(message_ids_))
    , disable_notification_(disable_notification_)
    , from_background_(from_background_)
    , as_album_(as_album_)
{}

const int32_t forwardMessages::ID;

void forwardMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "forwardMessages");
        s.store_field("chat_id", chat_id_);
        s.store_field("from_chat_id", from_chat_id_);
        {
            const std::vector<std::int64_t> &v = message_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("message_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("disable_notification", disable_notification_);
        s.store_field("from_background", from_background_);
        s.store_field("as_album", as_album_);
        s.store_class_end();
    }
}

generateChatInviteLink::generateChatInviteLink()
    : chat_id_()
{}

generateChatInviteLink::generateChatInviteLink(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t generateChatInviteLink::ID;

void generateChatInviteLink::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "generateChatInviteLink");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

getAccountTtl::getAccountTtl()
{
}

const int32_t getAccountTtl::ID;

void getAccountTtl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getAccountTtl");
        s.store_class_end();
    }
}

getActiveLiveLocationMessages::getActiveLiveLocationMessages()
{
}

const int32_t getActiveLiveLocationMessages::ID;

void getActiveLiveLocationMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getActiveLiveLocationMessages");
        s.store_class_end();
    }
}

getActiveSessions::getActiveSessions()
{
}

const int32_t getActiveSessions::ID;

void getActiveSessions::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getActiveSessions");
        s.store_class_end();
    }
}

getArchivedStickerSets::getArchivedStickerSets()
    : is_masks_()
    , offset_sticker_set_id_()
    , limit_()
{}

getArchivedStickerSets::getArchivedStickerSets(bool is_masks_, std::int64_t offset_sticker_set_id_,
                                               int32_t limit_)
    : is_masks_(is_masks_)
    , offset_sticker_set_id_(offset_sticker_set_id_)
    , limit_(limit_)
{}

const int32_t getArchivedStickerSets::ID;

void getArchivedStickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getArchivedStickerSets");
        s.store_field("is_masks", is_masks_);
        s.store_field("offset_sticker_set_id", offset_sticker_set_id_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

getAttachedStickerSets::getAttachedStickerSets()
    : file_id_()
{}

getAttachedStickerSets::getAttachedStickerSets(int32_t file_id_)
    : file_id_(file_id_)
{}

const int32_t getAttachedStickerSets::ID;

void getAttachedStickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getAttachedStickerSets");
        s.store_field("file_id", file_id_);
        s.store_class_end();
    }
}

getAuthorizationState::getAuthorizationState()
{
}

const int32_t getAuthorizationState::ID;

void getAuthorizationState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getAuthorizationState");
        s.store_class_end();
    }
}

getBasicGroup::getBasicGroup()
    : basic_group_id_()
{}

getBasicGroup::getBasicGroup(int32_t basic_group_id_)
    : basic_group_id_(basic_group_id_)
{}

const int32_t getBasicGroup::ID;

void getBasicGroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getBasicGroup");
        s.store_field("basic_group_id", basic_group_id_);
        s.store_class_end();
    }
}

getBasicGroupFullInfo::getBasicGroupFullInfo()
    : basic_group_id_()
{}

getBasicGroupFullInfo::getBasicGroupFullInfo(int32_t basic_group_id_)
    : basic_group_id_(basic_group_id_)
{}

const int32_t getBasicGroupFullInfo::ID;

void getBasicGroupFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getBasicGroupFullInfo");
        s.store_field("basic_group_id", basic_group_id_);
        s.store_class_end();
    }
}

getBlockedUsers::getBlockedUsers()
    : offset_()
    , limit_()
{}

getBlockedUsers::getBlockedUsers(int32_t offset_, int32_t limit_)
    : offset_(offset_)
    , limit_(limit_)
{}

const int32_t getBlockedUsers::ID;

void getBlockedUsers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getBlockedUsers");
        s.store_field("offset", offset_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

getCallbackQueryAnswer::getCallbackQueryAnswer()
    : chat_id_()
    , message_id_()
    , payload_()
{}

getCallbackQueryAnswer::getCallbackQueryAnswer(std::int64_t chat_id_, std::int64_t message_id_,
                                               object_ptr<CallbackQueryPayload> &&payload_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , payload_(std::move(payload_))
{}

const int32_t getCallbackQueryAnswer::ID;

void getCallbackQueryAnswer::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getCallbackQueryAnswer");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        if (payload_ == nullptr) {
            s.store_field("payload", "null");
        } else {
            payload_->store(s, "payload");
        }
        s.store_class_end();
    }
}

getChat::getChat()
    : chat_id_()
{}

getChat::getChat(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t getChat::ID;

void getChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getChat");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

getChatAdministrators::getChatAdministrators()
    : chat_id_()
{}

getChatAdministrators::getChatAdministrators(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t getChatAdministrators::ID;

void getChatAdministrators::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getChatAdministrators");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

getChatEventLog::getChatEventLog()
    : chat_id_()
    , query_()
    , from_event_id_()
    , limit_()
    , filters_()
    , user_ids_()
{}

getChatEventLog::getChatEventLog(std::int64_t chat_id_, std::string const &query_,
                                 std::int64_t from_event_id_, int32_t limit_, object_ptr<chatEventLogFilters> &&filters_,
                                 std::vector<int32_t> &&user_ids_)
    : chat_id_(chat_id_)
    , query_(std::move(query_))
    , from_event_id_(from_event_id_)
    , limit_(limit_)
    , filters_(std::move(filters_))
    , user_ids_(std::move(user_ids_))
{}

const int32_t getChatEventLog::ID;

void getChatEventLog::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getChatEventLog");
        s.store_field("chat_id", chat_id_);
        s.store_field("query", query_);
        s.store_field("from_event_id", from_event_id_);
        s.store_field("limit", limit_);
        if (filters_ == nullptr) {
            s.store_field("filters", "null");
        } else {
            filters_->store(s, "filters");
        }
        {
            const std::vector<int32_t> &v = user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

getChatHistory::getChatHistory()
    : chat_id_()
    , from_message_id_()
    , offset_()
    , limit_()
    , only_local_()
{}

getChatHistory::getChatHistory(std::int64_t chat_id_, std::int64_t from_message_id_,
                               int32_t offset_, int32_t limit_, bool only_local_)
    : chat_id_(chat_id_)
    , from_message_id_(from_message_id_)
    , offset_(offset_)
    , limit_(limit_)
    , only_local_(only_local_)
{}

const int32_t getChatHistory::ID;

void getChatHistory::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getChatHistory");
        s.store_field("chat_id", chat_id_);
        s.store_field("from_message_id", from_message_id_);
        s.store_field("offset", offset_);
        s.store_field("limit", limit_);
        s.store_field("only_local", only_local_);
        s.store_class_end();
    }
}

getChatMember::getChatMember()
    : chat_id_()
    , user_id_()
{}

getChatMember::getChatMember(std::int64_t chat_id_, int32_t user_id_)
    : chat_id_(chat_id_)
    , user_id_(user_id_)
{}

const int32_t getChatMember::ID;

void getChatMember::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getChatMember");
        s.store_field("chat_id", chat_id_);
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

getChatMessageByDate::getChatMessageByDate()
    : chat_id_()
    , date_()
{}

getChatMessageByDate::getChatMessageByDate(std::int64_t chat_id_, int32_t date_)
    : chat_id_(chat_id_)
    , date_(date_)
{}

const int32_t getChatMessageByDate::ID;

void getChatMessageByDate::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getChatMessageByDate");
        s.store_field("chat_id", chat_id_);
        s.store_field("date", date_);
        s.store_class_end();
    }
}

getChatReportSpamState::getChatReportSpamState()
    : chat_id_()
{}

getChatReportSpamState::getChatReportSpamState(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t getChatReportSpamState::ID;

void getChatReportSpamState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getChatReportSpamState");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

getChats::getChats()
    : offset_order_()
    , offset_chat_id_()
    , limit_()
{}

getChats::getChats(std::int64_t offset_order_, std::int64_t offset_chat_id_, int32_t limit_)
    : offset_order_(offset_order_)
    , offset_chat_id_(offset_chat_id_)
    , limit_(limit_)
{}

const int32_t getChats::ID;

void getChats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getChats");
        s.store_field("offset_order", offset_order_);
        s.store_field("offset_chat_id", offset_chat_id_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

getCreatedPublicChats::getCreatedPublicChats()
{
}

const int32_t getCreatedPublicChats::ID;

void getCreatedPublicChats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getCreatedPublicChats");
        s.store_class_end();
    }
}

getFavoriteStickers::getFavoriteStickers()
{
}

const int32_t getFavoriteStickers::ID;

void getFavoriteStickers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getFavoriteStickers");
        s.store_class_end();
    }
}

getFile::getFile()
    : file_id_()
{}

getFile::getFile(int32_t file_id_)
    : file_id_(file_id_)
{}

const int32_t getFile::ID;

void getFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getFile");
        s.store_field("file_id", file_id_);
        s.store_class_end();
    }
}

getFileExtension::getFileExtension()
    : mime_type_()
{}

getFileExtension::getFileExtension(std::string const &mime_type_)
    : mime_type_(std::move(mime_type_))
{}

const int32_t getFileExtension::ID;

void getFileExtension::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getFileExtension");
        s.store_field("mime_type", mime_type_);
        s.store_class_end();
    }
}

getFileMimeType::getFileMimeType()
    : file_name_()
{}

getFileMimeType::getFileMimeType(std::string const &file_name_)
    : file_name_(std::move(file_name_))
{}

const int32_t getFileMimeType::ID;

void getFileMimeType::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getFileMimeType");
        s.store_field("file_name", file_name_);
        s.store_class_end();
    }
}

getGameHighScores::getGameHighScores()
    : chat_id_()
    , message_id_()
    , user_id_()
{}

getGameHighScores::getGameHighScores(std::int64_t chat_id_, std::int64_t message_id_,
                                     int32_t user_id_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , user_id_(user_id_)
{}

const int32_t getGameHighScores::ID;

void getGameHighScores::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getGameHighScores");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

getGroupsInCommon::getGroupsInCommon()
    : user_id_()
    , offset_chat_id_()
    , limit_()
{}

getGroupsInCommon::getGroupsInCommon(int32_t user_id_, std::int64_t offset_chat_id_,
                                     int32_t limit_)
    : user_id_(user_id_)
    , offset_chat_id_(offset_chat_id_)
    , limit_(limit_)
{}

const int32_t getGroupsInCommon::ID;

void getGroupsInCommon::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getGroupsInCommon");
        s.store_field("user_id", user_id_);
        s.store_field("offset_chat_id", offset_chat_id_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

getImportedContactCount::getImportedContactCount()
{
}

const int32_t getImportedContactCount::ID;

void getImportedContactCount::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getImportedContactCount");
        s.store_class_end();
    }
}

getInlineGameHighScores::getInlineGameHighScores()
    : inline_message_id_()
    , user_id_()
{}

getInlineGameHighScores::getInlineGameHighScores(std::string const &inline_message_id_,
                                                 int32_t user_id_)
    : inline_message_id_(std::move(inline_message_id_))
    , user_id_(user_id_)
{}

const int32_t getInlineGameHighScores::ID;

void getInlineGameHighScores::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getInlineGameHighScores");
        s.store_field("inline_message_id", inline_message_id_);
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

getInlineQueryResults::getInlineQueryResults()
    : bot_user_id_()
    , chat_id_()
    , user_location_()
    , query_()
    , offset_()
{}

getInlineQueryResults::getInlineQueryResults(int32_t bot_user_id_, std::int64_t chat_id_,
                                             object_ptr<location> &&user_location_, std::string const &query_, std::string const &offset_)
    : bot_user_id_(bot_user_id_)
    , chat_id_(chat_id_)
    , user_location_(std::move(user_location_))
    , query_(std::move(query_))
    , offset_(std::move(offset_))
{}

const int32_t getInlineQueryResults::ID;

void getInlineQueryResults::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getInlineQueryResults");
        s.store_field("bot_user_id", bot_user_id_);
        s.store_field("chat_id", chat_id_);
        if (user_location_ == nullptr) {
            s.store_field("user_location", "null");
        } else {
            user_location_->store(s, "user_location");
        }
        s.store_field("query", query_);
        s.store_field("offset", offset_);
        s.store_class_end();
    }
}

getInstalledStickerSets::getInstalledStickerSets()
    : is_masks_()
{}

getInstalledStickerSets::getInstalledStickerSets(bool is_masks_)
    : is_masks_(is_masks_)
{}

const int32_t getInstalledStickerSets::ID;

void getInstalledStickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getInstalledStickerSets");
        s.store_field("is_masks", is_masks_);
        s.store_class_end();
    }
}

getInviteText::getInviteText()
{
}

const int32_t getInviteText::ID;

void getInviteText::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getInviteText");
        s.store_class_end();
    }
}

getMe::getMe()
{
}

const int32_t getMe::ID;

void getMe::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getMe");
        s.store_class_end();
    }
}

getMessage::getMessage()
    : chat_id_()
    , message_id_()
{}

getMessage::getMessage(std::int64_t chat_id_, std::int64_t message_id_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
{}

const int32_t getMessage::ID;

void getMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getMessage");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_class_end();
    }
}

getMessages::getMessages()
    : chat_id_()
    , message_ids_()
{}

getMessages::getMessages(std::int64_t chat_id_, std::vector<std::int64_t> &&message_ids_)
    : chat_id_(chat_id_)
    , message_ids_(std::move(message_ids_))
{}

const int32_t getMessages::ID;

void getMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getMessages");
        s.store_field("chat_id", chat_id_);
        {
            const std::vector<std::int64_t> &v = message_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("message_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

getNetworkStatistics::getNetworkStatistics()
    : only_current_()
{}

getNetworkStatistics::getNetworkStatistics(bool only_current_)
    : only_current_(only_current_)
{}

const int32_t getNetworkStatistics::ID;

void getNetworkStatistics::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getNetworkStatistics");
        s.store_field("only_current", only_current_);
        s.store_class_end();
    }
}

getNotificationSettings::getNotificationSettings()
    : scope_()
{}

getNotificationSettings::getNotificationSettings(object_ptr<NotificationSettingsScope> &&scope_)
    : scope_(std::move(scope_))
{}

const int32_t getNotificationSettings::ID;

void getNotificationSettings::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getNotificationSettings");
        if (scope_ == nullptr) {
            s.store_field("scope", "null");
        } else {
            scope_->store(s, "scope");
        }
        s.store_class_end();
    }
}

getOption::getOption()
    : name_()
{}

getOption::getOption(std::string const &name_)
    : name_(std::move(name_))
{}

const int32_t getOption::ID;

void getOption::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getOption");
        s.store_field("name", name_);
        s.store_class_end();
    }
}

getPasswordState::getPasswordState()
{
}

const int32_t getPasswordState::ID;

void getPasswordState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getPasswordState");
        s.store_class_end();
    }
}

getPaymentForm::getPaymentForm()
    : chat_id_()
    , message_id_()
{}

getPaymentForm::getPaymentForm(std::int64_t chat_id_, std::int64_t message_id_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
{}

const int32_t getPaymentForm::ID;

void getPaymentForm::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getPaymentForm");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_class_end();
    }
}

getPaymentReceipt::getPaymentReceipt()
    : chat_id_()
    , message_id_()
{}

getPaymentReceipt::getPaymentReceipt(std::int64_t chat_id_, std::int64_t message_id_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
{}

const int32_t getPaymentReceipt::ID;

void getPaymentReceipt::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getPaymentReceipt");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_class_end();
    }
}

getProxy::getProxy()
{
}

const int32_t getProxy::ID;

void getProxy::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getProxy");
        s.store_class_end();
    }
}

getPublicMessageLink::getPublicMessageLink()
    : chat_id_()
    , message_id_()
    , for_album_()
{}

getPublicMessageLink::getPublicMessageLink(std::int64_t chat_id_, std::int64_t message_id_,
                                           bool for_album_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , for_album_(for_album_)
{}

const int32_t getPublicMessageLink::ID;

void getPublicMessageLink::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getPublicMessageLink");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("for_album", for_album_);
        s.store_class_end();
    }
}

getRecentInlineBots::getRecentInlineBots()
{
}

const int32_t getRecentInlineBots::ID;

void getRecentInlineBots::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getRecentInlineBots");
        s.store_class_end();
    }
}

getRecentStickers::getRecentStickers()
    : is_attached_()
{}

getRecentStickers::getRecentStickers(bool is_attached_)
    : is_attached_(is_attached_)
{}

const int32_t getRecentStickers::ID;

void getRecentStickers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getRecentStickers");
        s.store_field("is_attached", is_attached_);
        s.store_class_end();
    }
}

getRecentlyVisitedTMeUrls::getRecentlyVisitedTMeUrls()
    : referrer_()
{}

getRecentlyVisitedTMeUrls::getRecentlyVisitedTMeUrls(std::string const &referrer_)
    : referrer_(std::move(referrer_))
{}

const int32_t getRecentlyVisitedTMeUrls::ID;

void getRecentlyVisitedTMeUrls::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getRecentlyVisitedTMeUrls");
        s.store_field("referrer", referrer_);
        s.store_class_end();
    }
}

getRecoveryEmailAddress::getRecoveryEmailAddress()
    : password_()
{}

getRecoveryEmailAddress::getRecoveryEmailAddress(std::string const &password_)
    : password_(std::move(password_))
{}

const int32_t getRecoveryEmailAddress::ID;

void getRecoveryEmailAddress::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getRecoveryEmailAddress");
        s.store_field("password", password_);
        s.store_class_end();
    }
}

getRemoteFile::getRemoteFile()
    : remote_file_id_()
    , file_type_()
{}

getRemoteFile::getRemoteFile(std::string const &remote_file_id_, object_ptr<FileType> &&file_type_)
    : remote_file_id_(std::move(remote_file_id_))
    , file_type_(std::move(file_type_))
{}

const int32_t getRemoteFile::ID;

void getRemoteFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getRemoteFile");
        s.store_field("remote_file_id", remote_file_id_);
        if (file_type_ == nullptr) {
            s.store_field("file_type", "null");
        } else {
            file_type_->store(s, "file_type");
        }
        s.store_class_end();
    }
}

getSavedAnimations::getSavedAnimations()
{
}

const int32_t getSavedAnimations::ID;

void getSavedAnimations::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getSavedAnimations");
        s.store_class_end();
    }
}

getSavedOrderInfo::getSavedOrderInfo()
{
}

const int32_t getSavedOrderInfo::ID;

void getSavedOrderInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getSavedOrderInfo");
        s.store_class_end();
    }
}

getSecretChat::getSecretChat()
    : secret_chat_id_()
{}

getSecretChat::getSecretChat(int32_t secret_chat_id_)
    : secret_chat_id_(secret_chat_id_)
{}

const int32_t getSecretChat::ID;

void getSecretChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getSecretChat");
        s.store_field("secret_chat_id", secret_chat_id_);
        s.store_class_end();
    }
}

getStickerEmojis::getStickerEmojis()
    : sticker_()
{}

getStickerEmojis::getStickerEmojis(object_ptr<InputFile> &&sticker_)
    : sticker_(std::move(sticker_))
{}

const int32_t getStickerEmojis::ID;

void getStickerEmojis::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getStickerEmojis");
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

getStickerSet::getStickerSet()
    : set_id_()
{}

getStickerSet::getStickerSet(std::int64_t set_id_)
    : set_id_(set_id_)
{}

const int32_t getStickerSet::ID;

void getStickerSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getStickerSet");
        s.store_field("set_id", set_id_);
        s.store_class_end();
    }
}

getStickers::getStickers()
    : emoji_()
    , limit_()
{}

getStickers::getStickers(std::string const &emoji_, int32_t limit_)
    : emoji_(std::move(emoji_))
    , limit_(limit_)
{}

const int32_t getStickers::ID;

void getStickers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getStickers");
        s.store_field("emoji", emoji_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

getStorageStatistics::getStorageStatistics()
    : chat_limit_()
{}

getStorageStatistics::getStorageStatistics(int32_t chat_limit_)
    : chat_limit_(chat_limit_)
{}

const int32_t getStorageStatistics::ID;

void getStorageStatistics::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getStorageStatistics");
        s.store_field("chat_limit", chat_limit_);
        s.store_class_end();
    }
}

getStorageStatisticsFast::getStorageStatisticsFast()
{
}

const int32_t getStorageStatisticsFast::ID;

void getStorageStatisticsFast::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getStorageStatisticsFast");
        s.store_class_end();
    }
}

getSupergroup::getSupergroup()
    : supergroup_id_()
{}

getSupergroup::getSupergroup(int32_t supergroup_id_)
    : supergroup_id_(supergroup_id_)
{}

const int32_t getSupergroup::ID;

void getSupergroup::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getSupergroup");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_class_end();
    }
}

getSupergroupFullInfo::getSupergroupFullInfo()
    : supergroup_id_()
{}

getSupergroupFullInfo::getSupergroupFullInfo(int32_t supergroup_id_)
    : supergroup_id_(supergroup_id_)
{}

const int32_t getSupergroupFullInfo::ID;

void getSupergroupFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getSupergroupFullInfo");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_class_end();
    }
}

getSupergroupMembers::getSupergroupMembers()
    : supergroup_id_()
    , filter_()
    , offset_()
    , limit_()
{}

getSupergroupMembers::getSupergroupMembers(int32_t supergroup_id_,
                                           object_ptr<SupergroupMembersFilter> &&filter_, int32_t offset_, int32_t limit_)
    : supergroup_id_(supergroup_id_)
    , filter_(std::move(filter_))
    , offset_(offset_)
    , limit_(limit_)
{}

const int32_t getSupergroupMembers::ID;

void getSupergroupMembers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getSupergroupMembers");
        s.store_field("supergroup_id", supergroup_id_);
        if (filter_ == nullptr) {
            s.store_field("filter", "null");
        } else {
            filter_->store(s, "filter");
        }
        s.store_field("offset", offset_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

getSupportUser::getSupportUser()
{
}

const int32_t getSupportUser::ID;

void getSupportUser::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getSupportUser");
        s.store_class_end();
    }
}

getTemporaryPasswordState::getTemporaryPasswordState()
{
}

const int32_t getTemporaryPasswordState::ID;

void getTemporaryPasswordState::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getTemporaryPasswordState");
        s.store_class_end();
    }
}

getTermsOfService::getTermsOfService()
{
}

const int32_t getTermsOfService::ID;

void getTermsOfService::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getTermsOfService");
        s.store_class_end();
    }
}

getTextEntities::getTextEntities()
    : text_()
{}

getTextEntities::getTextEntities(std::string const &text_)
    : text_(std::move(text_))
{}

const int32_t getTextEntities::ID;

void getTextEntities::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getTextEntities");
        s.store_field("text", text_);
        s.store_class_end();
    }
}

getTopChats::getTopChats()
    : category_()
    , limit_()
{}

getTopChats::getTopChats(object_ptr<TopChatCategory> &&category_, int32_t limit_)
    : category_(std::move(category_))
    , limit_(limit_)
{}

const int32_t getTopChats::ID;

void getTopChats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getTopChats");
        if (category_ == nullptr) {
            s.store_field("category", "null");
        } else {
            category_->store(s, "category");
        }
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

getTrendingStickerSets::getTrendingStickerSets()
{
}

const int32_t getTrendingStickerSets::ID;

void getTrendingStickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getTrendingStickerSets");
        s.store_class_end();
    }
}

getUser::getUser()
    : user_id_()
{}

getUser::getUser(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t getUser::ID;

void getUser::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getUser");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

getUserFullInfo::getUserFullInfo()
    : user_id_()
{}

getUserFullInfo::getUserFullInfo(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t getUserFullInfo::ID;

void getUserFullInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getUserFullInfo");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

getUserPrivacySettingRules::getUserPrivacySettingRules()
    : setting_()
{}

getUserPrivacySettingRules::getUserPrivacySettingRules(object_ptr<UserPrivacySetting> &&setting_)
    : setting_(std::move(setting_))
{}

const int32_t getUserPrivacySettingRules::ID;

void getUserPrivacySettingRules::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getUserPrivacySettingRules");
        if (setting_ == nullptr) {
            s.store_field("setting", "null");
        } else {
            setting_->store(s, "setting");
        }
        s.store_class_end();
    }
}

getUserProfilePhotos::getUserProfilePhotos()
    : user_id_()
    , offset_()
    , limit_()
{}

getUserProfilePhotos::getUserProfilePhotos(int32_t user_id_, int32_t offset_,
                                           int32_t limit_)
    : user_id_(user_id_)
    , offset_(offset_)
    , limit_(limit_)
{}

const int32_t getUserProfilePhotos::ID;

void getUserProfilePhotos::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getUserProfilePhotos");
        s.store_field("user_id", user_id_);
        s.store_field("offset", offset_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

getWallpapers::getWallpapers()
{
}

const int32_t getWallpapers::ID;

void getWallpapers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getWallpapers");
        s.store_class_end();
    }
}

getWebPageInstantView::getWebPageInstantView()
    : url_()
    , force_full_()
{}

getWebPageInstantView::getWebPageInstantView(std::string const &url_, bool force_full_)
    : url_(std::move(url_))
    , force_full_(force_full_)
{}

const int32_t getWebPageInstantView::ID;

void getWebPageInstantView::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getWebPageInstantView");
        s.store_field("url", url_);
        s.store_field("force_full", force_full_);
        s.store_class_end();
    }
}

getWebPagePreview::getWebPagePreview()
    : message_text_()
{}

getWebPagePreview::getWebPagePreview(std::string const &message_text_)
    : message_text_(std::move(message_text_))
{}

const int32_t getWebPagePreview::ID;

void getWebPagePreview::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "getWebPagePreview");
        s.store_field("message_text", message_text_);
        s.store_class_end();
    }
}

importContacts::importContacts()
    : contacts_()
{}

importContacts::importContacts(std::vector<object_ptr<contact>> &&contacts_)
    : contacts_(std::move(contacts_))
{}

const int32_t importContacts::ID;

void importContacts::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "importContacts");
        {
            const std::vector<object_ptr<contact>> &v = contacts_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("contacts", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

joinChatByInviteLink::joinChatByInviteLink()
    : invite_link_()
{}

joinChatByInviteLink::joinChatByInviteLink(std::string const &invite_link_)
    : invite_link_(std::move(invite_link_))
{}

const int32_t joinChatByInviteLink::ID;

void joinChatByInviteLink::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "joinChatByInviteLink");
        s.store_field("invite_link", invite_link_);
        s.store_class_end();
    }
}

logOut::logOut()
{
}

const int32_t logOut::ID;

void logOut::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "logOut");
        s.store_class_end();
    }
}

openChat::openChat()
    : chat_id_()
{}

openChat::openChat(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t openChat::ID;

void openChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "openChat");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

openMessageContent::openMessageContent()
    : chat_id_()
    , message_id_()
{}

openMessageContent::openMessageContent(std::int64_t chat_id_, std::int64_t message_id_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
{}

const int32_t openMessageContent::ID;

void openMessageContent::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "openMessageContent");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_class_end();
    }
}

optimizeStorage::optimizeStorage()
    : size_()
    , ttl_()
    , count_()
    , immunity_delay_()
    , file_types_()
    , chat_ids_()
    , exclude_chat_ids_()
    , chat_limit_()
{}

optimizeStorage::optimizeStorage(std::int64_t size_, int32_t ttl_, int32_t count_,
                                 int32_t immunity_delay_, std::vector<object_ptr<FileType>> &&file_types_,
                                 std::vector<std::int64_t> &&chat_ids_, std::vector<std::int64_t> &&exclude_chat_ids_,
                                 int32_t chat_limit_)
    : size_(size_)
    , ttl_(ttl_)
    , count_(count_)
    , immunity_delay_(immunity_delay_)
    , file_types_(std::move(file_types_))
    , chat_ids_(std::move(chat_ids_))
    , exclude_chat_ids_(std::move(exclude_chat_ids_))
    , chat_limit_(chat_limit_)
{}

const int32_t optimizeStorage::ID;

void optimizeStorage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "optimizeStorage");
        s.store_field("size", size_);
        s.store_field("ttl", ttl_);
        s.store_field("count", count_);
        s.store_field("immunity_delay", immunity_delay_);
        {
            const std::vector<object_ptr<FileType>> &v = file_types_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("file_types", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        {
            const std::vector<std::int64_t> &v = chat_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("chat_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        {
            const std::vector<std::int64_t> &v = exclude_chat_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("exclude_chat_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("chat_limit", chat_limit_);
        s.store_class_end();
    }
}

parseTextEntities::parseTextEntities()
    : text_()
    , parse_mode_()
{}

parseTextEntities::parseTextEntities(std::string const &text_,
                                     object_ptr<TextParseMode> &&parse_mode_)
    : text_(std::move(text_))
    , parse_mode_(std::move(parse_mode_))
{}

const int32_t parseTextEntities::ID;

void parseTextEntities::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "parseTextEntities");
        s.store_field("text", text_);
        if (parse_mode_ == nullptr) {
            s.store_field("parse_mode", "null");
        } else {
            parse_mode_->store(s, "parse_mode");
        }
        s.store_class_end();
    }
}

pinSupergroupMessage::pinSupergroupMessage()
    : supergroup_id_()
    , message_id_()
    , disable_notification_()
{}

pinSupergroupMessage::pinSupergroupMessage(int32_t supergroup_id_, std::int64_t message_id_,
                                           bool disable_notification_)
    : supergroup_id_(supergroup_id_)
    , message_id_(message_id_)
    , disable_notification_(disable_notification_)
{}

const int32_t pinSupergroupMessage::ID;

void pinSupergroupMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "pinSupergroupMessage");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("message_id", message_id_);
        s.store_field("disable_notification", disable_notification_);
        s.store_class_end();
    }
}

processDcUpdate::processDcUpdate()
    : dc_()
    , addr_()
{}

processDcUpdate::processDcUpdate(std::string const &dc_, std::string const &addr_)
    : dc_(std::move(dc_))
    , addr_(std::move(addr_))
{}

const int32_t processDcUpdate::ID;

void processDcUpdate::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "processDcUpdate");
        s.store_field("dc", dc_);
        s.store_field("addr", addr_);
        s.store_class_end();
    }
}

readAllChatMentions::readAllChatMentions()
    : chat_id_()
{}

readAllChatMentions::readAllChatMentions(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t readAllChatMentions::ID;

void readAllChatMentions::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "readAllChatMentions");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

recoverAuthenticationPassword::recoverAuthenticationPassword()
    : recovery_code_()
{}

recoverAuthenticationPassword::recoverAuthenticationPassword(std::string const &recovery_code_)
    : recovery_code_(std::move(recovery_code_))
{}

const int32_t recoverAuthenticationPassword::ID;

void recoverAuthenticationPassword::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "recoverAuthenticationPassword");
        s.store_field("recovery_code", recovery_code_);
        s.store_class_end();
    }
}

recoverPassword::recoverPassword()
    : recovery_code_()
{}

recoverPassword::recoverPassword(std::string const &recovery_code_)
    : recovery_code_(std::move(recovery_code_))
{}

const int32_t recoverPassword::ID;

void recoverPassword::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "recoverPassword");
        s.store_field("recovery_code", recovery_code_);
        s.store_class_end();
    }
}

registerDevice::registerDevice()
    : device_token_()
    , other_user_ids_()
{}

registerDevice::registerDevice(object_ptr<DeviceToken> &&device_token_,
                               std::vector<int32_t> &&other_user_ids_)
    : device_token_(std::move(device_token_))
    , other_user_ids_(std::move(other_user_ids_))
{}

const int32_t registerDevice::ID;

void registerDevice::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "registerDevice");
        if (device_token_ == nullptr) {
            s.store_field("device_token", "null");
        } else {
            device_token_->store(s, "device_token");
        }
        {
            const std::vector<int32_t> &v = other_user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("other_user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

removeContacts::removeContacts()
    : user_ids_()
{}

removeContacts::removeContacts(std::vector<int32_t> &&user_ids_)
    : user_ids_(std::move(user_ids_))
{}

const int32_t removeContacts::ID;

void removeContacts::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "removeContacts");
        {
            const std::vector<int32_t> &v = user_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("user_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

removeFavoriteSticker::removeFavoriteSticker()
    : sticker_()
{}

removeFavoriteSticker::removeFavoriteSticker(object_ptr<InputFile> &&sticker_)
    : sticker_(std::move(sticker_))
{}

const int32_t removeFavoriteSticker::ID;

void removeFavoriteSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "removeFavoriteSticker");
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

removeRecentHashtag::removeRecentHashtag()
    : hashtag_()
{}

removeRecentHashtag::removeRecentHashtag(std::string const &hashtag_)
    : hashtag_(std::move(hashtag_))
{}

const int32_t removeRecentHashtag::ID;

void removeRecentHashtag::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "removeRecentHashtag");
        s.store_field("hashtag", hashtag_);
        s.store_class_end();
    }
}

removeRecentSticker::removeRecentSticker()
    : is_attached_()
    , sticker_()
{}

removeRecentSticker::removeRecentSticker(bool is_attached_, object_ptr<InputFile> &&sticker_)
    : is_attached_(is_attached_)
    , sticker_(std::move(sticker_))
{}

const int32_t removeRecentSticker::ID;

void removeRecentSticker::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "removeRecentSticker");
        s.store_field("is_attached", is_attached_);
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

removeRecentlyFoundChat::removeRecentlyFoundChat()
    : chat_id_()
{}

removeRecentlyFoundChat::removeRecentlyFoundChat(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t removeRecentlyFoundChat::ID;

void removeRecentlyFoundChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "removeRecentlyFoundChat");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

removeSavedAnimation::removeSavedAnimation()
    : animation_()
{}

removeSavedAnimation::removeSavedAnimation(object_ptr<InputFile> &&animation_)
    : animation_(std::move(animation_))
{}

const int32_t removeSavedAnimation::ID;

void removeSavedAnimation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "removeSavedAnimation");
        if (animation_ == nullptr) {
            s.store_field("animation", "null");
        } else {
            animation_->store(s, "animation");
        }
        s.store_class_end();
    }
}

removeStickerFromSet::removeStickerFromSet()
    : sticker_()
{}

removeStickerFromSet::removeStickerFromSet(object_ptr<InputFile> &&sticker_)
    : sticker_(std::move(sticker_))
{}

const int32_t removeStickerFromSet::ID;

void removeStickerFromSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "removeStickerFromSet");
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_class_end();
    }
}

removeTopChat::removeTopChat()
    : category_()
    , chat_id_()
{}

removeTopChat::removeTopChat(object_ptr<TopChatCategory> &&category_, std::int64_t chat_id_)
    : category_(std::move(category_))
    , chat_id_(chat_id_)
{}

const int32_t removeTopChat::ID;

void removeTopChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "removeTopChat");
        if (category_ == nullptr) {
            s.store_field("category", "null");
        } else {
            category_->store(s, "category");
        }
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

reorderInstalledStickerSets::reorderInstalledStickerSets()
    : is_masks_()
    , sticker_set_ids_()
{}

reorderInstalledStickerSets::reorderInstalledStickerSets(bool is_masks_,
                                                         std::vector<std::int64_t> &&sticker_set_ids_)
    : is_masks_(is_masks_)
    , sticker_set_ids_(std::move(sticker_set_ids_))
{}

const int32_t reorderInstalledStickerSets::ID;

void reorderInstalledStickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "reorderInstalledStickerSets");
        s.store_field("is_masks", is_masks_);
        {
            const std::vector<std::int64_t> &v = sticker_set_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sticker_set_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

reportChat::reportChat()
    : chat_id_()
    , reason_()
{}

reportChat::reportChat(std::int64_t chat_id_, object_ptr<ChatReportReason> &&reason_)
    : chat_id_(chat_id_)
    , reason_(std::move(reason_))
{}

const int32_t reportChat::ID;

void reportChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "reportChat");
        s.store_field("chat_id", chat_id_);
        if (reason_ == nullptr) {
            s.store_field("reason", "null");
        } else {
            reason_->store(s, "reason");
        }
        s.store_class_end();
    }
}

reportSupergroupSpam::reportSupergroupSpam()
    : supergroup_id_()
    , user_id_()
    , message_ids_()
{}

reportSupergroupSpam::reportSupergroupSpam(int32_t supergroup_id_, int32_t user_id_,
                                           std::vector<std::int64_t> &&message_ids_)
    : supergroup_id_(supergroup_id_)
    , user_id_(user_id_)
    , message_ids_(std::move(message_ids_))
{}

const int32_t reportSupergroupSpam::ID;

void reportSupergroupSpam::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "reportSupergroupSpam");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("user_id", user_id_);
        {
            const std::vector<std::int64_t> &v = message_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("message_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

requestAuthenticationPasswordRecovery::requestAuthenticationPasswordRecovery()
{
}

const int32_t requestAuthenticationPasswordRecovery::ID;

void requestAuthenticationPasswordRecovery::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "requestAuthenticationPasswordRecovery");
        s.store_class_end();
    }
}

requestPasswordRecovery::requestPasswordRecovery()
{
}

const int32_t requestPasswordRecovery::ID;

void requestPasswordRecovery::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "requestPasswordRecovery");
        s.store_class_end();
    }
}

resendAuthenticationCode::resendAuthenticationCode()
{
}

const int32_t resendAuthenticationCode::ID;

void resendAuthenticationCode::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "resendAuthenticationCode");
        s.store_class_end();
    }
}

resendChangePhoneNumberCode::resendChangePhoneNumberCode()
{
}

const int32_t resendChangePhoneNumberCode::ID;

void resendChangePhoneNumberCode::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "resendChangePhoneNumberCode");
        s.store_class_end();
    }
}

resetAllNotificationSettings::resetAllNotificationSettings()
{
}

const int32_t resetAllNotificationSettings::ID;

void resetAllNotificationSettings::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "resetAllNotificationSettings");
        s.store_class_end();
    }
}

resetNetworkStatistics::resetNetworkStatistics()
{
}

const int32_t resetNetworkStatistics::ID;

void resetNetworkStatistics::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "resetNetworkStatistics");
        s.store_class_end();
    }
}

searchCallMessages::searchCallMessages()
    : from_message_id_()
    , limit_()
    , only_missed_()
{}

searchCallMessages::searchCallMessages(std::int64_t from_message_id_, int32_t limit_,
                                       bool only_missed_)
    : from_message_id_(from_message_id_)
    , limit_(limit_)
    , only_missed_(only_missed_)
{}

const int32_t searchCallMessages::ID;

void searchCallMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchCallMessages");
        s.store_field("from_message_id", from_message_id_);
        s.store_field("limit", limit_);
        s.store_field("only_missed", only_missed_);
        s.store_class_end();
    }
}

searchChatMembers::searchChatMembers()
    : chat_id_()
    , query_()
    , limit_()
{}

searchChatMembers::searchChatMembers(std::int64_t chat_id_, std::string const &query_,
                                     int32_t limit_)
    : chat_id_(chat_id_)
    , query_(std::move(query_))
    , limit_(limit_)
{}

const int32_t searchChatMembers::ID;

void searchChatMembers::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchChatMembers");
        s.store_field("chat_id", chat_id_);
        s.store_field("query", query_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

searchChatMessages::searchChatMessages()
    : chat_id_()
    , query_()
    , sender_user_id_()
    , from_message_id_()
    , offset_()
    , limit_()
    , filter_()
{}

searchChatMessages::searchChatMessages(std::int64_t chat_id_, std::string const &query_,
                                       int32_t sender_user_id_, std::int64_t from_message_id_, int32_t offset_,
                                       int32_t limit_, object_ptr<SearchMessagesFilter> &&filter_)
    : chat_id_(chat_id_)
    , query_(std::move(query_))
    , sender_user_id_(sender_user_id_)
    , from_message_id_(from_message_id_)
    , offset_(offset_)
    , limit_(limit_)
    , filter_(std::move(filter_))
{}

const int32_t searchChatMessages::ID;

void searchChatMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchChatMessages");
        s.store_field("chat_id", chat_id_);
        s.store_field("query", query_);
        s.store_field("sender_user_id", sender_user_id_);
        s.store_field("from_message_id", from_message_id_);
        s.store_field("offset", offset_);
        s.store_field("limit", limit_);
        if (filter_ == nullptr) {
            s.store_field("filter", "null");
        } else {
            filter_->store(s, "filter");
        }
        s.store_class_end();
    }
}

searchChatRecentLocationMessages::searchChatRecentLocationMessages()
    : chat_id_()
    , limit_()
{}

searchChatRecentLocationMessages::searchChatRecentLocationMessages(std::int64_t chat_id_,
                                                                   int32_t limit_)
    : chat_id_(chat_id_)
    , limit_(limit_)
{}

const int32_t searchChatRecentLocationMessages::ID;

void searchChatRecentLocationMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchChatRecentLocationMessages");
        s.store_field("chat_id", chat_id_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

searchChats::searchChats()
    : query_()
    , limit_()
{}

searchChats::searchChats(std::string const &query_, int32_t limit_)
    : query_(std::move(query_))
    , limit_(limit_)
{}

const int32_t searchChats::ID;

void searchChats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchChats");
        s.store_field("query", query_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

searchChatsOnServer::searchChatsOnServer()
    : query_()
    , limit_()
{}

searchChatsOnServer::searchChatsOnServer(std::string const &query_, int32_t limit_)
    : query_(std::move(query_))
    , limit_(limit_)
{}

const int32_t searchChatsOnServer::ID;

void searchChatsOnServer::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchChatsOnServer");
        s.store_field("query", query_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

searchContacts::searchContacts()
    : query_()
    , limit_()
{}

searchContacts::searchContacts(std::string const &query_, int32_t limit_)
    : query_(std::move(query_))
    , limit_(limit_)
{}

const int32_t searchContacts::ID;

void searchContacts::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchContacts");
        s.store_field("query", query_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

searchHashtags::searchHashtags()
    : prefix_()
    , limit_()
{}

searchHashtags::searchHashtags(std::string const &prefix_, int32_t limit_)
    : prefix_(std::move(prefix_))
    , limit_(limit_)
{}

const int32_t searchHashtags::ID;

void searchHashtags::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchHashtags");
        s.store_field("prefix", prefix_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

searchMessages::searchMessages()
    : query_()
    , offset_date_()
    , offset_chat_id_()
    , offset_message_id_()
    , limit_()
{}

searchMessages::searchMessages(std::string const &query_, int32_t offset_date_,
                               std::int64_t offset_chat_id_, std::int64_t offset_message_id_, int32_t limit_)
    : query_(std::move(query_))
    , offset_date_(offset_date_)
    , offset_chat_id_(offset_chat_id_)
    , offset_message_id_(offset_message_id_)
    , limit_(limit_)
{}

const int32_t searchMessages::ID;

void searchMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchMessages");
        s.store_field("query", query_);
        s.store_field("offset_date", offset_date_);
        s.store_field("offset_chat_id", offset_chat_id_);
        s.store_field("offset_message_id", offset_message_id_);
        s.store_field("limit", limit_);
        s.store_class_end();
    }
}

searchPublicChat::searchPublicChat()
    : username_()
{}

searchPublicChat::searchPublicChat(std::string const &username_)
    : username_(std::move(username_))
{}

const int32_t searchPublicChat::ID;

void searchPublicChat::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchPublicChat");
        s.store_field("username", username_);
        s.store_class_end();
    }
}

searchPublicChats::searchPublicChats()
    : query_()
{}

searchPublicChats::searchPublicChats(std::string const &query_)
    : query_(std::move(query_))
{}

const int32_t searchPublicChats::ID;

void searchPublicChats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchPublicChats");
        s.store_field("query", query_);
        s.store_class_end();
    }
}

searchSecretMessages::searchSecretMessages()
    : chat_id_()
    , query_()
    , from_search_id_()
    , limit_()
    , filter_()
{}

searchSecretMessages::searchSecretMessages(std::int64_t chat_id_, std::string const &query_,
                                           std::int64_t from_search_id_, int32_t limit_, object_ptr<SearchMessagesFilter> &&filter_)
    : chat_id_(chat_id_)
    , query_(std::move(query_))
    , from_search_id_(from_search_id_)
    , limit_(limit_)
    , filter_(std::move(filter_))
{}

const int32_t searchSecretMessages::ID;

void searchSecretMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchSecretMessages");
        s.store_field("chat_id", chat_id_);
        s.store_field("query", query_);
        s.store_field("from_search_id", from_search_id_);
        s.store_field("limit", limit_);
        if (filter_ == nullptr) {
            s.store_field("filter", "null");
        } else {
            filter_->store(s, "filter");
        }
        s.store_class_end();
    }
}

searchStickerSet::searchStickerSet()
    : name_()
{}

searchStickerSet::searchStickerSet(std::string const &name_)
    : name_(std::move(name_))
{}

const int32_t searchStickerSet::ID;

void searchStickerSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "searchStickerSet");
        s.store_field("name", name_);
        s.store_class_end();
    }
}

sendBotStartMessage::sendBotStartMessage()
    : bot_user_id_()
    , chat_id_()
    , parameter_()
{}

sendBotStartMessage::sendBotStartMessage(int32_t bot_user_id_, std::int64_t chat_id_,
                                         std::string const &parameter_)
    : bot_user_id_(bot_user_id_)
    , chat_id_(chat_id_)
    , parameter_(std::move(parameter_))
{}

const int32_t sendBotStartMessage::ID;

void sendBotStartMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendBotStartMessage");
        s.store_field("bot_user_id", bot_user_id_);
        s.store_field("chat_id", chat_id_);
        s.store_field("parameter", parameter_);
        s.store_class_end();
    }
}

sendCallDebugInformation::sendCallDebugInformation()
    : call_id_()
    , debug_information_()
{}

sendCallDebugInformation::sendCallDebugInformation(int32_t call_id_,
                                                   std::string const &debug_information_)
    : call_id_(call_id_)
    , debug_information_(std::move(debug_information_))
{}

const int32_t sendCallDebugInformation::ID;

void sendCallDebugInformation::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendCallDebugInformation");
        s.store_field("call_id", call_id_);
        s.store_field("debug_information", debug_information_);
        s.store_class_end();
    }
}

sendCallRating::sendCallRating()
    : call_id_()
    , rating_()
    , comment_()
{}

sendCallRating::sendCallRating(int32_t call_id_, int32_t rating_,
                               std::string const &comment_)
    : call_id_(call_id_)
    , rating_(rating_)
    , comment_(std::move(comment_))
{}

const int32_t sendCallRating::ID;

void sendCallRating::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendCallRating");
        s.store_field("call_id", call_id_);
        s.store_field("rating", rating_);
        s.store_field("comment", comment_);
        s.store_class_end();
    }
}

sendChatAction::sendChatAction()
    : chat_id_()
    , action_()
{}

sendChatAction::sendChatAction(std::int64_t chat_id_, object_ptr<ChatAction> &&action_)
    : chat_id_(chat_id_)
    , action_(std::move(action_))
{}

const int32_t sendChatAction::ID;

void sendChatAction::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendChatAction");
        s.store_field("chat_id", chat_id_);
        if (action_ == nullptr) {
            s.store_field("action", "null");
        } else {
            action_->store(s, "action");
        }
        s.store_class_end();
    }
}

sendChatScreenshotTakenNotification::sendChatScreenshotTakenNotification()
    : chat_id_()
{}

sendChatScreenshotTakenNotification::sendChatScreenshotTakenNotification(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t sendChatScreenshotTakenNotification::ID;

void sendChatScreenshotTakenNotification::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendChatScreenshotTakenNotification");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

sendChatSetTtlMessage::sendChatSetTtlMessage()
    : chat_id_()
    , ttl_()
{}

sendChatSetTtlMessage::sendChatSetTtlMessage(std::int64_t chat_id_, int32_t ttl_)
    : chat_id_(chat_id_)
    , ttl_(ttl_)
{}

const int32_t sendChatSetTtlMessage::ID;

void sendChatSetTtlMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendChatSetTtlMessage");
        s.store_field("chat_id", chat_id_);
        s.store_field("ttl", ttl_);
        s.store_class_end();
    }
}

sendCustomRequest::sendCustomRequest()
    : method_()
    , parameters_()
{}

sendCustomRequest::sendCustomRequest(std::string const &method_, std::string const &parameters_)
    : method_(std::move(method_))
    , parameters_(std::move(parameters_))
{}

const int32_t sendCustomRequest::ID;

void sendCustomRequest::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendCustomRequest");
        s.store_field("method", method_);
        s.store_field("parameters", parameters_);
        s.store_class_end();
    }
}

sendInlineQueryResultMessage::sendInlineQueryResultMessage()
    : chat_id_()
    , reply_to_message_id_()
    , disable_notification_()
    , from_background_()
    , query_id_()
    , result_id_()
{}

sendInlineQueryResultMessage::sendInlineQueryResultMessage(std::int64_t chat_id_,
                                                           std::int64_t reply_to_message_id_, bool disable_notification_, bool from_background_,
                                                           std::int64_t query_id_, std::string const &result_id_)
    : chat_id_(chat_id_)
    , reply_to_message_id_(reply_to_message_id_)
    , disable_notification_(disable_notification_)
    , from_background_(from_background_)
    , query_id_(query_id_)
    , result_id_(std::move(result_id_))
{}

const int32_t sendInlineQueryResultMessage::ID;

void sendInlineQueryResultMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendInlineQueryResultMessage");
        s.store_field("chat_id", chat_id_);
        s.store_field("reply_to_message_id", reply_to_message_id_);
        s.store_field("disable_notification", disable_notification_);
        s.store_field("from_background", from_background_);
        s.store_field("query_id", query_id_);
        s.store_field("result_id", result_id_);
        s.store_class_end();
    }
}

sendMessage::sendMessage()
    : chat_id_()
    , reply_to_message_id_()
    , disable_notification_()
    , from_background_()
    , reply_markup_()
    , input_message_content_()
{}

sendMessage::sendMessage(std::int64_t chat_id_, std::int64_t reply_to_message_id_,
                         bool disable_notification_, bool from_background_, object_ptr<ReplyMarkup> &&reply_markup_,
                         object_ptr<InputMessageContent> &&input_message_content_)
    : chat_id_(chat_id_)
    , reply_to_message_id_(reply_to_message_id_)
    , disable_notification_(disable_notification_)
    , from_background_(from_background_)
    , reply_markup_(std::move(reply_markup_))
    , input_message_content_(std::move(input_message_content_))
{}

const int32_t sendMessage::ID;

void sendMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendMessage");
        s.store_field("chat_id", chat_id_);
        s.store_field("reply_to_message_id", reply_to_message_id_);
        s.store_field("disable_notification", disable_notification_);
        s.store_field("from_background", from_background_);
        if (reply_markup_ == nullptr) {
            s.store_field("reply_markup", "null");
        } else {
            reply_markup_->store(s, "reply_markup");
        }
        if (input_message_content_ == nullptr) {
            s.store_field("input_message_content", "null");
        } else {
            input_message_content_->store(s, "input_message_content");
        }
        s.store_class_end();
    }
}

sendMessageAlbum::sendMessageAlbum()
    : chat_id_()
    , reply_to_message_id_()
    , disable_notification_()
    , from_background_()
    , input_message_contents_()
{}

sendMessageAlbum::sendMessageAlbum(std::int64_t chat_id_, std::int64_t reply_to_message_id_,
                                   bool disable_notification_, bool from_background_,
                                   std::vector<object_ptr<InputMessageContent>> &&input_message_contents_)
    : chat_id_(chat_id_)
    , reply_to_message_id_(reply_to_message_id_)
    , disable_notification_(disable_notification_)
    , from_background_(from_background_)
    , input_message_contents_(std::move(input_message_contents_))
{}

const int32_t sendMessageAlbum::ID;

void sendMessageAlbum::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendMessageAlbum");
        s.store_field("chat_id", chat_id_);
        s.store_field("reply_to_message_id", reply_to_message_id_);
        s.store_field("disable_notification", disable_notification_);
        s.store_field("from_background", from_background_);
        {
            const std::vector<object_ptr<InputMessageContent>> &v = input_message_contents_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("input_message_contents", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

sendPaymentForm::sendPaymentForm()
    : chat_id_()
    , message_id_()
    , order_info_id_()
    , shipping_option_id_()
    , credentials_()
{}

sendPaymentForm::sendPaymentForm(std::int64_t chat_id_, std::int64_t message_id_,
                                 std::string const &order_info_id_, std::string const &shipping_option_id_,
                                 object_ptr<InputCredentials> &&credentials_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , order_info_id_(std::move(order_info_id_))
    , shipping_option_id_(std::move(shipping_option_id_))
    , credentials_(std::move(credentials_))
{}

const int32_t sendPaymentForm::ID;

void sendPaymentForm::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "sendPaymentForm");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("order_info_id", order_info_id_);
        s.store_field("shipping_option_id", shipping_option_id_);
        if (credentials_ == nullptr) {
            s.store_field("credentials", "null");
        } else {
            credentials_->store(s, "credentials");
        }
        s.store_class_end();
    }
}

setAccountTtl::setAccountTtl()
    : ttl_()
{}

setAccountTtl::setAccountTtl(object_ptr<accountTtl> &&ttl_)
    : ttl_(std::move(ttl_))
{}

const int32_t setAccountTtl::ID;

void setAccountTtl::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setAccountTtl");
        if (ttl_ == nullptr) {
            s.store_field("ttl", "null");
        } else {
            ttl_->store(s, "ttl");
        }
        s.store_class_end();
    }
}

setAlarm::setAlarm()
    : seconds_()
{}

setAlarm::setAlarm(double seconds_)
    : seconds_(seconds_)
{}

const int32_t setAlarm::ID;

void setAlarm::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setAlarm");
        s.store_field("seconds", seconds_);
        s.store_class_end();
    }
}

setAuthenticationPhoneNumber::setAuthenticationPhoneNumber()
    : phone_number_()
    , allow_flash_call_()
    , is_current_phone_number_()
{}

setAuthenticationPhoneNumber::setAuthenticationPhoneNumber(std::string const &phone_number_,
                                                           bool allow_flash_call_, bool is_current_phone_number_)
    : phone_number_(std::move(phone_number_))
    , allow_flash_call_(allow_flash_call_)
    , is_current_phone_number_(is_current_phone_number_)
{}

const int32_t setAuthenticationPhoneNumber::ID;

void setAuthenticationPhoneNumber::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setAuthenticationPhoneNumber");
        s.store_field("phone_number", phone_number_);
        s.store_field("allow_flash_call", allow_flash_call_);
        s.store_field("is_current_phone_number", is_current_phone_number_);
        s.store_class_end();
    }
}

setBio::setBio()
    : bio_()
{}

setBio::setBio(std::string const &bio_)
    : bio_(std::move(bio_))
{}

const int32_t setBio::ID;

void setBio::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setBio");
        s.store_field("bio", bio_);
        s.store_class_end();
    }
}

setBotUpdatesStatus::setBotUpdatesStatus()
    : pending_update_count_()
    , error_message_()
{}

setBotUpdatesStatus::setBotUpdatesStatus(int32_t pending_update_count_,
                                         std::string const &error_message_)
    : pending_update_count_(pending_update_count_)
    , error_message_(std::move(error_message_))
{}

const int32_t setBotUpdatesStatus::ID;

void setBotUpdatesStatus::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setBotUpdatesStatus");
        s.store_field("pending_update_count", pending_update_count_);
        s.store_field("error_message", error_message_);
        s.store_class_end();
    }
}

setChatClientData::setChatClientData()
    : chat_id_()
    , client_data_()
{}

setChatClientData::setChatClientData(std::int64_t chat_id_, std::string const &client_data_)
    : chat_id_(chat_id_)
    , client_data_(std::move(client_data_))
{}

const int32_t setChatClientData::ID;

void setChatClientData::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setChatClientData");
        s.store_field("chat_id", chat_id_);
        s.store_field("client_data", client_data_);
        s.store_class_end();
    }
}

setChatDraftMessage::setChatDraftMessage()
    : chat_id_()
    , draft_message_()
{}

setChatDraftMessage::setChatDraftMessage(std::int64_t chat_id_,
                                         object_ptr<draftMessage> &&draft_message_)
    : chat_id_(chat_id_)
    , draft_message_(std::move(draft_message_))
{}

const int32_t setChatDraftMessage::ID;

void setChatDraftMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setChatDraftMessage");
        s.store_field("chat_id", chat_id_);
        if (draft_message_ == nullptr) {
            s.store_field("draft_message", "null");
        } else {
            draft_message_->store(s, "draft_message");
        }
        s.store_class_end();
    }
}

setChatMemberStatus::setChatMemberStatus()
    : chat_id_()
    , user_id_()
    , status_()
{}

setChatMemberStatus::setChatMemberStatus(std::int64_t chat_id_, int32_t user_id_,
                                         object_ptr<ChatMemberStatus> &&status_)
    : chat_id_(chat_id_)
    , user_id_(user_id_)
    , status_(std::move(status_))
{}

const int32_t setChatMemberStatus::ID;

void setChatMemberStatus::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setChatMemberStatus");
        s.store_field("chat_id", chat_id_);
        s.store_field("user_id", user_id_);
        if (status_ == nullptr) {
            s.store_field("status", "null");
        } else {
            status_->store(s, "status");
        }
        s.store_class_end();
    }
}

setChatPhoto::setChatPhoto()
    : chat_id_()
    , photo_()
{}

setChatPhoto::setChatPhoto(std::int64_t chat_id_, object_ptr<InputFile> &&photo_)
    : chat_id_(chat_id_)
    , photo_(std::move(photo_))
{}

const int32_t setChatPhoto::ID;

void setChatPhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setChatPhoto");
        s.store_field("chat_id", chat_id_);
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_class_end();
    }
}

setChatTitle::setChatTitle()
    : chat_id_()
    , title_()
{}

setChatTitle::setChatTitle(std::int64_t chat_id_, std::string const &title_)
    : chat_id_(chat_id_)
    , title_(std::move(title_))
{}

const int32_t setChatTitle::ID;

void setChatTitle::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setChatTitle");
        s.store_field("chat_id", chat_id_);
        s.store_field("title", title_);
        s.store_class_end();
    }
}

setDatabaseEncryptionKey::setDatabaseEncryptionKey()
    : new_encryption_key_()
{}

setDatabaseEncryptionKey::setDatabaseEncryptionKey(std::string const &new_encryption_key_)
    : new_encryption_key_(std::move(new_encryption_key_))
{}

const int32_t setDatabaseEncryptionKey::ID;

void setDatabaseEncryptionKey::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setDatabaseEncryptionKey");
        s.store_bytes_field("new_encryption_key", new_encryption_key_);
        s.store_class_end();
    }
}

setFileGenerationProgress::setFileGenerationProgress()
    : generation_id_()
    , expected_size_()
    , local_prefix_size_()
{}

setFileGenerationProgress::setFileGenerationProgress(std::int64_t generation_id_,
                                                     int32_t expected_size_, int32_t local_prefix_size_)
    : generation_id_(generation_id_)
    , expected_size_(expected_size_)
    , local_prefix_size_(local_prefix_size_)
{}

const int32_t setFileGenerationProgress::ID;

void setFileGenerationProgress::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setFileGenerationProgress");
        s.store_field("generation_id", generation_id_);
        s.store_field("expected_size", expected_size_);
        s.store_field("local_prefix_size", local_prefix_size_);
        s.store_class_end();
    }
}

setGameScore::setGameScore()
    : chat_id_()
    , message_id_()
    , edit_message_()
    , user_id_()
    , score_()
    , force_()
{}

setGameScore::setGameScore(std::int64_t chat_id_, std::int64_t message_id_, bool edit_message_,
                           int32_t user_id_, int32_t score_, bool force_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , edit_message_(edit_message_)
    , user_id_(user_id_)
    , score_(score_)
    , force_(force_)
{}

const int32_t setGameScore::ID;

void setGameScore::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setGameScore");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        s.store_field("edit_message", edit_message_);
        s.store_field("user_id", user_id_);
        s.store_field("score", score_);
        s.store_field("force", force_);
        s.store_class_end();
    }
}

setInlineGameScore::setInlineGameScore()
    : inline_message_id_()
    , edit_message_()
    , user_id_()
    , score_()
    , force_()
{}

setInlineGameScore::setInlineGameScore(std::string const &inline_message_id_, bool edit_message_,
                                       int32_t user_id_, int32_t score_, bool force_)
    : inline_message_id_(std::move(inline_message_id_))
    , edit_message_(edit_message_)
    , user_id_(user_id_)
    , score_(score_)
    , force_(force_)
{}

const int32_t setInlineGameScore::ID;

void setInlineGameScore::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setInlineGameScore");
        s.store_field("inline_message_id", inline_message_id_);
        s.store_field("edit_message", edit_message_);
        s.store_field("user_id", user_id_);
        s.store_field("score", score_);
        s.store_field("force", force_);
        s.store_class_end();
    }
}

setName::setName()
    : first_name_()
    , last_name_()
{}

setName::setName(std::string const &first_name_, std::string const &last_name_)
    : first_name_(std::move(first_name_))
    , last_name_(std::move(last_name_))
{}

const int32_t setName::ID;

void setName::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setName");
        s.store_field("first_name", first_name_);
        s.store_field("last_name", last_name_);
        s.store_class_end();
    }
}

setNetworkType::setNetworkType()
    : type_()
{}

setNetworkType::setNetworkType(object_ptr<NetworkType> &&type_)
    : type_(std::move(type_))
{}

const int32_t setNetworkType::ID;

void setNetworkType::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setNetworkType");
        if (type_ == nullptr) {
            s.store_field("type", "null");
        } else {
            type_->store(s, "type");
        }
        s.store_class_end();
    }
}

setNotificationSettings::setNotificationSettings()
    : scope_()
    , notification_settings_()
{}

setNotificationSettings::setNotificationSettings(object_ptr<NotificationSettingsScope> &&scope_,
                                                 object_ptr<notificationSettings> &&notification_settings_)
    : scope_(std::move(scope_))
    , notification_settings_(std::move(notification_settings_))
{}

const int32_t setNotificationSettings::ID;

void setNotificationSettings::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setNotificationSettings");
        if (scope_ == nullptr) {
            s.store_field("scope", "null");
        } else {
            scope_->store(s, "scope");
        }
        if (notification_settings_ == nullptr) {
            s.store_field("notification_settings", "null");
        } else {
            notification_settings_->store(s, "notification_settings");
        }
        s.store_class_end();
    }
}

setOption::setOption()
    : name_()
    , value_()
{}

setOption::setOption(std::string const &name_, object_ptr<OptionValue> &&value_)
    : name_(std::move(name_))
    , value_(std::move(value_))
{}

const int32_t setOption::ID;

void setOption::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setOption");
        s.store_field("name", name_);
        if (value_ == nullptr) {
            s.store_field("value", "null");
        } else {
            value_->store(s, "value");
        }
        s.store_class_end();
    }
}

setPassword::setPassword()
    : old_password_()
    , new_password_()
    , new_hint_()
    , set_recovery_email_address_()
    , new_recovery_email_address_()
{}

setPassword::setPassword(std::string const &old_password_, std::string const &new_password_,
                         std::string const &new_hint_, bool set_recovery_email_address_,
                         std::string const &new_recovery_email_address_)
    : old_password_(std::move(old_password_))
    , new_password_(std::move(new_password_))
    , new_hint_(std::move(new_hint_))
    , set_recovery_email_address_(set_recovery_email_address_)
    , new_recovery_email_address_(std::move(new_recovery_email_address_))
{}

const int32_t setPassword::ID;

void setPassword::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setPassword");
        s.store_field("old_password", old_password_);
        s.store_field("new_password", new_password_);
        s.store_field("new_hint", new_hint_);
        s.store_field("set_recovery_email_address", set_recovery_email_address_);
        s.store_field("new_recovery_email_address", new_recovery_email_address_);
        s.store_class_end();
    }
}

setPinnedChats::setPinnedChats()
    : chat_ids_()
{}

setPinnedChats::setPinnedChats(std::vector<std::int64_t> &&chat_ids_)
    : chat_ids_(std::move(chat_ids_))
{}

const int32_t setPinnedChats::ID;

void setPinnedChats::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setPinnedChats");
        {
            const std::vector<std::int64_t> &v = chat_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("chat_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

setProfilePhoto::setProfilePhoto()
    : photo_()
{}

setProfilePhoto::setProfilePhoto(object_ptr<InputFile> &&photo_)
    : photo_(std::move(photo_))
{}

const int32_t setProfilePhoto::ID;

void setProfilePhoto::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setProfilePhoto");
        if (photo_ == nullptr) {
            s.store_field("photo", "null");
        } else {
            photo_->store(s, "photo");
        }
        s.store_class_end();
    }
}

setProxy::setProxy()
    : proxy_()
{}

setProxy::setProxy(object_ptr<Proxy> &&proxy_)
    : proxy_(std::move(proxy_))
{}

const int32_t setProxy::ID;

void setProxy::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setProxy");
        if (proxy_ == nullptr) {
            s.store_field("proxy", "null");
        } else {
            proxy_->store(s, "proxy");
        }
        s.store_class_end();
    }
}

setRecoveryEmailAddress::setRecoveryEmailAddress()
    : password_()
    , new_recovery_email_address_()
{}

setRecoveryEmailAddress::setRecoveryEmailAddress(std::string const &password_,
                                                 std::string const &new_recovery_email_address_)
    : password_(std::move(password_))
    , new_recovery_email_address_(std::move(new_recovery_email_address_))
{}

const int32_t setRecoveryEmailAddress::ID;

void setRecoveryEmailAddress::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setRecoveryEmailAddress");
        s.store_field("password", password_);
        s.store_field("new_recovery_email_address", new_recovery_email_address_);
        s.store_class_end();
    }
}

setStickerPositionInSet::setStickerPositionInSet()
    : sticker_()
    , position_()
{}

setStickerPositionInSet::setStickerPositionInSet(object_ptr<InputFile> &&sticker_,
                                                 int32_t position_)
    : sticker_(std::move(sticker_))
    , position_(position_)
{}

const int32_t setStickerPositionInSet::ID;

void setStickerPositionInSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setStickerPositionInSet");
        if (sticker_ == nullptr) {
            s.store_field("sticker", "null");
        } else {
            sticker_->store(s, "sticker");
        }
        s.store_field("position", position_);
        s.store_class_end();
    }
}

setSupergroupDescription::setSupergroupDescription()
    : supergroup_id_()
    , description_()
{}

setSupergroupDescription::setSupergroupDescription(int32_t supergroup_id_,
                                                   std::string const &description_)
    : supergroup_id_(supergroup_id_)
    , description_(std::move(description_))
{}

const int32_t setSupergroupDescription::ID;

void setSupergroupDescription::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setSupergroupDescription");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("description", description_);
        s.store_class_end();
    }
}

setSupergroupStickerSet::setSupergroupStickerSet()
    : supergroup_id_()
    , sticker_set_id_()
{}

setSupergroupStickerSet::setSupergroupStickerSet(int32_t supergroup_id_,
                                                 std::int64_t sticker_set_id_)
    : supergroup_id_(supergroup_id_)
    , sticker_set_id_(sticker_set_id_)
{}

const int32_t setSupergroupStickerSet::ID;

void setSupergroupStickerSet::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setSupergroupStickerSet");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("sticker_set_id", sticker_set_id_);
        s.store_class_end();
    }
}

setSupergroupUsername::setSupergroupUsername()
    : supergroup_id_()
    , username_()
{}

setSupergroupUsername::setSupergroupUsername(int32_t supergroup_id_,
                                             std::string const &username_)
    : supergroup_id_(supergroup_id_)
    , username_(std::move(username_))
{}

const int32_t setSupergroupUsername::ID;

void setSupergroupUsername::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setSupergroupUsername");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("username", username_);
        s.store_class_end();
    }
}

setTdlibParameters::setTdlibParameters()
    : parameters_()
{}

setTdlibParameters::setTdlibParameters(object_ptr<tdlibParameters> &&parameters_)
    : parameters_(std::move(parameters_))
{}

const int32_t setTdlibParameters::ID;

void setTdlibParameters::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setTdlibParameters");
        if (parameters_ == nullptr) {
            s.store_field("parameters", "null");
        } else {
            parameters_->store(s, "parameters");
        }
        s.store_class_end();
    }
}

setUserPrivacySettingRules::setUserPrivacySettingRules()
    : setting_()
    , rules_()
{}

setUserPrivacySettingRules::setUserPrivacySettingRules(object_ptr<UserPrivacySetting> &&setting_,
                                                       object_ptr<userPrivacySettingRules> &&rules_)
    : setting_(std::move(setting_))
    , rules_(std::move(rules_))
{}

const int32_t setUserPrivacySettingRules::ID;

void setUserPrivacySettingRules::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setUserPrivacySettingRules");
        if (setting_ == nullptr) {
            s.store_field("setting", "null");
        } else {
            setting_->store(s, "setting");
        }
        if (rules_ == nullptr) {
            s.store_field("rules", "null");
        } else {
            rules_->store(s, "rules");
        }
        s.store_class_end();
    }
}

setUsername::setUsername()
    : username_()
{}

setUsername::setUsername(std::string const &username_)
    : username_(std::move(username_))
{}

const int32_t setUsername::ID;

void setUsername::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "setUsername");
        s.store_field("username", username_);
        s.store_class_end();
    }
}

terminateAllOtherSessions::terminateAllOtherSessions()
{
}

const int32_t terminateAllOtherSessions::ID;

void terminateAllOtherSessions::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "terminateAllOtherSessions");
        s.store_class_end();
    }
}

terminateSession::terminateSession()
    : session_id_()
{}

terminateSession::terminateSession(std::int64_t session_id_)
    : session_id_(session_id_)
{}

const int32_t terminateSession::ID;

void terminateSession::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "terminateSession");
        s.store_field("session_id", session_id_);
        s.store_class_end();
    }
}

testCallBytes::testCallBytes()
    : x_()
{}

testCallBytes::testCallBytes(std::string const &x_)
    : x_(std::move(x_))
{}

const int32_t testCallBytes::ID;

void testCallBytes::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testCallBytes");
        s.store_bytes_field("x", x_);
        s.store_class_end();
    }
}

testCallEmpty::testCallEmpty()
{
}

const int32_t testCallEmpty::ID;

void testCallEmpty::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testCallEmpty");
        s.store_class_end();
    }
}

testCallString::testCallString()
    : x_()
{}

testCallString::testCallString(std::string const &x_)
    : x_(std::move(x_))
{}

const int32_t testCallString::ID;

void testCallString::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testCallString");
        s.store_field("x", x_);
        s.store_class_end();
    }
}

testCallVectorInt::testCallVectorInt()
    : x_()
{}

testCallVectorInt::testCallVectorInt(std::vector<int32_t> &&x_)
    : x_(std::move(x_))
{}

const int32_t testCallVectorInt::ID;

void testCallVectorInt::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testCallVectorInt");
        {
            const std::vector<int32_t> &v = x_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("x", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

testCallVectorIntObject::testCallVectorIntObject()
    : x_()
{}

testCallVectorIntObject::testCallVectorIntObject(std::vector<object_ptr<testInt>> &&x_)
    : x_(std::move(x_))
{}

const int32_t testCallVectorIntObject::ID;

void testCallVectorIntObject::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testCallVectorIntObject");
        {
            const std::vector<object_ptr<testInt>> &v = x_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("x", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

testCallVectorString::testCallVectorString()
    : x_()
{}

testCallVectorString::testCallVectorString(std::vector<std::string> &&x_)
    : x_(std::move(x_))
{}

const int32_t testCallVectorString::ID;

void testCallVectorString::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testCallVectorString");
        {
            const std::vector<std::string> &v = x_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("x", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

testCallVectorStringObject::testCallVectorStringObject()
    : x_()
{}

testCallVectorStringObject::testCallVectorStringObject(std::vector<object_ptr<testString>> &&x_)
    : x_(std::move(x_))
{}

const int32_t testCallVectorStringObject::ID;

void testCallVectorStringObject::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testCallVectorStringObject");
        {
            const std::vector<object_ptr<testString>> &v = x_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("x", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                if (v[i] == nullptr) {
                    s.store_field("", "null");
                } else {
                    v[i]->store(s, "");
                }
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}

testGetDifference::testGetDifference()
{
}

const int32_t testGetDifference::ID;

void testGetDifference::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testGetDifference");
        s.store_class_end();
    }
}

testNetwork::testNetwork()
{
}

const int32_t testNetwork::ID;

void testNetwork::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testNetwork");
        s.store_class_end();
    }
}

testSquareInt::testSquareInt()
    : x_()
{}

testSquareInt::testSquareInt(int32_t x_)
    : x_(x_)
{}

const int32_t testSquareInt::ID;

void testSquareInt::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testSquareInt");
        s.store_field("x", x_);
        s.store_class_end();
    }
}

testUseError::testUseError()
{
}

const int32_t testUseError::ID;

void testUseError::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testUseError");
        s.store_class_end();
    }
}

testUseUpdate::testUseUpdate()
{
}

const int32_t testUseUpdate::ID;

void testUseUpdate::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "testUseUpdate");
        s.store_class_end();
    }
}

toggleBasicGroupAdministrators::toggleBasicGroupAdministrators()
    : basic_group_id_()
    , everyone_is_administrator_()
{}

toggleBasicGroupAdministrators::toggleBasicGroupAdministrators(int32_t basic_group_id_,
                                                               bool everyone_is_administrator_)
    : basic_group_id_(basic_group_id_)
    , everyone_is_administrator_(everyone_is_administrator_)
{}

const int32_t toggleBasicGroupAdministrators::ID;

void toggleBasicGroupAdministrators::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "toggleBasicGroupAdministrators");
        s.store_field("basic_group_id", basic_group_id_);
        s.store_field("everyone_is_administrator", everyone_is_administrator_);
        s.store_class_end();
    }
}

toggleChatIsPinned::toggleChatIsPinned()
    : chat_id_()
    , is_pinned_()
{}

toggleChatIsPinned::toggleChatIsPinned(std::int64_t chat_id_, bool is_pinned_)
    : chat_id_(chat_id_)
    , is_pinned_(is_pinned_)
{}

const int32_t toggleChatIsPinned::ID;

void toggleChatIsPinned::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "toggleChatIsPinned");
        s.store_field("chat_id", chat_id_);
        s.store_field("is_pinned", is_pinned_);
        s.store_class_end();
    }
}

toggleSupergroupInvites::toggleSupergroupInvites()
    : supergroup_id_()
    , anyone_can_invite_()
{}

toggleSupergroupInvites::toggleSupergroupInvites(int32_t supergroup_id_,
                                                 bool anyone_can_invite_)
    : supergroup_id_(supergroup_id_)
    , anyone_can_invite_(anyone_can_invite_)
{}

const int32_t toggleSupergroupInvites::ID;

void toggleSupergroupInvites::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "toggleSupergroupInvites");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("anyone_can_invite", anyone_can_invite_);
        s.store_class_end();
    }
}

toggleSupergroupIsAllHistoryAvailable::toggleSupergroupIsAllHistoryAvailable()
    : supergroup_id_()
    , is_all_history_available_()
{}

toggleSupergroupIsAllHistoryAvailable::toggleSupergroupIsAllHistoryAvailable(
    int32_t supergroup_id_, bool is_all_history_available_)
    : supergroup_id_(supergroup_id_)
    , is_all_history_available_(is_all_history_available_)
{}

const int32_t toggleSupergroupIsAllHistoryAvailable::ID;

void toggleSupergroupIsAllHistoryAvailable::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "toggleSupergroupIsAllHistoryAvailable");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("is_all_history_available", is_all_history_available_);
        s.store_class_end();
    }
}

toggleSupergroupSignMessages::toggleSupergroupSignMessages()
    : supergroup_id_()
    , sign_messages_()
{}

toggleSupergroupSignMessages::toggleSupergroupSignMessages(int32_t supergroup_id_,
                                                           bool sign_messages_)
    : supergroup_id_(supergroup_id_)
    , sign_messages_(sign_messages_)
{}

const int32_t toggleSupergroupSignMessages::ID;

void toggleSupergroupSignMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "toggleSupergroupSignMessages");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_field("sign_messages", sign_messages_);
        s.store_class_end();
    }
}

unblockUser::unblockUser()
    : user_id_()
{}

unblockUser::unblockUser(int32_t user_id_)
    : user_id_(user_id_)
{}

const int32_t unblockUser::ID;

void unblockUser::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "unblockUser");
        s.store_field("user_id", user_id_);
        s.store_class_end();
    }
}

unpinSupergroupMessage::unpinSupergroupMessage()
    : supergroup_id_()
{}

unpinSupergroupMessage::unpinSupergroupMessage(int32_t supergroup_id_)
    : supergroup_id_(supergroup_id_)
{}

const int32_t unpinSupergroupMessage::ID;

void unpinSupergroupMessage::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "unpinSupergroupMessage");
        s.store_field("supergroup_id", supergroup_id_);
        s.store_class_end();
    }
}

upgradeBasicGroupChatToSupergroupChat::upgradeBasicGroupChatToSupergroupChat()
    : chat_id_()
{}

upgradeBasicGroupChatToSupergroupChat::upgradeBasicGroupChatToSupergroupChat(std::int64_t chat_id_)
    : chat_id_(chat_id_)
{}

const int32_t upgradeBasicGroupChatToSupergroupChat::ID;

void upgradeBasicGroupChatToSupergroupChat::store(TlStorerToString &s,
                                                  const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "upgradeBasicGroupChatToSupergroupChat");
        s.store_field("chat_id", chat_id_);
        s.store_class_end();
    }
}

uploadFile::uploadFile()
    : file_()
    , file_type_()
    , priority_()
{}

uploadFile::uploadFile(object_ptr<InputFile> &&file_, object_ptr<FileType> &&file_type_,
                       int32_t priority_)
    : file_(std::move(file_))
    , file_type_(std::move(file_type_))
    , priority_(priority_)
{}

const int32_t uploadFile::ID;

void uploadFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "uploadFile");
        if (file_ == nullptr) {
            s.store_field("file", "null");
        } else {
            file_->store(s, "file");
        }
        if (file_type_ == nullptr) {
            s.store_field("file_type", "null");
        } else {
            file_type_->store(s, "file_type");
        }
        s.store_field("priority", priority_);
        s.store_class_end();
    }
}

uploadStickerFile::uploadStickerFile()
    : user_id_()
    , png_sticker_()
{}

uploadStickerFile::uploadStickerFile(int32_t user_id_, object_ptr<InputFile> &&png_sticker_)
    : user_id_(user_id_)
    , png_sticker_(std::move(png_sticker_))
{}

const int32_t uploadStickerFile::ID;

void uploadStickerFile::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "uploadStickerFile");
        s.store_field("user_id", user_id_);
        if (png_sticker_ == nullptr) {
            s.store_field("png_sticker", "null");
        } else {
            png_sticker_->store(s, "png_sticker");
        }
        s.store_class_end();
    }
}

validateOrderInfo::validateOrderInfo()
    : chat_id_()
    , message_id_()
    , order_info_()
    , allow_save_()
{}

validateOrderInfo::validateOrderInfo(std::int64_t chat_id_, std::int64_t message_id_,
                                     object_ptr<orderInfo> &&order_info_, bool allow_save_)
    : chat_id_(chat_id_)
    , message_id_(message_id_)
    , order_info_(std::move(order_info_))
    , allow_save_(allow_save_)
{}

const int32_t validateOrderInfo::ID;

void validateOrderInfo::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "validateOrderInfo");
        s.store_field("chat_id", chat_id_);
        s.store_field("message_id", message_id_);
        if (order_info_ == nullptr) {
            s.store_field("order_info", "null");
        } else {
            order_info_->store(s, "order_info");
        }
        s.store_field("allow_save", allow_save_);
        s.store_class_end();
    }
}

viewMessages::viewMessages()
    : chat_id_()
    , message_ids_()
    , force_read_()
{}

viewMessages::viewMessages(std::int64_t chat_id_, std::vector<std::int64_t> &&message_ids_,
                           bool force_read_)
    : chat_id_(chat_id_)
    , message_ids_(std::move(message_ids_))
    , force_read_(force_read_)
{}

const int32_t viewMessages::ID;

void viewMessages::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "viewMessages");
        s.store_field("chat_id", chat_id_);
        {
            const std::vector<std::int64_t> &v = message_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("message_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_field("force_read", force_read_);
        s.store_class_end();
    }
}

viewTrendingStickerSets::viewTrendingStickerSets()
    : sticker_set_ids_()
{}

viewTrendingStickerSets::viewTrendingStickerSets(std::vector<std::int64_t> &&sticker_set_ids_)
    : sticker_set_ids_(std::move(sticker_set_ids_))
{}

const int32_t viewTrendingStickerSets::ID;

void viewTrendingStickerSets::store(TlStorerToString &s, const char *field_name) const
{
    if (!LOG_IS_STRIPPED(ERROR)) {
        s.store_class_begin(field_name, "viewTrendingStickerSets");
        {
            const std::vector<std::int64_t> &v = sticker_set_ids_;
            const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size());
            const auto vector_name = "vector[" + std::to_string(multiplicity) + "]";
            s.store_class_begin("sticker_set_ids", vector_name.c_str());
            for (std::uint32_t i = 0; i < multiplicity; i++) {
                s.store_field("", v[i]);
            }
            s.store_class_end();
        }
        s.store_class_end();
    }
}
}  // namespace tdlib
