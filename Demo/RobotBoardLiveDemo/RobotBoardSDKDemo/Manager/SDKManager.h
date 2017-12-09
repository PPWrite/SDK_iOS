//
//  SDKManager.h
//  RobotBoardSDKDemo
//
//  Created by nb616 on 2017/11/14.
//  Copyright © 2017年 JMS. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "RobotPenManager.h"
#import "RobotPenDevice+Category.h"

@interface SDKManager : NSObject

+ (instancetype)share;

@property (nonatomic, strong) RobotPenDevice *device;

@end






