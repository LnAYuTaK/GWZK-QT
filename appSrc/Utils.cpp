
#include "Utils.h"

Utils::Utils(QObject *parent)
    : QObject{parent}
{

}
//-----------------------------------------------------------------
quint16  Utils::ModbusCrc16   (quint8 *data, qint16 length)
{
    quint16 crc = 0xFFFF;
    for (quint16 i = 0; i < length; ++i) {
        crc ^= data[i];

        for (quint8 j = 0; j < 8; ++j) {
            if (crc & 0x0001) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}
//-----------------------------------------------------------------
QByteArray Utils::IntToBytes (int number,Endian type)
{
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    if(type == Utils::LittileEndian){
        stream.setByteOrder(QDataStream::LittleEndian); //设置字节序 - 大端
    }
    else {
        stream.setByteOrder(QDataStream::BigEndian); //设置字节序 - 大端
    }
    stream << number;  // 数字流向stream流
    return  bytes;
}
//-----------------------------------------------------------------
int Utils::BytesToInt (QByteArray arr, Endian endian)
{
    if (arr.size() < 4) {
        return 0;
    }
    int res = 0;
    // 小端模式
    if (endian == LittileEndian) {
        res = arr.at(0) & 0x000000FF;
        res |= (arr.at(1) << 8) & 0x0000FF00;
        res |= (arr.at(2) << 16) & 0x00FF0000;
        res |= (arr.at(3) << 24) & 0xFF000000;
    }
    // 大端模式
    else if (endian == BigEndian) {
        res = (arr.at(0) << 24) & 0xFF000000;
        res |= (arr.at(1) << 16) & 0x00FF0000;
        res |= arr.at(2) << 8 & 0x0000FF00;
        res |= arr.at(3) & 0x000000FF;
    }
    return res;
}
//-----------------------------------------------------------------
