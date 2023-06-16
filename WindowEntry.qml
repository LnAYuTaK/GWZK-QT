import QtQuick 2.12
import QtGraphicalEffects 1.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import Qt.Singleton 1.0
import FluentUI 1.0
import "qrc:/common"
import "qrc:/common/qmlQianDialog"
import "qrc:/common/qmlQianHints"
Rectangle {
    id: windowEntry
    color: skin.mainColor
    gradient: skin.gradient


//    Message{
//        id:messageTip
//        z: 1
//        parent: Overlay.overlay
//    }

//    function message(type, message) {
//        if(type!=='success'&&type!=='error'&&type!=='info'){
//            return false
//        }
//        messageTip.open(type, message)
//    }

//    BlogDialog {
//        id: skinQianDialog
//        backParent: windowEntry
//        parent: Overlay.overlay
//        onAccept: {
//           message('success', "You clicked the accept button!")
//           skinQianDialog.close();
//        }
//    }

//    Component.onCompleted: {
//        skinQianDialog.dialogOpen()
//    }

    //程序启动弹出动画
//    SequentialAnimation {
//      id: appStartAnimation
//      running: true
//      NumberAnimation { target: windowEntry;
//          properties: "scale"; from: 0.3; to: 1.0; easing.type: Easing.InOutQuad; duration: 200 }

//    }
//    layer.enabled: skin.windowShadow && !appStartAnimation.running && !rootWindow.maximized? true : false
//    layer.effect: DropShadow {
//        color: "#000000"
//    }


    ColumnLayout {
        id :ui
        anchors.fill: parent
        spacing: 0
        WindowTilte {
            color: skin.titleColor
            Layout.fillWidth: true
            Layout.preferredHeight: contentList.fullscreen ? 0 :  42
            Layout.alignment: Qt.AlignTop
            Behavior on Layout.preferredHeight {
                NumberAnimation { duration: 300 }
            }
            clip: true
        }
        GridLayout {
            id :selectPrduct
            visible: true
            anchors.centerIn: parent
            //Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
               rows: 2
               columns: 3
               rowSpacing: 50
               columnSpacing: 50
               BaseButton {
                   id: product1
                   text: "Product 1"
                   backRadius: 4
                   bckcolor: "#4785FF"
                   onClicked: {
                       selectPrduct.visible =false
                       contentList.visible = true
                       // 调用Product1显示函数
                   }
                   Layout.row: 0
                   Layout.column: 0
               }

               BaseButton {
                   id: product2
                   text: "Product 2"
                   backRadius: 4
                   bckcolor: "#4785FF"
                   onClicked: {
                       // 调用Product2显示函数
                   }
                   Layout.row: 0
                   Layout.column: 1
               }
               BaseButton {
                   id: product3
                   text: "Product 3"
                   backRadius: 4
                   bckcolor: "#4785FF"
                   onClicked: {
                       // 调用Product2显示函数
                   }
                   Layout.row: 1
                   Layout.column: 0
               }

               BaseButton {
                   id: product4
                   text: "Product 4"
                   backRadius: 4
                   bckcolor: "#4785FF"
                   onClicked: {
                       // 调用Product2显示函数
                   }
                   Layout.row: 1
                   Layout.column: 1
               }
               // 依此类推，创建5个按钮
           }

        ContentList {
            id: contentList
            visible: false
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

}
