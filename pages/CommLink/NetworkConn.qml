import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import "qrc:/common"
import "qrc:/common/qmlQianHints"
import "qrc:/common/qmlQianDialog"
Item {
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
            anchors.rightMargin: 60
            anchors.topMargin: 30
            anchors.leftMargin: 60
            anchors.bottomMargin: 30
            anchors.fill: parent
            spacing: 10
            RowLayout {
                spacing:20
                YaheiText {
                    anchors.centerIn: parent.Center
                    text:qsTr("网络连接类型")
                    font.pixelSize: fontsize
                    Layout.preferredWidth: leftWidth
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                }
                BaseComboBox{
                    id:commSelct
                  Layout.alignment: Qt.AlignRight
                  Layout.preferredWidth:280
                  Layout.preferredHeight:40
                  model: ["UDP", "TCP"]
                }
            }
            RowLayout{
                spacing:20
                YaheiText {
                    anchors.centerIn: parent.Center
                    text:"IP"
                    font.pixelSize: fontsize
                    Layout.preferredWidth: leftWidth
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                }
                BaseTextField{
                  id:hostField
                  placeholderText:"请输入IP"
                  validator: RegExpValidator {
                      regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                  }
                  Layout.preferredWidth:280
                }
            }
            RowLayout{
                spacing:20
                YaheiText {
                    anchors.centerIn: parent.Center
                    text:"端口号"
                    font.pixelSize: fontsize
                    Layout.preferredWidth: leftWidth
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                }
                BaseTextField{
                  id:portField
                  placeholderText:"请输入端口号"
                  Layout.preferredWidth:280
                  validator: RegExpValidator {
                          regExp: /^(0|[1-9]\d{0,3}|[1-5]\d{4}|[6][0-4]\d{3}|[6][5][0-4]\d{2}|[6][5][5][0-2]\d|[6][5][5][3][0-5])$/
                     }
                }
            }
            RowLayout{
                Layout.fillWidth: true
                BaseButton {
                    text:  App.netWorkManager.IsTcpConnected? "已连接":"连接"
                    font.pixelSize:  20
                    backRadius: 4
                    bckcolor:  App.netWorkManager.IsTcpConnected ? "#4785FF" : "gray"
                    Layout.alignment:Qt.AlignBottom
                    onClicked: {
                        if((hostField.text.length ===0)&&(portField.text.length===0))
                        {
                            message("error","IP或端口号为空")
                            return
                        }
                        if(commSelct.currentText == "TCP")
                        {
                            App.netWorkManager.tcpConnect(hostField.text,portField.text)
                        }
                    }
                }
                Rectangle {
                     width: 200
                }
                BaseButton {
                    text: "断开"
                    font.pixelSize:  20
                    backRadius: 4
                    bckcolor: App.netWorkManager.IsTcpConnected? "#EC3315":"gray"
                    Layout.alignment:Qt.AlignBottom
                    onClicked: {
                        App.netWorkManager.tcpDisConnect()

                    }
                }
            }
            Rectangle {
                 width: parent.width
                 height: 10
             }
        }
    }

    Component.onCompleted: {
        //连接后端服务与qml的MSG 提示
        App.netWorkManager.InfoMsg.connect(message)
        //连接后端网络连接部分


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
