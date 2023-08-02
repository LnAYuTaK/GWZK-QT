
#include "LocalNetParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

LocalNetParaController::LocalNetParaController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->LocalNetParaSet())
    ,localIp1_("0.0.0.0")
    ,localGateway1_("0.0.0.0")
    ,localMask1_("255.255.255.0")
    ,localMACAddr1_("00-00-00-00-00-00")
    ,localIp2_("0.0.0.0")
    ,localGateway2_("0.0.0.0")
    ,localMask2_("255.255.255.0")
    ,localMACAddr2_("00-00-00-00-00-00")
{

}
//先暂时做一个只分割不校验
 QByteArray LocalNetParaController::ParseNetLocalString(ParaType type,QString paraStr)
 {
    QByteArray res{};
     switch (type) {
     case Ip:
     {
        auto ipList = paraStr.split(".");
        for(auto str:ipList){
            res += QByteArray(str.toUtf8());
        }
     }
     break;
     case Gateway:
     {
        auto gatewayList = paraStr.split(".");
        for(auto str:gatewayList){
            res += QByteArray(str.toUtf8());
        }
     }
    break;
    case Mask:
    {
        auto maskList = paraStr.split(".");
        for(auto str:maskList){
            res += QByteArray(str.toUtf8());
        }
    }
    break;
    case MACAddr:
    {
        auto maskList = paraStr.split("-");
        for(auto str:maskList){
            res += QByteArray(str.toUtf8());
        }
    }
    break;
    }
    qDebug() << res;
    return res;
}


void LocalNetParaController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(start,adressVector.count());
        qDebug() << sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void LocalNetParaController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //IP1地址 4个字节
        auto ipAdd1Data   = ParseNetLocalString(ParaType::Ip,localIp1_);
        //网关地址 4字节
        auto gateway1Data = ParseNetLocalString(ParaType::Gateway,localGateway1_);
        //子网掩码地址 4字节
        auto mask1Data    = ParseNetLocalString(ParaType::Gateway,localMask1_);
        //IPMA地址 6字节
        auto macAddr1Data  = ParseNetLocalString(ParaType::MACAddr,localMACAddr1_);
        //IP1地址 4个字节
        auto ipAdd2Data   = ParseNetLocalString(ParaType::Ip,localIp2_);
        //网关地址 4字节
        auto gateway2Data = ParseNetLocalString(ParaType::Gateway,localGateway2_);
        //子网掩码地址 4字节
        auto mask2Data    = ParseNetLocalString(ParaType::Gateway,localMask2_);
        //IPMA地址 6字节
        auto macAddr2Data  = ParseNetLocalString(ParaType::MACAddr,localMACAddr2_);
        //备用字节12个
        QByteArray standby(12,'\x00');
        //数据包总共 48
        QByteArray packData = ipAdd1Data+
                              gateway1Data+
                              mask1Data+
                              macAddr1Data+
                              ipAdd2Data+
                              gateway2Data+
                              mask2Data+
                              macAddr2Data+
                              standby;
        qDebug() << "LocalNetParaController SendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "MainParaController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}















