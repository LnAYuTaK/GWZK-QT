
#ifndef MAINOPTCONTROLLER_H
#define MAINOPTCONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"

class MainOptController : public QObject
{
    Q_OBJECT
public:
    explicit MainOptController(QObject *parent = nullptr);
    Q_PROPERTY(qint32   SysTime      READ SysTime      WRITE setSysTime)
    Q_PROPERTY(qint32   SysOpsAble   READ SysOpsAble   WRITE setSysOpsAble)

    qint32  sysTime(){return this->sysTime_;}
    void     setSysTime(qint32 sysTime){this->sysTime_ = sysTime;}

    qint32  SysOpsAble(){return this->sysOpsAble_;}
    void     setSysOpsAble(int sysOpsAble){this->sysOpsAble_ = sysOpsAble;}

    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

private:
    JsonFactGroup * regList_;
    qint32          sysTime_;
    qint32          sysOpsAble_;




};

#endif // MAINOPTCONTROLLER_H
