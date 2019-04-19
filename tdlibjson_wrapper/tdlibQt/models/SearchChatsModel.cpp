#include "SearchChatsModel.hpp"
#include "../TdlibJsonWrapper.hpp"
#include "tdlibQt/ParseObject.hpp"
namespace tdlibQt {

constexpr int SEARCH_LIMIT = 10;

SearchChatsModel::SearchChatsModel(QObject *parent) : QAbstractItemModel(parent),
    m_clientJson(TdlibJsonWrapper::instance())
{
    rootLocal = QSharedPointer<chat>(new chat);
    rootGlobal = QSharedPointer<chat>(new chat);
    connect(m_clientJson, &tdlibQt::TdlibJsonWrapper::newChatGenerated,
            this, &tdlibQt::SearchChatsModel::addChat);

}

QVariant SearchChatsModel::dataGlobal(const QModelIndex &index, int role) const
{
    int rowIndex = index.row();
    switch (role) {
    case ID: //int64
        return QString::number(m_globalResult[rowIndex]->id_);
    case DATE:
        if (m_globalResult[rowIndex]->last_message_.data() != nullptr) {
            return m_globalResult[rowIndex]->last_message_->date_;
        }
    case PHOTO:
        if (m_globalResult[rowIndex]->photo_.data() != nullptr) {
            if (m_globalResult[rowIndex]->photo_->small_.data() != nullptr)
                return QString::fromStdString(m_globalResult[rowIndex]->photo_->small_->local_->path_);
        }
        return QVariant();
    case TITLE:
        return QString::fromStdString(m_globalResult[rowIndex]->title_);
    case TYPE:
        switch (m_globalResult[rowIndex]->type_->get_id()) {
        case chatTypeBasicGroup::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::BasicGroup);
            return resultType;
        }
        case chatTypePrivate::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Private);
            return resultType;
        }
        case chatTypeSecret::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Secret);
            return resultType;
        }
        case chatTypeSupergroup::ID: {
            chatTypeSupergroup *superGroupMetaInfo   = static_cast<chatTypeSupergroup *>
                    (m_globalResult[rowIndex]->type_.data());
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Supergroup);
            resultType["is_channel"] = superGroupMetaInfo->is_channel_;
            resultType["supergroup_id"] = superGroupMetaInfo->supergroup_id_;
            return resultType;
        }
        }

    }
    return QVariant();
}

QVariant SearchChatsModel::dataLocal(const QModelIndex &index, int role) const
{
    int rowIndex = index.row();
    switch (role) {
    case ID: //int64
        return QString::number(m_localResult[rowIndex]->id_);
    case DATE:
        if (m_localResult[rowIndex]->last_message_.data() != nullptr) {
            return m_localResult[rowIndex]->last_message_->date_;
        }
    case PHOTO:
        if (m_localResult[rowIndex]->photo_.data() != nullptr) {
            if (m_localResult[rowIndex]->photo_->small_.data() != nullptr)
                return QString::fromStdString(m_localResult[rowIndex]->photo_->small_->local_->path_);
        }
        return QVariant();
    case TITLE:
        return QString::fromStdString(m_localResult[rowIndex]->title_);
    case TYPE:
        switch (m_localResult[rowIndex]->type_->get_id()) {
        case chatTypeBasicGroup::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::BasicGroup);
            return resultType;
        }
        case chatTypePrivate::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Private);
            return resultType;
        }
        case chatTypeSecret::ID: {
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Secret);
            return resultType;
        }
        case chatTypeSupergroup::ID: {
            chatTypeSupergroup *superGroupMetaInfo   = static_cast<chatTypeSupergroup *>
                    (m_localResult[rowIndex]->type_.data());
            QVariantMap resultType;
            resultType["type"] = QVariant::fromValue(tdlibQt::Enums::ChatType::Supergroup);
            resultType["is_channel"] = superGroupMetaInfo->is_channel_;
            resultType["supergroup_id"] = superGroupMetaInfo->supergroup_id_;
            return resultType;
        }
        }

    }
    return QVariant();
}

