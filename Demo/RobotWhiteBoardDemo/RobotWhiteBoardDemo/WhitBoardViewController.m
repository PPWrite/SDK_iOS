//
//  WhitBoardViewController.m
//  RobotWhiteBoardDemo
//
//  Created by Caffrey on 2020/4/7.
//  Copyright © 2020 robot. All rights reserved.
//

#import "WhitBoardViewController.h"
#import <AVKit/AVKit.h>
#import <RobotSimpleWhiteboard/RobotSimpleWhiteboard.h>
#import <RobotViewRecord/RobotViewRecord.h>

#import <RobotPen/RobotPen.h>

#import "MoviesListView.h"

#define kPenMaxWidth 30.0
#define kEraserMaxWidth 100.0

#define WEAK_SELF __weak typeof(self) wself = self;
#define STRONG_SELF __strong typeof(wself) self = wself;

typedef struct RBTPoint {
    CGPoint point;
    short p;
    short s;
} RBTPoint;

@interface WhitBoardViewController ()<RobotPenDelegate> {
    BOOL _isHorizontal;
}
/// 白板
@property (weak, nonatomic) IBOutlet RBTSimpleWhiteboardView *whiteBoardView;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *whiteBoardViewHeight;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *whiteBoardViewWidth;

/// 配置视图
@property (weak, nonatomic) IBOutlet UIStackView *settingView;
/// 配置按钮
@property (weak, nonatomic) IBOutlet UIButton *configureButton;
/// 笔/橡皮选择按钮
@property (weak, nonatomic) IBOutlet UIButton *penOrEraserButton;
/// 笔宽度按钮
@property (weak, nonatomic) IBOutlet UIButton *penWidthButton;
/// 笔颜色按钮
@property (weak, nonatomic) IBOutlet UIButton *penColorButton;
/// 清屏按钮
@property (weak, nonatomic) IBOutlet UIButton *clearButton;
/// 笔锋开关按钮
@property (weak, nonatomic) IBOutlet UIButton *penStrokeButton;

/// 笔宽度调整视图底部距离
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *penWidthChangeViewBottom;
/// 笔宽度调整视图
@property (weak, nonatomic) IBOutlet UIView *penWidthChangeView;
/// 显示笔宽度
@property (weak, nonatomic) IBOutlet UILabel *penWidthLabel;
/// 显示最小笔宽度
@property (weak, nonatomic) IBOutlet UILabel *penWidthMinLabel;
/// 显示最大笔宽度
@property (weak, nonatomic) IBOutlet UILabel *penWidthMaxLabel;
/// 笔宽度调整
@property (weak, nonatomic) IBOutlet UISlider *penWidthSlider;

/// 笔颜色调整视图
@property (weak, nonatomic) IBOutlet UIView *penColorChangeView;
/// 笔颜色调整视图底部距离
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *penColorChangeViewBottom;

/// 录制菜单视图
@property (weak, nonatomic) IBOutlet UIStackView *recordMenuView;
/// 录制菜单视图右边
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *recordMenuViewRight;
/// 显示录制视图按钮
@property (weak, nonatomic) IBOutlet UIButton *showRecordViewButton;
/// 录制按钮
@property (weak, nonatomic) IBOutlet UIButton *recordButton;
/// 已录制的视频列表按钮
@property (weak, nonatomic) IBOutlet UIButton *recordMoviesButton;

/// 录制视图
@property (weak, nonatomic) IBOutlet UIView *recordView;
/// 录制视图右边距离
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *recordViewRight;
/// 暂停/继续录制按钮
@property (weak, nonatomic) IBOutlet UIButton *pauseRecordButton;
/// 停止录制按钮
@property (weak, nonatomic) IBOutlet UIButton *stopRecordButton;
/// 视频列表
@property (weak, nonatomic) IBOutlet MoviesListView *moviesListView;

@property (weak, nonatomic) IBOutlet UIStackView *pageStackView;
/// 页码
@property (weak, nonatomic) IBOutlet UILabel *pageNumLabel;
@property (weak, nonatomic) IBOutlet UILabel *bookNumLabel;

/// 笔icon
@property (nonatomic, strong) UIImageView *penImgView;
/// 橡皮icon
@property (nonatomic, strong) UIImageView *eraserImgView;

/// 可以选择的笔的颜色
@property (nonatomic, copy) NSArray<UIColor *> *penColors;

