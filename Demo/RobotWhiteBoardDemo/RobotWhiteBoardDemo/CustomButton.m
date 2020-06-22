//
//  CustomButton.m
//  RobotWhiteBoardDemo
//
//  Created by Caffrey on 2020/4/10.
//  Copyright © 2020 robot. All rights reserved.
//

#import "CustomButton.h"

@implementation CustomButton

- (instancetype)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (self) {
        [self setupStyle];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setupStyle];
    }
    return self;
}

- (void)setupStyle {
    self.cornerRadius = 10;

    self.layer.shadowColor = UIColor.blackColor.CGColor;
    self.layer.shadowOpacity = 0.3;
    self.layer.shadowRadius = 5;
    self.layer.shadowOffset = CGSizeMake(0, 2);
}

- (void)setCornerRadius:(CGFloat)cornerRadius {
    self.layer.cornerRadius = cornerRadius;
}

- (CGFloat)cornerRadius {
    return self.layer.cornerRadius;
}

@end
