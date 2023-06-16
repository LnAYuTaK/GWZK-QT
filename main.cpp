#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "frameless.h"
#include <QQuickStyle>
#include <QQmlContext>
#include <QDir>
#include "appSrc/Application.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setOrganizationName("Some organization");

    Application * app = new Application(argc,argv);
    Q_CHECK_PTR(app);
    app->initAppCommon();
    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    qmlRegisterType<FramelessWindow>("Qt.Window", 1, 0, "Frameless");
    qmlRegisterSingletonType(QUrl("qrc:/common/SkinModel.qml"), "Qt.Singleton", 1, 0, "SkinSingleton");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app->exec();
}
