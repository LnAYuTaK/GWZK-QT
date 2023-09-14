
#include "WaterLevelDataController.h"

WaterLevelDataController::WaterLevelDataController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->WaterLevelData())
    ,rawData_("")
    ,alarmLevel_("")
{

}

//只能查询
void WaterLevelDataController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected()){
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::WaterLevelDataController_t,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void WaterLevelDataController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(data.size() == 10)
    {
        QByteArray WaterLevelBytes = QByteArray().append(data.at(0)).append(data.at(1));
        float waterLevelData  =  WaterLevelBytes.toHex().toInt(nullptr,16);
        QString str = QString::number(waterLevelData/10, 'f', 1);
        setRawData(str);
        //QByteArray alarmLevelBytes = QByteArray().append(data.at(2)).append(data.at(3));
        char alarmlevel = data.at(2);
        setAlarmLevel(QString::number((int)alarmlevel));
    }
}


