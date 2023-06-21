
#ifndef REGRDATAFACT_H
#define REGRDATAFACT_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QList>
enum  RegAccess{
    Invalid , //未定义行为
    ReadWrite, //RW
    WriteOnly, //W
    ReadOnly,  //R
    NoAccess //不可读不可写
};

//封装基础寄存器静态属性类
class RegDataFact
{
public:
    explicit RegDataFact(quint16 address,RegAccess type,QString content)
        :_address(address)
        ,_type(type)
        ,_content(content){
    }
    ~RegDataFact(){
    }
    quint16   _address{0}; //寄存器地址
    RegAccess _type{RegAccess::Invalid};
    QString   _content{""};
};
//寄存器工厂
class RegTypeFactory: public QObject
{

    Q_OBJECT
    Q_ENUM(RegAccess)
    //单个寄存器列表
    using RegisterConf   = QVector<RegDataFact>;
    //存放所有寄存器配置表
    using RegisterConfList = QList<RegisterConf>;
public:
    //寄存器
    explicit RegTypeFactory(QObject *parent = nullptr);
    ~RegTypeFactory(){}

public slots:
    //注册到本地List列表里

private:
    void registerList(RegisterConf&Conf);
    RegisterConfList *regList;


};

#endif // REGRDATAFACT_H
