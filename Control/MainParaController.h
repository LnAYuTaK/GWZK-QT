
#ifndef MIANPARACONTROL_H
#define MIANPARACONTROL_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"

class MainParaController : public QObject
{
    Q_OBJECT
public:
    explicit MainParaController(QObject *parent = nullptr);
    //地址
    Q_PROPERTY(QString address     READ address     WRITE setAddress)
    //通讯方式
    Q_PROPERTY(int  commType       READ commType    WRITE setCommType)
    //是否加密
    Q_PROPERTY(int encrypted     READ encrypted WRITE setEncrypt)
    //加密类型
    Q_PROPERTY(int encrypType      READ encrypType  WRITE setEncrypType)
    //软件版本地址
    Q_PROPERTY(QString softVersion READ softVersion WRITE setSoftVersion)

    QString address ()const{return  address_;}
    void    setAddress(QString address){this->address_ = address;}
    int     commType()const{return commType_;}
    void    setCommType(int commType) {this->commType_ = commType;}
    int     encrypted(){return isEncrypted_;}
    void    setEncrypt(int isEncrypted) {this->isEncrypted_ = isEncrypted;}
    int     encrypType (){return encrypType_;}
    void    setEncrypType(int encrypType) {this->encrypType_ = encrypType;}
    QString softVersion(){return softVersion_;}
    void    setSoftVersion(QString softVersion){this->softVersion_ = softVersion;}

    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

private:
    JsonFactGroup *regList_;
    QString address_;
    int     commType_;
    int    isEncrypted_;
    int     encrypType_;
    QString softVersion_;

};

#endif // MIANPARACONTROL_H
