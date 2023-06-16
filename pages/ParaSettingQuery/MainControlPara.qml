import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
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
                    anchors.rightMargin: 60
                    anchors.topMargin: 30
                    anchors.leftMargin: 60
                    anchors.bottomMargin: 30
                    anchors.fill: parent
                    spacing: 20

                    RowLayout{
                        Layout.fillWidth: true
                        spacing:20
                        YaheiText {
                            text:qsTr("数据类型")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:280
                          Layout.preferredHeight: 45
                          model: ["浮点数", "整数"]
                        }
                    }
                    BaseCheckBox{
                        font.pixelSize: fontsize
                        text: "数据加密"
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("加密芯片")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:280
                          Layout.preferredHeight: 45
                          model: ["南瑞", "中电普华"]
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
                          Layout.preferredWidth:280
                          Layout.preferredHeight: 45
                          model: ["GPRS", "RS232","以太网","3G优先","4G优先"]
                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        spacing:20
                        YaheiText {
                            text:qsTr("主控编码")
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
