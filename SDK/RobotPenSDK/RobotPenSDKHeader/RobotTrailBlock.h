//
//  RobotTrailBlock.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//


#import <Foundation/Foundation.h>

@interface RobotTrailBlock : NSObject
/*!
 @property
 @brief BlockID
 */
@property (nonatomic, assign) int BlockID;
/*!
 @property
 @brief NoteKey
 */
@property (nonatomic, copy) NSString *NoteKey;
/*!
 @property
 @brief BlockKey
 */
@property (nonatomic, copy) NSString *BlockKey;
/*!
 @property
 @brief NextBlockKey
 */
@property (nonatomic, copy) NSString *NextBlockKey;
/*!
 @property
 @brief 创建时间
 */
@property (nonatomic, assign) NSTimeInterval CreateTime;
/*!
 @property
 @brief 更新时间
 */
@property (nonatomic, assign) NSTimeInterval UpdateTime;
/*!
 @property
 @brief 页码信息
 */
@property (nonatomic, assign) int PageNumber;
@end
