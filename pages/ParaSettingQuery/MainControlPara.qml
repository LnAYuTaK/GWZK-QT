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

/*参数设置查询 ------主控参数 */
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
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("是否加密")
                            font.pixelSize: fontsize
                        }
                        BaseCheckBox{
                            id  :checkbox
                            onClicked: {
                                  App.protoManager.mainParaController.encrypted= checkState
                            }
                        }
                        YaheiText {
                            text:qsTr("加密芯片")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 40
                          model: ["南瑞", "中普","SD卡加密","其他"]
                           onCurrentTextChanged: {
                            App.protoManager.mainParaController.encrypType = currentText
                          }
                          enabled: checkbox.checkState
                        }
                        BaseTextField{
                            readOnly: true
                            Layout.preferredWidth:140
                            text: App.protoManager.mainParaController.encrypType
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("通讯方式")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 40
                          model: ["GPRS", "本地串口","本地网络","其他"]
                           onCurrentTextChanged: {
                              App.protoManager.mainParaController.commType = currentText
                          }
                        }
                        BaseTextField{
                            readOnly:  true
                            Layout.preferredWidth:140
                            text:App.protoManager.mainParaController.commType
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        spacing:20
                        YaheiText {
                            text:qsTr("主控地址")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseTextField{
                            id:mainControlField
                            Layout.preferredWidth:280
                            validator: RegExpValidator {
                                regExp: /^[a-zA-Z0-9]*$/ // 只允许输入字母和数字
                            }
                            maximumLength: 16
                            onTextChanged: {
                                App.protoManager.mainParaController.address = text
                            }
                            text : App.protoManager.mainParaController.address
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        spacing:20
                        YaheiText {
                            text:qsTr("软件版本")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseTextField{
                            readOnly: true
                            Layout.preferredWidth:280
                            text: App.protoManager.mainParaController.softVersion
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        BaseButton {
                            text:qsTr("查询")
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                            onClicked:{
                                 App.protoManager.mainParaController.queryData()
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
                            onClicked:{
                                if(!(mainControlField.acceptableInput))
                                {
                                   message("error","主控地址设置错误")
                                   return
                                }
                                App.protoManager.mainParaController.setData()
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
