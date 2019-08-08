#include "ChatShareModel.hpp"
#include "../tdlibjson_wrapper/tdlibQt/ParseObject.hpp"
#include <QDBusPendingReply>
#include <QDBusPendingCallWatcher>
#include <QDBusInterface>
#include <QDebug>
static const QString c_dbusServiceName = QStringLiteral("org.blacksailer.depecher");
static const QString c_dbusObjectPath = QStringLiteral("/org/blacksailer/depecher/share");
static const QString c_dbusInterface = QStringLiteral("org.blacksailer.depecher.share");
static const QString c_dbusMethod = QStringLiteral("getChatList");
static const QString c_extraName = QStringLiteral("dbus");

ChatShareModel::ChatShareModel(QObject *parent) :
    QAbstractListModel(parent)
{
    remoteAppIface = new QDBusInterface(QString(),
                                        c_dbusObjectPath,
                                        c_dbusInterface,
                                        QDBusConnection::connectToPeer("unix:path=/tmp/depecher", "depecherBus"),
                                        this);
}

ChatShareModel::~ChatShareModel()
{
}

QVariant ChatShareModel::answer() const
{
    return m_answer;
}

void ChatShareModel::setAnswer(QVariant answer)
{
    if (m_answer == answer)
        return;

    m_answer = answer;
    emit answerChanged(m_answer);
}

void ChatShareModel::addItems(QDBusPendingCallWatcher *call)
{
    QDBusPendingReply<QList<QVariant>> reply = *call;
    if (reply.isError())
        qDebug() << reply.error();
    else {
        beginInsertRows(QModelIndex(), m_chats.size(), m_chats.size() +  reply.argumentAt<0>().size() - 1);
        for (int i = 0; i < reply.argumentAt<0>().size(); i ++) {
            auto tmp2 = qdbus_cast<QVariantMap>(
                            reply.argumentAt<0>()[i].value<QDBusArgument>());
            auto tmp =  parseDBusArgument(tmp2);
            auto chat1 = tdlibQt::ParseObject::parseChat(QJsonObject::fromVariantMap(tmp));
            m_chats.append(chat1);
        }
        endInsertRows();
    }
    call->deleteLater();
    m_fetchPending = false;
}

QVariantMap ChatShareModel::parseDBusArgument(QMap<QString, QVariant> value)
{
    foreach (QString key, value.keys()) {
        if (QString(value[key].typeName()) == "QDBusArgument") {
//            qDebug() << key << value[key].value<QDBusArgument>().currentType() << value[key].typeName();
            if (value[key].value<QDBusArgument>().currentType() != QDBusArgument::ArrayType)
                value[key] = parseDBusArgument(qdbus_cast<QVariantMap>(value[key].value<QDBusArgument>()));
            else {
                value[key] = parseDBusArgumentArray(qdbus_cast<QVariantList>(value[key].value<QDBusArgument>()));
            }
        }
    }
    return value;
}

QVariantList ChatShareModel::parseDBusArgumentArray(QVariantList srcArray)
{
    QVariantList result;
    foreach (QVariant element, srcArray) {
        if (QString(element.typeName()) == "QDBusArgument") {
//            qDebug() << "Array" << element.value<QDBusArgument>().currentType() << element.typeName();
            result.append(parseDBusArgument(qdbus_cast<QVariantMap>(element.value<QDBusArgument>())));
        } else
//            qDebug() << QString(element.typeName());
            result.append(element);
    }
    return result;
}

int ChatShareModel::rowCount(const QModelIndex &parent) const
{
    return m_chats.size();
}

QVariant ChatShareModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    int rowIndex = index.row();
    switch (role) {
    case ID: //int64
        return QString::number(m_chats[rowIndex]->id_);
    case LAST_MESSAGE_ID: //int64
        return QString::number(m_chats[rowIndex]->last_message_->id_);
    case LAST_MESSAGE_INBOX_ID: //int64
        return QString::number(m_chats[rowIndex]->last_read_inbox_message_id_);
    case LAST_MESSAGE_OUTBOX_ID: //int64
        return QString::number(m_chats[rowIndex]->last_read_outbox_message_id_);

    case IS_PINNED:
        return m_chats[rowIndex]->is_pinned_;
    case IS_SPONSORED:
        return m_chats[rowIndex]->is_sponsored_;
    case IS_MARKED_UNREAD:
        return m_chats[rowIndex]->is_marked_as_unread_;
    case TYPE:
        switch (m_chats[rowIndex]->type_->get_id()) {
        case tdlibQt::chatTypeBasicGroup::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::BasicGroup);
            return resultType;
        }
        case tdlibQt::chatTypePrivate::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Private);
            return resultType;
        }
        case tdlibQt::chatTypeSecret::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Secret);
            return resultType;
        }
        case tdlibQt::chatTypeSupergroup::ID: {
            tdlibQt::chatTypeSupergroup *superGroupMetaInfo   = static_cast<tdlibQt::chatTypeSupergroup *>
                    (m_chats[rowIndex]->type_.data());
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Supergroup);
            resultType["is_channel"] = superGroupMetaInfo->is_channel_;
            resultType["supergroup_id"] = superGroupMetaInfo->supergroup_id_;
            return resultType;
        }
        }
    case TITLE:
        return QString::fromStdString(m_chats[rowIndex]->title_);
    case UNREAD_COUNT:
        return m_chats[rowIndex]->unread_count_;
    case UNREAD_MENTION_COUNT:
        return m_chats[rowIndex]->unread_mention_count_;