/// 显示配置
@property (nonatomic, assign) BOOL isShowSettingView;
/// 使用橡皮
@property (nonatomic, assign) BOOL isUseEraser;
/// 显示改变笔宽度的视图
@property (nonatomic, assign) BOOL isShowPenWidthChangeView;
/// 显示改变笔颜色的视图
@property (nonatomic, assign) BOOL isShowPenColorChangeView;
/// 选中的色彩值
@property (nonatomic, assign) NSInteger selectedColorIndex;

/// 录制状态 0: 未录制 1:录制中 2:录制暂停
@property (nonatomic, assign) uint recordStatus;
/// 显示录制视图
@property (nonatomic, assign) BOOL isShowRecordView;
/// 录制视频的路径
@property (nonatomic, strong) NSString *moviePath;
/// 连接的设备
@property (nonatomic, strong) RobotPenDevice *connectDevice;
/// 设备的大小
@property (nonatomic, assign) CGSize connectDeviceSize;
/// 设备的坐标系
@property (nonatomic, assign) RobotPenCoordinateSystem deviceCoordinate;
/// 设备类型
@property (nonatomic, assign) int deviceType;
/// 点阵类型
@property (nonatomic, assign) RobotLatticeSizeType latticeSizeType;
/// 当前页码
@property (nonatomic, assign) NSInteger pageNum;
/// 页码数组
@property (nonatomic, strong) NSMutableArray *pageNums;
/// 当前页码的下标
@property (nonatomic, assign) NSInteger pageIndex;
/// 页码对应的数组
@property (nonatomic, strong) NSMutableDictionary<NSNumber *, NSMutableArray *> *pagePoints;

@end

@implementation WhitBoardViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.isUseEraser = NO;
    self.pageNums = [NSMutableArray array];
    self.pagePoints = [NSMutableDictionary dictionary];

    [self didChangeStatusBarOrientation];
    [self setupSubviews];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didChangeStatusBarOrientation)
                                                 name:UIApplicationDidChangeStatusBarOrientationNotification
                                               object:nil];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    // 遵守RobotPenManager协议，必须实现
    [[RobotPenManager sharePenManager] setPenDelegate:self];

    self.connectDevice = [[RobotPenManager sharePenManager] getConnectDevice];

    [[RobotPenManager sharePenManager] setRobotA5PagedPoint:YES];

    [self setupWhiteboardSize];
}

- (void)dealloc {
    [RBTViewRecorder destroy];
}

#pragma mark - RobotPenDelegate -
- (void)getDeviceState:(DeviceState)State DeviceUUID:(NSString *)uuid {
    switch (State) {
        case DEVICE_CLEANDATA_ONLY_SUCCESS:
            NSLog(@"只擦除数据");
            [self cleanPage];
            break;
        case DEVICE_CLEANDATA_DELETE_SUCCESS:
            NSLog(@"擦除数据并清空离线笔记");
            [self cleanPage];
            break;
        case DEVICE_CLEANDATA_BUILD_SUCCESS:
            NSLog(@"擦除数据并新建离线笔记");
            [self cleanPage];
            break;
        default:
            break;
    }
}

- (void)getDevicePage:(int)page andNoteId:(int)NoteId {
    RobotPenDevice *device = [[RobotPenManager sharePenManager] getConnectDevice];
    if (device.deviceType != self.deviceType || device.latticeSizeType != self.latticeSizeType) {
        self.connectDevice = device;
        [self setupWhiteboardSize];
    }

    for (int i = 0; i < _pageNums.count; i++) {
        NSNumber *hasPage = _pageNums[i];
        if (hasPage.integerValue == page) {
            self.pageIndex = i;
            break;
        }
    }

    [self goPage:@(page)];
}

- (void)getBookID:(int)bookID {
    NSLog(@"点读码变化 %d", bookID);
    self.bookNumLabel.text = [NSString stringWithFormat:@"书码:%d", bookID];
    self.bookNumLabel.hidden = NO;
}

