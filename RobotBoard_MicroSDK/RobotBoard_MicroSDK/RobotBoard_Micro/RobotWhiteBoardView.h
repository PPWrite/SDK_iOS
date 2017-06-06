//
//  RobotWhiteBoardView.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RobotPenManager.h"
#import "WhiteBoardHeader.h"
#import "RobotPhotoImageView.h"
@class RobotPhotoImage;


@protocol WhiteBoardViewDelegate <NSObject>

@required

/**
 设置当前用户ID

 @return <#return value description#>
 */
- (long)getCurrUserId;
/**
 设置是否是橡皮擦模式，1：橡皮擦模式 0：非橡皮擦

 @return <#return value description#>
 */
- (int)getIsRubber;
//
/**
 设置橡皮擦宽度 默认为当前画笔宽度*10

 @return <#return value description#>
 */
- (float)getRubberWith;

/**
 设置当前笔记本Key

 @return <#return value description#>
 */
- (NSString *)getNoteKey;

/**
 设置当前笔记标题

 @return <#return value description#>
 */
- (NSString *)getNoteTitle;

/**
 设置笔迹颜色

 @return <#return value description#>
 */
- (UIColor *)getPenColor;

/**
 设置笔的粗细

 @return <#return value description#>
 */
- (CGFloat)getPenWeight;

/**
 设置压感模式 1：压感模式 2：非压感模式

 @return <#return value description#>
 */
- (int)getIsPressure;


/**
 是否是正在输入（书写）

 @param drawing <#drawing description#>
 */
- (void)isDrawing:(BOOL)drawing;

@optional

/**
 获取白板状态信息

 @param StateInfo <#StateInfo description#>
 */
- (void)GetWhiteBoardState:(NSDictionary *)StateInfo;

/**
 获取视频录制白板状态信息

 @param StateInfo <#StateInfo description#>
 */
- (void)GetVideoRecordState:(NSDictionary *)StateInfo;
//- (void)GetEndPercent:(int)percent; // 获取停止录制百分比

/**
 获取录制时间

 @param Seconds <#Seconds description#>
 */
- (void)GetVideoTime:(float)Seconds;

@end




@interface RobotWhiteBoardView : UIView
/** 设备类型*/
@property (nonatomic, assign) DeviceType deviceType;
/** 是否是横屏*/
@property (nonatomic, assign) int isHorizontal;
/** 白板代理*/
@property (nonatomic, weak) id<WhiteBoardViewDelegate> whiteBoardDelegate;
/** 当前笔记的blockkey*/
@property (nonatomic, copy) NSString *blockKey;
/** 是否连接设备*/
@property (nonatomic, assign) BOOL isConnected;
/** 笔记的总页数*/
@property (nonatomic, assign) int TotalPage;
/** 笔记所在的当前页*/
@property (nonatomic, assign) int CurrentPage;
/** 图片的旋转角度*/
@property (nonatomic, assign) int romate;
/** 图片的视图*/
@property (nonatomic, strong) RobotPhotoImageView *PhotoImgV;
/** 笔记名称Label*/
@property (nonatomic, strong) UILabel *titleLb;
/** 页码信息Label*/
@property (nonatomic, strong) UILabel *pageLb;
/** 是否保存笔记截图，默认为NO*/
@property (nonatomic, assign)BOOL isSaveScreenShot;

@property (nonatomic, strong) NSMutableDictionary *tagDict;
@property (nonatomic, strong) NSMutableDictionary *tagPointDict;

/** --------------------------------------设置类--------------------------------------------------*/

/**
 设置画板显示大小
 */
- (void)setSceneSize:(CGRect)frame;

/**
 设置设备类型
 */
- (void)setDeviceType:(DeviceType)deviceType;


/**
 设置画板方向，1：横屏 0：竖屏，默认为竖屏
 
 @param isHorizontal 是否是横屏
 */
- (void)setIsHorizontal:(int)isHorizontal;


/**
 设置输入模式 0：手模式 1：笔模式
 
 @param Type <#Type description#>
 */
- (void)SetDrawType:(DrawType)Type;

/**
 设置图片编辑模式 YES:编辑模式 NO:非编辑模式
 
 @param enblePhotoEdit <#enblePhotoEdit description#>
 */
- (void)setPhotoEdit:(BOOL)enblePhotoEdit;

/** ************************画板UI设置*************************/

/**
 根据路径设置画板背景图片（平铺）
 
 @param path 图片路径
 */
- (void)setBgPhoto:(NSString *)path;

/**
 根据int颜色设置画板背景颜色
 
 @param intColor intColor
 */
- (void)setBgIntColor:(int)intColor;

/**
 根据颜色设置画板背景颜色
 
 @param color <#color description#>
 */
- (void)setBgColor:(UIColor *)color;


/**
 设置 画笔图标
 */
- (void)setPenIcon:(UIImage *)image;



/**
 设置 不可书写图标 (仅用于笔模式，笔模式下手写提示)
 
 @param image <#image description#>
 */
- (void)setPenModleBanIcon:(UIImage *)image;


/**
 设置图片编辑框的颜色
 
 @param color 默认为透明
 */
- (void)setPhotoEditColor:(UIColor *)color;

/** --------------------------------------获取类--------------------------------------------------*/

/**
 获取画板设备类型
 
 @return <#return value description#>
 */
- (DeviceType)getDeviceType;

/**
 获取画板方向
 
 @return <#return value description#>
 */
