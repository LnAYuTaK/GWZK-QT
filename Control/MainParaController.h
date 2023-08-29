
#ifndef MIANPARACONTROL_H
#define MIANPARACONTROL_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QMap>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"
class MainParaController : public QObject
{
    Q_OBJECT
public:
    explicit MainParaController(QObject *parent = nullptr);
    //地址
    Q_PROPERTY(QString address     READ address     WRITE setAddress     NOTIFY addressChanged)
    //通讯方式
    Q_PROPERTY(QString commType    READ commType    WRITE setCommType    NOTIFY commTypeChanged)
    //是否加密
    Q_PROPERTY(int encrypted       READ encrypted   WRITE setEncrypt     NOTIFY encryptedChanged)
    //加密类型
    Q_PROPERTY(QString encrypType  READ encrypType  WRITE setEncrypType  NOTIFY encrypTypeChanged)
    //软件版本地址
    Q_PROPERTY(QString softVersion READ softVersion WRITE setSoftVersion NOTIFY softVersionChanged)
    //read
    QString address ()const{return  address_;}
    QString commType()const{return commType_;}
    int     encrypted(){return isEncrypted_;}
    QString encrypType (){return encrypType_;}
    QString softVersion(){return softVersion_;}
    //Set
    void    setAddress(QString address){
        this->address_ = address;
        emit addressChanged(address_);
    }
    void    setCommType(QString commType) {
        this->commType_ = commType;
        emit commTypeChanged(commType_);
    }
    void    setSoftVersion(QString softVersion){
        this->softVersion_ = softVersion;
        emit softVersionChanged(softVersion_);
    }
    void    setEncrypt(int isEncrypted) {
        this->isEncrypted_ = isEncrypted;
        emit encryptedChanged(isEncrypted_);
    }
    void    setEncrypType(QString encrypType) {
        this->encrypType_ = encrypType;
        emit  encrypTypeChanged(encrypType_);
    }
    //
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    QByteArray  getMainParaReg() {
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }
public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);
signals:
    void  addressChanged(QString address);
    void  commTypeChanged(QString commType);
    void  encryptedChanged(int isEncrypted);
    void  encrypTypeChanged(QString encrypType);
    void  softVersionChanged(QString softVersion);
private:
    JsonFactGroup *regList_;
    QString        address_;
    QString        commType_;
    int            isEncrypted_;
    QString        encrypType_;
    QString        softVersion_;

};

#endif // MIANPARACONTROL_H