- (void)getPointInfo:(RobotPenPoint *)point {
    if (point.latticeSizeType == RobotLatticeSizeType_Robot_A5 && // 罗博A5本
        ((point.touchState >= 1 && point.touchState <= 3)   ||    // 黑笔书写
         (point.touchState >= 5 && point.touchState <= 7)   ||    // 红笔书写
         (point.touchState >= 9 && point.touchState <= 11)) &&    // 橡皮书写
        [self isRobotA5FunctionalAreaWithPointX:point.originalX y:point.originalY]) {
        // 在功能区域，直接返回
        return;
    }

//    int type = -1;
//    if (point.touchState == RobotPenPointFloat) {
//        type = RBTSWBPointTypeSuspend;
//    }
//    if (point.touchState == RobotPenPointTouchBegin) {
//        type = RBTSWBPointTypeBegan;
//    }
//    if (point.touchState == RobotPenPointTouchMove) {
//        type = RBTSWBPointTypeMoved;
//    }
//    if (point.touchState == RobotPenPointTouchEnd) {
//        type = RBTSWBPointTypeEnded;
//    }
//    if (point.touchState == RobotPenPointLeave) {
//        type = RBTSWBPointTypeLeave;
//    }
//
//    if (type >= 0) {
//        CGPoint cgpoint;
//        int intervalTime = 0;
//        if (self.connectDevice.deviceType == D7) {
//            cgpoint = CGPointMake(point.originalY, point.originalX);
//            intervalTime = point.latticeTime;
//        } else {
//            cgpoint = CGPointMake(point.originalX, point.originalY);
//        }
//
//        [self.whiteBoardView drawDevicePoint:cgpoint
//                                    pressure:point.pressure
//                                   pointType:type
//                           pointIntervalTime:intervalTime
//                                  deviceSize:self.connectDeviceSize
//                            deviceCoordinate:(RBTSWBDeviceCoordinateType)self.connectDevice.function.coordinate];
//    }

    CGPoint cgpoint = [point getScenePointWithSceneWidth:self.whiteBoardView.bounds.size.width
                                             SceneHeight:self.whiteBoardView.bounds.size.height
                                            IsHorizontal:_isHorizontal];

    if (self.isUseEraser) {
        self.eraserImgView.center = cgpoint;
        self.eraserImgView.hidden = point.touchState == RobotPenPointLeave;
        self.penImgView.hidden = YES;
    } else {
        self.penImgView.center = cgpoint;
        self.penImgView.hidden = point.touchState == RobotPenPointLeave;
        self.eraserImgView.hidden = YES;
    }
}

- (void)robotPenReceivedDevicePrimitivePoint:(RobotDeviceOriginPoint)point {
    //NSLog(@"点:{%d, %d}  压力:%d  状态:0x%02x  时间:%d", point.x, point.y, point.p, point.s, point.time);
    if (point.isLattice &&
        point.s != 0x00 &&
        (point.sizeType != RobotLatticeSizeType_A4 &&
         point.sizeType != RobotLatticeSizeType_A5 &&
         point.sizeType != RobotLatticeSizeType_Robot_A5)) {
        NSLog(@"⚠️飞笔了⚠️");
        return;
    }

    if (point.s == 0x00) {
        NSLog(@"======================");
    }

    CGPoint cgpoint;
    if (_connectDevice.deviceType == D7) {
        cgpoint = CGPointMake(point.y, point.x);
    } else {
        cgpoint = CGPointMake(point.x, point.y);
    }

    if (_whiteBoardView.isUseEraser) {
        if (point.s == 0x10 || point.s == 0x20) {
            point.s = 0x30;
        } else if (point.s == 0x11 || point.s == 0x21) {
            point.s = 0x31;
        }
    }

    [_whiteBoardView drawDevicePoint:cgpoint
                            pressure:point.p
                         pointStatus:point.s
                   pointIntervalTime:point.time
                          deviceSize:_connectDeviceSize
                    deviceCoordinate:_deviceCoordinate];

    RBTPoint p = {cgpoint, point.p, point.s};
    [self savePoint:p];
}

#pragma mark - event method -
/// 关闭页码
- (IBAction)closeViewClick:(id)sender {
    [[RobotPenManager sharePenManager] disconnectDevice];
    [self dismissViewControllerAnimated:YES completion:nil];
}

/// 配置按钮点击
- (IBAction)configureBtnClick:(id)sender {
    self.isShowSettingView = !self.isShowSettingView;

    if (self.isShowPenWidthChangeView) {
        self.isShowPenWidthChangeView = false;
    }

    if (self.isShowPenColorChangeView) {
        self.isShowPenColorChangeView = false;
    }
}

/// 选择笔/橡皮按钮点击
- (IBAction)changePenOrEraserClick:(id)sender {
    self.isUseEraser = !self.isUseEraser;
    self.isShowPenWidthChangeView = YES;

    if (self.isShowPenColorChangeView) {
        self.isShowPenColorChangeView = false;
    }
}

/// 清屏按钮点击
- (IBAction)clearButtonClick:(id)sender {
    [self cleanPage];
}

/// 修改笔宽度按钮点击
- (IBAction)penWidthChangeBtnClick:(id)sender {
    self.isShowPenWidthChangeView = !self.isShowPenWidthChangeView;

    if (self.isShowPenColorChangeView) {
        self.isShowPenColorChangeView = false;
    }
}

