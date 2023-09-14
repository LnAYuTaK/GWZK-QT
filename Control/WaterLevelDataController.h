
#ifndef WATERLEVELDATACONTROLLER_H
#define WATERLEVELDATACONTROLLER_H



#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

//液位数据召测
class WaterLevelDataController : public QObject
{
    Q_OBJECT
public:
    explicit WaterLevelDataController(QObject *parent = nullptr);
    Q_PROPERTY(QString     rawData      READ rawData      WRITE setRawData      NOTIFY rawDataChanged)
    Q_PROPERTY(QString     alarmLevel   READ alarmLevel   WRITE setAlarmLevel   NOTIFY alarmLevelChanged)

    //Read
   QString   rawData() const {return rawData_;}
   QString     alarmLevel() const {return alarmLevel_;}
    //Set
    void   setRawData(QString rawData){
        rawData_ = rawData;
        emit rawDataChanged(rawData_);
    }
    void   setAlarmLevel(QString alarmLevel ){
        alarmLevel_ = alarmLevel ;
        emit  alarmLevelChanged(alarmLevel_);
    }

    //Function//
    Q_INVOKABLE void queryData();

signals:
    void rawDataChanged(QString rawData);
    void alarmLevelChanged(QString alarmLevel);
    void enableChanged(int enable);

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup * regList_;
    //原始值//
    QString rawData_;
    //单位
    QString unit_;
    //报警等级
    QString alarmLevel_;
};

#endif // WATERLEVELDATACONTROLLER_H
