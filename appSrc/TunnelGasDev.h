
#ifndef TUNNELGASDEV_H
#define TUNNELGASDEV_H
#include <QObject>
#include <QString>
#include <QDebug>
#include <QVector>
class TunnelGasDev : public QObject
{
    Q_OBJECT
public:
    explicit TunnelGasDev(QObject *parent = nullptr);

//    Q_INVOKABLE void setGasIdAddress(QString address);

//    Q_INVOKABLE void setGasIdFormat(QString adressformat);

//    Q_INVOKABLE void setGasUnitConunt(QString unitConunt);

//    Q_INVOKABLE void setGasUnitCycle(QString unitCycle);

//    Q_INVOKABLE void setGasUnitChannel(QString unitChannel);
private:
    QByteArray moduleBusBuffer_;
    QVector<QString> msg;
};

#endif // TUNNELGASDEV_H
