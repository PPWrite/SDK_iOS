//
//  ViewController.m
//  RobotPenManagerDemo
//
//  Created by JMS on 2017/2/18.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "ViewController.h"
#import "RobotPenManager.h"
#import "RobotPenDevice.h"
#import "RobotPenPoint.h"
#import "MBProgressHUD.h"
#define SCREEN_WIDTH self.view.bounds.size.width
#define SCREEN_HEIGHT self.view.bounds.size.height

@interface ViewController ()<RobotPenDelegate,UITableViewDelegate,UITableViewDataSource>
{
    int allNote;//所有离线笔记数
}
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

@property (nonatomic, strong) MBProgressHUD *hud; //HUD提示框
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
    [self setUI];
    [self refreshAll];
    //遵守RobotPenManager协议，必须实现
    [[RobotPenManager sharePenManager] setPenDelegate:self];
    // Do any additional setup after loading the view, typically from a nib.
}

/**
 设置UI相关
 */
- (void)setUI
{
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    _SyncButton.hidden = YES;
}
/**
 初始化相关数据
 */
-(void)refreshAll {
    _xValue.text = @"0.0";
    _yValue.text = @"0.0";
    _pressureLabel.text = @"0.0";
    _routeLabel.text = @"0";
    _deviceUUID.text = @"";
    _deviceName.text = @"";
    _SyncNumberLabel.text = @"0";
    _VersionLabel.text = @"0.0.0.0";
    _BatteryLabel.text = @"0";
    _RSSILabel.text = @"0";
    _SyncButton.hidden = YES;
    self.device = nil;
}

#pragma mark- ========== 按钮事件 ===========

- (IBAction)blueToothButtonPressed:(id)sender{   // 搜索设备事件
    if (!self.device) {
        //搜索设备
        [[RobotPenManager sharePenManager] scanDeviceWithALL:NO];
    } else{
        //断开连接
        [[RobotPenManager sharePenManager] disconnectDevice];
    }

    [self.deviceArray removeAllObjects];
    [_tableView reloadData];
}
-(IBAction)SyncButtonPressed:(id)sender
{// 同步笔记 （只有当有未同步笔记的状态下）
    _SyncButton.selected = !_SyncButton.selected;
    if (_SyncButton.selected) {
        //开始同步笔记
        [[RobotPenManager sharePenManager] startSyncNote];
    }
    else
    {
        //停止同步笔记
        [[RobotPenManager sharePenManager] stopSyncNote];
    } 
}

#pragma mark- ========== SDK 协议内容 ===========
/*!
 @method
 @abstract 获取原始点数据
 @param point 原始点
 */
-(void)getPointInfo:(RobotPenPoint *)point{    //获取点的信息
    self.xValue.text = [NSString stringWithFormat:@"%hd",point.originalX];
    self.yValue.text = [NSString stringWithFormat:@"%hd",point.originalY];
    self.pressureLabel.text = [NSString stringWithFormat:@"%hd",point.pressure];
    self.routeLabel.text = [NSString stringWithFormat:@"%d",point.touchState];
}
/**
 发现设备
 @param device <#device description#>
 */
- (void)getBufferDevice:(RobotPenDevice *)device{
    [self.deviceArray addObject:device];
    [self.tableView reloadData];
}
/**
 获取设备状态 （设备连接状态 ）
 @param State <#State description#>
 */
- (void)getDeviceState:(DeviceState)State{
    NSLog(@"State = %d",State);
    switch (State) {
        case DEVICE_DISCONNECTED://未连接
        {
            [self refreshAll];
            _blueToothButton.selected = NO;
            //搜索设备
            [[RobotPenManager sharePenManager] scanDeviceWithALL:NO];
        }
            break;
        case DEVICE_CONNECTE_SUCCESS://已连接
        {
            //停止搜索
            [[RobotPenManager sharePenManager] stopScanDevice];
        }
            break;
        case DEVICE_INFO_END://获取设备信息完成，大部分设备信息会在这里获取完毕。建议设备信息在这里获取、赋值。
        {
            //获取当前连接设备信息
            self.device = [[RobotPenManager sharePenManager] getConnectDevice];
            allNote = self.device.NoteNumber;
            
            self.deviceName.text = [NSString stringWithFormat:@"%@",[self.device getName]];
            self.SyncNumberLabel.text = [NSString stringWithFormat:@"%d",allNote];
            self.deviceUUID.text = [NSString stringWithFormat:@"%@",self.device.uuID];
            self.VersionLabel.text =[NSString stringWithFormat:@"%@",self.device.SWStr];
            self.BatteryLabel.text =[NSString stringWithFormat:@"%d",self.device.Battery];
            self.RSSILabel.text =[NSString stringWithFormat:@"%d",self.device.RSSI];
            self.SyncButton.hidden = (allNote <= 0);
            
            [self.deviceArray removeAllObjects];
            [self.tableView reloadData];
            _blueToothButton.selected = YES;
        }
            break;
        default:
            break;
    }
}

