#include "ListenObject.hpp"
#include <td/telegram/td_json_client.h>
#include <QDebug>
#include <QThread>
#include <QGuiApplication>
namespace tdlibQt {

static const QByteArray authorizationStateClosedStr("{\"@type\":\"updateAuthorizationState\",\"authorization_state\":{\"@type\":\"authorizationStateClosed\"}}");

ListenObject::ListenObject(void *client_, QWaitCondition *condition,
                           QObject *parent) : QObject(parent),
    client(client_),
    onActive(condition)
{
    timer = new QTimer(this);
    timer->setInterval(30 * 1000);
    qRegisterMetaType<Qt::ApplicationState>("Qt::ApplicationState");
    connect(qApp, &QGuiApplication::applicationStateChanged,
            this, &ListenObject::onApplicationStateChanged);
    connect(timer, &QTimer::timeout, this, &ListenObject::setIsActiveTrue);
}

void ListenObject::onApplicationStateChanged(Qt::ApplicationState state)
{
    switch (state) {
    case Qt::ApplicationActive:
        timer->stop();
        setIsActiveTrue();
        break;
    default:
        break;
    }
}

void ListenObject::setIsActiveTrue()
{
    isActive = true;
}

void ListenObject::listen()
{
    forever {
        //        mutex.lock();
        //        onActive->wait(&mutex);
        if (isActive) {
            try {
                //Throws std::logic_error for some  reason.
                std::string str = td_json_client_receive(client, 10);

                if (!str.empty()) {
                    QByteArray result = QByteArray::fromStdString(str);
                    if (result == authorizationStateClosedStr) {
                        qApp->quit();
                        return;
                    } else {
                        emit resultReady(result);
                    }
                }
            } catch (std::logic_error err) {
#ifdef QT_DEBUG
                qDebug() << "Logic error caught";
#endif
                if (qApp->applicationState() != Qt::ApplicationActive) {
                    setIsActiveTrue();
                    timer->start();
                }
            }
        }
        //        mutex.unlock();
    }
}
}//namespace tdlibQt
