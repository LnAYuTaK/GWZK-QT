
#ifndef PROTOCOLEVENT_H
#define PROTOCOLEVENT_H


#include <QObject>
class ProtocolEvent : public QObject
{
    Q_OBJECT
public:
    explicit ProtocolEvent(QObject *parent = nullptr);

signals:

private:
};

#endif // PROTOCOLEVENT_H
