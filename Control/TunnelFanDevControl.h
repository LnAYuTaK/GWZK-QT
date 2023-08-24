
#ifndef TUNNELFANDEVCONTROL_H
#define TUNNELFANDEVCONTROL_H


#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"

class TunnelFanDevControl : public QObject
{
    Q_OBJECT
public:
    explicit TunnelFanDevControl(QObject *parent = nullptr);
    //数量
    Q_PROPERTY(int count       READ count    WRITE setCount)
    //地址格式
    Q_PROPERTY(int format      READ format   WRITE setFormat)
    //风机地址
    Q_PROPERTY(QString address READ address  WRITE setAddress)
    //PROPERTY
    int  count() const {return count_;}
    void setCount(int count) {this->count_ = count;}
    int  format()const {return format_;}
    void setFormat(int format){this->format_ = format;}
    QString address()const {return  address_;}
    void setAddress(QString address) {this->address_ = address;}
    //Function
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    QByteArray getTunnelFanReg() {
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }
public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup *regList_;
    int count_;
    int format_;
    QString address_;
};

#endif // TUNNELFANDEVCONTROL_H
