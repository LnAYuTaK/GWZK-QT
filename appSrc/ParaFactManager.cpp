
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
    TunnelGasRegList_       = new JsonFactGroup("TunnelGasDevice",":/JsonProto/TunnelGasDevice.json");
    //主控参数设置寄存器列表
    MainConParaSetRegList_  = new JsonFactGroup("MainControlParaSetting",":/JsonProto/MainControlParaSettingRegList.json");
    //本地网络参数设置寄存器列表
    LocalNetParaSetRegList_ = new JsonFactGroup("LocalNetParaSetting",":/JsonProto/LocalNetParaSettingRegList.json");
    //网络参数设置寄存器列表
    NetParaSetRegList_      = new JsonFactGroup("NetParaSetting",":/JsonProto/NetParaSettingRegList.json");
    //气体参数设置寄存器列表
    GasParaSetRegList_      = new JsonFactGroup("GasParaSetting",":/JsonProto/GasParaSettingRegList.json");
    //隧道气体数据寄存器列表
    TunnelGasDataRegList_   = new JsonFactGroup("TunnelGasData",":/JsonProto/TunnelGasData.json");
    //隧道风机装置寄存器列表
    TunnelFanRegList_       = new JsonFactGroup("TunnelFanDevice",":/JsonProto/TunnelFanDeviceRegList.json");
    //主控操作寄存器列表
    MainControlRegList_     = new JsonFactGroup("MainControl",":/JsonProto/MainControlRegList.json");
}



