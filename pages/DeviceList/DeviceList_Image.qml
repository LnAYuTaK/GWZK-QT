import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import "qrc:/common"
/*装置列表 ------图像 */
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
                    //通道数
                    Row{
                        spacing:10
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text: "通道数      "
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }

                        BaseTextField {
                             width :200

                        }
                        BaseButton {
                            text: "设置"
                            font.pixelSize:  fontsize
                            backRadius: 4
                            bckcolor: "#4785FF"
                        }
                        BaseButton {
                            text: "查询"
                            font.pixelSize:  fontsize
                            backRadius: 4
                            bckcolor: "#4785FF"
                        }
                    }
                    //起始通道IP1
                    Row{
                        spacing:10
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text: "起始通道IP"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField {
                             width :200

                        }
                        BaseButton {
                            text: "上电"
                            font.pixelSize:  fontsize
                            backRadius: 4
                            bckcolor: "#4785FF"
                        }
                    }
                    //起始通道IP2
                    Row{
                        spacing:10
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text: "起始通道IP"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField {
                             width :200

                        }
                        BaseButton {
                            text: "拍照"
                            font.pixelSize:  fontsize
                            backRadius: 4
                            bckcolor: "#4785FF"
                        }
                    }
                    //下发拍照时间
                    BaseButton {
                        text: "下发拍照时间"
                        font.pixelSize:  fontsize
                        backRadius: 4
                        bckcolor: "#4785FF"
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
