import QtQuick 2.14
import QtGraphicalEffects 1.12
import Qt.Window 1.0
import QtQuick.Window 2.14
import Qt.Singleton 1.0
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.1
import Qt.labs.settings 1.0
import App 1.0

Frameless {
    id: rootWindow
    //项目名称
    property string titleStr: "国网中电调试软件"
    property var areas: [
            Qt.rect(0, 0, 99999, 42)
    ]
    property int skintype :0
    height:    Screen.height/1.5
     width:    Screen.width/1.5
    x: (Screen.width - width) / 2
    y: (Screen.height - height) / 2
    property color accentColor: SkinSingleton.skins[skintype].accentColor              // 皮肤深色
    property color accentContrlColor: SkinSingleton.skins[skintype].accentContrlColor  // 皮肤控件深色
    property color accentOpacityColor: Qt.rgba(accentColor.r, accentColor.g, accentColor.b, 0.5)        // 皮肤控件深色透明 (一般用在滚动条)
    property color accentOpacityHoverColor: Qt.rgba(accentColor.r, accentColor.g, accentColor.b, 0.45)  // 皮肤控件深色透明 淡色 (一般用在滚动条鼠标徘徊)

    property color tingeColor: skin.light ? "#555" : "#b1b1b1"                      // 皮肤淡色(白色皮肤为浅黑   黑色皮肤为灰色)
    property color tingeDrakerColor: Qt.darker(tingeColor, 1.2)                     // 皮肤谈深色

    property color tingeOpacityColor: skin.light ? "#11000000" : "#11FFFFFF"        // 皮肤谈透明色
    property color tingeOpacityLightColor: skin.light ? "#06000000" : "#06FFFFFF"   // 皮肤谈透明色(亮)


    property color mainColor: !skin.gradSupport && !skin.imageSupport ? skin.mainColor :
                              !skin.light  ? Qt.rgba(0,0,0, skin.gradMainOpacity - setting.skinOpacity * 0.48)    : Qt.rgba(1,1,1, skin.gradMainOpacity + setting.skinOpacity * 0.28)

    property var skin: SkinSingleton.skins[skintype]
//    property int xOffset: 0 // 自定义的属性
//    property int yOffset: 0 // 自定义的属性
//    MouseArea {
//        anchors.fill: parent
//        onPressed: {
//            // 记录鼠标按下时的窗口位置
//            rootWindow.xOffset = mainWindow.x - mouse.x
//            rootWindow.yOffset = mainWindow.y - mouse.y
//        }
//    }

//    // 鼠标移动事件
//    MouseArea {
//        anchors.fill: parent
//        onPositionChanged: {
//            // 当鼠标按下并移动时，更新窗口位置
//            if (mouse.buttons === Qt.LeftButton) {
//                rootWindow.x = mouse.x + rootWindow.xOffset
//                rootWindow.y = mouse.y + rootWindow.yOffset
//            }
//        }
//    }
    Material.accent: accentColor
    Material.theme:  Material.Light
    Material.foreground: tingeColor
    //安卓全屏
    Component.onCompleted:{
       if(rootWindow.isAndroid){
            rootWindow.width = Screen.width
            rootWindow.height =Screen.height
            rootWindow.showFullScreen()
       }
    }
    visible: true
    title: titleStr
    color: "transparent"
    resizable: true
    moveArea:  areas
    function closeFunc() {
        close();
    }
    WindowEntry {
        anchors.fill: parent
        anchors.margins: rootWindow.maximized ? 0 : 8
        radius: rootWindow.maximized ? 0 : 4
    }
    Settings {
        id: setting
        property int skinIndex: 1
        property real skinOpacity: 1
        property string skinCustomFile: ""
        fileName: "app.ini"
    }

}
