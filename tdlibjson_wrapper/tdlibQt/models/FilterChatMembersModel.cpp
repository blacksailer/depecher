#include "FilterChatMembersModel.hpp"
namespace tdlibQt {
FilterChatMembersModel::FilterChatMembersModel(QObject *parent):
    QSortFilterProxyModel(parent)
{

}

QString FilterChatMembersModel::search() const
{
    return m_search;
}

void FilterChatMembersModel::setSearch(const QString &search)
{
    if (m_search == search || !sourceModel())
        return;
    m_search = search;
    invalidateFilter();
    emit searchChanged();
}

bool FilterChatMembersModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

    static const int nameRole = sourceModel()->roleNames().key("name");
    static const int usernameRole = sourceModel()->roleNames().key("username");
    static const int deletedRole = sourceModel()->roleNames().key("deleted");

    if (m_search.isEmpty()) {
        if (m_showDeleted)
            return true;
        else
            return !sourceModel()->data(index, deletedRole).toBool();
    }

    return (!sourceModel()->data(index, deletedRole).toBool() &&
            (sourceModel()->data(index, nameRole).toString().contains(m_search, Qt::CaseInsensitive) ||
             sourceModel()->data(index, usernameRole).toString().contains(m_search, Qt::CaseInsensitive)));
}

int FilterChatMembersModel::sourceIndex(const int idx)
{
    return mapToSource(index(idx, 0)).row();
}

void FilterChatMembersModel::setShowDeleted(bool showDeleted)
{
    if (m_showDeleted == showDeleted)
        return;
    m_showDeleted = showDeleted;
    invalidateFilter();
}
} // tdlibQt
