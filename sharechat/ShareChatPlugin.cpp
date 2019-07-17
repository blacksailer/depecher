#include "tdlibQt/include/TdlibNamespace.hpp"
#include "ShareChatPlugin.hpp"
#include "ChatShareModel.hpp"
#include <qqml.h>
void ShareChatPlugin::registerTypes(const char *uri)
{
    // @uri org.blacksailer.depecher.sharechat
    qmlRegisterUncreatableType<tdlibQt::Enums>(uri, 1, 0, "TdlibState",
            "Error class uncreatable");
    qmlRegisterType<ChatShareModel>(uri, 1, 0, "ShareChatModel");
}
