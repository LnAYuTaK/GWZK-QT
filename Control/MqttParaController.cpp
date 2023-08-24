
#include "MqttParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"
MqttParaController::MqttParaController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->MqttParaSet())
    ,mqttIp_("0.0.0.0")
    ,mqttPort_(0)
    ,mqttClientId_("")
    ,mqttUserName_("")
    ,mqttPasswd_("")
{
}

void MqttParaController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::MqttParaController_t,start,adressVector.count());
        qDebug() << sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void MqttParaController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        //寄存器首地址
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //IP地址 4个字节
        QByteArray mqttIp = ProtocolManager::ParseNetLocalString(ProtocolManager::Ip,mqttIp_);
        //端口号 2个字节
        QByteArray port       = ProtocolManager::intToHexByteArray(mqttPort_);
        //mqtt客户端ID 32字节(不够补0)
        QByteArray clientIdSource = mqttClientId_.toLatin1();
        QByteArray clientId(32, '\x00');
        clientId.replace(0,clientIdSource.size(),clientIdSource);
        //mqtt用户名 32字节(不够补0)
        QByteArray userNameSource = mqttUserName_.toLatin1();
        QByteArray userName(32, '\x00');
        userName.replace(0,userNameSource.size(),userNameSource);
        //mqtt密码 32字节(不够补0)
        QByteArray passwdSource = mqttPasswd_.toLatin1();
        QByteArray passwd(32, '\x00');
        passwd.replace(0,passwdSource.size(),passwdSource);
        QByteArray packData = mqttIp +
                              port +
                              clientId  +
                              userName +
                              passwd;
         qDebug() << "MqttParaController SendPack Size: " << packData.size();
         auto sendMsg =  ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
         qDebug() << "MqttParaController SendMsg  Size: " <<sendMsg.size();
         app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void MqttParaController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
         QDataStream dataStream(&data, QIODevice::ReadOnly);
         QVector<quint16> quint16Array;
         while (!dataStream.atEnd()) {
             quint16 value;
             dataStream >> value;
             quint16Array.append(value);
         }
         for(auto i :quint16Array)
         {
             qDebug() << i;
         }
    }
    else if(type == ProtocolManager::HandleWrite) {
         //
         qDebug() << "Handle Write: "<< data;
    }

}