- (int)getIsHorizontal;


/**
 是否是笔记第一页
 
 @return <#return value description#>
 */
- (BOOL)GetIsFirstPage;

/**
 是否是笔记最后一页
 
 @return <#return value description#>
 */
- (BOOL)GetIsLastPage;

/**
 获取当前页的页码
 
 @return 当前页的页码
 */
- (int)getCurrentPage;


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



/**
 获取当前是否是图片编辑状态
 
 @return <#return value description#>
 */
- (BOOL)getIsPhotoEdit;

/**
 获取当前页是否有图片
 
 @return <#return value description#>
 */
- (BOOL)GetIsPhoto;


/**
 获取输入模式（手模式或笔模式）
 
 @return <#return value description#>
 */
- (DrawType)GetDrawType;



/**
 获取画布截图
 
 @return <#return value description#>
 */
- (UIImage *)saveSnapshot;



/**
 获取是否是输入状态
 
 @return <#return value description#>
 */
- (BOOL)GetIsDrawing;



/**
 获取当前页笔记的最后更新时间
 
 @return <#return value description#>
 */
-(long)GetEndTime;

/** --------------------------------------使用类--------------------------------------------------*/

/**
 根据坐标点画线方法

 @param penPoint 坐标点
 */
- (void)drawLine:(RobotPenPoint *)penPoint;


/**
 刷新画板
 */
- (void)RefreshAll;


/**
 翻页-->下一页
 */
- (void)nextPage;

/**
 翻页-->上一页
 */
- (void)frontPage;


/**
 在当前页插入下一页（新建页）
 */
- (void)NewNextPage;

/**
 插入多张图片翻页（每一页只有一张图片）

 @param block block
 */
- (void)ImageNextPageWithBlock:(NSString *)block;

/**
 根据页码跳转到指定页面
 
 @param page 页码（显示的页码）
 */
- (void)turnToPageWithPage:(int)page;


/**
 根据路径插入图片

 @param Path <#Path description#>
 */
- (void)insterPhotoWithPath:(NSString *)Path;

/**
 根据路径数组插入多页图片

 @param urlsArray 路径数组
 */
- (void)insterPhotoWithUrls:(NSArray *)urlsArray;

/**
 根据路径数组设置多页图片 PS:尽量使用insterPhotoWithUrls函数

 @param urlsArray <#urlsArray description#>
 */
- (void)insterLivePhotoWithUrls:(NSArray *)urlsArray;


/**
 设置图片的模式
 
 @param type <#type description#>
 */
- (void)setPhotoScaleType:(ScaleType)type;

/**
 顺时针旋转图片,每次旋转90°
 */
- (void)currPhotoRotate90;


/**
 清空画板内容
 */
- (void)cleanScreen;

/**
 清除画板图片
 */
- (void)cleanPhoto;
/**
 清除画板笔记内容
 */
- (void)cleanTrail;


/**
 删除当前页
 */
- (void)delCurrPage;


/**
 根据截图名称保存笔记截图
 路径为NSString *path = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES) firstObject] stringByAppendingString:[NSString stringWithFormat:@"/Robot/NoteSnaps"]] ;
 path/Key
 @param Key 截图名称
 */
- (void)saveNoteSnapshotWith:(NSString *)Key;

/**
 根据截图Key和blockKey保存笔记截图
 路径为NSString *path = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES) firstObject] stringByAppendingString:[NSString stringWithFormat:@"/Robot/NoteShareSnaps/%@",Key"]] ;
 path/blockKey
 @param Key 截图名称
 */
- (void)saveNoteShareSnapshotWith:(NSString *)Key andBlockKey:(NSString *)blockKey;



/**
 根据手势画线
 
 @param pan <#pan description#>
 */
- (void)drawByHand:(UIPanGestureRecognizer *)pan;

/**
 根据手势移动图片
 
 @param pinch <#pinch description#>
 */
- (void)handlePinches:(UIPinchGestureRecognizer *)pinch;

/**
 刷新当前页笔记数据
 */
- (void)RefreshNote;

/** --------------------------------------其他类--------------------------------------------------*/

/**
 设置设备点击事件

 @param Type 设备点击事件
 */
- (void)getDeviceEvent:(DeviceEventType)Type;

/**
 发送画板状态信息

 @param StateInfo <#StateInfo description#>
 */
- (void)SendStateInfo:(NSDictionary *)StateInfo;


/**
 保存图片到数据库

 @param photo 图片模型
 */
- (void)SaveImageNoteSql:(RobotPhotoImage *)photo;

/**
 保存笔记数据到数据库

 @param tag <#tag description#>
 @param isFull <#isFull description#>
 */
- (void)saveSQLWithTag:(NSString *)tag ForFull:(BOOL)isFull;

/**
 获取原始点坐标

 @param scenePoint 屏幕点坐标
 @return 原始点坐标
 */
- (CGPoint)getOriginalPointWith:(CGPoint)scenePoint;

/**
 获取原始设备尺寸

 @param sceneSize 屏幕尺寸
 @return 原始尺寸
 */
- (CGSize)getOriginalSizeWith:(CGSize)sceneSize;


/**
 设置播放笔记的笔迹数据

 @param model <#model description#>
 */
-(void)SetLiveTrailsWith:(RobotTrails *)model;
/**
 设置播放笔记的图片数据
 
 @param model <#model description#>
 */
-(void)SetLiveImageWith:(RobotTrails *)model;

@end
