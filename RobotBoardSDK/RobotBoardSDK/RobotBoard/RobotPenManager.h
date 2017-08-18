//
//  RobotPenManager.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RobotPenHeader.h"
#import "RobotNote.h"
#import "RobotTrailBlock.h"
#import "RobotTrails.h"
#import <CoreBluetooth/CoreBluetooth.h>
#import "RobotPenDevice.h"
#import "RobotPenPoint.h"
#import "RobotPenUtilPoint.h"


@protocol RobotPenDelegate <NSObject>

@optional

/**
 获取设备状态
 
 @param State <#State description#>
 */
- (void)getDeviceState:(DeviceState)State;


/**
 获取点数据
 
 @param point 原始点
 */
- (void)getPointInfo:(RobotPenPoint *)point;

/**
 获取优化点数据
 
 @param point 优化点
 */
- (void)getOptimizesPointInfo:(RobotPenUtilPoint *)point;

/**
 获取设备信息
 
 @param infos <#infos description#>
 */
- (void)getDeviceVersion:(NSDictionary *)infos;

/**
 获取电量、同步笔记信息
 
 @return <#return value description#>
 */
- (NSDictionary *)getDeviceBattery;

/**
 自动连接的中的设备
 
 @param device <#device description#>
 */
- (void)AutoConnectingDevice:(RobotPenDevice *)device;


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
/**
 同步状态
 
 @param state <#state description#>
 */
- (void)SyncState:(SYNCState)state;


/**
 获取离线笔记的笔迹数据
 */
- (void)getSyncData:(RobotTrails *)trails;

/**
 获取同步笔记的笔记信息

 @param note <#note description#>
 */
- (void)getSyncNote:(RobotNote *)note;

/**
 离线笔记数据同步进度

 @param length 总大小
 @param curlength 已同步大小
 @param progess 进度
 */
- (void)getSyncDataLength:(int )length andCurDataLength:(int)curlength andProgress:(float)progess;



/**
 获取笔记数量 和 电量
 @param num <#num description#>
 */
- (void)getStorageNum:(int)num andBattery:(int)battery;


/**
 获取设备电量百分比
 @param percentageBattery 电量百分比
 */
- (void)getDevicePercentageBattery:(PercentageBattery)percentageBattery;
/**
 获取MAC地址
 @param mac <#num description#>
 */
- (void)getMac:(NSString *)mac;

/**
 获取设备名称
 @param name <#num description#>
 */
- (void)getDeviceName:(NSString *)name;

/**
 发现设备

 @param device <#device description#>
 */
- (void)getBufferDevice:(RobotPenDevice *)device;

/**
 设备点击事件

 @param Type <#Type description#>
 */
- (void)getDeviceEvent:(DeviceEventType)Type;


/**
 获取蓝牙状态
 
 @param State <#State description#>
 */
- (void)getBLEState:(CBManagerState)State;

/** 页码检测专用----------------------------专用**/
/**
 获取设备当前页（仅限页码检测）

 @param page 当前页
 */
- (void)getDevicePage:(int)page andNoteKey:(NSString *)NoteKey;

/**
 T9A获取笔迹数据
 */
- (void)getTASyncData:(RobotTrails *)trails andBlockKey:(NSString *)BlockKey;

/**
 T9A获取笔记信息和页码信息

 @param note 笔记信息
 @param page 页码信息
 */
- (void)getTASyncNote:(RobotNote *)note andPage:(int)page;


@end


/**----------------------------------------------------------------------------------*/


@interface RobotPenManager : NSObject

/**
 单例初始化
 */
+ (RobotPenManager *)sharePenManager;

/**
 同步离线笔记抛点
 
 @param isoptimize 是否是优化点，默认为YES
 */
- (void)setSyncOptimizeType:(BOOL)isoptimize;


/**
 是否开启优化笔迹
 默认开启上报原始点 isOriginal = YES
 isOriginal = NO isOptimize = NO,则只开启上报屏幕点
 isOriginal = NO isOptimize = YES,则只开启上报优化后的屏幕点
 
 isOriginal = YES isOptimize = NO,则只开启上报原始点
 isOriginal = YES isOptimize = YES,则只开启上报原始点
 

 @param isOriginal 开启上报原始点
 @param isOptimize 开启上报优化点
 @param isTransform 开启上报原始点转换点(已左上角为（0，0）点)，只有开启上报原始点时有效
 */
