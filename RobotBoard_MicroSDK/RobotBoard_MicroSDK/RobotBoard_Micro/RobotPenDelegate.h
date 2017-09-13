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

/**
 RobotPenManager 代理
 */
@protocol RobotPenDelegate <NSObject>

@optional

#pragma mark 设备监听
/**
 发现电磁板设备
 
 @param device <#device description#>
 */
- (void)getBufferDevice:(RobotPenDevice *)device;
/**
 监听电磁板设备状态
 
 @param State <#State description#>
 */
- (void)getDeviceState:(DeviceState)State;

/**
 设备电磁板点击事件
 
 @param Type <#Type description#>
 */
- (void)getDeviceEvent:(DeviceEventType)Type;

/**
 监听系统蓝牙状态
 
 @param State <#State description#>
 */
- (void)getOSDeviceState:(OSDeviceStateType)State;

#pragma mark 数据监听

/**
 获取原始点数据
 
 @param point 原始点
 */
- (void)getPointInfo:(RobotPenPoint *)point;

/**
 获取优化点数据
 
 @param point 优化点
 */
- (void)getOptimizesPointInfo:(RobotPenUtilPoint *)point;


#pragma mark 离线笔记监听
/**
 同步离线笔记状态
 
 @param state <#state description#>
 */
- (void)SyncState:(SYNCState)state;


/**
 获取同步笔记的笔记信息
 
 @param note <#note description#>
 */
- (void)getSyncNote:(RobotNote *)note;

/**
 获取离线笔记的笔迹数据
 */
- (void)getSyncData:(RobotTrails *)trails;


/**
 离线笔记数据同步进度
 
 @param length 总大小
 @param curlength 已同步大小
 @param progess 进度
 */
- (void)getSyncDataLength:(int )length andCurDataLength:(int)curlength andProgress:(float)progess;


/**
 监听笔记数量和电量信息
 @param num <#num description#>
 */
- (void)getStorageNum:(int)num andBattery:(int)battery;

#pragma mark OTA监听
/**
 OTA升级state
 
 @param state <#state description#>
 */
- (void)OTAUpdateState:(OTAState)state;

/**
 OTA升级进度
 
 @param progess <#progess description#>
 */
- (void)OTAUpdateProgress:(float)progess;

#pragma mark 模组监听
/**
 SENSOR升级State
 
 @param state <#state description#>
 */
- (void)SensorUpdateState:(SensorState)state;

/**
 SENSOR升级进度
 
 @param progess <#progess description#>
 */
- (void)SensorUpdateProgress:(float)progess;


#pragma mark 页码检测监听

/**
 获取设备当前页（仅限页码检测设备）
 
 @param page 当前页
 */
- (void)getDevicePage:(int)page andNoteKey:(NSString *)NoteKey;

/**
 获取笔迹数据（仅限页码检测设备）
 */
- (void)getTASyncData:(RobotTrails *)trails andBlockKey:(NSString *)BlockKey;

/**
 获取笔记信息和页码信息（仅限页码检测设备）
 
 @param note 笔记信息
 @param page 页码信息
 */
- (void)getTASyncNote:(RobotNote *)note andPage:(int)page;

#pragma mark 其他

@end


