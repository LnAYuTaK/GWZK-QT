
#ifndef TUNNELGASDEV_H
#define TUNNELGASDEV_H
#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include  "appSrc/ParaFactManager.h"
#include "appSrc/Application.h"

class TunnelGasDev : public QObject
{
    Q_OBJECT
public:
    const QVector<QString>modelName{"O2","CO","H2",
                                    "Cl2","H2S","CO2",
                                    "CH4","温度","湿度"};

    explicit TunnelGasDev(QObject *parent = nullptr);

    Q_INVOKABLE void queryData();

signals:
    void TunnelGasQueryData(QByteArray data);

private:
    JsonFactGroup * regList_;
//    QByteArray moduleBusBuffer_;
//    QMap<QString ,QString>modelMap_;
};

#endif // TUNNELGASDEV_H
