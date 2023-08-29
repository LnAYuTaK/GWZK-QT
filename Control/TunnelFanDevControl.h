
#ifndef TUNNELFANDEVCONTROL_H
#define TUNNELFANDEVCONTROL_H


#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"
//装置列表 隧道风机
class TunnelFanDevControl : public QObject
{
    Q_OBJECT
public:
    explicit TunnelFanDevControl(QObject *parent = nullptr);
    //数量
    Q_PROPERTY(int count       READ count    WRITE setCount   NOTIFY countChanged)
    //地址格式
    Q_PROPERTY(QString format  READ format   WRITE setFormat  NOTIFY formatChanged)
    //风机地址
    Q_PROPERTY(QString address READ address  WRITE setAddress NOTIFY addressChanged)
    //Read
    int  count() const {return count_;}
    QString  format()const {return format_;}
    QString address()const {return  address_;}
    //Set
    void setCount(int count) {
        this->count_ = count;
        emit  countChanged(count_);
    }
    void setFormat(QString format){
        this->format_ = format;
        emit formatChanged(format_);
    }
    void setAddress(QString address) {
        this->address_ = address;
        emit addressChanged(address_);
    }
    //Function
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    QByteArray getTunnelFanReg() {
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }
public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);
signals:
    void countChanged(int count);
    void formatChanged(QString format);
    void addressChanged(QString address);
private:
    JsonFactGroup *regList_;
    int count_;
    QString format_;
    QString address_;
};

#endif // TUNNELFANDEVCONTROL_H
