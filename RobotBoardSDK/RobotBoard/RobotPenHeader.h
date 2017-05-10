
#ifdef DEBUG

#define RobotBLELog(fmt, ...) NSLog((@"RobotBLE Log :   %s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);

#else

#define RobotBLELog(...)

#endif

/**USB P1纵向 宽度**/ //4
#define VALUE_P1_WIDTH  17407.0f
/**USB P1纵向 高度**/
#define VALUE_P1_HEIGHT 10751.0f

/**BLE P7纵向 宽度**/ //1
#define VALUE_P7_WIDTH 14335.0f
/**BLE P7纵向 高度**/
#define VALUE_P7_HEIGHT  8191.0f

/**BLE ELITE纵向 宽度**/ //2
#define VALUE_ELITE_WIDTH  14335.0f
/**BLE ELITE纵向 高度**/
#define VALUE_ELITE_HEIGHT  8191.0f

/**BLE ELITE PLUS纵向 宽度**/ //3 5
#define VALUE_ELITE_PLUS_WIDTH  22015.0f
/**BLE ELITE PLUS纵向 高度**/
#define VALUE_ELITE_PLUS_HEIGHT  15359.0f

/**BLE T8A 纵向 宽度**/ // 6
#define VALUE_T8A_WIDTH  22600.0f
/**BLE T8A 纵向 高度**/
#define VALUE_T8A_HEIGHT  16650.0f

/**BLE ELITE 好写纵向 宽度**/ // 7
#define VALUE_ELITE_XY_WIDTH  14300.0f
/**BLE ELITE 好写纵向 高度**/
#define VALUE_ELITE_XY_HEIGHT  7950.0f

/**BLE ELITE PLUS J0 纵向 宽度**/ //8
#define VALUE_J0_A5_WIDTH  14435.0f
/**BLE ELITE PLUS J0 纵向 高度**/
#define VALUE_J0_A5_HEIGHT  8191.0f

/**BLE J0_A4 纵向 宽度**/ //11
#define VALUE_J0_A4_WIDTH  22015.0f
/**BLE J0_A4 纵向 高度**/
#define VALUE_J0_A4_HEIGHT  15359.0f


/**BLE T9A 纵向 宽度**/ //12
#define VALUE_T9A_WIDTH  22600.0f
/**BLE T9A 纵向 高度**/
#define VALUE_T9A_HEIGHT  16650.0f

/**BLE X8 纵向 宽度**/ //13
#define VALUE_X8_WIDTH  14335.0f
/**BLE X8 纵向 高度**/
#define VALUE_X8_HEIGHT  8191.0f
//OTA状态
typedef enum {
    OTA_ERROR,
    OTA_DATA,
    OTA_UPDATE,
    OTA_SUCCESS,
    OTA_RESET,
    OTA_ONE_SUCCESS,//一个升级成功
    
}OTAState;



//同步笔记状态
typedef enum {
    SYNC_ERROR,
    SYNC_NOTE,
    SYNC_NO_NOTE,
    SYNC_SUCCESS,
    SYNC_START,
    SYNC_STOP,
    SYNC_COMPLETE,
    
}SYNCState;



/**

 板子方向：
 //与Elite_Plus的区别在于顶点坐标在左下角
 Elite
 Elite_XY
 Elite_Plus_New
 J0_A5
 J0_A4
 
 //与Elite_Plus_New的区别在于顶点坐标在右上角
 Elite_Plus
 RobotPen_P7
 T8A
 T9A
 
 
 别名：
 Elite          == T7
 Elite_Plus     == T7P/Elite_Plus_A4
 Elite_Plus_New == T7P/Elite_Plus_A5
 T8A            == NEBULA_Node
 Elite_XY       == T7_XY
 J0_A5          == J0_A5 -> T7
 J0_A4          ==       ->T7P
 T9A            ==       -> T8A
 
 G1             == NEBULA_Gateway ->PC
 D1             == Dongle         ->PC
 
 X8             == Elite
 
 T8A:与T9A尺寸一样 同步笔记：T7P
 T9A:与T8A尺寸一样 同步笔记：T7
 
 J0_A5: 尺寸：T7  同步笔记：T7P
 J0_A4: 尺寸：T7P 同步笔记：T7P
 
 
*/


//设备类型
typedef enum {
    
    UnKnown = 0,
    
    RobotPen_P7  = 1,

    Elite = 2,
    
    Elite_Plus = 3,
    
    RobotPen_P1 = 4,
    
    Elite_Plus_New  =5,
    
    T8A = 6,
   
    Elite_XY = 7,
    
    J0_A5 = 8,

//    NEBULA_Gateway = 9,

//    Dongle = 10,

    J0_A4 = 11,

    T9A = 12,
    
    X8 = 13,
    
    
    
} DeviceType;

//连接状态
typedef enum {
    /**没有找到设备**/
    NOTHING,
    /**正在连接**/
    CONNECTING,
    /**连接成功**/
    CONNECTED,
    /**连接错误**/
    CONNECT_FAIL,
    /**正在断开**/
    DISCONNECTING,
    /**已断开**/
    DISCONNECTED,
    /**开始发现服务**/
    SERVICES_START,
    /**服务准备完成**/
    SERVICES_READY,
    /**发现服务失败**/
    SERVICES_FAIL,
    /**笔准备完成**/
    PEN_READY,
    /**笔初始化完成**/
    PEN_INIT_COMPLETE,
    /**设备信息获取**/
    DEVICE_INFO_END,
    /**检查设备更新**/
    DEVICE_UPDATE,
    /**设备名字修改成功**/
    DEVICE_NAME_UPDATED,
    /**设备名字更新**/
    DEVICE_NAME_UPDATE

    
}DeviceState;


typedef enum{
    DeviceEvent_CLick = 0,
    DeviceEvent_Double_CLick ,
    DeviceEvent_Front ,
    DeviceEvent_Next ,
    DeviceEvent_NewPage
}DeviceEventType;

















