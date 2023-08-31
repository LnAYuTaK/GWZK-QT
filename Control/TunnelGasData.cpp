
#include "TunnelGasData.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"

TunnelGas::TunnelGas(QObject *parent)
    : QObject{parent}
{

}

TunnelGasData::TunnelGasData(QObject *parent)
     : QObject{parent}
    ,regList_(regList_= app()->paraFactMgr()->TunnelGasData())
    ,GasO2_(new TunnelGas(this))
    ,GasCO_(new TunnelGas(this))
    ,GasCl2_(new TunnelGas(this))
    ,GasH2S_(new TunnelGas(this))
    ,GasH2_(new TunnelGas(this))
    ,GasCO2_(new TunnelGas(this))
    ,GasCH4_(new TunnelGas(this))
    ,EnvTemp_(new TunnelGas(this))
    ,EnvHumi_(new TunnelGas(this))
{
 qmlRegisterUncreatableType<TunnelGas>   ("App.ProtocolManager", 1, 0,"TunnelGas","Reference only");
}

void TunnelGasData::queryData()
{
   if(app()->netWorkMgr()->IsTcpConnected()){
       auto adressVector  = regList_->getAddress();
       QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
       auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::TunnelGasData_t,start,adressVector.count());
       app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
   }
}

//设置
void TunnelGasData::setData()
{

}

void TunnelGasData::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
   if(type == ProtocolManager::HandleRead) {
       //含量数据
       QByteArray O2Bytes= QByteArray().append(data.at(0)).append(data.at(1));
       int O2Data  =  O2Bytes.toHex().toInt(nullptr,16);
       this->GasO2_->setRawData(O2Data);
       //qDebug() << O2Data;

       QByteArray COBytes= QByteArray().append(data.at(2)).append(data.at(3));
       int COData  = COBytes.toHex().toInt(nullptr,16);
       this->GasCO_->setRawData(COData);
       //qDebug() << COData;

       QByteArray Cl2Bytes= QByteArray().append(data.at(4)).append(data.at(5));
       int Cl2Data = Cl2Bytes.toHex().toInt(nullptr,16);
       this->GasCl2_->setRawData(Cl2Data);
       //qDebug() << Cl2Data;

       QByteArray H2SBytes= QByteArray().append(data.at(6)).append(data.at(7));
       int H2SData = H2SBytes.toHex().toInt(nullptr,16);
       this->GasH2S_->setRawData(H2SData);
       //qDebug() <<  H2SData;

       QByteArray H2Bytes= QByteArray().append(data.at(8)).append(data.at(9));
       int H2Data = H2Bytes.toHex().toInt(nullptr,16);
       this->GasH2_->setRawData(H2Data);
       //qDebug() <<  H2Data;

       QByteArray CO2Bytes= QByteArray().append(data.at(10)).append(data.at(11));
       int CO2Data = CO2Bytes.toHex().toInt(nullptr,16);
       this->GasCO2_->setRawData(CO2Data);
       //qDebug() <<  CO2Data;

       QByteArray CH4Bytes= QByteArray().append(data.at(12)).append(data.at(13));
       int CH4Data = CH4Bytes.toHex().toInt(nullptr,16);
       this->GasCH4_->setRawData(CH4Data);
       //qDebug() <<  CH4Data;

       QByteArray TempBytes= QByteArray().append(data.at(14)).append(data.at(15));
       int TempData = TempBytes.toHex().toInt(nullptr,16);
       this->EnvTemp_->setRawData(TempData);
       //qDebug() << TempData;

       QByteArray HumiBytes= QByteArray().append(data.at(16)).append(data.at(17));
       int HumiData = HumiBytes.toHex().toInt(nullptr,16);
       this->EnvHumi_->setRawData(HumiData);
       //qDebug() << HumiData;

       //O2/CO/Cl2/H2S/H2/CO2/CH4报警等级 2字节 1819 20 21 22 23
       short leveldata =  ProtocolManager::CharsToShort(data.at(24),data.at(25));
       //温度湿度报警等级 2字节
       int O2Level = ProtocolManager::mergeBits(ProtocolManager::getShortBitValue(leveldata ,1),
                                                ProtocolManager::getShortBitValue(leveldata ,0));
       this->GasO2_->setAlarmLevel(O2Level);
       //qDebug()<< "O2Level: "<< O2Level;

       int COLevel = ProtocolManager::mergeBits(ProtocolManager::getShortBitValue(leveldata ,3),
                                                ProtocolManager::getShortBitValue(leveldata ,2));
       this->GasCO_->setAlarmLevel(COLevel);
       //qDebug() << "COLevel: " << COLevel;

       int Cl2Level = ProtocolManager::mergeBits(ProtocolManager::getShortBitValue(leveldata ,5),
                                                ProtocolManager::getShortBitValue(leveldata ,4));
       this->GasCl2_->setAlarmLevel(Cl2Level);
       //qDebug() << "Cl2Level: " << Cl2Level;

       int H2SLevel = ProtocolManager::mergeBits(ProtocolManager::getShortBitValue(leveldata ,7),
                                                 ProtocolManager::getShortBitValue(leveldata ,6));
       this->GasH2S_->setAlarmLevel(H2SLevel);
       //qDebug() << "H2SLevel: " << H2SLevel;

       int H2Level = ProtocolManager::mergeBits(ProtocolManager::getShortBitValue(leveldata ,9),
                                                 ProtocolManager::getShortBitValue(leveldata ,8));
       this->GasH2_->setAlarmLevel(H2Level);
       //qDebug() << "H2Level: " << H2Level;

       int CO2Level = ProtocolManager::mergeBits(ProtocolManager::getShortBitValue(leveldata ,11),
                                                ProtocolManager::getShortBitValue(leveldata ,10));
       this->GasCO2_->setAlarmLevel(CO2Level);
       //qDebug() << "CO2Level: " << CO2Level;

       int CH4Level = ProtocolManager::mergeBits(ProtocolManager::getShortBitValue(leveldata ,13),
                                                ProtocolManager::getShortBitValue(leveldata ,12));
       this->GasCH4_->setAlarmLevel(CH4Level);
       //qDebug() << "CH4Leve0l: " << CH4Level;

       short envdata =  ProtocolManager::CharsToShort(data.at(26),data.at(27));
       //环境温度,湿度等级
       int TempLevel = ProtocolManager::mergeBits( ProtocolManager::getShortBitValue(envdata,1),
                                                  ProtocolManager::getShortBitValue(envdata ,0));
       this->EnvTemp_->setAlarmLevel(TempLevel);
       //qDebug() << "TempLevel: " << TempLevel;
       int HumiLevel = ProtocolManager::mergeBits(ProtocolManager::getShortBitValue(envdata ,3),
                                                  ProtocolManager::getShortBitValue(envdata ,2));
       this->EnvHumi_->setAlarmLevel(HumiLevel);
       //qDebug() << "HumiLevel: " << HumiLevel;
       //数据使能

   }
   else if(type == ProtocolManager::HandleWrite) {
       //
       qDebug() << "Handle Write: "<< data;
   }
}

