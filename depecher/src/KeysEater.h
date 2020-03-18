#ifndef KEYSEATER_H
#define KEYSEATER_H

#include <QObject>

class QQuickItem;
class KeysEater : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem* target READ target WRITE setTarget)
    Q_PROPERTY(QList<int> keys READ keys WRITE setKeys NOTIFY keysChanged)
public:
    explicit KeysEater(QObject *parent = nullptr);

    QQuickItem *target() const;
    void setTarget(QQuickItem *target);

    QList<int> keys() const;
    void setKeys(const QList<int> &keys);

private:
    QQuickItem *m_target;
    QList<int> m_keys;

private:
    bool eventFilter(QObject *, QEvent *event);

signals:
    void keysChanged();
    void keyPressed(const int key);
};

#endif // KEYSEATER_H
