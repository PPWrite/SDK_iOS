//
//  WhiteBoardMicroViewController.m
//  RobotBoardSDKDemo
//
//  Created by JMS on 2017/2/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "WhiteBoardMicroViewController.h"
#import "RobotWhiteBoard_MicroView.h"
#import "Header.h"
#import "RobotSqlManager.h"
#import "RobotVideo.h"
#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKit.h>
#import "SDKManager.h"

static int interval_Board = 10;

@interface WhiteBoardMicroViewController ()<WhiteBoardViewDelegate,RobotPenDelegate,UIImagePickerControllerDelegate,UINavigationControllerDelegate>
{
    BOOL isRecord;// 是否是录制状态
    
    BOOL isHorizontal; //是否横屏
    
    DeviceType DeviceTypes;//设备类型
    
    NSURL *videoPathUrl;//视频地址（本地地址保存路径）
    
    NSString *saveT9ANoteKey;//T9A专用存笔记
    
    int saveT9ANotePage;//T9A专用存页码
    
    BOOL isfirstT9A;//是否是第一次进入T9专用
    
    int  CurrentPage;//记录当前所在的页T9专用
    
}
@property (nonatomic, strong) RobotWhiteBoard_MicroView *WhiteBoardView;//录制白板

@property (weak, nonatomic) IBOutlet UIButton *BackButton;//返回按钮

@property (weak, nonatomic) IBOutlet UIButton *RecordingButton;//录制、停止按钮

@property (weak, nonatomic) IBOutlet UIButton *StopRecordingButton;//暂停、继续录制按钮

@property (weak, nonatomic) IBOutlet UILabel *TimeLabel;//录制时间

@property (weak, nonatomic) IBOutlet UIView *WBBView;//白板背景

@property (weak, nonatomic) IBOutlet UILabel *PageLabel;//页码显示

@property (nonatomic, strong) UIColor *PenColor;//笔迹颜色

@property (nonatomic, assign) CGFloat PenWidth;//笔迹的宽度

@property (nonatomic, copy) NSString *NoteKey;//笔记的NoteKey（唯一标识） 根据这个Key值对笔记进行操作

@property (nonatomic, copy) NSString *NoteTitle;//笔记的标题

@end

@implementation WhiteBoardMicroViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setUI];
    
    DeviceTypes = 1;//已1为例，具体看电磁板设备类型
    
    [self BulidWhiteBoard];//初始化白板
    
    // Do any additional setup after loading the view from its nib.
}

