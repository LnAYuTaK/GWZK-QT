//*****************************************************************************
// * Copyright 2023-xxxx xxx Co., Ltd.
// * All right reserved. See COPYRIGHT for detailed Information.
// *
// * @file          QmlGlobal.h
// * @brief         QmlGlobal
// * @Description
// * @author        liukuan<807874484@qq.com>
// * @date          2023/06/15
// * @history
// ****************************************************************************
#ifndef QMLGLOBAL_H
#define QMLGLOBAL_H
#include <QObject>
#include "NetWorkManager.h"
#include "ProtocolManager.h"

class QmlGlobal : public QObject
{
    Q_OBJECT
public:
    explicit QmlGlobal(QObject *parent = nullptr);

    Q_PROPERTY(NetWorkManager  * netWorkManager  READ   netWorkManager CONSTANT)
    Q_PROPERTY(ProtocolManager * protoManager    READ   protoManager    CONSTANT)

    NetWorkManager       * netWorkManager(){return this->_netWorkManager;}
    ProtocolManager      * protoManager  (){return this->_protocolManager;}
private:
    NetWorkManager  *_netWorkManager;
    ProtocolManager *_protocolManager;

};

#endif // QMLGLOBAL_H
