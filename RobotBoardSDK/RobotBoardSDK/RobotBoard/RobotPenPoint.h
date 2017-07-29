//
//  RobotPenPoint.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RobotPenHeader.h"

@interface RobotPenPoint : NSObject
/** 坐标点 X*/
@property (nonatomic,assign) short originalX;
/** 坐标点 Y*/
@property (nonatomic,assign) short originalY;
/** 压感值*/
@property (nonatomic, assign) short pressure;
/** 设备类型*/
@property (nonatomic, assign) DeviceType deviceType;

/** 状态 0：离开(悬浮)状态 1：touchBegin状态 2：touchMove状态 3：touchEnd状态 4:离开感应范围 */
@property (nonatomic, assign) int touchState;

/**
 获取原始点坐标
 
 */
- (CGPoint)getOriginalPoint;

/**
 转换点坐标(以原始点为基础)

 @param isHorizontal NO:电磁板左上角为(0,0)点,YES:电磁板左下角为(0,0)点
 @return <#return value description#>
 */
- (CGPoint)getChangePointWithIsHorizontal:(BOOL)isHorizontal;

/**
 获取显示场景点坐标(以原始点为基础)
 
 @param sceneWidth 场景宽
 @param sceneHeight 场景高
 @param isHorizontal 场景是否竖屏
 @return 场景坐标点
 */
- (CGPoint)getScenePointWithSceneWidth:(float)sceneWidth SceneHeight:(float)sceneHeight IsHorizontal:(BOOL)isHorizontal;


/**
 获取显示场景点坐标(以转换点为基础)
 
 @param sceneWidth 场景宽
 @param sceneHeight 场景高
 @param isHorizontal 场景是否竖屏
 @return 场景坐标点
 */
- (CGPoint)getScenePointWithChangePointSceneWidth:(float)sceneWidth SceneHeight:(float)sceneHeight IsHorizontal:(BOOL)isHorizontal;

/**
 根据缩放比例获取场景点坐标(以原始点为基础)
 
 @param scaling 缩放比例（0 - 1）
 @param distance 最小的点间隔(重复点)
 @param isHorizontal 场景是否竖屏
 @return 返回坐标点（-10000，-10000）表示重复点（需要手动丢掉）
 */
- (CGPoint)getScenePointWithScaling:(float)scaling MinimumDistance:(float)distance IsHorizontal:(BOOL)isHorizontal;

@end
