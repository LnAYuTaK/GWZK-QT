
#include "ParaFactManager.h"

ParaFactManager::ParaFactManager(QObject *parent)
    : QObject{parent}
    ,TunnelGasRegList_(nullptr)
    ,MainConParaSetRegList_(nullptr)
    ,LocalNetParaSetRegList_(nullptr)
    ,NetParaSetRegList_(nullptr)
    ,TunnelGasDataRegList_(nullptr)
    ,TunnelFanRegList_(nullptr)
    ,MainControlRegList_(nullptr)
    ,MqttParaSetRegList_(nullptr)
    ,WaterLevelRegList_(nullptr)
    ,WaterPumpRegList_(nullptr)
    ,GasParaO2RegList_(nullptr)
    ,GasParaH2RegList_(nullptr)
    ,GasParaCl2RegList_(nullptr)
    ,GasParaH2SRegList_(nullptr)
    ,GasParaCH4RegList_(nullptr)
    ,GasParaCORegList_(nullptr)
    ,GasParaCO2RegList_(nullptr)
    ,EnvParaTempRegList_(nullptr)
    ,EnvParaHumidityRegList_(nullptr)
    ,EnvParaWaterLevelRegList_(nullptr)
    ,SensorEnableRegList_(nullptr)
    ,WaterLevelDataRegList_(nullptr)
{
    //隧道气体装置寄存器列表
    TunnelGasRegList_         = new JsonFactGroup("TunnelGasDevice",":/JsonProto/TunnelGasDevice.json");
    //主控参数设置寄存器列表
    MainConParaSetRegList_    = new JsonFactGroup("MasterPara",":/JsonProto/MasterPara.json");
    //本地网络参数设置寄存器列表
    LocalNetParaSetRegList_   = new JsonFactGroup("LocalNetPara",":/JsonProto/LocalNetPara.json");
    //网络参数设置寄存器列表
    NetParaSetRegList_        = new JsonFactGroup("NetPara",":/JsonProto/NetPara.json");
    //隧道气体数据召测寄存器列表
    TunnelGasDataRegList_     = new JsonFactGroup("TunnelGasData",":/JsonProto/TunnelGasData.json");
    //隧道风机装置寄存器列表
    TunnelFanRegList_         = new JsonFactGroup("TunnelFanDevice",":/JsonProto/TunnelFanDevice.json");
    //主控操作寄存器列表
    MainControlRegList_       = new JsonFactGroup("MasterOpt",":/JsonProto/MasterOpt.json");
    //mqtt参数设置寄存器列表
    MqttParaSetRegList_       = new JsonFactGroup("MqttPara",":/JsonProto/MqttPara.json");
    //液位装置寄存器列表
    WaterLevelRegList_        = new JsonFactGroup("WaterLevelDevice",":/JsonProto/WaterLevelDevice.json");
    //水泵装置寄存器列表
    WaterPumpRegList_         = new JsonFactGroup("WaterPumpDevice",":/JsonProto/WaterPumpDevice.json");
    //氧气气体参数设置寄存器列表
    GasParaO2RegList_         = new JsonFactGroup("GasParaO2",":/JsonProto/GasPara.json");
    //氢气气体参数设置寄存器列表
    GasParaH2RegList_         = new JsonFactGroup("GasParaH2",":/JsonProto/GasPara.json");
    //氯气气体参数设置寄存器列表
    GasParaCl2RegList_        = new JsonFactGroup("GasParaCl2",":/JsonProto/GasPara.json");
    //硫化氢气体参数设置寄存器列表
    GasParaH2SRegList_        = new JsonFactGroup("GasParaH2S",":/JsonProto/GasPara.json");
    //甲烷气体参数设置寄存器列表
    GasParaCH4RegList_        = new JsonFactGroup("GasParaCH4",":/JsonProto/GasPara.json");
    //一氧化碳气体参数设置寄存器列表
    GasParaCORegList_         = new JsonFactGroup("GasParaCO",":/JsonProto/GasPara.json");
    //二氧化碳气体参数设置寄存器列表
    GasParaCO2RegList_         = new JsonFactGroup("GasParaCO2",":/JsonProto/GasPara.json");
    //环境温度参数设置寄存器列表
    EnvParaTempRegList_       = new JsonFactGroup("TemperaturePara",":/JsonProto/EnvPara.json");
    //环境湿度参数设置寄存器列表
    EnvParaHumidityRegList_   = new JsonFactGroup("HumidityPara",":/JsonProto/EnvPara.json");
    //环境液位参数设置寄存器列表
    EnvParaWaterLevelRegList_ = new JsonFactGroup("WaterLevelPara",":/JsonProto/EnvPara.json");
    //传感器使能寄存器列表
    SensorEnableRegList_      = new JsonFactGroup("SensorEnable",":/JsonProto/SensorEnable.json");
    //液位数据寄存器列表
    WaterLevelDataRegList_    = new JsonFactGroup("WaterLevelData",":/JsonProto/WaterLevelData.json");
}





