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

class ParaFactManager : public QObject
{
    Q_OBJECT
public:
    explicit ParaFactManager(QObject *parent = nullptr);

signals:
public slots:
public:
    JsonFactGroup *TunnelGas(){return this->TunnelGasRegList_;}
    JsonFactGroup *MainConParaSet(){return this->MainConParaSetRegList_;}
    JsonFactGroup *LocalNetParaSet(){return this->LocalNetParaSetRegList_;}
    JsonFactGroup *NetParaSet(){return this->NetParaSetRegList_;}
    JsonFactGroup *GasParaSet(){return this->GasParaSetRegList_;}
    JsonFactGroup *TunnelGasData(){return TunnelGasRegList_;}
    JsonFactGroup *TunnelFan(){return this->TunnelFanRegList_;}
    JsonFactGroup *MainControl(){return this->MainControlRegList_;}

private:
    JsonFactGroup *TunnelGasRegList_;            //隧道气体装置寄存器列表
    JsonFactGroup *MainConParaSetRegList_;       //主控参数设置寄存器列表
    JsonFactGroup *LocalNetParaSetRegList_;      //本地网络参数设置寄存器列表
    JsonFactGroup *NetParaSetRegList_;           //网络参数设置寄存器列表
    JsonFactGroup *GasParaSetRegList_;           //气体参数设置寄存器列表
    JsonFactGroup *TunnelGasDataRegList_;        //隧道气体数据寄存器列表
    JsonFactGroup *TunnelFanRegList_;            //隧道风机装置寄存器列表
    JsonFactGroup *MainControlRegList_;          //主控操作寄存器列表
};

#endif // PARAFACTMANAGER_H
