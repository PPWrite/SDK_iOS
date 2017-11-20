//
//  RobotVideoImage.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RobotVideoImage : NSObject
/*!
 @property
 @brief 图片数据
 */
@property (nonatomic, assign) unsigned char *imageData;
/*!
 @property
 @brief Yuv数据
 */
@property (nonatomic, assign) uint8_t **YuvData;
@end

