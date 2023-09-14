
#include "MainOptController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/NetWorkManager.h"

MainOptController::MainOptController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->MainControl())
    ,sysTime_("")
    ,sysOpsAble_(0)
{

}
//设置系统状态
void MainOptController::setSysStateData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.last().toLatin1());
        //系统时间地址1 4字节
        QChar opts{};
        if(sysOpsAble_ == 0){
            //第一位置1
          opts =  ProtocolManager::setBit(opts,0,1);
        }
        else if(sysOpsAble_ == 1) {
            //第二位置1
           opts = ProtocolManager::setBit(opts,1,1);
        }
        //数据包总共四个字节
        QByteArray packData ;
        packData.append(opts).append('\x00');
//      qDebug() <<  "MainOptController Pack Size" << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,1,packData);
        qDebug() << "MainOptController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

//设置系统时间
void MainOptController::setSysTimeData()
{
    if(app()->netWorkMgr()->IsTcpConnected()) {
        auto adressVector = regList_->getAddress();


        QStringList dateTimeParts = sysTime_.split(" ");

        QString date = dateTimeParts[0];
        QString time = dateTimeParts[1];

        QStringList dateParts = date.split("-");
        QStringList timeParts = time.split(":");

        int year = dateParts[0].toInt();
        int month = dateParts[1].toInt();
        int day = dateParts[2].toInt();

        int hour = timeParts[0].toInt();
        int min = timeParts[1].toInt();
        int sec = timeParts[2].toInt();
        QTime timeData(hour, min, sec); // Set the time to midnight
        QDate dateData(year, month, day);
        QDateTime dateTime(dateData, timeData);

        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //数据包总共四个字节
        QByteArray packData = ProtocolManager::intToByteArray((int)((dateTime.toSecsSinceEpoch())),ProtocolManager::BigEndian);
       // qDebug()<< dateTime.toString();
        // qDebug() << packData;
        // qDebug() <<  "MainOptController Pack Size" << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,2,packData);
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

//查询系统时间
void MainOptController::querySysTimeData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::MainOptController_t,start,2);
        //qDebug() << sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void MainOptController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{

    if(type == ProtocolManager::HandleRead) {
        if(data.size()==4) {
           QByteArray timesBytes = data.left(4);
//          sysTime_  = time.toHex().toInt(nullptr, 16);
         //  qDebug()<< timesBytes.toHex().toInt(nullptr, 16);
           QDateTime dataTimeRes  =   QDateTime::fromSecsSinceEpoch(timesBytes.toHex().toInt(nullptr, 16));
           //获取年月日
           QDate date   = dataTimeRes.date();
           QString dataStr = QString::number(date.year())
                             +QString("-")
                             +QString::number(date.month())
                             +QString("-")
                             +QString::number(date.day())
                             +QString(" ");
            //获取时分秒
           QTime time  = dataTimeRes.time();
           QString timeStr =  QString::number(time.hour())
                             +QString(":")
                             +QString::number(time.minute())
                             +QString(":")
                             +QString::number(time.second());
           QString  res = dataStr+timeStr;
           setSysTime(res);
        }
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}











