#include "ProtocolManager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QThread>
#include <QDebug>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QJsonObject>

#include "Control/TunnelGasDev.h"
#include "Control/TunnelGasMonitor.h"
#include "Control/TunnelFanControl.h"
#include "Control/MainParaController.h"
#include "Control/LocalNetParaController.h"
#include "Control/NetParaController.h"
//从站地址
const QByteArray SlaveAddr {QByteArray::fromHex("FF")};
//读取保持寄存器值功能码
const QByteArray ReadKeepType {QByteArray::fromHex("3")};
//写单个寄存器值功能码
const QByteArray WriteSingleType {QByteArray::fromHex("6")};
//写多个寄存器值功能码
const QByteArray WriteMultipleType {QByteArray::fromHex("10")};

ProtocolManager::ProtocolManager(QObject *parent)
    : QObject{parent}
    ,tunnelGasDev_(new TunnelGasDev(this))
    ,tunnelGasMon_(new TunnelGasMonitor(this))
    ,tunnelFanControl_(new TunnelFanControl(this))
    ,mainParaController_(new MainParaController(this))
    ,localNetParaController_(new LocalNetParaController(this))
    ,netParaController_(new NetParaController(this))

{
    qmlRegisterUncreatableType<TunnelGasDev>          ("App.ProtocolManager", 1, 0, "TunnelGasDev",          "Reference only");
    qmlRegisterUncreatableType<TunnelGasMonitor>      ("App.ProtocolManager", 1, 0, "TunnelGasMonitor",      "Reference only");
    qmlRegisterUncreatableType<TunnelFanControl>      ("App.ProtocolManager", 1, 0, "TunnelFanControl",      "Reference only");
    qmlRegisterUncreatableType<MainParaController>    ("App.ProtocolManager", 1, 0, "MainParaController",    "Reference only");
    qmlRegisterUncreatableType<LocalNetParaController>("App.ProtocolManager", 1, 0, "LocalNetParaController","Reference only");
    qmlRegisterUncreatableType<NetParaController>     ("App.ProtocolManager", 1, 0, "NetParaController",     "Reference only");
}
//-----------------------------------------------------------------------------
/**
 * @brief Protocol::ProtocolHandle
 * @param sender
 * @param data
 */
void ProtocolManager::ProtocolHandle(QObject *sender,QByteArray data)
{
  Q_UNUSED(sender)
  Q_UNUSED(data)




}
//-----------------------------------------------------------------------------
QByteArray ProtocolManager::makeWriteRegProto(QByteArray start,int count,QByteArray Data)
{
  QByteArray res {};
  QByteArray regcount = intToHexByteArray(count);
  //这里在输入之前做了校验 可能会导致
  char charCount = (char)(count*2);
  //数据数量 N*2
  res = SlaveAddr+WriteMultipleType+start+regcount+QByteArray(&charCount,1)+Data;
  quint16 checkData = modbusCrc16((quint8*)res.data(),res.size());
  QByteArray crc{}; //CRC16结果要存入的QByteArray
  crc.resize(2);
  crc[0] = (uchar)(0x00ff&checkData);
  crc[1] = (uchar)((0xff00&checkData)>>8);  //转换-存入QByteArray
  return res+crc;
}

QByteArray ProtocolManager::makeReadRegProto(QByteArray start,int count)
{
  QByteArray res {};
  QByteArray regcount = intToHexByteArray(count);
  res = SlaveAddr+ReadKeepType+start+regcount;
  quint16 checkData = modbusCrc16((quint8*)res.data(),res.size());
  QByteArray crc{}; //CRC16结果要存入的QByteArray
  crc.resize(2);
  crc.fill(0,2);
  crc[0] = (uchar)(0x00ff&checkData);
  crc[1] = (uchar)((0xff00&checkData)>>8);  //转换-存入QByteArray
  return res+crc;
}
//-----------------------------------------------------------------------------
QByteArray ProtocolManager::intToHexByteArray(int data)
{
   QByteArray resByte;
   resByte.append(static_cast<char>((data >> 8) & 0xFF)); // 高字节
   resByte.append(static_cast<char>(data & 0xFF)); // 低字节
   return resByte;
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
//-----------------------------------------------------------------------------
//先暂时做一个只分割不校验
QByteArray ProtocolManager::ParseNetLocalString(ParaType type,QString paraStr)
{
  QByteArray res{};
  switch (type) {
  case Ip:
  {
      auto ipList = paraStr.split(".");
      for(const QString& part:ipList){
          int byteValue = part.toInt();
          if (byteValue >= 0 && byteValue <= 255) {
              res.append(static_cast<char>(byteValue));
          }
      }
  }
  break;
  case Gateway:
  {
      auto gateWayList = paraStr.split(".");
      for(const QString& gateway:gateWayList){
          int byteValue = gateway.toInt();
          if ( byteValue >= 0 && byteValue <= 255) {
              res.append(static_cast<char>(byteValue));
          }
      }
  }
  break;
  case Mask:
  {
      auto maskList = paraStr.split(".");
      for(const QString& mask:maskList){
          int byteValue = mask.toInt();
          if (byteValue >= 0 && byteValue <= 255) {
              res.append(static_cast<char>(byteValue));
          }
      }
  }
  break;
  case MACAddr:
  {
      auto macAddrList = paraStr.split("-");
      for(const QString& macAddr:macAddrList){
          int byteValue =  macAddr.toInt();
          if (byteValue >= 0 && byteValue <= 255) {
              res.append(static_cast<char>(byteValue));
          }
      }
  }
  break;
  }
  return res;
}





