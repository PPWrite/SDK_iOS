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
 @brief 坐标点 Y
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
 @method
 @abstract 获取显示场景点坐标(以原始点为基础)
 @param sceneWidth 场景宽
 @param sceneHeight 场景高
 @param isHorizontal 场景是否竖屏
 @result 返回结果
 */
- (CGPoint)getScenePointWithSceneWidth:(float)sceneWidth SceneHeight:(float)sceneHeight IsHorizontal:(BOOL)isHorizontal;


/*!
 @method
 @abstract 转换点坐标(以原始点为基础)
 @param isHorizontal NO:电磁板左上角为(0,0)点,YES:电磁板左下角为(0,0)点
 @result 返回结果
 */
- (CGPoint)getChangePointWithIsHorizontal:(BOOL)isHorizontal;

/*!
 @method
 @abstract 获取转换点坐标(以原始点为基础)
 @param type 坐标系原点位置
 @result 返回结果
 */
- (CGPoint)getTransformsPointWithType:(RobotPenCoordinateSystem)type;

/*!
 @method
 @abstract 转换MAC坐标系的Y坐标
 @discussion MAC方法
 @param isHorizontal NO:电磁板左上角为(0,0)点,YES:电磁板左下角为(0,0)点
 @result 返回结果
 */
- (CGPoint)changeMacPointWithIsHorizontal:(BOOL)isHorizontal;
@end
