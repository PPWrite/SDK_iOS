//
//  WhiteBoardViewController.m
//  RobotBoardSDKDemo
//
//  Created by JMS on 2017/2/21.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "WhiteBoardViewController.h"
#import "RobotWhiteBoardView.h"
#import "Header.h"
#import "RobotSqlManager.h"

static int interval_Board = 10;

@interface WhiteBoardViewController ()<WhiteBoardViewDelegate,RobotPenDelegate>
{
    BOOL isHorizontal; //是否横屏
    
    DeviceType DeviceTypes;//设备类型
    
}
@property (nonatomic, weak) IBOutlet UIButton *BackButton;//返回按钮

@property (nonatomic, weak) IBOutlet UIButton *CleanButton;//清除按钮

@property (nonatomic, weak) IBOutlet UIView *WBBView;//白板背景

@property (nonatomic, strong) RobotWhiteBoardView *WhiteBoardView;//白板

@property (nonatomic, strong) UIColor *PenColor;//笔迹颜色

@property (nonatomic, assign) CGFloat PenWidth;//笔迹的宽度

@property (nonatomic, copy) NSString *NoteKey;//笔记的NoteKey（唯一标识） 根据这个Key值对笔记进行操作

@property (nonatomic, copy) NSString *NoteTitle;//笔记的标题
@end

@implementation WhiteBoardViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    DeviceTypes = T7;//已1为例，具体看电磁板设备类型
    
    [self BulidWhiteBoard];//初始化白板
    
    [self.BackButton addTarget:self action:@selector(BackButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    [self.CleanButton addTarget:self action:@selector(CleanButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    // Do any additional setup after loading the view from its nib.
}

- (void)viewWillAppear:(BOOL)animated{
    
    //笔服务代理设置，必须实现。
    [[RobotPenManager sharePenManager] setPenDelegate:self];
    
    //获取当前连接设备
    RobotPenDevice *device = [[RobotPenManager sharePenManager] getConnectDevice];
    
    DeviceTypes = device.deviceType?device.deviceType:T7;//用于setDeviceType传值
    
    //数据库
    [RobotSqlManager checkRobotSqlManager]; //检测 数据库
    
    // 检查笔记是否存在
    if (![RobotSqlManager checkNoteWithNoteKey:@"WB"]) {
        
        [self BuildTempNote];   // 创建 一个NoteKey = @"WB"的笔记
        
    }
    
    
    //白板信息
    _NoteKey = @"WB";//用于getNoteKey传值
    
    _NoteTitle = @"白板";//用于getNoteTitle传值
    
    _PenColor = [UIColor redColor];//用于getPenColor传值
    
    _PenWidth = 1;//用于getPenWeight传值
    
    [self.WhiteBoardView SetDrawType:Gesture];// 输入的方式 （0:手、1:笔）
    
    [self setWB];   //设置画板并刷新
    
}

#pragma mark- ========== 白板实现===========
/**
 白板创建
 */
- (void)BulidWhiteBoard{
    
    
    self.WhiteBoardView = [[RobotWhiteBoardView alloc] init];//此处不要设置大小（在setWB方法里设置）
    self.WhiteBoardView.whiteBoardDelegate = self; //设置画板代理，必须实现
    [self.WBBView addSubview:self.WhiteBoardView];  // 添加视图
    [self.WhiteBoardView setBgColor:BG_NoteColor];  // 设置 背景颜色
    
}
- (void)setWB{
    
    //以下方法必须实现并且调用顺序不可变。
    [self.WhiteBoardView setDeviceType: DeviceTypes];   //设置设备类型（必须设置）
    
    [self.WhiteBoardView setIsHorizontal:isHorizontal]; //设置画板的横竖方向 0：竖 1：横（必须设置）
    
    [self.WhiteBoardView setSceneSize:CGRectMake(interval_Board , interval_Board , ScreenWidth - 2 * interval_Board,ScreenHeight - 2 * interval_Board - 64)]; //设置白板的Frame（根据传入的frame自动设置,必须设置））
    
    [self.WhiteBoardView RefreshAll];   //刷新白板内容（本地数据库操作,用不到数据库的可以不写）
    
}

-(void)BuildTempNote
{
    
    //创建笔记的Model
    RobotNote *notemodel =  [[RobotNote alloc]init];// 创建笔记Model
    
    notemodel.NoteKey = @"WB";//笔记的NoteKey（唯一标识），必填
    
    notemodel.Title = @"白板";//笔记的标题
    
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


#pragma mark - ========== 白板协议（信息获取类） ===========

//电磁板报点数据
-(void)getPointInfo:(RobotPenPoint *)point{
    
    //    NSLog(@"%hd %hd",point.originalX,point.originalY);
    
    //画板画线
    [self.WhiteBoardView drawLine:point];
    
}

//白板相关回调，用于返回白板状态信息，具体状态请查看RobotWhiteBoardView.h文件。
- (void)GetWhiteBoardState:(WBMessageType)State content:(NSString *)Info{
    
//    NSLog(@"WB StateInfo = %@",State);
    
}

#pragma mark- ========== Other===========

-(void)BackButtonPressed:(UIButton *)sender
{
    
    [self dismissViewControllerAnimated:YES completion:nil];
    
}
-(void)CleanButtonPressed:(UIButton *)sender
{
    
    [self.WhiteBoardView cleanScreen];//清除画板所有内容
    
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
