
#include "Protocol.h"
#include <QThread>
#include <QDebug>
Protocol::Protocol(QObject *parent)
    : QObject{parent}
{

    //qDebug()<<QStringLiteral("线程ID:")<<QThread::currentThreadId();
}
//-----------------------------------------------------------------------------
/**
 * @brief Protocol::ProtocolHandle
 * @param sender
 * @param data
 */
void Protocol::ProtocolHandle(QObject *sender , QByteArray data)
{
    //qDebug()<<QStringLiteral("线程ID:")<<QThread::currentThreadId();
    //




}
//-----------------------------------------------------------------------------
