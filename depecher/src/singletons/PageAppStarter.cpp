#include "PageAppStarter.hpp"

PageAppStarter::PageAppStarter(QObject *parent) : QObject(parent)
{

}
void PageAppStarter::addPage(QVariant chatId)
{
    QVariantMap NewPage;
    NewPage["pageParam"] = QString::number(chatId.toLongLong());
    m_pages.append(NewPage);
}

QVariantList PageAppStarter::getPages()
{
    QVariantList result;
    while (m_pages.size() > 0)
        result.append(m_pages.dequeue());

    return result;
}
