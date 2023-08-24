
#include "WaterLevelController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/Utils.h"
#include "appSrc/NetWorkManager.h"

WaterLevelController::WaterLevelController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->WaterLevel())
    ,count_(0)
    ,cycle_(0)
    ,channel_(0)
    ,format_(0)
    ,address_("DFEGWZD1234567890")
{

}

void WaterLevelController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::WaterLevelController_t,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void WaterLevelController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //地址 17字节
        QByteArray byteArray =QByteArray(address_.toUtf8())+QByteArray(1, '\x00');;
        //格式 2字节
        auto formatData = ProtocolManager::intToHexByteArray(format_);
        //数量 2字节
        auto countData = ProtocolManager::intToHexByteArray(count_);
        //周期 2字节
        auto cycleData = ProtocolManager::intToHexByteArray(cycle_);
        //通道 2字节
        auto channelData = ProtocolManager::intToHexByteArray(channel_);
        //备用 6字节
        QByteArray standby(6, '\x00');
        //数据包总共 31字节
        QByteArray packData  = byteArray +
                               formatData +
                               countData +
                               cycleData +
                               channelData +
                               standby;
        qDebug() << "WaterLevelControllerSendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "WaterLevelController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void WaterLevelController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
        qDebug() << data.size();
        qDebug() << data;
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}
