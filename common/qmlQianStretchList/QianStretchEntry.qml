import QtQuick 2.12
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtQml.Models 2.12
import Qt.Singleton 1.0
import "qrc:/common"

Item {
    signal switchPage(string name)
    property int strechCurrentIndex: 0
    property int strechLength: 0

    property var itemsArrays: [
        {
            name: "通信连接",
            stretch: false,
            subItem: [
                {
                    name: "网络连接",
                }
           ]
        },
        {
            name: "装置列表",
            stretch: false,
            subItem: [
                {
                    name:"隧道气体"
                },
                {
                    name:"隧道风机"
                }
           ]
        },
        {
            name: "参数设置查询",
            stretch: false,
            subItem: [
                {
                    name:"主控参数",
                },
                {
                    name:"本地网络",
                },
                {
                    name:"网络参数",
                },
                {
                    name:"气体参数",
                }
           ]
        },
        {
            name: "设置操作",
            stretch: false,
            subItem: [
                {
                    name: "主控操作",
                }
           ]
        },
        {
            name: "数据召测",
            stretch: false,
            subItem: [
                {
                    name: "气体召测",
                }
           ]
        }
    ]

    ListModel {
        id: stretchModel
        dynamicRoles : true
    }

    property int itemHeight: 60   // 184 * 60
    property string strechCurrentName:  ""
    property var alarmObjItem: null

    // 校验未知
    function checkUnknown(field, defaultData) {
        return field == undefined ? defaultData : field
    }

    function createModel(target, tier) {


        let idx = -999
        if( target.subItem == undefined  || !target.subItem.length) {
            idx = strechLength
            strechLength += 1
        }


        return {
            'name': target.name,
            'icon': checkUnknown(target.icon, ""),
            'hintNumber': checkUnknown(target.hintNumber, -1),
            'stretch':  checkUnknown(target.stretch, false),
            'tier': tier,
            'subItem' : [],
            'toIndex' :  idx,
        };
    }

    function createModel2(name, icon, tier, toIndex, hintNumber) {

        return {
            'name': name,
            'icon': icon,
            'hintNumber': hintNumber,
            'stretch': false,
            'tier': tier,
            'subItem' : [],
            'toIndex' :  toIndex,
        };
    }

    function appendSubItem(parent, subItem, tier) {
        if (subItem == undefined || subItem.length == 0) return;



        for(let i = 0; i < subItem.length; i++) {

            let model = createModel(subItem[i], tier);

            parent.subItem.append(model);

            let count = appendSubItem(parent.subItem.get(parent.subItem.count-1), subItem[i].subItem, tier+1);
        }
    }


    function searchItemByToIndex(parent, toIndex) {

        for(let i = 0; i < parent.count; i++) {

            let model = parent.get(i);

            if(model.toIndex == toIndex)
                return model;

            if(model.subItem.count > 0) {
                let ret = searchItemByToIndex(model.subItem, toIndex);
                if(ret != null) {
                    return ret;
                }
            }
        }
        return null;
    }


    Component.onCompleted: {
        for(let i = 0; i < itemsArrays.length; i++) {
            let tier = 0;
            let model = createModel(itemsArrays[i], tier);
            stretchModel.append(model);
            appendSubItem(stretchModel.get(stretchModel.count-1), itemsArrays[i].subItem, tier+1);
        }

    }


    ColumnLayout {
        anchors.fill: parent
        ListView {
            id: stretchList
            Layout.fillHeight: true
            Layout.topMargin: 8
            Layout.bottomMargin: 8
            Layout.rightMargin: skin.gradSupport  ? 0 :6
            Layout.fillWidth: true
            clip: true
            currentIndex: -1
            model: stretchModel


            delegate: QianStretchDalegate {
            }

            displaced: Transition {
                     NumberAnimation { properties: "x,y"; duration: 90 }
            }

            ScrollBar.vertical: ScrollBar {
                id: scroll1
                policy: size<1.0? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
                x: skin.gradSupport  ? 8 : stretchList.width-8

                contentItem: Rectangle {
                     implicitWidth: 8
                     implicitHeight: 100
                     radius: width / 2
                     color: skin.light ? skin.stretchSelectBackColor : accentOpacityHoverColor
                }
                width: 8
                background: Item {

                }
           }
        }



    }
}
