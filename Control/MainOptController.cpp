
#include "MainOptController.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "appSrc/ProtocolManager.h"
#include "appSrc/NetWorkManager.h"

MainOptController::MainOptController(QObject *parent)
    : QObject{parent}
    ,regList_(app()->paraFactMgr()->MainControl())
    ,sysTime_(0)
    ,sysOpsAble_(0)
{

}

void MainOptController::queryData()
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

void MainOptController::setData()
{
    if(app()->netWorkMgr()->IsTcpConnected())
    {










    }




}
