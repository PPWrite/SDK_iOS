//
//  RobotPenDevice+Category.m
//  RobotBoardSDKDemo
//
//  Created by nb616 on 2017/11/14.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "RobotPenDevice+Category.h"
#import <objc/runtime.h>
static char *isUpdate = "isUpdate";
static char *isNoteNumer = "isNoteNumer";
@implementation RobotPenDevice (Category)

- (void)setSWStrIsUpdate:(BOOL)SWStrIsUpdate {
    NSString *s = [NSString stringWithFormat:@"%d",SWStrIsUpdate];
    objc_setAssociatedObject(self, isUpdate, s, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

- (BOOL)SWStrIsUpdate {
    return [objc_getAssociatedObject(self, isUpdate) intValue];
}

- (void)setAllNoteNumers:(int)allNoteNumers {
    NSString *s = [NSString stringWithFormat:@"%d",allNoteNumers];
    objc_setAssociatedObject(self, isNoteNumer, s, OBJC_ASSOCIATION_COPY_NONATOMIC);
}
- (int)allNoteNumers {
    return [objc_getAssociatedObject(self, isNoteNumer) intValue];
}


@end
