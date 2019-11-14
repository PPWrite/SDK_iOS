//
//  RobotPenManager.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

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

/*!
 @method
 @abstract 设置原始点的偏移
 @discussion 用于标准A4设备对齐使用
 @param offset 偏移量
 */
-(void)setPointOffset:(CGPoint)offset;
#pragma mark ---------------------------设备相关---------------------------
#pragma mark 设备连接

/*!
 @method
 @abstract  扫描设备
 @param scanAll 是否搜索全部（未连接）设备，默认为NO(只搜索可配对与可连接状态);
 */
- (void)scanDeviceWithALL:(BOOL)scanAll;

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
 @discussion 蓝牙（BLE）专用
 @param autoConnect 布尔值
 */
- (void)setAutoCheckDeviceConnect:(BOOL)autoConnect;

/*!
 @method
 @abstract 自动连接配对列表中的最后一个设备
 @discussion 蓝牙（BLE）专用
 */
- (void)AutoCheckDeviceConnect;

/*!
 @method
 @abstract 设置电磁板链接超时时间（默认为5s）
 @discussion 蓝牙（BLE）专用
 @param overtime 时间
 */
- (void)setCheckDeviceOverTime:(float)overtime;

/*!
 @method
 @abstract  获取当前链接的设备
 @result 返回结果
 */
- (RobotPenDevice *)getConnectDevice;

/*!
 @method
 @abstract  设置搜索设备的名称前缀
 @discussion 只搜索带有该前缀的设备
 @param namePrefix 名称前缀数组
 */
- (void)setConnectLimitDeviceList:(NSArray *)namePrefix;

/*!
 @method 是否打开实时搜索设备
 @abstract  开启后蓝牙不会过滤相同的设备信号，默认关闭
 @discussion 蓝牙（BLE）专用
 @param open 是否开启
 @param search 是否开始搜索设备
 */
- (void)setOpenSearchRealTime:(BOOL)open startSearch:(BOOL)search;

/*!
 @method 是否打开实时获取打开搜索到设备的RSSI
 @abstract  打开后实时上报搜索到的设备的RSSI，默认关闭
 @discussion 需要打开setOpenSearchRealTime设置。
 @discussion 蓝牙（BLE）专用
 @param open 是否开启
 */
- (void)setOpenReadRealTimeRSSI:(BOOL)open;

/*!
 @method 打开周期更新设备列表
 @abstract  打开周期更新设备列表，默认关闭
 @discussion 打开后可根据setOpenInspectDeviceList方法设置的时间周期上报已断开的设备信息.
 当setOpenSearchRealTime开启后此方法无效。
 @discussion 蓝牙（BLE）专用
 @param open 是否开启
 */
- (void)setOpenInspectDeviceList:(BOOL)open;

/*!
 @method 设置设备列表更新的时间周期
 @abstract  设置上报断开设备的周期，默认为60s
 @discussion 蓝牙（BLE）专用
 @param timePeriod 时间周期，单位为秒
 */
- (void)setInspectDeviceListTimePeriod:(float)timePeriod;

/*!
 @method 设置上报无效设备延迟时间
 @abstract  设置上报无效设备延迟时间，默认为5s
 @discussion 每一秒大约检测15台设备，可根据场景设备数量适当调整，5s（大约65台设备）。
 此方法适用于setOpenSearchRealTime和setOpenInspectDeviceList开启
 设备数量/15 <= delayTime < timePeriod
 @discussion 蓝牙（BLE）专用
 @param delayTime 时间周期，单位为秒
 */
- (void)setReportInvalidDeviceDelayTime:(float)delayTime;

/*!
 @method
 @abstract 获取设备列表
 @result 返回结果
 */
- (NSArray *)getDeviceSearchList;

/*!
 @method
 @abstract 开启搜索限制设备 默认关闭
 @discussion 默认屏蔽的设备使用
 */
- (void)openLimitedDevice:(NSString *)deviceKey;

#pragma mark 设备配对
/*!
 @method
 @abstract 检查是否有配对过的设备
 @discussion 蓝牙（BLE）专用
 @result 返回结果
 */
- (BOOL)checkIsHaveMatch;

/*!
 @method
 @abstract 检查是否是已配对过的设备
 @discussion 蓝牙（BLE）专用
 @param device 设备
 @result 返回结果
 */
- (BOOL)getIsPairedWithDevice:(RobotPenDevice *)device;

/*!
 @method
 @abstract 获取配对设备列表
 @discussion 蓝牙（BLE）专用
 @result 返回结果
 */
- (NSArray *)getPairingDevice;

