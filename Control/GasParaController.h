﻿
#ifndef GASPARACONTROLLER_H
#define GASPARACONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/ParaFactManager.h"
#include "appSrc/Application.h"
#include "appSrc/ProtocolManager.h"
#include <QVector>
//气体参数
class GasPara;
class GasPara: public QObject
{
    Q_OBJECT
public:
    explicit GasPara(int  type,JsonFactGroup *regList);
    //报警阈值上限等级1
    Q_PROPERTY(QString  UpThresholdLimitLevel1  READ UpThresholdLimitLevel1   WRITE setUpThresholdLimitLevel1  NOTIFY UpThresholdLimitLevel1Changed)
    //报警阈值下限等级1
    Q_PROPERTY(QString  LowThresholdLimitLevel1 READ LowThresholdLimitLevel1  WRITE setLowThresholdLimitLevel1 NOTIFY LowThresholdLimitLevel1Changed)
    //报警阈值上限等级2
    Q_PROPERTY(QString UpThresholdLimitLevel2  READ UpThresholdLimitLevel2    WRITE setUpThresholdLimitLevel2  NOTIFY UpThresholdLimitLevel2Changed)
    //报警阈值下限等级2
    Q_PROPERTY(QString  LowThresholdLimitLevel2 READ LowThresholdLimitLevel2  WRITE setLowThresholdLimitLevel2 NOTIFY LowThresholdLimitLevel2Changed)
    //报警阈值上限等级3
    Q_PROPERTY(QString  UpThresholdLimitLevel3  READ UpThresholdLimitLevel3   WRITE setUpThresholdLimitLevel3  NOTIFY UpThresholdLimitLevel3Changed)
    //报警阈值下限等级3
    Q_PROPERTY(QString  LowThresholdLimitLevel3 READ LowThresholdLimitLevel3  WRITE setLowThresholdLimitLevel3 NOTIFY LowThresholdLimitLevel3Changed)
    //防抖阈值
    Q_PROPERTY(QString  KeepThresholdLimit      READ KeepThresholdLimit       WRITE setKeepThresholdLimit      NOTIFY KeepThresholdLimitChanged)
    //read
    QString UpThresholdLimitLevel1(){return this->upThresholdLimitLevel1_;}
    QString LowThresholdLimitLevel1(){return this->lowThresholdLimitLevel1_;}
    QString UpThresholdLimitLevel2(){return this->upThresholdLimitLevel2_;}
    QString LowThresholdLimitLevel2(){return this->lowThresholdLimitLevel2_;}
    QString UpThresholdLimitLevel3(){return this->upThresholdLimitLevel3_;}
    QString LowThresholdLimitLevel3(){return this->lowThresholdLimitLevel3_;}
    QString KeepThresholdLimit() {return keepThresholdLimit_;}
    //set
    void setUpThresholdLimitLevel1(QString upThresholdLimit){
        this->upThresholdLimitLevel1_ = upThresholdLimit;
        emit  UpThresholdLimitLevel1Changed(upThresholdLimitLevel1_);
    }
    void setLowThresholdLimitLevel1(QString lowThresholdLimit){
        this->lowThresholdLimitLevel1_ = lowThresholdLimit;
        emit  LowThresholdLimitLevel1Changed(lowThresholdLimitLevel1_);
    }
    void setUpThresholdLimitLevel2(QString upThresholdLimit){
        this->upThresholdLimitLevel2_ = upThresholdLimit;
        emit UpThresholdLimitLevel2Changed(upThresholdLimitLevel2_);
    }
    void setLowThresholdLimitLevel2(QString lowThresholdLimit){
        this->lowThresholdLimitLevel2_ = lowThresholdLimit;
        emit LowThresholdLimitLevel2Changed(lowThresholdLimitLevel2_);
    }
    void setUpThresholdLimitLevel3(QString upThresholdLimit){
        this->upThresholdLimitLevel3_ = upThresholdLimit;
        emit UpThresholdLimitLevel3Changed(upThresholdLimitLevel3_);
    }
    void setLowThresholdLimitLevel3(QString lowThresholdLimit){
        this->lowThresholdLimitLevel3_ = lowThresholdLimit;
        emit LowThresholdLimitLevel3Changed(lowThresholdLimitLevel3_);
    }
    void setKeepThresholdLimit(QString keepThresholdLimit){
        this->keepThresholdLimit_ = keepThresholdLimit;
        emit KeepThresholdLimitChanged(keepThresholdLimit_);
    }
    //FUNCTION
    void queryData();
    void setData();
    JsonFactGroup * regList(){return this->regList_;};
signals:
    void UpThresholdLimitLevel1Changed(QString upThresholdLimit);
    void LowThresholdLimitLevel1Changed(QString lowThresholdLimit);
    void UpThresholdLimitLevel2Changed(QString upThresholdLimit);
    void LowThresholdLimitLevel2Changed(QString lowThresholdLimit);
    void UpThresholdLimitLevel3Changed(QString  upThresholdLimit);
    void LowThresholdLimitLevel3Changed(QString lowThresholdLimit);
    void KeepThresholdLimitChanged(QString keepThresholdLimit);
private:
    int type_;
    JsonFactGroup * regList_;
    QString upThresholdLimitLevel1_;
    QString lowThresholdLimitLevel1_;
    QString upThresholdLimitLevel2_;
    QString lowThresholdLimitLevel2_;
    QString upThresholdLimitLevel3_;
    QString lowThresholdLimitLevel3_;
    QString keepThresholdLimit_;
};

