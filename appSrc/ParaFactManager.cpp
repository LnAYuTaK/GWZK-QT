
#include "ParaFactManager.h"

ParaFactManager::ParaFactManager(QObject *parent)
    : QObject{parent}
    ,TunnelGasRegList_(nullptr)
    ,MainConParaSetRegList_(nullptr)
    ,LocalNetParaSetRegList_(nullptr)
    ,NetParaSetRegList_(nullptr)
    ,GasParaSetRegList_(nullptr)
    ,TunnelGasDataRegList_(nullptr)
    ,TunnelFanRegList_(nullptr)
    ,MainControlRegList_(nullptr)
{
    //隧道气体装置寄存器列表
    TunnelGasRegList_       = new JsonFactGroup("TunnelGasDevice",":/TunnelGasDevice.json");
    //主控参数设置寄存器列表
    MainConParaSetRegList_  = new JsonFactGroup("MainControlParaSetting",":/MainControlParaSettingRegList.json");
    //本地网络参数设置寄存器列表
    LocalNetParaSetRegList_ = new JsonFactGroup("LocalNetParaSetting",":/LocalNetParaSettingRegList.json");
    //网络参数设置寄存器列表
    NetParaSetRegList_      = new JsonFactGroup("NetParaSetting",":/NetParaSettingRegList.json");
    //气体参数设置寄存器列表
    GasParaSetRegList_      = new JsonFactGroup("GasParaSetting",":/GasParaSettingRegList.json");
    //隧道气体数据寄存器列表
    TunnelGasDataRegList_   = new JsonFactGroup("TunnelGasData",":/TunnelGasData.json");
    //隧道风机装置寄存器列表
    TunnelFanRegList_       = new JsonFactGroup("TunnelFanDevice",":/TunnelFanDeviceRegList.json");
    //主控操作寄存器列表
    MainControlRegList_     = new JsonFactGroup("MainControl",":/MainControlRegList.json");
}



