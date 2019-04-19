#ifndef FILTERCONTACTSMODEL_HPP
#define FILTERCONTACTSMODEL_HPP

#include <QSortFilterProxyModel>
namespace tdlibQt {

class FilterContactsModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel *source READ source WRITE setSource NOTIFY sourceChanged)
    QAbstractItemModel *m_source;

public:
    FilterContactsModel(QObject *parent = 0);

    // QSortFilterProxyModel interface
    QAbstractItemModel *source() const;

public slots:
    void setSource(QAbstractItemModel *source);

signals:
    void sourceChanged(QAbstractItemModel *source);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};
} // tdlibQt
#endif // FILTERCONTACTSMODEL_HPP
