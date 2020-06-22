//
//  RBTViewRecorder.h
//  RobotViewRecord
//
//  Created by Caffrey on 2020/4/10.
//  Copyright © 2020 robot. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
#endif

#import "RBTViewRecorderHeader.h"

NS_ASSUME_NONNULL_BEGIN


/// 录制完成的回调
typedef void (^RBTViewRecordedCallback)(NSString *);

/// 视图录制的管理类
/// **重要提示:** 在使用沙盒进行调试的时候,不要随意删除为录制而准备的文件夹, 轻易删除会导致崩溃。
@interface RBTViewRecorder : NSObject

/// 单例对象
+ (instancetype)shared;

/// 销毁shared单例对象
+ (void)destroy;

#if TARGET_OS_IPHONE
/// 开始录制
///
/// 录制视图：keyWindow
/// 视频宽高：整个屏幕
/// 音频录制：开启
/// 视频帧率：10
///
/// @param moviePath 录制的视频存放的路径，不可以传nil
/// @return 是否开启成功
- (NSError * _Nullable)startRecordSaveInPath:(NSString *)moviePath;
#endif

/// 开始录制
/// @param view 录制的视图
/// @param videoSize 录制视频的大小，width 最好为 16 的倍数。如果 width 不是 16 的倍数， SDK 内部会向上调整为 16 的倍数，来防止视频画面扭曲。
/// @param microphoneEnabled 是否开启音频录制，包括麦克风和扬声器录制
/// @param moviePath 录制的视频存放的路径，不可以传nil
/// @param frameRate 视频帧率
/// @return 是否开启成功
- (NSError * _Nullable)startRecordView:(RBT_VIEW_CLASS *)view
                             videoSize:(CGSize)videoSize
                     microphoneEnabled:(BOOL)microphoneEnabled
                            saveInPath:(NSString *)moviePath
                             frameRate:(RBTViewRecordFrameRate)frameRate;

/// 暂停录制
- (void)pauseRecord;

/// 继续录制
- (void)resumeRecord;

/// 结束录制
/// @param videoRecorded 录制完成的回调
- (void)stopRecord:(RBTViewRecordedCallback)videoRecorded;

@end

NS_ASSUME_NONNULL_END
