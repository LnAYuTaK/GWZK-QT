
#include "GasParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

GasParaController::GasParaController(QObject *parent)
    : QObject{parent}
    ,GasO2regList_(app()->paraFactMgr()->GasParaO2())
    ,GasH2regList_(app()->paraFactMgr()->GasParaH2())
    ,GasCl2regList_(app()->paraFactMgr()->GasParaCl2())
    ,GasH2SregList_(app()->paraFactMgr()->GasParaH2S())
    ,GasCH4regList_(app()->paraFactMgr()->GasParaCH4())
    ,GasCOregList_(app()->paraFactMgr()->GasParaCO())
    ,GasCO2regList_(app()->paraFactMgr()->GasParaCO2())
    ,upThresholdLimitLevel1_(0)
    ,lowThresholdLimitLevel1_(0)
    ,upThresholdLimitLevel2_(0)
    ,lowThresholdLimitLevel2_(0)
    ,upThresholdLimitLevel3_(0)
    ,lowThresholdLimitLevel3_(0)
    ,keepThresholdLimit_(0)
{

}

void GasParaController::queryData(GasType type)
{
    ProtocolManager::ControllerType cmdType;
    if(app()->netWorkMgr()->IsTcpConnected())
    {   QVector<QString> adressVector;
        switch (type) {
        case GasType::O2:
            adressVector  = GasO2regList_->getAddress();
            cmdType =  ProtocolManager::GasParaO2Controller_t;
            break;
        case GasType::H2:
            adressVector  = GasH2regList_->getAddress();
            cmdType = ProtocolManager::GasParaH2Controller_t;
            break;
        case GasType::Cl2:
            adressVector  = GasCl2regList_->getAddress();
            cmdType = ProtocolManager::GasParaCl2Controller_t;
            break;
        case GasType::H2S:
            adressVector  = GasH2SregList_->getAddress();
            cmdType = ProtocolManager::GasParaH2SController_t;
            break;
        case GasType::CH4:
            adressVector  = GasCH4regList_->getAddress();
            cmdType = ProtocolManager::GasParaCH4Controller_t;
            break;
        case GasType::CO:
            adressVector  = GasCOregList_->getAddress();
            cmdType = ProtocolManager::GasParaCOController_t;
            break;
        case GasType::CO2:
            adressVector =  GasCO2regList_->getAddress();
            cmdType = ProtocolManager::GasParaCO2Controller_t;
            break;
        default:
            break;
        }
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(cmdType,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void GasParaController::setData(GasType type)
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        QVector<QString> adressVector;
        switch (type) {
        case GasType::O2:
            adressVector  = GasO2regList_->getAddress();
            break;
        case GasType::H2:
            adressVector  = GasH2regList_->getAddress();
            break;
        case GasType::Cl2:
            adressVector  = GasCl2regList_->getAddress();
            break;
        case GasType::H2S:
            adressVector  = GasH2SregList_->getAddress();
            break;
        case GasType::CH4:
            adressVector  = GasCH4regList_->getAddress();
            break;
        case GasType::CO:
            adressVector  = GasCOregList_->getAddress();
            break;
        case GasType::CO2:
            adressVector  = GasCO2regList_->getAddress();
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
                              standby;
        qDebug() << "GasParaController Pack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "MainParaController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}
