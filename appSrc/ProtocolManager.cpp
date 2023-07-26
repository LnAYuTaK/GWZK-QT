#include "ProtocolManager.h"
#include <QThread>
#include <QDebug>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QJsonObject>
#include "TunnelGasDev.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
ProtocolManager::ProtocolManager(QObject *parent)
    : QObject{parent}
    ,tunnelGasDev_(new TunnelGasDev(this))
{
    qmlRegisterUncreatableType<TunnelGasDev>("App.ProtocolManager",   1, 0, "TunnelGasDev",  "Reference only");
}
//-----------------------------------------------------------------------------
/**
 * @brief Protocol::ProtocolHandle
 * @param sender
 * @param data
 */
void ProtocolManager::ProtocolHandle(QObject *sender , QByteArray data)
{

  Q_UNUSED(sender)
  Q_UNUSED(data)
}
//-----------------------------------------------------------------------------
void ProtocolManager::SetUnit(int type){

  qDebug() << type;
}
//-----------------------------------------------------------------------------
void ProtocolManager::GetUnit(int type){

  qDebug() << type;
}
//-----------------------------------------------------------------------------
quint16 ProtocolManager::modbusCrc16(quint8 *data, qint16 length)
{
  quint16 crc = 0xFFFF;

  for (quint16 i = 0; i < length; ++i) {
      crc ^= data[i];

      for (quint8 j = 0; j < 8; ++j) {
          if (crc & 0x0001) {
              crc >>= 1;
              crc ^= 0xA001;
          } else {
              crc >>= 1;
          }
      }
  }
  return crc;
}

