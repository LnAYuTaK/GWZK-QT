import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import "qrc:/common"
import "qrc:/pages"
import "qrc:/pages/DeviceList"
import "qrc:/pages/ParaSettingQuery"
import "qrc:/pages/CommLink"
StackLayout {
    id: stack
    clip: true
    function switchPage(name) {
        for (var i = 0; i < stack.data.length; i++) {
            if (stack.data[i].name === name) {
                stack.currentIndex = i;
                break;
            }
        }
    }
    /***********************************************************************
                          通信连接  /pages/CommLink
    ***********************************************************************/
    NetworkConn{
        property string name: "网络连接"
        width: stack.width
        height: stack.height
    }
//    BaseControlPage {
//        property string name: "串口连接"
//        width: stack.width
//        height: stack.height

//    }
//    BaseOtherControlPage {
//        property string name: "网络连接"
//        width: stack.width
//        height: stack.height
//    }
//    HintPage{
//        property string name: "提示"
//        width: stack.width
//        height: stack.height
//    }

    /***********************************************************************
                          装置列表  /pages/DeviceList
    ***********************************************************************/
    DevicerList_GasMonitor{
         property string name: "气体监测"
         width: stack.width
         height: stack.height
    }
//    DeviceList_TowerIncline{
//        property string name: "杆塔倾斜"
//        width: stack.width
//        height: stack.height
//    }
//    DeviceList_WindYaw{
//        property string name: "微风振动"
//        width: stack.width
//        height: stack.height
//    }
//    DeviceList_WireSag{
//        property string name: "导线弧垂"
//        width: stack.width
//        height: stack.height
//    }
//    DeviceList_WireTemp{
//        property string name: "导线温度"
//        width: stack.width
//        height: stack.height
//    }
//    DevicerList_FrostySensor{
//        property string name: "覆冰"
//        width: stack.width
//        height: stack.height

//    }
//    DevicerList_BreezeScope{
//        property string name: "风偏"
//        width: stack.width
//        height: stack.height
//    }
//    DeviceList_Dance{
//        property string name: "舞动"
//        width: stack.width
//        height: stack.height

//    }
    DeviceList_Image{
        property string name: "图像"
        width: stack.width
        height: stack.height
    }
   /***********************************************************************
                    参数设置查询   /pages/ParaSettingQuery/
   ***********************************************************************/
   MainControlPara {
       property string name: "主控参数"
       width: stack.width
       height: stack.height
   }
   BGNetworkPara {
       property string name: "后台网络参数"
       width: stack.width
       height: stack.height
   }

   /**********************************************************************/
 }
