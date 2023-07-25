/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          ParaFactManager.h
 * @brief
 * @Description
 * @author        liukuan<807874484@qq.com>
 * @date          2023/06/20
 * @history
 *****************************************************************************/
#ifndef PARAFACTMANAGER_H
#define PARAFACTMANAGER_H


#include <QObject>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QJsonObject>
#include "fact/JsonFactGroup.h"
//数据格式参数管理器用于协议参数
class ParaFactManager : public QObject
{
    Q_OBJECT
public:
    explicit ParaFactManager(QObject *parent = nullptr);

signals:

public slots:

private:
    JsonFactGroup *TunnelGasRegList;            //隧道气体装置寄存器列表
    JsonFactGroup *MainConParaSetRegList;       //主控参数设置寄存器列表
    JsonFactGroup *LocalNetParaSetRegList;      //本地网络参数设置寄存器列表
    JsonFactGroup *NetParaSetRegList;           //网络参数设置寄存器列表
    JsonFactGroup *GasParaSetRegList;           //气体参数设置寄存器列表
    JsonFactGroup *TunnelGasDataRegList;        //隧道气体数据寄存器列表
    JsonFactGroup *TunnelFanRegList;            //隧道风机装置寄存器列表
    JsonFactGroup *MainControlRegList;          //主控操作寄存器列表
};

#endif // PARAFACTMANAGER_H
