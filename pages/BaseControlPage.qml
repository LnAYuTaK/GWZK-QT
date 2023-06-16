import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import "qrc:/common"
Item {
    property int leftWidth: 182
    property int fontsize: 19
    ScrollView {
        id:flickable
        anchors.fill: parent
        clip:         true
//        ScrollBar.horizontal.interactive: true
        ScrollBar.vertical.interactive: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
//        ScrollBar.vertical.policy: ScrollBar.AlwaysOff
                ColumnLayout {
                    id: contents
                    anchors.rightMargin: 60
                    anchors.topMargin: 30
                    anchors.leftMargin: 60
                    anchors.bottomMargin: 30
                    anchors.fill: parent
                    spacing: 10
                    RowLayout {
                        YaheiText {
                            text: "Buttons"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        ColumnLayout {
                            spacing: 20
                            RowLayout {
                                spacing: 20
                                SkinBaseButton {
                                  font.pixelSize:  14
                                  backRadius: 4
                                  text: "SkinBtn1"
                                }
                                SkinBaseButton2 {
                                    font.pixelSize:  14
                                    backRadius: 4
                                    text: "SkinBtn2"
                                }
                            }
                            RowLayout {
                                spacing: 20
                                BaseButton {
                                    text: "Blue"
                                    Layout.preferredHeight: 28
                                    Layout.preferredWidth: 78
                                    font.pixelSize:  14
                                    backRadius: 4
                                    bckcolor: "#4785FF"
                                }

                                BaseButton {
                                  bckcolor: "#EC3315"
                                  Layout.preferredHeight: 28
                                  Layout.preferredWidth: 78
                                  font.pixelSize:  14
                                  backRadius: 4
                                  text: "Red"

                                }

                                BaseButton {
                                    text: "Yellow"
                                    Layout.preferredHeight: 28
                                    Layout.preferredWidth: 78
                                    font.pixelSize:  14
                                    backRadius: 4
                                    bckcolor: "#ED9709"
                                }
                            }

                        }
                    }

                    Rectangle {
                        height: 1
                        color: tingeOpacityColor
                        Layout.fillWidth: true
                        Layout.topMargin: 12
                    }

                    RowLayout {
                        YaheiText {
                            text: "RadioButton"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                            Layout.topMargin: 12
                        }
                        ColumnLayout {
                            RadioButton {
                              font.pixelSize: fontsize - 2
                              indicator.width: 18
                              indicator.height: 18

                              font.family: "Microsoft Yahei"
                              text: "Option 1"

                            }
                            RadioButton {
                              font.pixelSize: fontsize - 2
                              indicator.width: 18
                              indicator.height: 18
                              font.family: "Microsoft Yahei"
                              text: "Option 2"
                            }
                            RadioButton {
                              enabled: false
                              font.pixelSize: fontsize - 2
                              indicator.width: 18
                              indicator.height: 18
                              font.family: "Microsoft Yahei"
                              text: "Option 3"
                            }

                        }
                    }

                    Rectangle {
                        height: 1
                        color: tingeOpacityColor
                        Layout.fillWidth: true
                    }

                    RowLayout {
                        YaheiText {
                            text: "CheckBox"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                            Layout.topMargin: 12

                        }
                        ColumnLayout {
                            BaseCheckBox {
                              font.pixelSize: fontsize - 2
                              text: "Option 1"
                            }
                            BaseCheckBox {
                              font.pixelSize: fontsize - 2
                              text: "Option 2"
                            }
                            BaseCheckBox {
                              enabled: false
                              font.pixelSize: fontsize - 2
                              text: "Option 3"
                            }

                        }
                    }

                    Rectangle {
                        height: 1
                        color: tingeOpacityColor
                        Layout.fillWidth: true
                    }

                    RowLayout {
                        YaheiText {
                            text: "Switch"
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                            Layout.topMargin: 12

                        }

                        RowLayout {
                            spacing: 20
                            Switch {
                              font.pixelSize: fontsize - 2
                              indicator.height: 18
                              font.family: "Microsoft Yahei"
                              text: "Blue"
                              Material.accent: "#4785FF"
                            }
                            Switch {
                              font.pixelSize: fontsize - 2
                              indicator.height: 18
                              font.family: "Microsoft Yahei"
                              text: "Red"
                              Material.accent: "#EC3315"
                            }
                            Switch {
                              enabled: false
                              font.pixelSize: fontsize - 2
                              indicator.height: 18
                              font.family: "Microsoft Yahei"
                              text: "Disable"

                            }

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

