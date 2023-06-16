import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12
ComboBox {
  id:combox
//  indicator.width: 22
//  indicator.height: 22
  font.family: "Microsoft Yahei"
  Material.accent: accentContrlColor
  topPadding: 3
  bottomPadding: 3
  leftPadding: 2
  rightPadding: 2
  background: Rectangle {
      color: "#FFFFFF"
      border.width: 1
      border.color: combox.focus ? "#5f5f5f" : "#a9a9a9"
      radius: 5
  }
}
