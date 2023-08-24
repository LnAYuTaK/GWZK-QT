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
/*参数设置查询 ------气体参数*/
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
            model: ["O2","H2", "Cl2","H2S","CH4","CO","CO2"]
            TabButton {
                text: modelData
                width: Math.max(100, bar.width / 8)
            }
        }
    }

    function selectGasType(typename)
    {
        var temp = typename
        if(temp  === "O2")
        {
            return GasParaController.O2
        }
        else if(temp  === "H2")
        {
            return GasParaController.H2
        }
        else if(temp  === "Cl2")
        {
            return GasParaController.Cl2
        }
        else if(temp  === "H2S")
        {
            return GasParaController.H2S
        }
        else if(temp  === "CH4")
        {
            return GasParaController.CH4
        }
        else if(temp  === "CO")
        {
            return GasParaController.CO
        }
        else if(temp  === "CO2")
        {
            return GasParaController.CO2
        }
    }
    StackLayout {
        anchors.top:bar.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        currentIndex: bar.currentIndex
        Repeater {
            model: ["O2","H2", "Cl2","H2S","CH4","CO","CO2"]
            Item {
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
                            validator: IntValidator {}
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    if(modelData === "O2"){
                                       App.protoManager.GasParaCtrl.GasParaO2.UpThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "H2"){
                                       App.protoManager.GasParaCtrl.GasParaH2.UpThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "Cl2"){
                                       App.protoManager.GasParaCtrl.GasParaCl2.UpThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "H2S"){
                                        App.protoManager.GasParaCtrl.GasParaH2S.UpThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "CH4") {
                                        App.protoManager.GasParaCtrl.GasParaCH4.UpThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "CO"){
                                        App.protoManager.GasParaCtrl.GasParaCO.UpThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "CO2"){
                                        App.protoManager.GasParaCtrl.GasParaCO2.UpThresholdLimitLevel1 = text
                                    }
                                }
                            }
                            text:{
                                if(modelData === "O2"){
                                   return App.protoManager.GasParaCtrl.GasParaO2.UpThresholdLimitLevel1
                                }
                                else if(modelData  === "H2"){
                                  return App.protoManager.GasParaCtrl.GasParaH2.UpThresholdLimitLevel1
                                }
                                else if(modelData  === "Cl2"){
                                  return App.protoManager.GasParaCtrl.GasParaCl2.UpThresholdLimitLevel1
                                }
                                else if(modelData  === "H2S"){
                                   return App.protoManager.GasParaCtrl.GasParaH2S.UpThresholdLimitLevel1
                                }
                                else if(modelData  === "CH4"){
                                   return App.protoManager.GasParaCtrl.GasParaCH4.UpThresholdLimitLevel1
                                }
                                else if(modelData  === "CO"){
                                   return App.protoManager.GasParaCtrl.GasParaCO.UpThresholdLimitLevel1
                                }
                                else if(modelData  === "CO2"){
                                   return App.protoManager.GasParaCtrl.GasParaCO2.UpThresholdLimitLevel1
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
                            validator: IntValidator {}
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    if(modelData === "O2"){
                                       App.protoManager.GasParaCtrl.GasParaO2.LowThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "H2"){
                                       App.protoManager.GasParaCtrl.GasParaH2.LowThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "Cl2"){
                                       App.protoManager.GasParaCtrl.GasParaCl2.LowThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "H2S"){
                                        App.protoManager.GasParaCtrl.GasParaH2S.LowThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "CH4"){
                                        App.protoManager.GasParaCtrl.GasParaCH4.LowThresholdLimitLevel1 = text
                                    }
                                    else if(modelData === "CO"){
                                        App.protoManager.GasParaCtrl.GasParaO2.LowThresholdLimitLevel1 = text
                                    }
                                    else if(modelData  === "CO2"){
                                        App.protoManager.GasParaCtrl.GasParaCO2.LowThresholdLimitLevel1 = text
                                    }
                                }
                            }
                            text:{
                                if(modelData === "O2"){
                                  return App.protoManager.GasParaCtrl.GasParaO2.LowThresholdLimitLevel1
                                }
                                else if(modelData  === "H2"){
                                  return App.protoManager.GasParaCtrl.GasParaH2.LowThresholdLimitLevel1
                                }
                                else if(modelData  === "Cl2"){
                                  return App.protoManager.GasParaCtrl.GasParaCl2.LowThresholdLimitLevel1
                                }
                                else if(modelData  === "H2S") {
                                  return  App.protoManager.GasParaCtrl.GasParaH2S.LowThresholdLimitLevel1
                                }
                                else if(modelData  === "CH4"){
                                  return  App.protoManager.GasParaCtrl.GasParaCH4.LowThresholdLimitLevel1
                                }
                                else if(modelData  === "CO"){
                                  return  App.protoManager.GasParaCtrl.GasParaCO.LowThresholdLimitLevel1
                                }
                                else if(modelData  === "CO2"){
                                  return  App.protoManager.GasParaCtrl.GasParaCO2.LowThresholdLimitLevel1
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
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    if(modelData === "O2"){
                                       App.protoManager.GasParaCtrl.GasParaO2.LowThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "H2"){
                                       App.protoManager.GasParaCtrl.GasParaH2.LowThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "Cl2"){
                                       App.protoManager.GasParaCtrl.GasParaCl2.LowThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "H2S"){
                                        App.protoManager.GasParaCtrl.GasParaH2S.LowThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "CH4"){
                                        App.protoManager.GasParaCtrl.GasParaCH4.LowThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "CO"){
                                        App.protoManager.GasParaCtrl.GasParaCO.LowThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "CO2"){
                                        App.protoManager.GasParaCtrl.GasParaCO2.LowThresholdLimitLevel2 = text
                                    }
                                }
                            }
                            text:{
                                if(modelData === "O2"){
                                   return App.protoManager.GasParaCtrl.GasParaO2.LowThresholdLimitLevel2
                                }
                                else if(modelData  === "H2"){
                                  return App.protoManager.GasParaCtrl.GasParaH2.LowThresholdLimitLevel2
                                }
                                else if(modelData  === "Cl2"){
                                  return App.protoManager.GasParaCtrl.GasParaCl2.LowThresholdLimitLevel2
                                }
                                else if(modelData === "H2S"){
                                  return  App.protoManager.GasParaCtrl.GasParaH2S.LowThresholdLimitLevel2
                                }
                                else if(modelData  === "CH4"){
                                  return  App.protoManager.GasParaCtrl.GasParaCH4.LowThresholdLimitLevel2
                                }
                                else if(modelData  === "CO"){
                                  return  App.protoManager.GasParaCtrl.GasParaCO.LowThresholdLimitLevel2
                                }
                                else if(modelData === "CO2"){
                                  return App.protoManager.GasParaCtrl.GasParaCO2.LowThresholdLimitLevel2
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
                            validator: IntValidator {}
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    if(modelData === "O2"){
                                       App.protoManager.GasParaCtrl.GasParaO2.UpThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "H2"){
                                       App.protoManager.GasParaCtrl.GasParaH2.UpThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "Cl2"){
                                       App.protoManager.GasParaCtrl.GasParaCl2.UpThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "H2S"){
                                        App.protoManager.GasParaCtrl.GasParaH2S.UpThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "CH4"){
                                        App.protoManager.GasParaCtrl.GasParaCH4.UpThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "CO"){
                                        App.protoManager.GasParaCtrl.GasParaCO.UpThresholdLimitLevel2 = text
                                    }
                                    else if(modelData  === "CO2"){
                                        App.protoManager.GasParaCtrl.GasParaCO2.UpThresholdLimitLevel2 = text
                                    }
                                }
                            }
                            text:{
                                if(modelData === "O2"){
                                  return App.protoManager.GasParaCtrl.GasParaO2.UpThresholdLimitLevel2
                                }
                                else if(modelData  === "H2"){
                                  return  App.protoManager.GasParaCtrl.GasParaH2.UpThresholdLimitLevel2
                                }
                                else if(modelData  === "Cl2"){
                                  return  App.protoManager.GasParaCtrl.GasParaCl2.UpThresholdLimitLevel2
                                }
                                else if(modelData  === "H2S"){
                                  return  App.protoManager.GasParaCtrl.GasParaH2S.UpThresholdLimitLevel2
                                }
                                else if(modelData  === "CH4") {
                                   return  App.protoManager.GasParaCtrl.GasParaCH4.UpThresholdLimitLevel2
                                }
                                else if(modelData  === "CO") {
                                   return  App.protoManager.GasParaCtrl.GasParaCO.UpThresholdLimitLevel2
                                }
                                else if(modelData  === "CO2"){
                                   return App.protoManager.GasParaCtrl.GasParaCO2.UpThresholdLimitLevel2
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
                            validator: IntValidator {}
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    if(modelData === "O2"){
                                       App.protoManager.GasParaCtrl.GasParaO2.UpThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "H2"){
                                       App.protoManager.GasParaCtrl.GasParaH2.UpThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "Cl2"){
                                       App.protoManager.GasParaCtrl.GasParaCl2.UpThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "H2S") {
                                        App.protoManager.GasParaCtrl.GasParaH2S.UpThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "CH4"){
                                        App.protoManager.GasParaCtrl.GasParaCH4.UpThresholdLimitLevel3 = text
                                    }
                                    else if(modelData === "CO") {
                                        App.protoManager.GasParaCtrl.GasParaCO.UpThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "CO2"){
                                        App.protoManager.GasParaCtrl.GasParaCO2.UpThresholdLimitLevel3 = text
                                    }
                                }
                            }
                            text:{

                                if(modelData === "O2"){
                                  return  App.protoManager.GasParaCtrl.GasParaO2.UpThresholdLimitLevel3
                                }
                                else if(modelData  === "H2"){
                                  return  App.protoManager.GasParaCtrl.GasParaH2.UpThresholdLimitLevel3
                                }
                                else if(modelData === "Cl2"){
                                  return App.protoManager.GasParaCtrl.GasParaCl2.UpThresholdLimitLevel3
                                }
                                else if(modelData  === "H2S"){
                                   return App.protoManager.GasParaCtrl.GasParaH2S.UpThresholdLimitLevel3
                                }
                                else if(modelData  === "CH4"){
                                   return App.protoManager.GasParaCtrl.GasParaCH4.UpThresholdLimitLevel3
                                }
                                else if(modelData  === "CO") {
                                   return App.protoManager.GasParaCtrl.GasParaCO.UpThresholdLimitLevel3
                                }
                                else if(modelData  === "CO2"){
                                   return App.protoManager.GasParaCtrl.GasParaCO2.UpThresholdLimitLevel3
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
                            validator: IntValidator {}
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    if(modelData === "O2"){
                                       App.protoManager.GasParaCtrl.GasParaO2.LowThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "H2"){
                                       App.protoManager.GasParaCtrl.GasParaH2.LowThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "Cl2"){
                                       App.protoManager.GasParaCtrl.GasParaCl2.LowThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "H2S") {
                                        App.protoManager.GasParaCtrl.GasParaH2S.LowThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "CH4"){
                                        App.protoManager.GasParaCtrl.GasParaCH4.LowThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "CO") {
                                        App.protoManager.GasParaCtrl.GasParaCO.LowThresholdLimitLevel3 = text
                                    }
                                    else if(modelData  === "CO2"){
                                        App.protoManager.GasParaCtrl.GasParaCO2.LowThresholdLimitLevel3 = text
                                    }
                                }
                            }
                            text:{
                                if(modelData === "O2"){
                                  return  App.protoManager.GasParaCtrl.GasParaO2.LowThresholdLimitLevel3
                                }
                                else if(modelData  === "H2"){
                                  return  App.protoManager.GasParaCtrl.GasParaH2.LowThresholdLimitLevel3
                                }
                                else if(modelData  === "Cl2"){
                                   return App.protoManager.GasParaCtrl.GasParaCl2.LowThresholdLimitLevel3
                                }
                                else if(modelData  === "H2S"){
                                  return   App.protoManager.GasParaCtrl.GasParaH2S.LowThresholdLimitLevel3
                                }
                                else if(modelData === "CH4"){
                                   return  App.protoManager.GasParaCtrl.GasParaCH4.LowThresholdLimitLevel3
                                }
                                else if(modelData === "CO") {
                                   return  App.protoManager.GasParaCtrl.GasParaCO.LowThresholdLimitLevel3
                                }
                                else if(modelData === "CO2"){
                                   return  App.protoManager.GasParaCtrl.GasParaCO2.LowThresholdLimitLevel3
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
                            validator: IntValidator {}
                            onEditingFinished: {
                                if(acceptableInput)
                                {
                                    if(modelData === "O2"){
                                       App.protoManager.GasParaCtrl.GasParaO2.KeepThresholdLimit = text
                                    }
                                    else if(modelData  === "H2"){
                                       App.protoManager.GasParaCtrl.GasParaH2.KeepThresholdLimit = text
                                    }
                                    else if(modelData  === "Cl2"){
                                       App.protoManager.GasParaCtrl.GasParaCl2.KeepThresholdLimit = text
                                    }
                                    else if(modelData  === "H2S") {
                                        App.protoManager.GasParaCtrl.GasParaH2S.KeepThresholdLimit = text
                                    }
                                    else if(modelData  === "CH4"){
                                        App.protoManager.GasParaCtrl.GasParaCH4.KeepThresholdLimit = text
                                    }
                                    else if(modelData  === "CO") {
                                        App.protoManager.GasParaCtrl.GasParaCO.KeepThresholdLimit = text
                                    }
                                    else if(modelData === "CO2"){
                                        App.protoManager.GasParaCtrl.GasParaCO2.KeepThresholdLimit = text
                                    }
                                }
                            }
                            text:{
                                if(modelData === "O2"){
                                   App.protoManager.GasParaCtrl.GasParaO2.KeepThresholdLimit
                                }
                                else if(modelData === "H2"){
                                   App.protoManager.GasParaCtrl.GasParaH2.KeepThresholdLimit
                                }
                                else if(modelData === "Cl2"){
                                   App.protoManager.GasParaCtrl.GasParaCl2.UpThresholdLimitLevel3
                                }
                                else if(modelData === "H2S"){
                                    App.protoManager.GasParaCtrl.GasParaH2S.UpThresholdLimitLevel3
                                }
                                else if(modelData === "CH4"){
                                    App.protoManager.GasParaCtrl.GasParaCH4.UpThresholdLimitLevel3
                                }
                                else if(modelData === "CO") {
                                    return App.protoManager.GasParaCtrl.GasParaCO.UpThresholdLimitLevel3
                                }
                                else if(modelData === "CO2"){
                                    return App.protoManager.GasParaCtrl.GasParaCO2.UpThresholdLimitLevel3
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
                                App.protoManager.GasParaCtrl.queryData(selectGasType(modelData))
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
                                     App.protoManager.GasParaCtrl.setData(selectGasType(modelData))
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
