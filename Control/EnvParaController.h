
#ifndef ENVPARACONTROLLER_H
#define ENVPARACONTROLLER_H


#include <QObject>
#include <QString>
#include <QDebug>
#include "appSrc/Application.h"
#include "appSrc/ParaFactManager.h"
#include "appSrc/ProtocolManager.h"
#include <QVector>
class EnvPara;
class  EnvPara: public QObject
{
   Q_OBJECT
public:
   explicit EnvPara(int  type,JsonFactGroup *regList);
   //报警阈值上限等级1
   Q_PROPERTY(int  UpThresholdLimitLevel1  READ UpThresholdLimitLevel1   WRITE setUpThresholdLimitLevel1  NOTIFY UpThresholdLimitLevel1Changed)
   //报警阈值下限等级1
   Q_PROPERTY(int  LowThresholdLimitLevel1 READ LowThresholdLimitLevel1  WRITE setLowThresholdLimitLevel1 NOTIFY LowThresholdLimitLevel1Changed)
   //报警阈值上限等级2
   Q_PROPERTY(int  UpThresholdLimitLevel2  READ UpThresholdLimitLevel2   WRITE setUpThresholdLimitLevel2  NOTIFY UpThresholdLimitLevel2Changed)
   //报警阈值下限等级2
   Q_PROPERTY(int  LowThresholdLimitLevel2 READ LowThresholdLimitLevel2  WRITE setLowThresholdLimitLevel2 NOTIFY LowThresholdLimitLevel2Changed)
   //报警阈值上限等级3
   Q_PROPERTY(int  UpThresholdLimitLevel3  READ UpThresholdLimitLevel3   WRITE setUpThresholdLimitLevel3  NOTIFY UpThresholdLimitLevel3Changed)
   //报警阈值下限等级3
   Q_PROPERTY(int  LowThresholdLimitLevel3 READ LowThresholdLimitLevel3  WRITE setLowThresholdLimitLevel3 NOTIFY LowThresholdLimitLevel3Changed)
   //防抖阈值
   Q_PROPERTY(int  KeepThresholdLimit      READ KeepThresholdLimit       WRITE setKeepThresholdLimit      NOTIFY KeepThresholdLimitChanged)
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
       emit  UpThresholdLimitLevel1Changed(upThresholdLimitLevel1_);
   }
   void setLowThresholdLimitLevel1(int lowThresholdLimit){
       this->lowThresholdLimitLevel1_ = lowThresholdLimit;
       emit  LowThresholdLimitLevel1Changed(lowThresholdLimitLevel1_);
   }
   void setUpThresholdLimitLevel2(int upThresholdLimit){
       this->upThresholdLimitLevel2_ = upThresholdLimit;
       emit UpThresholdLimitLevel2Changed(upThresholdLimitLevel2_);
   }
   void setLowThresholdLimitLevel2(int lowThresholdLimit){
       this->lowThresholdLimitLevel2_ = lowThresholdLimit;
       emit LowThresholdLimitLevel2Changed(lowThresholdLimitLevel2_);
   }
   void setUpThresholdLimitLevel3(int upThresholdLimit){
       this->upThresholdLimitLevel3_ = upThresholdLimit;
       emit UpThresholdLimitLevel3Changed(upThresholdLimitLevel3_);
   }
   void setLowThresholdLimitLevel3(int lowThresholdLimit){
       this->lowThresholdLimitLevel3_ = lowThresholdLimit;
       emit LowThresholdLimitLevel3Changed(lowThresholdLimitLevel3_);
   }
   void setKeepThresholdLimit(int keepThresholdLimit){
       this->keepThresholdLimit_ = keepThresholdLimit;
       emit KeepThresholdLimitChanged(keepThresholdLimit_);
   }

   JsonFactGroup * regList(){return this->regList_;};

   //FUNCTION
   void queryData();
   void setData();

signals:
   void UpThresholdLimitLevel1Changed(int upThresholdLimit);
   void LowThresholdLimitLevel1Changed(int lowThresholdLimit);
   void UpThresholdLimitLevel2Changed(int upThresholdLimit);
   void LowThresholdLimitLevel2Changed(int lowThresholdLimit);
   void UpThresholdLimitLevel3Changed(int  upThresholdLimit);
   void LowThresholdLimitLevel3Changed(int lowThresholdLimit);
   void KeepThresholdLimitChanged(int keepThresholdLimit);
private:
    int type_;
    JsonFactGroup * regList_;
    int upThresholdLimitLevel1_;
    int lowThresholdLimitLevel1_;
    int upThresholdLimitLevel2_;
    int lowThresholdLimitLevel2_;
    int upThresholdLimitLevel3_;
    int lowThresholdLimitLevel3_;
    int keepThresholdLimit_;

};

//环境参数----温度湿度液位
class EnvParaController : public QObject
{
    Q_OBJECT
    Q_ENUMS(EnvType)
public:
    enum EnvType {
        Temp,
        Humidity,
        WaterLevel
    };
    explicit EnvParaController(QObject *parent = nullptr);
    //温度
    Q_PROPERTY(EnvPara *EnvParaTemp          READ EnvParaTemp CONSTANT)
    //湿度
    Q_PROPERTY(EnvPara *EnvParaHumidity      READ EnvParaHumidity CONSTANT)
    //水位
    Q_PROPERTY(EnvPara *EnvParaWaterLevel    READ EnvParaWaterLevel CONSTANT)
    //read
    EnvPara * EnvParaTemp(){return this->envTemp_;}
    EnvPara * EnvParaHumidity(){return this->envHumidity_;}
    EnvPara * EnvParaWaterLevel(){return this->envWaterLevel_;}
    //FUNCTION
    Q_INVOKABLE void queryData(EnvType type);
    Q_INVOKABLE void setData(EnvType type);

    QByteArray getEnvTempReg() {
       return QByteArray::fromHex(envTemp_->regList()->getAddress().at(0).toLatin1());
    }

    QByteArray getEnvHumidityReg() {
       return QByteArray::fromHex(envHumidity_->regList()->getAddress().at(0).toLatin1());
    }

    QByteArray getEnvWaterLevelReg() {
       return QByteArray::fromHex(envWaterLevel_->regList()->getAddress().at(0).toLatin1());
    }
signals:

public slots:

    void handleRecvTemp(ProtocolManager::ReccType type,QByteArray data);
    void handleRecvHumidity(ProtocolManager::ReccType type,QByteArray data);
    void handleRecvWaterLevel(ProtocolManager::ReccType type,QByteArray data);
private:
    void recvSeleteType(EnvType type,EnvPara *target,QByteArray resdata);
    EnvPara *envTemp_;
    EnvPara *envHumidity_;
    EnvPara *envWaterLevel_;
};

#endif // ENVPARACONTROLLER_H
