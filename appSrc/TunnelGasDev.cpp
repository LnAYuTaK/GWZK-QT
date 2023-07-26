
#include "TunnelGasDev.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
TunnelGasDev::TunnelGasDev(QObject *parent)
     : QObject{parent}
{
   qmlRegisterUncreatableType<TunnelGasDev>("App",   1, 0, "TunnelGasDev",  "Reference only");
}

