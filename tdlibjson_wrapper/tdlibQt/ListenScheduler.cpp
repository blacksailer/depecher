#include "ListenScheduler.hpp"
#include <QGuiApplication>
#include <QDebug>
namespace tdlibQt {
void ListenScheduler::beginForever()
{
    forever {
        if (appIsActive)
            wakeUpListener();
    }
}

ListenScheduler::ListenScheduler(QObject *parent) : QObject(parent)
{
    connect(qApp, &QGuiApplication::applicationStateChanged,
            this, &ListenScheduler::onApplicationStateChanged);

    timer.setInterval(TIMEOUT_INTERVAL);
    connect(&timer, &QTimer::timeout, this, &ListenScheduler::wakeUpListener);
}

QWaitCondition *ListenScheduler::getCondition()
{
    return &stateAndTimeCondition;
}

void ListenScheduler::wakeUpListener()
{
    stateAndTimeCondition.wakeOne();
}

void ListenScheduler::onApplicationStateChanged(Qt::ApplicationState state)
{
    beginForever();
    switch (state) {
    case Qt::ApplicationActive:
        appIsActive = true;
        if (timer.isActive())
            timer.stop();
        break;
    default:
        appIsActive = false;
        if (!timer.isActive()) {
            qDebug() << "sleeping for 30 seconds";
            timer.start();
        }
        break;
    }
}

} //namespace tdlibQt
