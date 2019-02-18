//
//  RobotWhiteBoard_MicroView.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "RobotWhiteBoardView.h"

@interface RobotWhiteBoard_MicroView : RobotWhiteBoardView
/*!
 @method
 @abstract 检查是否可以录制
 @result 返回结果
 */
- (BOOL)GetIsVoiceEnable;
/*!
 @method
 @abstract 开始录制
 */
- (void)StartVideoRecord;
/*!
 @method
 @abstract 结束录制
 */
- (void)EndVideoRecord;
/*!
 @method
 @abstract 暂停录制
 */
- (void)PauseVideoRecord;
/*!
 @method
 @abstract 继续录制
 */
- (void)ContinueVideoRecord;
/*!
 @method
 @abstract 取消录制
 */
- (void)CancelVideoRecord;


@end

