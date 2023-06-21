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
////ModuBusFrame Type
enum FrameType{
    ModuleSend,//主站→装置
    ModuleRecv
};


//CRC 16校验
static  quint16 modbus_crc16(quint8 *data, qint16 length) {
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

class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = nullptr);
    void ProtocolHandle(QObject *sender , QByteArray data);
    //
signals:

private:
////    //Read读寄存器 请求  主站→装置
//    QModbusRequest makeReadReq(qint8 startAddressHi, //寄存器起始地址(高字节)
//                               qint8 startAddressLo, //寄存器起始地址(低字节)
//                               qint8 regCountHi,     //召唤寄存器个数N(高字节)
//                               qint8 regCountLo)     //召唤寄存器个数N(低字节)
//    {
//        QByteArray crcData{};
//        crcData.append(QModbusRequest::ReadHoldingRegisters). \
//            append(startAddressHi).append(startAddressLo).append(regCountHi). \
//            append(regCountLo);
//        quint16 crc = modbus_crc16((quint8*)crcData.data(), crcData.size());
//        qDebug()<< crc;
//        QByteArray data = crcData.append(quint8(crc >> 8)).append(quint8(crc & 0xFF)).remove(0,2);
//        return QModbusRequest(QModbusRequest::ReadHoldingRegisters,data);
//    }

//    //写寄存器 主站--设备
//    QModbusRequest makeWriteReq(quint8 startAddressHi,  //起始地址高位
//                                quint8 startAddressLo,  //起始地址低位
//                                quint8 regCountHi,      //写寄存器个数高位
//                                quint8 regCountLo,      //写寄存器个数低位
//                                QVector<quint8>regData) //寄存器数据Vector
//    {
//        QByteArray regTemp{};
//        for(quint8 i:regData) {
//            regTemp.append(i);
//        }
//        QByteArray  crcData{};
//        crcData.append(QModbusRequest::WriteMultipleRegisters).append(startAddressHi).append(startAddressLo).\
//            append(regCountHi).append(regCountLo).append(quint8(regData.size()*2)).append(regTemp);
//        quint16 crc = modbus_crc16((quint8*)crcData.data(), crcData.size());
//        QByteArray data = crcData.append(quint8(crc >> 8)).append(quint8(crc & 0xFF)).remove(0,2);
//        return QModbusRequest(QModbusRequest::WriteMultipleRegisters,data);
//    }
};

#endif // PROTOCOL_H
