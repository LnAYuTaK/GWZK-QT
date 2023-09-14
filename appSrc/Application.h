/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          Application.h
 * @brief         Application
 * @Description   App类全局单例 可以通过app() 接口全局获取
 * @author        liukuan<807874484@qq.com>
 * @date          2023/06/15
 * @history
 *****************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#include <QObject>
#include <QQmlEngine>
#include <QSettings>
class ParaFactManager;
class NetWorkManager;
class ProtocolManager;
class QmlGlobal;
class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int &argc, char* argv[]);
    ~Application();
    bool event(QEvent *e) override;
    static Application*  _app;

    NetWorkManager *  netWorkMgr(){return this->_netWorkMgr;}
    ParaFactManager * paraFactMgr(){return this->_paraFactMgr;}
    ProtocolManager * protocolMgr(){return this->_protocolMgr;}

public :
    void initAppCommon();
    void initAppView();
private:
    ParaFactManager * _paraFactMgr;
    NetWorkManager  * _netWorkMgr;
    ProtocolManager * _protocolMgr;
};
Application* app(void);
#endif // FREEKAPPLICATION_H
