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
/*参数设置查询 ------=Mqtt参数设置 */
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
                    //MqttIP地址
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("IP地址")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id:ip
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: RegExpValidator {
                                regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                            }
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                   App.protoManager.MqttParaCtrl.MqttIp = text
                                }
                            }
                            text : App.protoManager.MqttParaCtrl.MqttIp

                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("端口号")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                        }
                        BaseTextField{
                            id:port
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: IntValidator {
                                  bottom: 0
                                  top: 65535
                            }
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    App.protoManager.MqttParaCtrl.MqttPort = text
                                }
                            }
                            text : App.protoManager.MqttParaCtrl.MqttPort
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("客户端ID")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id:clientId
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            maximumLength: 32
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                   App.protoManager.MqttParaCtrl.MqttClientId = text
                                }
                            }
                            text: App.protoManager.MqttParaCtrl.MqttClientId
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("用户名")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id: username
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            maximumLength: 32
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    App.protoManager.MqttParaCtrl.MqttUserName = text
                                }
                            }
                            text: App.protoManager.MqttParaCtrl.MqttUserName
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("密码")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id: passwd
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            maximumLength: 32
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    App.protoManager.MqttParaCtrl.MqttPasswd = text
                                }
                            }
                            text:App.protoManager.MqttParaCtrl.MqttPasswd
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
                                App.protoManager.MqttParaCtrl.queryData()
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
                                if(!(ip.acceptableInput
                                     &&port.acceptableInput
                                     &&clientId.acceptableInput
                                     &&username.acceptableInput
                                     &&passwd.acceptableInput))
                                    {
                                          message("error","格式设置错误")
                                          return
                                    }
                                    else
                                    {
                                       App.protoManager.netParaController.setData()
                                    }
                            }

                        }
                    }
                    //填充最底部
                    Rectangle {
                         width: parent.width
                         height: 10
                     }
            }
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
