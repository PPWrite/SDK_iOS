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

/*!
 @method
 @abstract 单例初始化
 */
+ (RobotPenManager *)sharePenManager;

/*!
 @method
 @abstract 设置回调代理
 @param delegate 代理
 */
- (void)setPenDelegate:(id<RobotPenDelegate>)delegate;


#pragma mark 实时报点类型相关

/*!
 @method
 @abstract 是否开启优化笔迹
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

/*!
 @method
 @abstract 设置场景尺寸(isOriginal = NO时需要设置)
 @param width 场景（显示区域）的宽度
 @param height 场景（显示区域）的高度
 @param isHorizontal 显示的方向
 */
- (void)setSceneSizeWithWidth:(float)width andHeight:(float)height andIsHorizontal:(BOOL)isHorizontal;


/*!
 @method
 @abstract  设置笔线条宽度(isOptimize = YES时需要设置)
 @param width 宽度
 */
- (void)setStrokeWidth:(float)width;

/*!
 @method
 @abstract 设置是否上报悬浮点，默认打开
 @param isReport 默认为YES
 */
- (void)setReportSuspensionPoint:(BOOL)isReport;

/*!
 @method
 @abstract 设置抛出优化点时是否抛出原始点
 @param isoriginal 默认为NO
 */
- (void)setSendOriginalPointWhenIsOptimize:(BOOL)isoriginal;

/*!
 @method
 @abstract 设置中心偏移
 @param point 原始点
 */
- (void)setOffset:(CGPoint)point;


#pragma mark ---------------------------设备相关---------------------------
#pragma mark 设备连接

/*!
 @method
 @abstract  扫描设备
 */
- (void)scanDevice;

/*!
 @method
 @abstract 停止扫描
 */
-(void)stopScanDevice;
/*!
 @method
 @abstract 连接设备
 @param penDevice 设备
 */
- (void)connectDevice:(RobotPenDevice *)penDevice ;

/*!
 @method
 @abstract 断开设备
 */
- (void)disconnectDevice;
/*!
 @method
 @abstract 设置是否自动链接（自动连接配对列表中的最后一个）
 @param autoConnect 布尔值
 */
- (void)setAutoCheckDeviceConnect:(BOOL)autoConnect;

/*!
 @method
 @abstract 自动连接配对列表中的最后一个设备
 */
- (void)AutoCheckDeviceConnect;

/*!
 @method
 @abstract 设置电磁板链接超时时间（默认为5s）
 @param overtime 时间
 */
- (void)setCheckDeviceOverTime:(float)overtime;

/*!
 @method
 @abstract  获取当前链接的设备
 @result 返回结果
 */
- (RobotPenDevice *)getConnectDevice;

#pragma mark 设备配对
/*!
 @method
 @abstract 检查是否有配对过的设备
 @result 返回结果
 */
- (BOOL)checkIsHaveMatch;

/*!
 @method
 @abstract 获取配对设备列表
 @result 返回结果
 */
- (NSArray *)getPairingDevice;

/*!
 @method
 @abstract 删除指定的配对设备
 @param device 设备
 */
- (void)deletePairingMacDevice:(RobotPenDevice *)device;

/*!
 @method
 @abstract  取消当前配对
 */
- (void)deleteConnect;

/*!
 @method
 @abstract  清空所有配对设备
 */
- (void)cleanAllPairingDevice;

#pragma mark 设备改名
/*!
 @method
 @abstract 修改设备名字
 */
- (void)changeName:(NSString *)name;


#pragma mark ---------------------------离线笔记相关---------------------------
/*!
 @method
 @abstract 设置同步离线笔记抛点
 @param isoptimize 是否是优化点，默认为YES
 */
- (void)setSyncOptimizeType:(BOOL)isoptimize;
/*!
 @method
 @abstract  开始同步笔记
 */
- (void)startSyncNote;
/*!
 @method
 @abstract 根据密码开始同步笔记
 */
- (void)startSyncNoteWithPassWord:(NSString *)password;
/*!
 @method
 @abstract 停止同步笔记
 */
-(void)stopSyncNote;

#pragma mark ---------------------------OTA(固件升级)相关---------------------------
/*!
 @method
 @abstract 开始OTA升级
 */
- (void)startOTA;
/*!
 @method
 @abstract  结束OTA升级
 */
- (void)ExitOTA;
#pragma mark ---------------------------模组相关---------------------------
/*!
 @method
 @abstract 开始SENSOR升级
 */
- (void)startSensor;
/*!
 @method
 @abstract 频率校准
 */
- (void)startCalibration;


#pragma mark ---------------------------硬件版本检测相关---------------------------
/*!
 @method
 @abstract 检查固件（BLE&MCU）是否需要更新
 */
- (void)getIsNeedUpdate;

/*!
 @method
 @abstract  取消检查固件版本
 */
- (void)cancelSession;
/*!
 @method
 @abstract 是否是支持BLE和MCU的OTA升级
 */
- (BOOL)getIsBLEAndMCUOTADevice;
/*!
 @method
 @abstract 是否支持获取MAC和设备名称
 */
- (BOOL)getIsMACAndNameDevice;
/*!
 @method
 @abstract 是否支持获取模组版本
 */
- (BOOL)getIsSensorDevice;
/*!
 @method
 @abstract 获取模组版本信息、是否支持笔校准模式
 */
- (void)getSensorVersion;

/** 页码检测专用----------------------------专用**/
/*!
 @method
 @abstract 获取页码信息（页码检测设备专用）
 */
