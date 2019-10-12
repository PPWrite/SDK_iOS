
/*********************************************************/
/*********************************************************/
/*----------------------SDK 4.2.4------------------------*/
/*********************************************************/
/*********************************************************/

#ifndef RobotPenHeader_h
#define RobotPenHeader_h

#ifdef DEBUG
#define RobotBLELog(fmt, ...) NSLog((@"RobotBLE Log :   %s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define RobotBLELog(...)
#endif

#import <UIKit/UIKit.h>

/** 蓝牙系统提示框*/
#define ShowBLEAlert NO

/*!
 @enum
 @abstract 设备类型
 */
typedef enum {
    UnKnown = 0,
    P7  = 1,
    T7 = 2,
    T7P = 3,
    P1 = 4,
    T7P_New  =5,
    T8A = 6,
    T7_XY = 7,
    J0_A5 = 8,
    Gateway = 9,
    Dongle = 10,
    J0_A4 = 11,
    T9A = 12,
    X8_A5 = 13,
    T7PL = 14,
    T7E_TS = 15,
    T7_TS = 16,
    T7_LW = 17,
    T9_J0 = 18,
    J0_A4_P = 19,
    T9E = 20,
    J0_T9 = 21,
    T7_CY =22,
    D1_CY = 23,
    C7 = 24,
    W7 = 25,
    S7_JD = 26,
    DM6 = 27,
    T7A = 28,
    T7_HI = 29,
    T8B = 30,
    T9B_YD = 31,
    T7B_HF = 32,
    X8E_A5 = 33,
    T9W = 34,
    T8C = 35,
    S7_SD = 36,
    T7E = 37,
    T7E_HFHH = 38,
    S7_JD_M3 = 39,
    P1_CX_M3 = 40,
    T9A_EN = 41,
    T9W_A = 42,
    T9B_YD2 = 43,
    S1_DE = 44,
    J7E = 45,
    J7B_HF = 46,
    J7B_ZY = 47,
    T8S = 48,
    J7B = 49,
    T9W_QX = 50,
    K7_DE = 51,
    K8_ZM = 52,
    K7_C5 = 53,
    T7C_BN = 54,
    T9W_YJ = 55,
    T7PL_CL = 56,
    T9W_WX = 57,
    T8B_DH2 = 58,
    T9W_B_KZ = 59,
    C5 = 60,
    T9B = 61,
    T9B_ZXB = 62,
    T8B_D2 = 63,
    T9W_A_TY = 64,
    T9W_A_XF = 65,
    W9_XF = 66,
    S7_TY_A = 67,
    S7_TY_B = 68,
    T7C = 69,
    T9W_TAL = 70,
    X9 = 71,
    T7A_QX = 72,
    X9_TAL = 73,
    T9W_H = 74,
    T10 = 75,
    T7PL_XDF = 76,
    K8_HF = 77,
    K8 = 78,
    J7B_XY = 79,
    T9C = 80,
    T9C_FB = 81,
    T9W_H_TAL = 82,
    K7W = 83,
    X10 = 84,
    T9W_Y = 85,
    T9W_ZHL = 86,
    T8S_LQ = 87,
    
    A4 = 998,//A4占位
    A5 = 999,//A5占位
} DeviceType;

/*!
 @enum
 @abstract 连接状态
 */