class GasParaController : public QObject
{
    Q_OBJECT
    Q_ENUMS(GasType)
public:
    enum GasType {
        O2,
        H2,
        Cl2,
        H2S,
        CH4,
        CO,
        CO2
    };
    explicit GasParaController(QObject *parent = nullptr);
    //O2
    Q_PROPERTY(GasPara *GasParaO2     READ GasParaO2   CONSTANT)
    //H2
    Q_PROPERTY(GasPara *GasParaH2     READ GasParaH2   CONSTANT)
    //Cl2
    Q_PROPERTY(GasPara *GasParaCl2    READ GasParaCl2  CONSTANT)
    //H2S
    Q_PROPERTY(GasPara *GasParaH2S    READ GasParaH2S  CONSTANT)
    //CH4
    Q_PROPERTY(GasPara *GasParaCH4    READ GasParaCH4  CONSTANT)
    //CO
    Q_PROPERTY(GasPara *GasParaCO     READ GasParaCO   CONSTANT)
    //CO2
    Q_PROPERTY(GasPara *GasParaCO2    READ GasParaCO2  CONSTANT)

    GasPara * GasParaO2 (){return gasO2_;}
    GasPara * GasParaH2(){return  gasH2_;}
    GasPara*  GasParaCl2(){return gasCl2_;}
    GasPara*  GasParaH2S(){return gasH2S_;}
    GasPara*  GasParaCH4(){return gasCH4_;}
    GasPara*  GasParaCO(){return  gasCO_;}
    GasPara*  GasParaCO2(){return gasCO2_;}

    //FUNCTION
    Q_INVOKABLE void queryData(GasType type);
    Q_INVOKABLE void setData(GasType type);

    //获取设置类型寄存器头
    QByteArray getGasO2Reg() {
        return  QByteArray::fromHex(gasO2_->regList()->getAddress().at(0).toLatin1());
    }
    QByteArray getGasH2Reg() {
        return  QByteArray::fromHex(gasH2_->regList()->getAddress().at(0).toLatin1());
    }
    QByteArray getGasCl2Reg() {
        return QByteArray::fromHex(gasCl2_->regList()->getAddress().at(0).toLatin1());
    }
    QByteArray getGasH2SReg() {
        return QByteArray::fromHex(gasH2S_->regList()->getAddress().at(0).toLatin1());
    }
    QByteArray getGasCH4Reg() {
       return QByteArray::fromHex(gasCH4_->regList()->getAddress().at(0).toLatin1());
    }
    QByteArray getGasCOReg() {
       return QByteArray::fromHex(gasCO_->regList()->getAddress().at(0).toLatin1());
    }
    QByteArray getGasCO2Reg() {
       return QByteArray::fromHex(gasCO2_->regList()->getAddress().at(0).toLatin1());
    }
public slots:
    void handleRecvO2(ProtocolManager::ReccType type,QByteArray data);
    void handleRecvH2(ProtocolManager::ReccType type,QByteArray data);
    void handleRecvCl2(ProtocolManager::ReccType type,QByteArray data);
    void handleRecvH2S(ProtocolManager::ReccType type,QByteArray data);
    void handleRecvCH4(ProtocolManager::ReccType type,QByteArray data);
    void handleRecvCO(ProtocolManager::ReccType type,QByteArray data);
    void handleRecvCO2(ProtocolManager::ReccType type,QByteArray data);
private:
    void recvSeleteType(GasType type,GasPara *target,QByteArray resdata);
    GasPara *gasO2_;
    GasPara *gasH2_;
    GasPara *gasCl2_;
    GasPara *gasH2S_;
    GasPara *gasCH4_;
    GasPara *gasCO_;
    GasPara *gasCO2_;
};

#endif // GASPARACONTROLLER_H
