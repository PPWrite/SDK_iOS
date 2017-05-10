//
//  RobotPhotoImageView.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RobotPhotoImage.h"

@interface RobotPhotoImageView : UIImageView

/** 是否可以编辑*/
@property (nonatomic, assign) int enbleEdit;
/** 图片*/
@property (nonatomic, strong)RobotPhotoImage *photo;


/**
 设置编辑状态
 
 @param enbleEdit 是否可以编辑
 */
- (void)setEditMode:(BOOL)enbleEdit;

/**
 设置编辑框的颜色，默认为透明

 @param color 颜色
 @param isshow 是否显示编辑框
 */
-(void)setLayerColor:(UIColor *)color andIsShowLayer:(BOOL)isshow;

@end
