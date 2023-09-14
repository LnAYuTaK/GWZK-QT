
#include "EnvParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"
#include <QVector>

EnvPara::EnvPara(int type,JsonFactGroup *regList)
    :type_(type)
    ,regList_(regList)
    ,upThresholdLimitLevel1_("")
    ,lowThresholdLimitLevel1_("")
    ,upThresholdLimitLevel2_("")
    ,lowThresholdLimitLevel2_("")
    ,upThresholdLimitLevel3_("")
    ,lowThresholdLimitLevel3_("")
    ,keepThresholdLimit_("")
{
}

void EnvPara::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        ProtocolManager::ControllerType type;
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        switch (type_) {
        case 0:
            type = ProtocolManager::ControllerType::EnvTempController_t;
           break;
        case 1:
            type = ProtocolManager::ControllerType::EnvHumidityController_t;
            break;
        case 2:
            type = ProtocolManager::ControllerType::EnvWaterLevelController_t;
            break;
        default:
            return;
        }
        auto sendMsg = ProtocolManager::makeReadRegProto(type,start,adressVector.size());
        //qDebug()<< adressVector.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void EnvPara::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        int multiple  = 1;
        switch (type_) {
        case 0:
            //温度放大100倍
            multiple = 100* multiple;
            break;
        case 1:
            //湿度放大10倍
            multiple = 10* multiple;
            break;
        case 2:
            //液位放大10倍
            multiple = 10* multiple;
            break;
        default:
            return;
        }
        auto adressVector  = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //报警阈值上限等级1 2字节
        auto uplimit1  = ProtocolManager::intToHexByteArray(upThresholdLimitLevel1_.toFloat()*multiple);
        //报警阈值下限等级1 2字节
        auto lowlimit1 = ProtocolManager::intToHexByteArray(lowThresholdLimitLevel1_.toFloat()*multiple);
        //报警阈值上限等级2 2字节
        auto uplimit2  = ProtocolManager::intToHexByteArray(upThresholdLimitLevel2_.toFloat()*multiple);
        //报警阈值下限等级2 2字节
        auto lowlimit2 = ProtocolManager::intToHexByteArray(lowThresholdLimitLevel2_.toFloat()*multiple);
        //报警阈值上限等级3 2字节
        auto uplimit3  = ProtocolManager::intToHexByteArray(upThresholdLimitLevel3_.toFloat()*multiple);
        //报警阈值下限等级3 2字节
        auto lowlimit3 = ProtocolManager::intToHexByteArray(lowThresholdLimitLevel3_.toFloat()*multiple);
        //防抖阈值 2字节
        auto keeplimit = ProtocolManager::intToHexByteArray(keepThresholdLimit_.toFloat()*multiple);
        //备用字节 4字节
        QByteArray standby(4, '\x00');
        //数据包共 16字节
        QByteArray packData = uplimit1 +
                              lowlimit1 +
                              uplimit2 +
                              lowlimit2 +
                              uplimit3 +
                              lowlimit3 +
                              keeplimit +
                              standby;
        qDebug()  <<"EnvParaController Pack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.size(),packData);
        qDebug() << "EnvParaController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}


EnvParaController::EnvParaController(QObject *parent)
    : QObject{parent}
    ,envTemp_(new EnvPara(Temp,app()->paraFactMgr()->EnvParaTemp()))
    ,envHumidity_(new EnvPara(Humidity,app()->paraFactMgr()->EnvParaHumidity()))
    ,envWaterLevel_(new EnvPara(WaterLevel,app()->paraFactMgr()->EnvParaWaterLevel()))
{
   qmlRegisterUncreatableType<EnvPara>   ("App.ProtocolManager", 1, 0,"EnvPara","Reference only");
}

void EnvParaController::queryData(EnvType type)
{
    switch (type) {
    case Temp:
        envTemp_->queryData();
       break;
    case Humidity:
       envHumidity_->queryData();
       break;
    case WaterLevel:
       envWaterLevel_->queryData();
       break;
    default:
        break;
    }
}
void EnvParaController::setData(EnvType type)
{
    switch (type) {
    case Temp:
        envTemp_->setData();
        break;
    case Humidity:
        envHumidity_->setData();
        break;
    case WaterLevel:
        envWaterLevel_->setData();
        break;
    default:
        break;
    }
}