- (void)setUI{
    
    isRecord= NO;
    
    [self.RecordingButton setTitle:@"录制" forState:UIControlStateNormal];
    
    [self.RecordingButton setTitle:@"停止" forState:UIControlStateSelected];
    
    [self.RecordingButton addTarget:self action:@selector(RecordingClicked:) forControlEvents:UIControlEventTouchUpInside];
    
    [self.StopRecordingButton setTitle:@"暂停" forState:UIControlStateNormal];
    
    [self.StopRecordingButton setTitle:@"继续" forState:UIControlStateSelected];
    
    [self.StopRecordingButton addTarget:self action:@selector(StopRecordingClicked:) forControlEvents:UIControlEventTouchUpInside];
    
    [_BackButton addTarget:self action:@selector(BackButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
}
- (void)viewWillAppear:(BOOL)animated{      // 获取笔设备  这里可以获取到 详细的笔设备相关信息
    
    //笔服务代理设置，必须实现。
    [[RobotPenManager sharePenManager] setPenDelegate:self];
    
    // 获取当前已连接设备
    RobotPenDevice *device = [[RobotPenManager sharePenManager] getConnectDevice];
    
    DeviceTypes = device.deviceType;//用于setDeviceType传值
    
    //本地数据库，RobotSqlManager包含白板所有产生数据（笔记、截图、各种资源、文件等）详情查看RobotSqlManager.h
    [RobotSqlManager checkRobotSqlManager];
    
    // 检查笔记是否存在
    if (![RobotSqlManager checkNoteWithNoteKey:@"WBMicro"]) {
        
        [self BuildTempNote]; // 创建 一个NoteKey = @"WBMicro"的笔记
        
    }
    
    //白板信息
    _NoteKey = @"WBMicro";//用于getNoteKey传值
    
    _NoteTitle = @"录制白板";//用于getNoteTitle传值
    
    _PenColor = [UIColor redColor];//用于getPenColor传值
    
    _PenWidth = 1;//用于getPenWeight传值
    
    [self.WhiteBoardView SetDrawType:PenDraw];// 输入的方式 （0:手、1:笔）
    
    [self setWB];//设置画板并刷新
    
    
}

#pragma mark- ========== 白板实现===========

/**
 白板创建
 */
- (void)BulidWhiteBoard{
    
    self.WhiteBoardView = [[RobotWhiteBoard_MicroView alloc] init];   //此处不要设置大小（在setWB方法里设置Frame）
    
    self.WhiteBoardView.whiteBoardDelegate = self;       // 设置画板代理，必须实现
    
    [self.WBBView addSubview:self.WhiteBoardView];       // 添加视图
    
    [self.WhiteBoardView setBgColor:BG_NoteColor];   // 设置背景颜色（这是设置白板的颜色）
    
}

- (void)setWB{
    
    //以下方法必须实现并且调用顺序不可变。
    [self.WhiteBoardView setDeviceType: DeviceTypes];   //设置设备类型（必须设置）
    
    [self.WhiteBoardView setIsHorizontal:isHorizontal]; //设置画板的横竖方向 0：竖 1：横（必须设置）
    
    [self.WhiteBoardView setSceneSize:CGRectMake(0 , 0 , 3 * ScreenWidth /4 - 45/4 -5,ScreenHeight - 202)]; //设置白板的Frame（根据传入的frame自动设置,必须设置））
    
    [self.WhiteBoardView RefreshAll];   //刷新白板内容（本地数据库操作）
    
}
-(void)BuildTempNote{ // 创建 一本笔记
    
    RobotNote *notemodel =  [[RobotNote alloc]init];// 创建笔记Model
    
    notemodel.NoteKey = @"WBMicro";//笔记的NoteKey（唯一标识），必填
    
    notemodel.Title = @"录制白板";//笔记的标题
    
    notemodel.DeviceType = DeviceTypes;//笔记的设备类型，必填
    
    notemodel.UserID = 0;//用户id
    
    notemodel.IsHorizontal = 0;//笔记方向，必填
    
    // 创建一本笔记
    [RobotSqlManager BuildNote:notemodel Success:^(id responseObject) {
        
//        NSLog(@"responseObject = %@",responseObject);
        
    } Failure:^(NSError *error) {
        
    }];
    
    
}



#pragma mark - ========== 白板协议（设置属性类）  ===========

//获取当前用户ID
- (long)getCurrUserId{
    
    return 0;
    
}
//大于0表示是橡皮擦，需要用到橡皮擦功能则需要实现
- (int)getIsRubber{
    
    return 0;
    
}


//大于0表示是有压感，需要用到压感功能则需要实现
- (int)getIsPressure
{
    return 1;
}

//获取当前笔记本Key，需要用到画板功能则需要实现
- (NSString *)getNoteKey{
    
    return _NoteKey;
    
}
//获取笔颜色，需要设置笔迹颜色功能则需要实现
- (UIColor *)getPenColor{
    
    return _PenColor;
    
}

//获取笔的粗细，需要设置笔迹宽度功能则需要实现
- (CGFloat)getPenWeight{
    
    return _PenWidth/[UIScreen mainScreen].scale;
    
}
//设置笔记标题，需要设置笔迹标题功能则需要实现
- (NSString *)getNoteTitle
{
    return _NoteTitle;
}



#pragma mark ========== 白板协议（信息获取类） ===========


/**
 电磁板按键事件

 @param Type <#Type description#>
 */
- (void)getDeviceEvent:(DeviceEventType)Type{
    
    [_WhiteBoardView getDeviceEvent:Type];
}


/**
 电磁板原始数据上报

 @param point <#point description#>
 */
-(void)getPointInfo:(RobotPenPoint *)point{
    
        NSLog(@"%hd %hd %d",point.originalX,point.originalY,point.touchState);

    //if 判断为T9A专用，其他设备可以忽略
    if ([SDKManager share].device.deviceType == T9A) {

        if ([self.NoteKey isEqualToString:saveT9ANoteKey]) {
            
            if (CurrentPage != [self.PageLabel.text intValue]) {
                
                [self.WhiteBoardView setManagePageWithPage:CurrentPage];
                
            }
            
        }
        else
        {
            self.NoteKey = saveT9ANoteKey;
            
            self.NoteTitle = [NSString stringWithFormat:@"%@",saveT9ANoteKey];
            
            CurrentPage = saveT9ANotePage;
            
            [self.WhiteBoardView setManagePageWithPage:saveT9ANotePage];

        }
        
    }

    //画板画线
    [self.WhiteBoardView drawLine:point];
  
    
}

- (void)GetVideoTime:(float)Seconds{ // 获取录制时间
    
    self.TimeLabel.text = [NSString stringWithFormat:@"%@",[self getMMSSFromSS:[NSString stringWithFormat:@"%f",Seconds]]];
    
}

//转换时间格式
-(NSString *)getMMSSFromSS:(NSString *)totalTime{
    
    NSInteger seconds = [totalTime integerValue];
    
    NSString *str_hour = [NSString stringWithFormat:@"%02ld",seconds/3600];
    
    NSString *str_minute = [NSString stringWithFormat:@"%02ld",(seconds%3600)/60];
    
    NSString *str_second = [NSString stringWithFormat:@"%02ld",seconds%60];
    
    NSString *format_time = [NSString stringWithFormat:@"%@:%@:%@",str_hour,str_minute,str_second];
    
    return format_time;
    
}

//白板相关回调，用于返回白板状态信息，具体状态请查看RobotWhiteBoardView.h文件。
- (void)GetWhiteBoardState:(WBMessageType)State content:(NSString *)Info{
    
    //    NSLog(@"WB StateInfo = %@",State);
    
}
- (void)GetVideoRecordState:(WBVideoMessageType)StateInfo content:(NSString *)Info
{
    //    NSLog(@"Video StateInfo = %@",StateInfo);
}

/**
 T9A设备专用

 @param page <#page description#>
 @param NoteId <#NoteKey description#>
 */
- (void)getDevicePage:(int)page andNoteId:(int)NoteId
{
//     NSLog(@"T9A page = %d NoteId = %d",page,NoteId);

    //显示当前页码
    self.PageLabel.text = [NSString stringWithFormat:@"%d",page];
    
    NSString *NoteKey = [NSString stringWithFormat:@"%@%d",@"T9A",NoteId];
    
    //判断电磁板笔记与当前笔记是否相同
    if ([self.NoteKey isEqualToString:NoteKey]) {

        //相同笔记
        self.NoteKey = NoteKey;
        
        self.NoteTitle = [NSString stringWithFormat:@"%@",NoteKey];
        
        CurrentPage = page;

        //管理页码信息
        [self.WhiteBoardView setManagePageWithPage:page];

    }
    else
    {
        //检查数据库中是否存在电磁板笔记
        if ([RobotSqlManager checkNoteWithNoteKey:NoteKey]) {

        }
        else
        {
            RobotNote *notemodel =  [[RobotNote alloc]init];
            
            notemodel.NoteKey = NoteKey;
            
            notemodel.Title = [NSString stringWithFormat:@"%@",NoteKey];
            
            notemodel.DeviceType = [[[NSUserDefaults standardUserDefaults] objectForKey:@"DeviceType"] intValue];
            
            notemodel.UserID = [[[NSUserDefaults standardUserDefaults] objectForKey:@"UserID"] intValue];
            
            notemodel.IsHorizontal =[[[NSUserDefaults standardUserDefaults] objectForKey:@"isHorizontal"] intValue];

            //创建新笔记
            [RobotSqlManager BuildNote:notemodel Success:^(id responseObject) {

            } Failure:^(NSError *error) {

                return ;
            }];

        }

        if (isfirstT9A) {
            
            self.NoteKey = NoteKey;
            
            self.NoteTitle = [NSString stringWithFormat:@"%@",NoteKey];
            
            //页码管理
            [self.WhiteBoardView setManagePageWithPage:page];

        }

    }

    if (!isfirstT9A) {
        
        isfirstT9A = YES;
    }

    saveT9ANoteKey = NoteKey;
    
    saveT9ANotePage = page;

}
- (void)getDevicePageNoteIdNumber:(int)NotePage
{
    NSLog(@"T9A的页码与笔记合并页码 = %d",NotePage);
}
#pragma mark- ========== 按钮点击事件 （控制类）  ===========

-(void)BackButtonPressed:(UIButton *)sender
{
    
    [self dismissViewControllerAnimated:YES completion:nil];
    
}
//取消录制
- (IBAction)CancelVideoClicked:(id)sender
{
    self.RecordingButton.selected = NO;
    
    self.StopRecordingButton.selected = NO;
    
    self.TimeLabel.text = @"00:00:00";
    
    //取消录制
    [self.WhiteBoardView CancelVideoRecord];
    
    
}
//播放视频
- (IBAction)VideoPlayClicked:(id)sender
{
    
    AVPlayerViewController *player = [[AVPlayerViewController alloc] init];
    
    player.player = [[AVPlayer alloc] initWithURL:videoPathUrl];
    
    [self presentViewController:player animated:YES completion:^{
        
    }];

    
}

//视频地址
- (IBAction)VideoAddressClicked:(id)sender
{
    [RobotSqlManager GetVideoListWithPage:0 Success:^(id responseObject) {
        
        NSArray *videoPathArray = [NSArray arrayWithArray:[responseObject objectForKey:@"Data"]];
       
        if (videoPathArray.count > 0) {
            
            //这里取最新录制的视频
            RobotVideo *models = [videoPathArray objectAtIndex:0];
            
            videoPathUrl = [NSURL fileURLWithPath:[RobotSqlManager GetVideoPathWithNameKey:models.NameKey]];

        }
    } Failure:^(NSError *error) {
               
        NSLog(@"error %@",error);
        
    }];
    
    if (videoPathUrl) {
        
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"视频地址" message:[NSString stringWithFormat:@"%@",videoPathUrl] preferredStyle:UIAlertControllerStyleAlert ];
        
        UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleDefault handler:nil];
        
        [alertController addAction:cancelAction];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            
            [self presentViewController:alertController animated:YES completion:nil];
            
        });

    }
   
}


