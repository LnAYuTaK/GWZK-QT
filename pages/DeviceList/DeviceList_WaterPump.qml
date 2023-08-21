﻿import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import App.NetWorkManager 1.0
import "qrc:/common/qmlQianHints"
import "qrc:/common/qmlQianDialog"
import "qrc:/common"
/*装置列表 ------水泵 */
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
                    //数量
                    RowLayout {
                        Layout.fillWidth: true  // 外部 Row，子项填充水平空间
                        Row{
                            spacing:10
                            YaheiText {
                                anchors.centerIn: parent.Center
                                text: qsTr("数量")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                            }
                            BaseTextField{
                                width :90
                                id:count
                                color: acceptableInput  ? "black" : "#ff0000"
                                validator: IntValidator {
                                      bottom: 0
                                      top: 65535
                                }
                                onEditingFinished: {
                                    //验证通过写入
                                    if(acceptableInput)
                                    {
                                        App.protoManager.WaterPumpCtrl.Count = text
                                    }
                                }
                            }
                        }
                    }
                    Rectangle {
                        height: 1
                        color: tingeOpacityColor
                        Layout.fillWidth: true
                    }
                    RowLayout{
                        spacing:10
                        Layout.fillWidth: true
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:qsTr("水泵地址格式")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 40
                          model: ["递增", "相同"]
                          onCurrentIndexChanged: {
                            App.protoManager.WaterPumpCtrl.Format = currentIndex
                          }
                        }
                        BaseTextField{
                            readOnly: true
                            Layout.preferredWidth:140
                        }
                    }
                    //编码
                    RowLayout{
                        spacing:10
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text: qsTr("水泵装置编码")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id:address
                            Layout.preferredWidth:280
                            maximumLength: 17
                            validator: RegExpValidator {
                                regExp: /^[a-zA-Z0-9]*$/ // 只允许输入字母和数字
                            }
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                   App.protoManager.WaterPumpCtrl.Address = text
                                }
                            }
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        BaseButton {
                            text: qsTr("查询")
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                            onClicked:{
                                App.protoManager.WaterPumpCtrl.queryData()
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
                                if(!(address.acceptableInput
                                     &&count.acceptableInput))
                                {
                                    message("error","格式设置错误")
                                    return
                                }
                                else
                                {
                                    App.protoManager.WaterPumpCtrl.setData()
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
