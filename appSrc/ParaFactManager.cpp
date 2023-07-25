
#include "ParaFactManager.h"

ParaFactManager::ParaFactManager(QObject *parent)
    : QObject{parent}
    ,TunnelGasRegList(nullptr)
    ,MainConParaSetRegList(nullptr)
    ,LocalNetParaSetRegList(nullptr)
    ,NetParaSetRegList(nullptr)
    ,GasParaSetRegList(nullptr)
    ,TunnelGasDataRegList(nullptr)
    ,TunnelFanRegList(nullptr)
    ,MainControlRegList(nullptr)
{
    TunnelGasRegList       = new JsonFactGroup("TunnelGasDevice",":/TunnelGasDeviceRegList.json");
    MainConParaSetRegList  = new JsonFactGroup("MainControlParaSetting",":/MainControlParaSettingRegList.json");
    LocalNetParaSetRegList = new JsonFactGroup("LocalNetParaSetting",":/LocalNetParaSettingRegList.json");
    NetParaSetRegList      = new JsonFactGroup("NetParaSetting",":/NetParaSettingRegList.json");
    GasParaSetRegList      = new JsonFactGroup("GasParaSetting",":/GasParaSettingRegList.json");
    TunnelGasDataRegList   = new JsonFactGroup("TunnelGasData",":/TunnelGasData.json");
    TunnelFanRegList       = new JsonFactGroup("TunnelFanDevice",":/TunnelFanDeviceRegList.json");
    MainControlRegList     = new JsonFactGroup("MainControl",":/MainControlRegList.json");
}