/*!
 @method
 @abstract 删除指定的配对设备
 @discussion 蓝牙（BLE）专用
 @param device 设备
 */
- (void)deletePairingMacDevice:(RobotPenDevice *)device;

/*!
 @method
 @abstract  取消当前配对
 @discussion 蓝牙（BLE）专用
 */
- (void)deleteConnect;

/*!
 @method
 @abstract  清空所有配对设备
 @discussion 蓝牙（BLE）专用
 */
- (void)cleanAllPairingDevice;

#pragma mark 设备改名
/*!
 @method
 @abstract 修改设备名字
 @param name 只支持字母、数字和下划线
 */
- (void)changeName:(NSString *)name;

#pragma mark 连接的设备RSSI

/*!
 @method 是否打开当前连接设备的RSSI
 @abstract 默认关闭
 @param open <#open description#>
 */
- (void)setOpenReadDeviceRSSI:(BOOL)open;

/*!
 @method 设置读取当前连接设备的RSSI时间周期
 @abstract 默认为5S
 @param timePeriod 时间周期，单位为秒
 */
- (void)setReadDeviceRSSITimePeriod:(float)timePeriod;

/*!
 @method 读取当前连接设备RSSI
 @abstract 读取当前连接设备RSSI
 */
- (void)readDeviceRSSI;

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

/*!
 @method
 @abstract 删除所有离线笔记
 @discussion 在非同步模式下使用（T9A_EN/T9W_WX）
 */
-(void)deleteAllSyncNote;

/**
 设置离线笔记的笔迹宽度

 @param width 笔迹宽度
 */
-(void)setSyncNoteWidth: (CGFloat) width;

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
- (BOOL)getIsBLEAndMCUOTADevice DEPRECATED_MSG_ATTRIBUTE("Please use RobotPenDevice.function.overTheAir == RobotFirmwareOTAType_OTA_ALL");
/*!
 @method
 @abstract 是否支持获取MAC和设备名称
 */
- (BOOL)getIsMACAndNameDevice DEPRECATED_MSG_ATTRIBUTE("Please use RobotPenDevice.function.getMACAddress");
/*!
 @method
 @abstract 是否支持获取模组版本
 */
- (BOOL)getIsSensorDevice DEPRECATED_MSG_ATTRIBUTE("Please use RobotPenDevice.function.getSensor");
/**
 @method
 @abstract获取是否是支持主动删除离线数据的设备
 */
- (BOOL)getIsDeleteNoteDevice DEPRECATED_MSG_ATTRIBUTE("Please use RobotPenDevice.function.deleteOfflineNote");

/*!
 @method
 @abstract 获取模组版本信息、是否支持笔校准模式
 */
- (void)getSensorVersion DEPRECATED_MSG_ATTRIBUTE("Please use RobotPenDevice.function.getSensor");
#pragma mark ---------------------------硬件版本检测相关-OEM系列---------------------------
/*!
 @method
 @abstract 获取页码信息
 @discussion T9系列专用
 */
-(void)getTAPageInfo;

/*!
 @method
 @abstract 获取设备休眠时间
 @discussion T9B/T8C系列专用
*/
-(void)getOEMDeviceDormantTime;

/*!
 @method
 @abstract 设置设备休眠时间
 @discussion T9B/T8C系列专用
 @param time 0-65535min
 */
-(void)setOEMDeviceDormantTimeWith:(int)time;

/*!
 @method
 @abstract 获取设备尺寸及笔记标识位
 @discussion T8C专用
 */
-(void)getOEMDeviceSize;

/*!
 @method
 @abstract 获取设备存储扇区大小
 @discussion T9A_EN专用
 */
-(void)getDeviceSectionSize;
/*!
 @method
 @abstract 设置是否获取mac、Sensor和Name
 @param getMAC 布尔值
 @param getSensor 布尔值
 @param getName 布尔值
 */
- (void)setGetMAC:(BOOL)getMAC getSensor:(BOOL)getSensor getName:(BOOL)getName;


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
 @param sensorType 模组类型 Ps:目前只支持128/129
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
 @abstract 设置设备转换点坐标
 @param type 坐标系原点位置
 */
- (void)setTransformsPointWithType:(RobotPenCoordinateSystem)type;
/**
 @method
 @abstract 设置数据点转换比例，强制转换。
 @discussion 默认为原始比例
 @param type 转换类型
 */
- (void)setScalePointTo:(RobotPaperSizeType)type;
/*!
 @method
 @abstract 设置电磁板报点尺寸类型，非强转。
 @discussion 默认为原始比例，暂时只用于T9W_A
 @param type 转换类型
 */
