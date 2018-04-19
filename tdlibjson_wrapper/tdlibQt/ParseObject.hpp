#ifndef PARSEOBJECT_HPP
#define PARSEOBJECT_HPP

#include <QObject>
#include <QJsonObject>
#include <QVariantList>

#include "tdlibQt/include/TdlibNamespace.hpp"
#include "tdlibQt/items/TdApi.hpp"
#include "FileWriter.hpp"

namespace tdlibQt {
class ParseObject : public QObject
{
    Q_OBJECT
public:
    explicit ParseObject(QObject *parent = 0);

    QMap<int, QString> users_;
    std::map<qint64, QString> chat_title_;
    FileWriter jsonWriter;

    QString getUserName(int userId);
    inline static qint64 getInt64(const QJsonValue &value)
    {
        switch (value.type()) {
        case QJsonValue::Double:
            return value.toDouble();
        case QJsonValue::String:
            return value.toString().toLongLong();
        default:
            return -1;
        }
    }
    static QSharedPointer<message> parseMessage(const QJsonObject &messageObject);
    static QSharedPointer<ChatType> parseType(const QJsonObject &typeObject);

    static QSharedPointer<MessageContent> parseMessageContent(const QJsonObject &messageContentObject);
    static QSharedPointer<messageText> parseMessageText(const QJsonObject &messageTextObject);
    static QSharedPointer<messageSticker> parseMessageSticker(const QJsonObject &messageStikerObject);
    static QSharedPointer<sticker> parseSticker(const QJsonObject &stikerObject);

    static QSharedPointer<maskPosition> parseMaskPosition(const QJsonObject &maskPositionObject);
    static QSharedPointer<notificationSettings> parseNotificationSettings(
        const QJsonObject &notificationSettingsObject);
    static QSharedPointer<messagePhoto> parseMessagePhoto(const QJsonObject &messagePhotoObject);
    static QSharedPointer<photo> parsePhoto(const QJsonObject &photoObject);
    static QSharedPointer<photoSize> parsePhotoSize(const QJsonObject &photoSizeObject);

    static QSharedPointer<formattedText> parseFormattedTextContent(const QJsonObject
                                                                   &formattedTextObject);
    static QSharedPointer<chatPhoto> parseChatPhoto(const QJsonObject &chatPhotoObject);
    static QSharedPointer<file> parseFile(const QJsonObject &fileObject);
    static QSharedPointer<updateUserChatAction> parseChatAction(const QJsonObject &chatActionObject);
    enum class UpdateState {
        updateAuthorizationState,
        updateBasicGroup,
        updateBasicGroupFullInfo,
        updateCall,
        updateChatDraftMessage,
        updateChatIsPinned,
        updateChatLastMessage,
        updateChatOrder,
        updateChatPhoto,
        updateChatReadInbox,
        updateChatReadOutbox,
        updateChatReplyMarkup,
        updateChatTitle,
        updateChatUnreadMentionCount,
        updateConnectionState,
        updateDeleteMessages,
        updateFavoriteStickers,
        updateFile,
        updateFileGenerationStart,
        updateFileGenerationStop,
        updateInstalledStickerSets,
        updateMessageContent,
        updateMessageContentOpened,
        updateMessageEdited,
        updateMessageMentionRead,
        updateMessageSendAcknowledged,
        updateMessageSendFailed,
        updateMessageSendSucceeded,
        updateMessageViews,
        updateNewCallbackQuery,
        updateNewChat,
        updateNewChosenInlineResult,
        updateNewCustomEvent,
        updateNewCustomQuery,
        updateNewInlineCallbackQuery,
        updateNewInlineQuery,
        updateNewPreCheckoutQuery,
        updateNewShippingQuery,
        updateNotificationSettings,
        updateOption,
        updateRecentStickers,
        updateSavedAnimations,
        updateSecretChat,
        updateServiceNotification,
        updateSupergroup,
        updateSupergroupFullInfo,
        updateTrendingStickerSets,
        updateUser,
        updateUserChatAction,
        updateUserFullInfo,
        updateUserPrivacySettingRules,
        updateUserStatus,
        updateNewMessage
    };
    QString getFirstName(int userId);
    static QSharedPointer<messageAnimation> parseMessageAnimation(const QJsonObject
                                                                  &messageAnimationObject);
    static QSharedPointer<animation> parseAnimation(const QJsonObject &animationObject);
    static QSharedPointer<MessageForwardInfo> parseForwardInfo(const QJsonObject &forwardObject);
signals:
    void updateAuthorizationState(Enums::AuthorizationState &authorizationState);
    void updateConnectionState(Enums::ConnectionState &connectionState);

    void newAuthorizationState(const QSharedPointer<AuthorizationState> &authorizationState);

    void updateNewMessage(const QVariantMap &msg);
    void updateFile(const QJsonObject &fileObject);
    void meReceived(const QJsonObject &meObject);
    void updateChatOrder(const QJsonObject &chatOrderObject);
    void updateChatLastMessage(const QJsonObject &chatLastMessage);
    void updateChatReadInbox(const QJsonObject &chatReadInbox);
    void updateChatReadOutbox(const QJsonObject &chatReadOutbox);
    void updateChatAction(const QJsonObject &chatAction);
    void updateChatMention(const QJsonObject &chatAction);
    void updateMentionRead(const QJsonObject &messageMentionReadObject);
    void chatIds(const QVariantList &ids);
    void getChat(const qint64 id);
    void newChatReceived(const QJsonObject &chatItem);
    void newMessages(const QJsonObject &messageItem);
    void newMessageFromUpdate(const QJsonObject &messageItem);
    void updateTotalCount(int totalCount);
    void proxyReceived(const QJsonObject &proxyObject);

public slots:
    void parseResponse(const QByteArray &json);
};
}//namespace tdlibQt
#endif // PARSEOBJECT_HPP
