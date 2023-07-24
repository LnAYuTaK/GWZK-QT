
#include "ParaFactManager.h"
ParaFactManager::ParaFactManager(QObject *parent)
    : QObject{parent}
    ,TunnelGasRegList(nullptr)
    ,MainConParaSetRegList(nullptr)
    ,LocalNetParaSetRegList(nullptr)
    ,NetParaSetRegList(nullptr)
    ,GasParaSetRegList(nullptr)
{
    JsonFactGroup *NetPara = new JsonFactGroup("NetParaSetting",":/NetParaSettingRegList.json");

    QVector<quint16>addressVector  = NetPara->getAddress();
    for(auto i : addressVector)
    {
        qDebug() << i;
    }




}



