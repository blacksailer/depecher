#ifndef SHARECHATPLUGIN_HPP
#define SHARECHATPLUGIN_HPP

#include <QQmlExtensionPlugin>

class ShareChatPlugin  : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);

};

#endif // SHARECHATPLUGIN_HPP
