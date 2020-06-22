//
//  MoviesListView.h
//  RobotWhiteBoardDemo
//
//  Created by Caffrey on 2020/4/10.
//  Copyright © 2020 robot. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MoviesListView : UIView

@property (nonatomic, weak) UIViewController *superVC;

- (void)reload;

@end

NS_ASSUME_NONNULL_END
