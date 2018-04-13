#ifndef LISTENSCHEDULER_HPP
#define LISTENSCHEDULER_HPP

#include <QObject>
#include <QWaitCondition>
#include <QTimer>
namespace tdlibQt {
class ListenScheduler : public QObject
{
    Q_OBJECT
    QWaitCondition stateAndTimeCondition;
    QTimer timer;
    const int TIMEOUT_INTERVAL = 30 * 1000;
    bool appIsActive = false;
public:
    explicit ListenScheduler(QObject *parent = 0);
    QWaitCondition *getCondition();
signals:

private slots:
    void wakeUpListener();
public slots:
    void onApplicationStateChanged(Qt::ApplicationState state);
    void beginForever();

};

} //namespace tdlibQt

#endif // LISTENSCHEDULER_HPP
