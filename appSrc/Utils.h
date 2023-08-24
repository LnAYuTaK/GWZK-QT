
#ifndef UTILS_H
#define UTILS_H

#include <QObject>


class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);

    static void splitQuint16(quint16 value, char& highByte, char& lowByte) {
        highByte = static_cast<char>((value >> 8) & 0xFF);
        lowByte = static_cast<char>(value & 0xFF);
    }


signals:

};

#endif // UTILS_H
