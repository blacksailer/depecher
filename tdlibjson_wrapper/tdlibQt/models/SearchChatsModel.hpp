#ifndef SEACHCHATSMODEL_H
#define SEACHCHATSMODEL_H

#include <QAbstractItemModel>
#include <QAbstractListModel>
#include "tdlibQt/items/TdApi.hpp"

namespace tdlibQt {

class TdlibJsonWrapper;
class chat;
class SearchChatsModel : public QAbstractItemModel
{
    Q_OBJECT
    QList<chat> m_localResult;
    QList<chat> m_globalResult;
    QSharedPointer<chat> rootLocal;
    QSharedPointer<chat> rootGlobal;

public:
    explicit SearchChatsModel(QObject *parent = nullptr);
    TdlibJsonWrapper *m_clientJson;
    enum Roles {
        ID,
        TYPE,
        TITLE,
        DATE,
        PHOTO
    };
    QVariant dataLocal(const QModelIndex &index, int role) const;
    QVariant dataGlobal(const QModelIndex &index, int role) const;
signals:

private slots:

    void addChat(const QJsonObject &chatObject);
    void updateChatPhoto(const QJsonObject &fileObject);

public slots:
    void searchChats(const QString &query);


    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};
} //namespace tdlibQt

#endif // SEACHCHATSMODEL_H
