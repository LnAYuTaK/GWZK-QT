
#ifndef MQTTPARACONTROLLER_H
#define MQTTPARACONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"
class MqttParaController : public QObject
{
    Q_OBJECT
public:
    explicit MqttParaController(QObject *parent = nullptr);
    //mqttip地址
    Q_PROPERTY(QString MqttIp         READ MqttIp        WRITE setMqttIp        NOTIFY MqttIpChanged)
    //mqttIP端口号
    Q_PROPERTY(QString MqttPort       READ MqttPort      WRITE setMqttPort      NOTIFY MqttPortChanged)
    //MqttclientIP
    Q_PROPERTY(QString MqttClientId   READ MqttClientId  WRITE setMqttClientId  NOTIFY MqttMqttClientIdChanged)
    //Mqtt用户名
    Q_PROPERTY(QString MqttUserName   READ MqttUserName  WRITE setMqttUserName  NOTIFY MqttUserNameChanged)
    //Mqtt密码
    Q_PROPERTY(QString MqttPasswd     READ MqttPasswd    WRITE setMqttPasswd    NOTIFY MqttPasswdChanged)
    //read
    QString MqttIp(){return mqttIp_;}
    QString MqttPort(){return mqttPort_;}
    QString MqttClientId(){ return mqttClientId_;}
    QString MqttUserName(){return mqttUserName_;}
    QString MqttPasswd(){return mqttPasswd_;}
    //set
    void setMqttIp(QString mqtt_ip){
        mqttIp_ = mqtt_ip;
        emit MqttIpChanged(mqttIp_);
    }
    void setMqttPort(QString mqtt_port){
        mqttPort_ =  mqtt_port ;
        emit MqttPortChanged(mqttPort_);
    }
    void setMqttClientId(QString mqtt_clientid){
        mqttClientId_ = mqtt_clientid;
        emit MqttMqttClientIdChanged(mqttClientId_);
    }
    void setMqttUserName(QString mqtt_username){
        mqttUserName_ = mqtt_username;
        emit MqttUserNameChanged(mqttUserName_);
    }
    void setMqttPasswd(QString mqtt_passwd){
        mqttPasswd_ = mqtt_passwd;
        emit  MqttPasswdChanged(mqttPasswd_);
    }
    //FUNCTION
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();


    QByteArray getMqttParaReg(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

signals:
    void MqttIpChanged(QString mqttIp);
    void MqttPortChanged(QString mqttPort);
    void MqttMqttClientIdChanged(QString mqttClientid);
    void MqttUserNameChanged(QString mqttUsername);
    void MqttPasswdChanged(QString mqttPasswd);
private:
    JsonFactGroup *regList_;
    QString mqttIp_;
    QString  mqttPort_;
    QString mqttClientId_;
    QString mqttUserName_;
    QString mqttPasswd_;

};

#endif // MQTTPARACONTROLLER_H
