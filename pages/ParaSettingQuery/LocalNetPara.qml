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
/*参数设置查询 ------本地网络模块 */
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
                    //本机IP
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("本地IP地址1")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            validator: RegExpValidator {
                                regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                            }
                            onTextChanged: {
                                App.protoManager.localNetParaController.LocalIp1 = text
                            }

                            Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("本地网关1")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
                            //validator: RegExpValidator{regExp:/(?=(\b|\D))(((\d{1,2})|(1\d{1,2})|(2[0-4]\d)|(25[0-5]))\.){3}((\d{1,2})|(1\d{1,2})|(2[0-4]\d)|(25[0-5]))(?=(\b|\D))/}
                            validator: RegExpValidator {
                                regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                            }
                            onTextChanged: {
                                App.protoManager.localNetParaController.LocalGateway1 = text
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("子网掩码1")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                          Layout.preferredWidth:280
                          validator: RegExpValidator {
                              regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                          }
                          onTextChanged: {
                              App.protoManager.localNetParaController.LocalMask1 = text
                          }
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("MAC地址1")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
                            validator: RegExpValidator {
                                regExp: /^(?:[0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}$/
                            }
                            onTextChanged: {
                                App.protoManager.localNetParaController.LocalMACAddr1 = text
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("本机IP2")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
                            validator: RegExpValidator {
                                regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                            }
                            onTextChanged: {
                                App.protoManager.localNetParaController.LocalIp2 = text
                            }
                            //验证..
                            onEditingFinished: {
                                   if(text.length < 16)
                                   {
                                       message("error","IP格式错误")
                                   }
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("本地网关2")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            validator: RegExpValidator {
                                regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                            }
                            Layout.preferredWidth:280
                            onTextChanged: {
                                App.protoManager.localNetParaController.LocalGateway2 =text
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("子网掩码2")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
                            validator: RegExpValidator {
                                regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                            }
                            onTextChanged: {
                                App.protoManager.localNetParaController.LocalMask2 = text
                            }
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("MAC地址2")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            validator: RegExpValidator {
                                regExp: /^(?:[0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}$/
                            }
                            Layout.preferredWidth:280
                            onTextChanged: {
                                App.protoManager.localNetParaController.LocalMACAddr2 =text
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
                                App.protoManager.localNetParaController.queryData()
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

                                App.protoManager.localNetParaController.setData()
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
    Message{
        id:messageTip
        z: 1
        parent: Overlay.overlay
    }

    function message(type, message) {
        if(type!=='success'&&type!=='error'&&type!=='info'){
            return false
        }
        messageTip.open(type, message)
    }

    SkinQianDialog {
        id: skinQianDialog
        backParent: windowEntry
        parent: Overlay.overlay
        onAccept: {
           skinQianDialog.close();
        }
    }
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

}
