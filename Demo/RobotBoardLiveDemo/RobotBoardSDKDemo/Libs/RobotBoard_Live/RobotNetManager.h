//
//  RobotNetManager.h
//  RobotNetManager
//
//  Created by JMS on 2016/11/20.
//  Copyright © 2016年 Robot.cn. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface RobotNetManager : NSObject

/**
 单例初始化
 */
+ (RobotNetManager *)shareNetManager;

/** 重置session*/
- (void)sessionManagerSet;

/*!
 @method 设置请求超时时间
 @abstract  设置请求超时时间
 */
- (void)setTimeOut:(int)timeOut;

/*!
 @method   获取直播间频道名称
 @abstract  获取直播间频道名称
 @param liveID 直播间liveID
 @param isEncrypt 是否加密1：加密0：未加密
 @param password 直播间密码
 @return <#return value description#>
 */
- (NSString *)getLiveChannelNameWithLiveID:(NSString *)liveID IsEncrypt:(BOOL)isEncrypt Password:(NSString *)password;
/*!
 @method  获取直播间信息
 @abstract 获取直播间信息
 @param liveID 直播间liveID
 @param isEncrypt 是否加密1：加密0：未加密
 @param password 直播间密码
 @param userID 用户UserID
 @param userSession 用户UserSession
 */
- (void)getLiveInfomationWithLiveID:(NSString *)liveID IsEncrypt:(BOOL)isEncrypt Password:(NSString *)password UserID:(NSString *)userID UserSession:(NSString *)userSession Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method  创建直播间
 @abstract 创建直播间
 @param name 直播间名称
 @param password 直播间密码
 @param userID 用户UserID
 @param userSession 用户UserSession
 @param about 直播间简介
 @param tags 直播间标签数组

 */
- (void)BuildLiveStudioWithName:(NSString *)name Password:(NSString *)password UserID:(NSString *)userID UserSession:(NSString *)userSession About:(NSString *)about Tags:(NSArray *)tags Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method  获取我的直播列表
 @abstract 获取我的直播列表
 @param userID 用户UserID
 @param userSession 用户UserSession
 @param pageIndex 页码
 */
- (void)getMyLiveStudioListWithUserID:(long)userID UserSession:(NSString *)userSession PageIndex:(int)pageIndex Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;






#pragma mark 内部用

/*!
 @method 重置session
 @abstract  重置session
 */
- (void)sessionManagerSet;

/*!
 @method  文件资源列举
 @abstract 文件资源列举
 */
- (void)getFileSourceWithFilePath:(NSString *)FilePath Token:(NSString *)Token Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;
/*!
 @method  删除文件资源
 @abstract 删除文件资源
 */
- (void)deleteFileSourceWithFilePath:(NSString *)FilePath Token:(NSString *)Token Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method  文件头信息获取
 @abstract文件头信息获取
 */
- (void)GetFileWithFilePath:(NSString *)FilePath Token:(NSString *)Token Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


@end