/// 笔/橡皮宽度改变
- (IBAction)penWidthSliderChanged:(UISlider *)sender {
    if (self.isUseEraser) {
        CGFloat width = kEraserMaxWidth * ((int)(sender.value * 100 + 0.5)) / 100.0;
        width = width < 0.5 ? 0.5 : width;
        self.penWidthLabel.text = [NSString stringWithFormat:@"橡皮 %.1f", width];
        self.whiteBoardView.eraserWidth = width;

        self.eraserImgView.bounds = CGRectMake(0, 0, width, width);
        self.eraserImgView.layer.cornerRadius = width / 2;
    } else {
        CGFloat width = kPenMaxWidth * ((int)(sender.value * 100 + 0.5)) / 100.0;
        width = width < 0.5 ? 0.5 : width;
        self.penWidthLabel.text = [NSString stringWithFormat:@"笔 %.1f", width];
        self.whiteBoardView.penWidth = width;

        CGFloat penImgSize = width < 20 ? 20 : width;
        self.penImgView.bounds = CGRectMake(0, 0, penImgSize, penImgSize);
    }
}

/// 笔颜色按钮点击
- (IBAction)showPenColorBtnClick:(id)sender {
    self.isShowPenColorChangeView = !self.isShowPenColorChangeView;

    if (self.isShowPenWidthChangeView) {
        self.isShowPenWidthChangeView = false;
    }
}

/// 笔颜色改变
- (IBAction)penChangeColorBtnClick:(UIButton *)sender {
    self.selectedColorIndex = sender.tag - 100;
}

/// 显示录制视图
- (IBAction)showRecordViewBtnClick:(id)sender {
    self.isShowRecordView = !self.isShowRecordView;
}

/// 录制
- (IBAction)recordBtnClick:(id)sender {
    if (self.recordStatus == 0) {
        [self startRecord];
    } else if (self.recordStatus == 1) {
        [self pauseRecord];
    } else if (self.recordStatus == 2) {
        [self resumeRecord];
    }
}

/// 停止录制
- (IBAction)stopRecordBtnClick:(id)sender {
    if (self.recordStatus != 0) {
        [self stopRecord];
    }
}

/// 录制列表
- (IBAction)moviesListBtnClick:(id)sender {
    self.moviesListView.hidden = !self.moviesListView.hidden;
    if (!self.moviesListView.hidden) {
        [self.moviesListView reload];
    }
}

- (IBAction)penStrokeBtnClick:(UIButton *)sender {
    sender.selected = !sender.selected;
    self.whiteBoardView.isOpenStroke = sender.selected;
}

- (void)panGRHandle:(UIPanGestureRecognizer *)panGR {
    CGPoint localPoint = [panGR locationInView:panGR.view];
    BOOL showIcon = NO;
    switch (panGR.state) {
        case UIGestureRecognizerStateBegan:
            showIcon = YES;
            [self.whiteBoardView drawPoint:localPoint pointType:RBTSWBPointTypeBegan];
            break;
        case UIGestureRecognizerStateChanged:
            showIcon = YES;
            [self.whiteBoardView drawPoint:localPoint pointType:RBTSWBPointTypeMoved];
            break;
        case UIGestureRecognizerStateEnded:
            showIcon = NO;
            [self.whiteBoardView drawPoint:localPoint pointType:RBTSWBPointTypeEnded];
            break;
        default:
            break;
    }

    if (self.isUseEraser) {
        self.eraserImgView.center = localPoint;
        self.eraserImgView.hidden = !showIcon;
        self.penImgView.hidden = YES;
    } else {
        self.penImgView.center = localPoint;
        self.penImgView.hidden = !showIcon;
        self.eraserImgView.hidden = YES;
    }
}

- (void)didChangeStatusBarOrientation {
    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
    _isHorizontal = orientation == UIDeviceOrientationLandscapeLeft || orientation == UIDeviceOrientationLandscapeRight;
    [self.whiteBoardView setIsHorizontal:_isHorizontal];
    [self setupWhiteboardSize];
}

- (IBAction)previousButtonClick:(id)sender {
    if (_pageNums.count == 0) {
        return;
    }
    if (_pageIndex != 0) {
        self.pageIndex -= 1;
    }

    [self goPage:_pageNums[_pageIndex]];
}

