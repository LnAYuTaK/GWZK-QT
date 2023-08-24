
#ifndef TUNNELGASDEVCONTROLH_H
#define TUNNELGASDEVCONTROLH_H


#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include  "appSrc/ParaFactManager.h"
#include "appSrc/Application.h"
#include "appSrc/ProtocolManager.h"
class TunnelGasDevControl : public QObject
{
    Q_OBJECT
public:
    explicit TunnelGasDevControl(QObject *parent = nullptr);
    //数量
    Q_PROPERTY(int count       READ count    WRITE setCount)
    //周期
    Q_PROPERTY(int cycle       READ cycle    WRITE setCycle)
    //通道
    Q_PROPERTY(int channel     READ channel  WRITE setChannel)
    //地址格式
    Q_PROPERTY(int format      READ format   WRITE setFormat)
    //隧道气体地址
    Q_PROPERTY(QString address READ address  WRITE setAddress)
    //FUNCTION
    int  count() const {return count_;}
    void setCount(int count) {this->count_ = count;}
    int  cycle()const {return cycle_;}
    void setCycle(int cycle) {this->cycle_ = cycle;}
    int  channel()const {return channel_;}
    void setChannel(int channel) {this->channel_= channel;}
    int  format()const {return format_;}
    void setFormat(int format){this->format_ = format;}
    QString address()const {return  address_;}
    void setAddress(QString address) {this->address_ = address;}
    //Function
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    QByteArray getTunnelGasDev()
    {
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup *regList_;
    int            count_;
    int            cycle_;
    int            channel_;
    int            format_;
    QString        address_;
};

#endif // TUNNELGASDEVCONTROLH_H
