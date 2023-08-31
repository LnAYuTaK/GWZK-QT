
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
class TunnelGas :public  QObject
{
    Q_OBJECT
public:
    explicit TunnelGas(QObject *parent = nullptr);
    Q_PROPERTY(int       rawData      READ rawData      WRITE setRawData      NOTIFY rawDataChanged)
    Q_PROPERTY(QString   unit         READ unit         CONSTANT)
    Q_PROPERTY(int       alarmLevel   READ alarmLevel   WRITE setAlarmLevel   NOTIFY alarmLevelChanged)
    Q_PROPERTY(int       enable       READ enable       WRITE setEnable       NOTIFY enableChanged)
    //Read
    int     rawData() const {return rawData_;}
    QString unit()const {return unit_;}
    int     alarmLevel() const {return alarmLevel_;}
    int     enable()const {return enable_;}
    //Set
    void   setRawData(int rawData){
        rawData_ = rawData;
        emit rawDataChanged(rawData_);
    }
    //Set
    void   setAlarmLevel(int alarmLevel ){
        alarmLevel_ = alarmLevel ;
        emit  alarmLevelChanged(alarmLevel_);
    }
    void setEnable(int enable) {
       enable_ = enable;
       emit  enableChanged(alarmLevel_);
    }

signals:
    void rawDataChanged(int rawData);
    void alarmLevelChanged(int alarmLevel);
    void enableChanged(int enable);
private:
    //原始值//
    int  rawData_;
    //单位
    QString unit_;
    //报警等级
    int alarmLevel_;
    //是否使能
    int enable_;
};

class TunnelGasData : public QObject
{
    Q_OBJECT
public:
    const QVector<QString>modelName{"O2","CO","H2",
                                    "Cl2","H2S","CO2",
                                    "CH4","温度","湿度"};

    explicit TunnelGasData(QObject *parent = nullptr);


    Q_PROPERTY(TunnelGas   *GasO2    READ GasO2     CONSTANT)
    Q_PROPERTY(TunnelGas   *GasCO    READ GasCO     CONSTANT)
    Q_PROPERTY(TunnelGas   *GasCl2   READ GasCl2    CONSTANT)
    Q_PROPERTY(TunnelGas   *GasH2S   READ GasH2S    CONSTANT)
    Q_PROPERTY(TunnelGas   *GasH2    READ GasH2     CONSTANT)
    Q_PROPERTY(TunnelGas   *GasCO2   READ GasCO2    CONSTANT)
    Q_PROPERTY(TunnelGas   *GasCH4   READ GasCH4    CONSTANT)
    Q_PROPERTY(TunnelGas   *EnvTemp  READ EnvTemp   CONSTANT)
    Q_PROPERTY(TunnelGas   *EnvHumi  READ EnvHumi   CONSTANT)

    //Function//
    Q_INVOKABLE void queryData();
    Q_INVOKABLE void setData();
    //Read
    TunnelGas *GasO2(){return GasO2_;}
    TunnelGas *GasCO(){return GasCO_;}
    TunnelGas *GasCl2(){return GasCl2_;}
    TunnelGas *GasH2S(){return GasH2S_;}
    TunnelGas *GasH2(){return GasH2_;}
    TunnelGas *GasCO2(){return GasCO2_;}
    TunnelGas *GasCH4(){return GasCH4_;}
    TunnelGas *EnvTemp(){return EnvTemp_;}
    TunnelGas *EnvHumi(){return EnvHumi_;}

    QByteArray getTunnelGasData() {
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

signals:
    void TunnelGasQueryData(QByteArray data);

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup * regList_;
    TunnelGas * GasO2_;
    TunnelGas * GasCO_;
    TunnelGas * GasCl2_;
    TunnelGas * GasH2S_;
    TunnelGas * GasH2_;
    TunnelGas * GasCO2_;
    TunnelGas * GasCH4_;
    TunnelGas * EnvTemp_;
    TunnelGas * EnvHumi_;
};

#endif // TUNNELGASDATA_H