typedef enum {
      /************************************设备基础状态******************************/
      /**未知错误*/
      DEVICE_UNKNOW = 0 ,
      /**正在连接*/
      DEVICE_CONNECTING,
      /**连接成功*/
      DEVICE_CONNECTE_SUCCESS,
      /**连接错误*/
      DEVICE_CONNECT_FAIL,
      /**已断开*/
      DEVICE_DISCONNECTED,
      /**服务准备完成*/
      DEVICE_SERVICES_READY = 5,
      /**笔初始化完成*/
      DEVICE_INIT_COMPLETE,
      /**设备信息获取完成*/
      DEVICE_INFO_END,
      /**检查设备更新*/
      DEVICE_UPDATE,
      /**检查设备更新失败*/
      DEVICE_UPDATE_FAIL,
      /************************************设备更新状态******************************/
      /**设备可更新*/
      DEVICE_UPDATE_CAN = 10,
      /**设备不可更新*/
      DEVICE_UPDATE_CANT,
      /**支持频率校准*/
      DEVICE_CALIBRATION_SUPPORT,
      /**不支持频率校准*/
      DEVICE_CALIBRATION_NONSUPPORT,
      /**支持模组升级*/
      DEVICE_SENSOR_SUPPORT,
      /**不支持模组升级*/
      DEVICE_SENSOR_NONSUPPORT = 15,
      /**模组必须更新,否则无法使用*/
      DEVICE_SENSOR_UPDATE_MUST,
      /**模组不用强制更新*/
      DEVICE_SENSOR_UPDATE_MUSTNOT,
      /**模组可更新*/
      DEVICE_SENSOR_UPDATE_CAN,
      /**模组不可更新*/
      DEVICE_SENSOR_UPDATE_CANT,
      /************************************异常状态******************************/
      /**设备已连接（已经存在连接设备）*/
      /**连接设备时候用,防止重复连接*/
      DEVICE_ERROR_CONNECTED = 20,
      /**未找到设备*/
      DEVICE_ERROR_OFFS,
      /**系统状态异常*/
      DEVICE_ERRORE_SYSTEM,
      /**未遵守协议*/
      DEVICE_ERROR_DELEGATE,
      /************************************点数据结构状态******************************/
      /**点数据改变为2点结构*/
      DEVICE_POINT_STRUCT_UPDATE_TYPE2 = 25,
      /**点数据改变为3点结构*/
      DEVICE_POINT_STRUCT_UPDATE_TYPE3,
      /************************************频率校准状态******************************/
      /**进入频率校准模式*/
      DEVICE_CALIBRATION_REDAY = 30,
      /**进入频率校准超时*/
      DEVICE_CALIBRATION_OUTTIME,
      /**频率校准成功*/
      DEVICE_CALIBRATION_SUCCESS,
      /**频率校准失败*/
      DEVICE_CALIBRATION_FAIL,
      /**退出频率校准模式*/
      DEVICE_CALIBRATION_QUIT,
      /************************************修改设备名状态******************************/
      /**设备名字修改成功*/
      DEVICE_NAME_UPDATED = 35,
      /**设备名字更新*/
      DEVICE_NAME_UPDATE,
      /************************************获取休眠状态******************************/
      /**获取、设置设备休眠时间成功（T9B、T8C系列）*/
      DEVICE_DORMANTTIME_SUCCESS = 37,
      /************************************获取设备尺寸状态******************************/
      /**获取、设置设备尺寸成功（T8C系列）*/
      DEVICE_SIZE_SUCCESS = 38,
      /**获取设备存储空间成功*/
      DEVICE_SIZE_SECTION_SUCCESS = 39,
      /************************************设置同步密码状态******************************/
      /**设置同步密码成功*/
      DEVICE_SET_PASSWORD_SUCCESS = 40,
      /**设置原同步密码错误*/
      DEVICE_SET_OLDPASSWORD_ERROR,
      /**设置新同步密码错误*/
      DEVICE_SET_NEWPASSWORD_ERROR,
      /************************************上报轨迹状态******************************/
      /**开启上报轨迹数据成功*/
      DEVICE_SET_REPORTRE_OPEN_SUCCESS = 50,
      /**开启上报轨迹数据失败*/
      DEVICE_SET_REPORTRE_OPEN_FAIL,
      /**关闭上报轨迹数据成功*/
      DEVICE_SET_REPORTRE_CLOSE_SUCCESS,
      /**关闭上报轨迹数据失败*/
      DEVICE_SET_REPORTRE_CLOSE_FAIL,
      /************************************数据擦除状态******************************/
      /**只擦除数据*/
      DEVICE_CLEANDATA_ONLY_SUCCESS = 60,
      /**擦除数据并清空离线笔记*/
      DEVICE_CLEANDATA_DELETE_SUCCESS,
      /**擦除数据并新建离线笔记*/
      DEVICE_CLEANDATA_BUILD_SUCCESS,
      /**无擦除权限*/
      DEVICE_CLEANDATA_NOTAUTHORIZED,
      /************************************删除全部离线笔记状态******************************/
      /**删除成功*/
      DEVICE_NOTE_DELETE_SUCCESS = 65,
      /**设备模式错误*/
      DEVICE_NOTE_DELETE_ERROR_STATE,
      /**设备类型错误*/
      DEVICE_NOTE_DELETE_ERROR_DEVICE,
      /************************************鼠标设备模式******************************/
      /**鼠标模式获取成功*/
      DEVICE_MOUSE_MODEL_GET_SUCCESS,
      /**鼠标模式改变成功*/
      DEVICE_MOUSE_MODEL_CHANGE_SUCCESS,
      
}DeviceState;

/*!
 @enum
 @abstract 坐标点的状态
 */
