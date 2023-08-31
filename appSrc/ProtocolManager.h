/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          Protocol.h
 * @brief         Protocol
 * @Description
 * @author        liukuan<807874484@qq.com>
 * @date          2023/06/16
 * @history
 *****************************************************************************/
#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <QObject>
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QDataStream>
#include "Application.h"
class TunnelGasData;
class TunnelGasDevControl;
class TunnelFanDevControl;
class MainParaController;
class LocalNetParaController;
class NetParaController;
class MainOptController;
class MqttParaController;
class WaterLevelController;
class WaterPumpController;
class GasParaController;
class EnvParaController;

class ProtocolManager : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolManager(QObject *parent = nullptr);
    //Use Recvtype
    enum ControllerType {
        TunnelGasData_t ,
        TunnelGasDevControl_t,
        TunnelFanDevControl_t,
        MainParaController_t,
        LocalNetParaController_t,
        NetParaController_t,
        MainOptController_t,
        MqttParaController_t,
        WaterLevelController_t,
        WaterPumpController_t,
        GasParaO2Controller_t,
        GasParaH2Controller_t,
        GasParaCl2Controller_t,
        GasParaH2SController_t,
        GasParaCH4Controller_t,
        GasParaCOController_t,
        GasParaCO2Controller_t,
        EnvTempController_t,
        EnvHumidityController_t,
        EnvWaterLevelController_t,
        UnknowType
    };
    //
    enum  ParaType {
        Ip,
        Gateway,
        Mask,
        MACAddr
    };
    //接收类型信号
    enum ReccType {
      HandleRead,
      HandleWrite
    };

    enum Endian {
      LittileEndian,
      BigEndian
    };

    Q_PROPERTY(TunnelGasDevControl*     tunnelGasDevControl     READ  tunnelGasDevControl    CONSTANT)
    Q_PROPERTY(TunnelFanDevControl*     tunnelFanDevControl     READ  tunnelFanDevControl    CONSTANT)
    Q_PROPERTY(MainParaController*      mainParaController      READ  mainParaController     CONSTANT)
    Q_PROPERTY(LocalNetParaController*  localNetParaController  READ  localNetParaController CONSTANT)
    Q_PROPERTY(NetParaController*       netParaController       READ  netParaController      CONSTANT)
    Q_PROPERTY(MainOptController*       MainOptCtrl             READ  MainOptCtrl            CONSTANT)
    Q_PROPERTY(MqttParaController*      MqttParaCtrl            READ  MqttParaCtrl           CONSTANT)
    Q_PROPERTY(WaterLevelController*    WaterLevelCtrl          READ  WaterLevelCtrl         CONSTANT)
    Q_PROPERTY(WaterPumpController*     WaterPumpCtrl           READ  WaterPumpCtrl          CONSTANT)
    Q_PROPERTY(GasParaController*       GasParaCtrl             READ  GasParaCtrl            CONSTANT)
    Q_PROPERTY(EnvParaController*       EnvParaCtrl             READ  EnvParaCtrl            CONSTANT)
    Q_PROPERTY(TunnelGasData*           tunnelGasData           READ  tunnelGasData          CONSTANT)

    TunnelGasData        *  tunnelGasData()          {return this->tunnelGasData_;}
    TunnelGasDevControl*    tunnelGasDevControl()    {return this->tunnelGasDevControl_;}
    TunnelFanDevControl*    tunnelFanDevControl()    {return this->tunnelFanDevControl_;}
    MainParaController*     mainParaController()     {return this->mainParaController_;}
    LocalNetParaController* localNetParaController() {return this->localNetParaController_;}
    NetParaController *     netParaController()      {return this->netParaController_;}
    MainOptController *     MainOptCtrl()            {return this->mainOptController_;}
    MqttParaController *    MqttParaCtrl()           {return this->mqttParaController_;}
    WaterLevelController *  WaterLevelCtrl()         {return this->waterLevelController_;}
    WaterPumpController *   WaterPumpCtrl()          {return this->waterPumpConrtroller_;}
    GasParaController *     GasParaCtrl()            {return this->gasParaController_;}
    EnvParaController *     EnvParaCtrl()            {return this->envParaController_;}

    void ProtocolHandle(QObject *sender , QByteArray data);

    static QByteArray makeWriteRegProto(QByteArray start,int count,QByteArray Data);

    static QByteArray makeReadRegProto(ProtocolManager::ControllerType type,QByteArray start,int count);

    //int 转双字节QByteArray
    static QByteArray intToHexByteArray(int data);
    //int 转四字节 QByteArray
    static QByteArray intToByteArray(int number,Endian type) {
        QByteArray bytes;
        QDataStream stream(&bytes, QIODevice::WriteOnly);
        if(type == LittileEndian){
          stream.setByteOrder(QDataStream::LittleEndian); //设置字节序 - 大端
        }
        else {
          stream.setByteOrder(QDataStream::BigEndian); //设置字节序 - 大端
        }
        stream << number;  // 数字流向stream流
        return  bytes;
    }

    //将协议内所有数据拼接成quint16返回
    static QVector<quint16> getProtocolData(QByteArray data);
    //处理 网络参数字符串
    static QByteArray ParseNetLocalString(ParaType type,QString paraStr);
    //设置当前查询状态
    void setNowType(ControllerType type){ nowType_= type;}
    //拼接QByteAray
    static QVector<qint16>ByteArrayToIntVec(QByteArray byteArray);

    static QVector<QByteArray> SpiltData(QByteArray byteArray);
    //大端模式 TODO
    static short bytesToshort(QByteArray bytes)
    {
        int addr = bytes[0] & 0x000000FF;
        addr |= ((bytes[1] << 8) & 0x0000FF00);
        return addr;
    }
    //双字节QByteArray转 short
    static short bytesToshort(QByteArray bytes,Endian type)
    {
        if(type == Endian::LittileEndian)
        {
            int addr = bytes[1] & 0x000000FF;
            addr |= ((bytes[0] << 8) & 0x0000FF00);
            return addr;
        }
        else
        {
            int addr = bytes[0] & 0x000000FF;
            addr |= ((bytes[1] << 8) & 0x0000FF00);
            return addr;
        }
    }
    //大端模式
    static int byteAraryToInt(QByteArray arr, Endian endian)
    {
        if (arr.size() < 4) {
            return 0;
        }
        int res = 0;
        // 小端模式
        if (endian == LittileEndian){
            res = arr.at(0) & 0x000000FF;
            res |= (arr.at(1) << 8) & 0x0000FF00;
            res |= (arr.at(2) << 16) & 0x00FF0000;
            res |= (arr.at(3) << 24) & 0xFF000000;
        }
        // 大端模式
        else if (endian == BigEndian){
            res = (arr.at(0) << 24) & 0xFF000000;
            res |= (arr.at(1) << 16) & 0x00FF0000;
            res |= arr.at(2) << 8 & 0x0000FF00;
            res |= arr.at(3) & 0x000000FF;
        }
        return res;
    }
    //QbyteArray转QbyteArray Vector
    static QVector<QByteArray> bytesToVector(QByteArray bytes){
        QVector<QByteArray>  vectorByteArray;
        for (int i = 0; i < bytes.size(); i++) {
            QByteArray singleByte;
            singleByte.append(bytes.mid(i, 1));
            vectorByteArray.push_back(singleByte);
        }
        return vectorByteArray;
    }
    //设置QChar 置零置一
    static QChar setBit(QChar ch, int bitIndex, bool value) {
        ushort unicode = ch.unicode();
        if (value) {
            unicode |= (1 << bitIndex);
        } else {
            unicode &= ~(1 << bitIndex);
        }
        return QChar(unicode);
    }
    //获取QChar 某一位的bit值
    static bool getBitValue(const QChar& ch, int bitIndex)
    {
        int unicode = ch.unicode();
        int mask = 1 << bitIndex;  // 创建一个只有特定位为1的掩码
        bool bitValue = (unicode & mask) != 0;  // 通过位运算获取特定位的值
        return bitValue;
    }

    static int getBitValue(char c, int position) {
        // 创建一个位掩码，只有目标位为1，其余位为0
        char mask = 1 << position;
        // 将位掩码与字符进行按位与操作
        // 如果目标位为1，结果不为0；如果目标位为0，结果为0
        return (c & mask) >> position;
    }
    static int getShortBitValue(short value, int position) {
            short mask = 1 << position;
            return (value & mask) != 0 ? 1 : 0;

    }
    //两位拼接出整数
    static int mergeBits(int bit1, int bit2) {
        int result = (bit1 << 1) | bit2;
        return result;
    }
    //char tos hort
    static short CharsToShort(char highByte, char lowByte) {
        short result = 0;
        result |= highByte;                   // 将高字节赋值给结果
        result = result << 8;                 // 将结果左移8位，腾出低字节的位置
        result |= static_cast<short>(lowByte); // 将低字节赋值给结果

        return result;
    }
