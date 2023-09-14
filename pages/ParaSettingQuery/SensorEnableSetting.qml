import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import App.NetWorkManager 1.0
import "qrc:/common"
import "qrc:/common/qmlQianHints"
import "qrc:/common/qmlQianDialog"
/*传感器使能------ */
Item {
    id:root
    property int leftWidth: 182
    property int fontsize: 19
    property int boxleftWidth: 40
    property int textWidth: 120
    property bool isChecked: false
    ScrollView {
        id:flickable
        anchors.fill: parent
        clip:         true
        ScrollBar.vertical.interactive: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ColumnLayout {
                    id: contents
                    anchors.margins: 30
                    anchors.fill: parent
                    spacing: 20
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("O2")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                            //checked: App.protoManager.SensorEnableCtrl.O2Enable
                            onCheckedChanged: {

                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("CO")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                            //checked: App.protoManager.SensorEnableCtrl.COEnable
                            onCheckedChanged: {
                                //App.protoManager.SensorEnableCtrl.COEnable  = checkState
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("Cl2")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                            //checked:App.protoManager.SensorEnableCtrl.Cl2Enable
                            onCheckedChanged: {
                                //App.protoManager.SensorEnableCtrl.Cl2Enable  = checkState
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("H2S")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                            //checked: App.protoManager.SensorEnableCtrl.H2SEnable
                            onCheckedChanged: {
                               //  App.protoManager.SensorEnableCtrl.H2SEnable  = checkState
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("H2")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                            //checked:App.protoManager.SensorEnableCtrl.H2Enable
                            onCheckedChanged: {
                                //  App.protoManager.SensorEnableCtrl.H2Enable  = checkState
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("CO2")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                            //checked: App.protoManager.SensorEnableCtrl.CO2Enable
                            onCheckedChanged: {
                               // App.protoManager.SensorEnableCtrl.CO2Enable  = checkState
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("CH4")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                           //checked: App.protoManager.SensorEnableCtrl.CH4Enable
                            onCheckedChanged: {
                                //App.protoManager.SensorEnableCtrl.CH4Enable  = checkState
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("温湿度")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                            //checked: App.protoManager.SensorEnableCtrl.TemHumEnable
                            onCheckedChanged: {
                                // App.protoManager.SensorEnableCtrl.TemHumEnable = checkState
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("液位")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: boxleftWidth
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseCheckBox{
                            //checked:App.protoManager.SensorEnableCtrl.WaterLevelEnable
                            onCheckedChanged: {
                                // App.protoManager.SensorEnableCtrl.WaterLevelEnable = checkState
                            }
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        BaseButton {
                            text:qsTr("查询")
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                            onClicked: {
                               //App.protoManager.SensorEnableCtrl.queryData()
                            }
                        }
                        Rectangle {
                             width: 200
                        }
                        BaseButton {
                            text: qsTr("设置")
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                            onClicked: {
                                //App.protoManager.SensorEnableCtrl.setData()
                            }
                        }
                    }
                    //填充最底部
                    Rectangle {
                         width: parent.width
                         height: 10
                     }
                }
        //}
    }
    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }

}