-(void)getTAPageInfo;

/*!
 @method
 @abstract 设置是否获取mac 和 Sensor
 @param getMAC 布尔值
 @param getSensor 布尔值
 */
- (void)setGetMAC:(BOOL)getMAC getSensor:(BOOL)getSensor;


#pragma mark ---------------------------硬件外部升级相关---------------------------

/*!
 @method
 @abstract 根据自定义的地址获取固件是否需要更新,此方法只需设置URL即可不可与本组以下方法同用。
 @param urlString 自定义地址（定制专用）
 */
- (void)getIsNeedUpdateWithURL:(NSString *)urlString;

/*!
 @method
 @abstract 设置升级数据包是否是外接,用于固件自己下载
 @param isOther 默认为No
 */
- (void)setOtherUpdateAddress:(BOOL)isOther;

/*!
 @method
 @abstract 设置升级目标的固件版本号
 @param bleVersion ble版本号
 @param mcuVersion mcu版本号
 */
- (void)setHardWareUpdateVerSionWithBLEVersion:(int)bleVersion andMCUVersion:(int)mcuVersion;

/*!
 @method
 @abstract 设置升级目标的固件数据
 @param bleData ble数据
 @param mcuData mcu数据
 */
- (void)setHardWareUpdateDataWithBLEData:(NSData *)bleData andMCUData:(NSData *)mcuData;


/*!
 @method
 @abstract 设置模组升级版本
 @param sensorType 模组类型 Ps:目前只支持128
 @param sensorVersion 模组版本
 */
- (void)setSensorUpdateVerSionWithSensorType:(int)sensorType andSensorVersion:(int)sensorVersion;

/*!
 @method
 @abstract 设置模组升级数据
 @param sensorDatas sensor数据
 */
- (void)setSensorUpdateDataWithSensorData:(NSData *)sensorDatas;


#pragma mark ---------------------------转换相关---------------------------

/*!
 @method
 @abstract 以设备宽和场景宽为基础，获取原始/场景的笔迹宽度
 @param W 场景/原始的笔迹宽度
 @param width 场景/原始宽度
 @param ishorizontal 是否是横向
 @param deviceType 设备类型
 @param isOriginal 原始/场景
 @result 返回结果
 */
- (CGFloat)getWidth:(CGFloat)W  andSceneWidth:(CGFloat)width andisHorizontal:(BOOL)ishorizontal andDevicetype:(DeviceType)deviceType  isOriginal:(BOOL)isOriginal;

/*!
 @method
 @abstract 获取电磁板宽高比
 @param deviceType 设备类型
 @param ishorizontal 是否为横向
 @result 返回结果
 */
- (CGFloat)getDeviceScaleWithDeviceType:(DeviceType)deviceType andIsHorizontal:(BOOL)ishorizontal;

/*!
 @method
 @abstract 根据原始图片尺寸获取屏幕图片尺寸
 @param sceneImageSize 屏幕图片尺寸
 @param sceneWidth 屏幕显示宽度
 @param deviceType 设备类型
 @param isHorizontal 电磁板方向
 @result 返回结果
 */
- (CGSize)getSceneImageSizeWith:(CGSize)sceneImageSize WithSceneWidth:(float)sceneWidth DeviceType:(int)deviceType IsHorizontal:(BOOL)isHorizontal;

/*!
 @method
 @abstract 根据屏幕图片尺寸获取原始图片尺寸
 @param sceneImageSize 屏幕图片尺寸
 @param sceneWidth 屏幕显示宽度
 @param deviceType 设备类型
 @param isHorizontal 电磁板方向
 @result 返回结果
 */
- (CGSize)getOriginalImageSizeWith:(CGSize)sceneImageSize WithSceneWidth:(float)sceneWidth DeviceType:(int)deviceType IsHorizontal:(BOOL)isHorizontal
;

#pragma mark ---------------------------Other---------------------------

/*!
 @method 设置默认连接设备型号
 @abstract 用于连接之前防止出现未知类型设置设备类型，适用于单一设备（只用一种设备）。
 @param deviceType 设备类型
 */
- (void)setDeviceType:(DeviceType)deviceType;

/*!
 @method 设置已连接设备型号
 @abstract 用于已经连接设备后设置设备类型
 @param deviceType 设备类型
 */
- (void)setConnectedDeviceType:(DeviceType)deviceType;

/*!
 @method
 @abstract 获取当前的系统服务状态
 @result 返回结果
 */
- (OSDeviceStateType)getOSDeviceState;

/*!
 @method
 @abstract 设置新的同步密码
 @param oldPassWord 旧密码
 @param newPassword 新密码
 */
- (void)setSyncPassWordWithOldPassWord:(NSString *)oldPassWord NewPassWord:(NSString *)newPassword;
/*!
 @method
 @abstract 开启数据上报
 */
- (void)OpneReportedData;

/*!
 @method
 @abstract 关闭数据上报
 */
- (void)CloseReportedData;

/*!
 @method
 @abstract 擦除数据
 */
- (void)CleanDeviceDataWithType:(CleanDataType)type;
#pragma mark ---------------------------内部专用---------------------------

/*!
 @method
 @abstract 发送页码信息
 @param Current 当前页
 @param Totla 所有页码
 */
- (void)SendPage:(int)Current :(int)Totla;

/*!
 @method
 @abstract 设置离线笔记轨迹的Block
 */
- (void)SetBlockWithBlock:(NSString *)blocks;







@end

