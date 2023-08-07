
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
    ,localWifiName_("")
{

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
        auto ipAdd1Data   =  ProtocolManager::ParseNetLocalString(ProtocolManager::Ip,localIp1_);
        //网关地址 4字节
        auto gateway1Data =  ProtocolManager::ParseNetLocalString(ProtocolManager::Gateway,localGateway1_);
        //子网掩码地址 4字节
        auto mask1Data    =  ProtocolManager::ParseNetLocalString(ProtocolManager::Mask,localMask1_);
        //IP1MAC地址 6字节
        QByteArray ip1Mac(6,'\x00');
        //IP1地址 4个字节
        auto ipAdd2Data   =  ProtocolManager::ParseNetLocalString(ProtocolManager::Ip,localIp2_);
        //网关地址 4字节
        auto gateway2Data =  ProtocolManager::ParseNetLocalString(ProtocolManager::Gateway,localGateway2_);
        //子网掩码地址 4字节
        auto mask2Data    =  ProtocolManager::ParseNetLocalString(ProtocolManager::Mask,localMask2_);
        //IPMAC地址 6字节(暂时不需要)
        QByteArray ip2Mac(6,'\x00');
//        auto macAddr2Data  = ProtocolManager::ParseNetLocalString(ProtocolManager::MACAddr,localMACAddr2_);
        //wifi名 8字节(不够自动补0)
        QByteArray wifiNameSource = localWifiName_.toLatin1();
        QByteArray wifiName(8,'\x00');
        wifiName.replace(0,wifiNameSource.size(),wifiNameSource);
        //备用字节12个
        QByteArray standby(12,'\x00');
        //数据包总共 56
        QByteArray packData = ipAdd1Data+
                              gateway1Data+
                              mask1Data+
                              ip1Mac +
                              ipAdd2Data+
                              gateway2Data+
                              mask2Data+
                              ip2Mac +
                              wifiName +
                              standby;
//        qDebug() <<  ipAdd1Data.size() << " " << gateway1Data.size() << " " << mask1Data.size() <<" "
//                 <<  ip1Mac.size() << " " << ipAdd2Data.size() << " " << gateway2Data.size()<<  " "
//                 << mask2Data.size() << " " << ip2Mac.size() << " " <<  wifiName.size() << " "<<standby.size();
        qDebug() << "LocalNetPara PackData Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "LocalNetPara SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}















