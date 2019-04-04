//
//  RobotPenPoint.h
//  RobotPenManagerMacSDKDemo
//
//  Created by JMS on 2017/8/17.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RobotPenHeader.h"

@interface RobotPenPoint : NSObject
/*!
 @property
 @brief 坐标点 X
 */
@property (assign , nonatomic) short originalX;
/*!
 @property
 @brief 坐标点 Y
 */
@property (assign , nonatomic) short originalY;
/*!
 @property
 @brief 压感值
 */
@property (assign , nonatomic) short pressure;
/*!
 @property
 @brief 笔迹设备类型
 */
@property (assign , nonatomic) DeviceType deviceType;
/*!
 @property
 @brief 笔迹点的状态
 */
@property (assign , nonatomic) RobotPenPointTouchStatus touchState;

/*!
 @property
 @brief 点尺寸的类型
 */
@property (assign, nonatomic) RobotPaperSizeType pointSizeType;

/*!
 @method
 @abstract 获取显示场景点坐标(以原始点为基础)
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
 @abstract 获取场景转换点坐标(以原始点为基础)
 @param isHorizontal NO:电磁板左上角为(0,0)点,YES:电磁板左下角为(0,0)点
 @result 返回结果
 */
- (CGPoint)getChangePointWithIsHorizontal:(BOOL)isHorizontal;

/*!
 @method
 @abstract 获取设备转换点坐标(以原始点为基础)
 @param type 坐标系原点位置
 @result 返回结果
 */
- (CGPoint)getTransformsPointWithType:(RobotPenCoordinateSystem)type;

/**
 @method
 @abstract 获取标准纸张缩放点(以原始点为基础)
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
