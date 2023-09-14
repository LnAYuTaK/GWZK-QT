
#ifndef TUNNELGASDEVFACTGROUP_H
#define TUNNELGASDEVFACTGROUP_H

#include "fact/FactGroup.h"

class TunnelGasDevFactGroup : public FactGroup
{
public:
    explicit TunnelGasDevFactGroup(QObject *parent = nullptr);
    Q_PROPERTY(Fact* address       READ address       CONSTANT)
    Q_PROPERTY(Fact* format        READ format        CONSTANT)
    Q_PROPERTY(Fact* count         READ count         CONSTANT)
    Q_PROPERTY(Fact* dataCycle     READ datacycle     CONSTANT)
    Q_PROPERTY(Fact* stateCycle    READ stateCycle    CONSTANT)
    Q_PROPERTY(Fact* channel       READ channel       CONSTANT)
    //READ
    Fact *address()       {return addressFact_;}
    Fact *format()        {return formatFact_;}
    Fact *count()         {return countFact_;}
    Fact *dataCycle()     {return dataCycleFact_;}
    Fact *stateCycle()    {return stateCycleFact_;}
    Fact *channel()       {return channelFact_;}

protected:
    void   handleMessage(QObject *form,QByteArray data) override;
private:
    static const char* tunnelGasAddressFactName_;
    static const char* tunnelGasformatFactName_;
    static const char* tunnelGasCountFactName_;
    static const char* tunnelGasDataCycleFactName_;
    static const char* tunnelGasStateCycleFactName_;
    static const char* tunnelGasChannelFactName_;
private:
    //Fact
    Fact *addressFact_;
    Fact *formatFact_;
    Fact *countFact_;
    Fact *dataCycleFact_;
    Fact *stateCycleFact_;
    Fact *channelFact_;
};

#endif // TUNNELGASDEVFACTGROUP_H
