//
//  RobotPenLiveManager.h
//  PPWrite
//
//  Created by JMS on 2017/11/13.
//  Copyright © 2017年 Robot. All rights reserved.
//

#import "RobotPenLiveHeader.h"
#import "RobotTrails.h"


@protocol RobotPenLiveDelegate <NSObject>

@optional

/*!
 @method  获取直播白板状态
 @abstract 获取白板服务状态
 @param wbState 白板状态
 */
- (void)getLiveWhiteBoardState:(WBLiveStateType)wbState;

/*!
 @method  获取直播间状态
 @abstract 获取直播间状态
 @param studioState 直播间状态
 @param Content 观众userID/人数/直播耗时
 @param delay 延迟信息
 */
- (void)getLiveStudioState:(LiveStudioMessageType)studioState Content:(NSString *)Content Delay:(NSInteger)delay;

/*!
 @method  获取直播数据
 @abstract 获取直播数据
 @param dataType 直播数据类型
 @param data 直播数据
 */
- (void)getLiveDataMessageType:(LiveDataMessageType)dataType data:(RobotTrails *)data;

@end