- (IBAction)nextButtonClick:(id)sender {
    if (_pageNums.count == 0) {
        return;
    }
    if (_pageIndex != _pageNums.count - 1) {
        self.pageIndex += 1;
    }

    [self goPage:_pageNums[_pageIndex]];
}
#pragma mark - privacy method -
- (void)setupSubviews {
    [self setupCornerShadowView:self.penWidthChangeView];
    [self setupCornerShadowView:self.penColorChangeView];

    [self setupChangeColorView];

    UIPanGestureRecognizer *panGR = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(panGRHandle:)];
    [self.whiteBoardView addGestureRecognizer:panGR];
    self.whiteBoardView.userInteractionEnabled = YES;

    [self.whiteBoardView addSubview:self.penImgView];
    [self.whiteBoardView addSubview:self.eraserImgView];
    [self.whiteBoardView setIsHorizontal:_isHorizontal];

    [self selectedColor];

    self.pauseRecordButton.layer.cornerRadius = 15;
    self.pauseRecordButton.clipsToBounds = YES;

    self.stopRecordButton.layer.cornerRadius = 15;
    self.stopRecordButton.clipsToBounds = YES;

    [self setupCornerShadowView:self.recordView];

    self.moviesListView.superVC = self;

    self.penStrokeButton.selected = self.whiteBoardView.isOpenStroke;
}

- (void)setupCornerShadowView:(UIView *)view {
    view.layer.cornerRadius = 15;
    view.layer.shadowColor = UIColor.blackColor.CGColor;
    view.layer.shadowOpacity = 0.3;
    view.layer.shadowRadius = 5;
    view.layer.shadowOffset = CGSizeMake(0, 2);
}

- (void)setupChangeColorView {
    UIView *colorStactView = self.penColorChangeView.subviews.firstObject;
    for (UIView *view in colorStactView.subviews) {
        view.layer.cornerRadius = 15;
        if (view.tag - 100 == self.selectedColorIndex) {
            view.layer.borderColor = UIColor.darkGrayColor.CGColor;
        } else {
            view.layer.borderColor = UIColor.lightGrayColor.CGColor;
        }
        view.layer.borderWidth = 5;
        view.clipsToBounds = YES;
        view.backgroundColor = self.penColors[view.tag - 100];
    }
}

- (void)selectedColor {
    UIView *colorStactView = self.penColorChangeView.subviews.firstObject;
    for (UIView *view in colorStactView.subviews) {
        if (view.tag - 100 == self.selectedColorIndex) {
            view.layer.borderColor = UIColor.darkGrayColor.CGColor;
        } else {
            view.layer.borderColor = UIColor.lightGrayColor.CGColor;
        }
    }

    self.whiteBoardView.penColor = self.penColors[self.selectedColorIndex];
}

- (void)setupRecordView {
    if (self.recordStatus == 0) {
        BOOL isShow = self.isShowRecordView;
        [UIView animateWithDuration:0.3
                              delay:0
                            options:UIViewAnimationOptionCurveEaseInOut
                         animations:^{
            self.recordButton.alpha = isShow ? 1 : 0;
            self.recordButton.hidden = isShow ? NO : YES;

            self.recordMoviesButton.alpha = isShow ? 1 : 0;
            self.recordMoviesButton.hidden = isShow ? NO : YES;

            self.recordMenuView.alpha = isShow ? 1 : 0.5;
            self.recordMenuViewRight.constant = 15;

            self.recordView.alpha = 0;
            self.recordViewRight.constant = -65;

            [self.view layoutIfNeeded];
        } completion:nil];

        if (!isShow) {
            self.moviesListView.hidden = YES;
        }
    } else {
        [UIView animateWithDuration:0.3
                              delay:0
                            options:UIViewAnimationOptionCurveEaseInOut
                         animations:^{
            self.recordView.alpha = 1;
            self.recordViewRight.constant = 15;

            self.recordMenuView.alpha = 0;
            self.recordMenuViewRight.constant = -65;

            [self.view layoutIfNeeded];
        } completion:nil];

        self.moviesListView.hidden = YES;
    }

    NSString *pauseBtnImg = @"play";
    if (self.recordStatus == 1) pauseBtnImg = @"pause";

    [self.pauseRecordButton setImage:[UIImage imageNamed:pauseBtnImg] forState:UIControlStateNormal];
}

