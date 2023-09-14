import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import App.NetWorkManager 1.0
import "qrc:/common"
import "qrc:/common/qmlQianHints"
import "qrc:/common/qmlQianDialog"
/*参数设置查询 ------网络参数设置模块 (后台网络)*/
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
                    //服务器地址
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("主站IP地址")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                        }
                        BaseTextField{
                          id:masterip
                          color: acceptableInput  ? "black" : "#ff0000"
                          Layout.preferredWidth:280
                          validator: RegExpValidator {
                              regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                          }
                          onEditingFinished: {
                              //验证通过写入
                              if(acceptableInput){

                              }
                          }

                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("主站IP端口地址")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                        }
                        BaseTextField{
                            id:masterport
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: IntValidator {
                                  bottom: 0
                                  top: 65535
                            }
                            onEditingFinished: {
                                if(acceptableInput)
                                {

                                }
                            }

                        }
                    }
                    RowLayout{
                        spacing:20
                        Layout.fillWidth: true
                        YaheiText {
                            text:qsTr("主站连接方式")
                            Layout.preferredWidth: leftWidth
                            font.pixelSize: fontsize
                            Layout.alignment: Qt.AlignTop |Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 45
                          model: ["TCP","UDP"]
                          onCurrentTextChanged: {

                          }
                        }
                        BaseTextField{
                          Layout.preferredWidth:140

                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"SIM1卡APN"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                          id:simapn
                          Layout.preferredWidth:280
                          maximumLength: 32
                          color: acceptableInput  ? "black" : "#ff0000"
                          validator: RegExpValidator {
                              regExp: /^[a-zA-Z0-9]*$/ // 只允许输入字母和数字
                          }
                          onEditingFinished: {
                              if(acceptableInput){

                              }
                          }

                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"SIM1卡用户名"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id:simusername
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: RegExpValidator {
                                regExp: /^[a-zA-Z0-9]*$/ // 只允许输入字母和数字
                            }
                            onEditingFinished: {
                                if(acceptableInput){

                                }
                            }


                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"SIM1卡密码"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id:simpasswd
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: RegExpValidator {
                                regExp: /^[a-zA-Z0-9]*$/ // 只允许输入字母和数字
                            }
                            onEditingFinished: {
                                if(acceptableInput)
                                {

                                }
                            }

                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"备用IP地址"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }

                        BaseTextField{
                            id:alternateIp
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: RegExpValidator {
                                regExp: /^((([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\.){3})([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$/
                            }
                            onEditingFinished: {
                                if(acceptableInput)
                                {

                                }
                            }

                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"备用端口地址"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id: alternateport
                            Layout.preferredWidth:280
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: IntValidator {
                                  bottom: 0
                                  top: 65535
                            }
                            onEditingFinished: {
                                if(acceptableInput)
                                {

                                }
                            }

                        }
                    }
                    RowLayout{
                        spacing:20
                        YaheiText {
                            anchors.centerIn: parent.Center
                            text:"备用链接方式"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseComboBox{
                          Layout.preferredWidth:120
                          Layout.preferredHeight: 45
                          model: [ "TCP","UDP"]
                          onCurrentTextChanged: {

                          }
                        }
                        BaseTextField{
                          readOnly: true
                          Layout.preferredWidth:140

                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        BaseButton {
                            text: "查询"
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                            onClicked: {

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
                                if(!(masterip.acceptableInput && masterport.acceptableInput&&
                                     simapn.acceptableInput && simusername.acceptableInput &&
                                     simpasswd.acceptableInput && alternateIp.acceptableInput &&
                                     alternateIp.acceptableInput && alternateport.acceptableInput))
                                {
                                     message("error","格式设置错误")
                                     return
                                }
                                else
                                {

                                }
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
