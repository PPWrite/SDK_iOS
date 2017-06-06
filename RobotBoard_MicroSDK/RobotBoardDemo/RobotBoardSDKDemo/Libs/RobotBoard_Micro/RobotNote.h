//
//  RobotPenPoint.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RobotNote : NSObject
/** NoteID*/
@property (nonatomic, assign) int NoteID;
/** NoteKey*/
@property (nonatomic, copy) NSString *NoteKey;
/** 设备类型*/
@property (nonatomic, assign) int DeviceType;
/** 笔记标题*/
@property (nonatomic, copy) NSString *Title;
/** UserID*/
@property (nonatomic, assign) long UserID;
/** 创建时间*/
@property (nonatomic, assign) NSTimeInterval CreateTime;
/** 更新时间*/
@property (nonatomic, assign) NSTimeInterval UpdateTime;
/** 横竖屏*/
@property (nonatomic, assign) int  IsHorizontal;


@end
