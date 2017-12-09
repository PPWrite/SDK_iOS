//
//  WhiteBoardLiveStudioViewController.h
//  RobotBoardSDKDemo
//
//  Created by JMS on 2017/11/30.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface WhiteBoardLiveStudioViewController : UIViewController
/** 用户ID*/
@property (nonatomic,copy) NSString *userIDStr;
/** 用户Session*/
@property (nonatomic,copy) NSString *userSessionStr;
/** 直播间ID*/
@property (nonatomic,copy) NSString *liveIDStr;
/** 房间密码*/
@property (nonatomic,copy) NSString *passwordStr;
@end
