#include "NetWorkManager.h"
#include "ProtocolManager.h"
#include "Application.h"
NetWorkManager::NetWorkManager(QObject *parent)
    : QObject{parent}
    ,_socketIsConnected(false)
    ,_socket(nullptr)
{

}
//-----------------------------------------------------------------------------
NetWorkManager::~NetWorkManager()
{
    if(_socket) {
        setTcpConnected(false);
        _socket->deleteLater();
        _socket = nullptr;
    }
}
//-----------------------------------------------------------------------------
bool NetWorkManager::tcpConnect(QString IP,QString port)
{
    return this->_tcpConnect(IP,port.toInt());
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
            emit bytesReceived(this,buffer);
        }
    }
}
//-----------------------------------------------------------------------------
void NetWorkManager::_tcpWriteBytes(const QByteArray data)
{
    if(_socket) {
        _socket->write(data);
        emit bytesSent(this,data);
    }
}
//-----------------------------------------------------------------------------
bool NetWorkManager::_tcpConnect(QString IP,qint16 port)
{
    if(_socket==nullptr) {
        _protocolMgr = app()->protocolMgr();
        _socket = new QTcpSocket(this);
        QObject::connect(_socket, &QIODevice::readyRead, this, &NetWorkManager::_tcpReadBytes);
        QObject::connect(_socket, &QTcpSocket::disconnected, this, &NetWorkManager::tcpDisConnect);
        _socket->connectToHost(IP,port);
        if (!_socket->waitForConnected(1000)) {
            _socket->deleteLater();
            _socket = nullptr;
            setTcpConnected(false);
            return false;
        }
        setTcpConnected(true);
        connect(this,&NetWorkManager::bytesReceived,_protocolMgr,&ProtocolManager::ProtocolHandle);
        return true;
    }
    else {
        return false;
    }
}
//-----------------------------------------------------------------------------
void NetWorkManager::tcpDisConnect()
{
    //如果已经连接//
    if(this->IsTcpConnected()) {
        if(_socket) {
            setTcpConnected(false);
            _socket->close();
            _socket->deleteLater();
            _socket = nullptr;
        }
    }
}
//-----------------------------------------------------------------------------
void NetWorkManager::setTcpConnected(bool connect){
    this->_socketIsConnected = connect;
    emit ConnectedChanged(_socketIsConnected);
}
