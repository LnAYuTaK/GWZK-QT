
#include "NetParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

NetParaController::NetParaController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->NetParaSet())
    ,masterIp_("0.0.0.0")
    ,masterPort_(0)
    ,linkType_(0)
    ,simApn_("")
    ,simUserName_("")
    ,simPasswd_("")
    ,alternateIp_("0.0.0.0")
    ,alternatePort_(0)
    ,alternateLinktype_(0)
{

}

void NetParaController::queryData()
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

void NetParaController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector = regList_->getAddress();
        auto start =  QByteArray::fromHex(adressVector.at(0).toLatin1());
        //IP1地址 4个字节
        QByteArray ipAdd1Data = ProtocolManager::ParseNetLocalString(ProtocolManager::Ip,masterIp_);
        //端口2字节
        QByteArray port       = ProtocolManager::intToHexByteArray(masterPort_);
        //链接方式2字节
        QByteArray linktype   = ProtocolManager::intToHexByteArray(linkType_);
        //SIM卡APN32字节(不够自动补0)
        QByteArray simApSource = simApn_.toLatin1();
        QByteArray simApn(32, '\x00');
        simApn.replace(0,simApSource.size(),simApSource);
        //SIM卡用户名32字节(不够自动补0)
        QByteArray simUserNameSource = simUserName_.toLatin1();
        QByteArray simUserName(32, '\x00');
        simUserName.replace(0,simUserNameSource.size(),simUserNameSource);
        //SIM卡密码32字节(不够自动补0)
        QByteArray simPasswdSource = simPasswd_.toLatin1();
        QByteArray simPasswd(32, '\x00');
        simPasswd.replace(0,simUserNameSource.size(),simUserNameSource);
        //备用地址4字节 高低位
        QByteArray alternateIp  = ProtocolManager::ParseNetLocalString(ProtocolManager::Ip,alternateIp_);
        //备用端口地址 2字节
        QByteArray alternatePort =ProtocolManager::intToHexByteArray(alternatePort_);
        //备用连接方式 2字节
        QByteArray alternateLinktype = ProtocolManager::intToHexByteArray(alternateLinktype_);
        //数据包总共 112字节
        QByteArray packData = ipAdd1Data +
                        port +
                        linktype+
                        simApn +
                        simUserName +
                        simPasswd+
                        alternateIp+
                        alternatePort+
                        alternateLinktype;
        qDebug() << "NetPara SendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "NetPara SendMsg Size: " <<sendMsg.size();
        app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}


