//
//  RBTSimpleWhiteboardView.h
//  RBTSimpleWhiteboardView
//
//  Created by Caffrey on 2020/4/14.
//  Copyright © 2020 robot. All rights reserved.
//

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
#endif

#import "RBTSimpleWhiteboardEnums.h"
#import "RBTSimpleWhiteboardViewDelegate.h"

NS_ASSUME_NONNULL_BEGIN

/// 默认画笔的ID。
extern NSString * const kRBTSimpleWhiteboardViewPenID;

/// 画布视图。
@interface RBTSimpleWhiteboardView : RBT_IMAGE_VIEW_CLASS

/// 回调 delegate。
@property (nonatomic, weak) id<RBTSimpleWhiteboardViewDelegate> delegate;

#pragma mark - 画布设置

/// 绘制队列。
/// 默认为非主线程串行队列。
@property (nonatomic, strong) dispatch_queue_t drawQueue;

/// 画布大小。
/// 画布越大占用内存越大，不建议频繁变动此值，会影响绘制效率。
@property (nonatomic, assign) CGSize drawSize;

/// 自动根据当前视图的 bounds.size 更新drawSize的值。
/// 默认为 YES。
/// 在为YES时，不建议频繁调整当前视图的大小，drawSize 会随之改动，会影响绘制效率。
@property (nonatomic, assign) BOOL autoUpdateDrawSize;

/// 绘制的图片的比例因子，必须是 >= 1 的整数。
///
/// 默认为UIScreen.mainScreen.scale。
/// UIScreen.mainScreen.scale 为 3 的设备上，将此值设置为 2 内存占用会降低 1 / 3，不过稍微有一点锯齿。
/// 不建议设置大于 UIScreen.mainScreen.scale 的值，会大大增加内存使用。
@property (nonatomic, assign) CGFloat drawScale;

/// 压力值的中位值。
///
/// 默认是 800。压力值 > medianPressure 时，绘制的 笔迹宽度 > _penWidth，反之亦然。
/// 注意：此值仅仅会影响没有笔锋的笔迹，比如isOpenStroke == NO时，或者 penWidth > autoCloseStrokeWidth时。
@property (nonatomic, assign) CGFloat medianPressure;

/// 开启笔锋。
///
/// 默认 true。
@property (nonatomic, assign) BOOL isOpenStroke;

/// 自动关闭笔锋的宽度值。
///
/// 笔迹越宽，笔锋处理可能丢失的点越多，所以设置一个宽度峰值，当 penWidth >= 此值时就自动不使用笔锋算法。
/// 默认为 3。
@property (nonatomic, assign) CGFloat autoCloseStrokeWidth;

/// 是否工作在横屏模式。
///
/// 默认是 NO。
@property (nonatomic, assign) BOOL isHorizontal;

#pragma mark - 默认的画笔设置

/// 默认画笔的颜色。
///
/// 默认为黑色。
@property (nonatomic, strong) RBT_COLOR_CLASS *penColor;

/// 默认画笔的宽度。
///
/// 默认为 1。这个宽度只是个基准宽度，绘制的宽度会根据点的压力值变化。
@property (nonatomic, assign) CGFloat penWidth;

/// 默认画笔的橡皮的宽度。
///
/// 默认为 黑色。
@property (nonatomic, assign) CGFloat eraserWidth;

/// 默认画笔是否工作在橡皮模式。
///
/// 默认 false。
@property (nonatomic, assign) BOOL isUseEraser;

/// 获取当前白板显示的Image。
///
/// 注意：请在主线程调用此方法。
///
/// @return 当前白板显示的Image。图片的size为 "当前视图的size *  UIScreen.mainScreen.scale / self.drawScale"，默认情况下 "UIScreen.mainScreen.scale == self.drawScale"，所以默认情况下图片 "size == 当前视图的size"。图片的 "scale == self.drawScale"。
- (nullable RBT_IMAGE_CLASS *)currentWhiteboardImage;

#pragma mark - 批量绘制方法

/// 开始批量绘制。
/// 当执行此方法后，'drawPoint' 和 'drawDevicePoint' 方法绘制的点都不会更新到界面上，直到‘endBatchDrawing’方法。
- (void)startBatchDrawing;

/// 结束批量绘制。
/// 和方法'startBatchDrawing'成对出现，执行此方法后，会将'startBatchDrawing'之后绘制的图像显示到界面上。
///
/// @param drawingDone 绘制结束的回调，因为在sdk内部，所有的绘制都在子线程移步绘制，所以调用此方法后不一定立刻结束绘制，而是子线程执行完成所有任务后才会结束绘制。
- (void)endBatchDrawing:( void(^ _Nullable)(void))drawingDone;

