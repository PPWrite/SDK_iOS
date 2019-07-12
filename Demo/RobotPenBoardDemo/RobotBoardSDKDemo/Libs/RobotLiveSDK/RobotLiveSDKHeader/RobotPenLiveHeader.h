//
//  RobotPenLiveHeader.h
//  PPWrite
//
//  Created by JMS on 2017/11/13.
//  Copyright © 2017年 Robot. All rights reserved.
//

#ifdef DEBUG

#define RobotLiveLog(fmt, ...) NSLog((@"RobotLive Log :   %s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);

#else

#define RobotLiveLog(...)

#endif

/*!
 @enum 直播间消息
 @abstract 直播间消息
 */
typedef enum {
    
    /** 主播进入房间*/
    LiveStudioMessage_People_Anchor_Enter ,
    /** 观众进入房间*/
    LiveStudioMessage_People_Audience_Enter,
    /** 观众离开房间*/
    LiveStudioMessage_People_Audience_Leave,
    
    /** 授予说话权限*/
    LiveStudioMessage_People_Audience_Speak_Award ,
    /** 授予写入权限*/
    LiveStudioMessage_People_Audience_Write_Award ,
    /** 踢人*/
    LiveStudioMessage_People_Audience_Leave_Award ,
    
    /** 请求说话权限*/
    LiveStudioMessage_People_Audience_Speak_Ask ,
    /** 请求写入权限*/
    LiveStudioMessage_People_Audience_Write_Ask ,
    
    
    /** 直播耗时*/
    LiveStudioMessage_Studio_Time ,
    /** 直播间人数*/
    LiveStudioMessage_Studio_Number ,
    
    /** 房主延迟*/
    LiveStudioMessage_People_Anchor_Delay ,
    /** 观众延迟*/
    LiveStudioMessage_People_Audience_Delay ,
    
}LiveStudioMessageType;


/*!
 @enum 直播间数据消息
 @abstract 直播间数据消息
 */
typedef enum {
    
    /** 同步笔迹数据*/
    LiveDataMessage_Tralis_Syns ,
    /** 同步图片数据*/
    LiveDataMessage_Image_Syns ,
    /** 同步翻页*/
    LiveDataMessage_Page_Turn ,
    /** 同步删除页码*/
    LiveDataMessage_Page_Delete ,
    
    /** 同步清除图片*/
    LiveDataMessage_Image_Delete ,
    /** 同步清除笔迹*/
    LiveDataMessage_Tralis_Delete ,
    /** 同步清除笔迹和图片*/
    LiveDataMessage_All_Delete ,
    
    /** 同步区块成功*/
    LiveDataMessage_Block_Syns_Success ,
    /** 同步区块失败*/
    LiveDataMessage_Block_Syns_Fail ,
    
}LiveDataMessageType;
/*!
 @enum 直播信号强度
 @abstract 直播间信号强度
 */
typedef enum {
    /** 位置网络*/
    Live_Quality_Unknown ,
    /** 信号极好*/
    Live_Quality_Excellent ,
    /** 信号较好*/
    Live_Quality_Good ,
    /** 信号较差*/
    Live_Quality_Poor ,
    /** 信号很差*/
    Live_Quality_Bad ,
    /** 信号极差*/
    Live_Quality_VBad ,
    /** 无信号*/
    Live_Quality_Down
    
}LiveNetQuality;

/*!
 @enum 直播白板状态
 @abstract 直播白板状态
 */
typedef enum {
    /** 直播白板启动成功*/
    WBLiveState_WB_Start_Success ,
    /** 直播白板启动失败*/
    WBLiveState_WB_Start_Fail,
    /** 语音服务启动成功*/
    WBLiveState_Vocie_Start_Success ,
    /** 语音服务启动失败*/
    WBLiveState_Vocie_Start_Fail,
    /** 直播白板关闭成功*/
    WBLiveState_WB_End_Success ,
    /** 直播白板关闭失败*/
    WBLiveState_WB_End_Fail,
    /** 语音服务关闭成功*/
    WBLiveState_Vocie_End_Success ,
    /** 语音服务关闭失败*/
    WBLiveState_Vocie_End_Fail,
    
}WBLiveStateType;

