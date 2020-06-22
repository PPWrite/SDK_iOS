//
//  RobotPenDeviceFunction.h
//  PPNote
//
//  Created by JMS on 2019/4/1.
//  Copyright © 2019 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RobotPenHeader.h"

typedef enum {
    /** 旧特性 **/
    BluetoothModeOld = 0,
    /** 新特性 **/
    BluetoothModeNew,
} BluetoothMode;

/*!
 @enum
 @abstract 设备OTA模块
 */
typedef enum {
    /** 不支持升级*/
    RobotFirmwareOTAType_OTA_NULL = 0,
    /** BLE升级*/
    RobotFirmwareOTAType_OTA_BLE,
    /** MCU升级*/
    RobotFirmwareOTAType_OTA_MCU,
    /** BLE和MCU升级*/
    RobotFirmwareOTAType_OTA_ALL,
} RobotFirmwareOTAType;
/*!
 @enum
 @abstract 同步头类型
 */
typedef enum {
    /** 未知*/
    RobotSyncHeaderType_UnKnown = 0,
    /** 短型*/
    RobotSyncHeaderType_Short,
    /** 长型*/
    RobotSyncHeaderType_Long,
    /** 超长型*/
    RobotSyncHeaderType_Overlength,
} RobotSyncHeaderType;

/**
 @enum
 @abstract 页码识别类型
 */
typedef enum {
    /** 不支持*/
    PageIdentificationDeviceType_none = 0,
    /** 普通的页码识别*/
    PageIdentificationDeviceType_common,
    /** 通过点阵进行页码识别*/
    PageIdentificationDeviceType_lattice,
} PageIdentificationDeviceType;

@interface RobotPenDeviceFunction : NSObject

/*!
 @property
 @brief 设备识别范围
 */
@property(nonatomic, assign) CGSize deviceSize;

/*!
 @property
 @brief 原始坐标点位置
 */
@property(nonatomic, assign) RobotPenCoordinateSystem coordinate;

/*!
 @property
 @brief 支持OTA升级
 */
@property(nonatomic, assign) RobotFirmwareOTAType overTheAir;
/*!
 @property
 @brief 支持JEDI升级
 */
@property(nonatomic, assign) BOOL JEDI;
/*!
 @property
 @brief 支持三点数据结构
 */
@property(nonatomic, assign) BOOL newPointStructure;
/*!
 @property
 @brief 支持获取MAC地址
 */
@property(nonatomic, assign) BOOL getMACAddress;
/*!
 @property
 @brief 支持获取模组版本
 */
@property(nonatomic, assign) BOOL getSensor;

/*!
 @property
 @brief 支持主动删除离线笔记
 */
@property(nonatomic, assign) BOOL deleteOfflineNote;
/*!
 @property
 @brief 整形同步数据结构
 */
@property(nonatomic, assign) BOOL intergerSyncData;
/*!
 @property
 @brief 同步数据头结构
 */
@property(nonatomic, assign) RobotSyncHeaderType syncHeaderType;

/*!
 @property
 @brief 支持页码显示
 */
@property(nonatomic, assign) BOOL pageShowDevice;
/*!
 @property
 @brief 支持页码识别
 */
@property(nonatomic, assign) PageIdentificationDeviceType pageIdentificationDevice;
/*!
 @property
 @brief 被限制的设备
 */
@property(nonatomic, assign) BOOL isLimitDevice;

/*!
 @property
 @brief 是否支持蓝牙新特性
 */
@property(nonatomic, assign) BOOL isBLENewFeatureAvailable;

/*!
 @property
 @brief 当前蓝牙模式
 */
@property(nonatomic, assign) BluetoothMode bluetoothMode;

/*!
 @property
 @brief 是否支持获取识别范围
 */
@property(nonatomic, assign) BOOL getSize;

/*!
 @property
 @brief 点数据默认偏移
 */
@property(nonatomic, assign) CGSize pointOffset;
/*!
 @property
 @brief 是否是点阵设备
 */
@property (nonatomic, assign) BOOL isLatticeDevice;
/*!
 @property
 @brief 附加
 */
@property(nonatomic, assign) int extra;
/*!
@property
@brief 心跳时间（秒），0 代表没有心跳。
*/
@property (nonatomic, assign) int heartbeat;
/*!
@property
@brief OTA 升级时需要发送版本好
*/
@property (nonatomic, assign) BOOL otaUpdateNeedSendVersion;

@end
