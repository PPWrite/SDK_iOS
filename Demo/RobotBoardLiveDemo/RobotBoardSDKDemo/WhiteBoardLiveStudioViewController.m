//
//  WhiteBoardLiveStudioViewController.m
//  RobotBoardSDKDemo
//
//  Created by JMS on 2017/11/30.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "WhiteBoardLiveStudioViewController.h"
#import "RobotWhiteBoard_LiveView.h"
#import "RobotPenLiveManager.h"
#import "RobotNetManager.h"
#import "RobotSqlManager.h"
#import "Header.h"
#import "MJExtension.h"
#import "SDKManager.h"
static int interval_Board = 10;

@interface WhiteBoardLiveStudioViewController ()<RobotPenLiveDelegate,WhiteBoardViewDelegate,WhiteBoardLiveViewDelegate>
{
    RobotLiveStudioModel *liveStudioModel;
    //是否可以书写
    BOOL isCanWrite;
    //是否是房主
    BOOL isOwner;
}
@property (weak, nonatomic) IBOutlet UIButton *BackButton;

@property (weak, nonatomic) IBOutlet UIView *LiveWBView;

@property (nonatomic, strong) RobotWhiteBoard_LiveView *WhiteBoardView;//直播白板

@property (nonatomic, copy) NSString *NoteKey;//笔记标识

@property (nonatomic, copy) NSString *NoteTitle;//笔记标题
@end

@implementation WhiteBoardLiveStudioViewController

