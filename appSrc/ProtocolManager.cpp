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
{
    //reg qml
}
//-----------------------------------------------------------------------------
/**
 * @brief Protocol::ProtocolHandle
 * @param sender
 * @param data
 */
//分割quint16为高低位
void splitQuint16(quint16 value, char& highByte, char& lowByte) {
    highByte = static_cast<char>((value >> 8) & 0xFF);
    lowByte = static_cast<char>(value & 0xFF);
}
//2字节一组数据
QVector<qint16> ProtocolManager::ByteArrayToIntVec(QByteArray byteArray){
    QVector<qint16> intArray{};
    for (int i = 0; i < byteArray.size(); i += 2) {
        //高位                  //低位
        qint16 value = (byteArray[i + 1] << 8) | byteArray[i];
        intArray.append(value);
    }
    return intArray;
}

QVector<QByteArray> ProtocolManager::SpiltData(QByteArray byteArray)
{
    QVector<QByteArray>byteArrayGroups;
    for (int i = 0; i < byteArray.size(); i += 2) {
        QByteArray group = byteArray.mid(i, 2);
        byteArrayGroups.append(group);
    }
    return byteArrayGroups;
}

void ProtocolManager::sendSignal(ReccType recvType,ControllerType type,QByteArray data)
{
    switch (type) {
    case TunnelGasData_t:
        emit TunnelGasDataSig(recvType,data);
        break;
    case TunnelGasDevControl_t:
        emit TunnelGasDevSig(recvType,data);
        break;
    case TunnelFanDevControl_t:
        emit TunnelFunDevSig(recvType,data);
        break;
    case WaterLevelController_t:
        emit WaterLevelDeviceSig(recvType,data);
        break;
    case WaterPumpController_t:
        emit WaterPumpDeviceSig(recvType,data);
        break;
    case MainParaController_t:
        emit MainControlParaSig(recvType,data);
        break;
    case LocalNetParaController_t:
        emit LoaclNetParaSig(recvType,data);
        break;
    case NetParaController_t:
        emit NetparaSig(recvType,data);
        break;
    case MqttParaController_t:
        emit MqttParaSig(recvType,data);
        break;
    case MainOptController_t:
        emit MainControlOptsSig(recvType,data);
        break;
    case GasParaO2Controller_t:
        emit GasParaO2Sig(recvType,data);
        break;
    case GasParaH2Controller_t:
        emit GasParaH2Sig(recvType,data);
        break;
    case GasParaCl2Controller_t:
        emit GasParaCl2Sig(recvType,data);
        break;
    case GasParaH2SController_t:
        emit GasParaH2SSig(recvType,data);
        break;
    case GasParaCH4Controller_t:
        emit GasParaCH4Sig(recvType,data);
        break;
    case GasParaCOController_t:
        emit  GasParaCOSig(recvType,data);
        break;
    case GasParaCO2Controller_t:
        emit  GasParaCO2Sig(recvType,data);
        break;
    case EnvTempController_t:
        emit EnvParaTempSig(recvType,data);
        break;
    case EnvHumidityController_t:
        emit EnvParaHumiditySig(recvType,data);
        break;
    case EnvWaterLevelController_t:
        emit EnvParaWaterLevelSig(recvType,data);
        break;
    case WaterLevelDataController_t:
        emit WaterLevelDataSig(recvType,data);
        break;
    case SensorEnableController_t:
        emit SensorEnableSig(recvType,data);
        break;
    case  UnknowType:
        break;
    default:
        break;
    }
}

void ProtocolManager::ProtocolHandle(QObject *sender,QByteArray data)
{
    Q_UNUSED(sender)
    //先拆头字节//
    if(data.size()>0)
    {
        const char* pData = data.constData();
        if(pData[0]=='\xff')
        {
            //校验下CRC//高字节在前
            char CRC16TempHi;
            char CRC16TempLo;
            quint16 crc =  modbusCrc16((quint8*)data.data(),data.size()-2);
            splitQuint16(crc,CRC16TempHi,CRC16TempLo);
            //CRC 两个字节
            char CRC16Hi = pData[data.size()-1];
            char CRC16Lo = pData[data.size()-2];
            if((CRC16Hi == CRC16TempHi)&&(CRC16Lo==CRC16TempLo))
            {
                //读寄存器返回类型//
                if(pData[1]=='\x03')
                {
                    //去掉从站地址 报文类型 数据长度 校验码
                    data.remove(0, 3);
                    data.chop(2);
                    QByteArray master_read  = data;
                    //根据上次操作判断是什么类型的返回
//                    if(this->recvReadTimer->isActive())
//                    {
                        qDebug() << "Recv: "<< master_read << " Type: "<<nowType_;
                        //根据上次操作判断是
                        sendSignal(HandleRead,nowType_ ,master_read);
//                    }
                }
                //写寄存器返回类型//
                else if(pData[1]=='\x10')
                {
                    //去掉头尾2字节
                    QByteArray master_write = data.mid(2,(data.size() - 4));
                    //根据返回的起始地址高低字节判断是什么类型
                    //拼接起始地址
                    char regStartHi = master_write.at(0);
                    char regStartLo = master_write.at(1);
                    QByteArray byteArray;
                    byteArray.append(regStartHi);
                    byteArray.append(regStartLo);
                    qDebug() << "Recv 0x10" ;
                }
                else
                {
                    qDebug()<< "ERROR";
                    return;
                }
            }
            else
            {
                qDebug() << "Check CRC Error";
            }

        }
    }
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
//-----------------------------------------------------------------------------
QByteArray ProtocolManager::makeReadRegProto(ProtocolManager::ControllerType type,QByteArray start,int count)
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
  //记录一下当前正在准备接收的处理类型
  app()->protocolMgr()->setNowType(type);
  //记录一下 当前start地址类型
  return res+crc;
}
//-----------------------------------------------------------------------------
QByteArray ProtocolManager::intToHexByteArray(int data)
{
   QByteArray resByte{};
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