//暂停继续
-(void)StopRecordingClicked:(UIButton *)sender{
    
    if (!isRecord) {
        
        return;
        
    }
    if (sender.isSelected) {
        
        sender.selected = NO;
        
        //继续录制
        [self.WhiteBoardView ContinueVideoRecord];
        
    }else{
        
        sender.selected = YES;
        
        //暂停录制
        [self.WhiteBoardView PauseVideoRecord];
        
    }
}
//录制和停止
-(void)RecordingClicked:(UIButton *)sender{
    
    if (sender.isSelected) {
        
        sender.selected = NO;
        
        //结束录制
        [self.WhiteBoardView EndVideoRecord];
        
        isRecord = NO;
        
        self.TimeLabel.text = @"录制完成";
        
    }else{
        
        sender.selected = YES;
        
        isRecord = YES;
        
        //开始录制
        [self.WhiteBoardView StartVideoRecord];
    }
    
}


//前一页
- (IBAction)FrontPageClicked:(id)sender {
    
    //前一页
    [self.WhiteBoardView frontPage];
    
}

//后一页
- (IBAction)NextPageClicked:(id)sender {
    
    //后一页
    [self.WhiteBoardView nextPage];
    
}

//删除当前页
- (IBAction)DeletePageClicked:(id)sender {
    
    //删除当前页
    [self.WhiteBoardView delCurrPage];
    
}

