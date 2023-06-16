//*****************************************************************************
// * Copyright 2023-xxxx xxx Co., Ltd.
// * All right reserved. See COPYRIGHT for detailed Information.
// *
// * @file          QmlGlobal.h
// * @brief         QmlGlobal
// * @Description   将所有模块单例注册到QML
// * @author        liukuan<807874484@qq.com>
// * @date          2023/06/15
// * @history
// ****************************************************************************
#ifndef QMLGLOBAL_H
#define QMLGLOBAL_H
#include <QObject>
class NetWorkManager;
class QmlGlobal : public QObject
{
    Q_OBJECT
public:
    explicit QmlGlobal(QObject *parent = nullptr);
    Q_PROPERTY(NetWorkManager *  netWorkManager  READ   netWorkManager    CONSTANT)

    NetWorkManager * netWorkManager(){return this->_netWorkManager;}
private:
    NetWorkManager *_netWorkManager;

};

#endif // QMLGLOBAL_H
