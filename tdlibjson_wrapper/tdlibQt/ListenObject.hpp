#ifndef LISTENOBJECT_HPP
#define LISTENOBJECT_HPP

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QTimer>
class QWaitCondition;

namespace tdlibQt {


class ListenObject : public QObject
{
    Q_OBJECT
    void *client;
    QWaitCondition *onActive;
    QMutex mutex;
    QTimer *timer;
    bool isActive = true;

public:
    explicit ListenObject(void *client_ = nullptr, QWaitCondition *condition = nullptr,
                          QObject *parent = 0);

signals:
    void resultReady(const QByteArray &s);

private slots:
    void onApplicationStateChanged(Qt::ApplicationState state);
    void setIsActiveTrue();
public slots:
    void listen();

};
}//namespace tdlibQt
#endif // LISTENOBJECT_HPP
