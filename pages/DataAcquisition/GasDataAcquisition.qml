﻿import QtQuick 2.14
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
                ColumnLayout {
                    id: contents
                    anchors.margins: 30
                    anchors.fill: parent
                    spacing: 20
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("O2(VOL)")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("CO(ppm)")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("Cl2(ppm)")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("H2S(ppm)")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("H2(ppm)")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("CO2(ppm))")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("CH4(%LEL)")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("环境温度(℃)")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
                            }
                        }
                    RowLayout{
                            spacing:10
                            Layout.fillWidth: true
                            YaheiText {
                                text:qsTr("环境湿度(%RH)")
                                font.pixelSize: fontsize
                                Layout.preferredWidth: leftWidth
                                Layout.alignment:  Qt.AlignTop |Qt.AlignLeft
                            }
                            BaseTextField{
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
                                readOnly: true
                                Layout.preferredWidth:100
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
