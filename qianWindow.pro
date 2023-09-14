QT += quick
QT += quickcontrols2
QT += widgets
QT += network
CONFIG += c++17
CONFIG += resources_big
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Control/EnvParaController.cpp \
    Control/GasParaController.cpp \
    Control/LocalNetParaController.cpp \
    Control/MainOptController.cpp \
    Control/MainParaController.cpp \
    Control/MqttParaController.cpp \
    Control/NetParaController.cpp \
    Control/SensorEnableController.cpp \
    Control/TunnelFanDevControl.cpp \
    Control/TunnelGasData.cpp \
    Control/WaterLevelController.cpp \
    Control/WaterLevelDataController.cpp \
    Control/WaterPumpController.cpp \
    appSrc/Application.cpp \
    appSrc/ControllerManager.cpp \
    appSrc/NetWorkManager.cpp \
    appSrc/ParaFactManager.cpp \
    appSrc/ProtocolManager.cpp \
    appSrc/QmlGlobal.cpp \
    Control/TunnelGasMonitor.cpp \
    appSrc/Utils.cpp \
    fact/Fact.cpp \
    fact/FactGroup.cpp \
    fact/JsonFactGroup.cpp \
    groups/TunnelGasDevFactGroup.cpp \
        main.cpp \


RESOURCES += qml.qrc
include(./common/Frameless/frameless.pri)
include(./common/Backed/Backed.pri)


RC_FILE += ./windowRes/Icon.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    Control/EnvParaController.h \
    Control/GasParaController.h \
    Control/LocalNetParaController.h \
    Control/MainOptController.h \
    Control/MainParaController.h \
    Control/MqttParaController.h \
    Control/NetParaController.h \
    Control/SensorEnableController.h \
    Control/TunnelFanDevControl.h \
    Control/TunnelGasData.h \
    Control/TunnelGasDevControl.h \
    Control/WaterLevelController.h \
    Control/WaterLevelDataController.h \
    Control/WaterPumpController.h \
    appSrc/Application.h \
    appSrc/ControllerManager.h \
    appSrc/NetWorkManager.h \
    appSrc/ParaFactManager.h \
    appSrc/ProtocolManager.h \
    appSrc/QmlGlobal.h \
    appSrc/Utils.h \
    fact/Fact.h \
    fact/FactGroup.h \
    fact/JsonFactGroup.h \
    groups/TunnelGasDevFactGroup.h
