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
                                id: countfield
                                width :90
                                //0-65535
                                validator: IntValidator {
                                      bottom: 0
                                      top: 65535
                                }
                                onTextChanged: {
                                    App.protoManager.TunnelGasMon.count = text
                                }
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
                                id: cyclefield
                                 width :90
                                 //0-65535
                                 validator: IntValidator {
                                       bottom: 0
                                       top: 65535
                                   }
                                 onTextChanged: {
                                     App.protoManager.TunnelGasMon.cycle = text
                                 }
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
                                id:channelfield
                                width:90
                                //0-65535
                                validator: IntValidator {
                                      bottom: 0
                                      top: 65535
                                  }
                                onTextChanged: {
                                    App.protoManager.TunnelGasMon.channel = text
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
                            text:qsTr("气体地址格式")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 40
                          model: ["递增", "相同"]
                          onCurrentIndexChanged: {
                             App.protoManager.TunnelGasMon.format = currentIndex
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
                            text: qsTr("气体监测编码")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id:gasCode
                            Layout.preferredWidth:280
                            maximumLength: 17
                            validator: RegExpValidator {
                                regExp: /^[a-zA-Z0-9]*$/ // 只允许输入字母和数字
                            }
                            onTextChanged: {
                                App.protoManager.TunnelGasMon.address = text
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
                            onClicked:{
                                 App.protoManager.TunnelGasMon.queryData()
                            }
                        }
                        Rectangle {
                             width: 200
                        }
                        BaseButton {
                            text: "设置"
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                            onClicked:{
                                //校验输入数据
                                if(countfield.text == "")
                                {
                                    message("error","数量设置格式错误")
                                    return
                                }
                                if(cyclefield.text == "")
                                {
                                    message("error","周期设置格式错误")
                                    return
                                }
                                if(channelfield.text == "")
                                {
                                    message("error","通道设置格式错误")
                                    return
                                }
                                if(gasCode.text.length <17)
                                {
                                    message("error","气体编码设置格式错误")
                                    return
                                }
                                App.protoManager.TunnelGasMon.setData()
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