//笔的颜色
- (IBAction)PenColorClicked:(id)sender {
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"线的颜色" message:nil preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *blueAction = [UIAlertAction actionWithTitle:@"绿色" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        self.PenColor = [UIColor greenColor];
        
    }];
    
    UIAlertAction *purpleAction = [UIAlertAction actionWithTitle:@"黑色" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        self.PenColor = [UIColor blackColor];
        
    }] ;
    
    UIAlertAction *cancleAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        
    }];
    
    [alert addAction:blueAction];
    
    [alert addAction:purpleAction];
    
    [alert addAction:cancleAction];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        [self presentViewController:alert animated:YES completion:nil];
        
    });
    
}
//笔的粗细
- (IBAction)PenWidthClicked:(id)sender {
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"笔的粗细" message:nil preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *twoAction = [UIAlertAction actionWithTitle:@"2" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        self.PenWidth = 2.0f;
        
    }];
    UIAlertAction *fourAction = [UIAlertAction actionWithTitle:@"4" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        self.PenWidth = 4.0f;
        
    }] ;
    UIAlertAction *sixAction = [UIAlertAction actionWithTitle:@"6" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        self.PenWidth = 6.0f;
        
    }] ;
    UIAlertAction *cancleAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        
        
    }];
    
    [alert addAction:twoAction];
    
    [alert addAction:fourAction];
    
    [alert addAction:sixAction];
    
    [alert addAction:cancleAction];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        [self presentViewController:alert animated:YES completion:nil];
        
    });
}
//插图
- (IBAction)InsertImageClicked:(id)sender {
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"选择插图的方式" message:nil preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *albumAction = [UIAlertAction actionWithTitle:@"相册" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        UIImagePickerController *picker = [[UIImagePickerController alloc] init];
        
        picker.delegate = self;
        
        picker.allowsEditing = NO;
        
        picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        
        [self presentViewController:picker animated:YES completion:nil];
        
    }];
    
    UIAlertAction *photoAction = [UIAlertAction actionWithTitle:@"拍照" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
        UIImagePickerController *picker = [[UIImagePickerController alloc] init];
        
        picker.delegate = self;
        
        picker.allowsEditing = NO;
        
        picker.sourceType = UIImagePickerControllerSourceTypeCamera;
        
        [self presentViewController:picker animated:YES completion:nil];
        
    }] ;
    
    UIAlertAction *cancleAction = [UIAlertAction actionWithTitle:@"取消" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        
    }];
    
    [alert addAction:albumAction];
    
    [alert addAction:photoAction];
    
    [alert addAction:cancleAction];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        [self presentViewController:alert animated:YES completion:nil];
        
    });
    
}
//图片旋转
- (IBAction)ChangeImageClicked:(id)sender {
    
    if (![self.WhiteBoardView GetIsPhoto]) {
        
        return;
        
    }
    
    //顺时针旋转图片，每次旋转90°。
    [self.WhiteBoardView currPhotoRotate90];
    
}
//清笔迹
- (IBAction)CleanTrailClicked:(id)sender {
    
    //清除所有笔迹
    [self.WhiteBoardView cleanTrail];
    
}
//清图片
- (IBAction)CleanPhotoClicked:(id)sender {
    
    //清除图片
    [self.WhiteBoardView cleanPhoto];
    
}
//清画布
- (IBAction)CleanScreenClicked:(id)sender {
    
    //清空画布笔迹和图片
    [self.WhiteBoardView cleanScreen];
    
}

