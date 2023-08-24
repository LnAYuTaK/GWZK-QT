
#include "WaterPumpController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"
WaterPumpController::WaterPumpController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->WaterPump())
    ,address_("DFEGWZD123456789")
    ,format_(0)
    ,count_(0)
{

}

void WaterPumpController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::WaterPumpController_t,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void WaterPumpController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        //寄存器首地址
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //地址 17字节
        QByteArray addressData =QByteArray(address_.toLatin1())+QByteArray(1, '\x00');
        //格式 2字节
        auto formatData = ProtocolManager::intToHexByteArray(format_);
        //数量 2字节
        auto countData = ProtocolManager::intToHexByteArray(count_);
        //备用字节 6字节
        QByteArray standby(6, '\x00');
        //数据包总共27字节
        QByteArray packData = addressData +
                              formatData +
                              countData +
                              standby;
        qDebug() << "WaterPumpController SendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(), packData);
        qDebug() << "WaterPumpController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void WaterPumpController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
        qDebug() << data.size();
        qDebug() << data;
    }
    else if(type == ProtocolManager::HandleWrite) {
        qDebug() << "Handle Write: "<< data;
    }
}



