
#ifndef LOCALNETPARACONTROLLER_H
#define LOCALNETPARACONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"

class LocalNetParaController : public QObject
{
    Q_OBJECT
public:
    explicit LocalNetParaController(QObject *parent = nullptr);
    //本地IP1地址
    Q_PROPERTY(QString LocalIp1       READ LocalIp1       WRITE setLocalIp1)
    //本地IP1网关
    Q_PROPERTY(QString LocalGateway1  READ LocalGateway1  WRITE setLocalGateway1)
    //本地IP1子网掩码
    Q_PROPERTY(QString LocalMask1     READ LocalMask1     WRITE setLocalMask1)
    //本地IP1MAC地址
    Q_PROPERTY(QString LocalMACAddr1  READ LocalMACAddr1  WRITE setLocalMACAddr1)
    //本地IP2地址
    Q_PROPERTY(QString LocalIp2       READ LocalIp2       WRITE setLocalIp2)
    //本地IP2网关
    Q_PROPERTY(QString LocalGateway2  READ LocalGateway2  WRITE setLocalGateway2)
    //本地IP2子网掩码
    Q_PROPERTY(QString LocalMask2     READ LocalMask2     WRITE setLocalMask2)
    //本地IP2MAC地址
    Q_PROPERTY(QString LocalMACAddr2  READ LocalMACAddr2  WRITE setLocalMACAddr2)
    //Local IP 1
    QString LocalIp1()const {return localIp1_;}
    void setLocalIp1(QString localIp1 ){this->localIp1_ = localIp1;}
    QString LocalGateway1()const {return localGateway1_;}
    void setLocalGateway1(QString localGateway1){this->localGateway1_ =localGateway1;}
    QString LocalMask1()const {return localMask1_;}
    void setLocalMask1(QString localMask1){this->localMask1_ = localMask1;}
    QString LocalMACAddr1()const {return this->localMACAddr1_;}
    void setLocalMACAddr1(QString localMACAddr1){this->localMACAddr1_ = localMACAddr1;}
    //Local IP 2
    QString LocalIp2()const {return localIp2_;}
    void setLocalIp2(QString localIp2 ){this->localIp2_ = localIp2;}
    QString LocalGateway2()const {return localGateway2_;}
    void setLocalGateway2(QString localGateway2){this->localGateway2_ =localGateway2;}
    QString LocalMask2()const {return localMask2_;}
    void setLocalMask2(QString localMask2){this->localMask2_ = localMask2;}
    QString LocalMACAddr2()const {return this->localMACAddr2_;}
    void setLocalMACAddr2(QString localMACAddr2){this->localMACAddr2_ = localMACAddr2;}

    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    enum  ParaType{
        Ip,
        Gateway,
        Mask,
        MACAddr
    };
    //处理 网络参数字符串
    QByteArray ParseNetLocalString(ParaType type,QString paraStr);

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

};

#endif // LOCALNETPARACONTROLLER_H
