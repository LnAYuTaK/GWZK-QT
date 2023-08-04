import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12
TextField {
    id: textfield
    selectByMouse: true
    font.family: "Microsoft Yahei"
    font.pixelSize: 16
    property color backColor: skin.light ?  "#77FFFFFF" : "11000000"
    property color focusColor: Material.accent
    property color normalColor: Material.foreground
    topPadding: 3
    bottomPadding: 3
    leftPadding: 2
    rightPadding: 2
    color: acceptableInput  ? "black" : "#ff0000"
    background: Rectangle {
        color: "#FFFFFF"
        border.width: 1
        border.color: textfield.focus ? "#5f5f5f" : "#a9a9a9"
        radius: 5
    }
}