//设备发送
void EnvParaController::recvSeleteType(EnvType type,EnvPara *target,QByteArray data)
{
    auto resdata = ProtocolManager::SpiltData(data);
    short bit =  ProtocolManager::bytesToshort(resdata[1],ProtocolManager::LittileEndian);
    qDebug() << QString::number((bit/100.0),'f',2);
    if(resdata.size()==9)
    {
        short upLim1 =  ProtocolManager::bytesToshort(resdata[0],ProtocolManager::LittileEndian);
        short lowLim1 =  ProtocolManager::bytesToshort(resdata[1],ProtocolManager::LittileEndian);
        short upLim2=  ProtocolManager::bytesToshort(resdata[2],ProtocolManager::LittileEndian);
        short lowLim2=  ProtocolManager::bytesToshort(resdata[3],ProtocolManager::LittileEndian);
        short upLim3 =  ProtocolManager::bytesToshort(resdata[4],ProtocolManager::LittileEndian);
        short lowLim3 =  ProtocolManager::bytesToshort(resdata[5],ProtocolManager::LittileEndian);
        short keep =  ProtocolManager::bytesToshort(resdata[6],ProtocolManager::LittileEndian);
        switch (type) {
        case Temp:
            //保留一位小数
            envTemp_->setUpThresholdLimitLevel1(
                QString::number(
                    (upLim1/100.0),'f',2)
                );
            envTemp_->setLowThresholdLimitLevel1(
                QString::number(
                    (lowLim1/100.0),'f',2)
                );
            envTemp_->setUpThresholdLimitLevel2(
                QString::number(
                   (upLim2/100.0),'f',2)
                );
            envTemp_->setLowThresholdLimitLevel2(
                QString::number(
                   (lowLim2/100.0),'f',2)
                );
            envTemp_->setUpThresholdLimitLevel3(
                QString::number(
                   (upLim3/100.0),'f',2)
                );
            envTemp_->setLowThresholdLimitLevel3(
                QString::number(
                   (lowLim3/100.0),'f',2)
                );
            envTemp_->setKeepThresholdLimit(
                QString::number(
                   (keep/100.0),'f',2)
                );
            break;
        case Humidity:
            envHumidity_->setUpThresholdLimitLevel1(
                QString::number(
                    resdata[0].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envHumidity_->setLowThresholdLimitLevel1(
                QString::number(
                    resdata[1].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envHumidity_->setUpThresholdLimitLevel2(
                QString::number(
                    resdata[2].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envHumidity_->setLowThresholdLimitLevel2(
                QString::number(
                    resdata[3].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envHumidity_->setUpThresholdLimitLevel3(
                QString::number(
                    resdata[4].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envHumidity_->setLowThresholdLimitLevel3(
                QString::number(
                    resdata[5].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envHumidity_->setKeepThresholdLimit(
                QString::number(
                    resdata[6].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
                break;
        case WaterLevel:
            envWaterLevel_->setUpThresholdLimitLevel1(
                QString::number(
                    resdata[0].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envWaterLevel_->setLowThresholdLimitLevel1(
                QString::number(
                    resdata[1].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envWaterLevel_->setUpThresholdLimitLevel2(
                QString::number(
                    resdata[2].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envWaterLevel_->setLowThresholdLimitLevel2(
                QString::number(
                    resdata[3].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envWaterLevel_->setUpThresholdLimitLevel3(
                QString::number(
                    resdata[4].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envWaterLevel_->setLowThresholdLimitLevel3(
                QString::number(
                    resdata[5].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            envWaterLevel_->setKeepThresholdLimit(
                QString::number(
                    resdata[6].toHex().toInt(nullptr,16)/10.0,'f',1)
                );
            break;
        default:
            break;
        }
    }
}

//处理接收
void EnvParaController::handleRecvTemp(ProtocolManager::ReccType type,QByteArray data)
{
    //读返回
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(Temp,envTemp_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        qDebug() << "Handle Write: "<< data;
    }
}

void EnvParaController::handleRecvHumidity(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(Humidity,envHumidity_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        qDebug() << "Handle Write: "<< data;
    }
}

void EnvParaController::handleRecvWaterLevel(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
       recvSeleteType(WaterLevel,envWaterLevel_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}




