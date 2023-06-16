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
                  Layout.preferredWidth:280
                }
            }
            RowLayout{
                Layout.fillWidth: true
                BaseButton {
                    text: "连接"
                    font.pixelSize:  20
                    backRadius: 4
                    bckcolor: "#4785FF"
                    Layout.alignment:Qt.AlignBottom
                    onClicked: {
                        App.netWorkManager.tcpConnect(hostField.text,portField.text)
                    }
                }
                Rectangle {
                     width: 200
                }
                BaseButton {
                    text: "断开"
                    font.pixelSize:  20
                    backRadius: 4
                    bckcolor: "#4785FF"
                    Layout.alignment:Qt.AlignBottom
                    onClicked: {
                        App.netWorkManager.witeString("123123123123")
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

    //连接提示
    function tcpConnectFun(type)
    {
        message('success', "TCP连接!")
    }
    Component.onCompleted: {

        App.netWorkManager.connected.connect(tcpConnectFun)
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
           message('success', "You clicked the accept button!")
           skinQianDialog.close();
        }
    }
    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }

}
