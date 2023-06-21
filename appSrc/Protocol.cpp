#include "Protocol.h"
#include <QThread>
#include <QDebug>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QJsonObject>
Protocol::Protocol(QObject *parent)
    : QObject{parent}
{
//         quint8 data[] = {0x10,0x21, 0x22,0x23, 0x24, 0x06, 0x31, 0x32,0x33};
//         quint16 length = sizeof(data) / sizeof(data[0]);
//        //qDebug() << QString("0x%1").arg(crc, 4, 16, QLatin1Char('0'));;
//        QVector<quint8> test{0x31,0x32,0x33};
//        QModbusRequest  f=  makeWriteReq(quint8(0x21),quint8(0x22),quint8(0x23),quint8(0x24),test);
//        QModbusRequest f =  makeReadReq(quint8(0x21),quint8(0x22),quint8(0x23),quint8(0x24));
//        QByteArray byteArray{};
//        QDataStream stream(&byteArray, QIODevice::WriteOnly);
//        stream.setByteOrder(QDataStream::BigEndian);
//        stream << f;
//        qDebug() << f;

    // 读取qrc文件中的JSON资源
//    QResource res(":/RegFact.json");
//    if (!res.isValid()) {
//        qWarning() << "Failed to load resource.";
//        return;
//    }
//    // 读取JSON数据
//    QByteArray jsonData = res.uncompressedData();
//    // 解析JSON数据
//    QJsonParseError error;
//    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);

//    if (error.error != QJsonParseError::NoError) {
//        qWarning() << "Failed to parse JSON:" << error.errorString();
//        return;
//    }

//    if (!jsonDoc.isObject()) {
//        qWarning() << "JSON document is not an object.";
//        return;
//    }
//    QJsonObject jsonObj = jsonDoc.object();
//    QJsonArray netParaSettingReg = jsonObj["NetParaSettingReg"].toArray();
//    // 遍历NetParaSettingReg数组
//    for (int i = 0; i < netParaSettingReg.size(); ++i) {
//        QJsonObject obj = netParaSettingReg[i].toObject();
//        // 读取JSON对象中的属性值
//        QString address = obj["address"].toString();
//        QString operate = obj["operate"].toString();
//        QString content = obj["content"].toString();
//        QString format = obj["format"].toString();
//        qDebug() << "address:" << address << "operate:" << operate << "content:" << content << "format:" << format;
//    }
}
//-----------------------------------------------------------------------------
/**
 * @brief Protocol::ProtocolHandle
 * @param sender
 * @param data
 */
void Protocol::ProtocolHandle(QObject *sender , QByteArray data)
{
  Q_UNUSED(sender)
  Q_UNUSED(data)
}
//-----------------------------------------------------------------------------