- (void)setupWhiteboardSize {
    if (self.connectDevice && self.connectDevice.deviceType != 0) {
        self.connectDeviceSize = self.connectDevice.function.deviceSize;
        self.deviceCoordinate = self.connectDevice.function.coordinate;
        self.deviceType = self.connectDevice.deviceType;
        self.latticeSizeType = self.connectDevice.latticeSizeType;

        CGFloat contentHeight = self.view.bounds.size.height - self.view.safeAreaInsets.top - self.view.safeAreaInsets.bottom;
        CGFloat contentWidth = self.view.bounds.size.width - self.view.safeAreaInsets.left - self.view.safeAreaInsets.right;

        CGFloat contentWHScale = contentWidth / contentHeight;

        CGFloat deviceWHScale = self.connectDeviceSize.width / self.connectDeviceSize.height;

        if (_isHorizontal) {
            deviceWHScale = self.connectDeviceSize.height / self.connectDeviceSize.width;
        }

        if (contentWHScale > deviceWHScale) {
            self.whiteBoardViewHeight.constant = contentHeight;
            self.whiteBoardViewWidth .constant = contentHeight * deviceWHScale;
        } else {
            self.whiteBoardViewWidth.constant = contentWidth;
            self.whiteBoardViewHeight.constant = contentWidth / deviceWHScale;
        }

        self.whiteBoardView.drawSize = CGSizeMake(self.whiteBoardViewWidth.constant, self.whiteBoardViewHeight.constant);
    }
}


// 罗博A5本笔颜色区域
// {minx,  miny,  maxx,  maxy}
// {4400,  20250, 5600,  21000}
static CGRect const kBlackPenColorArea  = {4400,  20250, 1200, 750};
// {5900,  20250, 6800,  21000}
static CGRect const kRedPenColorArea    = {5900,  20250, 900,  750};
// {7100,  20250, 8400,  21000}
static CGRect const kGreenPenColorArea  = {7100,  20250, 1300, 750};
// {8700,  20250, 9700,  21000}
static CGRect const kBluePenColorArea   = {8700,  20250, 1000, 750};

// 罗博A5本笔宽度区域
// {10400, 20250, 11100, 21000}
static CGRect const kThinPenWidthArea   = {10400, 20250, 700,  750};
// {11400, 20250, 12100, 21000}
static CGRect const kMediumPenWidthArea = {11400, 20250, 700,  750};
// {12400, 20250, 13100, 21000}
static CGRect const kBoldPenWidthArea   = {12400, 20250, 700,  750};

/// 点所在位置是否罗博A5本的功能区域
/// @param px 点x
/// @param py 点y
- (BOOL)isRobotA5FunctionalAreaWithPointX:(CGFloat)px y:(CGFloat)py {
    BOOL inRect = NO;

    CGPoint point = {px, py};

    if (CGRectContainsPoint(kBlackPenColorArea, point)) {
        inRect = YES;

        if (![self.whiteBoardView.penColor isEqual:UIColor.blackColor]) {

            self.whiteBoardView.penColor = UIColor.blackColor;
        }

    } else if (CGRectContainsPoint(kRedPenColorArea, point)) {
        inRect = YES;

        if (![self.whiteBoardView.penColor isEqual:UIColor.redColor]) {

            self.whiteBoardView.penColor = UIColor.redColor;
        }

    } else if (CGRectContainsPoint(kGreenPenColorArea, point)) {
        inRect = YES;

        if (![self.whiteBoardView.penColor isEqual:UIColor.greenColor]) {

            self.whiteBoardView.penColor = UIColor.greenColor;
        }

    } else if (CGRectContainsPoint(kBluePenColorArea, point)) {
        inRect = YES;

        if (![self.whiteBoardView.penColor isEqual:UIColor.blueColor]) {

            self.whiteBoardView.penColor = UIColor.blueColor;
        }

    } else if (CGRectContainsPoint(kThinPenWidthArea, point)) {
        inRect = YES;

        if (self.whiteBoardView.penWidth != 0.5) {

            self.whiteBoardView.penWidth = 0.5;
        }

    } else if (CGRectContainsPoint(kMediumPenWidthArea, point)) {
        inRect = YES;

        if (self.whiteBoardView.penWidth != 1.5) {

            self.whiteBoardView.penWidth = 1.5;
        }

    } else if (CGRectContainsPoint(kBoldPenWidthArea, point)) {
        inRect = YES;

        if (self.whiteBoardView.penWidth != 3) {

            self.whiteBoardView.penWidth = 3;
        }
    }

    return inRect;
}

#pragma mark - record -
- (void)startRecord {
    NSError *err = [RBTViewRecorder.shared startRecordView:self.view
                                                 videoSize:self.view.bounds.size
                                         microphoneEnabled:YES
                                                saveInPath:self.moviePath
                                                 frameRate:RBTViewRecordFrameRate10];

    if (err) {
        NSLog(@"❌ 开始录制失败 %@", err);
        self.moviePath = nil;
        return;
    }

    self.recordStatus = 1;
}

- (void)pauseRecord {
    [RBTViewRecorder.shared pauseRecord];
    self.recordStatus = 2;
}

