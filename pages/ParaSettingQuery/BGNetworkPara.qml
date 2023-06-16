import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import "qrc:/common"
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
                    anchors.rightMargin: 60
                    anchors.topMargin: 30
                    anchors.leftMargin: 60
                    anchors.bottomMargin: 30
                    anchors.fill: parent
                    spacing: 20
                    //服务器地址
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("服务器地址")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:280
                          Layout.alignment: Qt.AlignRight
                          Layout.preferredHeight: 45
                          model: ["无IP地址", "有IP地址"]
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("通信方式")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.alignment: Qt.AlignRight
                          Layout.preferredWidth:280
                          Layout.preferredHeight: 45
                          model: ["UDP", "TCP"]
                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"服务器IP"
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
                            text:"MAC地址"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:280
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
