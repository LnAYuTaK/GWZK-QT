import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import App.NetWorkManager 1.0
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
                    Repeater{
                        id:repeater
                        model: ["O2","CO","H2", "Cl2","H2S","CO2","CH4","温度","湿度"]
                        delegate:RowLayout{
                            spacing:20
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr(modelData+"含量")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
                                id:textfield
                                Layout.preferredWidth:280
                            }
                        }
                    }
                    BaseButton {
                        text: qsTr("查询")
                        font.pixelSize:  20
                        backRadius: 4
                        bckcolor: "#4785FF"
                        onClicked: {

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
