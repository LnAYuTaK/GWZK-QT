
#include "MainOptController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

MainOptController::MainOptController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->MainControl())
    ,sysTime_(0)
    ,sysOpsAble_(0)
{

}

void MainOptController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(start,adressVector.count());
        qDebug() << sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void MainOptController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {

        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //系统时间地址1 4字节
        QByteArray sysTime;
        sysTime.resize(sizeof(sysTime_));
        memcpy(sysTime.data(), &sysTime_,sizeof(sysTime_));
        //系统操作使能  2字节
        QByteArray sysOpsAble = ProtocolManager::intToHexByteArray(sysOpsAble_);
        //数据包总共6字节
        QByteArray packData = sysTime +
                              sysOpsAble;
        qDebug() << sysTime.size()<< " "<< sysOpsAble.size();
        qDebug() <<  "MainOptController Pack Size" << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "MainOptController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);

    }
}
