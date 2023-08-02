
#include "MainParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

MainParaController::MainParaController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->MainConParaSet())
    ,address_("0000000000000000")
    ,commType_(2)
    ,isEncrypted_(0)
    ,encrypType_(0)
    ,softVersion_("")
{

}


void MainParaController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(start,adressVector.count());
        qDebug() << sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void MainParaController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //地址 17字节
        QByteArray addressData =QByteArray(address_.toUtf8())+QByteArray(1, '\x00');
        //通讯方式 2字节
        auto commTypeData = ProtocolManager::intToHexByteArray(commType_);
        //是否加密 2字节
        auto encryptedData = ProtocolManager::intToHexByteArray(isEncrypted_);
        //加密类型 2字节
        auto encrypType = ProtocolManager::intToHexByteArray(encrypType_);
        //软件版本地址 4字节
        QByteArray softVersion(4, '\x00');
        //备用字节 6字节
        QByteArray standby(6, '\x00');
        //数据包共33字节
        QByteArray packData  = addressData+
                           commTypeData+
                           encryptedData+
                           encrypType +
                           softVersion +
                           standby;
        qDebug() << "MainParaController SendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "MainParaController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}









