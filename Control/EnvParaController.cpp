
#include "EnvParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/Utils.h"
#include "appSrc/NetWorkManager.h"
#include <QVector>

EnvPara::EnvPara(int type,JsonFactGroup *regList)
    :type_(type)
    ,regList_(regList)
    ,upThresholdLimitLevel1_(0)
    ,lowThresholdLimitLevel1_(0)
    ,upThresholdLimitLevel2_(0)
    ,lowThresholdLimitLevel2_(0)
    ,upThresholdLimitLevel3_(0)
    ,lowThresholdLimitLevel3_(0)
    ,keepThresholdLimit_(0)
{
    qmlRegisterUncreatableType<EnvPara>   ("App.ProtocolManager", 1, 0,"EnvPara","Reference only");
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
        auto sendMsg = ProtocolManager::makeReadRegProto(type,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void EnvPara::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //报警阈值上限等级1 2字节
        auto uplimit1  = ProtocolManager::intToHexByteArray(upThresholdLimitLevel1_);
        //报警阈值下限等级1 2字节
        auto lowlimit1 = ProtocolManager::intToHexByteArray(lowThresholdLimitLevel1_);
        //报警阈值上限等级2 2字节
        auto uplimit2  = ProtocolManager::intToHexByteArray(upThresholdLimitLevel2_);
        //报警阈值下限等级2 2字节
        auto lowlimit2 = ProtocolManager::intToHexByteArray(lowThresholdLimitLevel2_);
        //报警阈值上限等级3 2字节
        auto uplimit3  = ProtocolManager::intToHexByteArray(upThresholdLimitLevel3_);
        //报警阈值下限等级3 2字节
        auto lowlimit3 = ProtocolManager::intToHexByteArray(lowThresholdLimitLevel3_);
        //防抖阈值 2字节
        auto keeplimit = ProtocolManager::intToHexByteArray(keepThresholdLimit_);
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
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
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

    if(resdata.size()==9)
    {
        switch (type) {
        case Temp:
            qDebug()<< data;
            envTemp_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
            envTemp_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
            envTemp_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
            envTemp_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
            envTemp_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
            envTemp_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
            envTemp_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
            envTemp_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
            break;
        case Humidity:
           envHumidity_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
           envHumidity_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
           envHumidity_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
           envHumidity_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
           envHumidity_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
           envHumidity_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
           envHumidity_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
           envHumidity_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
           break;
        case WaterLevel:
           envWaterLevel_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
           envWaterLevel_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
           envWaterLevel_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
           envWaterLevel_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
           envWaterLevel_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
           envWaterLevel_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
           envWaterLevel_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
           envWaterLevel_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
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
        // 将QByteArray拆分成两个一组的QByteArray
        recvSeleteType(Temp,envTemp_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        qDebug() << "Handle Write: "<< data;
    }
}

void EnvParaController::handleRecvHumidity(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
        QByteArray datares = data;
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




