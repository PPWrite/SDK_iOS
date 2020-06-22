//
//  RBTSimpleWhiteboardEnums.h
//  RBTSimpleWhiteboardEnums
//
//  Created by Caffrey on 2020/4/14.
//  Copyright © 2020 robot. All rights reserved.
//

#ifndef RBTSimpleWhiteboardEnums_h
#define RBTSimpleWhiteboardEnums_h

#if TARGET_OS_IPHONE

#define RBT_COLOR_CLASS UIColor
#define RBT_IMAGE_CLASS UIImage
#define RBT_IMAGE_VIEW_CLASS UIImageView

#elif TARGET_OS_MAC

#define RBT_COLOR_CLASS NSColor
#define RBT_IMAGE_CLASS NSImage
#define RBT_IMAGE_VIEW_CLASS NSImageView

#endif

/// 坐标系类型
typedef NS_ENUM(int, RBTSWBDeviceCoordinateType) {
    /** 左上角为坐标原点 */
    RBTSWBDeviceCoordinateUpperLeft = 1,
    /** 左下角为坐标原点 */
    RBTSWBDeviceCoordinateLowerLeft,
    /** 右上角为坐标原点 */
    RBTSWBDeviceCoordinateUpperRight,
    /** 右下角为坐标原点 */
    RBTSWBDeviceCoordinateLowerRight,
};

/// 绘制的点的类型
typedef NS_ENUM(int, RBTSWBPointType) {
    /** 悬浮点，在使用手写版硬件时使用 */
    RBTSWBPointTypeSuspend = 0,
    /** 开始点 */
    RBTSWBPointTypeBegan,
    /** 移动点 */
    RBTSWBPointTypeMoved,
    /** 结束点 */
    RBTSWBPointTypeEnded,
    /** 离开感应范围点，在使用手写版硬件时使用 */
    RBTSWBPointTypeLeave,
};

#endif /* RBTSimpleWhiteboardEnums_h */
