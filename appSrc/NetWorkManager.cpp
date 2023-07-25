#include "NetWorkManager.h"

NetWorkManager::NetWorkManager(QObject *parent)
    : QObject{parent}
    ,_socketIsConnected(false)
    ,_socket(nullptr)
    ,_protocol(new Protocol(this))
    ,_tcpThread(new QThread(this))
{

}
//-----------------------------------------------------------------------------
NetWorkManager::~NetWorkManager()
{
    if(_socket)
    {
        _socketIsConnected =false;
        emit ConnectedChanged(_socketIsConnected);
        _socket->deleteLater();
        _socket = nullptr;
    }
}
//-----------------------------------------------------------------------------
bool NetWorkManager::tcpConnect(QString IP,QString port)
{
    if (_socket) {
        emit InfoMsg("info",QStringLiteral("请勿重复TCP连接"));
        return false;
    }
    return this->_tcpConnect(IP,port.toInt());
}
//-----------------------------------------------------------------------------
void NetWorkManager::tcpDisConnect()
{
    if(!_socket)
    {
        emit InfoMsg("info",QStringLiteral("尚未创建TCP连接"));
        return;
    }
    this->_tcpDisConnect();
}
//-----------------------------------------------------------------------------
void NetWorkManager::_tcpReadBytes()
{
    if (_socket) {
        qint64 byteCount = _socket->bytesAvailable();
        if (byteCount)
        {
            QByteArray buffer;
            buffer.resize(byteCount);
            _socket->read(buffer.data(), buffer.size());
            emit bytesReceived(nullptr,buffer);
            qDebug()<<QThread::currentThreadId();
        }
    }
}
//-----------------------------------------------------------------------------
void NetWorkManager::_tcpWriteBytes(const QByteArray data)
{
    if(_socket) {
        _socket->write(data);
        emit bytesSent(nullptr,data);
    }
}
//-----------------------------------------------------------------------------
bool NetWorkManager::_tcpConnect(QString IP,qint16 port)
{
    _socket = new QTcpSocket(this);
    QObject::connect(_socket, &QIODevice::readyRead, this, &NetWorkManager::_tcpReadBytes);
    QObject::connect(_socket, &QTcpSocket::disconnected, this, &NetWorkManager::_tcpDisConnect);
    _socket->connectToHost(IP,port);
    if (!_socket->waitForConnected(1000))
    {
        _socket->deleteLater();
        _socket = nullptr;
        _socketIsConnected = false;
        emit ConnectedChanged(_socketIsConnected);
        emit InfoMsg("error",QStringLiteral("TCP连接失败"));
        return false;
    }
    emit InfoMsg("success",QStringLiteral("TCP连接成功"));
    _socketIsConnected = true;
    emit ConnectedChanged(_socketIsConnected);
    _tcpThread = new QThread();
    //Bind ProtolHandle
    connect(this,&NetWorkManager::bytesReceived,_protocol,&Protocol::ProtocolHandle);
    _protocol->moveToThread(_tcpThread);
    _tcpThread->start();
    return true;
}
//-----------------------------------------------------------------------------
void NetWorkManager::_tcpDisConnect()
{
    if(_socket)
    {
        _socket->close();
        _socketIsConnected =false;
        emit ConnectedChanged(_socketIsConnected);
        _socket->deleteLater();
        _socket = nullptr;
    }
    emit InfoMsg("info",QStringLiteral("与服务器断开链接"));
}
//-----------------------------------------------------------------------------

