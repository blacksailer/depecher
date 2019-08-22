#ifndef DEPECHERPLUGININFO_HPP
#define DEPECHERPLUGININFO_HPP
#include <TransferEngine-qt5/transferplugininfo.h>
#include <TransferEngine-qt5/transfermethodinfo.h>

class DepecherPluginInfo: public TransferPluginInfo
{
    Q_OBJECT
public:
    DepecherPluginInfo();
    QList<TransferMethodInfo> info() const;
    void query();
    bool ready() const;

private:
    QList<TransferMethodInfo> m_infoList;
    bool m_ready;

};

#endif // DEPECHERPLUGININFO_HPP
