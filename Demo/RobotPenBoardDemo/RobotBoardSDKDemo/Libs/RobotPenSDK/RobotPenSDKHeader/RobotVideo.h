//
//  RobotVideo.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RobotVideo : NSObject
/*!
 @property
 @brief NameKey
 */
@property (nonatomic, copy) NSString *NameKey;
/*!
 @property
 @brief 视频标题
 */
@property (nonatomic, copy) NSString *Alias;
/*!
 @property
 @brief 视频大小
 */
@property (nonatomic, assign) long long Size;
/*!
 @property
 @brief 视频长度
 */
@property (nonatomic, assign) long Length;
/*!
 @property
 @brief 视频标识
 */
@property (nonatomic, assign) BOOL IsOnLine;
/*!
 @property
 @brief 视频唯一标识（MD5）
 */
@property (nonatomic, copy) NSString *Md5Str;
@end
