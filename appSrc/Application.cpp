#include <QtQml>
#include "Application.h"
#include "ModuleBox.h"
#include "NetWorkManager.h"
#include "QmlGlobal.h"
#include "ParaFactManager.h"
#include "ProtocolManager.h"
Application* Application::_app = nullptr;
Application::Application(int &argc, char* argv[])
    :QApplication(argc, argv)
    ,_paraFactMgr(nullptr)
    ,_netWorkMgr(nullptr)
    ,_protocolMgr(nullptr)
{
    _app = this;
    _paraFactMgr = new ParaFactManager(this);
    _netWorkMgr =  new NetWorkManager(this);
    _protocolMgr = new ProtocolManager(this);
}
//-----------------------------------------------------------------------------
Application::~Application()
{
    _netWorkMgr->deleteLater();
    _protocolMgr->deleteLater();
}
//-----------------------------------------------------------------------------
Application* app(void)
{
    return Application::_app;
}
//-----------------------------------------------------------------------------
//close Windows
bool Application::event(QEvent *e)
{
    Q_UNUSED(e)
    return QApplication::event(e);
}
//-----------------------------------------------------------------------------
static QObject *QmlGlobalRegist(QQmlEngine*, QJSEngine*)
{
    QmlGlobal *  qmlGlobal = new QmlGlobal(app());
    return  qobject_cast<QObject *>(qmlGlobal);
}
//-----------------------------------------------------------------------------
void Application::initAppCommon()
{
    qmlRegisterUncreatableType<NetWorkManager>  ("App.NetWorkManager",   1, 0, "NetWorkManager",  "Reference only");
    qmlRegisterUncreatableType<ProtocolManager> ("App.ProtocolManager",   1, 0, "ProtocolManager",  "Reference only");
    qmlRegisterSingletonType<QmlGlobal>("App",1,0,"App",QmlGlobalRegist);
}
//-----------------------------------------------------------------------------
void Application::initAppView()
{
    //TUDO
}
//-----------------------------------------------------------------------------








