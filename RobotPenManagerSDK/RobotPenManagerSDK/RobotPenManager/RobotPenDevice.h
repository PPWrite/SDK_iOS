//
//  RobotPenDevice.h
//  RobotPenManagerMacSDKDemo
//
//  Created by JMS on 2017/8/17.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RobotPenHeader.h"
#import <CoreBluetooth/CoreBluetooth.h>


@interface RobotPenDevice : NSObject<NSCoding>
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
  1 == 0格 电量<5%
  2 == 1格 5%<=电量<20%
  3 == 1格 20%<=电量<40%
  4 == 2格 40%<=电量<60%
  5 == 3格 60%<=电量<80%
  6 == 4格 80%<=电量<100%
  7 == 4格 电量 = 100%  
  254:充电中
  255:已充满
 */
@property (nonatomic, assign) int Battery;
/** 信号强度*/
@property (nonatomic, assign) int RSSI;

/** 设备名称*/
@property (nonatomic, copy) NSString *deviceName;

/** 设备离线笔记数量*/
@property (nonatomic, assign) int NoteNumber;

/**
 BLE:固件mac标识
 */
@property (nonatomic, assign) int MacSign;
/**
 获取设备名

 @return 设备名
 */
- (NSString *)getName;


/**
 获取电量百分比显示
 
 @return <#return value description#>
 */
- (int)getDevicePercentageBattery;
/**
 获取倒序的MAC地址
 
 @return <#return value description#>
 */
- (NSString *)getReverseMAC;
@end
