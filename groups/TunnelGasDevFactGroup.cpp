#include "TunnelGasDevFactGroup.h"

const char* TunnelGasDevFactGroup::tunnelGasAddressFactName_ = "TunnelGasDevAddress";
const char* TunnelGasDevFactGroup::tunnelGasformatFactName_ = "TunnelGasDevFormat";
const char* TunnelGasDevFactGroup::tunnelGasCountFactName_ = "TunnelGasCount";
const char* TunnelGasDevFactGroup::tunnelGasDataCycleFactName_= "TunnelGasDataCycle";
const char* TunnelGasDevFactGroup::tunnelGasStateCycleFactName_ = "TunnelGasStateCycle";
const char* TunnelGasDevFactGroup::tunnelGasChannelFactName_ = "TunnelGasChannel";

TunnelGasDevFactGroup::TunnelGasDevFactGroup(QObject* parent)
    :FactGroup(":/JsonProto/TunnelGasTest.json",parent)
    ,addressFact_(getFact(tunnelGasAddressFactName_))
    ,formatFact_(getFact(tunnelGasformatFactName_))
    ,countFact_(getFact(tunnelGasDataCycleFactName_))
    ,dataCycleFact_(getFact(tunnelGasDataCycleFactName_))
    ,stateCycleFact_(getFact(tunnelGasStateCycleFactName_))
    ,channelFact_(getFact(tunnelGasChannelFactName_))
{

}
//-------------------------------------------------------------------------
void  TunnelGasDevFactGroup::handleMessage(QObject *form,QByteArray data)
{



}


