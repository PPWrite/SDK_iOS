//
//  RobotPenUtilPoint.h
//  RobotPenManagerMacSDKDemo
//
//  Created by JMS on 2017/8/17.
//  Copyright © 2017年 JMS. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "RobotPenHeader.h"
#import "RobotPenPoint.h"

@interface RobotPenUtilPoint : NSObject
/*!
 @property
 @brief 优化后的坐标点 X
 */
@property (nonatomic,assign) float optimizeX;
/*!
 @property
 @brief 优化后的坐标点 Y
 */
@property (nonatomic,assign) float optimizeY;
/*!
 @property
 @brief 优化后的笔迹宽度
 */
@property (nonatomic,assign) float width;
/*!
 @property
 @brief 笔迹类型
 */
@property (nonatomic, assign) DeviceType deviceType;
/*!
 @property
 @brief 点的速度
 */
@property (nonatomic,assign) float speed;
/*!
 @property
 @brief 状态 0：离开(悬浮)状态 1：touchBegin状态 2：touchMove状态 3：touchEnd状态 4:离开感应范围
 */
@property (nonatomic, assign) int touchState;

/*!
 @property
 @brief 点尺寸的类型
 */
@property (assign, nonatomic) RobotPaperSizeType pointSizeType;
/*!
 @method
 @abstract 获取优化点坐标
 @result 返回结果
 */
- (CGPoint)getOptimizePoint;

/*!
 @method
 @abstract 根据优化点点获取显示场景点坐标
 @param sceneWidth 场景宽
 @param sceneHeight 场景高
 @param isHorizontal 场景是否横屏
 @result 返回结果
 */
- (CGPoint)getScenePointWithSceneWidth:(float)sceneWidth SceneHeight:(float)sceneHeight IsHorizontal:(BOOL)isHorizontal;

/*!
 @method
 @abstract 获取显示场景点坐标(以原始点为基础)
 @param sceneWidth 场景宽
 @param sceneHeight 场景高
 @param isHorizontal 场景是否横屏
 @param deviceSize 设备识别范围
 @result 返回结果
 */
- (CGPoint)getScenePointWithSceneWidth:(float)sceneWidth SceneHeight:(float)sceneHeight IsHorizontal:(BOOL)isHorizontal DeviceSize:(CGSize)deviceSize;

/*!
 @method
 @abstract 根据屏幕点获取优化点坐标
 @param sceneWidth 场景宽
 @param sceneHeight 场景高
 @param isHorizontal 场景是否横屏
 @result 返回结果
 */
- (CGPoint)getOriginalPointWithSceneWidth:(float)sceneWidth SceneHeight:(float)sceneHeight IsHorizontal:(BOOL)isHorizontal;

/*!
 @method
 @abstract 获取转换点坐标(以原始坐标尺寸为基础)
 @param type 坐标系原点位置
 @result 返回结果
 */
- (CGPoint)getTransformsPointWithType:(RobotPenCoordinateSystem)type;
/**
 @method
 @abstract 获取标准纸张缩放点(以原始坐标尺寸为基础)
 @discussion 以高固定缩放
 @param type 转换类型
 @param coordinateType 坐标系原点位置
 @result 返回结果
 */
- (CGPoint)getScalePointTo:(RobotPaperSizeType)type CoordinateSystemType:(RobotPenCoordinateSystem)coordinateType;
/*!
 @method
 @abstract 转换MAC坐标系的Y坐标
 @discussion MAC方法
 @param isHorizontal NO:电磁板左上角为(0,0)点,YES:电磁板左下角为(0,0)点
 @result 返回结果
 */
- (CGPoint)changeMacPointWithIsHorizontal:(BOOL)isHorizontal;
@end


