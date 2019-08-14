#include "DepecherPluginInfo.hpp"

DepecherPluginInfo::DepecherPluginInfo() : m_ready(false)
{

}

QList<TransferMethodInfo> DepecherPluginInfo::info() const
{
    return m_infoList;
}

void DepecherPluginInfo::query()
{
    TransferMethodInfo info;

    QStringList capabilities;
    capabilities <<  QLatin1String("application/*")
                 << QLatin1String("image/*")
                 << QLatin1String("audio/*")
                 << QLatin1String("video/*")
                 << QLatin1String("text/plain")
                 << QLatin1String("text/x-url")
                 << QLatin1String("text/vcard");
    /*
    {"data":"BEGIN:VCARD\r\nVERSION:2.1\nEND:VCARD\r\n",
    "icon":"image://theme/icon-m-telephony-contact-avatar","name":"contact.vcf","type":"text/vcard"}
    */
    /* {"data":"Виктор Лемпитцкий - зрение\nВетров - вероятностные модели\nИи павлов\nВижн лабс\n",
     * "name":"note.txt","type":"text/plain",
     * "status":"Виктор Лемпитцкий - зрение\nВетров - вероятностные модели\nИи павлов\nВижн лабс\n",
     * "linkTitle":"note.txt"}*/
    info.displayName     = QLatin1String("Depecher");
    info.methodId        = QLatin1String("DepecherSharePlugin");
    info.accountIcon     = QLatin1String("/usr/share/depecher/qml/assets/icons/depecher.png");
    info.shareUIPath     = QLatin1String("/usr/share/depecher/qml/ShareUI.qml");
    info.capabilitities  = capabilities;
    m_infoList.clear();
    m_infoList << info;

    m_ready = true;
    Q_EMIT infoReady();
}

bool DepecherPluginInfo::ready() const
{
    return m_ready;
}
