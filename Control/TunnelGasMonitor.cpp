
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
        //地址
        QByteArray byteArray =QByteArray(address_.toUtf8())+QByteArray::fromHex("00");
        //格式
        auto formatData = ProtocolManager::intToHexByteArray(format_);
        //数量
        auto countData = ProtocolManager::intToHexByteArray(count_);
        //周期
        auto cycleData = ProtocolManager::intToHexByteArray(cycle_);
        //通道
        auto channelData = ProtocolManager::intToHexByteArray(channel_);

        auto adressVector = regList_->getAddress();
        //起始地址
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        QByteArray data = byteArray +
                          formatData +
                          countData +
                          cycleData +
                          channelData +
                          ProtocolManager::intToHexByteArray(0)+
                          ProtocolManager::intToHexByteArray(0)+
                          ProtocolManager::intToHexByteArray(0);
//                          qDebug() << byteArray << " "
//                                   << formatData << " "
//                                   << countData << " "
//                                   << cycleData << " "
//                                   << channelData << " "
//                                   <<  ProtocolManager::intToHexByteArray(0);
//        app()->netWorkMgr()->_tcpWriteBytes(data);
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),data);

        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}





