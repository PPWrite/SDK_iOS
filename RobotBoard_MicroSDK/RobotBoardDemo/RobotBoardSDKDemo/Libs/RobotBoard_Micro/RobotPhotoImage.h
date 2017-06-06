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
/** 附加信息*/
@property (nonatomic, copy)NSString *Ext;
/** blockKey*/
@property (nonatomic, copy)NSString * blockKey;
/** Image*/
@property (nonatomic, strong) UIImage *Image;


/**
 根据Data获取图片

 @param data data
 @return 图片
 */
+ (RobotPhotoImage *)ImageWithData:(NSData *)data;

/**
 根据路径获取图片

 @param path 路径
 @return 图片
 */
+ (RobotPhotoImage *)ImageWithContentsOfFile:(NSString *)path;

@end
