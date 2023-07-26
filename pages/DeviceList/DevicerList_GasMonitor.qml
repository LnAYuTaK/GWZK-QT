import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import "qrc:/common"
/*装置列表 ------气体监测 */
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
                                text: "数量"
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                            }
                            BaseTextField{
                                width :90
                            }
                        }
                        Row {
                            spacing:10
                            YaheiText {
                                anchors.centerIn: parent.Center
                                text: "周期"
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                            }
                            BaseTextField {
                                 width :90

                            }
                        }
                        Row {
                            spacing:10
                            YaheiText {
                                anchors.centerIn: parent.Center
                                text: "通道"
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                            }
                            BaseTextField{
                                width:90
                            }
                        }
                    }
                    Rectangle {
                        height: 1
                        color: tingeOpacityColor
                        Layout.fillWidth: true
                    }
                    //编码
                    Repeater{
                        model:5
                        RowLayout{
                            spacing:10
                            YaheiText {
                                anchors.centerIn: parent.Center
                                text: "气体监测编码"+(index+1)
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                            }
                            BaseTextField{
                                Layout.preferredWidth:280
                            }
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
        //}
    }
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

}
