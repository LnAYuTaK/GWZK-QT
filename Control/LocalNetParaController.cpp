
#include "LocalNetParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"

LocalNetParaController::LocalNetParaController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->LocalNetParaSet())
    ,localIp1_("")
    ,localGateway1_("")
    ,localMask1_("")
    ,localMACAddr1_("")
    ,localIp2_("")
    ,localGateway2_("")
    ,localMask2_("")
    ,localMACAddr2_("")
    ,localWifiName_("")
{

}

void LocalNetParaController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::LocalNetParaController_t,start,adressVector.count());
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

void LocalNetParaController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
        if(data.size()==48)
        {
            //本地IP地址1
            localIp1_ = QString::number(QChar(data.at(0)).unicode())
                        +"."
                        + QString::number(QChar(data.at(1)).unicode())
                        +"."
                        + QString::number(QChar(data.at(2)).unicode())
                        +"."
                        + QString::number(QChar(data.at(3)).unicode());
            qDebug() << localIp1_;
            //本地IP网关地址1
            localGateway1_ =   QString::number(QChar(data.at(4)).unicode())
                             +"."
                             + QString::number(QChar(data.at(5)).unicode())
                             +"."
                             + QString::number(QChar(data.at(6)).unicode())
                             +"."
                             + QString::number(QChar(data.at(7)).unicode());
            qDebug() << localGateway1_;
            //子网掩码1
            localMask1_ =   QString::number(QChar(data.at(8)).unicode())
                          +"."
                          + QString::number(QChar(data.at(9)).unicode())
                          +"."
                          + QString::number(QChar(data.at(10)).unicode())
                          +"."
                          + QString::number(QChar(data.at(11)).unicode());
            qDebug() << localMask1_;
            //本地IPMAC地址1
            localMACAddr1_ =   QString::number(QChar(data.at(12)).unicode())
                             +":"
                             + QString::number(QChar(data.at(13)).unicode())
                             +":"
                             + QString::number(QChar(data.at(14)).unicode())
                             +":"
                             + QString::number(QChar(data.at(15)).unicode())
                             +":"
                             + QString::number(QChar(data.at(16)).unicode())
                             +":"
                             + QString::number(QChar(data.at(17)).unicode());
            qDebug() << localMACAddr1_;

            QString localIp2_  = QString::number(QChar(data.at(18)).unicode())
                                +"."
                                + QString::number(QChar(data.at(19)).unicode())
                                +"."
                                + QString::number(QChar(data.at(20)).unicode())
                                +"."
                                + QString::number(QChar(data.at(21)).unicode());
            qDebug() << localIp2_;
            //本地IP网关地址1
            localGateway2_=   QString::number(QChar(data.at(22)).unicode())
                             +"."
                             + QString::number(QChar(data.at(23)).unicode())
                             +"."
                             + QString::number(QChar(data.at(24)).unicode())
                             +"."
                             + QString::number(QChar(data.at(25)).unicode());
            qDebug() << localGateway2_;
            //子网掩码1
            localMask2_ =   QString::number(QChar(data.at(26)).unicode())
                          +"."
                          + QString::number(QChar(data.at(27)).unicode())
                          +"."
                          + QString::number(QChar(data.at(28)).unicode())
                          +"."
                          + QString::number(QChar(data.at(29)).unicode());
            qDebug() << localMask2_;
            //本地IPMAC地址1
            localMACAddr2_=   QString::number(QChar(data.at(30)).unicode())
                             +":"
                             + QString::number(QChar(data.at(31)).unicode())
                             +":"
                             + QString::number(QChar(data.at(32)).unicode())
                             +":"
                             + QString::number(QChar(data.at(33)).unicode())
                             +":"
                             + QString::number(QChar(data.at(34)).unicode())
                             +":"
                             + QString::number(QChar(data.at(35)).unicode());
            qDebug() << localMACAddr2_;
            //八个字符添加到
            auto i = 8;
            QByteArray wifiBytes{};
            while(i--)
            {
                wifiBytes.prepend(data.at(36+i));
            }
            localWifiName_  = QString::fromUtf8(wifiBytes);
        }
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}














