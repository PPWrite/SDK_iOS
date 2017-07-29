
/*********************************************************/
/*********************************************************/
/*----------------------SDK 3.1.0------------------------*/
/*********************************************************/
/*********************************************************/
#ifdef DEBUG

#define RobotBLELog(fmt, ...) NSLog((@"RobotBLE Log :   %s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);

#else

#define RobotBLELog(...)

#endif
//注意：必看！！！
//此处的宽高为板子横向的宽高。
//即
//WIDTH 表示板子长边的像素值
//HEIGHT 表示板子长边的像素值


/**USB P1纵向 宽度**/ //4
#define VALUE_P1_WIDTH  17407.0f
/**USB P1纵向 高度**/
#define VALUE_P1_HEIGHT 10751.0f

/**BLE P7纵向 宽度**/ //1
#define VALUE_P7_WIDTH 14335.0f
/**BLE P7纵向 高度**/
#define VALUE_P7_HEIGHT  8191.0f

/**BLE T7纵向 宽度**/ //2
#define VALUE_T7_WIDTH  14335.0f
/**BLE T7纵向 高度**/
#define VALUE_T7_HEIGHT  8191.0f

/**BLE T7 PLUS纵向 宽度**/ //3 5
#define VALUE_T7P_WIDTH  22015.0f
/**BLE T7 PLUS纵向 高度**/
#define VALUE_T7P_HEIGHT  15359.0f

/**BLE T8A 纵向 宽度**/ // 6
#define VALUE_T8A_WIDTH  22600.0f
/**BLE T8A 纵向 高度**/
#define VALUE_T8A_HEIGHT  16650.0f

/**BLE T7 好写纵向 宽度**/ // 7
#define VALUE_T7_XY_WIDTH  14300.0f
/**BLE T7 好写纵向 高度**/
#define VALUE_T7_XY_HEIGHT  7950.0f

/**BLE T7 PLUS J0 纵向 宽度**/ //8
#define VALUE_J0_A5_WIDTH  14435.0f
/**BLE T7 PLUS J0 纵向 高度**/
#define VALUE_J0_A5_HEIGHT  8191.0f

/**BLE J0_A4 纵向 宽度**/ //11
#define VALUE_J0_A4_WIDTH  22600.0f
/**BLE J0_A4 纵向 高度**/
#define VALUE_J0_A4_HEIGHT  16650.0f


/**BLE T9A 纵向 宽度**/ //12
#define VALUE_T9A_WIDTH  22600.0f
/**BLE T9A 纵向 高度**/
#define VALUE_T9A_HEIGHT  16650.0f

/**BLE X8 纵向 宽度**/ //13
#define VALUE_X8_A5_WIDTH  22100.0f
/**BLE X8 纵向 高度**/
#define VALUE_X8_A5_HEIGHT  14650.0f

//OTA状态
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

//SENSOR状态
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


//同步笔记状态
typedef enum {
    /** 同步错误*/
    SYNC_ERROR,
    /** 有未同步笔记*/
    SYNC_NOTE,
    /** 没有未同步笔记*/
    SYNC_NO_NOTE,
    /** 同步成功（一个）*/
    SYNC_SUCCESS,
    /** 开始同步*/
    SYNC_START,
    /** 停止同步*/
    SYNC_STOP,
    /** 同步完成（全部）*/
    SYNC_COMPLETE,
    
}SYNCState;



/**
 
 板子方向：
 //与T7P的区别在于顶点坐标在左下角
 T7
 T7_XY
 T7P_New
 J0_A5
 X8
 
 
 //与T7P_New的区别在于顶点坐标在右上角
 T7P
 RobotPen_P7
 T8A
 T9A
 J0_A4
 
 别名：
 T7          == T7
 T7P     == T7P/T7P_A4
 T7P_New == T7P/T7P_A5
 T8A            == NEBULA_Node
 T7_XY       == T7_XY
 J0_A5          == J0_A5 -> T7
 J0_A4          ==       ->T7P
 T9A            ==       -> T8A
 
 G1             == NEBULA_Gateway ->PC
 D1             == Dongle         ->PC
 
 X8             == T7
 
 T8A:与T9A尺寸一样 同步笔记：T7P
 T9A:与T8A尺寸一样 同步笔记：T7
 
 J0_A5: 尺寸：T7  同步笔记：T7P
 J0_A4: 尺寸：T7P 同步笔记：T7P
 
 
 */


//设备类型
typedef enum {
    
    UnKnown = 0,
    
    RobotPen_P7  = 1,
    
    T7 = 2,
    
    T7P = 3,
    
    RobotPen_P1 = 4,
    
    T7P_New  =5,
    
    T8A = 6,
    
    T7_XY = 7,
    
    J0_A5 = 8,
    
    //    NEBULA_Gateway = 9,
    
    //    Dongle = 10,
    
    J0_A4 = 11,
    
    T9A = 12,
    
    X8_A5 = 13,
    
    
    
} DeviceType;

//连接状态
typedef enum {
    /**没有找到设备*/
    NOTHING,
    /**正在连接*/
    CONNECTING,
    /**连接成功*/
    CONNECTED,
    /**连接错误*/
    CONNECT_FAIL,
    /**正在断开*/
    DISCONNECTING,
    /**已断开*/
    DISCONNECTED,
    /**开始发现服务*/
    SERVICES_START,
    /**服务准备完成*/
    SERVICES_READY,
    /**发现服务失败*/
    SERVICES_FAIL,
    /**笔准备完成*/
    PEN_READY,
    /**笔初始化完成*/
    PEN_INIT_COMPLETE,
    /**设备信息获取*/
    DEVICE_INFO_END,
    /**检查设备更新*/
    DEVICE_UPDATE,
    /**检查设备更新失败*/
    DEVICE_UPDATE_FAIL,
    /**设备可更新*/
    DEVICE_UPDATE_CAN,
    /**设备不可更新*/
    DEVICE_UPDATE_CANT,
    /**设备名字修改成功*/
    DEVICE_NAME_UPDATED,
    /**设备名字更新*/
    DEVICE_NAME_UPDATE,
    /**支持频率校准*/
    DEVICE_CALIBRATION_SUPPORT,
    /**不支持频率校准*/
    DEVICE_CALIBRATION_NONSUPPORT,
    /**进入频率校准模式*/
    DEVICE_CALIBRATION_REDAY,
    /**进入频率校准超时*/
    DEVICE_CALIBRATION_OUTTIME,
    /**频率校准成功*/
    DEVICE_CALIBRATION_SUCCESS,
    /**频率校准失败*/
    DEVICE_CALIBRATION_FAIL,
    /**退出频率校准模式*/
    DEVICE_CALIBRATION_QUIT,
    /**支持模组升级*/
    DEVICE_SENSOR_SUPPORT,
    /**不支持模组升级*/
    DEVICE_SENSOR_NONSUPPORT,
    /**模组必须更新,否则无法使用*/
    DEVICE_SENSOR_UPDATE_MUST,
    /**模组不用强制更新*/
    DEVICE_SENSOR_UPDATE_MUSTNOT,
    /**模组可更新*/
    DEVICE_SENSOR_UPDATE_CAN,
    /**模组不可更新*/
    DEVICE_SENSOR_UPDATE_CANT,
    
    
    
}DeviceState;


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
    DeviceEvent_NewPage
}DeviceEventType;

