#pragma mark - 默认笔绘制方法

/// 使用默认画笔在白板上绘制点。
/// 笔迹宽度：penWidth 或者 eraserWidth。
/// 是否橡皮：使用画布的 isUseEraser。
/// @param point 点在视图中的坐标。
/// @param type 点的类型。
- (void)drawPoint:(CGPoint)point
        pointType:(RBTSWBPointType)type;

/// 使用默认画笔在白板上绘制点，并可以设置当前点的宽度。
/// 笔迹宽度：使用自定义点的宽度，忽略 penWidth / eraserWidth。
/// 是否橡皮：使用画布的 isUseEraser。
/// @param point 点在视图中的坐标。
/// @param width 点的宽度。
/// @param type 点的类型。
- (void)drawPoint:(CGPoint)point
            width:(float)width
        pointType:(RBTSWBPointType)type;

/// 使用默认画笔在白板上绘制设备上报的点。
/// 笔迹宽度：非橡皮点基于 pressure 和 penWidth 计算，橡皮点宽度 eraserWidth。
/// 是否橡皮：使用画布的 isUseEraser。
/// @param point 点在硬件上的坐标。
/// @param pressure 压力值，范围 0 ～ 1024，这个值会影响笔迹宽度。
/// @param type 点的类型。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
- (void)drawDevicePoint:(CGPoint)point
               pressure:(float)pressure
              pointType:(RBTSWBPointType)type
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate;

/// 使用默认画笔在白板上绘制设备上报的点，并可以传入距离上一个点的时间间隔来优化绘制。
/// 笔迹宽度：非橡皮点基于 pressure 和 penWidth 计算，橡皮点宽度 eraserWidth。
/// 是否橡皮：使用画布的 isUseEraser。
/// @param point 点在硬件上的坐标。
/// @param pressure 压力值，范围 0 ～ 1024，这个值会影响笔迹宽度。
/// @param type 点的类型。
/// @param intervalTime 点的时间间隔。传入此值可以帮助画布判断此点是否是不正常的飞点。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
- (void)drawDevicePoint:(CGPoint)point
               pressure:(float)pressure
              pointType:(RBTSWBPointType)type
      pointIntervalTime:(int)intervalTime
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate;

/// 使用默认画笔在白板上绘制设备上报的点。
/// 笔迹宽度：非橡皮点基于 pressure 和 penWidth 计算，橡皮点宽度 eraserWidth。
/// 是否橡皮：根据本方法的 status 参数判断，status == 0x30 || status == 0x31。
/// @param point 点在硬件上的坐标。
/// @param pressure 压力值，范围 0 ～ 1024，这个值会影响笔迹宽度。
/// @param status 点的状态。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
- (void)drawDevicePoint:(CGPoint)point
               pressure:(float)pressure
            pointStatus:(int)status
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate;

/// 使用默认画笔在白板上绘制设备上报的点，并可以传入距离上一个点的时间间隔来优化绘制。
/// 笔迹宽度：非橡皮点基于 pressure 和 penWidth 计算，橡皮点宽度 eraserWidth。
/// 是否橡皮：根据本方法的 status 参数判断，status == 0x30 || status == 0x31。
/// @param point 点在硬件上的坐标。
/// @param pressure 压力值，范围 0 ～ 1024，这个值会影响笔迹宽度。
/// @param status 点的状态。
/// @param intervalTime 点的时间间隔，传入此值可以帮助画布判断此点是否是不正常的飞点。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
- (void)drawDevicePoint:(CGPoint)point
               pressure:(float)pressure
            pointStatus:(int)status
      pointIntervalTime:(int)intervalTime
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate;


/// 使用默认画笔绘制已知宽度的设备点。
/// @param point 点。
/// @param width 点的宽度。
/// @param status 点的状态，如果值为 0x30 或者 0x31 代表是当前使用的是橡皮。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
- (void)drawDevicePoint:(CGPoint)point
             pointWidth:(float)width
            pointStatus:(int)status
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate;

#pragma mark - 自定义笔绘制方法

/// 使用自定义的笔在白板上绘制点。
/// @param point 点在视图中的坐标。
/// @param eraser 是否是橡皮。
/// @param type 点的类型。
/// @param width 点的宽度。
/// @param color 点的颜色。
/// @param penID 笔的ID。
- (void)drawPoint:(CGPoint)point
           eraser:(BOOL)eraser
        pointType:(RBTSWBPointType)type
       pointWidth:(float)width
       pointColor:(RBT_COLOR_CLASS *)color
            penID:(NSString *)penID;

