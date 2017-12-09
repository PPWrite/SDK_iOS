//
//  RobotLiveTrails.h
//  PPWrite
//
//  Created by JMS on 2017/11/1.
//  Copyright © 2017年 Robot. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface RobotLiveTrails : NSObject
#if defined(__LP64__) && __LP64__
/** UserID*/
@property (nonatomic, assign)int user;
/** Block*/
@property (nonatomic, copy)NSString *block;
/** 笔迹颜色*/
@property (nonatomic, assign)int color;
/** 设备类型 0:轨迹 1:图片*/
@property (nonatomic, assign) int type;
/** 笔迹数据*/
@property (nonatomic, strong)NSArray *data;
/** 创建时间*/
@property (nonatomic, assign)double start_at;
/** 更新时间*/
@property (nonatomic, assign)double end_at;
/** 图片模型key 和 翻页|*/
@property (nonatomic, copy)NSString *ext;
/** TrailID*/
@property (nonatomic, assign)int trailid;


#else
/** UserID*/
@property (nonatomic, assign)int user;
/** Block*/
@property (nonatomic, copy)NSString *block;
/** 笔迹颜色*/
@property (nonatomic, assign)int color;
/** 设备类型 0:轨迹 1:图片*/
@property (nonatomic, assign) int type;
/** 笔迹数据*/
@property (nonatomic, strong)NSArray *data;
/** 创建时间*/
@property (nonatomic, assign)double start_at;
/** 更新时间*/
@property (nonatomic, assign)double end_at;
/** 图片模型key 和 翻页|*/
@property (nonatomic, copy)NSString *ext;
/** TrailID*/
@property (nonatomic, assign)int trailid;

#endif



- (NSData*)getJSONOptions:(NSJSONWritingOptions)options error:(NSError**)error;


@end
