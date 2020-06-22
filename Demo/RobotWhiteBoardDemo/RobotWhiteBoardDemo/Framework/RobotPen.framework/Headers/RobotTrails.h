//
//  RobotTrails.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//


#import <Foundation/Foundation.h>

@interface RobotTrails : NSObject
#if defined(__LP64__) && __LP64__
/*!
 @property
 @brief TrailID
 */
@property(nonatomic, assign) int TrailID;
/*!
 @property
 @brief Block
 */
@property(nonatomic, copy) NSString *Block;
/*!
 @property
 @brief 笔迹颜色
 */
@property(nonatomic, assign) long Color;
/*!
 @property
 @brief 笔迹数据
 */
@property(nonatomic, strong) NSArray *Data;
/*!
 @property
 @brief 设备类型 0:轨迹 1:图片
 */
@property(nonatomic, assign) int Type;
/*!
 @property
 @brief 图片模型key 和 翻页
 */
@property(nonatomic, copy) NSString *EXT;
/*!
 @property
 @brief UserID
 */
@property(nonatomic, assign) long UserID;
/*!
 @property
 @brief 创建时间
 */
@property(nonatomic, assign) long ST;
/*!
 @property
 @brief 更新时间
 */
@property(nonatomic, assign) long ET;


#else
/*!
 @property
 @brief TrailID
 */
@property (nonatomic, assign) int TrailID;
/*!
 @property
 @brief Block
 */
@property (nonatomic, copy) NSString *Block;
/*!
 @property
 @brief 笔迹颜色*
 */
@property (nonatomic, assign) long long Color;
/*!
 @property
 @brief 笔迹数据
 */
@property (nonatomic, strong) NSArray *Data;
/*!
 @property
 @brief 设备类型 0:轨迹 1:图片
 */
@property (nonatomic, assign) int Type;
/*!
 @property
 @brief  图片模型key 和 翻页
 */
@property (nonatomic, copy) NSString *EXT;
/*!
 @property
 @brief UserID
 */
@property (nonatomic, assign) long long UserID;
/*!
 @property
 @brief 创建时间
 */
@property (nonatomic, assign) long long ST;
/*!
 @property
 @brief 更新时间
 */
@property (nonatomic, assign) long long ET;

#endif


- (NSData *)getJSONOptions:(NSJSONWritingOptions)options error:(NSError **)error;

@end
