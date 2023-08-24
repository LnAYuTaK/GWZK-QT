import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.14
import "qrc:/common"
import "qrc:/pages"
import "qrc:/pages/DeviceList"
import "qrc:/pages/ParaSettingQuery"
import "qrc:/pages/CommLink"
import "qrc:/pages/DataAcquisition"
import "qrc:/pages/MasterOperation"
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
    /***********************************************************************
                          装置列表  /pages/DeviceList
    ***********************************************************************/
    DevicerList_GasMonitor{
         property string name: "隧道气体"
         width: stack.width
         height: stack.height
    }
    DeviceList_TunnelFan{
         property string name: "隧道风机"
         width: stack.width
         height: stack.height
    }
    DeviceList_WaterLevel{
        property string name:  "液位装置"
        width: stack.width
        height: stack.height
    }
    DeviceList_WaterPump{
        property string name: "水泵装置"
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
   LocalNetPara {
       property string name: "本地网络"
       width: stack.width
       height: stack.height
   }
   BGNetworkPara {
       property string name: "网络参数"
       width: stack.width
       height: stack.height
   }
   GasParaSetting {
       property string name: "气体参数"
       width: stack.width
       height: stack.height
   }
   EnvPara{
       property string name: "环境参数"
       width: stack.width
       height: stack.height
   }
   MqttPara {
       property string name: "mqtt参数"
       width: stack.width
       height: stack.height
   }
   /**********************************************************************
                设置操作   /pages/OperationSet/
   /**********************************************************************/
   MainConOperation {
       property string name: "主控操作"
       width: stack.width
       height: stack.height
   }
   /**********************************************************************
                数据召测   /pages/DataAcquisition/
   /**********************************************************************/
   GasDataAcquisition {
       property string name: "气体召测"
       width: stack.width
       height: stack.height
   }
 }
