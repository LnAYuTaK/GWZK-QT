
#ifndef MAINOPTCONTROLLER_H
#define MAINOPTCONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"
//主控参数设置
class MainOptController : public QObject
{
    Q_OBJECT
public:
    explicit MainOptController(QObject *parent = nullptr);
    Q_PROPERTY(QString   SysTime      READ SysTime     WRITE setSysTime    NOTIFY sysTimeChanged)
    Q_PROPERTY(int       SysOpsAble   READ SysOpsAble  WRITE setSysOpsAble NOTIFY sysOpsAbleChanged)

    QString SysTime(){return this->sysTime_;}
    int  SysOpsAble(){return this->sysOpsAble_;}
    void setSysTime(QString sysTime){
        this->sysTime_ = sysTime;
        emit sysTimeChanged(sysTime_);
    }
    void setSysOpsAble(int sysOpsAble){
        this->sysOpsAble_ = sysOpsAble;
        emit sysOpsAbleChanged(sysOpsAble_);
    }
    //系统状态设置
    Q_INVOKABLE void setSysStateData();
    //系统时间参数设置查询
    Q_INVOKABLE void setSysTimeData();
    Q_INVOKABLE void querySysTimeData();


    //获取寄存器首地址
    QByteArray getMainOptReg(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

signals:
    void sysTimeChanged(QString sysTime);
    void sysOpsAbleChanged(int sysOpsAble);

private:
    JsonFactGroup * regList_;
    QString         sysTime_;
    int          sysOpsAble_;

};

#endif // MAINOPTCONTROLLER_H
