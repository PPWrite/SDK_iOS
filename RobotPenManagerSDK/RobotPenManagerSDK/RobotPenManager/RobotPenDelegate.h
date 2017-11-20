//
//  RobotPenBLEDeviceDelegate.h
//  RobotPenManagerMacSDKDemo
//
//  Created by JMS on 2017/8/17.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RobotPenHeader.h"
#import "RobotNote.h"
#import "RobotTrails.h"
#import "RobotPenDevice.h"
#import "RobotPenPoint.h"
#import "RobotPenUtilPoint.h"

/*!
 @protocol
 @abstract 代理
 @discussion RobotPenManager 代理
 */
@protocol RobotPenDelegate <NSObject>

@optional

#pragma mark 设备监听
/*!
 @method
 @abstract 发现电磁板设备
 @param device 设备
 */
- (void)getBufferDevice:(RobotPenDevice *)device;

/*!
 @method
 @abstract 监听电磁板设备状态
 @param State 状态
 */
- (void)getDeviceState:(DeviceState)State;

/*!
 @method
 @abstract 设备电磁板点击事件
 @param Type 事件类型
 */
- (void)getDeviceEvent:(DeviceEventType)Type;

/*!
 @method
 @abstract 监听系统蓝牙状态
 @param State 状态
 */
- (void)getOSDeviceState:(OSDeviceStateType)State;

#pragma mark 数据监听

/*!
 @method
 @abstract 获取原始点数据
 @param point 原始点
 */
- (void)getPointInfo:(RobotPenPoint *)point;

/*!
 @method
 @abstract 获取优化点数据
 @param point 优化点
 */
- (void)getOptimizesPointInfo:(RobotPenUtilPoint *)point;


#pragma mark 离线笔记监听

/*!
 @method
 @abstract 同步离线笔记状态
 @param state 状态
 */
- (void)SyncState:(SYNCState)state;

/*!
 @method
 @abstract 获取同步笔记的笔记信息
 @param note 笔记
 */
- (void)getSyncNote:(RobotNote *)note;

/*!
 @method
 @abstract  获取离线笔记的笔迹数据
 @param trails 笔迹模型
 */
- (void)getSyncData:(RobotTrails *)trails;

/*!
 @method
 @abstract 离线笔记数据同步进度
 @param length 总大小
 @param curlength 已同步大小
 @param progess 进度
 */
- (void)getSyncDataLength:(int )length andCurDataLength:(int)curlength andProgress:(float)progess;

/*!
 @method
 @abstract  监听笔记数量和电量信息
 @param num 数量
 @param battery 电量
 */
- (void)getStorageNum:(int)num andBattery:(int)battery;

#pragma mark OTA监听

/*!
 @method
 @abstract OTA升级state
 @param state 状态
 */
- (void)OTAUpdateState:(OTAState)state;

/*!
 @method
 @abstract OTA升级进度
 @param progess 进度
 */
- (void)OTAUpdateProgress:(float)progess;

#pragma mark 模组监听
/*!
 @method
 @abstract SENSOR升级State
 @param state 状态
 */
- (void)SensorUpdateState:(SensorState)state;

/*!
 @method
 @abstract SENSOR升级进度
 @param progess 状态
 */
- (void)SensorUpdateProgress:(float)progess;

#pragma mark 页码检测监听

/*!
 @method
 @abstract 获取设备笔记和页码编号（仅限页码检测设备）
 @param page 页码编号
 @param NoteId 笔记编号
 */
- (void)getDevicePage:(int)page andNoteId:(int)NoteId;

/*!
 @method
 @abstract 获取设备笔记页码合并编号（仅限页码检测设备）
 @param NotePage 笔记页码编号
 */
- (void)getDevicePageNoteIdNumber:(int)NotePage;
/*!
 @method
 @abstract 获取同步离线笔记信息和页码信息（仅限页码检测设备）
 @param note 笔记信息
 @param page 页码信息
 */
- (void)getTASyncNote:(RobotNote *)note andPage:(int)page;

#pragma mark 其他

@end


