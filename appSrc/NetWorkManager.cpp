#include "NetWorkManager.h"
NetWorkManager::NetWorkManager(QObject *parent)
    : QObject{parent}
    ,_socket(nullptr)
    ,_socketIsConnected(false)
{

}
//-----------------------------------------------------------------------------
NetWorkManager::~NetWorkManager()
{
    if(_socket)
    {
        _socketIsConnected =false;
        _socket->deleteLater();
        _socket = nullptr;
    }
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
            qDebug()<<QString(buffer);
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
    QObject::connect(_socket, &QTcpSocket::disconnected, this, &NetWorkManager::tcpDisConnect);
    _socket->connectToHost(IP,port);
    if (!_socket->waitForConnected(1000))
    {
        _socket->deleteLater();
        _socket = nullptr;
        _socketIsConnected = false;
        emit errorMsg(TCP_LINK,QString("connect falut"));
        return false;
    }
    _socketIsConnected = true;
    emit connected(TCP_LINK);
    return true;
}
//-----------------------------------------------------------------------------
void NetWorkManager::tcpDisConnect()
{
    //服务器断线处理 立即删除资源
    qDebug()<<"DisConnect";
    if(_socket)
    {
        _socket->close();
        _socketIsConnected =false;
        _socket->deleteLater();
        _socket = nullptr;
    }
    emit disConnect(TCP_LINK);
}
//-----------------------------------------------------------------------------

