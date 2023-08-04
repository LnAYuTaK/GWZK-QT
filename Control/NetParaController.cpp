
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
void NetParaController::setData()
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
void NetParaController::queryData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {



    }
}

