//
//  WhiteBoardHeader.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//


#ifdef DEBUG

#define RobotWBLog(fmt, ...) NSLog((@"RobotWB Log :   %s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);

#else

#define RobotWBLog(...)

#endif


/*!
 @enum
 @abstract 白板信息状态
 */
typedef enum {
    /** 笔迹加载成功*/
    WBMessage_Note_Load_SUCCESS = 0,
    /** 笔迹加载失败*/
    WBMessage_Note_Load_FAIL,
    /** 图片加载成功*/
    WBMessage_Image_Load_SUCCESS,
    /** 图片加载失败*/
    WBMessage_Image_Load_FAIL,
    /** 图片截取成功*/
    WBMessage_Image_Cut_SUCCESS,
    /** 图片截取失败*/
    WBMessage_Image_Cut_FAIL = 5,
    /** 图片插入成功*/
    WBMessage_Image_Insert_SUCCESS,
    /** 图片插入失败*/
    WBMessage_Image_Insert_FAIL,
    /** 手绘结束*/
    WBMessage_Draw_Hand_End,
    /** 页码信息*/
    WBMessage_Page_Info,
    /** 页码识别信息*/
    WBMessage_Page_TA_Info = 10,
    
    
}WBMessageType;


/*!
 @enum
 @abstract 录制白板信息状态
 */
typedef enum {
    /** 录课取消成功*/
    WBVideoMessage_Video_Cancel_SUCCESS,
    /** 录课取消失败*/
    WBVideoMessage_Video_Cancel_FAIL,
    /** 录课保存成功*/
    WBVideoMessage_Video_Save_SUCCESS,
    /** 录课保存失败*/
    WBVideoMessage_Video_Save_FAIL,
    
}WBVideoMessageType;
/*!
 @enum
 @abstract 状态
 */
typedef enum {
    /** 居中*/
    ScaleType_Center,
    /** 填充*/
    ScaleType_Fill,
    /** 顶部对齐*/
    ScaleType_Top,
}ScaleType;

/*!
 @enum
 @abstract 画板绘画方式
 */
typedef enum{
    /** 手输入*/
    Gesture ,
    /** 笔输入*/
    PenDraw
} DrawType;