//截图
- (IBAction)ScreenshotsClicked:(id)sender {
    
    [self.WhiteBoardView saveSnapshot];
    
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"图片地址" message:[NSString stringWithFormat:@"已保存到相册"] preferredStyle:UIAlertControllerStyleAlert ];
    
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"确定" style:UIAlertActionStyleDefault handler:nil];
    
    [alertController addAction:cancelAction];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        [self presentViewController:alertController animated:YES completion:nil];
        
    });
    
}
// 改变输入模式
- (IBAction)drawType:(id)sender {
    ((UIButton *)sender).selected = !((UIButton *)sender).selected;
    [self.WhiteBoardView SetDrawType:((UIButton *)sender).selected];
}


#pragma mark - ========== ImagePickerDelegate ===========

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    
    __weak __block id weakPicker = picker;
    
    [picker dismissViewControllerAnimated:YES completion:^{
        
        [weakPicker removeFromParentViewController];
        
    }];
    
}
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<NSString *,id> *)info{
    
    if ([[info objectForKey:UIImagePickerControllerMediaType] isEqualToString:@"public.image"]) {
        
        UIImage* image = [info objectForKey:@"UIImagePickerControllerOriginalImage"];
        
        NSString *path = [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"image1"];
        
        [UIImagePNGRepresentation(image) writeToFile:path atomically:YES];
        
        UIGraphicsEndImageContext();
        
        //根据文件地址插入图片
        [self.WhiteBoardView insterPhotoWithPath:path];
        
        __weak __block id weakPicker = picker;
        
        [picker dismissViewControllerAnimated:YES completion:^{
            
            [weakPicker removeFromParentViewController];
            
            weakPicker = nil;
            
        }];
        
        image = nil;
    }
}

#pragma mark- ========== Other===========

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
