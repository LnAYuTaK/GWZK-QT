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
enum FrameType{
    ModuleSend,//主站→装置
    ModuleRecv
};
enum  ProtocolType{
    TunnelGasDevType,
    TunnelFanDevType
};

class TunnelGasDev;
class TunnelGasMonitor;
class TunnelFanControl;
class MainParaController;

class ProtocolManager : public QObject
{
    Q_OBJECT
public:
    Q_ENUM(ProtocolType)

    explicit ProtocolManager(QObject *parent = nullptr);

    Q_PROPERTY(TunnelGasDev*        TunnelGas           READ  TunnelGas          CONSTANT)
    Q_PROPERTY(TunnelGasMonitor*    TunnelGasMon        READ  TunnelGasMon       CONSTANT)
    Q_PROPERTY(TunnelFanControl*    tunnelFanControl    READ  tunnelFanControl   CONSTANT)
    Q_PROPERTY(MainParaController*  mainParaController  READ  mainParaController CONSTANT)

    TunnelGasDev    *   TunnelGas()        {return this->tunnelGasDev_;}
    TunnelGasMonitor*   TunnelGasMon()     {return this->tunnelGasMon_;}
    TunnelFanControl*   tunnelFanControl() {return this->tunnelFanControl_;}
    MainParaController* mainParaController() {return this->mainParaController_;}
    /**
     * @brief ProtocolHandle
     * @param sender
     * @param data
     */
    void ProtocolHandle(QObject *sender , QByteArray data);

    /**
     * @brief makeWriteRegProto 主站 --> 装置 写寄存器
     * @param start  寄存器起始地址2Byte
     * @param regCount 寄存器个数
     * @param Data  寄存器数据
     */
    static QByteArray makeWriteRegProto(QByteArray start,int count,QByteArray Data);

    /**
     * @brief makeReadRegProto 主站-->装置 读寄存器
     * @param start 寄存器起始地址2Byte
     * @param regCount 寄存器个数
     */
    static QByteArray makeReadRegProto(QByteArray start,int count);
    //int 转换为字节数组 2字节高低位
    static QByteArray intToHexByteArray(int data);
public slots:

signals:

private:
    static quint16 modbusCrc16(quint8 *data, qint16 length);

    TunnelGasDev     * tunnelGasDev_;
    TunnelGasMonitor * tunnelGasMon_;
    TunnelFanControl * tunnelFanControl_;
    MainParaController * mainParaController_;

};

#endif // PROTOCOL_H
