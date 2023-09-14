
#include "SensorEnableController.h"

SensorEnableController::SensorEnableController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->SensorEnable())
    ,O2Enabale_(false)
    ,COEnable_(false)
    ,Cl2Enable_(false)
    ,H2SEnable_(false)
    ,H2Enable_(false)
    ,CO2Enable_(false)
    ,CH4Enable_(false)
    ,TemHumEnable_(false)
    ,WaterLevelEnable_(false)
{

}

void SensorEnableController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected()){
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::SensorEnableController_t,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void SensorEnableController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        QByteArray packData{};
        //寄存器首地址
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        char Hi = 0;
        char Low = 0;
        ProtocolManager::setBit(Hi,7,O2Enabale_);
        ProtocolManager::setBit(Hi,6,COEnable_);
        ProtocolManager::setBit(Hi,5,Cl2Enable_);
        ProtocolManager::setBit(Hi,4,H2SEnable_);
        ProtocolManager::setBit(Hi,3,H2Enable_);
        ProtocolManager::setBit(Hi,2,CO2Enable_);
        ProtocolManager::setBit(Hi,1,CH4Enable_);
        ProtocolManager::setBit(Hi,0,TemHumEnable_);
        ProtocolManager::setBit(Low,7,TemHumEnable_);
        ProtocolManager::setBit(Low,6,WaterLevelEnable_);
        QByteArray  padding = {6,'\x00'};
        packData.append(Hi).append(Low).append(padding);
        qDebug() << "SendPack Size: " << packData.size();
        auto sendMsg =  ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void SensorEnableController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(data.size()==8)
    {
        //最低为
        bool O2Enabale = ProtocolManager::getBitValue(data.at(0),7);
        setO2Enable(O2Enabale);
        bool COEnable  = ProtocolManager::getBitValue(data.at(0),6);
        setCOEnable(COEnable);
        bool Cl2Enable = ProtocolManager::getBitValue(data.at(0),5);
        setCl2Enable(Cl2Enable);
        bool H2SEnable  = ProtocolManager::getBitValue(data.at(0),4);
        setH2SEnable(H2SEnable);
        bool H2Enable  = ProtocolManager::getBitValue(data.at(0),3);
        setH2Enable(H2Enable);
        bool CO2Enable = ProtocolManager::getBitValue(data.at(0),2);
        setCO2Enable (CO2Enable);
        bool CH4Enable = ProtocolManager::getBitValue(data.at(0),1);
        setCH4Enable(CH4Enable);
        bool TemHumEnable = ProtocolManager::getBitValue(data.at(0),0);
        setTemHumEnable(TemHumEnable);
        //第二字节第二个
        bool WaterLevelEnable = ProtocolManager::getBitValue(data.at(1),6);
        setWaterLevelEnable(WaterLevelEnable);
    }
}



