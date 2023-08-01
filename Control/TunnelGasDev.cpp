
#include "TunnelGasDev.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"
TunnelGasDev::TunnelGasDev(QObject *parent)
     : QObject{parent}
    ,regList_(nullptr)
{
   regList_= app()->paraFactMgr()->TunnelGasData();
}

void TunnelGasDev::queryData()
{
   if(app()->netWorkMgr()->IsTcpConnected())
   {
       auto adressVector  = regList_->getAddress();
       QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
       auto sendMsg = ProtocolManager::makeReadRegProto(start,adressVector.count());
       app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
   }
}



