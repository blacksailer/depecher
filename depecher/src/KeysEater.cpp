#include "KeysEater.h"
#include <QQuickItem>

KeysEater::KeysEater(QObject *parent) :
    QObject(parent),
    m_target(NULL)
{

}

QList<int> KeysEater::keys() const
{
    return m_keys;
}

void KeysEater::setKeys(const QList<int> &keys)
{
    if (m_keys == keys)
        return;
    m_keys = keys;
    emit keysChanged();
}


QQuickItem *KeysEater::target() const
{
    return m_target;
}

void KeysEater::setTarget(QQuickItem *target)
{
    if (m_target == target)
        return;
    if (m_target)
        m_target->removeEventFilter(this);
    m_target = target;
    if (target)
        m_target->installEventFilter(this);
}

bool KeysEater::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QKeyEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        int i = m_keys.indexOf(keyEvent->key());
        if (i >= 0) {;
            emit keyPressed(m_keys.at(i));
            return true;
        }
    }
    return false;
}
