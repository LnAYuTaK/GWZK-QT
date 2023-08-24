
#include "GasParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"

GasPara::GasPara(int type,JsonFactGroup *regList)
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
    qmlRegisterUncreatableType<GasPara>("App.ProtocolManager", 1, 0,"GasPara","Reference only");
}

void GasPara::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        ProtocolManager::ControllerType type;
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        switch (type_) {
        case 0:
            type = ProtocolManager::ControllerType::GasParaO2Controller_t;
            break;
        case 1:
            type = ProtocolManager::ControllerType::GasParaH2Controller_t;
            break;
        case 2:
            type = ProtocolManager::ControllerType::GasParaCl2Controller_t;
            break;
        case 3:
            type = ProtocolManager::ControllerType::GasParaH2SController_t;
            break;
        case 4:
            type = ProtocolManager::ControllerType::GasParaCH4Controller_t;
            break;
        case 5:
            type = ProtocolManager::ControllerType::GasParaCOController_t;
            break;
        case 6:
            type = ProtocolManager::ControllerType::GasParaCO2Controller_t;
            break;
        default:
            return;
        }
        auto sendMsg = ProtocolManager::makeReadRegProto(type,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void GasPara::setData()
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
        qDebug()  <<"GasParaController Pack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "GasParaController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

GasParaController::GasParaController(QObject *parent)
    : QObject{parent}
    ,gasO2_(new GasPara(O2,app()->paraFactMgr()->GasParaCO2()))
    ,gasH2_(new GasPara(H2,app()->paraFactMgr()->GasParaH2()))
    ,gasCl2_(new GasPara(Cl2,app()->paraFactMgr()->GasParaCl2()))
    ,gasH2S_(new GasPara(H2S,app()->paraFactMgr()->GasParaH2S()))
    ,gasCH4_(new GasPara(CH4,app()->paraFactMgr()->GasParaCH4()))
    ,gasCO_(new GasPara(CO,app()->paraFactMgr()->GasParaCO()))
    ,gasCO2_(new GasPara(CO2,app()->paraFactMgr()->GasParaCO2()))
{

}

void GasParaController::queryData(GasType type)
{
    switch (type) {
    case O2:
        gasO2_->queryData();
        break;
    case H2:
        gasH2_->queryData();
        break;
    case Cl2:
        gasCl2_->queryData();
        break;
    case H2S:
        gasH2S_->queryData();
        break;
    case CH4:
        gasCH4_->queryData();
        break;
    case CO:
        gasCO_->queryData();
        break;
    case CO2:
        gasCO2_->queryData();
        break;
    default:
        break;
    }
}
void GasParaController::setData(GasType type)
{
    switch (type) {
    case O2:
        gasO2_->setData();
        break;
    case H2:
        gasH2_->setData();
        break;
    case Cl2:
        gasCl2_->setData();
        break;
    case H2S:
        gasH2S_->setData();
        break;
    case CH4:
        gasCH4_->setData();
        break;
    case CO:
        gasCO_->setData();
        break;
    case CO2:
        gasCO2_->setData();
        break;
    default:
        break;
    }
}

void GasParaController::recvSeleteType(GasType type,GasPara *target,QByteArray data)
{
    auto resdata = ProtocolManager::SpiltData(data);
    if(resdata.size()==9)
    {
        switch (type) {
        case O2:
            gasO2_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
            gasO2_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
            gasO2_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
            gasO2_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
            gasO2_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
            gasO2_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
            gasO2_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
            gasO2_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
            break;
        case H2:
            gasH2_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
            gasH2_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
            gasH2_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
            gasH2_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
            gasH2_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
            gasH2_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
            gasH2_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
            gasH2_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
            break;
        case Cl2:
            gasCl2_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
            gasCl2_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
            gasCl2_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
            gasCl2_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
            gasCl2_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
            gasCl2_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
            gasCl2_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
            gasCl2_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
            break;
        case H2S:
            gasH2S_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
            gasH2S_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
            gasH2S_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
            gasH2S_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
            gasH2S_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
            gasH2S_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
            gasH2S_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
            gasH2S_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
            break;
        case CH4:
            gasCH4_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
            gasCH4_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
            gasCH4_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
            gasCH4_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
            gasCH4_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
            gasCH4_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
            gasCH4_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
            gasCH4_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
            break;
        case CO:
            gasCO_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
            gasCO_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
            gasCO_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
            gasCO_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
            gasCO_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
            gasCO_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
            gasCO_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
            gasCO_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
            break;
        case CO2:
            gasCO2_->setUpThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[0]));
            gasCO2_->setLowThresholdLimitLevel1((int)ProtocolManager::bytesToshort(resdata[1]));
            gasCO2_->setUpThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[2]));
            gasCO2_->setLowThresholdLimitLevel2((int)ProtocolManager::bytesToshort(resdata[3]));
            gasCO2_->setUpThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[4]));
            gasCO2_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[5]));
            gasCO2_->setLowThresholdLimitLevel3((int)ProtocolManager::bytesToshort(resdata[6]));
            gasCO2_->setKeepThresholdLimit((int)ProtocolManager::bytesToshort(resdata[7]));
            break;
        default:
            break;
        }
    }
}

void GasParaController::handleRecvO2(ProtocolManager::ReccType type,QByteArray data)
{
    //读返回
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(O2,gasO2_,data);
    }
    //写寄存器返回
    else if(type == ProtocolManager::HandleWrite) {

        qDebug() << "Handle Write: "<< data;
    }
}

void GasParaController::handleRecvH2(ProtocolManager::ReccType type,QByteArray data)
{
    //读返回
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(H2,gasH2_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}

void GasParaController::handleRecvCl2(ProtocolManager::ReccType type,QByteArray data)
{
    //读返回
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(Cl2,gasCl2_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}

void GasParaController::handleRecvH2S(ProtocolManager::ReccType type,QByteArray data)
{
    //读返回
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(H2S,gasH2S_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}

void GasParaController::handleRecvCH4(ProtocolManager::ReccType type,QByteArray data)
{
    //读返回
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(H2S,gasH2S_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}

void GasParaController::handleRecvCO(ProtocolManager::ReccType type,QByteArray data)
{
    //读返回
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(CO,gasCO_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}

void GasParaController::handleRecvCO2(ProtocolManager::ReccType type,QByteArray data)
{
    //读返回
    if(type == ProtocolManager::HandleRead) {
        recvSeleteType(CO2,gasCO2_,data);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}
