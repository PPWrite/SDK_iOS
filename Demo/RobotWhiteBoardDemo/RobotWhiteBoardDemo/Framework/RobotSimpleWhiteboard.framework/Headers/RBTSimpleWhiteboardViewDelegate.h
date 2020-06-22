//
//  RBTSimpleWhiteboardViewDelegate.h
//  RobotWhiteBoardDemo
//
//  Created by Caffrey on 2020/6/5.
//  Copyright © 2020 robot. All rights reserved.
//

#ifndef RBTSimpleWhiteboardViewDelegate_h
#define RBTSimpleWhiteboardViewDelegate_h

#import <Foundation/Foundation.h>
#import "RBTSimpleWhiteboardEnums.h"

@class RBTSimpleWhiteboardView;

@protocol RBTSimpleWhiteboardViewDelegate <NSObject>

@optional

/// 画布收到了优化点。
///
/// 注意：不要在这个回调里面做耗时操作，会影响绘制效率
/// 注意：此回调不一定在主线程
///
/// @param wbView 画布
/// @param x 点 x 坐标
/// @param y 点 y 坐标
/// @param width 点的宽度
/// @param speed 点的速度
/// @param status 点的状态
/// @param type 点的类型，此值是根据status生成的。可以选择使用status也可以选择使用type。
/// @param penID 当前点对应的笔的ID
- (void)rbtSimpleWhiteboardView:(RBTSimpleWhiteboardView *)wbView
             didReceiptedPointX:(float)x
                         pointY:(float)y
                          width:(float)width
                          speed:(float)speed
                         status:(int)status
                           type:(RBTSWBPointType)type
                          penID:(NSString *)penID;

@end

#endif /* RBTSimpleWhiteboardViewDelegate_h */
