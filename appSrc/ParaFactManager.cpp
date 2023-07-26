
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
    TunnelGasRegList_       = new JsonFactGroup("TunnelGasDevice",":/TunnelGasDeviceRegList.json");
    MainConParaSetRegList_  = new JsonFactGroup("MainControlParaSetting",":/MainControlParaSettingRegList.json");
    LocalNetParaSetRegList_ = new JsonFactGroup("LocalNetParaSetting",":/LocalNetParaSettingRegList.json");
    NetParaSetRegList_      = new JsonFactGroup("NetParaSetting",":/NetParaSettingRegList.json");
    GasParaSetRegList_      = new JsonFactGroup("GasParaSetting",":/GasParaSettingRegList.json");
    TunnelGasDataRegList_   = new JsonFactGroup("TunnelGasData",":/TunnelGasData.json");
    TunnelFanRegList_       = new JsonFactGroup("TunnelFanDevice",":/TunnelFanDeviceRegList.json");
    MainControlRegList_     = new JsonFactGroup("MainControl",":/MainControlRegList.json");
}



