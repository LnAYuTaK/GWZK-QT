import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import "qrc:/common"
/*设置操作 ------主控操作 */
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
                            text:qsTr("系统时间")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseTextField{
                            Layout.preferredWidth:140
                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("系统操作")
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 40
                          model: ["系统重启","重新拨号"]
                        }
                        BaseTextField{
                            Layout.preferredWidth:140
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