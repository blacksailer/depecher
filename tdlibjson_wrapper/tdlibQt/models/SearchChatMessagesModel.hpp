#ifndef SEARCHCHATMESSAGESMODEL_HPP
#define SEARCHCHATMESSAGESMODEL_HPP

#include <QtCore>
#include "tdlibQt/items/TdApi.hpp"
namespace tdlibQt {
class TdlibJsonWrapper;
class SearchChatMessagesModel : public QAbstractListModel
{
    Q_OBJECT

    TdlibJsonWrapper *m_tdlibJson;
    QList<QSharedPointer<message>> m_messages;
public:
    explicit SearchChatMessagesModel(QObject *parent = nullptr);

signals:

public slots:
};
} // namespace tdlibQt
#endif // SEARCHCHATMESSAGESMODEL_HPP
