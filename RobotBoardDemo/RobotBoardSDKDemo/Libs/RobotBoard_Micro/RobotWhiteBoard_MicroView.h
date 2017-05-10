//
//  RobotWhiteBoard_MicroView.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "RobotWhiteBoardView.h"

@interface RobotWhiteBoard_MicroView : RobotWhiteBoardView
/** 检查是否可以录制*/
- (BOOL)GetIsVoiceEnable;
/** 开始录制*/
- (void)StartVideoRecord;
/** 结束录制*/
- (void)EndVideoRecord;
/** 暂停录制*/
- (void)PauseVideoRecord;
/** 继续录制 */
- (void)ContinueVideoRecord;
/** 取消录制*/
- (void)CancelVideoRecord;
/** 发送录制状态及信息*/
- (void)SendStateInfo:(NSDictionary *)StateInfo;



@end
