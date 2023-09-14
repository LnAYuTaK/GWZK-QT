
#include "NetParaController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "appSrc/NetWorkManager.h"
#include "appSrc/Utils.h"
NetParaController::NetParaController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->NetParaSet())
    ,masterIp_("")
    ,masterPort_("")
    ,linkType_(QString::fromLocal8Bit("TCP"))
    ,simApn_("")
    ,simUserName_("")
    ,simPasswd_("")
    ,alternateIp_("")
    ,alternatePort_("")
    ,alternateLinktype_(QString::fromLocal8Bit("TCP"))
{

}

void NetParaController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {
        auto adressVector  = regList_->getAddress();
        QByteArray start =QByteArray::fromHex(adressVector.at(0).toLatin1());
        auto sendMsg = ProtocolManager::makeReadRegProto(ProtocolManager::NetParaController_t,start,adressVector.count());
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
        QByteArray port       = ProtocolManager::intToHexByteArray(masterPort_.toInt());
        //链接方式2字节
        int linktypeInt  =0;
        if(linkType_ == QString::fromLocal8Bit("TCP")){
            linktypeInt = 0;
        }
        else if(linkType_ == QString::fromLocal8Bit("UDP")){
            linktypeInt = 1;
        }
        QByteArray linktype   = ProtocolManager::intToHexByteArray(linktypeInt);
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
        QByteArray alternatePort =ProtocolManager::intToHexByteArray(alternatePort_.toInt());
        //备用连接方式 2字节
        int altlinktypeInt  =0;
        if(alternateLinktype_ == QString::fromLocal8Bit("TCP")){
            altlinktypeInt = 0;
        }
        else if(alternateLinktype_ == QString::fromLocal8Bit("UDP")){
            altlinktypeInt = 1;
        }
        QByteArray alternateLinktype = ProtocolManager::intToHexByteArray(altlinktypeInt);
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
        //qDebug() << "NetPara SendPack Size: " << packData.size();
        auto sendMsg = ProtocolManager::makeWriteRegProto(start,adressVector.count(),packData);
        qDebug() << "NetPara SendMsg Size: " <<sendMsg.size();
        //app()->netWorkMgr()->_tcpWriteBytes(sendMsg);
    }
}

void NetParaController::handleRecv(ProtocolManager::ReccType type,QByteArray data)
{
    if(type == ProtocolManager::HandleRead) {
       //解析IP地址
        QString masterIp = QString::number(QChar(data.at(0)).unicode())
                    +"."
                    + QString::number(QChar(data.at(1)).unicode())
                    +"."
                    + QString::number(QChar(data.at(2)).unicode())
                    +"."
                    + QString::number(QChar(data.at(3)).unicode());
        //qDebug() << masterIp;
        setMasterIp(masterIp);
        QByteArray portdata{};
        portdata.append(data.at(4)).append(data.at(5));
        setMasterPort(QString(portdata.toHex().toInt(nullptr,16)));
        QByteArray linktypedata{};
        linktypedata.append(data.at(6)).append(data.at(7));
        int linktypeInt = linktypedata.toHex().toInt(nullptr,16);
        if(linktypeInt == 0){
            setLinkType(QString::fromLocal8Bit("TCP"));
        }
        else if(linktypeInt == 1){
            setLinkType(QString::fromLocal8Bit("UDP"));
        }
        //SIM卡APN 32字节
        QByteArray APN = data.mid(8,32);
        qDebug() << QString(APN);
        setSIMAPN(APN);
        //SIM卡用户名 32字节
        QByteArray UserName = data.mid(8+32,32);
        qDebug() << QString(UserName);
        setSIMUserName(UserName);
        //SIM卡密码 32字节
        QByteArray Passwd= data.mid(8+32+32,32);
        qDebug() << QString(Passwd);
        setSIMPasswd(Passwd);
        //备用地址
        QString altIp= QString::number(QChar(data.at(8+32+32+32)).unicode())
                           +"."
                           + QString::number(QChar(data.at(8+32+32+32+1)).unicode())
                           +"."
                           + QString::number(QChar(data.at(8+32+32+32+2)).unicode())
                           +"."
                           + QString::number(QChar(data.at(8+32+32+32+3)).unicode());
        qDebug() << altIp;
        setAlternateIp(altIp);
        //备用端口 2字节
        QByteArray altportdata{};
        altportdata.append(data.at(8+32+32+32+3+1)).append(data.at(8+32+32+32+3+2));
        setAlternatePort(QString(altportdata.toHex().toInt(nullptr,16)));
        qDebug() << altportdata.toHex().toInt(nullptr,16);
        //备用链接方式 2字节
        QByteArray altlinktype{};
        altlinktype.append(data.at(8+32+32+32+3+3)).append(data.at(8+32+32+32+3+4));
        qDebug() << altlinktype.toHex().toInt(nullptr,16);
        int altlinktypeInt = altlinktype.toHex().toInt(nullptr,16);
        if(altlinktypeInt  == 0){
            setAlternateLinktype(QString("TCP"));
        }
        else if(altlinktypeInt  == 1){
            setAlternateLinktype(QString("UDP"));
        }
    }
    else if(type == ProtocolManager::HandleWrite) {
        //
        qDebug() << "Handle Write: "<< data;
    }
}
