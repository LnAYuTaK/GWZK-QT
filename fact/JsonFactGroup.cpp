
#include "JsonFactGroup.h"
JsonFactGroup::JsonFactGroup(QString  jsonObjName ,QString jsonfile)
{
    QResource       _res;
    QJsonParseError _error;
    _res.setFileName(jsonfile);
    if (!_res.isValid()) {
        qWarning() <<jsonfile << " Failed to load resource.";
        return;
    }
    QByteArray     jsonData = _res.uncompressedData();
    QJsonDocument  jsonDoc =  QJsonDocument::fromJson(jsonData,&_error);
    if (_error.error != QJsonParseError::NoError) {
        qWarning() << jsonfile <<" Failed to parse JSON:" << _error.errorString();
        return;
    }
    if (!jsonDoc.isObject()) {
        qWarning() <<jsonfile <<"JSON document is not an object.";
        return;
    }
    QJsonObject  jsonObj = jsonDoc.object();
    _jsonArrayObj = jsonObj[jsonObjName].toArray();

}
//-----------------------------------------------------------------------------
QVector<quint16> JsonFactGroup::getAddress()
{
    QVector<quint16>addressVector{};
    for(auto i= _jsonArrayObj.begin();i!= _jsonArrayObj.end();i++)
    {
        QJsonObject obj =  i->toObject();
        quint16 value = obj["address"].toString().toUInt(nullptr, 16);
        addressVector.push_back(value);
    }
    return addressVector;
}
//-----------------------------------------------------------------------------
QVector<QString> JsonFactGroup::getOperate()
{
    QVector<QString> operateVector{};
    for(auto i= _jsonArrayObj.begin();i!= _jsonArrayObj.end();i++)
    {
        QJsonObject obj =  i->toObject();
        QString value = obj["operate"].toString();
        operateVector.push_back(value);
    }
    return operateVector;
}
//-----------------------------------------------------------------------------
QVector<QString> JsonFactGroup::getContent()
{
    QVector<QString>contentVector{};
    for(auto i= _jsonArrayObj.begin();i!= _jsonArrayObj.end();i++)
    {
        QJsonObject obj =  i->toObject();
        QString value = obj["content"].toString();
        contentVector.push_back(value);
    }
    return contentVector;
}
//-----------------------------------------------------------------------------
QVector<QString> JsonFactGroup::getFormat()
{
    QVector<QString>formatVector{};
    for(auto i= _jsonArrayObj.begin();i!= _jsonArrayObj.end();i++)
    {
        QJsonObject obj =  i->toObject();
        QString value = obj["format"].toString();
        formatVector.push_back(value);
    }
    return formatVector;
}
//-----------------------------------------------------------------------------

