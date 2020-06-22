//
//  RBTViewRecorderHeader.h
//  RobotViewRecord
//
//  Created by Caffrey on 2020/4/22.
//  Copyright © 2020 robot. All rights reserved.
//

#ifndef RBTViewRecorderHeader_h
#define RBTViewRecorderHeader_h


#if TARGET_OS_IPHONE

#ifndef RBT_COLOR_CLASS
#define RBT_COLOR_CLASS UIColor
#endif

#ifndef RBT_IMAGE_CLASS
#define RBT_IMAGE_CLASS UIImage
#endif

#ifndef RBT_VIEW_CLASS
#define RBT_VIEW_CLASS UIView
#endif


#elif TARGET_OS_MAC

#ifndef RBT_COLOR_CLASS
#define RBT_COLOR_CLASS NSColor
#endif

#ifndef RBT_IMAGE_CLASS
#define RBT_IMAGE_CLASS NSImage
#endif

#ifndef RBT_VIEW_CLASS
#define RBT_VIEW_CLASS NSView
#endif

#endif


/// 视频录制的帧率
typedef NS_ENUM(NSInteger, RBTViewRecordFrameRate) {
    /// 每秒 5 帧
    RBTViewRecordFrameRate5 = 5,
    /// 每秒 10 帧  (在模拟器上如果高于这个值,就会导致视频帧写入失败,因为mac跑起来很卡卡,真机可以运行.)
    RBTViewRecordFrameRate10 = 10,
    /// 每秒 15 帧
    RBTViewRecordFrameRate15 = 15,
    /// 每秒 20 帧
    RBTViewRecordFrameRate20 = 20,
    /// 每秒 25 帧
    RBTViewRecordFrameRate25 = 25,
    /// 每秒 30 帧
    RBTViewRecordFrameRate30 = 30,
};

/// 开始录制的错误码
typedef NS_ENUM(NSUInteger, RBTVRStartErrorCode) {
    /// 路径错误
    RBTVRStartErrorCodeWrongPath = 10000,
    /// 文件夹不存在
    RBTVRStartErrorCodeInexistentDir = 10001,
    /// 文件已经存在
    RBTVRStartErrorCodeExistentFile = 10002,
    /// 已在录制中
    RBTVRStartErrorCodeStarted = 20000,
    /// 视频宽/高为零
    RBTVRStartErrorCodeWrongVideoSize = 30000,
    /// 音频录制初始化错误
    RBTVRStartErrorCodeAudioInitErr = 40000,
    /// 没有录制音频的权限
    RBTVRStartErrorCodeNoAudioAuthorization = 40001,
};


#endif /* RBTViewRecorderHeader_h */
