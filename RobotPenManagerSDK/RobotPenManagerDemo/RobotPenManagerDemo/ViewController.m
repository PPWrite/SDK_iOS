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

#define SCREEN_WIDTH self.view.bounds.size.width
#define SCREEN_HEIGHT self.view.bounds.size.height

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource,RobotPenDelegate>
{
    BOOL isConnect;     //是否连接
    
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

@property (weak, nonatomic) IBOutlet UIButton *UpdateButton;//固件升级按钮

@property (weak, nonatomic) IBOutlet UILabel *BatteryLabel;//设备电量

@property (weak, nonatomic) IBOutlet UILabel *RSSILabel;//设备信号强度

@property(nonatomic,strong) RobotPenDevice *device;//连接中的设备

@property(nonatomic,strong) NSMutableArray *deviceArray;//设备列表数组
@end

@implementation ViewController

-(NSMutableArray *)deviceArray{
    
    if (!_deviceArray) {
        
        _deviceArray = [NSMutableArray array];
    }
    return _deviceArray;
}


#pragma mark- ========== 初始化 ===========

- (void)viewDidLoad {
    [super viewDidLoad];
    
    isConnect = NO;         // 是否连接
    
    self.tableView.delegate = self;
    
    self.tableView.dataSource = self;
    
    [_blueToothButton setTitle:@"查找设备" forState:UIControlStateNormal];
    
    [_blueToothButton setTitle:@"断开连接" forState:UIControlStateSelected];
    
    [_blueToothButton addTarget:self action:@selector(blueToothButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    //_SyncButton.hidden = YES;
    
    //_UpdateButton.hidden = YES;
    
    [_SyncButton setTitle:@"同步" forState:UIControlStateNormal];
    
    [_SyncButton setTitle:@"停止同步" forState:UIControlStateSelected];
    
    [_SyncButton addTarget:self action:@selector(SyncButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    [_UpdateButton addTarget:self action:@selector(UpdateButtonPressed:) forControlEvents:UIControlEventTouchUpInside];

    //遵守RobotPenManager协议，必须实现
    [[RobotPenManager sharePenManager] setPenDelegate:self];
    
    // Do any additional setup after loading the view, typically from a nib.
}

-(void)refreshAll {  //初始化全部数据状态
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
    
    _UpdateButton.hidden = YES;
    
    self.device = nil;
    
}



#pragma mark- ========== 按钮事件 ===========

-(void)blueToothButtonPressed:(UIButton *)sender{   // 搜索设备事件
    NSLog(@"%s",__func__);
    
    if (isConnect == NO) {
        
        [self.deviceArray removeAllObjects];
        
        //搜索设备
        [[RobotPenManager sharePenManager] scanDevice];
        
    } else{
        
        sender.selected = NO;
        
        [self.deviceArray removeAllObjects];
        
        [_tableView reloadData];
        
        //断开连接
        [[RobotPenManager sharePenManager] disconnectDevice];
    }
}

-(void)SyncButtonPressed:(UIButton *)sender {// 同步笔记 （只有当有未同步笔记的状态下）
    sender.selected = !sender.selected;
    
    if (sender.selected) {
        //开始同步笔记
        [[RobotPenManager sharePenManager] startSyncNote];
    }
    else
    {
        //停止同步笔记
        [[RobotPenManager sharePenManager] stopSyncNote];
    }
   
}

-(void)UpdateButtonPressed:(UIButton *)sender{// 升级按钮事件 （只有当有设备升级时）
    //OTA升级 过程中不要进行其他操作。
   [[RobotPenManager sharePenManager] startOTA];
    
}






#pragma mark- ========== SDK 协议内容 ===========

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
    
    switch (State) {
            
        case DISCONNECTED://未连接
            
            NSLog(@"disconnect");
            
            isConnect = NO;
            
            _blueToothButton.selected = NO;
            
            [self refreshAll];
            
            [[RobotPenManager sharePenManager] scanDevice];
            
            break;
            
        case CONNECTED://已连接
            
            NSLog(@"CONNECTED");
            
            [[RobotPenManager sharePenManager] stopScanDevice];

            break;
            
        case CONNECTING://正在连接
            
            NSLog(@"connecting");
            
            break;
            
        case DEVICE_UPDATE://可以进行检查更新操作，检查更新操作尽量在这里进行。
        {
           //检查更新
            [[RobotPenManager sharePenManager] getIsNeedUpdate];
                
        }
            break;
            
        case DEVICE_UPDATE_CAN://设备可以更新
        {
            
            _UpdateButton.hidden = NO;
            
        }
            break;

        case DEVICE_INFO_END://获取设备信息完成，大部分设备信息会在这里获取完毕。建议设备信息在这里获取、赋值。
        {
            isConnect = YES;
            
            _blueToothButton.selected = YES;
            
            //获取当前连接设备信息
            self.device = [[RobotPenManager sharePenManager] getConnectDevice];
            
            [self.deviceArray removeAllObjects];
            
            [self.deviceArray addObject:self.device];

            self.deviceName.text = [NSString stringWithFormat:@"%@",[self.device getName]];
            
            self.deviceUUID.text = [NSString stringWithFormat:@"%@",self.device.uuID];
            
            self.VersionLabel.text =[NSString stringWithFormat:@"%@",self.device.SWStr];
            
            self.BatteryLabel.text =[NSString stringWithFormat:@"%d",self.device.Battery];
            
            self.RSSILabel.text =[NSString stringWithFormat:@"%d",self.device.RSSI];
            
            [self.tableView reloadData];
            
        }
            break;
            
        default:
            
            break;
    }
    
}



#pragma mark 同步笔记
- (void)getSyncData:(RobotTrails *)trails{ // 获取同步笔迹
    
    NSLog(@"同步笔记的轨迹：%@",trails);
}

- (void)getSyncNote:(RobotNote *)note{ // 获取同步笔记信息
    
    NSLog(@"同步笔记的笔记：%@",note);
    
}

- (void)SyncState:(SYNCState)state{ // 同步状态
    
    switch (state) {
            
        case SYNC_ERROR:
        {
            NSLog(@"同步笔记错误");
        }
            break;
            
        case SYNC_NOTE:
        {
            NSLog(@"有未同步笔记");
            
        }
            break;
            
        case SYNC_NO_NOTE:
        {
            NSLog(@"没有未同步笔记");
            
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
        }
            break;
            
        case SYNC_STOP:
        {
            NSLog(@"停止同步");
            
            _SyncButton.selected = NO;
        }
            break;
        case SYNC_COMPLETE:
        {
            NSLog(@"同步完成");
            
            _SyncButton.selected = NO;
            
            _SyncButton.hidden = YES;
            
        }
            break;
            
        default:
            break;
    }
}

- (void)getStorageNum:(int)num andBattery:(int)battery{//获取未同步笔记条数
    
    _SyncNumberLabel.text = [NSString stringWithFormat:@"%d",num];
    
    if (num > 0) {
        
        _SyncButton.hidden = NO;
        
    }
}



#pragma mark OTA

- (void)OTAUpdateState:(OTAState)state{ //OTA 升级状态
    
    switch (state) {
        case OTA_DATA:
        {
            NSLog(@"正在下载固件");
            
        }
            break;
            
        case OTA_UPDATE:
        {
            NSLog(@"ota升级");
        }
            break;
            
        case OTA_SUCCESS:
        {
            
            NSLog(@"升级成功");
            
            if (!_UpdateButton.hidden) {
                
                _UpdateButton.hidden = YES;
            }
            
        }
            break;
            
        case OTA_RESET:
        {
            NSLog(@"重启设备");
            
        }
            break;
            
        case OTA_ERROR:
        {
            NSLog(@"OTA升级错误");
        }
            break;
            
        default:
            break;
    }
}

/**
 OTA升级进度
 */
- (void)OTAUpdateProgress:(float)progress{
    
    NSLog(@"OTA升级进度：%d%%",(int)(progress * 100));
    
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
    
    NSLog(@"%s",__func__);
    
    if (!self.device) {
        
        RobotPenDevice *selectItem = [self.deviceArray objectAtIndex:[indexPath row]]; // 设备Model
        
        //连接设备
        [[RobotPenManager sharePenManager] connectDevice:selectItem];

    }
    
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
