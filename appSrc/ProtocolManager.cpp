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

#include "Control/TunnelGasData.h"
#include "Control/TunnelGasDevControl.h"
#include "Control/TunnelFanDevControl.h"
#include "Control/MainParaController.h"
#include "Control/LocalNetParaController.h"
#include "Control/NetParaController.h"
#include "Control/MainOptController.h"
#include "Control/MqttParaController.h"
#include "Control/WaterLevelController.h"
#include "Control/WaterPumpController.h"
#include "Control/GasParaController.h"
#include "Control/EnvParaController.h"

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
    ,tunnelGasData_(new TunnelGasData(this))
    ,tunnelGasDevControl_(new TunnelGasDevControl(this))
    ,tunnelFanDevControl_(new TunnelFanDevControl(this))
    ,mainParaController_(new MainParaController(this))
    ,localNetParaController_(new LocalNetParaController(this))
    ,netParaController_(new NetParaController(this))
    ,mainOptController_(new MainOptController(this))
    ,mqttParaController_(new MqttParaController(this))
    ,waterLevelController_(new WaterLevelController(this))
    ,waterPumpConrtroller_(new WaterPumpController(this))
    ,gasParaController_(new GasParaController(this))
    ,envParaController_(new EnvParaController(this))
    ,recvReadTimer(new QTimer(this))
{
    recvReadTimer->setInterval(1000); // 设置1秒的时间间隔
    connect(this->recvReadTimer, &QTimer::timeout, [=]() {
        recvReadTimer->stop();
    });
    qmlRegisterUncreatableType<TunnelGasDevControl>   ("App.ProtocolManager", 1, 0, "TunnelGasDevControl",   "Reference only");
    qmlRegisterUncreatableType<TunnelFanDevControl>   ("App.ProtocolManager", 1, 0, "TunnelFanDevControl",   "Reference only");
    qmlRegisterUncreatableType<MainParaController>    ("App.ProtocolManager", 1, 0, "MainParaController",    "Reference only");
    qmlRegisterUncreatableType<LocalNetParaController>("App.ProtocolManager", 1, 0, "LocalNetParaController","Reference only");
    qmlRegisterUncreatableType<NetParaController>     ("App.ProtocolManager", 1, 0, "NetParaController",     "Reference only");
    qmlRegisterUncreatableType<MainOptController>     ("App.ProtocolManager", 1, 0, "MainOptController",     "Reference only");
    qmlRegisterUncreatableType<MqttParaController>    ("App.ProtocolManager", 1, 0, "MqttParaController",    "Reference only");
    qmlRegisterUncreatableType<WaterLevelController>  ("App.ProtocolManager", 1, 0, "WaterLevelController",  "Reference only");
    qmlRegisterUncreatableType<WaterPumpController>   ("App.ProtocolManager", 1, 0, "WaterPumpController",   "Reference only");
    qmlRegisterUncreatableType<GasParaController>     ("App.ProtocolManager", 1, 0, "GasParaController",     "Reference only");
    qmlRegisterUncreatableType<EnvParaController>     ("App.ProtocolManager", 1, 0, "EnvParaController",     "Reference only");
    qmlRegisterUncreatableType<TunnelGasData>         ("App.ProtocolManager", 1, 0, "TunnelGasData",         "Reference only");
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

ProtocolManager::ControllerType ProtocolManager::getProtoTypeByReg(QByteArray data)
{
    if(data == tunnelGasData_->getTunnelGasData())
    {
        return  TunnelGasData_t;
    }
    else if(data == tunnelGasDevControl_->getTunnelGasDev())
    {
        return TunnelGasDevControl_t;
    }
    else if(data == tunnelFanDevControl_->getTunnelFanReg())
    {
        return TunnelFanDevControl_t;
    }
    else if(data == mainParaController_->getMainParaReg())
    {
        return MainParaController_t;
    }
    else if(data == localNetParaController_->getLocalNetParaReg())
    {
        return  LocalNetParaController_t;
    }
    else if(data == netParaController_->getNetParaReg())
    {
        return NetParaController_t;
    }
    else if(data == mainOptController_->getMainOptReg())
    {
        return MainOptController_t;
    }
    else if(data == mqttParaController_->getMqttParaReg())
    {
        return MqttParaController_t;
    }
    else if(data == waterLevelController_->getWaterLevel())
    {
        return  WaterLevelController_t;
    }
    else if(data == waterPumpConrtroller_->getWaterPumpReg())
    {
        return WaterPumpController_t;
    }
    else if(data ==gasParaController_->getGasO2Reg())
    {
        return GasParaO2Controller_t;
    }
    else if(data == gasParaController_->getGasH2Reg())
    {
        return GasParaH2SController_t;
    }
    else if(data == gasParaController_->getGasCl2Reg())
    {
        return GasParaCl2Controller_t;
    }
    else if(data == gasParaController_->getGasH2SReg())
    {
        return GasParaH2SController_t;
    }
    else if(data == gasParaController_->getGasCH4Reg())
    {
        return GasParaCH4Controller_t;
    }
    else if(data == gasParaController_->getGasCOReg())
    {
        return GasParaCOController_t;
    }
    else if(data == gasParaController_->getGasCO2Reg())
    {
        return GasParaCO2Controller_t;
    }
    else if(data == envParaController_->getEnvTempReg())
    {
        return EnvTempController_t;
    }
    else if(data == envParaController_->getEnvHumidityReg())
    {
        return  EnvHumidityController_t;
    }
    else if(data == envParaController_->getEnvWaterLevelReg())
    {
        return  EnvWaterLevelController_t;
    }
    return UnknowType;
}

void ProtocolManager::sendSignal(ReccType recvType,ControllerType type,QByteArray data)
{
    switch (type) {
    case TunnelGasData_t:
        emit TunnelGasDevieSig(recvType,data);
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
        emit MainControlParaSig(recvType,data);
        break;
    case GasParaO2Controller_t:
        emit GasParaO2Sig(recvType,data);
        break;
    case GasParaH2SController_t:
        emit GasParaH2Sig(recvType,data);
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
    case  UnknowType:
        break;
    default:
        break;
    }
}

void ProtocolManager::ProtocolHandle(QObject *sender,QByteArray data)
{
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
            char CRC16Lo= pData[data.size()-2];
            if((CRC16Hi == CRC16TempHi)&&(CRC16Lo==CRC16TempLo))
            {
                //
                //读寄存器返回类型//
                if(pData[1]=='\x03')
                {
                    //去掉头尾2字节
                    QByteArray master_read = data.mid(2,(data.size() - 4));
                    //根据上次操作判断是什么类型的返回
//                    if(this->recvReadTimer->isActive())
//                    {
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
                    qDebug() << "Recv X10" ;
                    getProtoTypeByReg(byteArray);
                    sendSignal(HandleWrite,getProtoTypeByReg(byteArray),master_write);
                }
                else
                {
                    qDebug()<< "ERROR";
                    return;
                }
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
  //开启接收定时器
  app()->protocolMgr()->recvTimer()->start();
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
  crc = ((crc >> 8) & 0xFF) | ((crc & 0xFF) << 8);
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





