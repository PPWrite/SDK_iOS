//
//  RobotPenPoint.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RobotNote : NSObject
/*!
 @property
 @brief 笔记编号
 */
@property(nonatomic, assign) int NoteID;
/*!
 @property
 @brief 笔记唯一标识
 */
@property(nonatomic, copy) NSString *NoteKey;
/*!
 @property
 @brief 设备类型
 */
@property(nonatomic, assign) int DeviceType;
/*!
 @property
 @brief 笔记标题
 */
@property(nonatomic, copy) NSString *Title;
/*!
 @property
 @brief UserID
 */
@property(nonatomic, assign) long UserID;
/*!
 @property
 @brief 创建时间
 */
@property(nonatomic, assign) NSTimeInterval CreateTime;
/*!
 @property
 @brief 更新时间
 */
@property(nonatomic, assign) NSTimeInterval UpdateTime;
/*!
 @property
 @brief 横竖屏
 */
@property(nonatomic, assign) int IsHorizontal;


@end
