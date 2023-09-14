/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          Utils.h
 * @brief
 * @Description
 * @author        liukuan<807874484@qq.com>
 * @date          2023/09/13
 * @history
 *****************************************************************************/
#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QDataStream>
class Utils : public QObject
{
    Q_OBJECT
public:
    typedef enum{
        LittileEndian,
        BigEndian
    }Endian;
    explicit Utils(QObject *parent = nullptr);
    //CRC 校验
    static quint16    ModbusCrc16   (quint8 *data, qint16 length);
    //int 转四字节ByteArray
    static QByteArray IntToBytes (int number,Endian type);
    //ByteArray 转 int
    static int        BytesToInt (QByteArray arr, Endian endian);
signals:

};

#endif // UTILS_H
