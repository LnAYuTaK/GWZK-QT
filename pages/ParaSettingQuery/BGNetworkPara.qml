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
/*参数设置查询 ------后台网络模块 */
Item {
    id:root
    property int leftWidth: 182
    property int fontsize: 19
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
                    //服务器地址
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("主站IP地址")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth

                            Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                        }
                        BaseTextField{
                          Layout.preferredWidth:280
                          validator: RegExpValidator {
                              regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                          }
                          onTextChanged: {

                          }
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("主站IP端口地址")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                        }
                        BaseTextField{
                          Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("通信方式")
                            Layout.preferredWidth: leftWidth
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignTop |Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 45
                          model: ["UDP", "TCP"]
                        }
                        BaseTextField{
                          Layout.preferredWidth:140
                        }

                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"SIM1卡APN"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                          Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"SIM1卡用户名"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                          Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"SIM1卡密码"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                          Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"备用IP地址1"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"备用IP地址2"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"备用端口地址"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"备用链接方式"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 45
                          model: ["UDP", "TCP"]
                        }
                        BaseTextField{
                          Layout.preferredWidth:140
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        BaseButton {
                            text: "查询"
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                        }
                        Rectangle {
                             width: 200
                        }
                        BaseButton {
                            text: "设置"
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                        }
                    }
                    //填充最底部
                    Rectangle {
                         width: parent.width
                         height: 10
                     }
                }
    }
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

}