/*!
 @method
 @abstract 设备电磁板点击事件
 @param Type 事件类型
 */
- (void)getDeviceEvent:(DeviceEventType)Type
{
    NSLog(@"getDeviceEvent = %u",Type);
}
#pragma mark 同步笔记
- (void)getSyncData:(RobotTrails *)trails{ // 获取同步笔迹
    NSLog(@"同步笔记的轨迹：%@",trails);
}
- (void)getSyncNote:(RobotNote *)note{ // 获取同步笔记信息
    NSLog(@"同步笔记的笔记：%@",note);
}
- (void)SyncState:(SYNCState)state{ // 同步状态
    NSLog(@"SyncState = %u",state);
    switch (state) {
        case SYNC_ERROR:
        {
            [self hiddenHUD];
        }
            break;
        case SYNC_SUCCESS:
        {
            NSLog(@"同步成功");
        }
            break;
        case SYNC_START:
        {
            NSLog(@"开始同步");
            [self showHUD:@"正在同步中" after:0];
        }
            break;
        case SYNC_STOP:
        {
            NSLog(@"停止同步");
            [self hiddenHUD];
            _SyncButton.selected = NO;
        }
            break;
        case SYNC_COMPLETE:
        {
            NSLog(@"同步完成");
            [self hiddenHUD];
            _SyncButton.selected = NO;
            _SyncButton.hidden = YES;
        }
            break;
        default:
            break;
    }
}
- (void)getStorageNum:(int)num andBattery:(int)battery{//获取未同步笔记条数
    if (_SyncButton.selected) {
        if (self.hud) {
            _SyncNumberLabel.text = [NSString stringWithFormat:@"%d",num];
            if (self.hud.mode != MBProgressHUDModeDeterminate) self.hud.mode = MBProgressHUDModeDeterminate;
            float vlaue = (float)(allNote - num)/allNote;
            self.hud.progress = vlaue;
            self.hud.labelText = [NSString stringWithFormat:@"同步进度:%d%%",(int)(vlaue * 100)];
        }
    }
}
/** 页码检测专用**/
- (void)getTASyncNote:(RobotNote *)note andPage:(int)page
{
    //    NSLog(@"T9A同步笔记的笔记：%@",note);
    //页码检测专用
    //    [RobotSqlManager SaveTANote:note andPage:page Success:^(id responseObject) {
    //
    //        [[RobotPenManager sharePenManager] SetBlockWithBlock:(NSString *)responseObject];
    //
    //    } Failure:^(NSError *error) {
    //        NSLog(@"%@",error);
    //    }];
}

#pragma mark- ========== table delegate相关 ===========
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    NSInteger rowNumber = 0;
    if (self.deviceArray && [self.deviceArray count] > 0) {
        rowNumber = [self.deviceArray count];
    }
    return rowNumber;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString *cellIdentifier = @"cellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    cell.textLabel.text = [[self.deviceArray objectAtIndex:indexPath.row] getName];  //获取设备名称
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    if (!self.device) {
        RobotPenDevice *selectItem = [self.deviceArray objectAtIndex:[indexPath row]]; // 设备Model
        //连接设备
        [[RobotPenManager sharePenManager] connectDevice:selectItem];
    }
}
- (void)hiddenHUD
{
    if (self.hud) {
        [self.hud hide:YES];
        [self.hud removeFromSuperview];
        self.hud = nil;
    }
}
- (void)showHUD:(NSString *)text after:(float)time
{
    self.hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    self.hud.mode = MBProgressHUDModeText;
    self.hud.labelText = text;
    [self.hud show:YES];
    if (time > 0) [self.hud hide:YES afterDelay:time];
    [self.hud removeFromSuperViewOnHide];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