public slots:
    //接收超速定时器
    QTimer *recvTimer() {return this->recvReadTimer;}
signals:
    //接收到信号数据发送//
    //隧道气体装置信号
    void TunnelGasDataSig(ReccType type,QByteArray data);
    //隧道气体召测
    void TunnelGasDevSig(ReccType type,QByteArray data);
    //隧道风机装置信号
    void TunnelFunDevSig(ReccType type,QByteArray data);
    //液位装置信号
    void WaterLevelDeviceSig(ReccType type,QByteArray data);
    //水泵装置信号
    void WaterPumpDeviceSig(ReccType type,QByteArray data);
    //主控参数设置
    void MainControlParaSig(ReccType type,QByteArray data);
    //本地网络设置
    void LoaclNetParaSig(ReccType type,QByteArray data);
    //网络参数设置
    void NetparaSig(ReccType type,QByteArray data);
    //MQTT参数设置
    void MqttParaSig(ReccType type,QByteArray data);
    //主控操作设置
    void MainControlOptsSig(ReccType type,QByteArray data);
    //气体参数氧气设置
    void GasParaO2Sig(ReccType type,QByteArray data);
    //气体参数硫化氢设置
    void GasParaH2Sig(ReccType type,QByteArray data);
    //气体参数氯气设置
    void GasParaCl2Sig(ReccType type,QByteArray data);
    //气体参数氯气设置
    void GasParaH2SSig(ReccType type,QByteArray data);
    //气体参数甲烷设置
    void GasParaCH4Sig(ReccType type,QByteArray data);
    //气体参数一氧化碳设置
    void GasParaCOSig(ReccType type,QByteArray data);
    //气体参数二氧化碳参数设置
    void GasParaCO2Sig(ReccType type,QByteArray data);
    //环境温度参数设置
    void  EnvParaTempSig(ReccType type,QByteArray data);
    //环境湿度参数设置
    void  EnvParaHumiditySig(ReccType type,QByteArray data);
    //环境液位参数设置
    void  EnvParaWaterLevelSig(ReccType type,QByteArray data);
private:
    static quint16 modbusCrc16(quint8 *data, qint16 length);
    //根据寄存器值返回相应的类型
    ControllerType getProtoTypeByReg(QByteArray data);
    //根据类型发送相应的信号
    void sendSignal(ReccType recvType,ControllerType type,QByteArray data);
    TunnelGasData     *     tunnelGasData_;
    TunnelGasDevControl *   tunnelGasDevControl_;
    TunnelFanDevControl *   tunnelFanDevControl_;
    MainParaController *    mainParaController_;
    LocalNetParaController* localNetParaController_;
    NetParaController *     netParaController_;
    MainOptController *     mainOptController_;
    MqttParaController *    mqttParaController_;
    WaterLevelController *  waterLevelController_;
    WaterPumpController *   waterPumpConrtroller_;
    GasParaController *     gasParaController_;
    EnvParaController*      envParaController_;
    QTimer  *recvReadTimer;
    ControllerType nowType_;

};

#endif // PROTOCOL_H
