
#include "TunnelFanDevControl.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/NetWorkManager.h"

TunnelFanDevControl::TunnelFanDevControl(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->TunnelFan())
    ,count_(0)
    ,format_("递增")
    ,address_("")
{

}

void TunnelFanDevControl::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::TunnelFanDevControl_t,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void TunnelFanDevControl::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //地址 17字节
        QByteArray addressData = QByteArray(address_.toUtf8())+QByteArray(1, '\x00');
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
        //备用字节 4字节
        QByteArray standby(4, '\x00');
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

void TunnelFanDevControl::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
       //风机ID 地址 18 字节
        QByteArray address = data.left(18);
        setAddress(QString::fromUtf8(address));
        //ID地址格式 2字节
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
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}
