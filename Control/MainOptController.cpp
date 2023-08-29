
#include "MainOptController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"

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
        if(app()->netWorkMgr()->IsTcpConnected())
        {
            auto adressVector = regList_->getAddress();
            auto start =  QByteArray::fromHex(adressVector.last().toLatin1());
            //系统时间地址1 4字节
            QChar opts;
            if(sysOpsAble_ == 0){
                //第一位置1
              opts =   ProtocolManager::setBit(opts,1,1);
            }
            else if(sysOpsAble_ == 1) {
                //第二位置1
                ProtocolManager::setBit(opts,2,1);
            }
            //数据包总共四个字节
            QByteArray packData ;
            packData.append(opts);
//            qDebug() <<  "MainOptController Pack Size" << packData.size();
            auto sendMsg = ProtocolManager::makeWriteRegProto(start,1,packData);
            qDebug() << "MainOptController SendMsg Size: " <<sendMsg.size();
            app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
        }
    }
}

//设置系统时间
void MainOptController::setSysTimeData()
{
    if(app()->netWorkMgr()->IsTcpConnected()) {
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //数据包总共四个字节
        QByteArray packData = ProtocolManager::intToByteArray(sysTime_.toInt(),ProtocolManager::LittileEndian);
        qDebug()<<sysTime_.toInt();
        qDebug() << packData;
        qDebug() <<  "MainOptController Pack Size" << packData.size();
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
        qDebug() << sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void MainOptController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
        if(data.size()==6) {
            QByteArray  time = data.left(4);
            sysTime_  = time.toHex().toInt(nullptr, 16);
            setSysTime(QString(sysTime_));
        }
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}











