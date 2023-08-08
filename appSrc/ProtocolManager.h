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


class TunnelGasDev;
class TunnelGasMonitor;
class TunnelFanControl;
class MainParaController;
class LocalNetParaController;
class NetParaController;
class MainOptController;
class ProtocolManager : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolManager(QObject *parent = nullptr);

    Q_PROPERTY(TunnelGasDev*            TunnelGas               READ  TunnelGas              CONSTANT)
    Q_PROPERTY(TunnelGasMonitor*        TunnelGasMon            READ  TunnelGasMon           CONSTANT)
    Q_PROPERTY(TunnelFanControl*        tunnelFanControl        READ  tunnelFanControl       CONSTANT)
    Q_PROPERTY(MainParaController*      mainParaController      READ  mainParaController     CONSTANT)
    Q_PROPERTY(LocalNetParaController*  localNetParaController  READ  localNetParaController CONSTANT)
    Q_PROPERTY(NetParaController*       netParaController       READ  netParaController      CONSTANT)
    Q_PROPERTY(MainOptController*       MainOptCtrl             READ  MainOptCtrl      CONSTANT)

    TunnelGasDev    *       TunnelGas()              {return this->tunnelGasDev_;}
    TunnelGasMonitor*       TunnelGasMon()           {return this->tunnelGasMon_;}
    TunnelFanControl*       tunnelFanControl()       {return this->tunnelFanControl_;}
    MainParaController*     mainParaController()     {return this->mainParaController_;}
    LocalNetParaController* localNetParaController() {return this->localNetParaController_;}
    NetParaController *     netParaController()      {return this->netParaController_;}
    MainOptController *     MainOptCtrl()            {return this->mainOptController_;}

    /**
     * @brief ProtocolHandle 协议处理负责接收设备数据解析
     * @param sender    发送者
     * @param data      数据
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
    /**
     * @brief intToHexByteArray int 转双字节高低位Byte
     * @param data
     * @return
     */
    static QByteArray intToHexByteArray(int data);

    enum  ParaType{
        Ip,
        Gateway,
        Mask,
        MACAddr
    };

    //处理 网络参数字符串
   static QByteArray ParseNetLocalString(ParaType type,QString paraStr);

public slots:

signals:

private:
    static quint16 modbusCrc16(quint8 *data, qint16 length);

    TunnelGasDev     *      tunnelGasDev_;
    TunnelGasMonitor *      tunnelGasMon_;
    TunnelFanControl *      tunnelFanControl_;
    MainParaController *    mainParaController_;
    LocalNetParaController* localNetParaController_;
    NetParaController *     netParaController_;
    MainOptController *     mainOptController_;
};

#endif // PROTOCOL_H
