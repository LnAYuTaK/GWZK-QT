import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.12
import Qt.Singleton 1.0
import "qrc:/common"
/*标题栏*/
Rectangle {
    id: windowtitle

    MouseArea {
        anchors.fill: parent
        onDoubleClicked: {
            scaleInput.clicked();
        }
    }
    RowLayout {
        z: 2
        anchors.fill: parent
        anchors.leftMargin: 8
        anchors.margins: 0
        Layout.margins: 0
        spacing: 0

        YaheiText {
            text: rootWindow.title
            font.pixelSize: 17
            color: "#FFF"
            Layout.fillWidth: true
            Layout.leftMargin: 3
        }

        ImageButton {
            imageSrc: "qrc:/windowRes/minimize.png"
            Layout.alignment:  Qt.AlignTop | Qt.AlignRight
            backHoverColor: "#22FFFFFF"

            BaseToolTip {
                 visible: parent.hovered
                 text: "最小化"
                 font.pixelSize: 12
                 delay: 1000

            }
            //安卓不显示缩小
            visible: !(rootWindow.isAndroid)
            onClicked: {
               showMinimized()
            }
            padding: 1
        }
        ScaleImageButton {
            id: scaleInput
            backHoverColor:"#22FFFFFF"
            normalImage: "qrc:/windowRes/normal.png"
            maxImage: "qrc:/windowRes/max.png"
            //安卓不显示最大化
            visible: !(rootWindow.isAndroid)
            BaseToolTip {
                 visible: parent.hovered
                 text: scaleInput.shrink ? "最大化" : "恢复"
                 font.pixelSize: 12
                 delay: 1000
            }
            Layout.alignment : Qt.AlignTop | Qt.AlignRight
            focusPolicy: Qt.NoFocus
            onShrinkChanged: {
                rootWindow.maximized = !shrink
                rootWindow.update();
            }
            padding: 3

        }
        ImageButton {
            imageSrc: "qrc:/windowRes/close.png"
            Layout.alignment:  Qt.AlignTop | Qt.AlignRight
            backHoverColor: "#FA5151"

            BaseToolTip {
                 visible: parent.hovered
                 text: "关闭"
                 font.pixelSize: 12
                 delay: 1000

            }
            onClicked: rootWindow.closeFunc()
            padding: 3
        }
    }
    SkinPopup {
        id: skin_popup
    }



}
