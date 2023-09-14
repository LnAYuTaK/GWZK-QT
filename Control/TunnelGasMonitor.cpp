
#include "TunnelGasDevControl.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

TunnelGasDevControl::TunnelGasDevControl(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->TunnelGas())
    ,count_(0)
    ,cycle_(0)
    ,stateCycle_(0)
    ,channel_(0)
    ,format_(QString::fromLocal8Bit("递增"))
    ,address_("")
{

}

void TunnelGasDevControl::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::TunnelGasDevControl_t,start,adressVector.count());
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void TunnelGasDevControl::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        auto start = QByteArray::fromHex(adressVector.at(0).toLatin1());
        //地址17个字符
        qDebug() << address_.size();
        if(address_.size()<17){
            return;
        }
        QByteArray byteArray = QByteArray(address_.left(17).toLatin1())+QByteArray(1, '\x00');;
        //格式 2字节
        int format = 0;
        (format_==QString::fromLocal8Bit("递增"))?format = 0:format=1;
        auto formatData = ProtocolManager::intToHexByteArray(format);
        //数量 2字节
        auto countData = ProtocolManager::intToHexByteArray(count_);
        //数据周期 2字节
        auto cycleData = ProtocolManager::intToHexByteArray(cycle_);
        //状态周期 2字节
        auto stateCycleData = ProtocolManager::intToHexByteArray(stateCycle_);
        //通道 2字节
        auto channelData = ProtocolManager::intToHexByteArray(channel_);
        //备用 4字节
        QByteArray standby(4, '\x00');
        //数据包总共 32字节
        QByteArray packData  = byteArray +
                          formatData +
                          countData +
                          cycleData +
                          stateCycleData +
                          channelData +
                          standby;
        qDebug() << "TunnelGasDev SendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "TunnelGasDev SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void TunnelGasDevControl::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
        //气体ID 地址 18 字节
        QByteArray address = data.left(18);
        setAddress(QString::fromUtf8(address));
        QByteArray formatdata{};
        int format = 0;
        formatdata.append(data.at(18)).append(data.at(19));
        format = formatdata.toHex().toInt(nullptr,16);
        if(format  == 0){
            setFormat(QString::fromLocal8Bit("递增"));
        }
        else if(format  == 1){
            setFormat(QString::fromLocal8Bit("相同"));
        }
        //数量 2字节
        QByteArray countdata{};
        int count = 0;
        countdata.append(data.at(20)).append(data.at(21));
        count =  countdata.toHex().toInt(nullptr,16);
        setCount(count);
        //数据周期 2字节
        QByteArray cycledata{};
        int cycle= 0;
        cycledata.append(data.at(22)).append(data.at(23));
        cycle =  cycledata.toHex().toInt(nullptr,16);
        setCycle(cycle);
        //状态周期 2字节
        QByteArray stateCycledata{};
        int stateCycle= 0;
        stateCycledata.append(data.at(24)).append(data.at(25));
        stateCycle  =  stateCycledata.toHex().toInt(nullptr,16);
        setStateCycle(stateCycle);
        //通道 2字节
        QByteArray channeldata{};
        int channel= 0;
        channeldata.append(data.at(26)).append(data.at(27));
        channel=  channeldata.toHex().toInt(nullptr,16);
        setChannel(channel);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}




