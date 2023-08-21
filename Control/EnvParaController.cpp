
#include "EnvParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

EnvParaController::EnvParaController(QObject *parent)
    : QObject{parent}
    ,TempRegList_(app()->paraFactMgr()->EnvParaTemp())
    ,HumidityRegList_(app()->paraFactMgr()->EnvParaHumidity())
    ,WaterLevelRegList_(app()->paraFactMgr()->EnvParaWaterLevel())
    ,upThresholdLimitLevel1_(0)
    ,lowThresholdLimitLevel1_(0)
    ,upThresholdLimitLevel2_(0)
    ,lowThresholdLimitLevel2_(0)
    ,upThresholdLimitLevel3_(0)
    ,lowThresholdLimitLevel3_(0)
    ,keepThresholdLimit_(0)
{

}

void EnvParaController::queryData(EnvType type)
{
    ProtocolManager::ControllerType cmdType;
    if(app()->netWorkMgr()->IsTcpConnected())
    {   QVector<QString> adressVector;
        switch (type) {
        case EnvType::Temp:
            adressVector  = TempRegList_->getAddress();
            cmdType = ProtocolManager::ControllerType::EnvTempController_t;
            break;
        case EnvType::Humidity:
            adressVector  = HumidityRegList_->getAddress();
            cmdType = ProtocolManager::ControllerType::EnvHumidityController_t;
            break;
        case EnvType::WaterLevel:
            adressVector  = WaterLevelRegList_->getAddress();
            cmdType = ProtocolManager::ControllerType::EnvWaterLevelController_t;
            break;
        default:
            break;
        }
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(cmdType,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void EnvParaController::setData(EnvType type)
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        QVector<QString> adressVector;
        switch (type) {
            case EnvType::Temp:
                adressVector  = TempRegList_->getAddress();
                break;
            case EnvType::Humidity:
                adressVector  = HumidityRegList_->getAddress();
                break;
            case EnvType::WaterLevel:
                adressVector  = WaterLevelRegList_->getAddress();
                break;
            default:
                break;
        }
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
        qDebug() << "GasParaController Pack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "MainParaController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}


