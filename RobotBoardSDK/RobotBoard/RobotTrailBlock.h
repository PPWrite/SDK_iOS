//
//  RobotTrailBlock.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//


#import <Foundation/Foundation.h>

@interface RobotTrailBlock : NSObject
/** BlockID*/
@property (nonatomic, assign) int BlockID;
/** NoteKey*/
@property (nonatomic, copy) NSString *NoteKey;
/** BlockKey*/
@property (nonatomic, copy) NSString *BlockKey;
/** NextBlockKey*/
@property (nonatomic, copy) NSString *NextBlockKey;
/** 创建时间*/
@property (nonatomic, assign)NSTimeInterval CreateTime;
/** 更新时间*/
@property (nonatomic, assign)NSTimeInterval UpdateTime;

@end
