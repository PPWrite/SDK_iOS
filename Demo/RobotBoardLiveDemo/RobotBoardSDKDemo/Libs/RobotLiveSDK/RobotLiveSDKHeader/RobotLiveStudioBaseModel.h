//
//  RobotLiveStudioBaseModel.h
//  PPWrite
//
//  Created by JMS on 2017/11/25.
//  Copyright © 2017年 Robot. All rights reserved.
//

#import <Foundation/Foundation.h>
/*!
 @class 直播间初始化模型
 @abstract 直播间初始化模型
 */
@interface RobotLiveStudioBaseModel : NSObject
/*!
 @property  直播间频道
 @brief 直播间频道
 */
@property (nonatomic, copy) NSString *Channel;
/*!
 @property  直播间ID
 @brief 直播间ID
 */
@property (nonatomic, copy) NSString *LiveID;
/*!
 @property  直播间Session
 @brief 直播间Session
 */
@property (nonatomic, copy) NSString *LiveSession;
/*!
 @property  用户UserID
 @brief 用户UserID
 */
@property (nonatomic, copy) NSString *UserID;
/*!
 @property  主播UserID
 @brief 主播UserID
 */
@property (nonatomic, copy) NSString *HostID;
/*!
 @property  主播UserSession
 @brief 主播UserSession
 */
@property (nonatomic, copy) NSString *UserSession;
/*!
 @property  语音权限
 @brief 语音权限
 */
@property (nonatomic, assign) BOOL IsSpeak;
/*!
 @property  输写权限
 @brief 输写权限
 */
@property (nonatomic, assign) BOOL IsWrite;
/*!
 @property  直播间笔记标识
 @brief 直播间笔记标识
 */
@property (nonatomic, copy) NSString *NoteKey;
/*!
 @property  直播间当前页码标识
 @brief 直播间当前页码标识
 */
@property (nonatomic, copy) NSString *BlockKey;
/*!
 @property  直播间当前设备类型
 @brief 直播间当前设备类型
 */
@property (nonatomic, copy) NSString *DeviceType;
/*!
 @property  直播间当前白板方向
 @brief 直播间当前白板方向
 */
@property (nonatomic, copy) NSString *IsHorizontal;
/*!
 @property  直播间当前页码信息集合字符串
 @brief 直播间当前页码信息集合字符串
 */
@property (nonatomic, copy) NSString *Blocks;
@end
