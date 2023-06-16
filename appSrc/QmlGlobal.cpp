#include "QmlGlobal.h"
#include "Application.h"
#include "NetWorkManager.h"

QmlGlobal::QmlGlobal(QObject *parent)
    : QObject{parent}
    ,_netWorkManager(nullptr)
{
    _netWorkManager = app()->netWorkMgr();
}
//-----------------------------------------------------------------------------

