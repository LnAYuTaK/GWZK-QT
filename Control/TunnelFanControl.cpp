
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
    ,address_("00000000000000000")
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
        //地址
        QByteArray byteArray =QByteArray(address_.toUtf8())+QByteArray::fromHex("00");
        //格式
        auto formatData = ProtocolManager::intToHexByteArray(format_);
        //数量
        auto countData = ProtocolManager::intToHexByteArray(count_);
        auto adressVector = regList_->getAddress();
        //起始地址
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //备用字节
        QByteArray standby{3,0};

        QByteArray data = byteArray +
                          formatData +
                          countData +
                          standby;

        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),data);

        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}
