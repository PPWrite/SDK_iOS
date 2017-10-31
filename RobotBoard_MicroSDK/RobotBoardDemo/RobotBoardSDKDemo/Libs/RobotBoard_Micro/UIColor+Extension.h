//
//  UIColor+Extension.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIColor (Extension)

+ (int)getARGBIntWithColor:(UIColor *)color;

+ (UIColor *)getColorWithARGBInt:(int)intColor;

@end
