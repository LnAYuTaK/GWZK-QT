
#ifndef WATERLEVELCONTROLLER_H
#define WATERLEVELCONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/ParaFactManager.h"
#include "appSrc/Application.h"
#include "appSrc/ProtocolManager.h"
class WaterLevelController : public QObject
{
    Q_OBJECT
public:
    explicit WaterLevelController(QObject *parent = nullptr);
    //数量
    Q_PROPERTY(int count       READ count    WRITE setCount   NOTIFY countChanged)
    //周期
    Q_PROPERTY(int cycle       READ cycle    WRITE setCycle   NOTIFY cycleChanged)
    //通道
    Q_PROPERTY(int channel     READ channel  WRITE setChannel NOTIFY channelChanged)
    //地址格式
    Q_PROPERTY(QString format  READ format   WRITE setFormat  NOTIFY formatChanged)
    //隧道气体地址
    Q_PROPERTY(QString address READ address  WRITE setAddress NOTIFY addressChanged)
    //Read
    int  count() const {return count_;}
    int  cycle()const {return cycle_;}
    int  channel()const {return channel_;}
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


    QByteArray getWaterLevel(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }
public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);
signals:
    void countChanged   (int count);
    void cycleChanged   (int cycle);
    void channelChanged (int channel);
    void formatChanged  (QString format);
    void addressChanged (QString address);
private:
    JsonFactGroup *regList_;
    int            count_;
    int            cycle_;
    int            channel_;
    QString        format_;
    QString        address_;


};

#endif // WATERLEVELCONTROLLER_H