/// 使用自定义的笔在白板上绘制设备上报的点。
/// @param point 点在硬件上的坐标。
/// @param pressure 点的压力。
/// @param eraser 是否是橡皮。
/// @param type 点的状态。
/// @param penWidth 笔的宽度，非橡皮点绘制时实际的宽度是根据 pressure 和 penWidth计算；橡皮点宽度 就是 penWidth。
/// @param penColor 笔的颜色，非橡皮点绘制时使用；橡皮点会直接绘制透明色。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
/// @param penID 笔的ID。
- (void)drawDevicePoint:(CGPoint)point
               pressure:(float)pressure
                 eraser:(BOOL)eraser
              pointType:(RBTSWBPointType)type
               penWidth:(float)penWidth
               penColor:(RBT_COLOR_CLASS *)penColor
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate
                  penID:(NSString *)penID;

/// 使用自定义的笔在白板上绘制设备上报的点。
/// @param point 点在硬件上的坐标。
/// @param pressure 点的压力。
/// @param eraser 是否是橡皮。
/// @param type 点的状态。
/// @param intervalTime 点的时间间隔，传入此值可以帮助画布判断此点是否是不正常的飞点。
/// @param penWidth 笔的宽度，非橡皮点绘制时实际的宽度是根据 pressure 和 penWidth计算；橡皮点宽度 就是 penWidth。
/// @param penColor 笔的颜色，非橡皮点绘制时使用；橡皮点会直接绘制透明色。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
/// @param penID 笔的ID。
- (void)drawDevicePoint:(CGPoint)point
               pressure:(float)pressure
                 eraser:(BOOL)eraser
              pointType:(RBTSWBPointType)type
      pointIntervalTime:(int)intervalTime
               penWidth:(float)penWidth
               penColor:(RBT_COLOR_CLASS *)penColor
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate
                  penID:(NSString *)penID;

/// 使用自定义的笔在白板上绘制设备上报的原始状态点。
/// @param point 点在硬件上的坐标。
/// @param pressure 点的压力。
/// @param status 点的状态，如果值为 0x30 或者 0x31 代表是当前使用的是橡皮。
/// @param penWidth 笔的宽度，非橡皮点绘制时实际的宽度是根据 pressure 和 penWidth计算；橡皮点宽度 就是 penWidth。
/// @param penColor 笔的颜色，非橡皮点绘制时使用；橡皮点会直接绘制透明色。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
/// @param penID 笔的ID。
- (void)drawDevicePoint:(CGPoint)point
               pressure:(float)pressure
            pointStatus:(int)status
               penWidth:(float)penWidth
               penColor:(RBT_COLOR_CLASS *)penColor
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate
                  penID:(NSString *)penID;

/// 使用自定义的笔在白板上绘制设备上报的原始状态点。
/// @param point 点在硬件上的坐标。
/// @param pressure 点的压力。
/// @param status 点的状态，如果值为 0x30 或者 0x31 代表是当前使用的是橡皮。
/// @param intervalTime 点的时间间隔。传入此值可以帮助画布判断此点是否是不正常的飞点。
/// @param penWidth 笔的宽度，非橡皮点绘制时实际的宽度是根据 pressure 和 penWidth计算；橡皮点宽度 就是 penWidth。
/// @param penColor 笔的颜色，非橡皮点绘制时使用；橡皮点会直接绘制透明色。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
/// @param penID 笔的ID。
- (void)drawDevicePoint:(CGPoint)point
               pressure:(float)pressure
            pointStatus:(int)status
      pointIntervalTime:(int)intervalTime
               penWidth:(float)penWidth
               penColor:(RBT_COLOR_CLASS *)penColor
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate
                  penID:(NSString *)penID;

/// 使用自定义笔绘制已知宽度的设备点。
/// 笔迹宽度：根据方法 width 参数决定。
/// 是否橡皮：根据本方法的 status 参数判断，status == 0x30 || status == 0x31。
/// @param point 点。
/// @param width 点的宽度。
/// @param status 点的状态，如果值为 0x30 或者 0x31 代表是当前使用的是橡皮。
/// @param penColor 笔的颜色，非橡皮点绘制时使用；橡皮点会直接绘制透明色。
/// @param deviceSize 点所属的设备的大小。
/// @param deviceCoordinate 点所属的设备的坐标类型。
/// @param penID 笔的ID。
- (void)drawDevicePoint:(CGPoint)point
             pointWidth:(float)width
            pointStatus:(int)status
               penColor:(CGColorRef)penColor
             deviceSize:(CGSize)deviceSize
       deviceCoordinate:(RBTSWBDeviceCoordinateType)deviceCoordinate
                  penID:(NSString *)penID;

/// 清理白板
- (void)clear;

@end

NS_ASSUME_NONNULL_END
