//
//  MoviesListView.m
//  RobotWhiteBoardDemo
//
//  Created by Caffrey on 2020/4/10.
//  Copyright © 2020 robot. All rights reserved.
//

#import "MoviesListView.h"
#import <AVKit/AVKit.h>

@interface MoviesListView()<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) UITableView *tableView;

@property (nonatomic, strong) NSMutableArray<NSDictionary *> *files;

@end

@implementation MoviesListView

- (instancetype)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (self) {
        [self setupView];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setupView];
    }
    return self;
}

- (void)setupView {
    self.tableView = [[UITableView alloc] initWithFrame:self.bounds style:UITableViewStylePlain];
    [self addSubview:self.tableView];

    self.tableView.rowHeight = 40;
    self.tableView.delegate = self;
    self.tableView.dataSource = self;

    self.tableView.layer.cornerRadius = 15;
    self.tableView.clipsToBounds = YES;

    self.files = [NSMutableArray array];

    self.layer.cornerRadius = 15;

    self.layer.shadowColor = UIColor.blackColor.CGColor;
    self.layer.shadowOpacity = 0.3;
    self.layer.shadowRadius = 5;
    self.layer.shadowOffset = CGSizeMake(0, 2);
}

- (void)layoutSubviews {
    [super layoutSubviews];
    self.tableView.frame = self.bounds;
}

- (void)reload {
    [self.files removeAllObjects];

    NSString *path = NSTemporaryDirectory();

    NSFileManager *fileManager = NSFileManager.defaultManager;
    NSArray<NSString *> *subpaths = [fileManager subpathsAtPath:path];

    for (NSString *subpath in subpaths) {
        if (![subpath containsString:@"mp4"]) {
            continue;
        }

        NSString *fillPath = [path stringByAppendingPathComponent:subpath];
        NSDictionary<NSFileAttributeKey, id> *fileAttributes = [fileManager attributesOfItemAtPath:fillPath error:nil];

        if (fileAttributes) {
            NSMutableDictionary *tmpdic = [fileAttributes mutableCopy];
            tmpdic[@"file_subpath"] = subpath;
            [self.files addObject:tmpdic];
        }
    }

    [self.files sortUsingComparator:^NSComparisonResult(NSDictionary *obj1, NSDictionary *obj2) {
        NSDate *date1 = (NSDate *)obj1[NSFileCreationDate];
        NSDate *date2 = (NSDate *)obj2[NSFileCreationDate];
        NSTimeInterval timeInterval = [date1 timeIntervalSinceDate:date2];
        if (timeInterval > 0) {
            return NSOrderedAscending;
        } else if (timeInterval < 0) {
            return NSOrderedDescending;
        } else {
            return NSOrderedSame;
        }
    }];

    [self.tableView reloadData];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.files.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [[UITableViewCell alloc] init];
    NSDictionary *fileinfo = self.files[indexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"%@: %.2fMB", fileinfo[@"file_subpath"], [fileinfo[NSFileSize] floatValue]/1024/1024];
    cell.textLabel.textAlignment = NSTextAlignmentCenter;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *fillPath = [NSTemporaryDirectory() stringByAppendingPathComponent:self.files[indexPath.row][@"file_subpath"]];

    AVPlayerViewController *playVC = [[AVPlayerViewController alloc] init];
    playVC.player = [AVPlayer playerWithURL:[NSURL fileURLWithPath:fillPath]];

    [self.superVC presentViewController:playVC animated:YES completion:nil];
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *fillPath = [NSTemporaryDirectory() stringByAppendingPathComponent:self.files[indexPath.row][@"file_subpath"]];

    __weak typeof(self) wself = self;
    UITableViewRowAction *delAction = [UITableViewRowAction rowActionWithStyle:UITableViewRowActionStyleDefault title:@"删除" handler:^(UITableViewRowAction * _Nonnull action, NSIndexPath * _Nonnull indexPath) {
        [NSFileManager.defaultManager removeItemAtPath:fillPath error:NULL];
        [wself.files removeObjectAtIndex:indexPath.row];
        [wself.tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
        if (wself.files.count == 0) {
            wself.hidden = YES;
        }
    }];

    UITableViewRowAction *shareAction = [UITableViewRowAction rowActionWithStyle:UITableViewRowActionStyleNormal title:@"分享" handler:^(UITableViewRowAction * _Nonnull action, NSIndexPath * _Nonnull indexPath) {

        UIActivityViewController *activityVC = [[UIActivityViewController alloc] initWithActivityItems:@[[NSURL fileURLWithPath:fillPath]] applicationActivities:nil];

        [wself.superVC presentViewController:activityVC animated:YES completion:nil];
    }];


    return @[delAction, shareAction];
}
#pragma clang diagnostic pop
@end
