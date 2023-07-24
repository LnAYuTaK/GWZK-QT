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





};

#endif // PROTOCOL_H
