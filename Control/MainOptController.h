
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
    Q_PROPERTY(int   SysTime      READ SysTime      WRITE setSysTime)
    Q_PROPERTY(int   SysOpsAble   READ SysOpsAble   WRITE setSysOpsAble)

    int  SysTime(){return this->sysTime_;}
    void setSysTime(int sysTime){this->sysTime_ = sysTime;}

    int  SysOpsAble(){return this->sysOpsAble_;}
    void setSysOpsAble(int sysOpsAble){this->sysOpsAble_ = sysOpsAble;}

    Q_INVOKABLE void queryData();
    Q_INVOKABLE void setData();
    //获取寄存器首地址
    QByteArray getMainOptReg(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup * regList_;
    int          sysTime_;
    int          sysOpsAble_;

};

#endif // MAINOPTCONTROLLER_H
