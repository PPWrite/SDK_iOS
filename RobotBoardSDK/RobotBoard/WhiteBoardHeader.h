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

#define ThemeColor [UIColor colorWithRed:54/255.0 green:189/255.0 blue:164/255.0 alpha:1] //图片操作边框颜色

//Scale状态
typedef enum {
    CENTER,
    FIT,
}ScaleType;
//画板绘画方式
typedef enum{
    Gesture ,
    PenDraw
} DrawType;
