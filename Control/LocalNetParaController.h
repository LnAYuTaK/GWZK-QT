
#ifndef LOCALNETPARACONTROLLER_H
#define LOCALNETPARACONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"

#include "appSrc/ProtocolManager.h"
//本地网络设置
class LocalNetParaController : public QObject
{
    Q_OBJECT
public:
    explicit LocalNetParaController(QObject *parent = nullptr);
    //本地IP1地址
    Q_PROPERTY(QString LocalIp1       READ LocalIp1       WRITE setLocalIp1       NOTIFY LocalIp1Changed)
    //本地IP1网关
    Q_PROPERTY(QString LocalGateway1  READ LocalGateway1  WRITE setLocalGateway1  NOTIFY LocalGateway1Changed)
    //本地IP1子网掩码
    Q_PROPERTY(QString LocalMask1     READ LocalMask1     WRITE setLocalMask1     NOTIFY LocalMask1Changed)
    //本地IP1MAC地址
    Q_PROPERTY(QString LocalMACAddr1  READ LocalMACAddr1  WRITE setLocalMACAddr1  NOTIFY LocalMACAddr1Changed)
    //本地IP2地址
    Q_PROPERTY(QString LocalIp2       READ LocalIp2       WRITE setLocalIp2       NOTIFY LocalIp2Changed)
    //本地IP2网关
    Q_PROPERTY(QString LocalGateway2  READ LocalGateway2  WRITE setLocalGateway2  NOTIFY LocalGateway2Changed)
    //本地IP2子网掩码
    Q_PROPERTY(QString LocalMask2     READ LocalMask2     WRITE setLocalMask2     NOTIFY LocalMask2Changed)
    //本地IP2MAC地址
    Q_PROPERTY(QString LocalMACAddr2  READ LocalMACAddr2  WRITE setLocalMACAddr2  NOTIFY LocalMACAddr2Changed)
    //本地Wifi名称
    Q_PROPERTY(QString LocalWifiName  READ LocalWifiName  WRITE setLocalWifiName  NOTIFY LocalWifiNameChanged)
    //Local IP 1
    QString LocalIp1()const {return localIp1_;}
    void setLocalIp1(QString localIp1 ){
        this->localIp1_ = localIp1;
        emit LocalIp1Changed(localIp1_);
    }
    QString LocalGateway1()const {return localGateway1_;}
    void setLocalGateway1(QString localGateway1){
        this->localGateway1_ =localGateway1;
        emit LocalGateway1Changed(localGateway1_);
    }
    QString LocalMask1()const {return localMask1_;}
    void setLocalMask1(QString localMask1){
        this->localMask1_ = localMask1;
        emit  LocalMask1Changed(localMask1_);
    }
    QString LocalMACAddr1()const {return this->localMACAddr1_;}
    void setLocalMACAddr1(QString localMACAddr1){
        this->localMACAddr1_ = localMACAddr1;
        emit LocalMACAddr1Changed(localMACAddr1_);
    }
    //Local IP 2
    QString LocalIp2()const {return localIp2_;}
    void setLocalIp2(QString localIp2 ){
        this->localIp2_ = localIp2;
        emit LocalIp2Changed(localIp2_);
    }
    QString LocalGateway2()const {return localGateway2_;}
    void setLocalGateway2(QString localGateway2){
        this->localGateway2_ =localGateway2;
        emit LocalGateway2Changed(localGateway2_);
    }
    QString LocalMask2()const {return localMask2_;}
    void setLocalMask2(QString localMask2){
        this->localMask2_ = localMask2;
        emit  LocalMask2Changed(localMask2_);
    }
    QString LocalMACAddr2()const {return this->localMACAddr2_;}
    void setLocalMACAddr2(QString localMACAddr2){
        this->localMACAddr2_ = localMACAddr2;
        emit LocalMACAddr2Changed(localMACAddr2_);
    }
    //wifi
    QString LocalWifiName(){return this->localWifiName_;}
    void   setLocalWifiName(QString localWifiName){
        this->localWifiName_ = localWifiName;
        LocalWifiNameChanged(localWifiName_);
    }
    //FCUNTION
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();
    //获取寄存器首地址
    QByteArray getLocalNetParaReg(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }

public slots:
  void handleRecv(ProtocolManager::ReccType type,QByteArray data);

signals:
    void  LocalIp1Changed(QString LocalIp1);
    void  LocalGateway1Changed(QString LocalGateway1);
    void  LocalMask1Changed(QString LocalMask1);
    void  LocalMACAddr1Changed(QString LocalMACAddr1);
    void  LocalIp2Changed(QString LocalIp2);
    void  LocalGateway2Changed(QString LocalGateway2);
    void  LocalMask2Changed(QString LocalMask2);
    void  LocalMACAddr2Changed(QString  LocalMACAddr2);
    void  LocalWifiNameChanged(QString LocalWifiName);

private:
    JsonFactGroup *regList_;
    QString localIp1_;
    QString localGateway1_;
    QString localMask1_;
    QString localMACAddr1_;
    QString localIp2_;
    QString localGateway2_;
    QString localMask2_;
    QString localMACAddr2_;
    QString localWifiName_;
};

#endif // LOCALNETPARACONTROLLER_H
