
#ifndef TUNNELGASDEVCONTROLH_H
#define TUNNELGASDEVCONTROLH_H


#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include  "appSrc/ParaFactManager.h"
#include "appSrc/Application.h"
#include "appSrc/ProtocolManager.h"
//装置列表 隧道气体
class TunnelGasDevControl : public QObject
{
    Q_OBJECT
public:
    explicit TunnelGasDevControl(QObject *parent = nullptr);
    //数量
    Q_PROPERTY(int count       READ count       WRITE setCount        NOTIFY countChanged)
    //数据周期
    Q_PROPERTY(int cycle       READ cycle       WRITE setCycle        NOTIFY cycleChanged)
    //状态周期
    Q_PROPERTY(int stateCycle  READ stateCycle  WRITE setStateCycle   NOTIFY stateCycleChanged)
    //状态周期
    Q_PROPERTY(int channel     READ channel     WRITE setChannel      NOTIFY channelChanged)
    //地址格式
    Q_PROPERTY(QString format  READ format      WRITE setFormat       NOTIFY formatChanged)
    //隧道气体地址
    Q_PROPERTY(QString address READ address     WRITE setAddress      NOTIFY addressChanged)
    //Read
    int  count() const {return count_;}
    int  cycle()const {return cycle_;}
    int  channel()const {return channel_;}
    int  stateCycle()const {return stateCycle_;}
    QString format()const {return format_;}
    QString address()const {return  address_;}

    //Set
    void setCount(int count) {
        this->count_ = count;
        emit countChanged(count_);
    }
    void setCycle(int cycle) {
        this->cycle_ = cycle;
        emit cycleChanged(cycle_);
    }
    void setChannel(int channel) {
        this->channel_= channel;
        emit channelChanged(channel_);
    }
    void setStateCycle(int stateCycle) {
        this->stateCycle_ = stateCycle;
        emit stateCycleChanged(stateCycle_);
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

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

signals:
    void countChanged       (int count);
    void cycleChanged       (int cycle);
    void stateCycleChanged  (int stateCycle);
    void channelChanged     (int channel);
    void formatChanged      (QString format);
    void addressChanged     (QString address);
private:
    JsonFactGroup *regList_;
    int            count_;
    int            cycle_;
    int            stateCycle_;
    int            channel_;
    QString        format_;
    QString        address_;
};

#endif // TUNNELGASDEVCONTROLH_H
