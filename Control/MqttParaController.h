
#ifndef MQTTPARACONTROLLER_H
#define MQTTPARACONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"

class MqttParaController : public QObject
{
    Q_OBJECT
public:
    explicit MqttParaController(QObject *parent = nullptr);
    //mqttip地址
    Q_PROPERTY(QString MqttIp   READ MqttIp  WRITE setMqttIp)
    //mqttIP端口号
    Q_PROPERTY(int MqttPort   READ MqttPort  WRITE setMqttPort)
    //MqttclientIP
    Q_PROPERTY(QString MqttClientId   READ MqttClientId  WRITE setMqttClientId)
    //Mqtt用户名
    Q_PROPERTY(QString MqttUserName   READ MqttUserName  WRITE setMqttUserName)
    //Mqtt密码
    Q_PROPERTY(QString MqttPasswd   READ MqttPasswd  WRITE setMqttPasswd)

    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();
    //read
    QString MqttIp(){return mqttIp_;}
    int   MqttPort(){return mqttPort_;}
    QString MqttClientId(){ return mqttClientId_;}
    QString MqttUserName(){return mqttUserName_;}
    QString MqttPasswd(){return mqttPasswd_;}
    //set
    void setMqttIp(QString mqtt_ip){mqttIp_ = mqtt_ip;}
    void setMqttPort(int mqtt_port){mqttPort_ =  mqtt_port ;}
    void setMqttClientId(QString mqtt_clientid){mqttClientId_ = mqtt_clientid;}
    void setMqttUserName(QString mqtt_username){mqttUserName_ = mqtt_username;}
    void setMqttPasswd(QString mqtt_passwd){this->mqttPasswd_ = mqtt_passwd;}

    QByteArray getMqttParaReg(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

private:
    JsonFactGroup *regList_;
    QString mqttIp_;
    int  mqttPort_;
    QString mqttClientId_;
    QString mqttUserName_;
    QString mqttPasswd_;

};

#endif // MQTTPARACONTROLLER_H
