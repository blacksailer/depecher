#include "FilterContactsModel.hpp"
namespace tdlibQt {
FilterContactsModel::FilterContactsModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

QAbstractItemModel *FilterContactsModel::source() const
{
    return m_source;
}


void FilterContactsModel::setSource(QAbstractItemModel *source)
{
    if (m_source == source)
        return;

    m_source = source;
    setSourceModel(m_source);

    emit sourceChanged(m_source);
}

void FilterContactsModel::sortModel(Qt::SortOrder order)
{
    this->sort(0, order);
}

bool FilterContactsModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (m_source) {
        QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

        return (sourceModel()->data(index, 1).toString().contains(filterRegExp())
                || sourceModel()->data(index, 2).toString().contains(filterRegExp())
                || sourceModel()->data(index, 3).toString().contains(filterRegExp()));
    }
    return true;
}
} // tdlibQt
