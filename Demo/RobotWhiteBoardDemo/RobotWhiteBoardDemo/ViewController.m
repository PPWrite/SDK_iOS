//
//  ViewController.m
//  RobotWhiteBoardDemo
//
//  Created by Caffrey on 2020/4/7.
//  Copyright © 2020 robot. All rights reserved.
//

#import "ViewController.h"
#import <RobotPen/RobotPen.h>
#ifdef DEBUG
#import <DoraemonKit/DoraemonManager.h>
#endif

#define SCREEN_WIDTH self.view.bounds.size.width
#define SCREEN_HEIGHT self.view.bounds.size.height

@interface ViewController ()<RobotPenDelegate,UITableViewDelegate,UITableViewDataSource>

@property (weak, nonatomic) IBOutlet UILabel *xValue;//x坐标
@property (weak, nonatomic) IBOutlet UILabel *yValue;//y坐标
@property (weak, nonatomic) IBOutlet UILabel *pressureLabel;//压感值
@property (weak, nonatomic) IBOutlet UILabel *routeLabel;//笔的状态
@property (weak, nonatomic) IBOutlet UILabel *deviceUUID;//设备UUID
@property (weak, nonatomic) IBOutlet UILabel *deviceName;//设备名称
@property (weak, nonatomic) IBOutlet UITableView *tableView;//设备列表
@property (weak, nonatomic) IBOutlet UIButton *blueToothButton;//搜索设备按钮
@property (weak, nonatomic) IBOutlet UILabel *SyncNumberLabel;//同步笔记个数
@property (weak, nonatomic) IBOutlet UIButton *SyncButton;//同步按钮
@property (weak, nonatomic) IBOutlet UILabel *VersionLabel;//固件版本号
@property (weak, nonatomic) IBOutlet UILabel *BatteryLabel;//设备电量
@property (weak, nonatomic) IBOutlet UILabel *RSSILabel;//设备信号强度

@property(nonatomic,strong) RobotPenDevice *device;//连接中的设备
@property(nonatomic,strong) NSMutableArray *deviceArray;//设备列表数组

@end

@implementation ViewController
- (NSMutableArray *)deviceArray{
    if (!_deviceArray) {
        _deviceArray = [NSMutableArray array];
    }
    return _deviceArray;
}

#pragma mark- ========== 初始化 ===========

- (void)viewDidLoad {
    [super viewDidLoad];
    #ifdef DEBUG
    [[DoraemonManager shareInstance] install];
    #endif

    self.tableView.delegate = self;
    self.tableView.dataSource = self;

    [self refreshAll];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    // 遵守RobotPenManager协议，必须实现
    [[RobotPenManager sharePenManager] setPenDelegate:self];
    // 抛出硬件点，一般不用开启，这里是为了观察点的变化才开启
    [[RobotPenManager sharePenManager] openReportDevicePrimitivePointData:YES];

    self.device = [[RobotPenManager sharePenManager] getConnectDevice];
    if (!self.device) {
        [[RobotPenManager sharePenManager] AutoCheckDeviceConnect];
    }
    [self refreshAll];
}

/// 初始化相关数据
- (void)refreshAll {

    self.deviceName.text = self.device?[NSString stringWithFormat:@"%@",self.device.deviceName]:@"";
    self.SyncNumberLabel.text =self.device?[NSString stringWithFormat:@"%d",self.device.NoteNumber]:@"";
    self.deviceUUID.text = self.device?[NSString stringWithFormat:@"%@",self.device.uuID]:@"";
    self.VersionLabel.text = self.device?[NSString stringWithFormat:@"%@",self.device.SWStr]:@"";
    self.BatteryLabel.text = self.device?[NSString stringWithFormat:@"%d",self.device.Battery]:@"";
    self.RSSILabel.text = self.device?[NSString stringWithFormat:@"%d",self.device.RSSI]:@"";
    self.SyncButton.hidden = (self.device.NoteNumber <= 0);

    _xValue.text = @"0.0";
    _yValue.text = @"0.0";
    _pressureLabel.text = @"0.0";
    _routeLabel.text = @"0";
    _SyncNumberLabel.text = @"0";

    _SyncButton.hidden = YES;
    _blueToothButton.selected = self.device != nil;
}

#pragma mark- ========== 按钮事件 ===========
/// 搜索设备事件
- (IBAction)blueToothButtonPressed:(id)sender {
    if (!self.device) {
        //搜索设备
        [[RobotPenManager sharePenManager] scanDeviceWithALL:NO];
    } else {
        //断开连接
        [[RobotPenManager sharePenManager] disconnectDevice];
    }

    [self.deviceArray removeAllObjects];
    [_tableView reloadData];
}

