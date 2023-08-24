
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
    //ID地址
    Q_PROPERTY(QString Address READ Address  WRITE setAddress)
    //地址格式
    Q_PROPERTY(int Format      READ Format   WRITE setFormat)
    //数量
    Q_PROPERTY(int Count       READ Count    WRITE setCount)
    //周期
    Q_PROPERTY(int Cycle       READ Cycle    WRITE setCycle)
    //通道
    Q_PROPERTY(int Channel     READ Channel  WRITE setChannel)
    //read
    QString Address()const {return  address_;}
    int  Format()const {return format_;}
    int  Count() const {return count_;}
    int  Cycle()const {return cycle_;}
    int  Channel()const {return channel_;}
    //set
    void setAddress(QString address) {this->address_ = address;}
    void setFormat(int format){this->format_ = format;}
    void setCount(int count) {this->count_ = count;}
    void setCycle(int cycle) {this->cycle_ = cycle;}
    void setChannel(int channel) {this->channel_= channel;}
    //Function
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    QByteArray getWaterLevel(){
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
signals:

};

#endif // WATERLEVELCONTROLLER_H
