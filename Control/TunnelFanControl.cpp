
#include "TunnelFanControl.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

TunnelFanControl::TunnelFanControl(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->TunnelFan())
    ,count_(0)
    ,format_(0)
    ,address_("0000000000000000")
{

}

void TunnelFanControl::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void TunnelFanControl::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //地址 17字节
        QByteArray addressData = QByteArray(address_.toUtf8())+QByteArray(1, '\x00');
        //格式 2字节
        auto formatData = ProtocolManager::intToHexByteArray(format_);
        //数量 2字节
        auto countData = ProtocolManager::intToHexByteArray(count_);
        //备用字节 4字节
        QByteArray standby{4, '\x00'};
        //数据包总共25字节
        QByteArray packData = addressData +
                          formatData +
                          countData +
                          standby;
        qDebug() << "TunnelFanControl SendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(), packData);
        qDebug() << "TunnelFanControl SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}
