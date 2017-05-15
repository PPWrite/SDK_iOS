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

- (void)OTAUpdateProgress:(float)progess;


/**
 SYNCNoteState
 
 @param state <#state description#>
 */
- (void)SyncState:(SYNCState)state;


/**
 获取离线笔记数据
 */
- (void)getSyncData:(RobotTrails *)trails;
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



//设备点击事件
- (void)getDeviceEvent:(DeviceEventType)Type;

/** T9A----------------------------专用**/
/**
 获取设备当前页（仅限T9A）

 @param page 当前页
 */
- (void)getDevicePage:(int)page;

/**
 T9A获取笔记数据
 */
- (void)getTASyncData:(RobotTrails *)trails andBlockKey:(NSString *)BlockKey;
- (void)getTASyncNote:(RobotNote *)note andPage:(int)page;


@end


/**----------------------------------------------------------------------------------*/


@interface RobotPenManager : NSObject

/**
 单例初始化
 */
+ (RobotPenManager *)sharePenManager;



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

 @param width <#width description#>
 @param height <#height description#>
 @param isHorizontal <#isHorizontal description#>
 */
- (void)setSceneSizeWithWidth:(float)width andHeight:(float)height andIsHorizontal:(BOOL)isHorizontal;


/**
 设置笔线条宽度(isOptimize = YES时需要设置)

 @param width <#width description#>
 */
- (void)setStrokeWidth:(float)width;


/**
 设置中心偏移

 @param point 原始点
 */
- (void)setOffset:(CGPoint)point;

#pragma mark 设备相关
////获取当前链接的设备
- (RobotPenDevice *)getConnectDevice;
//
//连接设备
- (void)connectDevice:(RobotPenDevice *)penDevice :(id<RobotPenDelegate>)delegate;
- (void)connectDevice:(RobotPenDevice *)penDevice ;
/**
 扫描设备
 @param delegate <#delegate description#>
 */
- (void)scanDevice:(id<RobotPenDelegate>)delegate;
- (void)scanDevice;

  
//断开设备
- (void)disconnectDevice;



//获取版本号
- (NSDictionary *)getDeviceVersion;

/**
 获取固件是否需要更新
 */
- (BOOL)getIsNeedUpdateWithURL:(NSString *)urlString;

- (BOOL)getIsNeedUpdate;

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


//检查设备是否连接
- (BOOL)checkDeviceConnect;

//检查是否有配对过的设备
- (BOOL)checkIsHaveMatch;

//检查设备是否连接 -- 自动链接
- (void)AutoCheckDeviceConnect;

//设置是否自动链接
- (void)setAutoCheckDeviceConnect:(BOOL)autoConnect;

/**
 取消配对
 */
- (void)deleteConnect;

#pragma mark OTA

/**
 开始OTA升级
 
 @param delegate <#delegate description#>
 */
-(void)startOTA:(id<RobotPenDelegate>)delegate;

- (void)startOTA;


#pragma mark 同步笔记
/**
 同步笔记 开始
 
 @param delegate <#delegate description#>
 */
- (void)startSyncNote:(id<RobotPenDelegate>)delegate;

- (void)startSyncNote;

/**
 同步笔记 停止
 */
-(void)stopSyncNote;



#pragma mark Other

//发送页码信息
- (void)SendPage:(int)Current :(int)Totla;


//修改设备名字
- (void)changeName:(NSString *)name;


//设置离线笔记轨迹的Block
- (void)SetBlockWithBlock:(NSString *)blocks;

/** T9A----------------------------专用**/
//设置离线笔记轨迹的Block
- (void)SetBlockWithBlock:(NSString *)blocks andPage:(int)page;



/**
 是否是新的版本规则
 
 @return <#return value description#>
 */
- (BOOL)getIsNewDeviceVersion;

@end
