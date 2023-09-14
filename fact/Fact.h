/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          Fact.h
 * @brief         基础实例
 * @Description
 * @author        liukuan<807874484@qq.com>
 * @date          2023/09/14
 * @history
 *****************************************************************************/
#ifndef FACT_H
#define FACT_H


#include <QObject>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QAbstractListModel>
#include <QMetaObject>
#include <QQmlEngine>

//用于数据基本类型统一  注意
class Fact : public QObject
{
    Q_OBJECT
public:
    typedef enum {
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
        valueTypeByteArray,
        valueKnow
    } ValueType_t;
    Q_ENUM(ValueType_t)

    explicit Fact(const QString& name ,QObject *parent  = nullptr);
    //名称
    Q_PROPERTY(QString     name           READ  name          CONSTANT)
    //起始地址
    Q_PROPERTY(QByteArray  slaveAddr      READ  slaveAddr     CONSTANT)
    //寄存器个数
    Q_PROPERTY(int         regCount       READ  regCount      CONSTANT)
    //unit
    Q_PROPERTY(QString     unit           READ  unit          CONSTANT)
    //type
    Q_PROPERTY(ValueType_t type           READ  type          CONSTANT)
    //描述
    Q_PROPERTY(QString     description    READ  description   CONSTANT)
    //是否可读
    Q_PROPERTY(bool        readEnable     READ  readEnable     CONSTANT)
    //是否可写
    Q_PROPERTY(bool        writeEnable    READ  writeEnable    CONSTANT)
    //实际值
    Q_PROPERTY(QVariant    value          READ  value         WRITE setValue    NOTIFY valueChanged)
    //READ
    QString     name          () const {return name_;}
    QByteArray  slaveAddr     () const {return slaveAddr_;}
    int         regCount      () const {return regCount_;}
    QString     unit          () const {return unit_;}
    ValueType_t type          () const {return type_;}
    QString     description   () const {return description_;}
    bool        writeEnable   () const {return writeEnable_;}
    bool        readEnable    () const {return readEnable_;}
    QVariant    value         () const {return value_;}
    //WRITE
    void setName         (const QString& name)     { name_ = name;}
    void setSlaveAddr    (const QByteArray &bytes) { slaveAddr_ =  bytes;}
    void setRegCount     (const int count)         { regCount_  = count;}
    void setUnit         (const QString& unit)     { unit_ = unit;}
    void setType         (const ValueType_t type)     { type_ = type;}
    void setDescription  (const QString& desc)     { description_ = desc;}
    void setValue        (const QVariant& value);
    void setReadEnable   (bool  bValue)            { readEnable_  = bValue; }
    void setWriteEnable  (bool  bValue)            { writeEnable_ = bValue; }

    static ValueType_t          StringToValueType(const QString& typeString);
    static QString              TypeToValueString(ValueType_t type);
signals:
    void   valueChanged         (QVariant value);
private:
    static const char*          typeStrings_[];
    static const ValueType_t    valueTypes_[];
    QString                     name_;
    QByteArray                  slaveAddr_;
    int                         regCount_;
    QString                     unit_;
    ValueType_t                 type_;
    QString                     description_;
    bool                        readEnable_;
    bool                        writeEnable_;
    QVariant                    value_;

};

#endif // FACT_H
