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


class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = nullptr);


    void ProtocolHandle(QObject *sender , QByteArray data);
signals:

};

#endif // PROTOCOL_H
