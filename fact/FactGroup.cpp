
#include "FactGroup.h"
#include "qjsondocument.h"

FactGroup::FactGroup(const QString& jsonFilename,QObject *parent)
    : QObject{parent}
    ,factGroupName_("")
{
    createMapFromJsonFile(jsonFilename,factMap_);
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}
//--------------------------------------------------------------------------------------
Fact * FactGroup::getFact(const QString &name)
{
    Fact*   fact =  nullptr;
    if (factMap_.contains(name)) {
        fact = factMap_[name];
        QQmlEngine::setObjectOwnership(fact, QQmlEngine::CppOwnership);
    } else {
        qWarning() << "Unknown Fact" << name;
    }
    return fact;
}
//--------------------------------------------------------------------------------------
bool FactGroup::factExists(const QString& name)
{  
   return  factMap_.contains(name);
}
//----------------------------------------------------------------------------------------
void FactGroup::addFact(const QString& name,Fact* fact)
{
   if (factMap_.contains(name)) {
        qWarning() << "Duplicate Fact" << name;
        return;
   }
   factMap_.insert(name,fact);
}
//----------------------------------------------------------------------------------------
void FactGroup::handleMessage(QObject *from,QByteArray data)
{

}
//----------------------------------------------------------------------------------------
bool  FactGroup::createMapFromJsonFile(const QString& jsonFilename,QMap<QString, Fact*>& map)
{
  //实例化Fact //TUDO
    QResource       _res;
    QJsonParseError _error;
    _res.setFileName(jsonFilename);
    if (!_res.isValid()) {
        qWarning() <<jsonFilename << " Failed to load resource.";
        return false;
    }
    QByteArray     jsonData = _res.uncompressedData();
    QJsonDocument  jsonDoc =  QJsonDocument::fromJson(jsonData,&_error);
    if (_error.error != QJsonParseError::NoError) {
        qWarning() << jsonFilename <<" Failed to parse JSON:" << _error.errorString();
        return false;
    }
    if (!jsonDoc.isObject()) {
        qWarning() <<jsonFilename <<"JSON document is not an object.";
        return false;
    }
    //处理header
    QJsonObject  jsonObj = jsonDoc.object();
    if(jsonObj.keys().contains("header")){
        handleJsonFactHeader(jsonObj);
    }
    //处理body
    if(jsonObj.keys().contains("body")){
       QJsonArray  bodyArray = jsonObj["body"].toArray();
       handleJsonFactBody(bodyArray);
    }
    return true;
}

//-----------------------------------------------------------------------------------------
void   FactGroup::handleJsonFactHeader(QJsonObject &jsonObj)
{
    QJsonObject jsonHeader = jsonObj["header"].toObject();
    factGroupName_         = jsonHeader["name"].toString();
    QString slaveAddr      = jsonHeader["slaveAddr"].toString();
    slaveAddr.remove(0, 2); // 去除开头的"0x"
    slaveAddr_             = QByteArray::fromHex(slaveAddr.toLatin1());
    regCount_              = jsonHeader["count"].toInt();
}
//-----------------------------------------------------------------------------------------
void FactGroup::handleJsonFactBody(QJsonArray &jsonArray)
{
    for(auto i= jsonArray.begin();i!= jsonArray.end();i++)
    {
       QJsonObject obj =  i->toObject();
       factNames_ = obj.keys();
       foreach (QString key, factNames_) {
           //实例化Fact
           Fact *fact = new Fact(key,this);
           QJsonArray fieldArray = obj[key].toArray();
           if (!fieldArray.isEmpty() && fieldArray[0].isObject()) {
               QJsonObject fieldObj = fieldArray[0].toObject();
               //SlaveAddr
               if (fieldObj.contains("slaveAddr") && fieldObj["slaveAddr"].isString()) {
                   QString slaveAddr= fieldObj["slaveAddr"].toString();
                   QByteArray bytes =  slaveAddr.remove(0, 2).toLatin1();
                   fact->setSlaveAddr(bytes);
               }
               //count
               if (fieldObj.contains("count") && fieldObj["count"].isString()) {
                   int count= fieldObj["count"].toInt();
                   fact->setRegCount(count);
               }
               //operate
               if (fieldObj.contains("operate") && fieldObj["operate"].isString()) {
                   QString operate = fieldObj["operate"].toString();
                   if(operate.compare("R",Qt::CaseInsensitive)){
                       fact->setReadEnable(true);
                   }
                   else if(operate.compare("W",Qt::CaseInsensitive)){
                       fact->setWriteEnable(true);
                   }
                   else if(operate.compare("R/W",Qt::CaseInsensitive)){
                       fact->setReadEnable(true);
                       fact->setWriteEnable(true);
                   }
               }
               //valueType
               if (fieldObj.contains("valueType") && fieldObj["valueType"].isString()) {
                   QString valueType= fieldObj["valueType"].toString();
                   fact->setType(Fact::StringToValueType(valueType));
               }
               //unit
               if (fieldObj.contains("unit") && fieldObj["unit"].isString()) {
                   QString unit= fieldObj["unit"].toString();
                   fact->setUnit(unit);
               }
               if (fieldObj.contains("describe") && fieldObj["describe"].isString()) {
                   QString describe= fieldObj["describe"].toString();
                   fact->setDescription(describe);
               } 
           }
           addFact(key,fact);
       }
    }
}


