
#include "ParaFactManager.h"
ParaFactManager::ParaFactManager(QObject *parent)
    : QObject{parent}
{
    JsonFactGroup *NetPara = new JsonFactGroup("NetParaSettingReg",":/RegFact.json");
    QVector<quint16>addressVector  = NetPara->getAddress();
    for(auto &i :addressVector)
    {
        qDebug() << i;
    }





}