- (void)setOrigina:(BOOL)isOriginal optimize:(BOOL)isOptimize transform:(BOOL)isTransform;

/**
 设置场景尺寸(isOriginal = NO时需要设置)

 @param width 场景（显示区域）的宽度
 @param height 场景（显示区域）的高度
 @param isHorizontal 显示的方向
 */
- (void)setSceneSizeWithWidth:(float)width andHeight:(float)height andIsHorizontal:(BOOL)isHorizontal;


/**
 设置笔线条宽度(isOptimize = YES时需要设置)

 @param width <#width description#>
 */
- (void)setStrokeWidth:(float)width;

/**
 设置是否上报悬浮点，默认打开

 @param isReport 默认为YES
 */
- (void)setReportSuspensionPoint:(BOOL)isReport;
/**
 设置抛出优化点时是否抛出原始点
 
 @param isoriginal 默认为NO
 */
- (void)setSendOriginalPointWhenIsOptimize:(BOOL)isoriginal;
/**
 设置中心偏移

 @param point 原始点
 */
- (void)setOffset:(CGPoint)point;

#pragma mark 设备相关

/**
 获取当前链接的设备

 @return <#return value description#>
 */
- (RobotPenDevice *)getConnectDevice;


/**
 连接设备

 @param penDevice <#penDevice description#>
 @param delegate <#delegate description#>
 */
- (void)connectDevice:(RobotPenDevice *)penDevice :(id<RobotPenDelegate>)delegate;


/**
  连接设备  PS：遵循了delegate建议使用这个方法。

 @param penDevice <#penDevice description#>
 */
- (void)connectDevice:(RobotPenDevice *)penDevice ;

/**
 扫描设备
 @param delegate <#delegate description#>
 */
- (void)scanDevice:(id<RobotPenDelegate>)delegate;

/**
 扫描设备 PS：遵循了delegate建议使用这个方法。
 */
- (void)scanDevice;

  
/**
 断开设备
 */
- (void)disconnectDevice;

/**
 获取版本号
 */
- (NSDictionary *)getDeviceVersion;

/**
 是否支持模组升级

 @return <#return value description#>
 */
- (BOOL)getIsHaveSensor;

/**
 获取模组版本信息、是否支持笔校准模式
 */
- (void)getSensorVersion;

/**
 开始SENSOR升级
 
 @param delegate <#delegate description#>
 */
- (void)startSensor:(id<RobotPenDelegate>)delegate;

/**
  开始SENSOR升级 PS：遵循了delegate建议使用这个方法。
 */
- (void)startSensor;

/**
 根据自定义的地址获取固件是否需要更新

 @param urlString 自定义地址（定制专用）
 */
- (void)getIsNeedUpdateWithURL:(NSString *)urlString;

/**
 获取固件是否需要更新
 */
- (void)getIsNeedUpdate;

/**
 获取设备类型

 @return <#return value description#>
 */
- (DeviceType)getConnectDeviceType;


/**
 设置回调代练

 @param delegate <#delegate description#>
 */
- (void)setPenDelegate:(id<RobotPenDelegate>)delegate;




/**
 停止扫描
 **/
-(void)stopScanDevice;


/**
 检查设备是否连接
 */
- (BOOL)checkDeviceConnect;

/**
 检查是否有配对过的设备
 */
- (BOOL)checkIsHaveMatch;

/**
 获取配对设备列表

 @return <#return value description#>
 */
- (NSArray *)getPairingDevice;

/**
 删除指定的配对设备

 @param device <#device description#>
 */
- (void)deletePairingMacDevice:(RobotPenDevice *)device;

/**
 配对指定的设备

 @param device <#device description#>
 */
- (void)savePairingMacDevice:(RobotPenDevice *)device;


/**
 清空所有配对设备
 */
- (void)cleanAllPairingDevice;

/**
 自动链接（自动连接配对列表中的最后一个）
 */
- (void)AutoCheckDeviceConnect;

/**
 设置是否自动链接（自动连接配对列表中的最后一个）
 */
- (void)setAutoCheckDeviceConnect:(BOOL)autoConnect;

/**
 取消当前配对
 */
- (void)deleteConnect;

#pragma mark OTA

/**
 开始OTA升级
 
 @param delegate <#delegate description#>
 */
-(void)startOTA:(id<RobotPenDelegate>)delegate;

/**
 开始OTA升级 PS：遵循了delegate建议使用这个方法。
 */
