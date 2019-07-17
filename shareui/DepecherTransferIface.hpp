#ifndef DEPECHERTRANSFERIFACE_HPP
#define DEPECHERTRANSFERIFACE_HPP

#include <TransferEngine-qt5/transferplugininterface.h>
#include <TransferEngine-qt5/transferplugininfo.h>
#include <TransferEngine-qt5/transfermethodinfo.h>
#include <TransferEngine-qt5/mediatransferinterface.h>


class DepecherTransferIface : public QObject, public TransferPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.blacksailer.depecher.transfer.plugin")
    Q_INTERFACES(TransferPluginInterface)
public:
    DepecherTransferIface();
    QString pluginId() const;
    bool enabled() const;
    TransferPluginInfo *infoObject();
    MediaTransferInterface *transferObject();
};

#endif // DEPECHERTRANSFERIFACE_HPP
