
#ifndef TUNNELGASDEVFACTGROUP_H
#define TUNNELGASDEVFACTGROUP_H

#include "fact/FactGroup.h"

class TunnelGasDevFactGroup : public FactGroup
{
public:
    explicit TunnelGasDevFactGroup(QObject *parent = nullptr);
//    Q_PROPERTY(Fact* blocksPending  READ blocksPending  CONSTANT)
//    Q_PROPERTY(Fact* blocksLoaded   READ blocksLoaded   CONSTANT)


};

#endif // TUNNELGASDEVFACTGROUP_H
