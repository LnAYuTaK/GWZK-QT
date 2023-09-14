/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          FactGroup.h
 * @brief
 * @Description   从Json文件中加载实例化Fact
 * @author        liukuan<807874484@qq.com>
 * @date          2023/09/13
 * @history
 *****************************************************************************/
#ifndef FACTGROUP_H
#define FACTGROUP_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QDebug>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QJsonObject>
#include "Fact.h"
class FactGroup : public QObject
{
    Q_OBJECT
public:
    //通过Json文件实例化Fact
    explicit FactGroup(const QString &jsonFilename,QObject *parent = nullptr);
    //内部所有Fact名称
    Q_PROPERTY(QStringList  factNames       READ factNames       CONSTANT)
    //自身的FactGroup名称
    Q_PROPERTY(QString      factGroupName   READ factGroupName   CONSTANT)
    //从站地址
    Q_PROPERTY(QByteArray   slaveAddr       READ slaveAddr       CONSTANT)
    //寄存器总个数
    Q_PROPERTY(int          regCount        READ regCount        CONSTANT)
    //获取Fact
    Q_INVOKABLE Fact* getFact               (const QString& name);
    //查询Fact 是否存在
    Q_INVOKABLE bool  factExists            (const QString& name);
    //READ
    QStringList       factNames             (void) const {return factNames_;}
    QString           factGroupName         (void) const {return factGroupName_;}
    QByteArray        slaveAddr             (void) const {return slaveAddr_;}
    int               regCount              (void) const {return regCount_;}

protected:
    virtual void      handleMessage(QObject *form,QByteArray data);
private:
    void              addFact               (const QString& name,Fact* fact);
    //从Json文件中实例化Fact
    bool              createMapFromJsonFile (const QString& jsonFilename,QMap<QString, Fact*>& map);
    //处理Json文件header部分
    void              handleJsonFactHeader  (QJsonObject &obj);
    //处理Json文件body部分
    void              handleJsonFactBody    (QJsonArray &jsonArray);
private:
    QMap<QString, Fact*> factMap_{};
    QStringList          factNames_;
    QString              factGroupName_;
    QByteArray           slaveAddr_;
    int                  regCount_;


};

#endif // FACTGROUP_H
