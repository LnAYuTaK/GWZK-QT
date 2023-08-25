﻿
#include "TunnelFanDevControl.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"
TunnelFanDevControl::TunnelFanDevControl(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->TunnelFan())
    ,count_(0)
    ,format_(0)
    ,address_("0000000000000000")
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
        auto formatData = ProtocolManager::intToHexByteArray(format_);
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
        qDebug() << data.size();
        qDebug() << data;
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}