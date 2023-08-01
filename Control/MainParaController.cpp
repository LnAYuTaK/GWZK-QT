
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
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void MainParaController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        //地址
        QByteArray addressData =QByteArray(address_.toUtf8())+QByteArray::fromHex("00");
        //通讯方式
        auto commTypeData = ProtocolManager::intToHexByteArray(commType_);
        //是否加密
        auto encryptedData = ProtocolManager::intToHexByteArray(isEncrypted_);
        //加密类型
        auto encrypType = ProtocolManager::intToHexByteArray(encrypType_);
        //软件版本地址这里设置两个空字节
        QByteArray softVersionFake{};
        softVersionFake.resize(2);
        softVersionFake.fill(0,2);
        //备用字节
        QByteArray res{3,0};
        //起始地址
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        QByteArray data  = addressData+
                           commTypeData+
                           encryptedData+
                           encrypType +
                           res;
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),data);
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}









