import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import App.NetWorkManager 1.0
import "qrc:/common/qmlQianHints"
import "qrc:/common/qmlQianDialog"
import "qrc:/common"
/*装置列表 ------隧道风机 */
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
                    //数量--周期--通道
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
                                validator: IntValidator {
                                      bottom: 0
                                      top: 65535
                                }
                                onTextChanged: {
                                    App.protoManager.tunnelFanControl.count = text
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
                            text:qsTr("风机地址格式")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 40
                          model: ["递增", "相同"]
                          onCurrentIndexChanged: {
                             App.protoManager.tunnelFanControl.format = currentIndex

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
                            text: qsTr("隧道风机监测编码")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
                            maximumLength: 16
                            validator: RegExpValidator {
                                regExp: /^[a-zA-Z0-9]*$/ // 只允许输入字母和数字
                            }
                            onTextChanged: {
                                App.protoManager.tunnelFanControl.address = text
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
                                 App.protoManager.tunnelFanControl.queryData()
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
                                App.protoManager.tunnelFanControl.setData()
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
