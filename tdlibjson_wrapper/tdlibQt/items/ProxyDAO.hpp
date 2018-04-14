#ifndef PROXYDAO_HPP
#define PROXYDAO_HPP

#include <QObject>

class ProxyDAO : public QObject
{
    Q_OBJECT
public:
    explicit ProxyDAO(QObject *parent = 0);

signals:

public slots:
};

#endif // PROXYDAO_HPP