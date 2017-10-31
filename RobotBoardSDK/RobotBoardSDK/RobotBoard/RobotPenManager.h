//
//  RobotPenManager.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RobotPenHeader.h"
#import "RobotPenDelegate.h"


@interface RobotPenManager : NSObject

#pragma mark ---------------------------基础设置---------------------------
#pragma mark 基础方法
/**
 单例初始化
 */
+ (RobotPenManager *)sharePenManager;


/**
 设置回调代理
 
 @param delegate <#delegate description#>
 */
- (void)setPenDelegate:(id<RobotPenDelegate>)delegate;


#pragma mark 实时报点类型相关
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


#pragma mark ---------------------------设备相关---------------------------
#pragma mark 设备连接
/**
 扫描设备
 */
- (void)scanDevice;

/**
 停止扫描
 */
-(void)stopScanDevice;

/**
 连接设备
 
 @param penDevice <#penDevice description#>
 */
- (void)connectDevice:(RobotPenDevice *)penDevice ;

/**
 断开设备
 */
- (void)disconnectDevice;


/**
 设置是否自动链接（自动连接配对列表中的最后一个）
 */
- (void)setAutoCheckDeviceConnect:(BOOL)autoConnect;


/**
 自动连接配对列表中的最后一个设备
 */
- (void)AutoCheckDeviceConnect;

/**
 设置电磁板链接超时时间（默认为5s）
 */
- (void)setCheckDeviceOverTime:(float)overtime;

/**
 获取当前链接的设备

 @return <#return value description#>
 */
- (RobotPenDevice *)getConnectDevice;

#pragma mark 设备配对

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
 取消当前配对
 */
- (void)deleteConnect;
/**
 清空所有配对设备
 */
- (void)cleanAllPairingDevice;

#pragma mark 设备改名
/**
 修改设备名字
 */
- (void)changeName:(NSString *)name;


#pragma mark ---------------------------离线笔记相关---------------------------
/**
 设置同步离线笔记抛点
 
 @param isoptimize 是否是优化点，默认为YES
 */
- (void)setSyncOptimizeType:(BOOL)isoptimize;


/**
 开始同步笔记
 */
- (void)startSyncNote;

/**
 根据密码开始同步笔记
 */
- (void)startSyncNoteWithPassWord:(NSString *)password;

/**
 停止同步笔记
 */
-(void)stopSyncNote;

#pragma mark ---------------------------OTA(固件升级)相关---------------------------
/**
 开始OTA升级
 */
- (void)startOTA;

/**
 结束OTA升级
 */
- (void)ExitOTA;
#pragma mark ---------------------------模组相关---------------------------

/**
 开始SENSOR升级
 */
- (void)startSensor;


/**
 频率校准
 */
- (void)startCalibration;


#pragma mark ---------------------------硬件版本检测相关---------------------------

/**
 检查固件（BLE&MCU）是否需要更新
 */
- (void)getIsNeedUpdate;

/**
 取消检查固件版本
 */
- (void)cancelSession;

/**
 是否是支持BLE和MCU的OTA升级
 */
- (BOOL)getIsBLEAndMCUOTADevice;

/**
 是否支持获取MAC和设备名称
 */
- (BOOL)getIsMACAndNameDevice;

/**
 是否支持获取模组版本
 */
- (BOOL)getIsSensorDevice;

/**
 获取模组版本信息、是否支持笔校准模式
 */
- (void)getSensorVersion;

/** 页码检测专用----------------------------专用**/

/**
 获取页码信息（页码检测设备专用）
 */
-(void)getTAPageInfo;


/**
 设置是否获取mac 和 Sensor
 
 @param getMAC <#getMAC description#>
 @param getSensor <#getSensor description#>
 */
- (void)setGetMAC:(BOOL)getMAC getSensor:(BOOL)getSensor;


#pragma mark ---------------------------硬件外部升级相关---------------------------


/**
 根据自定义的地址获取固件是否需要更新
 此方法只需设置URL即可不可与本组以下方法同用。
 @param urlString 自定义地址（定制专用）
 */
- (void)getIsNeedUpdateWithURL:(NSString *)urlString;

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


#pragma mark ---------------------------转换相关---------------------------
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
- (CGSize)getOriginalImageSizeWith:(CGSize)sceneImageSize WithSceneWidth:(float)sceneWidth DeviceType:(int)deviceType IsHorizontal:(BOOL)isHorizontal
;

#pragma mark ---------------------------Other---------------------------

/**
 设置连接设备型号
 
 @param deviceType <#deviceType description#>
 */
- (void)setDeviceType:(DeviceType)deviceType;

/**
 获取当前的系统服务状态

 @return <#return value description#>
 */
- (OSDeviceStateType)getOSDeviceState;

/**
 设置新的同步密码
 
 @param oldPassWord 旧密码
 @param newPassword 新密码
 */
- (void)setSyncPassWordWithOldPassWord:(NSString *)oldPassWord NewPassWord:(NSString *)newPassword;

/**
 开启数据上报
 */
- (void)OpneReportedData;

/**
 关闭数据上报
 */
- (void)CloseReportedData;


/**
 擦除数据
 
 @param type 操作类型
 */
- (void)CleanDeviceDataWithType:(CleanDataType)type;
#pragma mark ---------------------------内部专用---------------------------

/**
 发送页码信息
 */
- (void)SendPage:(int)Current :(int)Totla;

/**
 设置离线笔记轨迹的Block
 */
- (void)SetBlockWithBlock:(NSString *)blocks;







@end
