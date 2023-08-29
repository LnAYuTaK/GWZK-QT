
#include "MainParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"
MainParaController::MainParaController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->MainConParaSet())
    ,address_("")
    ,commType_("GPRS")
    ,isEncrypted_(0)
    ,encrypType_("")
    ,softVersion_("")
{

}

void MainParaController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::MainParaController_t,start,adressVector.count());
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
        //地址 18字节
        QByteArray addressData  = QByteArray(18,'\x00');
        //通讯方式 2字节
        int commRes = 0 ;
        if(commType_ == ""){
            return ;
        }
        else if(commType_ == "GPRS"){
            commRes = 0;
        }
        else if(commType_ == "本地串口"){
            commRes = 1;
        }
        else if(commType_ == "本地网络"){
            commRes = 2;
        }
        else if(commType_ == "其他"){
            commRes = 3;
        }
        auto commTypeData = ProtocolManager::intToHexByteArray(commRes);
        qDebug() <<commType_;
        //是否加密 2字节
        auto encryptedData = ProtocolManager::intToHexByteArray(isEncrypted_);
        //加密类型 2字节
        qDebug()<< encrypType_;
        QByteArray encType{};
        //如果加密
        if(isEncrypted_){
            encType.append('\x01');
            if(encrypType_ == "南瑞"){
                encType.append('\x00');
            }
            else if(encrypType_ == "普华"){
                encType.append('\x01');
            }
            else if(encrypType_ == "SD卡加密"){
                encType.append('\x02');
            }
            else if(encrypType_ == "其他"){
                encType.append('\x03');
            }
        }
        //如果不加密
        else{
            encType.append('\x01').append('\x00');
        }
        //auto encrypType = ProtocolManager::intToHexByteArray(encrypType_.toint());
        //软件版本地址 4字节
        QByteArray softVersion(4, '\x00');
        //备用字节 6字节
        QByteArray standby(6, '\x00');
        //数据包共33字节
        QByteArray packData  = addressData+
                               commTypeData+
                               encryptedData+
                               encType +
                               softVersion +
                               standby;
        qDebug() << "MainParaController Pack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "MainParaController SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void MainParaController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
    //先获取18个字节
    QByteArray  address = data.left(18);
    //19 20 字节// 通讯方式
    short commType = ProtocolManager::bytesToshort(data.mid(18,2),ProtocolManager::LittileEndian);
    if(commType == 0){
        setCommType(QString::fromLocal8Bit("GPRS"));
    }
    else if(commType == 1){
        setCommType(QString::fromLocal8Bit("本地串口"));
    }
    else if(commType == 2){
        setCommType(QString::fromLocal8Bit("本地网络"));
    }
    else if(commType == 3){
        setCommType(QString::fromLocal8Bit("其他"));
    }
    //是否加密 /加密方式20 21字节//
    int isEncrypted =data.mid(20,1).toHex().toInt();
    setEncrypt(isEncrypted);
    int encrypTypem =data.mid(21,1).toHex().toInt();
    if(isEncrypted) {
        if(encrypTypem == 0){
            setEncrypType(QString::fromLocal8Bit("南瑞"));
        }
        else if(encrypTypem == 1){
            setEncrypType(QString::fromLocal8Bit("普华"));
        }
        else if(encrypTypem == 2){
            setEncrypType(QString::fromLocal8Bit("SD卡加密"));
        }
        else if(encrypTypem == 3){
            setEncrypType(QString::fromLocal8Bit("其他"));
        }
    }
    else {
        setEncrypType(QString::fromLocal8Bit("未加密"));
    }
    //版本地址1 高位
    QString version1Hi =QString::number(QChar(data.at(22)).unicode());
    qDebug() << version1Hi;
    //版本地址1 高位
    QString version1Low =QString::number(QChar(data.at(23)).unicode());
    qDebug() << version1Low;
    //版本地址2 高位
    QString version2Hi =QString::number(QChar(data.at(24)).unicode());
    //版本地址2 高位
    QString  versio21Low =QString::number(QChar(data.at(25)).unicode());
    QString  softVersion = QString(version1Hi)
                          + "."
                          + QString(version1Low)
                          + "."
                          + QString(version2Hi)
                          + "."
                          + QString(versio21Low);
    setSoftVersion(softVersion);
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}








