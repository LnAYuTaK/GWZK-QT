
#include "TunnelGasMonitor.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

TunnelGasMonitor::TunnelGasMonitor(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->TunnelGas())
    ,count_(0)
    ,cycle_(0)
    ,channel_(0)
    ,format_(0)
    ,address_("00000000000000000")
{

}

void TunnelGasMonitor::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void TunnelGasMonitor::setData()
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
        QByteArray standby{6, '\x00'};
        //数据包总共 31字节
        QByteArray packData  = byteArray +
                          formatData +
                          countData +
                          cycleData +
                          channelData +
                          standby;
        qDebug() << "TunnelGasMonitor SendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "TunnelGasMonitor SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}





