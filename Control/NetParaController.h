
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
    Q_PROPERTY(QString MasterIp      READ MasterIp          WRITE setMasterIp)
    //主站端口地址
    Q_PROPERTY(int MasterPort        READ MasterPort        WRITE setMasterPort)
    //主站连接方式
    Q_PROPERTY(int LinkType          READ LinkType          WRITE setLinkType)
    //SIM卡APN
    Q_PROPERTY(QString SIMAPN        READ SIMAPN            WRITE setSIMAPN)
    //SIM卡用户名
    Q_PROPERTY(QString SIMUserName   READ SIMUserName       WRITE setSIMUserName)
    //SIM卡密码
    Q_PROPERTY(QString SIMPasswd     READ SIMPasswd         WRITE setSIMPasswd)
    //备用IP地址
    Q_PROPERTY(QString AlternateIp   READ AlternateIp       WRITE setAlternateIp)
    //备用端口地址
    Q_PROPERTY(int AlternatePort     READ AlternatePort     WRITE setAlternatePort)
    //备用连接
    Q_PROPERTY(int AlternateLinktype READ AlternateLinktype WRITE setAlternateLinktype)

    //read
    QString MasterIp(){return this->masterIp_;}
    int     MasterPort(){return this->masterPort_;}
    int     LinkType(){return this->linkType_;}
    QString SIMAPN(){return simApn_;}
    QString SIMUserName(){return simUserName_;}
    QString SIMPasswd() {return simPasswd_;}
    QString AlternateIp(){return alternateIp_;}
    int AlternatePort(){return alternatePort_;}
    int AlternateLinktype(){return alternateLinktype_;}
    //set
    void setMasterIp(QString masterIp){this->masterIp_ = masterIp;}
    void setMasterPort(int masterPort){this->masterPort_ = masterPort;}
    void setLinkType(int linkType){this->linkType_ = linkType;}
    void setSIMAPN(QString simApn){this->simApn_ = simApn;}
    void setSIMUserName(QString userName){this->simUserName_ = userName;}
    void setSIMPasswd(QString passWd){this->simPasswd_ = passWd;}
    void setAlternateIp(QString alternateIp){this->alternateIp_ = alternateIp;}
    void setAlternatePort(int alternatePort){this->alternatePort_ = alternatePort;}
    void setAlternateLinktype(int alternateLinktype){this->alternateLinktype_ = alternateLinktype;}

    //FUNCTION
    Q_INVOKABLE void setData();
    Q_INVOKABLE void queryData();

    QByteArray getNetParaReg(){
        return QByteArray::fromHex(regList_->getAddress().at(0).toLatin1());
    }


public slots:
    void handleRecv(ProtocolManager::ReccType type,QByteArray data);

private:
    JsonFactGroup *regList_;
    QString masterIp_;
    int     masterPort_;
    int     linkType_;
    QString simApn_;
    QString simUserName_;
    QString simPasswd_;
    QString alternateIp_;
    int     alternatePort_;
    int     alternateLinktype_;

};

#endif // NETPARACONTROLLER_H
