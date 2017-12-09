//
//  SearchDeviceViewController.m
//  RobotBoardSDKDemo
//
//  Created by JMS on 2017/2/21.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "SearchDeviceViewController.h"
#import "RobotPenManager.h"
#import "RobotPenDevice.h"
#import "RobotPenPoint.h"
#import "MBProgressHUD.h"
#import "SDKManager.h"
#import "RobotSqlManager.h"

#define SCREEN_WIDTH self.view.bounds.size.width
#define SCREEN_HEIGHT self.view.bounds.size.height

@interface SearchDeviceViewController ()<UITableViewDelegate,UITableViewDataSource,RobotPenDelegate>
{
    BOOL isSysnNote;
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

@property (weak, nonatomic) IBOutlet UIButton *BackButton;


@property(nonatomic,strong)NSMutableArray *deviceArray;//设备列表数组

@property (nonatomic, strong) MBProgressHUD *hud; //圆形
@end

@implementation SearchDeviceViewController

-(NSMutableArray *)deviceArray{
    
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

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self resetUI];
}

/**
 设置UI相关
 */
- (void)setUI
{
    self.tableView.delegate = self;
    
    self.tableView.dataSource = self;
    
    [_blueToothButton setTitle:@"查找设备" forState:UIControlStateNormal];
    
    [_blueToothButton setTitle:@"断开连接" forState:UIControlStateSelected];
    
    [_blueToothButton addTarget:self action:@selector(blueToothButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    _SyncButton.hidden = YES;
    
    _UpdateButton.hidden = YES;
    
    [_SyncButton setTitle:@"同步" forState:UIControlStateNormal];
    
    [_SyncButton setTitle:@"停止同步" forState:UIControlStateSelected];
    
    [_SyncButton addTarget:self action:@selector(SyncButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    [_UpdateButton addTarget:self action:@selector(UpdateButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    [_BackButton addTarget:self action:@selector(BackButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
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
    
    _UpdateButton.hidden = YES;
    
    [SDKManager share].device = nil;
    
}

- (void)resetUI {
    
    if ([SDKManager share].device) {
        
        self.deviceName.text = [NSString stringWithFormat:@"%@",[[SDKManager share].device getName]];
        
        self.deviceUUID.text = [NSString stringWithFormat:@"%@",[SDKManager share].device.uuID];
        
        self.VersionLabel.text =[NSString stringWithFormat:@"%@",[SDKManager share].device.SWStr];
        
        self.BatteryLabel.text =[NSString stringWithFormat:@"%d",[SDKManager share].device.Battery];
        
        self.RSSILabel.text =[NSString stringWithFormat:@"%d",[SDKManager share].device.RSSI];
        
        self.SyncNumberLabel.text = [NSString stringWithFormat:@"%d",[SDKManager share].device.NoteNumber];
        
        _UpdateButton.hidden = ![SDKManager share].device.SWStrIsUpdate;
        
        _blueToothButton.selected = YES;
        
        _SyncButton.hidden = ![SDKManager share].device.NoteNumber;

        [self.deviceArray removeAllObjects];
        
        [self.deviceArray addObject:[SDKManager share].device];
        
        [self.tableView reloadData];
    }
}


#pragma mark- ========== 按钮事件 ===========

-(void)blueToothButtonPressed:(UIButton *)sender{   // 搜索设备事件
    NSLog(@"%s",__func__);
    
    if (![SDKManager share].device) {
        //搜索设备
        [self.deviceArray removeAllObjects];
        [[RobotPenManager sharePenManager] scanDevice];
    } else{
        
        //断开连接
        _blueToothButton.selected = NO;
        [[RobotPenManager sharePenManager] disconnectDevice];
    }
}

-(void)SyncButtonPressed:(UIButton *)sender {// 同步笔记 （只有当有未同步笔记的状态下）
    sender.selected = !sender.selected;
    
    if (sender.selected) {
        //开始同步笔记
        isSysnNote = YES;
        self.hud.labelText = @"开始同步笔记...";
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

-(void)BackButtonPressed:(UIButton *)sender{
    
   [self dismissViewControllerAnimated:YES completion:nil];
    
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
 @param device device
 */
- (void)getBufferDevice:(RobotPenDevice *)device{
    
    [self.deviceArray addObject:device];
    
    [self.tableView reloadData];
    
}

/**
 获取设备状态 （设备连接状态 ）
 @param State state
 */
- (void)getDeviceState:(DeviceState)State{
    
    switch (State) {
            
        case DEVICE_DISCONNECTED://未连接
            
            NSLog(@"disconnect");
        
            _blueToothButton.selected = NO;
            
            [self.deviceArray removeAllObjects];
            
            [_tableView reloadData];
            
            //搜索设备
            [[RobotPenManager sharePenManager] scanDevice];
            
            break;
            
        case DEVICE_CONNECTE_SUCCESS://已连接
            
            NSLog(@"CONNECTED");
            //停止搜索
            [[RobotPenManager sharePenManager] stopScanDevice];
            
            break;
            
        case DEVICE_CONNECTING://正在连接
            
            NSLog(@"connecting");
            
            break;
            
        case DEVICE_INFO_END://获取设备信息完成，大部分设备信息会在这里获取完毕。建议设备信息在这里获取、赋值。
        {
            
            _blueToothButton.selected = YES;
            
            //获取当前连接设备信息
            [SDKManager share].device = [[RobotPenManager sharePenManager] getConnectDevice];
            
            [self.deviceArray removeAllObjects];
            
            [SDKManager share].device.allNoteNumers =  [SDKManager share].device.NoteNumber;
            
            [self.deviceArray addObject:[SDKManager share].device];
            
            [self resetUI];
            
        }
            break;
            
        case DEVICE_UPDATE://可以进行检查更新操作，检查更新操作尽量在这里进行。
        {
            //检查更新
            [[RobotPenManager sharePenManager] getIsNeedUpdate];
            
        }
            break;
            
        case DEVICE_UPDATE_CAN://设备可以更新
        {
            NSLog(@"设备可更新");
            
            _UpdateButton.hidden = NO;
            
            [SDKManager share].device.SWStrIsUpdate = YES;
            
        }
            break;
        case DEVICE_UPDATE_CANT:
        {
            [SDKManager share].device.SWStrIsUpdate = NO;
            
            _UpdateButton.hidden = YES;
            
            NSLog(@"设备不可更新");
        }
            break;
            
        default:
            
            break;
    }
    
}


/**
 T9A设备专用
 
 @param page <#page description#>
 @param NoteId <#NoteKey description#>
 */
- (void)getDevicePage:(int)page andNoteId:(int)NoteId
{
    //    NSLog(@"T9A page = %d NoteId = %d",page,NoteId);
    
  
}
- (void)getDevicePageNoteIdNumber:(int)NotePage
{
    NSLog(@"T9A的页码与笔记合并页码 = %d",NotePage);
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
            [SDKManager share].device.allNoteNumers =  [SDKManager share].device.NoteNumber;
            
            NSLog(@"同步笔记错误");
            
            isSysnNote = NO;
            
            dispatch_async(dispatch_get_main_queue(), ^{
                
                [self.hud hide:YES];
                
                self.hud = nil;
                
            });
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
            
            [SDKManager share].device.allNoteNumers =  [SDKManager share].device.NoteNumber;
            
            _SyncButton.selected = NO;
            
            isSysnNote = NO;
            
        }
            break;
        case SYNC_COMPLETE:
        {
            isSysnNote = NO;
            
            NSLog(@"同步完成");
            
            [SDKManager share].device.allNoteNumers =  [SDKManager share].device.NoteNumber;
            
            dispatch_async(dispatch_get_main_queue(), ^{
                
                [self.hud hide:YES];
                
                self.hud = nil;
                
            });
            
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

    if (isSysnNote) {
        
        float vlaue = (float)([SDKManager share].device.allNoteNumers - num)/[SDKManager share].device.allNoteNumers;
        
        self.hud.progress = vlaue;
        
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


#pragma mark OTA

- (void)OTAUpdateState:(OTAState)state{ //OTA 升级状态
    
    switch (state) {
        case OTA_DATA:
        {
            NSLog(@"正在下载固件");
            
            self.hud.labelText = @"正在下载固件...";
            
        }
            break;
            
        case OTA_UPDATE:
        {
            NSLog(@"ota升级");
            
            self.hud.labelText = @"正在载入固件...";
        }
            break;
            
        case OTA_SUCCESS:
        {
            
            NSLog(@"升级成功");
            
            if (!_UpdateButton.hidden) {
                
                _UpdateButton.hidden = YES;
                
            }
            dispatch_async(dispatch_get_main_queue(), ^{
                
                [self.hud hide:YES];
                
                self.hud = nil;
                
            });
            
        }
            break;
            
        case OTA_RESET:
        {
            NSLog(@"重启设备");
            
        }
            break;
            
        case OTA_ERROR:
        {
            dispatch_async(dispatch_get_main_queue(), ^{
                
                [self.hud hide:YES];
                
                self.hud = nil;
                
            });
            
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
- (void)OTAUpdateProgress:(float)progress {
    
    NSLog(@"OTA升级进度：%d%%",(int)(progress * 100));
    
    self.hud.labelText = [NSString stringWithFormat:@"OTA升级进度:%d%%",(int)(progress * 100)];
    
    self.hud.progress = progress;
    
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
    
    if (![SDKManager share].device) {
        
        RobotPenDevice *selectItem = [self.deviceArray objectAtIndex:[indexPath row]]; // 设备Model
        
        //连接设备
        [[RobotPenManager sharePenManager] connectDevice:selectItem];
        
    }
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)backaction:(id)sender {
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (MBProgressHUD *)hud {
    
    if (!_hud) {
        
        _hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        
        _hud.mode = MBProgressHUDModeDeterminate;
        
        _hud.dimBackground = YES;
        
    }
    return _hud;
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
