
#include "TunnelGasData.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"
TunnelGasData::TunnelGasData(QObject *parent)
     : QObject{parent}
    ,regList_(regList_= app()->paraFactMgr()->TunnelGasData())
{

}

void TunnelGasData::queryData()
{
   if(app()->netWorkMgr()->IsTcpConnected())
   {
       auto adressVector  = regList_->getAddress();
       QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
       auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::TunnelGasData_t,start,adressVector.count());
       app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
   }
}

void TunnelGasData::handleRecv(ProtocolManager::ReccType type,QByteArray data)
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

