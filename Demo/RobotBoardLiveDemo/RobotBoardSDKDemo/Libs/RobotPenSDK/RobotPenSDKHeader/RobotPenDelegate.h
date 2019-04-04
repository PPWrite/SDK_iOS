//
//  RobotPenBLEDeviceDelegate.h
//  RobotPenManagerMacSDKDemo
//
//  Created by JMS on 2017/8/17.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
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
- (void)getDeviceState:(DeviceState)State DEPRECATED_MSG_ATTRIBUTE("Please use -(void)getDeviceState:(DeviceState)State DeviceUUID:(NSString *)uuid");

/*!
 @method
 @abstract 监听电磁板设备状态
 @param State 状态
 @param uuid uuid
 */
- (void)getDeviceState:(DeviceState)State DeviceUUID:(NSString *)uuid;

/*!
 @method
 @abstract 设备电磁板点击事件
 @param Type 事件类型
 */
- (void)getDeviceEvent:(DeviceEventType)Type;

/*!
 @method
 @abstract 监听系统状态
 @param State 状态
 */
- (void)getOSDeviceState:(OSDeviceStateType)State;

/*!
 @method 监听已连接设备RSSI
 @abstract 监听已连接设备RSSI,需打开RSSI开关。
 @param RSSI RSSI
 */
- (void)getDeviceRSSI:(NSNumber *)RSSI;

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
 @method 监听笔记数量和电量信息(以后会弃用，请及时更新)
 @abstract  监听笔记数量和电量信息
 @param num 数量
 @param battery 电量
 */
- (void)getStorageNum:(int)num andBattery:(int)battery DEPRECATED_MSG_ATTRIBUTE("Please use - (void)getStorageNum:(int)num andBattery:(int)battery andNotePercent:(int)percent");

/*!
 @method 监听笔记数量和电量信息
 @abstract  监听笔记数量和电量信息
 @param num 数量
 @param battery 电量
 @param percent 存储条数百分比
 */
- (void)getStorageNum:(int)num andBattery:(int)battery andNotePercent:(int)percent;

/*!
 @method
 @abstract  获取离线笔记的原始笔迹数据（需要验证）
 @param data 笔迹数据
 */
- (void)getSyncOriginalData:(NSData *)data;

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

#pragma mark OEM系列
/*!
 @method
 @abstract 获取设备笔记和页码编号
 @discussion T9系列专用
 @param page 页码编号
 @param NoteId 笔记编号
 */
- (void)getDevicePage:(int)page andNoteId:(int)NoteId;

/*!
 @method
 @abstract 获取设备笔记页码合并编号
 @discussion T9系列专用
 @param NotePage 笔记页码编号
 */
- (void)getDevicePageNoteIdNumber:(int)NotePage;
/*!
 @method
 @abstract 获取同步离线笔记信息和页码信息
 @discussion T9系列专用
 @param note 笔记信息
 @param page 页码信息
 */
- (void)getTASyncNote:(RobotNote *)note andPage:(int)page;

/*!
 @method
 @abstract 获取设备休眠时间
 @discussion T9B/T8C系列专用
 @param time 设备休眠时间 0-65535min
 */
- (void)getDeviceDormantTime:(int)time;

/*!
 @method
 @abstract 获取设备尺寸
 @discussion T8C系列专用
 @param size 设备尺寸
 */
- (void)getDeviceSize:(CGSize)size;

/*!
 @method
 @abstract 获取设备存储扇区
 @discussion T9A_EN系列专用
 @param total 总扇区 单位：byte
 @param free 剩余扇区 单位：byte
 */
- (void)getDeviceSectionTotal:(int)total Free:(int)free;

#pragma mark 其他


@end