-(void)BackButtonPressed:(UIButton *)sender
{
    [[RobotPenLiveManager sharePenLiveManager] exitStudioWithisHost:NO];
    
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    [_BackButton addTarget:self action:@selector(BackButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    [self BulidWhiteBoard];
    // Do any additional setup after loading the view from its nib.
}
- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    //创建直播间
//    [self BuildLiveStudio];
    
    //进入直播间
    [self getLiveStudioInfo];
    
    [[RobotPenLiveManager sharePenLiveManager] setPenLiveDelegate:self];
}


#pragma mark- ========== 白板实现===========
/**
 白板创建
 */
- (void)BulidWhiteBoard{
    
    
    self.WhiteBoardView = [[RobotWhiteBoard_LiveView alloc] init];//此处不要设置大小（在setWB方法里设置）
    
    self.WhiteBoardView.whiteBoardDelegate = self; //设置画板代理，必须实现
    
    self.WhiteBoardView.WBLiveDelegate = self; //设置画板代理，必须实现
    
    [self.LiveWBView addSubview:self.WhiteBoardView];  // 添加视图
    
    [self.WhiteBoardView setBgColor:BG_NoteColor];  // 设置 背景颜色
    
}
- (void)setWB{
    
    //以下方法必须实现并且调用顺序不可变。
    [self.WhiteBoardView setDeviceType:[liveStudioModel.DeviceType intValue]];   //设置设备类型（必须设置）
    
    [self.WhiteBoardView setIsHorizontal:[liveStudioModel.IsHorizontal intValue]]; //设置画板的横竖方向 0：竖 1：横（必须设置）
    
    [self.WhiteBoardView setSceneSize:CGRectMake(interval_Board , interval_Board , ScreenWidth - 2 * interval_Board,ScreenHeight - 2 * interval_Board - 64)]; //设置白板的Frame（根据传入的frame自动设置,必须设置））
    
    [self.WhiteBoardView RefreshAll];   //刷新白板内容（本地数据库操作,用不到数据库的可以不写）
    
}

#pragma mark - ========== 获取、初始化直播间信息  ===========
/**
 创建直播间
 */
- (void)BuildLiveStudio
{
    [[RobotNetManager shareNetManager] BuildLiveStudioWithName:@"iOS Test" Password:@"" UserID:self.userIDStr UserSession:self.userSessionStr About:@"" Tags:@[] Success:^(id responseObject) {
        
        if ([[responseObject allKeys] containsObject:@"error"]) {
            
        }
        else
        {
            liveStudioModel = [RobotLiveStudioModel mj_objectWithKeyValues:responseObject];
            //初始化并开启直播
            [self initLiveStudioWith:liveStudioModel isStartLiving:YES];
        }
        
    } Failure:^(NSError *error) {
        
    }];
}

/**
 获取直播间信息
 */
- (void)getLiveStudioInfo
{
    //测试账号
    
    self.userIDStr = @"10025";
    self.userSessionStr = @"ddaf98f60442ded1c3e44d27629d78da";
    self.liveIDStr = @"15";
    self.passwordStr = @"";
    
    //这里以是否有密码判断，有密码则认为是加密房间，否则则是非加密房间
    BOOL IsEncrypts= NO;
    if (![self.passwordStr isEqualToString:@""]) {
        IsEncrypts = YES;
    }
    liveStudioModel = [[RobotLiveStudioModel alloc] init];
    //根据直播间LiveID、是否加密、密码、进入直播间的用户的UserID和UserSession，获取直播间信息。
    [[RobotNetManager shareNetManager] getLiveInfomationWithLiveID:self.liveIDStr IsEncrypt:IsEncrypts Password:self.passwordStr UserID:self.userIDStr UserSession:self.userSessionStr Success:^(id responseObject) {
        if([responseObject isKindOfClass:[NSDictionary class]])
        {
            if ([[responseObject allKeys] containsObject:@"error"]) {
                NSLog(@"获取信息错误");
                [self dismissViewControllerAnimated:YES completion:nil];
            }
            else
            {
                liveStudioModel = [RobotLiveStudioModel mj_objectWithKeyValues:responseObject];
                NSLog(@"model = %@",liveStudioModel);
                isCanWrite = [liveStudioModel.IsSpeak intValue] == 0 ? NO : YES;
                //判断是否是房主，利用直播间信息初始化直播间
                if ([self.userIDStr intValue] == [[liveStudioModel.User objectForKey:@"UserID"] intValue]) {
                    [self initLiveStudioWith:liveStudioModel isStartLiving:YES];
                }
                else{
                    [self initLiveStudioWith:liveStudioModel isStartLiving:NO];
                }
                
            }
        }
    } Failure:^(NSError *error) {
        
    }];

}

/**
 初始化直播间

 @param liveModel 直播间信息模型
 @param isStart 是否是房主
 */
- (void)initLiveStudioWith:(RobotLiveStudioModel *)liveModel isStartLiving:(BOOL)isStart
{
    isOwner = isStart;
    NSString *newnoteKey = @"";
    //isStart 表示是否是房主，如果是房主则需要开启直播，不是则初始化完成即可。
    if (isStart) {
        //房主拥有书写权限
        isCanWrite = YES;
        //直播间未开启，则开启直播间
        if ([liveModel.LiveSession intValue] == 0) {
            //主播笔记的横竖方向
            liveModel.IsHorizontal = @"0";
            //主播笔记的设备类型，默认为“4”，可根据DeviceType范围自定义默认值
            liveModel.DeviceType = [SDKManager share].device.deviceType != 0 ?[NSString stringWithFormat:@"%d",[SDKManager share].device.deviceType]:@"4";
            //这里以LiveID_时间戳 为笔记标识，确保每次开启直播的笔记notekey不同
            newnoteKey = [NSString stringWithFormat:@"%@_%lld",liveModel.LiveID,(long long)[RobotSqlManager GetTimeInterval]];
        }
        else {//直播中出现意外断开，需重新开启
            newnoteKey = [NSString stringWithFormat:@"%@_%@",liveModel.LiveID,liveModel.LiveSession];
        }
        
    }
    else
    {
        //房主不在,创建此直播间的临时笔记
        if ([liveModel.LiveSession intValue] == 0) {
            newnoteKey = liveModel.LiveID;
        }
        else {//房主在,创建此直播间笔记，存在则刷新
            newnoteKey = [NSString stringWithFormat:@"%@_%@",liveModel.LiveID,liveModel.LiveSession];
        }
        
    }
    //创建直播间笔记
    [self.WhiteBoardView BuildNoteWithLiveModel:liveModel NoteKey:newnoteKey IsNote:isStart];
    //设置白板笔记标识
    self.NoteKey = newnoteKey;
    //设置白板笔记标题
    self.NoteTitle =  [NSString stringWithFormat:@"%@(%@)",liveModel.Name,liveModel.LiveID];
    //刷新直播间白板
    [self setWB];
    
    //确保观众和主播的页码信息一致
    if (!isStart) {
        [self.WhiteBoardView turnToPageWithPage:(int)[liveModel.Blocks indexOfObject:liveModel.Block] + 1];
    }
    //清空当前的直播通道避免直播通道未关闭导致的信号错乱
    [[RobotPenLiveManager sharePenLiveManager] CleanChannel];
    //初始化直播间
    [[RobotPenLiveManager sharePenLiveManager] initLiveStudioWithChannel:liveModel.Channel LiveSession:[NSString stringWithFormat:@"%@",liveModel.LiveSession] UserID:self.userIDStr HostID:liveModel.User[@"UserID"] ];
    //语音系统本地权限，语音权限在本地设置。
    [[RobotPenLiveManager sharePenLiveManager] setSpeakCan:([liveModel.IsSpeak intValue] == 1?YES:NO)];
    
    //房主开启直播间
    if (isStart) {
        
        NSString *newLiveSessions = @"";
        //主播开始直播
        if ([liveModel.LiveSession intValue] == 0) {

            if ([self.NoteKey containsString:@"_"]) {
                
                NSArray *arr = [self.NoteKey componentsSeparatedByString:@"_"];
                newLiveSessions = arr[1];
            }
            else
            {
                newLiveSessions = self.NoteKey;
            }
        }
        else//主播直播意外断开后，重新进入
        {
            newLiveSessions = liveModel.LiveSession;
        }
        
        RobotLiveStudioBaseModel *startliveModel = [[RobotLiveStudioBaseModel alloc] init];
        startliveModel.Channel = liveModel.Channel;
        startliveModel.LiveID = liveModel.LiveID;
        startliveModel.LiveSession = liveModel.LiveSession;
        startliveModel.BlockKey = self.WhiteBoardView.blockKey;
        startliveModel.UserID = self.userIDStr;
        startliveModel.NoteKey = self.NoteKey;
        startliveModel.UserSession = self.userSessionStr;
        //直播间的横竖方向设置，与主播笔记的横竖方向一致
        startliveModel.IsHorizontal = @"0";
        //直播间的设备类型，与主播笔记的设备类型一致，默认为“4”，可根据DeviceType范围自定义默认值
        startliveModel.DeviceType = [SDKManager share].device.deviceType != 0 ?[NSString stringWithFormat:@"%d",[SDKManager share].device.deviceType]:@"4";
        [[RobotPenLiveManager sharePenLiveManager] startStudioWithModel:startliveModel];
    }
 
}


#pragma mark - ========== 直播协议  ===========

/*!
 @method
 @abstract 设置书写权限
 @result 返回结果
 */
- (BOOL)GetIsLiveWrite
{
    return isCanWrite;
}
/*!
 @method
 @abstract 设置是否是房主
 @result 返回结果
 */
- (BOOL)GetIsOwner
{
    return isOwner;
}

/*!
 @method
 @abstract 设置直播间LiveID
 @result 返回结果
 */
- (NSString *)GetLiveId
{
    return liveStudioModel.LiveID;
}
/*!
 @method  获取直播白板状态
 @abstract 获取白板服务状态
 @param wbState 白板状态
 */
- (void)getLiveWhiteBoardState:(WBLiveStateType)wbState
{
    switch (wbState) {
        case WBLiveState_WB_Start_Success:
            break;
        case WBLiveState_Vocie_Start_Success:
            break;
        case WBLiveState_WB_End_Success:
        {
          [self dismissViewControllerAnimated:YES completion:nil];
        }
            break;
        default:
            break;
    }
}

/*!
 @method  获取直播间状态
 @abstract 获取直播间状态
 @param studioState 直播间状态
 @param Content 观众userID/人数/直播耗时
 @param delay 延迟信息
 */
- (void)getLiveStudioState:(LiveStudioMessageType)studioState Content:(NSString *)Content Delay:(NSInteger)delay
{
    switch (studioState){
        /**主播进入直播间*/
    case LiveStudioMessage_People_Anchor_Enter:
        {
            //不是房主，需要刷新一下直播间数据
            if (([self.userIDStr intValue] != [[liveStudioModel.User objectForKey:@"UserID"] intValue])) {
                [self getLiveStudioInfo];
            }
        }
        break;
        /**用户进入直播间*/
    case LiveStudioMessage_People_Audience_Enter:
        {
            NSLog(@"用户：%@进入直播间",Content);
        }
        break;
        /** 观众离开房间*/
    case LiveStudioMessage_People_Audience_Leave:
        {
            NSLog(@"用户：%@离开直播间",Content);
        }
        break;
        /** 授予说话权限*/
    case LiveStudioMessage_People_Audience_Speak_Award:
        {
            NSLog(@"用户：%@被授予说话权限",Content);
        }
        break;
        /** 授予写入权限*/
    case LiveStudioMessage_People_Audience_Write_Award:
        {
            NSLog(@"用户：%@被授予书写权限",Content);
        }
        break;
        /** 踢人*/
    case LiveStudioMessage_People_Audience_Leave_Award:
        {
            if ([Content intValue] == 0)
            {
                NSLog(@"房主退出直播间");
                [[RobotPenLiveManager sharePenLiveManager] exitStudioWithisHost:NO];
                [self dismissViewControllerAnimated:YES completion:nil];
                
            }else
            {
                NSLog(@"用户：%@被踢出直播",Content);
            }
        }
        break;
        /** 请求说话权限*/
    case LiveStudioMessage_People_Audience_Speak_Ask:
        {
            NSLog(@"用户：%@请求说话权限",Content);
        }
        break;
        /** 请求写入权限*/
    case LiveStudioMessage_People_Audience_Write_Ask:
        {
            NSLog(@"用户：%@请求书写权限",Content);
        }
        break;
        /** 直播耗时*/
    case LiveStudioMessage_Studio_Time:
        {
            NSLog(@"直播剩余时间：%@毫秒",Content);
            
        }
        break;
        /** 直播间人数*/
    case LiveStudioMessage_Studio_Number:
        {
            
            NSLog(@"直播间人数：%@人",Content);
        }
        break;
        /** 房主延迟*/
    case LiveStudioMessage_People_Anchor_Delay:
        {
            NSLog(@"房主延迟：%ld",(long)delay);
            
        }
        break;
        /** 观众延迟*/
    case LiveStudioMessage_People_Audience_Delay:
        {
            NSLog(@"观众%@的延迟：%ld",Content,(long)delay);
        }
        break;
        
    default:
        break;
    }
}

/*!
 @method  获取直播数据
 @abstract 获取直播数据
 @param dataType 直播数据类型
 @param data 直播数据
 */
- (void)getLiveDataMessageType:(LiveDataMessageType)dataType data:(RobotTrails *)data
{
    //处理直播数据
    [self.WhiteBoardView manageLiveDataMessageType:dataType data:data];
}
#pragma mark - ========== 白板协议（设置属性类）  ===========

//大于0表示是橡皮擦，需要用到橡皮擦功能则需要实现
- (int)getIsRubber{
    
    return 0;
    
}

//大于0表示是有压感，需要用到压感功能则需要实现
- (int)getIsPressure
{
    return 1;
}
//获取笔颜色，需要设置笔迹颜色功能则需要实现
- (UIColor *)getPenColor{
    
    return [UIColor blackColor];
    
}

//获取笔的粗细，需要设置笔迹宽度功能则需要实现
- (CGFloat)getPenWeight{
    
    return 1;
    
}


//获取当前笔记本Key，需要用到画板功能则需要实现
- (NSString *)getNoteKey{
    
    return _NoteKey;
    
}

//设置笔记标题，需要设置笔迹标题功能则需要实现
- (NSString *)getNoteTitle
{
    return _NoteTitle;
}

//获取当前用户ID
- (long)getCurrUserId{
    
    return [self.userIDStr longLongValue];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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
