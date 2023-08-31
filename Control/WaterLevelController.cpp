
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
    ,format_("递增")
    ,address_("")
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
        int format = 0;
        if(format_ == "递增"){
            format=0;
        }
        else if(format_ == "相同"){
            format=0;
        }
        auto formatData = ProtocolManager::intToHexByteArray(format);
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
        //液位 ID 地址 18 字节
        QByteArray address = data.left(18);
        setAddress(QString::fromUtf8(address));
        QByteArray formatdata{};
        int format = 0;
        formatdata.append(data.at(18)).append(data.at(19));
        format = formatdata.toHex().toInt(nullptr,16);
        if(format  == 0){
            setFormat(QString::fromLocal8Bit("递增"));
        }
        else if(format  == 1){
            setFormat(QString::fromLocal8Bit("相同"));
        }
        //数量 2字节
        QByteArray countdata{};
        int count = 0;
        countdata.append(data.at(20)).append(data.at(21));
        count =  countdata.toHex().toInt(nullptr,16);
        setCount(count);
        //周期 2字节
        QByteArray cycledata{};
        int cycle= 0;
        cycledata.append(data.at(22)).append(data.at(23));
        cycle =  cycledata.toHex().toInt(nullptr,16);
        setCycle(cycle);
        //通道 2字节
        QByteArray channeldata{};
        int channel= 0;
        channeldata.append(data.at(24)).append(data.at(25));
        channel=  channeldata.toHex().toInt(nullptr,16);
        setChannel(channel);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}
