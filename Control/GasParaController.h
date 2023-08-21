
#ifndef GASPARACONTROLLER_H
#define GASPARACONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/ParaFactManager.h"
#include "appSrc/Application.h"

//气体参数
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
    //报警阈值上限等级1
    Q_PROPERTY(int  UpThresholdLimitLevel1   READ UpThresholdLimitLevel1   WRITE setUpThresholdLimitLevel1)
    //报警阈值下限等级1
    Q_PROPERTY(int  LowThresholdLimitLevel1  READ LowThresholdLimitLevel1  WRITE setLowThresholdLimitLevel1)
    //报警阈值上限等级2
    Q_PROPERTY(int  UpThresholdLimitLevel2   READ UpThresholdLimitLevel2   WRITE setUpThresholdLimitLevel2)
    //报警阈值下限等级2
    Q_PROPERTY(int  LowThresholdLimitLevel2  READ LowThresholdLimitLevel2  WRITE setLowThresholdLimitLevel2)
    //报警阈值上限等级3
    Q_PROPERTY(int  UpThresholdLimitLevel3   READ UpThresholdLimitLevel3   WRITE setUpThresholdLimitLevel3)
    //报警阈值下限等级3
    Q_PROPERTY(int  LowThresholdLimitLevel3  READ LowThresholdLimitLevel3  WRITE setLowThresholdLimitLevel3)
    //防抖阈值
    Q_PROPERTY(int  KeepThresholdLimit READ KeepThresholdLimit WRITE setKeepThresholdLimit)
    //read
    int UpThresholdLimitLevel1(){return this->upThresholdLimitLevel1_;}
    int LowThresholdLimitLevel1(){return this->lowThresholdLimitLevel1_;}
    int UpThresholdLimitLevel2(){return this->upThresholdLimitLevel2_;}
    int LowThresholdLimitLevel2(){return this->lowThresholdLimitLevel2_;}
    int UpThresholdLimitLevel3(){return this->upThresholdLimitLevel3_;}
    int LowThresholdLimitLevel3(){return this->lowThresholdLimitLevel3_;}
    int KeepThresholdLimit() {return keepThresholdLimit_;}
    //set
    void setUpThresholdLimitLevel1(int upThresholdLimit){
        this->upThresholdLimitLevel1_ = upThresholdLimit;
    }
    void setLowThresholdLimitLevel1(int lowThresholdLimit){
        this->lowThresholdLimitLevel1_ = lowThresholdLimit;
    }
    void setUpThresholdLimitLevel2(int upThresholdLimit){
        this->upThresholdLimitLevel2_ = upThresholdLimit;
    }
    void setLowThresholdLimitLevel2(int lowThresholdLimit){
        this->lowThresholdLimitLevel2_ = lowThresholdLimit;
    }
    void setUpThresholdLimitLevel3(int upThresholdLimit){
        this->upThresholdLimitLevel3_ = upThresholdLimit;
    }
    void setLowThresholdLimitLevel3(int lowThresholdLimit){
        this->lowThresholdLimitLevel3_ = lowThresholdLimit;
    }
    void setKeepThresholdLimit(int keepThresholdLimit){
       this->keepThresholdLimit_ = keepThresholdLimit;
    }
    //FUNCTION
    Q_INVOKABLE void queryData(GasType type);
    Q_INVOKABLE void setData(GasType type);

    //获取设置类型寄存器头
    QByteArray getGasO2Reg() {
       return  QByteArray::fromHex(GasO2regList_->getAddress().at(0).toLatin1());
    }
    QByteArray getGasH2Reg() {
       return  QByteArray::fromHex(GasH2regList_->getAddress().at(0).toLatin1());
    }
    QByteArray getGasCl2Reg() {
       return QByteArray::fromHex(GasCl2regList_->getAddress().at(0).toLatin1());
    }
    QByteArray getGasH2SReg() {
       return QByteArray::fromHex(GasH2SregList_->getAddress().at(0).toLatin1());
    }
    QByteArray getGasCH4Reg() {
       return QByteArray::fromHex(GasCH4regList_->getAddress().at(0).toLatin1());
    }
    QByteArray getGasCOReg() {
       return QByteArray::fromHex(GasCOregList_->getAddress().at(0).toLatin1());
    }
    QByteArray getGasCO2Reg() {
       return QByteArray::fromHex(GasCO2regList_->getAddress().at(0).toLatin1());
    }
private:
    JsonFactGroup * GasO2regList_;
    JsonFactGroup * GasH2regList_;
    JsonFactGroup * GasCl2regList_;
    JsonFactGroup * GasH2SregList_;
    JsonFactGroup * GasCH4regList_;
    JsonFactGroup * GasCOregList_;
    JsonFactGroup * GasCO2regList_;
    GasType  type;
    int upThresholdLimitLevel1_;
    int lowThresholdLimitLevel1_;
    int upThresholdLimitLevel2_;
    int lowThresholdLimitLevel2_;
    int upThresholdLimitLevel3_;
    int lowThresholdLimitLevel3_;
    int keepThresholdLimit_;
    QByteArray addressNow;
};

#endif // GASPARACONTROLLER_H
