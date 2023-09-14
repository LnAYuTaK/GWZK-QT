import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import App 1.0
import App.NetWorkManager 1.0
import App.ProtocolManager 1.0
import "qrc:/common"
import "qrc:/common/qmlQianHints"
import "qrc:/common/qmlQianDialog"
/*参数设置查询 ------环境参数*/
Item {
    id:root
    property int leftWidth: 182
    property int fontsize: 19
    visible:true
    // 界面1
    TabBar {
        id: bar
        width: parent.width
        Repeater {
            model: ["温度","湿度","液位"]
            TabButton {
                text: modelData
                width: Math.max(100, bar.width / 3)
            }
        }
    }
    StackLayout {
        anchors.top:bar.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        currentIndex: bar.currentIndex
        Repeater {
            id:envRepeater
            model: ["温度","湿度","液位"]
            delegate:Item {
              ColumnLayout {
                   anchors.fill: parent
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
                            id:uplimit1
                            Layout.preferredWidth:240
                            color: acceptableInput  ? "black" : "#ff0000"
                            //int 验证器
                           validator: DoubleValidator {}
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
                            text:qsTr(modelData +"报警阈值下限等级1")
                            font.pixelSize: fontsize
                            Layout.preferredWidth: leftWidth
                            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                        }
                        BaseTextField{
                            id:lowlimit1
                            Layout.preferredWidth:240
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: DoubleValidator {}
                            onEditingFinished: {
                                if(acceptableInput){
                                }
                            }
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
                            id:uplimit2
                            Layout.preferredWidth:240
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: DoubleValidator {}
                            onEditingFinished: {
                                if(acceptableInput){
                                }
                            }
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
                            id:lowlimit2
                            Layout.preferredWidth:240
                            color: acceptableInput  ? "black" : "#ff0000"
                            validator: DoubleValidator {}
                            onEditingFinished: {
                                if(acceptableInput){
                                }
                            }
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
                            id:uplimit3
                            Layout.preferredWidth:240
                            color: acceptableInput  ? "black" : "#ff0000"
                           validator: DoubleValidator {}
                            onEditingFinished: {
                                if(acceptableInput){
                                }
                            }
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
                            id:lowlimit3
                            Layout.preferredWidth:240
                            color: acceptableInput  ? "black" : "#ff0000"
                           validator: DoubleValidator {}
                            onEditingFinished: {
                                if(acceptableInput){
                                }
                            }
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
                            id:keeplimit
                            Layout.preferredWidth:240
                            color: acceptableInput  ? "black" : "#ff0000"
                           validator: DoubleValidator {}
                            onEditingFinished: {
                                if(acceptableInput) {
                                }
                            }

                        }
                    }
                    RowLayout{
                        Layout.fillWidth: true
                        BaseButton {
                            text:qsTr("查询")
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
                            text: qsTr("设置")
                            font.pixelSize:  20
                            backRadius: 4
                            bckcolor: "#4785FF"
                            onClicked: {
                                if(!(uplimit1.acceptableInput&&uplimit2.acceptableInput&&uplimit3.acceptableInput
                                     &&lowlimit1.acceptableInput&&lowlimit2.acceptableInput&&lowlimit3.acceptableInput
                                     &&keeplimit.acceptableInput))
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
                }
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
}
