//
//  RobotPenUtilPoint.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RobotPenHeader.h"
@interface RobotPenUtilPoint : NSObject
/** 优化后的坐标点 X*/
@property (nonatomic,assign) float optimizeX;
/** 优化后的坐标点 Y*/
@property (nonatomic,assign) float optimizeY;
/** 优化后的笔迹宽度*/
@property (nonatomic,assign) float width;
/** 笔迹类型*/
@property (nonatomic, assign) DeviceType deviceType;
/** 点的速度*/
@property (nonatomic,assign) float speed;
/** 状态 0：离开状态 1：touchBegin状态 2：touchMove状态 3：touchEnd状态 4:离开感应范围 */
@property (nonatomic, assign) int touchState;

/**
    获取优化点坐标
 
 */
- (CGPoint)getOptimizePoint;


/**
 获取显示场景点坐标
 
 @param sceneWidth 场景宽
 @param sceneHeight 场景高
 @param isHorizontal 场景是否竖屏
 @return 屏幕点
 */
- (CGPoint)getScenePointWith :(float)sceneWidth :(float)sceneHeight :(BOOL)isHorizontal;
@end
