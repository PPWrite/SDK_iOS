//
//  RobotPenDevice.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RobotPenHeader.h"
#import <CoreBluetooth/CoreBluetooth.h>

@interface RobotPenDevice : NSObject
/** 设备类型*/
@property (nonatomic, assign) DeviceType deviceType;
/** 蓝牙*/
@property (retain, nonatomic) CBPeripheral *peripheral;
/** UUID*/
@property (copy, nonatomic) NSString *uuID;
/** MAC地址*/
@property (copy, nonatomic)  NSString *Mac;
/** 硬件版本*/
@property (nonatomic, copy) NSString *HWStr;
/** 固件版本*/
@property (nonatomic, copy) NSString *SWStr;
/** 模组版本*/
@property (nonatomic, copy) NSString *MWStr;
/** 电池电量 (1-7个等级)
  1 == 0格
  2 == 1格
  3 == 1格
  4 == 2格
  5 == 3格
  6 == 4格
  7 == 4格
 */
@property (nonatomic, assign) int Battery;
/** 信号强度*/
@property (nonatomic, assign) int RSSI;

/** 设备名称*/
@property (nonatomic, copy) NSString *deviceName;

/** 设备离线笔记数量*/
@property (nonatomic, assign) int NoteNumber;
/**
 获取设备名

 @return 设备名
 */
- (NSString *)getName;

@end
