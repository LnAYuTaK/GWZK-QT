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
public:
    //装置列表
    JsonFactGroup *TunnelFan(){return this->TunnelFanRegList_;}
    JsonFactGroup *TunnelGas(){return this->TunnelGasRegList_;}
    JsonFactGroup *WaterLevel(){return this->WaterLevelRegList_;}
    JsonFactGroup *WaterPump(){return this->WaterPumpRegList_;}
    //参数设置查询
    JsonFactGroup *MainConParaSet(){return this->MainConParaSetRegList_;}
    JsonFactGroup *LocalNetParaSet(){return this->LocalNetParaSetRegList_;}
    JsonFactGroup *NetParaSet(){return this->NetParaSetRegList_;}
    JsonFactGroup *GasParaO2(){return this->GasParaO2RegList_;}
    JsonFactGroup *GasParaH2(){return this->GasParaH2RegList_;}
    JsonFactGroup *GasParaCl2(){return this->GasParaCl2RegList_;}
    JsonFactGroup *GasParaH2S(){return this->GasParaH2SRegList_;}
    JsonFactGroup *GasParaCH4(){return this->GasParaCH4RegList_;}
    JsonFactGroup *GasParaCO(){return this->GasParaCORegList_;}
    JsonFactGroup *GasParaCO2(){return this->GasParaCO2RegList_;}
    JsonFactGroup *EnvParaTemp(){return this->EnvParaTempRegList_;}
    JsonFactGroup *EnvParaHumidity(){return this->EnvParaHumidityRegList_;}
    JsonFactGroup *EnvParaWaterLevel(){return this->WaterLevelRegList_;}
    JsonFactGroup *MqttParaSet(){return this->MqttParaSetRegList_;}
    //设置操作
    JsonFactGroup *MainControl(){return this->MainControlRegList_;}
    //数据召测
    JsonFactGroup *TunnelGasData(){return TunnelGasDataRegList_;}
private:
    JsonFactGroup *TunnelGasRegList_;            //隧道气体装置寄存器列表
    JsonFactGroup *MainConParaSetRegList_;       //主控参数设置寄存器列表
    JsonFactGroup *LocalNetParaSetRegList_;      //本地网络参数设置寄存器列表
    JsonFactGroup *NetParaSetRegList_;           //网络参数设置寄存器列表
    JsonFactGroup *TunnelFanRegList_;            //隧道风机装置寄存器列表
    JsonFactGroup *MainControlRegList_;          //主控操作寄存器列表
    JsonFactGroup *MqttParaSetRegList_;          //mqtt参数设置寄存器列表
    JsonFactGroup *WaterLevelRegList_;           //液位装置寄存器列表
    JsonFactGroup *WaterPumpRegList_;            //水泵装置寄存器列表
    JsonFactGroup *GasParaO2RegList_;            //氧气气体参数设置寄存器列表
    JsonFactGroup *GasParaH2RegList_;            //氢气气体参数设置寄存器列表
    JsonFactGroup *GasParaCl2RegList_;           //氯气气体参数设置寄存器列表
    JsonFactGroup *GasParaH2SRegList_;           //硫化氢气体参数设置寄存器列表
    JsonFactGroup *GasParaCH4RegList_;           //甲烷气体参数设置寄存器列表
    JsonFactGroup *GasParaCORegList_;            //一氧化碳气体参数设置寄存器列表
    JsonFactGroup *GasParaCO2RegList_;           //二氧化碳气体参数设置寄存器列表
    JsonFactGroup *EnvParaTempRegList_;          //环境温度参数设置寄存器列表
    JsonFactGroup *EnvParaHumidityRegList_;      //环境湿度参数设置寄存器列表
    JsonFactGroup *EnvParaWaterLevelRegList_;    //环境液位参数设置寄存器列表
    JsonFactGroup *TunnelGasDataRegList_;        //隧道气体数据寄存器列表
};

#endif // PARAFACTMANAGER_H
