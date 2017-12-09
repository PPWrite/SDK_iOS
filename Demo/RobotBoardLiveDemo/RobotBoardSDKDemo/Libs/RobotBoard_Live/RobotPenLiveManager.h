//
//  RobotPenLiveManager.h
//  PPWrite
//
//  Created by JMS on 2017/11/13.
//  Copyright © 2017年 Robot. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RobotPenLiveHeader.h"
#import "RobotPenLiveDelegate.h"
#import "RobotLiveStudioBaseModel.h"
#import "RobotLiveStudioModel.h"
@interface RobotPenLiveManager : NSObject

#pragma mark ---------------------------基础设置---------------------------
#pragma mark 基础方法

/*!
 @method
 @abstract 单例初始化
 */
+ (RobotPenLiveManager *)sharePenLiveManager;

/*!
 @method
 @abstract 设置回调代理
 @param delegate 代理
 */
- (void)setPenLiveDelegate:(id<RobotPenLiveDelegate>)delegate;

/*!
 @method  初始化直播间
 @abstract 初始化直播间
 @param channel 直播频道
 @param liveSession 直播Session
 @param userID 用户ID
 @param hostID 主播ID
 */
- (void)initLiveStudioWithChannel:(NSString *)channel LiveSession:(NSString *)liveSession UserID:(NSString *)userID HostID:(NSString *)hostID;

/*!
 @method  开始直播
 @abstract 主播开始直播，
 @param model 开启直播信息
 */
-(void)startStudioWithModel:(RobotLiveStudioBaseModel *)model;
/*!
 @method  退出直播
 @abstract 退出直播
 @param isHost 是否是主播退出
 */
-(void)exitStudioWithisHost:(BOOL)isHost;

/*!
 @method  踢人
 @abstract 主播踢人
 @param userID 用户ID
 */
- (void)awardLeaveWithUserID:(NSString *)userID;

/*!
 @method  授予语音权限
 @abstract 授予语音权限
 @param userID 用户ID
 @param liveID 直播ID
 @param canspeak 是否可以说话
 @param isHost 是否是房主
 */
- (void)awardSpeakWithUserID:(NSString *)userID LiveID:(NSString *)liveID CanSpeak:(BOOL)canspeak IsHost:(BOOL)isHost;

/*!
 @method  授予书写权限
 @abstract 授予书写权限
 @param userID 用户ID
 @param liveID 直播ID
 @param canwrite 是否可以输入
 @param isHost 是否是房主
 */
- (void)awardWriteWithUserID:(NSString *)userID LiveID:(NSString *)liveID CanWrite:(BOOL)canwrite IsHost:(BOOL)isHost;

/*!
 @method  申请语音权限
 @abstract 申请语音权限
 @param userID 用户ID
 @param liveID 直播ID
 */
- (void)askSpeakWithUserID:(NSString *)userID LiveID:(NSString *)liveID;

/*!
 @method  申请书写权限
 @abstract 申请书写权限
 @param userID 用户ID
 @param liveID 直播ID
 */
- (void)askWriteWithUserID:(NSString *)userID LiveID:(NSString *)liveID;

/*!
 @method 清除通道服务
 @abstract 清除通道服务
 */
-(void)CleanChannel;

/*!
 @method  听筒模式/扬声器模式
 @abstract 切换听筒模式/扬声器模式
 @param isLoudspeaker YES：扬声器模式 NO：听筒模式
 @return 是否切换成功
 */
- (BOOL)setLoudspeakerModel:(BOOL)isLoudspeaker;

/*!
 @method  手动设置书写权限
 @abstract 手动设置书写权限，用于权限授予
 @isCan 是否可以书写
 */
-(void)setWriteCan:(BOOL)isCan;

/*!
 @method  手动设置语音权限
 @abstract 手动设置语音权限
 @isCan 是否可以语音
 */
-(void)setSpeakCan:(BOOL)isCan;
@end