- (void)resumeRecord {
    [RBTViewRecorder.shared resumeRecord];
    self.recordStatus = 1;
}

- (void)stopRecord {

    WEAK_SELF
    [RBTViewRecorder.shared stopRecord:^(NSString * _Nonnull path) {
        STRONG_SELF
        dispatch_async(dispatch_get_main_queue(), ^{
            AVPlayerViewController *playVC = [[AVPlayerViewController alloc] init];
            playVC.player = [AVPlayer playerWithURL:[NSURL fileURLWithPath:path]];
            [self presentViewController:playVC animated:YES completion:nil];

            self.moviePath = nil;
        });
    }];

    self.recordStatus = 0;
}

#pragma 页面处理

- (void)cleanPage {
    if (_pageNums.count != 0) {
        NSNumber *page = _pageNums[_pageIndex];
        NSMutableArray<NSValue *> *points = _pagePoints[page];
        [points removeAllObjects];
    }
    [self.whiteBoardView clear];
}

/// 保存点
- (void)savePoint:(RBTPoint)point {
    if (_pageNum == 0) {
        return;
    }
    NSNumber *page = @(_pageNum);

    NSMutableArray *points = _pagePoints[page];
    if (!points) {
        points = [NSMutableArray array];
        _pagePoints[page] = points;

        BOOL hasCurPage = NO;
        for (int i = 0; i < _pageNums.count; i++) {
            NSNumber *hasPage = _pageNums[i];
            if ([hasPage isEqualToNumber:page]) {
                self.pageIndex = i;
                hasCurPage = YES;
                break;
            }
        }

        if (!hasCurPage) {
            [_pageNums addObject:page];
            self.pageIndex = _pageNums.count - 1;
            self.pageNumLabel.text = [NSString stringWithFormat:@"页码%ld (%ld/%ld)", (long)_pageNum, _pageIndex + 1, _pageNums.count];
        }
    }

    [points addObject:[NSValue valueWithBytes:&point objCType:@encode(RBTPoint)]];
}

/// 到指定页面
- (void)goPage:(NSNumber *)page {
    self.pageNum = page.integerValue;
    NSArray<NSValue *> *points = _pagePoints[page];

    [self.whiteBoardView startBatchDrawing];

    for (NSValue *pv in points) {
        RBTPoint point;
        [pv getValue:&point];
        [self.whiteBoardView drawDevicePoint:point.point
                                    pressure:point.p
                                 pointStatus:point.s
                                  deviceSize:_connectDeviceSize
                            deviceCoordinate:_deviceCoordinate];
    }

    [self.whiteBoardView endBatchDrawing:^{

    }];
}

#pragma mark - setter/getter -
- (void)setIsShowSettingView:(BOOL)isShowSettingView {
    _isShowSettingView = isShowSettingView;

    [UIView animateWithDuration:0.3
                          delay:0
                        options:UIViewAnimationOptionCurveEaseInOut
                     animations:^{
        self.clearButton.alpha = isShowSettingView ? 1 : 0;
        self.clearButton.hidden = isShowSettingView ? NO : YES;

        self.penColorButton.alpha = isShowSettingView ? 1 : 0;
        self.penColorButton.hidden = isShowSettingView ? NO : YES;

        self.penWidthButton.alpha = isShowSettingView ? 1 : 0;
        self.penWidthButton.hidden = isShowSettingView ? NO : YES;

        self.penOrEraserButton.alpha = isShowSettingView ? 1 : 0;
        self.penOrEraserButton.hidden = isShowSettingView ? NO : YES;

        self.penStrokeButton.alpha = isShowSettingView ? 1 : 0;
        self.penStrokeButton.hidden = isShowSettingView ? NO : YES;

        self.settingView.alpha = isShowSettingView ? 1 : 0.5;
    } completion:nil];
}

- (void)setIsUseEraser:(BOOL)isUseEraser {
    _isUseEraser = isUseEraser;

    NSString *imgName = isUseEraser ? @"eraser" : @"pen";
    [self.penOrEraserButton setImage:[UIImage imageNamed:imgName]
                            forState:UIControlStateNormal];

    if (isUseEraser) {
        self.penWidthSlider.value = self.whiteBoardView.eraserWidth / kEraserMaxWidth;
        self.penWidthLabel.text = [NSString stringWithFormat:@"橡皮 %.1f", self.whiteBoardView.eraserWidth];
        self.penWidthMaxLabel.text = [NSString stringWithFormat:@"%.0f", kEraserMaxWidth];
    } else {
        self.penWidthSlider.value = self.whiteBoardView.penWidth / kPenMaxWidth;
        self.penWidthLabel.text = [NSString stringWithFormat:@"笔 %.1f", self.whiteBoardView.penWidth];
        self.penWidthMaxLabel.text = [NSString stringWithFormat:@"%.0f", kPenMaxWidth];
    }

    self.whiteBoardView.isUseEraser = self.isUseEraser;
}

