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
#include "TunnelGasDev.h"
enum FrameType{
    ModuleSend,//主站→装置
    ModuleRecv
};
enum  ProtocolType{
    TunnelGasDevType,
    TunnelFanDevType
};

class ProtocolManager : public QObject
{
    Q_OBJECT
public:
    Q_ENUM(ProtocolType)
    explicit ProtocolManager(QObject *parent = nullptr);

    Q_PROPERTY(TunnelGasDev*  TunnelGas  READ  TunnelGas CONSTANT)

    Q_INVOKABLE void PrintF(){qDebug()<< "2323";}

    TunnelGasDev  *TunnelGas(){return this->tunnelGasDev_;}
    //协议流处理
    void ProtocolHandle(QObject *sender , QByteArray data);
    //设置单元
    Q_INVOKABLE void SetUnit(int type);
    //查询单元
    Q_INVOKABLE void GetUnit(int type);
signals:

private:
    quint16 modbusCrc16(quint8 *data, qint16 length);

    TunnelGasDev  *tunnelGasDev_;
};

#endif // PROTOCOL_H
