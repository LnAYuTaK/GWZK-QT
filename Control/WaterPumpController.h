
#ifndef WATERPUMPCONTROLLER_H
#define WATERPUMPCONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"
//液位装置
class WaterPumpController : public QObject
{
    Q_OBJECT
public:
    explicit WaterPumpController(QObject *parent = nullptr);
    //ID地址
    Q_PROPERTY(QString Address READ Address  WRITE setAddress)
    //地址格式
    Q_PROPERTY(int Format      READ Format   WRITE setFormat)
    //数量
    Q_PROPERTY(int Count       READ Count    WRITE setCount)
    //read
    QString Address()const {return  address_;}
    int  Format()const {return format_;}
    int  Count() const {return count_;}
    //set
    void setAddress(QString address) {this->address_ = address;}
    void setFormat(int format){this->format_ = format;}
    void setCount(int count) {this->count_ = count;}

    //Function
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    QByteArray getWaterPumpReg(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup *regList_;
    QString        address_;
    int            format_;
    int            count_;
};

#endif // WATERPUMPCONTROLLER_H