- (void)setIsShowPenWidthChangeView:(BOOL)isShowPenWidthChangeView {
    _isShowPenWidthChangeView = isShowPenWidthChangeView;

    BOOL isShow = isShowPenWidthChangeView;
    [UIView animateWithDuration:0.3
                          delay:0
                        options:UIViewAnimationOptionCurveEaseInOut
                     animations:^{
        self.penWidthChangeViewBottom.constant = isShow ? 80 : -110;
        self.penWidthChangeView.alpha = isShow ? 1 : 0;
        [self.view layoutIfNeeded];
    } completion:nil];
}

- (void)setIsShowPenColorChangeView:(BOOL)isShowPenColorChangeView {
    _isShowPenColorChangeView = isShowPenColorChangeView;

    BOOL isShow = isShowPenColorChangeView;
    [UIView animateWithDuration:0.3
                          delay:0
                        options:UIViewAnimationOptionCurveEaseInOut
                     animations:^{
        self.penColorChangeViewBottom.constant = isShow ? 80 : -90;
        self.penColorChangeView.alpha = isShow ? 1 : 0;
        [self.view layoutIfNeeded];
    } completion:nil];
}

- (void)setSelectedColorIndex:(NSInteger)selectedColorIndex {
    _selectedColorIndex = selectedColorIndex;
    [self selectedColor];
}

- (NSArray<UIColor *> *)penColors {
    if (nil == _penColors) {
        _penColors = @[UIColor.blackColor,
                       UIColor.redColor,
                       UIColor.orangeColor,
                       UIColor.yellowColor,
                       UIColor.greenColor,
                       UIColor.blueColor,
                       UIColor.whiteColor];
    }

    return _penColors;
}

- (UIImageView *)penImgView {
    if (nil == _penImgView) {
        _penImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"icon_pen"]];
        _penImgView.frame = CGRectMake(0, 0, 20, 20);
        _penImgView.hidden = true;

        _penImgView.layer.anchorPoint = CGPointMake(0.1, 0.9);
        _penImgView.layer.shadowColor = UIColor.whiteColor.CGColor;
        _penImgView.layer.shadowRadius = 1;
        _penImgView.layer.shadowOpacity = 0.3;
        _penImgView.layer.shadowOffset = CGSizeMake(0, 0);
    }

    return _penImgView;
}

- (UIImageView *)eraserImgView {
    if (nil == _eraserImgView) {
        _eraserImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"eraser"]];
        CGFloat eraserWidth = self.whiteBoardView.eraserWidth;
        _eraserImgView.frame = CGRectMake(0, 0, eraserWidth, eraserWidth);
        _eraserImgView.hidden = true;
        _eraserImgView.clipsToBounds = YES;
        _eraserImgView.backgroundColor = UIColor.darkGrayColor;
        _eraserImgView.alpha = 0.5;

        _eraserImgView.layer.cornerRadius = eraserWidth/2;
    }

    return _eraserImgView;
}

- (void)setIsShowRecordView:(BOOL)isShowRecordView {
    _isShowRecordView  = isShowRecordView;

    [self setupRecordView];
}

- (void)setRecordStatus:(uint)recordStatus {
    _recordStatus = recordStatus;

    [self setupRecordView];
}

- (NSString *)moviePath {
    if (nil == _moviePath) {
        NSDate *date = [NSDate date];
        NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
        dateFormatter.dateFormat = @"yyyy_MM_dd-hh_mm_ss";
        NSString *movieName = [NSString stringWithFormat:@"%@.mp4", [dateFormatter stringFromDate:date]];
        _moviePath = [NSTemporaryDirectory() stringByAppendingPathComponent:movieName];

        NSLog(@"视频路径 %@", _moviePath);
    }

    return _moviePath;
}

- (void)setPageNum:(NSInteger)pageNum {
    if (_pageNum != pageNum) {
        NSLog(@"页码变化, 旧页码:%ld  新页码:%ld", (long)_pageNum, (long)pageNum);
    }
    _pageNum = pageNum;

    self.pageNumLabel.text = [NSString stringWithFormat:@"页码%ld (%ld/%ld)", (long)_pageNum, _pageIndex + 1, _pageNums.count];
    self.pageStackView.hidden = NO;
    [self.whiteBoardView clear];
}

@end