/// 同步笔记 （只有当有未同步笔记的状态下）
- (IBAction)SyncButtonPressed:(id)sender {
    _SyncButton.selected = !_SyncButton.selected;
    if (_SyncButton.selected) {
        //开始同步笔记
        [[RobotPenManager sharePenManager] startSyncNote];
    } else {
        //停止同步笔记
        [[RobotPenManager sharePenManager] stopSyncNote];
    }
}

#pragma mark - ========== RobotPenSDK 笔服务协议 ===========
#pragma mark - ---------- 基础协议 ----------
/// 获取点的信息
- (void)getPointInfo:(RobotPenPoint *)point {
    self.xValue.text = [NSString stringWithFormat:@"%hd",point.originalX];
    self.yValue.text = [NSString stringWithFormat:@"%hd",point.originalY];
    self.pressureLabel.text = [NSString stringWithFormat:@"%hd",point.pressure];
    self.routeLabel.text = [NSString stringWithFormat:@"%d",point.touchState];
}

/// 发现设备
- (void)getBufferDevice:(RobotPenDevice *)device {
    [self.deviceArray addObject:device];
    [self.tableView reloadData];
}

/// 获取设备状态 （设备连接状态 ）
- (void)getDeviceState:(DeviceState)State DeviceUUID:(NSString *)uuid {
    NSLog(@"getDeviceState = %d",State);
    switch (State) {
        case DEVICE_DISCONNECTED: {
            //设备断开
            self.device = nil;
            [self refreshAll];
            [self blueToothButtonPressed:nil];
        } break;

        case DEVICE_INFO_END: {
            //连接成功
            //获取当前连接设备信息
            self.device = [[RobotPenManager sharePenManager] getConnectDevice];
            [self refreshAll];
            [self.deviceArray removeAllObjects];
            [self.tableView reloadData];
            if (self.device.deviceType == C7) {
                [[RobotPenManager sharePenManager] OpenReportedData];
            }
        } break;

        default: break;
    }
}

- (void)robotPenReceivedDevicePrimitivePoint:(RobotDeviceOriginPoint)point {
    NSLog(@"点 {%d, %d} 压力:%d 状态:%d", point.x, point.y, point.p, point.s);
}

#pragma mark - ---------- 按键事件协议 ----------
/// 设备电磁板点击事件
- (void)getDeviceEvent:(DeviceEventType)Type {
    NSLog(@"getDeviceEvent = %u",Type);
}

#pragma mark - ----------  同步笔记协议 ----------
/// 获取同步笔迹
- (void)getSyncData:(RobotTrails *)trails{
    NSLog(@"同步笔记的轨迹：%@",trails);
}

/// 获取同步笔记信息
- (void)getSyncNote:(RobotNote *)note{
    NSLog(@"同步笔记的笔记：%@",note);
}

/// 同步状态
- (void)SyncState:(SYNCState)state {
    NSLog(@"SyncState = %u",state);
    switch (state) {
        case SYNC_ERROR: {
            NSLog(@"同步错误");
        } break;

        case SYNC_SUCCESS: {
            NSLog(@"同步成功");
        } break;

        case SYNC_START: {
            NSLog(@"开始同步");
        } break;

        case SYNC_STOP: {
            NSLog(@"停止同步");
            _SyncButton.selected = NO;
        } break;

        case SYNC_COMPLETE: {
            NSLog(@"同步完成");
            _SyncButton.selected = NO;
            _SyncButton.hidden = YES;
        } break;

        default: break;
    }
}

///获取未同步笔记条数
- (void)getStorageNum:(int)num andBattery:(int)battery andNotePercent:(int)percent {
    if (_SyncButton.selected) {
        _SyncNumberLabel.text = [NSString stringWithFormat:@"%d",num];
    }
}

#pragma mark- ========== table delegate相关 ===========
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSInteger rowNumber = 0;

    if (self.deviceArray && [self.deviceArray count] > 0) {
        rowNumber = [self.deviceArray count];
    }

    return rowNumber;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellIdentifier = @"cellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];

    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }

    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    // 获取设备名称
    cell.textLabel.text = [[self.deviceArray objectAtIndex:indexPath.row] getName];

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (!self.device) {
        // 设备Model
        RobotPenDevice *selectItem = [self.deviceArray objectAtIndex:[indexPath row]];
        // 连接设备
        [[RobotPenManager sharePenManager] connectDevice:selectItem];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
