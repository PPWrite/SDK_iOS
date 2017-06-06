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
/** TrailID*/
@property (nonatomic, assign)int TrailID;
/** 图片模型key 和 翻页|*/
@property (nonatomic, copy)NSString *EXT;
/** Block*/
@property (nonatomic, copy)NSString *Block;
/** 笔迹颜色*/
@property (nonatomic, assign)long Color;
/** UserID*/
@property (nonatomic, assign)long UserID;
/** 创建时间*/
@property (nonatomic, assign)long ST;
/** 更新时间*/
@property (nonatomic, assign)long  ET;
/** 笔迹数据*/
@property (nonatomic, strong)NSArray *Data;
/** 设备类型 0:轨迹 1:图片*/
@property (nonatomic, assign) int Type;


#else
/** TrailID*/
@property (nonatomic, assign)int TrailID;
/** 图片模型key 和 翻页|*/
@property (nonatomic, copy)NSString *EXT;
/** Block*/
@property (nonatomic, copy)NSString *Block;
/** 笔迹颜色*/
@property (nonatomic, assign)long long Color;
/** UserID*/
@property (nonatomic, assign)long long UserID;
/** 创建时间*/
@property (nonatomic, assign)long long ST;
/** 更新时间*/
@property (nonatomic, assign)long long ET;
/** 笔迹数据*/
@property (nonatomic, strong)NSArray *Data;
/** 设备类型 0:轨迹 1:图片*/
@property (nonatomic, assign) int Type;

#endif



- (NSData*)getJSONOptions:(NSJSONWritingOptions)options error:(NSError**)error;

@end