- (void)startOTA;


#pragma mark 同步笔记
/**
 同步笔记 开始
 
 @param delegate <#delegate description#>
 */
- (void)startSyncNote:(id<RobotPenDelegate>)delegate;

/**
 同步笔记 开始 PS：遵循了delegate建议使用这个方法。
 */
- (void)startSyncNote;

/**
 同步笔记 停止
 */
-(void)stopSyncNote;


/**
 频率校准
 */
- (void)startCalibration;


#pragma mark Other


/**
 以设备宽和场景宽为基础，获取原始/场景的笔迹宽度
 @param W 场景/原始的笔迹宽度
 @param width 场景/原始宽度
 @param ishorizontal 是否是横向
 @param deviceType 设备类型
 @param isOriginal 原始/场景
 @return <#return value description#>
 */
- (CGFloat)getWidth:(CGFloat)W  andSceneWidth:(CGFloat)width andisHorizontal:(BOOL)ishorizontal andDevicetype:(DeviceType)deviceType  isOriginal:(BOOL)isOriginal;


/**
 获取电磁板宽高比
 ishorizontal = yes 长边/短边
 @param deviceType 设备类型
 @param ishorizontal 是否为横向
 @return <#return value description#>
 */
- (CGFloat)getDeviceScaleWithDeviceType:(DeviceType)deviceType andIsHorizontal:(BOOL)ishorizontal;



/**
 根据原始图片尺寸获取屏幕图片尺寸
 
 @param sceneImageSize 屏幕图片尺寸
 @param sceneWidth 屏幕显示宽度
 @param deviceType 设备类型
 @param isHorizontal 电磁板方向
 @return <#return value description#>
 */
- (CGSize)getSceneImageSizeWith:(CGSize)sceneImageSize WithSceneWidth:(float)sceneWidth DeviceType:(int)deviceType IsHorizontal:(BOOL)isHorizontal;


/**
 根据屏幕图片尺寸获取原始图片尺寸
 
 @param sceneImageSize 屏幕图片尺寸
 @param sceneWidth 屏幕显示宽度
 @param deviceType 设备类型
 @param isHorizontal 电磁板方向
 @return <#return value description#>
 */
- (CGSize)getOriginalImageSizeWith:(CGSize)sceneImageSize WithSceneWidth:(float)sceneWidth DeviceType:(int)deviceType IsHorizontal:(BOOL)isHorizontal;

/**
 
 设置升级地址是否是外接
 用于固件自己下载
 @param isOther 默认为No
 */
- (void)setOtherUpdateAddress:(BOOL)isOther;



/**

 设置升级目标的固件版本号

 @param bleVersion ble版本号
 @param mcuVersion mcu版本号
 */
- (void)setHardWareUpdateVerSionWithBLEVersion:(int)bleVersion andMCUVersion:(int)mcuVersion;


/**
 设置升级目标的固件数据

 @param bleData ble数据
 @param mcuData mcu数据
 */
- (void)setHardWareUpdateDataWithBLEData:(NSData *)bleData andMCUData:(NSData *)mcuData;



/**
 设置模组升级版本

 @param sensorType 模组类型 Ps:目前只支持128
 @param sensorVersion 模组版本
 */
- (void)setSensorUpdateVerSionWithSensorType:(int)sensorType andSensorVersion:(int)sensorVersion;

/**
 设置模组升级数据

 @param sensorDatas sensor数据
 */
- (void)setSensorUpdateDataWithSensorData:(NSData *)sensorDatas;



/**
 发送页码信息
 */
- (void)SendPage:(int)Current :(int)Totla;

/**
 修改设备名字
 */
- (void)changeName:(NSString *)name;

/**
 设置离线笔记轨迹的Block
 */
- (void)SetBlockWithBlock:(NSString *)blocks;


/**
 是否支持获取MAC和设备名称
 @return <#return value description#>
 */
- (BOOL)getIsMACAndNameDevice;

/**
 是否是支持BLE和MCU的OTA升级
 
 @return <#return value description#>
 */
- (BOOL)getIsBLEAndMCUOTADevice;


/**
 是否支持获取模组版本
 
 @return <#return value description#>
 */
- (BOOL)getIsSensorDevice;
/**
 取消请求固件版本
 */
- (void)cancelSession;

/** 页码检测专用----------------------------专用**/

/**
 获取页码信息（页码检测设备专用）
 */
-(void)getTAPageInfo;



@end
