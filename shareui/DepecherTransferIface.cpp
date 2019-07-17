#include "DepecherTransferIface.hpp"
#include "DepecherPluginInfo.hpp"
#include "DepecherMediaTransfer.hpp"
DepecherTransferIface::DepecherTransferIface()
{

}

QString DepecherTransferIface::pluginId() const
{
    return QLatin1String("DepecherSharePlugin");
}
bool DepecherTransferIface::enabled() const
{
    return true;
}

TransferPluginInfo *DepecherTransferIface::infoObject()
{
    return new DepecherPluginInfo;
}

MediaTransferInterface *DepecherTransferIface::transferObject()
{
    return new DepecherMediaTransfer;
}
