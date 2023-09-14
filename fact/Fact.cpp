
#include "Fact.h"

const char* Fact::typeStrings_[] = {
    "Uint8",
    "Int8",
    "Uint16",
    "Int16",
    "Uint32",
    "Int32",
    "Uint64",
    "Int64",
    "Float",
    "Double",
    "String",
    "Bool",
    "ByteArray",
};

const Fact::ValueType_t Fact::valueTypes_[] = {
    valueTypeUint8,
    valueTypeInt8,
    valueTypeUint16,
    valueTypeInt16,
    valueTypeUint32,
    valueTypeInt32,
    valueTypeUint64,
    valueTypeInt64,
    valueTypeFloat,
    valueTypeDouble,
    valueTypeString,
    valueTypeBool,
    valueTypeByteArray
};

Fact::Fact(const QString& name,QObject *parent)
    : QObject{parent}
    , name_(name)
    , slaveAddr_(QByteArray(2,'\x00'))
    , regCount_(0)
    , unit_("")
    , type_(valueKnow)
    , description_("")
    , readEnable_(false)
    , writeEnable_(false)
    , value_(0)
{
  //交付管理权//
  QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}
//--------------------------------------------------------------------
void Fact::setValue(const QVariant& value)
{
  value_ = value;
  emit valueChanged(value_);
}
//--------------------------------------------------------------------
Fact::ValueType_t Fact::StringToValueType(const QString& typeString)
{
  for (size_t i=0; i<sizeof(typeStrings_)/sizeof(typeStrings_[0]); i++) {
      if (typeString.compare(typeStrings_[i], Qt::CaseInsensitive) == 0) {
          return valueTypes_[i];
      }
  }
  return valueKnow;
}
//--------------------------------------------------------------------
QString  Fact::TypeToValueString(Fact::ValueType_t type)
{
  for (size_t i=0; i<sizeof(typeStrings_)/sizeof(typeStrings_[0]); i++) {
      if (type == valueTypes_[i]) {
          return typeStrings_[i];
      }
  }
  return QStringLiteral("UnknownType%1").arg(type);
}
//--------------------------------------------------------------------





















