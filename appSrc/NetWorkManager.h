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
    //属性
    //Q_PROPERTY()
    //函数
    //Q_INVOKABLE()

    Q_INVOKABLE bool tcpConnect(QString IP,QString port)
    {

        if (_socket) {
            qWarning() << "connect called while already connected";
            return true;
        }
        return this->_tcpConnect(IP,port.toInt());
    }

    Q_INVOKABLE void witeString(QString Str){
        this->_tcpWriteBytes(Str.toUtf8());
    }

signals:
    void connected          (LinkType type);
    void errorMsg           (LinkType type,QString errorMsg);
    void disConnect         (LinkType type);
    void bytesReceived      (QObject* link, QByteArray data);
    void bytesSent          (QObject* link, QByteArray data);

private slots:
    bool _tcpConnect(QString IP,qint16 port);
    void _tcpReadBytes  ();
    void _tcpWriteBytes (const QByteArray data);
    //断线处理
    void tcpDisConnect();
private:
    bool          _socketIsConnected;
    QTcpSocket *  _socket;


};

#endif // NETWORKMANAGER_H