typedef enum {
      /** 黑笔悬浮状态 **/
      RobotPenPointFloat = 0,
      /** 黑笔touchBegin状态 **/
      RobotPenPointTouchBegin,
      /** 黑笔touchMove状态 **/
      RobotPenPointTouchMove,
      /** 黑笔touchEnd状态 **/
      RobotPenPointTouchEnd,
      /** 离开感应范围 **/
      RobotPenPointLeave,
      /** 红笔touchBegin状态**/
      RobotPenPointAssistTouchBegin = 5,
      /** 红笔touchMove状态**/
      RobotPenPointAssistTouchMove,
      /** 红笔touchEnd状态**/
      RobotPenPointAssistTouchEnd,
      /** 红笔悬浮状态 **/
      RobotPenPointAssistFloat,
      
      /** 橡皮擦touchBegin状态**/
      RobotPenPointRubberBegin = 9,
      /** 橡皮擦touchMove状态**/
      RobotPenPointRubberMove,
      /** 橡皮擦touchEnd状态**/
      RobotPenPointRubberEnd,
      /** 橡皮擦悬浮状态 **/
      RobotPenPointRubberFloat
      
}RobotPenPointTouchStatus;

/*!
 @enum
 @abstract 同步笔记状态
 */
typedef enum {
      /** 同步错误*/
      SYNC_ERROR,
      /** 有未同步笔记*/
      SYNC_NOTE,
      /** 没有未同步笔记*/
      SYNC_NO_NOTE,
      /** 单个笔记同步成功*/
      SYNC_SUCCESS,
      /** 开始同步*/
      SYNC_START,
      /** 停止同步*/
      SYNC_STOP = 5,
      /** 全部笔记同步完成*/
      SYNC_COMPLETE,
      /** 笔记同步密码校验成功*/
      SYNC_PASSWORD_SUCCESS,
      /** 笔记同步密码校验失败*/
      SYNC_PASSWORD_FAIL,
      /** 笔记同步密码尚未启用*/
      SYNC_PASSWORD_NULL,
      
}SYNCState;

/*!
 @enum
 @abstract 点击事件状态
 */
typedef enum{
      /** 单击*/
      DeviceEvent_CLick = 0,
      /** 双击*/
      DeviceEvent_Double_CLick ,
      /** 向前*/
      DeviceEvent_Front ,
      /** 向后*/
      DeviceEvent_Next ,
      /** 电源键双击*/
      DeviceEvent_NewPage,
      /** A*/
      DeviceEvent_A = 5,
      /** B*/
      DeviceEvent_B ,
      /** C*/
      DeviceEvent_C ,
      /** D*/
      DeviceEvent_D ,
      /** E/UP*/
      DeviceEvent_E ,
      /** F/DOWN*/
      DeviceEvent_F = 10 ,
      /** 正确*/
      DeviceEvent_TRUE ,
      /** 错误*/
      DeviceEvent_WRONG ,
      /** 取消*/
      DeviceEvent_CANCEL,
      /** 确定*/
      DeviceEvent_ENSURE,
      
      /**J7B-HF事件*/
      /**上翻页单击*/
      DeviceEvent_FRONT_Single = 15,
      /**上翻页双击*/
      DeviceEvent_FRONT_Double,
      /**上翻页长按*/
      DeviceEvent_FRONT_Long,
      /**下翻页单击*/
      DeviceEvent_NEXT_Single,
      /**下翻页双击*/
      DeviceEvent_NEXT_Double,
      /**下翻页长按*/
      DeviceEvent_NEXT_Long = 20,
      /**自定义按键1单击*/
      DeviceEvent_SELF1_Single,
      /**自定义按键1双击*/
      DeviceEvent_SELF1_Double,
      /**自定义按键1长按*/
      DeviceEvent_SELF1_Long,
      /**自定义按键2单击*/
      DeviceEvent_SELF2_Single,
      /**自定义按键2双击*/
      DeviceEvent_SELF2_Double = 25,
      /**自定义按键2长按*/
      DeviceEvent_SELF2_Long,
}DeviceEventType;

/*!
 @enum
 @abstract 系统状态
 */
typedef enum{
      /** 未知设备*/
      OSDeviceState_BLE_Unknown = 0,
      /** 蓝牙已重启*/
      OSDeviceState_BLE_Resetting,
      /** 蓝牙不支持*/
      OSDeviceState_BLE_Unsupported,
      /** 蓝牙未授权*/
      OSDeviceState_BLE_Unauthorized,
      /** 蓝牙已关闭*/
      OSDeviceState_BLE_PoweredOff,
      /** 蓝牙已打开*/
      OSDeviceState_BLE_PoweredOn,
      //MAC方法
      /** USB打开成功*/
      OSDeviceState_USB_SUCCESS  = 6,
      /** USB打开失败*/
      OSDeviceState_USB_Error,
      
}OSDeviceStateType;

