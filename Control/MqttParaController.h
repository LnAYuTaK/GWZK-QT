
#ifndef MQTTPARACONTROLLER_H
#define MQTTPARACONTROLLER_H


#include <QObject>


class MqttParaController : public QObject
{
    Q_OBJECT
public:
    explicit MqttParaController(QObject *parent = nullptr);

signals:

};

#endif // MQTTPARACONTROLLER_H
