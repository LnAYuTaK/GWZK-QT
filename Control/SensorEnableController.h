
#ifndef SENSORENABLECONTROLLER_H
#define SENSORENABLECONTROLLER_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/ParaFactManager.h"
#include "appSrc/Application.h"
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

class SensorEnableController : public QObject
{
    Q_OBJECT
public:
    explicit SensorEnableController(QObject *parent = nullptr);
    //传感器使能
    Q_PROPERTY(bool O2Enable          READ  O2Enable             WRITE setO2Enable          NOTIFY O2EnableChanged)
    Q_PROPERTY(bool COEnable          READ  COEnable             WRITE setCOEnable          NOTIFY COEnableChanged)
    Q_PROPERTY(bool Cl2Enable         READ  Cl2Enable            WRITE setCl2Enable         NOTIFY Cl2EnableChanged)
    Q_PROPERTY(bool H2SEnable         READ  H2SEnable            WRITE setH2SEnable         NOTIFY H2SEnableChanged)
    Q_PROPERTY(bool H2Enable          READ  H2Enable             WRITE setH2Enable          NOTIFY H2EnableChanged)
    Q_PROPERTY(bool CO2Enable         READ  CO2Enable            WRITE setCO2Enable         NOTIFY CO2EnableChanged)
    Q_PROPERTY(bool CH4Enable         READ  CH4Enable            WRITE setCH4Enable         NOTIFY CH4EnableChanged)
    Q_PROPERTY(bool TemHumEnable      READ  TemHumEnable         WRITE setTemHumEnable      NOTIFY TemHumEnableChanged)
    Q_PROPERTY(bool WaterLevelEnable  READ  WaterLevelEnable     WRITE setWaterLevelEnable  NOTIFY WaterLevelEnableChanged)
    //Read
    bool O2Enable()        {return O2Enabale_;}
    bool COEnable()        {return COEnable_;}
    bool Cl2Enable()       {return Cl2Enable_;}
    bool H2SEnable()       {return H2SEnable_;}
    bool H2Enable()        {return H2Enable_;}
    bool CO2Enable()       {return CO2Enable_;}
    bool CH4Enable()       {return CH4Enable_;}
    bool TemHumEnable()    {return TemHumEnable_;}
    bool WaterLevelEnable(){return WaterLevelEnable_;}
    //Set
    void setO2Enable(bool isEnable){
        O2Enabale_ = isEnable;
        emit O2EnableChanged(O2Enabale_);
    }
    void setCOEnable(bool isEnable){
        COEnable_ = isEnable;
        emit COEnableChanged(COEnable_);
    }
    void setCl2Enable(bool isEnable){
        Cl2Enable_ = isEnable;
        emit Cl2EnableChanged(Cl2Enable_);
    }
    void setH2SEnable(bool isEnable){
        H2SEnable_ = isEnable;
        emit H2SEnableChanged(H2SEnable_);
    }
    void setH2Enable(bool isEnable){
        H2Enable_ = isEnable;
        emit H2EnableChanged(H2Enable_);
    }
    void setCO2Enable(bool isEnable){
        CO2Enable_ = isEnable;
        emit CO2EnableChanged(CO2Enable_);
    }
    void setCH4Enable(bool isEnable){
        CH4Enable_ = isEnable;
        emit CH4EnableChanged(CH4Enable_);
    }
    void setTemHumEnable(bool isEnable){
        TemHumEnable_ = isEnable;
        emit TemHumEnableChanged(TemHumEnable_);
    }
    void setWaterLevelEnable(bool isEnable){
        WaterLevelEnable_ = isEnable;
        emit WaterLevelEnableChanged(WaterLevelEnable_);
    }
    //FUNCTION
    Q_INVOKABLE void queryData();
    Q_INVOKABLE void setData();

signals:
    void O2EnableChanged(bool isEnable);
    void COEnableChanged(bool isEnable);
    void Cl2EnableChanged(bool isEnable);
    void H2SEnableChanged(bool isEnable);
    void H2EnableChanged(bool isEnable);
    void CO2EnableChanged(bool isEnable);
    void CH4EnableChanged(bool isEnable);
    void TemHumEnableChanged(bool isEnable);
    void WaterLevelEnableChanged(bool isEnable);

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup * regList_;
    bool  O2Enabale_;
    bool  COEnable_;
    bool  Cl2Enable_;
    bool  H2SEnable_;
    bool  H2Enable_;
    bool  CO2Enable_;
    bool  CH4Enable_;
    bool  TemHumEnable_;
    bool  WaterLevelEnable_;

};

#endif // SENSORENABLECONTROLLER_H
