//
//  RobotLiveStudioModel.h
//  PPWrite
//
//  Created by JMS on 2017/11/23.
//  Copyright © 2017年 Robot. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @class 直播间信息模型
 @abstract 直播间信息模型
 */
@interface RobotLiveStudioModel : NSObject
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
 @property  主播UserID
 @brief 主播UserID
 */
@property (nonatomic, copy) NSString *UserID;
/*!
 @property  语音权限
 @brief 语音权限
 */
@property (nonatomic, assign) NSString *IsSpeak;
/*!
 @property  输写权限
 @brief 输写权限
 */
@property (nonatomic, assign) NSString *IsWrite;
/*!
 @property  直播间笔记标识
 @brief 直播间笔记标识
 */
@property (nonatomic, copy) NSString *NoteKey;
/*!
 @property  直播间当前页码标识
 @brief 直播间当前页码标识
 */
@property (nonatomic, copy) NSString *Block;
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
 @property  直播间当前页码信息集合
 @brief 直播间当前页码信息集合
 */
@property (nonatomic, copy) NSArray *Blocks;



/*!
 @property  直播间标签
 @brief 直播间标签
 */
@property (nonatomic, copy) NSArray *Tags;


/*!
 @property  直播间封面
 @brief 直播间封面
 */
@property (nonatomic, copy) NSString *Cover;
/*!
 @property  直播间评论
 @brief 直播间评论
 */
@property (nonatomic, copy) NSString *IsComment;
/*!
 @property  直播间是否加密
 @brief 直播间是否加密，1为加密
 */
@property (nonatomic, copy) NSString *IsEncrypt;
/*!
 @property  直播间耗时
 @brief 直播间耗时
 */
@property (nonatomic, copy) NSString *LiveHour;
/*!
 @property  直播间点赞数
 @brief 直播间点赞数
 */
@property (nonatomic, copy) NSString *LiveLike;
/*!
 @property  直播间名称
 @brief 直播间点名称
 */
@property (nonatomic, copy) NSString *Name;
/*!
 @property  直播间最后更改时间
 @brief 直播间最后更改时间
 */
@property (nonatomic, copy) NSString *UpdateTime;
/*!
 @property  直播间创建者信息
 @brief 直播间创建者信息
 */
@property (nonatomic, copy) NSDictionary *User;

/*!
 @property  直播间标识
 @brief 直播间标识
 */
@property (nonatomic, copy) NSString *Online;

/*!
 @property  直播间简介
 @brief 直播间简介
 */
@property (nonatomic, copy) NSString *About;



@end