/*!
 @enum
 @abstract OTA状态
 */
typedef enum {
      /** OTA升级错误*/
      OTA_ERROR,
      /** OTA升级*/
      OTA_UPDATE,
      /** OTA成功*/
      OTA_SUCCESS,
      /** 复位*/
      OTA_RESET,
      /** 单个升级成功*/
      OTA_ONE_SUCCESS,
      /** 低电不能升级*/
      OTA_STATUS_ERROR,
      /** 版本错误*/
      OTA_VERSION_ERROR,
      
}OTAState;

/*!
 @enum
 @abstract SENSOR状态
 */
typedef enum {
      /** 模组升级错误*/
      SENSOR_ERROR,
      /** 进入模组升级模式*/
      SENSOR_REDAY,
      /** 模组正在升级*/
      SENSOR_UPDATE,
      /** 模组升级成功*/
      SENSOR_SUCCESS,
      /** 模组升级失败*/
      SENSOR_FAIL,
      
}SensorState;

/*!
 @enum
 @abstract 线程设置
 */
typedef enum{
      /** 默认主线程*/
      BLEQueueType_Main = 0,
      /** 全局高优先级队列*/
      BLEQueueType_High,
      /** 全局中优先级队列*/
      BLEQueueType_Default,
      /** 全局低优先级队列*/
      BLEQueueType_Low,
      /** 全局后台队列*/
      BLEQueueType_Background,
      /** 自定义队列*/
      BLEQueueType_User,
      
}BLEQueueType;
/*!
 @enum
 @abstract 电磁板电量状态
 */
typedef enum {
      /** 0  */
      Battery_0,
      /** 10 */
      Battery_10,
      /** 20*/
      Battery_20,
      /** 50*/
      Battery_50,
      /** 75*/
      Battery_75,
      /** 85*/
      Battery_85,
      /** 100*/
      Battery_100,
      /** 充电中*/
      Battery_Charge,
      /**充电完成*/
      Battery_Charged,
      
}PercentageBattery;

/*!
 @enum
 @abstract 坐标原点方向
 */
typedef enum {
      /** 设备默认坐标系点**/
      RobotPenCoordinateDefault = 0,
      /** 左上角为坐标原点 **/
      RobotPenCoordinateUpperLeft,
      /** 左下角为坐标原点 **/
      RobotPenCoordinateLowerLeft,
      /** 右上角为坐标原点 **/
      RobotPenCoordinateUpperRight,
      /** 右下角为坐标原点 **/
      RobotPenCoordinateLowerRight,
      
}RobotPenCoordinateSystem;

/*!
 @enum
 @abstract 数据点范围尺寸
 */
typedef enum {
      /** 设备原始尺寸 **/
      RobotPaperSizeType_Original = 0,
      /** 标准A4尺寸 **/
      RobotPaperSizeType_A4,
      /** 标准A5尺寸 **/
      RobotPaperSizeType_A5,
      
}RobotPaperSizeType;

/*!
 @enum
 @abstract 清除电磁板离线数据类型
 */
typedef enum {
      /** 只擦除数据 **/
      CleanDataOnly = 0,
      /** 擦除数据并清空离线笔记 **/
      CleanDataAndCleanNote,
      /** 擦除数据并新建离线笔记 **/
      CleanDataAndBuildNote,
      
}CleanDataType;

/*!
 @enum
 @abstract 点结构类型
 */
typedef enum {
      /** 2点结构 **/
      PointStructType2 = 0,
      /** 3点结构 **/
      PointStructType3,
}PointStructType;


/*!
 @enum
 @abstract SDK类型
 @discussion MAC方法
 */
typedef enum {
      /** 蓝牙模式 **/
      BLEModel = 0,
      /** USB模式 **/
      USBModel,
      
}RobotPenMACSDKModel;

/*!
 @enum
 @abstract 电磁板模式
 @discussion MAC方法
 */
typedef enum {
      /** 蓝牙模式 **/
      Device_BLEModel = 0,
      /** 2.4G模式 **/
      Device_24GModel,
      /** USB模式 **/
      Device_USBModel,
      
}RobotPenDeviceModel;

/*!
 @enum
 @abstract SDK类型
 @discussion MAC方法
 */
typedef enum {
      /** 鼠标模式 **/
      MouseModel = 0,
      /** 书写模式 **/
      HandModel,
      
}RobotPenMouseDeviceModel;

#endif /* RobotPenHeader_h */



