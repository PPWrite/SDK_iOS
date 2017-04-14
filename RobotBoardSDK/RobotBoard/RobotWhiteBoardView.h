//
//  RobotWhiteBoardView.h
//  RobotWhiteBoardView
//
//  Created by JMS on 2016/11/17.
//  Copyright © 2016年 Robot.cn. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "RobotPenManager.h"
#import "WhiteBoardHeader.h"
#import "PhotoImgView.h"
@class PhotoImage;
@protocol WhiteBoardViewDelegate <NSObject>
@required
//获取当前用户ID
- (long)getCurrUserId;
//大于0表示是橡皮擦
- (int)getIsRubber;
//获取橡皮擦宽度 默认为当前画笔宽度*10
- (float)getRubberWith;
//获取当前笔记本Key
- (NSString *)getNoteKey;
- (NSString *)getNoteTitle;
//获取笔颜色
- (UIColor *)getPenColor;
//获取笔的粗细
- (CGFloat)getPenWeight;
//获取压感
- (int)getIsPressure;
- (void)isDrawing:(BOOL)drawing;
@optional
- (void)GetWhiteBoardState:(NSDictionary *)StateInfo;// 获取白板状态信息
- (void)GetVideoRecordState:(NSDictionary *)StateInfo; // 获取视频录制状态信息
//- (void)GetEndPercent:(int)percent; // 获取停止录制百分比
- (void)GetVideoTime:(float)Seconds; //获取录制时间
@end
@interface RobotWhiteBoardView : UIView
@property (nonatomic, assign) DeviceType deviceType;
@property (nonatomic, assign) int isHorizontal;
@property (nonatomic, weak) id<WhiteBoardViewDelegate> whiteBoardDelegate;
@property (nonatomic, copy)NSString *blockKey;
@property (nonatomic, assign)BOOL isConnected;
@property (nonatomic, assign) int TotalPage;
@property (nonatomic, assign) int CurrentPage;
@property (nonatomic, assign) int romate;
@property (nonatomic, strong) PhotoImgView *PhotoImgV;
@property (nonatomic, strong) NSMutableDictionary *tagDict;
@property (nonatomic, strong) NSMutableDictionary *tagPointDict;

@property (nonatomic, strong) UILabel *pageLb;//底部标题、页码信息
/**
 设置画板
 */
- (void)setDrawAreaFrame:(CGRect)frame;
/**
 设置背景
 */
- (void)setBgPhoto:(NSString *)path;
- (void)setBgIntColor:(int)intColor;
- (void)setBgColor:(UIColor *)color;
/**
 设置 画笔图标
 */
- (void)setPenIcon:(UIImage *)image;
/**
 设备类型
 */
- (void)setDeviceType:(DeviceType)deviceType;
- (DeviceType)getDeviceType;
/**
 是否横屏
 */
- (void)setIsHorizontal:(int)isHorizontal;
- (int)getIsHorizontal;
//笔记画点
- (void)drawLine:(PenPoint *)penPoint;
//刷新所有
- (void)RefreshAll;
//翻页
- (void)nextPage;
- (void)frontPage;
- (void)NewNextPage;

- (BOOL)GetIsFirstPage;
- (BOOL)GetIsLastPage;
/**
 获取当前页的页码
 
 @return 当前页的页码
 */
- (int)getCurrentPage;

/**
 根据页码跳转到指定页面
 
 @param page 页码（显示的页码）
 */
- (void)turnToPageWithPage:(int)page;


/**
 获取笔记总页数
 
 @return 笔记总页数
 */
- (int)getTotalPage;

/**
 获取当前页面的Block
 
 @return 当前页面的Block
 */
- (NSString *)getCurrentBlock;
//获取当前是否是图片编辑状态
- (BOOL)getIsPhotoEdit;
- (BOOL)GetIsPhoto;
- (DrawType)GetDrawType;
- (void)SetDrawType:(DrawType)Type;
////获取插入的图片数量
//- (int)getPhotoCount;
- (void)setPhotoScaleType:(ScaleType)type;
//设置图片编辑模式
- (void)setPhotoEdit:(BOOL)enblePhotoEdit;
//插入图片
- (void)insterPhotoWithPath:(NSString *)Path;
- (void)insterPhotoWithUrls:(NSArray *)urlsArray;
- (void)insterLivePhotoWithUrls:(NSArray *)urlsArray;
//清除全部资源
- (void)cleanScreen;
//清除画布上的所有图片
- (void)cleanPhoto;
/**
 清除笔记内容
 */
- (void)cleanTrail;
//删除分页
- (void)delCurrPage;
//旋转当前图片,每次旋转90°
- (void)currPhotoRotate90;
//删除当前编辑图片
//- (void)delCurrEditPhoto;
//保存截图
- (UIImage *)saveSnapshot;
- (void)getDeviceEvent:(DeviceEventType)Type;
- (BOOL)GetIsDrawing;
- (void)SendStateInfo:(NSDictionary *)StateInfo;
- (void)SaveImageNoteSql:(PhotoImage *)photo;
- (void)saveSQLWithTag:(NSString *)tag ForFull:(BOOL)isFull;
- (void)drawByHand:(UIPanGestureRecognizer *)pan;
- (void)handlePinches:(UIPinchGestureRecognizer *)pinch;
- (void)RefreshNote;
- (CGPoint)getOriginalPointWith:(CGPoint)scenePoint;
- (CGSize)getOriginalSizeWith:(CGSize)sceneSize;
-(void)SetLiveTrailsWith:(RobotTrails *)model;
-(void)SetLiveImageWith:(RobotTrails *)model;
@end
