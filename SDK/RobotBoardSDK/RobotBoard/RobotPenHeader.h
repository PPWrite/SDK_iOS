
/*********************************************************/
/*********************************************************/
/*----------------------SDK 3.1.8------------------------*/
/*********************************************************/
/*********************************************************/
#ifdef DEBUG

#define RobotBLELog(fmt, ...) NSLog((@"RobotBLE Log :   %s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);

#else

#define RobotBLELog(...)

#endif

/** 蓝牙系统提示框*/
#define ShowBLEAlert NO

//注意：必看！！！
//此处的宽高为板子横向的宽高。
//即
//WIDTH 表示板子长边的像素值
//HEIGHT 表示板子短边的像素值


//对应设备：T8A/J0_A4/T9A/T9_J0/J0_A4_P/T9E/J0-T9/T8B/T9B-YD 硬件号 6/11/12/18/19/20/21/30/31
/** 标准A4设备纵向 纵向 宽度**/
#define VALUE_A4_WIDTH  22600.0f
/** 标准A4设备纵向 高度**/
#define VALUE_A4_HEIGHT 16650.0f

//对应设备：P7/T7/T7E/T7_TS/T7_LW/T7_CY/C7/S7_JD/T7A/T7_HI 硬件号 1/2/15/16/17/22/24/26/28/29
/** 标准A5设备纵向 纵向 宽度**/
#define VALUE_A5_WIDTH  14335.0f
/** 标准A5设备纵向 高度**/
#define VALUE_A5_HEIGHT 8191.0f

/**USB P1纵向 宽度**/ //4
#define VALUE_P1_WIDTH  17407.0f
/**USB P1纵向 高度**/
#define VALUE_P1_HEIGHT 10751.0f

/**BLE T7 PLUS纵向 宽度**/ //3 5
#define VALUE_T7P_WIDTH  22015.0f
/**BLE T7 PLUS纵向 高度**/
#define VALUE_T7P_HEIGHT  15359.0f

/**BLE T7 好写纵向 宽度**/ // 7
#define VALUE_T7_XY_WIDTH  14300.0f
/**BLE T7 好写纵向 高度**/
#define VALUE_T7_XY_HEIGHT  7950.0f

/**BLE T7 PLUS J0 纵向 宽度**/ //8
#define VALUE_J0_A5_WIDTH  14435.0f
/**BLE T7 PLUS J0 纵向 高度**/
#define VALUE_J0_A5_HEIGHT  8191.0f

/**BLE X8 纵向 宽度**/ //13
#define VALUE_X8_A5_WIDTH  22100.0f
/**BLE X8 纵向 高度**/
#define VALUE_X8_A5_HEIGHT  14650.0f

/**BLE DM6 纵向 宽度**/ //27
#define VALUE_DM6_WIDTH  109.0f
/**BLE DM6 纵向 高度**/
#define VALUE_DM6_HEIGHT  175.0f


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
    
    T7E = 15,
    
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
    
} DeviceType;

/*!
 @enum
 @abstract 连接状态
 */
typedef enum {
    /************************************设备基础状态******************************/
    /**设备已连接（已经存在连接设备）*/
    /**连接设备时候用,防止重复连接*/
    DEVICE_CONNECTED = 0 ,
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
    /************************************频率校准状态******************************/
    /**进入频率校准模式*/
    DEVICE_CALIBRATION_REDAY = 20,
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
    DEVICE_NAME_UPDATED = 30,
    /**设备名字更新*/
    DEVICE_NAME_UPDATE,
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

}DeviceState;

/*!
 @enum
 @abstract 蓝牙状态
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

}OSDeviceStateType;

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
    /** 新建页*/
    DeviceEvent_NewPage,
    /** A*/
    DeviceEvent_A ,
    /** B*/
    DeviceEvent_B ,
    /** C*/
    DeviceEvent_C ,
    /** D*/
    DeviceEvent_D ,
    /** E*/
    DeviceEvent_E ,
    /** F*/
    DeviceEvent_F ,
    /** 正确*/
    DeviceEvent_TRUE ,
    /** 错误*/
    DeviceEvent_WRONG ,
}DeviceEventType;



/*!
 @enum
 @abstract OTA状态
 */
typedef enum {
    /** OTA升级错误*/
    OTA_ERROR,
    /** OTA数据传输*/
    OTA_DATA,
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
    /** 进入模组升级数据*/
    SENSOR_DATA,
    /** 模组正在升级*/
    SENSOR_UPDATE,
    /** 模组升级成功*/
    SENSOR_SUCCESS,
    /** 模组升级失败*/
    SENSOR_FAIL,
    
}SensorState;


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
    SYNC_STOP,
    /** 全部笔记同步完成*/
    SYNC_COMPLETE,
    
}SYNCState;



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
 @abstract 坐标点的状态
 */
typedef enum {
    
    RobotPenPointFloat = 0,     /** 离开(悬浮)状态 **/
    
    RobotPenPointTouchBegin,    /** touchBegin状态 **/
    
    RobotPenPointTouchMove,     /** touchMove状态 **/
    
    RobotPenPointTouchEnd,      /** touchEnd状态 **/
    
    RobotPenPointLeave          /** 离开感应范围 **/
    
}RobotPenPointTouchStatus;


/*!
 @enum
 @abstract 清除电磁板离线数据类型
 */
typedef enum {
    
    CleanDataOnly = 0,     /** 只擦除数据 **/
    
    CleanDataAndCleanNote,    /** 擦除数据并清空离线笔记 **/
    
    CleanDataAndBuildNote,     /** 擦除数据并新建离线笔记 **/
   
    
}CleanDataType;








