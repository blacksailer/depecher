#ifndef FILTERCHATMEMBERSMODEL_HPP
#define FILTERCHATMEMBERSMODEL_HPP

#include <QSortFilterProxyModel>
namespace tdlibQt {
class FilterChatMembersModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
    Q_PROPERTY(bool showDeleted WRITE setShowDeleted)
public:
    FilterChatMembersModel(QObject *parent = 0);

    QString search() const;
    void setSearch(const QString &search);
    void setShowDeleted(bool showDeleted);

    Q_INVOKABLE int sourceIndex(const int idx);

private:
    QString m_search;
    bool m_showDeleted;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

signals:
    void searchChanged();
};
} // tdlibQt
#endif // FILTERCHATMEMBERSMODEL_HPP
