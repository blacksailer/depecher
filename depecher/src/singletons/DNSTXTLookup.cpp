#include "DNSTXTLookup.hpp"
#include <QDebug>
#include <QHostAddress>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/nameser.h>

static const QString DNS_SERVER = QStringLiteral("sfosfc.toxip.net");

//Do not work in emulator
DNSTXTLookup::DNSTXTLookup(QObject *parent) : QObject(parent),
    dns(new QDnsLookup(this))
{
    connect(dns, &QDnsLookup::finished,
            this, &DNSTXTLookup::handleLookup);

    dns->setType(QDnsLookup::TXT);
    dns->setName(DNS_SERVER);
}

DNSTXTLookup::~DNSTXTLookup()
{
    dns->deleteLater();
}

void DNSTXTLookup::lookupServer()
{
    dns->lookup();
}

void DNSTXTLookup::handleLookup()
{

    // Handle the results.
    const auto records = dns->textRecords();
    for (const QDnsTextRecord &record : records) {
        {
            setInviteLink(record.values().last());
        }
    }
    // Check the lookup succeeded.
    if (dns->error() != QDnsLookup::NoError) {
        qWarning("DNS lookup failed");
        qDebug() << dns->error() << dns->errorString();
        return;
    }
}
