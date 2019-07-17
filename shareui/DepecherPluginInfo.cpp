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
    capabilities << QLatin1String("image/*")
                 << QLatin1String("audio/*")
                 << QLatin1String("video/*")
                 << QLatin1String("text/plain")
                 << QLatin1String("text/x-url")
                 << QLatin1String("text/vcard");
    /*
    {"data":"BEGIN:VCARD\r\nVERSION:2.1\r\nFN;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:=D0=91=D0=BE=D1=80=D0=B8=D1=81 =\r\n=D0=A1=D0=BE=D0=BA=D0=BE=D0=BB=D0=BE=D0=B2\r\nN;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:=D0=A1=D0=BE=D0=BA=D0=BE=D0=BB=D0=\r\n=BE=D0=B2;=D0=91=D0=BE=D1=80=D0=B8=D1=81;;;\r\nX-QTPROJECT-FAVORITE:true;0\r\nREV:2019-02-24T11:28:29Z\r\nADR;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE;HOME:;;;=D0=9C=D0=BE=D1=81=D0=\r\n=BA=D0=B2=D0=B0;;;=D0=A0=D0=BE=D1=81=D1=81=D0=B8=D1=8F\r\nADR;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE;HOME:;;;=D0=9C=D0=BE=D1=81=D0=\r\n=BA=D0=B2=D0=B0;;;=D0=A0=D0=BE=D1=81=D1=81=D0=B8=D1=8F\r\nBDAY:1992-11-23\r\nTEL;CELL:+79031859219\r\nTEL;CELL:89\r\nURL:https://m.vk.com/id2111761\r\nURL:https://m.vk.com/id2111761\r\nEND:VCARD\r\n",
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
