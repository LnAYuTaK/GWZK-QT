
#ifndef NETPARACONTROLLER_H
#define NETPARACONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"

class NetParaController : public QObject
{
    Q_OBJECT
public:
    explicit NetParaController(QObject *parent = nullptr);
    //主站IP地址
    Q_PROPERTY(QString MasterIp          READ MasterIp          WRITE setMasterIp          NOTIFY MasterIpChanged)
    //主站端口地址
    Q_PROPERTY(QString MasterPort        READ MasterPort        WRITE setMasterPort        NOTIFY MasterPortChanged)
    //主站连接方式
    Q_PROPERTY(QString LinkType          READ LinkType          WRITE setLinkType          NOTIFY LinkTypeChanged)
    //SIM卡APN
    Q_PROPERTY(QString SIMAPN            READ SIMAPN            WRITE setSIMAPN            NOTIFY SIMAPNChanged)
    //SIM卡用户名
    Q_PROPERTY(QString SIMUserName       READ SIMUserName       WRITE setSIMUserName       NOTIFY SIMUserNameChanged)
    //SIM卡密码
    Q_PROPERTY(QString SIMPasswd         READ SIMPasswd         WRITE setSIMPasswd         NOTIFY SIMPasswdChanged)
    //备用IP地址
    Q_PROPERTY(QString AlternateIp       READ AlternateIp       WRITE setAlternateIp       NOTIFY AlternateIpChanged)
    //备用端口地址
    Q_PROPERTY(QString AlternatePort     READ AlternatePort     WRITE setAlternatePort     NOTIFY AlternatePortChanged)
    //备用连接
    Q_PROPERTY(QString AlternateLinktype READ AlternateLinktype WRITE setAlternateLinktype NOTIFY AlternateLinktypeChanged)
    //read
    QString MasterIp(){return this->masterIp_;}
    QString MasterPort(){return this->masterPort_;}
    QString LinkType(){return this->linkType_;}
    QString SIMAPN(){return simApn_;}
    QString SIMUserName(){return simUserName_;}
    QString SIMPasswd() {return simPasswd_;}
    QString AlternateIp(){return alternateIp_;}
    QString AlternatePort(){return alternatePort_;}
    QString AlternateLinktype(){return alternateLinktype_;}
    //set
    void setMasterIp(QString masterIp){
        this->masterIp_ = masterIp;
        emit MasterIpChanged(masterIp_);
    }
    void setMasterPort(QString  masterPort){
        this->masterPort_ = masterPort;
        emit MasterPortChanged(masterPort_);
    }
    void setLinkType(QString linkType){
        this->linkType_ = linkType;
        emit LinkTypeChanged(linkType_);
    }
    void setSIMAPN(QString simApn){
        this->simApn_ = simApn;
        emit SIMAPNChanged(simApn_);
    }
    void setSIMUserName(QString userName){
        this->simUserName_ = userName;
        emit SIMUserNameChanged(simUserName_);
    }
    void setSIMPasswd(QString passWd){
        this->simPasswd_ = passWd;
        emit SIMPasswdChanged(simPasswd_);
    }
    void setAlternateIp(QString alternateIp){
        this->alternateIp_ = alternateIp;
        emit  AlternateIpChanged(alternateIp_);
    }
    void setAlternatePort(QString alternatePort){
        this->alternatePort_ = alternatePort;
        emit AlternatePortChanged(alternatePort_);
    }
    void setAlternateLinktype(QString alternateLinktype){
        this->alternateLinktype_ = alternateLinktype;
        emit AlternateLinktypeChanged(alternateLinktype_);
    }

    //FUNCTION
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    QByteArray getNetParaReg(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }


public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

signals:
    void MasterIpChanged(QString masterIp);
    void MasterPortChanged(QString masterPort);
    void LinkTypeChanged(QString linkType);
    void SIMAPNChanged(QString simApn);
    void SIMUserNameChanged(QString userName);
    void SIMPasswdChanged(QString passWd);
    void AlternateIpChanged(QString alternateIp);
    void AlternatePortChanged(QString alternatePort);
    void AlternateLinktypeChanged(QString alternateLinktype);
private:
    JsonFactGroup *regList_;
    QString masterIp_;
    QString masterPort_;
    QString linkType_;
    QString simApn_;
    QString simUserName_;
    QString simPasswd_;
    QString alternateIp_;
    QString alternatePort_;
    QString alternateLinktype_;

};

#endif // NETPARACONTROLLER_H