- (void)setDeviceScalePointType:(RobotPaperSizeType)type;
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
- (CGSize)getOriginalImageSizeWith:(CGSize)sceneImageSize WithSceneWidth:(float)sceneWidth DeviceType:(int)deviceType IsHorizontal:(BOOL)isHorizontal;

#pragma mark ---------------------------C7--------------------------

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
- (void)OpenReportedData;

/*!
 @method
 @abstract 关闭数据上报
 */
- (void)CloseReportedData;

/*!
 @method
 @abstract 擦除数据
 @param type 操作类型
 */
- (void)CleanDeviceDataWithType:(CleanDataType)type;

#pragma mark ---------------------------T7B_HF--------------------------

/*!
 @method
 @abstract 复位休眠时间
 @discussion T7B_HF 使用
 */
- (void)resetDeviceSleepTime;

#pragma mark ---------------------------MouseMode--------------------------
/*!
 @method
 @abstract 是否是支持鼠标模式的设备
 @discussion MouseMode设备USB使用
 */
- (BOOL)getIsMouseDevice DEPRECATED_MSG_ATTRIBUTE("Please use RobotPenDevice.function.mouseMode");
/*!
 @method
 @abstract 获取设备当前模式
 @discussion MouseMode设备USB使用
 */
- (RobotPenMouseDeviceModel)getMouseDeviceMode;
/*!
 @method
 @abstract 改变设备模式
 @discussion 改变设备的当前模式（鼠标模式、书写模式），MouseMode设备USB使用。
 @param model 模式
 */
- (void)changeMouseDeviceMode:(RobotPenMouseDeviceModel)model;

#pragma mark ---------------------------DM6--------------------------
/*!
 @method
 @abstract 设置DM6点阵排列适配方式
 @discussion DM6 使用,默认为NO
 @param isHorizontal 是否是g横向
 */
- (BOOL)setDM6Arrangement:(BOOL)isHorizontal;
/*!
 @method
 @abstract 设置原点坐标
 @discussion DM6 使用
 @param upleftPoint 左上角坐标
 @param lowrightPoint 右下坐标
 */
- (void)setDM6OriginPointWithUpleftPoint:(CGPoint)upleftPoint LowrightPoint:(CGPoint)lowrightPoint;

/*!
 @method
 @abstract 获取点阵纸的图片
 @discussion DM6 使用
 @param sk 用户秘钥
 @param point 坐标
 */
- (void)getDM6OriginImageWithSK:(NSString *)sk Point:(CGPoint)point Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

#pragma mark ---------------------------PointStruct---------------------------
/*!
 @method
 @abstract 自动升级为高级点模式
 @discussion T7C_BN/T8S/J7B_ZY/T9B_ZXB使用
 @discussion 默认为NO
 */
- (void)setDevicePointUpdate:(BOOL)update;
/*!
 @method
 @abstract  设置点结构的类型
 @discussion T7C_BN/T8S/J7B_ZY/T9B_ZXB使用
 @param type 点数据结构类型
 */
- (void)setDevicePointStruct:(PointStructType)type;

#pragma mark ---------------------------Other---------------------------

/*!
 @method 设置蓝牙线程
 @abstract 用于设置蓝牙线程,默认主线程
 @discussion 蓝牙（BLE）专用
 @param queueType 设备类型
 @param queue 用户自定义线程 queueType =  BLEQueueType_User时必填，否则可为nil
 */
- (void)setBLEQueueType:(BLEQueueType)queueType queue:(nullable dispatch_queue_t)queue;

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
 @abstract 获取设备尺寸
 @param type 设备类型
 @result 返回结果
 */
- (CGSize)getDeviceSizeWithDeviceType:(DeviceType)type;

/*!
 @method
 @abstract 获取当前的系统服务状态
 @result 返回结果
 */
- (OSDeviceStateType)getOSDeviceState;

/*!
 @method 获取SDK版本号
 @abstract 获取SDK版本号
 */
- (NSString *)getSDKVersion;

#pragma mark ---------------------------内部专用---------------------------

/*!
 @method
 @abstract 发送页码信息
 @param Current 当前页
 @param total 所有页码
 */
- (void)SendPage:(int)Current :(int)total;

/*!
 @method
 @abstract 设置离线笔记轨迹的Block
 */
- (void)SetBlockWithBlock:(NSString *)blocks;

/*!
 @method
 @abstract 清除BLE的一些缓存数据
 */
-(void)cleanCache;

/*!
 @method
 @abstract 开启离线笔记原始数据上报
 */
- (void)openSyncOriginalData:(NSString *)key;


@end


