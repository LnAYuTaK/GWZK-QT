#include <QtQml>
#include "Application.h"
#include "ModuleBox.h"
#include "NetWorkManager.h"
#include "QmlGlobal.h"

Application* Application::_app = nullptr;
Application::Application(int &argc, char* argv[])
    :QApplication(argc, argv)
    ,_netWorkMgr(nullptr)
{
    _app = this;
    _netWorkMgr = new NetWorkManager(this);
}
//-----------------------------------------------------------------------------
Application::~Application()
{
    _netWorkMgr->deleteLater();
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
//这里将所有模块注册到QML 中使用 类似头文件
void Application::initAppCommon()
{
    qmlRegisterUncreatableType<NetWorkManager>  ("App.NetWorkManager",   1, 0, "NetWorkManager",  "Reference only");
    qmlRegisterSingletonType<QmlGlobal>("App",1,0,"App",QmlGlobalRegist);
}
//-----------------------------------------------------------------------------
void Application::initAppView()
{
    //TUDO
}
//-----------------------------------------------------------------------------








