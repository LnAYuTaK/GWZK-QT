#include "QmlGlobal.h"
#include "Application.h"
QmlGlobal::QmlGlobal(QObject *parent)
    : QObject{parent}
    ,_netWorkManager(nullptr)
    ,_protocolManager(nullptr)
{
    _netWorkManager = app()->netWorkMgr();
    _protocolManager= app()->protocolMgr();
}
//-----------------------------------------------------------------------------
















//-----------------------------------------------------------------------------













//-----------------------------------------------------------------------------

