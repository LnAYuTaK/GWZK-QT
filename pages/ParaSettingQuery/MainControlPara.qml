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
                            text:qsTr("加密芯片")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 40
                          model: ["南瑞", "中电普华","SD卡加密","其他"]
                          onCurrentIndexChanged: {

                          }
                        }

                        BaseTextField{
                            Layout.preferredWidth:140
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
                        }
                        BaseTextField{
                            Layout.preferredWidth:140
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
                            Layout.preferredWidth:280
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
                            Layout.preferredWidth:280
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        BaseButton {
                            text:qsTr("查询")
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                        }
                        Rectangle {
                             width: 200
                        }
                        BaseButton {
                            text: qsTr("设置")
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