//    case CHAT_ACTION:
//        if (chatActionMap.contains(m_chats[rowIndex]->id_)) {
//            if (chatActionMap.count(m_chats[rowIndex]->id_) > 1)
//                return  QString::number(chatActionMap.count(m_chats[rowIndex]->id_)) + " are typing";
//            auto chatAction = chatActionMap.value(m_chats[rowIndex]->id_);
//            return tdlibJson->parseObject->getFirstName(chatAction->user_id_) + " is typing";
//        }
        return QVariant();
    case LAST_MESSAGE:
        if (m_chats[rowIndex]->last_message_.data() != nullptr) {
            //Return content
            if (m_chats[rowIndex]->last_message_->content_.data() != nullptr) {
                if (m_chats[rowIndex]->last_message_->content_->get_id() == tdlibQt::messageText::ID) {
                    auto contentPtr = static_cast<tdlibQt::messageText *>
                                      (m_chats[rowIndex]->last_message_->content_.data());
                    if (contentPtr->text_.data() != nullptr) {
                        return QString::fromStdString(contentPtr->text_->text_);
                    }
                }

                return tdlibQt::ParseObject::messageTypeToString(m_chats[rowIndex]->last_message_->content_->get_id());

                return QVariant();
            }
        }
//    case LAST_MESSAGE_AUTHOR:
//        return tdlibJson->parseObject->getFirstName(
//                   m_chats[rowIndex]->last_message_->sender_user_id_);
    case DATE:
        if (m_chats[rowIndex]->last_message_.data() != nullptr) {
            return m_chats[rowIndex]->last_message_->date_;
        }
    case MUTE_FOR:
        if (m_chats[rowIndex]->notification_settings_.data() != nullptr) {
            return m_chats[rowIndex]->notification_settings_->mute_for_;
        }

    case PHOTO:
        if (m_chats[rowIndex]->photo_.data() != nullptr) {
            if (m_chats[rowIndex]->photo_->small_.data() != nullptr)
                return QString::fromStdString(m_chats[rowIndex]->photo_->small_->local_->path_);
        }
        return QVariant();
    case SENDING_STATE: {
        if (m_chats[rowIndex]->last_message_->sending_state_.data()) {
            if (m_chats[rowIndex]->last_message_->sending_state_->get_id() == tdlibQt::messageSendingStatePending::ID)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Pending);
            if (m_chats[rowIndex]->last_message_->sending_state_->get_id() == tdlibQt::messageSendingStateFailed::ID)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Failed);
        }
        if (m_chats[rowIndex]->last_message_->is_outgoing_) {
            if (m_chats[rowIndex]->last_message_->id_ <= m_chats[rowIndex]->last_read_outbox_message_id_)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Read);
            else
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Not_Read);
        } else {
            if (m_chats[rowIndex]->last_message_->id_ <= m_chats[rowIndex]->last_read_inbox_message_id_)
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Read);
            else
                return QVariant::fromValue(tdlibQt::Enums::MessageState::Sending_Not_Read);
        }

    }

    default:
        return QVariant();
    }

    return QVariant();
}

QHash<int, QByteArray> ChatShareModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ID] = "id";
    roles[TYPE] = "type";
    roles[PHOTO] = "photo";
    roles[ORDER] = "order";
    roles[DATE] = "date";
    roles[MUTE_FOR] = "mute_for";
    roles[TITLE] = "title";
    roles[CHAT_ACTION] = "action";
    roles[LAST_MESSAGE] = "last_message";
    roles[LAST_MESSAGE_ID] = "last_message_id";

    roles[LAST_MESSAGE_AUTHOR] = "last_message_author";
    roles[LAST_MESSAGE_INBOX_ID] = "last_message_inbox_id";
    roles[LAST_MESSAGE_OUTBOX_ID] = "last_message_outbox_id";
    roles[IS_PINNED] = "is_pinned";
    roles[IS_SPONSORED] = "is_sponsored";
    roles[IS_MARKED_UNREAD] = "is_marked_unread";
    roles[UNREAD_COUNT] = "unread_count";
    roles[UNREAD_MENTION_COUNT] = "unread_mention_count";
    roles[NOTIFICATION_SETTINGS] = "notification_settings";
    roles[REPLY_MARKUP_MESSAGE_ID] = "reply_markup_message_id";
    roles[DRAFT_MESSAGE] = "draft_message";
    roles[CLIENT_DATA] = "client_data";
    roles[SENDING_STATE] = "sending_state";
    return roles;
}

void ChatShareModel::fetchMore(const QModelIndex &parent)
{
    if (!m_fetchPending) {
        m_fetchPending = true;
        qint64 lastChatId = 0;
        qint64 offset = std::numeric_limits<std::int64_t>::max();
        if (m_chats.size() > 0) {
            offset = m_chats.last()->order_;
            lastChatId = m_chats.last()->id_;
        }
        QDBusPendingCall async = remoteAppIface->asyncCall(c_dbusMethod, lastChatId, offset);
        QDBusPendingCallWatcher *dbusWatcher = new QDBusPendingCallWatcher(async, this);
        connect(dbusWatcher, &QDBusPendingCallWatcher::finished,
                this, &ChatShareModel::addItems);

    }
}

bool ChatShareModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return !m_fetchPending;
}
