import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import App.NetWorkManager 1.0
import "qrc:/common"
/*数据召测 ------隧道气体召测 */
Item {
    id:root
    property int leftWidth: 120
    property int fontsize: 18
    ScrollView {
        id:flickable
        anchors.fill: parent
        clip:         true
        ScrollBar.vertical.interactive: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        property var strArray:[]
                ColumnLayout {
                    id: contents
                    anchors.margins: 30
                    anchors.fill: parent
                    spacing: 20
                    Repeater{
                        id:repeater
                        model: ["O2","CO","H2", "Cl2","H2S","CO2","CH4","温度","环境"]
                        delegate:RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr(modelData)
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
                                id:dataField
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                            YaheiText {
                                text:qsTr("报警等级")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
                                id:lecelField
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    }
                    BaseButton {
                        text: qsTr("查询")
                        font.pixelSize:  20
                        backRadius: 4
                        bckcolor: "#4785FF"
                        onClicked: {
                               App.protoManager.TunnelGas.queryData()
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
