
#include "TunnelGasData.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"

TunnelGas::TunnelGas(QObject *parent)
    : QObject{parent}
    ,rawData_("")
    ,alarmLevel_("")
    ,enable_(1)
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
   //数据使能//
}

void TunnelGasData::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
   if(type == ProtocolManager::HandleRead) {

       QByteArray O2Bytes= QByteArray().append(data.at(0)).append(data.at(1));
       float O2Data =  O2Bytes.toHex().toInt(nullptr,16);
       QString O2str= QString::number(O2Data/100, 'f', 2);
       this->GasO2_->setRawData(O2str);
       //qDebug() << O2Data;

       QByteArray COBytes= QByteArray().append(data.at(2)).append(data.at(3));
       float COData  = COBytes.toHex().toInt(nullptr,16);
       QString COstr= QString::number(COData/100, 'f', 2);
       this->GasCO_->setRawData(COstr);
       //qDebug() << COData;

       QByteArray Cl2Bytes= QByteArray().append(data.at(4)).append(data.at(5));
       float Cl2Data = Cl2Bytes.toHex().toInt(nullptr,16);
       QString Cl2str= QString::number(Cl2Data/100, 'f', 2);
       this->GasCl2_->setRawData(Cl2str);
       //qDebug() << Cl2Data;

       QByteArray H2SBytes= QByteArray().append(data.at(6)).append(data.at(7));
       float H2SData = H2SBytes.toHex().toInt(nullptr,16);
       QString H2Sstr= QString::number(H2SData/100, 'f', 2);
       this->GasH2S_->setRawData(H2Sstr);
       //qDebug() <<  H2SData;

       QByteArray H2Bytes= QByteArray().append(data.at(8)).append(data.at(9));
       float H2Data = H2Bytes.toHex().toInt(nullptr,16);
       QString  H2str= QString::number(H2Data/100, 'f', 2);
       this->GasH2_->setRawData(H2str);
       //qDebug() <<  H2Data;

       QByteArray CO2Bytes= QByteArray().append(data.at(10)).append(data.at(11));
       float CO2Data = CO2Bytes.toHex().toInt(nullptr,16);
       QString  CO2str= QString::number(CO2Data /100, 'f', 2);
       this->GasCO2_->setRawData(CO2str);
       //qDebug() <<  CO2Data;

       QByteArray CH4Bytes= QByteArray().append(data.at(12)).append(data.at(13));
       float CH4Data = CH4Bytes.toHex().toInt(nullptr,16);
       QString  CH4str= QString::number(CH4Data /100, 'f', 2);
       this->GasCH4_->setRawData(CH4str);
       //qDebug() <<  CH4Data;

       QByteArray TempBytes= QByteArray().append(data.at(14)).append(data.at(15));
       float TempData = TempBytes.toHex().toInt(nullptr,16);
       QString  Tempstr= QString::number(TempData /100, 'f', 2);
       this->EnvTemp_->setRawData(Tempstr);
       //qDebug() << TempData;

       QByteArray HumiBytes= QByteArray().append(data.at(16)).append(data.at(17));
       float HumiData = HumiBytes.toHex().toInt(nullptr,16);
       QString  Humistr= QString::number(HumiData /10, 'f', 1);
       this->EnvHumi_->setRawData(Humistr);
       //O2/CO/Cl2/H2S/H2/CO2/CH4报警等级 2字节 18 19 20 21 22 23
       QByteArray levelBytes {};
       levelBytes.append(data.at(24)).append(data.at(25));
       short res = ProtocolManager::bytesToshort(levelBytes,ProtocolManager::LittileEndian);
       QVector<bool> boolVector;
       // 遍历short类型数据的每个位
       for (int i = 0; i < sizeof(short) * 8; i++) {
           // 获取当前位的值，并将其存入boolVector中
           bool bit = res & (1 << i);
           boolVector.append(bit);
           qDebug() << bit;
       }
       //O2
       int O2Level = ProtocolManager::mergeBits(boolVector.at(15),boolVector.at(14));
       this->GasO2_->setAlarmLevel(QString::number(O2Level));
       qDebug()<< "O2Level: "<< O2Level;
       //CO
       int COLevel = ProtocolManager::mergeBits(boolVector.at(13),boolVector.at(12));
       this->GasCO_->setAlarmLevel(QString::number(COLevel));
       qDebug() << "COLevel: " << COLevel;
       //Cl2
       int Cl2Level = ProtocolManager::mergeBits(boolVector.at(11),boolVector.at(10));
       this->GasCl2_->setAlarmLevel(QString::number(Cl2Level));
       qDebug() << "Cl2Level: " << Cl2Level;
       //H2S
       int H2SLevel = ProtocolManager::mergeBits(boolVector.at(9),boolVector.at(8));
       this->GasH2S_->setAlarmLevel(QString::number(H2SLevel));
       qDebug() << "H2SLevel: " << H2SLevel;
       //H2
       int H2Level = ProtocolManager::mergeBits(boolVector.at(7),boolVector.at(6));
       this->GasH2_->setAlarmLevel(QString::number(H2Level));
       qDebug() << "H2Level: " << H2Level;
       //CO
       int CO2Level = ProtocolManager::mergeBits(boolVector.at(5),boolVector.at(4));
       this->GasCO2_->setAlarmLevel(QString::number(CO2Level));
       qDebug() << "CO2Level: " << CO2Level;
       //CH4
       int CH4Level = ProtocolManager::mergeBits(boolVector.at(3),boolVector.at(2));
       this->GasCH4_->setAlarmLevel(QString::number(CH4Level));
       qDebug() << "CH4Leve0l: " << CH4Level;
       QByteArray EnvBytes {};
       EnvBytes.append(data.at(26)).append(data.at(27));

       short envRes = ProtocolManager::bytesToshort(EnvBytes,ProtocolManager::LittileEndian);
       QVector<bool> envBoolVector;
       // 遍历short类型数据的每个位
       for (int i = 0; i < sizeof(short) * 8; i++) {
           // 获取当前位的值，并将其存入boolVector中
           bool bit = envRes & (1 << i);
           envBoolVector.append(bit);
        }
//       //环境温度,湿度等级
       int TempLevel = ProtocolManager::mergeBits(envBoolVector.at(15),envBoolVector.at(14));
       this->EnvTemp_->setAlarmLevel(QString::number(TempLevel));
       qDebug() << "TempLevel: " << TempLevel;

       int HumiLevel = ProtocolManager::mergeBits(envBoolVector.at(13),envBoolVector.at(12));
       this->EnvHumi_->setAlarmLevel(QString::number(HumiLevel));
       qDebug() << "HumiLevel: " << HumiLevel;
       //数据使能
   }
   else if(type == ProtocolManager::HandleWrite) {
       //
       qDebug() << "Handle Write: "<< data;
   }
}

