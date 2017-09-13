//
//  RobotPenPoint.h
//  RobotPenManagerMacSDKDemo
//
//  Created by JMS on 2017/8/17.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RobotPenHeader.h"
@interface RobotPenPoint : NSObject

/** 坐标点 Y **/
@property (assign , nonatomic) short originalX;

/** 坐标点 Y **/
@property (assign , nonatomic) short originalY;

/** 压感值 **/
@property (assign , nonatomic) short pressure;

/** 笔迹设备类型 **/
@property (assign , nonatomic) DeviceType deviceType;

/** 笔迹点的状态  **/
@property (assign , nonatomic) RobotPenPointTouchStatus touchState;


/**
 获取显示场景点坐标(以原始点为基础)
 
 @param sceneWidth 场景宽
 @param sceneHeight 场景高
 @param isHorizontal 场景是否竖屏
 @return 场景坐标点
 */
- (CGPoint)getScenePointWithSceneWidth:(float)sceneWidth SceneHeight:(float)sceneHeight IsHorizontal:(BOOL)isHorizontal;

/**
 转换点坐标(以原始点为基础)
 
 @param isHorizontal NO:电磁板左上角为(0,0)点,YES:电磁板左下角为(0,0)点
 @return 坐标
 */
- (CGPoint)getChangePointWithIsHorizontal:(BOOL)isHorizontal;


@end
