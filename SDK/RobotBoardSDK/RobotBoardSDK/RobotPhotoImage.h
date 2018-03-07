//
//  RobotPhotoImage.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface RobotPhotoImage : NSObject
/*!
 @property
 @brief 附加信息
 */
@property (nonatomic, copy) NSString *Ext;
/*!
 @property
 @brief blockKey
 */
@property (nonatomic, copy) NSString * blockKey;
/*!
 @property
 @brief Image
 */
@property (nonatomic, strong) UIImage *Image;

/*!
 @method
 @abstract 根据Data获取图片
 @param data 数据
 @result 图片
 */
+ (RobotPhotoImage *)ImageWithData:(NSData *)data;

/*!
 @method
 @abstract 根据路径获取图片
 @param path 路径
 @result 图片
 */
+ (RobotPhotoImage *)ImageWithContentsOfFile:(NSString *)path;

@end

