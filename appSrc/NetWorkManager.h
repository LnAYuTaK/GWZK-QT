/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          NetWorkManager.h
 * @brief         NetWorkManager
 * @Description
 * @author        liukuan<807874484@qq.com>
 * @date          2023/06/15
 * @history
 *****************************************************************************/
#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include "Protocol.h"
enum LinkType{
    TCP_LINK,
    MQTT_LINK,
    UDP_LINK
};

class NetWorkManager : public QObject
{
    Q_OBJECT
public:
    Q_ENUM(LinkType)
    explicit NetWorkManager(QObject *parent = nullptr);
    ~NetWorkManager();

    //绑定前端
    Q_PROPERTY(bool IsTcpConnected READ IsTcpConnected NOTIFY ConnectedChanged);
public:
    bool IsTcpConnected ()const
    {
        return this->_socketIsConnected;
    }

    //*********TCP*********//
    //连接函数
    Q_INVOKABLE bool tcpConnect(QString IP,QString port);
    //断开函数
    Q_INVOKABLE void tcpDisConnect();
    //*********UDP*********//
    // Q_INVOKABLE bool ucpConnect(QString IP,QString port);
    // Q_INVOKABLE void ucpDisConnect();

    Q_INVOKABLE void WiteTest()
    {

    }
signals:
    /**
     * @brief InfoMsg
     * @param type 1. success 2.error 3.info
     * @param Msg
     */
    void InfoMsg            (QString  type,QString Msg);

    void bytesReceived      (QObject* link, QByteArray data);
    void bytesSent          (QObject* link, QByteArray data);
    void ConnectedChanged (bool isconnect);
private slots:
    //*********TCP*********//
    bool _tcpConnect(QString IP,qint16 port);
    void _tcpReadBytes  ();
    void _tcpWriteBytes (const QByteArray data);
    void _tcpDisConnect();
    //*********UDP*********//

private:
    bool          _socketIsConnected;
    QTcpSocket *  _socket;
    Protocol   *  _protocol;
    QThread    *  _tcpThread;
};

#endif // NETWORKMANAGER_H
