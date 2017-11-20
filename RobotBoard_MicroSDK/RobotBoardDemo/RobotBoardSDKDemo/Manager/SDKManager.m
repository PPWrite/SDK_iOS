//
//  SDKManager.m
//  RobotBoardSDKDemo
//
//  Created by nb616 on 2017/11/14.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "SDKManager.h"
static SDKManager *_manager = nil;

@implementation SDKManager
+ (instancetype)share {
    
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        if (!_manager) {
            
            _manager = [[SDKManager alloc] init];
            
        }
    });
    return _manager;
}
@end
