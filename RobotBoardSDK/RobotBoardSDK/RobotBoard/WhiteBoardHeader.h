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


//Scale状态
typedef enum {
    /** 居中*/
    CENTER,
    /** 填充*/
    FIT,
}ScaleType;
//画板绘画方式
typedef enum{
    /** 手输入*/
    Gesture ,
    /** 笔输入*/
    PenDraw
} DrawType;
