/******************************************************************************
 * Copyright 2023-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file          FactGroup.h
 * @brief
 * @Description   JsonValue Readhelper
 * @author        liukuan<807874484@qq.com>
 * @date          2023/06/20
 * @history
 *****************************************************************************/
#ifndef JSONFACTGROUP_H
#define JSONFACTGROUP_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QJsonObject>

class JsonFactGroup : public QObject
{
    Q_OBJECT

public:
    explicit JsonFactGroup(QString jsonObjName,QString jsonfile);

    QVector<QString> getAddress();

    QVector<QString> getOperate();

    QVector<QString> getContent();

    QVector<QString> getFormat();

    int              getRegConunt();
signals:

private:
    QJsonArray     _jsonArrayObj;
    QVector<quint16>  data;

};

#endif // JSONFACTGROUP_H
