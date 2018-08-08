#ifndef PAGEAPPSTARTER_HPP
#define PAGEAPPSTARTER_HPP

#include <QObject>
#include <QQueue>
#include <QVariant>
class PageAppStarter : public QObject
{
    Q_OBJECT
    QQueue<QVariantMap> m_pages;

public:
    explicit PageAppStarter(QObject *parent = nullptr);
    void addPage(QVariant chatId);
signals:

public slots:
    QVariantList getPages();

};

#endif // PAGEAPPSTARTER_HPP