void SearchChatsModel::addChat(const QJsonObject &chatObject)
{
    if (chatObject.contains("@extra"))    {
        if (chatObject["@extra"].toString() == "searchChatsOnServer" ||
                chatObject["@extra"].toString() == "searchChats") {
            QSharedPointer<chat> chatItem = ParseObject::parseChat(chatObject);
            if (chatObject["@extra"].toString() == "searchChatsOnServer") {
                beginInsertRows(QModelIndex(), m_globalResult.size(), m_globalResult.size());
                m_globalResult.append(chatItem);
                endInsertRows();
            } else if (chatObject["@extra"].toString() == "searchChats") {
                beginInsertRows(QModelIndex(), m_localResult.size(), m_localResult.size());
                m_localResult.append(chatItem);
                endInsertRows();
            }

            if (chatItem->photo_.data() != nullptr) {
                if (chatItem->photo_->small_.data() != nullptr)
                    if (!chatItem->photo_->small_->local_->is_downloading_completed_)
                        m_clientJson->downloadFile(chatItem->photo_->small_->id_, 1, "chatPhoto");
            }
        }
    }

}

void SearchChatsModel::updateChatPhoto(const QJsonObject &updateFileObject)
{
    if (updateFileObject["@type"].toString() == "updateFile") {
        auto fileObject = updateFileObject["file"].toObject();
        for (int i = 0; i < m_localResult.size(); i++) {
            if (m_localResult[i]->photo_.data() != nullptr) {
                if (m_localResult[i]->photo_->small_.data() != nullptr)
                    if (m_localResult[i]->photo_->small_->id_ == fileObject["id"].toInt()) {
                        m_localResult[i]->photo_->small_ = ParseObject::parseFile(fileObject);
                        QVector<int> photoRole;
                        photoRole.append(PHOTO);
                        emit dataChanged(this->createIndex(i, 0), this->createIndex(i, 0), photoRole);
                        break;
                    }
            }
        }
    }

}

void SearchChatsModel::searchChats(const QString &query)
{
    m_clientJson->searchChats(query, SEARCH_LIMIT);
    m_clientJson->searchChatsOnServer(query, SEARCH_LIMIT);
}

QModelIndex SearchChatsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (parent.column() > -1) {
        chat *Item = static_cast<chat *>(parent.internalPointer());
        if (Item == rootLocal.data())
            return createIndex(row, column, m_localResult.at(parent.row()).data());

        if (Item == rootGlobal.data())
            return createIndex(row, column, m_globalResult.at(parent.row()).data());
    }


    return QModelIndex();
}

QModelIndex SearchChatsModel::parent(const QModelIndex &child) const
{
    //in parent 3 rows. 1 - Local chats list, 2 - Global chats list,
    //3 - message search list(TODO, Future)

    if (!child.isValid())
        return QModelIndex();

    if (child.column() == -1)
        return QModelIndex();


    chat *childItem = static_cast<chat *>(child.internalPointer());

    if (!childItem)
        return QModelIndex();

    if (childItem == rootLocal.data())
        return QModelIndex();

    if (childItem == rootGlobal.data())
        return QModelIndex();


    int rowPosition = 0;

    for (int i = 0; i < m_localResult.size(); i++)
        if (m_localResult.at(i).data() == childItem) {
            rowPosition = i;
            return createIndex(rowPosition, 0, rootLocal.data());
        }
    for (int i = 0; i < m_globalResult.size(); i++)
        if (m_globalResult.at(i).data() == childItem) {
            rowPosition = i;
            return createIndex(rowPosition, 0, rootGlobal.data());
        }
    return QModelIndex();
}

int SearchChatsModel::rowCount(const QModelIndex &parent) const
{
    chat *item = static_cast<chat *>(parent.internalPointer());
    if (parent == QModelIndex())
        return 2; //Will be 3 with messages

    if (item == rootLocal.data()) {
        return m_localResult.size();
    } else if (item == rootGlobal.data()) {
        return m_globalResult.size();
    }
    return 0;
}

int SearchChatsModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant SearchChatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0)
        return QVariant();
    chat *childItem = static_cast<chat *>(index.internalPointer());
    if (!childItem)
        return QVariant();

    int rowIndex = index.row();
    if (childItem == rootLocal.data()) {
        return "Local chats";
    } else if (childItem == rootGlobal.data()) {
        return "Global chats";
    }
    if (static_cast<chat *>(index.parent().internalPointer()) == rootLocal.data()) {
        return dataLocal(index, role);
    }
    if (static_cast<chat *>(index.parent().internalPointer()) == rootGlobal.data()) {
        return dataGlobal(index, role);
    }

    return QVariant();
}

QHash<int, QByteArray> SearchChatsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ID] = "id";
    roles[TYPE] = "type";
    roles[TITLE] = "title";
    roles[DATE] = "date";
    roles[PHOTO] = "photo";

    return roles;
}
}
