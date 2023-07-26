import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import "qrc:/common"
/*参数设置查询 ------气体参数*/
Item {
    id:root
    property int leftWidth: 182
    property int fontsize: 19
    SwipeView {
          id: swipeView
          anchors.fill: parent
          interactive: true
          currentIndex: 0
          Repeater {
              model: ["O2","CO","H2", "Cl2","H2S","CO2","CH4","温度","湿度"]
              ColumnLayout {
                  spacing: 0
                  RowLayout{
                      spacing:20
                      Layout.fillWidth: true
                      YaheiText {
                          text:qsTr(modelData +"报警阈值上限等级1")
                          font.pixelSize: fontsize
                          Layout.preferredWidth: leftWidth
                          Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                      }
                      BaseTextField{
                          Layout.preferredWidth:240
                      }
                  }
                  RowLayout{
                      spacing:20
                      Layout.fillWidth: true
                      YaheiText {
                          text:qsTr(modelData +"报警阈值下限等级1")
                          font.pixelSize: fontsize
                          Layout.preferredWidth: leftWidth
                          Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                      }
                      BaseTextField{
                          Layout.preferredWidth:240
                      }
                  }
                  RowLayout{
                      spacing:20
                      Layout.fillWidth: true
                      YaheiText {
                          text:qsTr(modelData +"报警阈值上限等级2")
                          font.pixelSize: fontsize
                          Layout.preferredWidth: leftWidth
                          Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                      }
                      BaseTextField{
                          Layout.preferredWidth:240
                      }
                  }
                  RowLayout{
                      spacing:20
                      Layout.fillWidth: true
                      YaheiText {
                          text:qsTr(modelData +"报警阈值下限等级2")
                          font.pixelSize: fontsize
                          Layout.preferredWidth: leftWidth
                          Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                      }
                      BaseTextField{
                          Layout.preferredWidth:240
                      }
                  }
                  RowLayout{
                      spacing:20
                      Layout.fillWidth: true
                      YaheiText {
                          text:qsTr(modelData +"报警阈值上限等级3")
                          font.pixelSize: fontsize
                          Layout.preferredWidth: leftWidth
                          Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                      }
                      BaseTextField{
                          Layout.preferredWidth:240
                      }
                  }
                  RowLayout{
                      spacing:20
                      Layout.fillWidth: true
                      YaheiText {
                          text:qsTr(modelData +"报警阈值下限等级3")
                          font.pixelSize: fontsize
                          Layout.preferredWidth: leftWidth
                          Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                      }
                      BaseTextField{
                          Layout.preferredWidth:240
                      }
                  }
                  RowLayout{
                      spacing:20
                      Layout.fillWidth: true
                      YaheiText {
                          text:qsTr(modelData +"防抖阈值")
                          font.pixelSize: fontsize
                          Layout.preferredWidth: leftWidth
                          Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                      }
                      BaseTextField{
                          Layout.preferredWidth:240
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
              }
          }
      }
    PageIndicator {
        count: 9 // 页面数量
        currentIndex: swipeView.currentIndex

    }
    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }

//    ScrollView {
//        id:flickable
//        anchors.fill: parent
//        clip:         true
//        ScrollBar.vertical.interactive: true
//        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
//                ColumnLayout {
//                    id: contents
//                    anchors.rightMargin: 60
//                    anchors.topMargin: 30
//                    anchors.leftMargin: 60
//                    anchors.bottomMargin: 30
//                    anchors.fill: parent
//                    spacing: 20
//                    //本机IP
//                    RowLayout{
//                        spacing:20
//                        YaheiText {
//                            anchors.centerIn: parent.Center
//                            text:qsTr("氧气")
//                            font.pixelSize: fontsize
//                            Layout.preferredWidth: leftWidth
//                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
//                        }
//                        BaseTextField{
//                            Layout.preferredWidth:50
//                        }
//                    }
//                    RowLayout{
//                        spacing:20
//                        YaheiText {
//                            anchors.centerIn: parent.Center
//                            text:qsTr("网关")
//                            font.pixelSize: fontsize
//                            Layout.preferredWidth: leftWidth
//                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
//                        }
//                        BaseTextField{
//                            Layout.preferredWidth:280
//                        }
//                    }
//                    RowLayout{
//                        spacing:20
//                        YaheiText {
//                            anchors.centerIn: parent.Center
//                            text:qsTr("子网掩码")
//                            font.pixelSize: fontsize
//                            Layout.preferredWidth: leftWidth
//                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
//                        }
//                        BaseTextField{
//                          Layout.preferredWidth:280
//                        }
//                    }
//                    RowLayout{
//                        spacing:20
//                        YaheiText {
//                            anchors.centerIn: parent.Center
//                            text:qsTr("MAC地址")
//                            font.pixelSize: fontsize
//                            Layout.preferredWidth: leftWidth
//                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
//                        }
//                        BaseTextField{
//                            Layout.preferredWidth:280
//                        }
//                    }
//                    RowLayout{
//                        Layout.fillWidth: true
//                        BaseButton {
//                            text:qsTr("查询")
//                            font.pixelSize:  20
//                            backRadius: 4
//                            bckcolor: "#4785FF"
//                        }
//                        Rectangle {
//                             width: 200
//                        }
//                        BaseButton {
//                            text: qsTr("设置")
//                            font.pixelSize:  20
//                            backRadius: 4
//                            bckcolor: "#4785FF"
//                        }
//                    }
//                    //填充最底部
//                    Rectangle {
//                         width: parent.width
//                         height: 10
//                     }
//                }
//        //}
//    }
//    Item {
//        Layout.fillHeight: true
//        Layout.fillWidth: true
//    }

}
