
#ifndef TUNNELGASDATA_H
#define TUNNELGASDATA_H
#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include  "appSrc/ParaFactManager.h"
#include "appSrc/Application.h"
#include "appSrc/ProtocolManager.h"
//数据召测
class TunnelGasData : public QObject
{
    Q_OBJECT
public:
    const QVector<QString>modelName{"O2","CO","H2",
                                    "Cl2","H2S","CO2",
                                    "CH4","温度","湿度"};

    explicit TunnelGasData(QObject *parent = nullptr);
    //Function//
    Q_INVOKABLE void queryData();

    QByteArray getTunnelGasData() {
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

signals:
    void TunnelGasQueryData(QByteArray data);

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup * regList_;
//    QByteArray moduleBusBuffer_;
//    QMap<QString ,QString>modelMap_;
};

#endif // TUNNELGASDATA_H
