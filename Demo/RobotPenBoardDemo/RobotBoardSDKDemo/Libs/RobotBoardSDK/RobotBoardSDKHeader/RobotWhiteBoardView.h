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

/*!
 @method
 @abstract 设置当前用户ID
 @result 返回结果
 */
- (long)getCurrUserId;

/*!
 @method
 @abstract 设置是否是橡皮擦模式，1：橡皮擦模式 0：非橡皮擦
 @result 返回结果
 */
- (int)getIsRubber;

/*!
 @method
 @abstract 设置橡皮擦宽度 默认为当前画笔宽度*10
 @result 返回结果
 */
- (float)getRubberWith;

/*!
 @method
 @abstract 设置当前笔记本Key
 @result 返回结果
 */
- (NSString *)getNoteKey;

/*!
 @method
 @abstract 设置当前笔记标题
 @result 返回结果
 */
- (NSString *)getNoteTitle;

/*!
 @method
 @abstract 设置笔迹颜色
 @result 返回结果
 */
- (UIColor *)getPenColor;

/*!
 @method
 @abstract 设置笔的粗细
 @result 返回结果
 */
- (CGFloat)getPenWeight;

/*!
 @method
 @abstract 设置压感模式 1：压感模式 0：非压感模式
 @result 返回结果
 */
- (int)getIsPressure;

/*!
 @method
 @abstract 是否是正在输入（书写）
 @param drawing 布尔值
 */
- (void)isDrawing:(BOOL)drawing;




@optional

/*!
 @method
 @abstract 获取手绘点数据
 @param point 屏幕点
 */
- (void)getTouchPointInfo:(RobotPenUtilPoint *)point;

/*!
 @method
 @abstract 获取轨迹数据
 @param trails 轨迹数据
 */
- (void)getTrailsInfo:(RobotTrails *)trails;
/*!
 @method
 @abstract 获取左上角转换点轨迹数据
 @param trails 轨迹数据
 */
- (void)getTransformsTrailsInfo:(RobotTrails *)trails;

/*!
 @method
 @abstract 获取白板状态信息
 @param State 状态
 @param Info 信息
 多张图片操作只会返回操作失败，不会返回具体第几张，失败的图片自动过滤。
 */
- (void)GetWhiteBoardState:(WBMessageType)State content:(NSString *)Info;

/*!
 @method
 @abstract 获取视频录制白板状态信息
 @param StateInfo 状态
 @param Info 信息
 */
- (void)GetVideoRecordState:(WBVideoMessageType)StateInfo content:(NSString *)Info;

/*!
 @method
 @abstract 获取录制时间
 @param Seconds 秒
 */
- (void)GetVideoTime:(float)Seconds;

/*!
 @method
 @abstract 获取画板截图
 @param image 白板截图
 */
-(void)getWhiteBoardImage:(UIImage *)image;

@end


@interface RobotWhiteBoardView : UIView
/*!
 @property
 @brief 设备类型
 */
@property (nonatomic, assign) DeviceType deviceType;
/*!
 @property
 @brief 是否是横屏
 */
@property (nonatomic, assign) int isHorizontal;
/*!
 @property
 @brief 白板代理
 */
@property (nonatomic, weak) id<WhiteBoardViewDelegate> whiteBoardDelegate;
/*!
 @property
 @brief 当前笔记的blockkey
 */
@property (nonatomic, copy) NSString *blockKey;
/*!
 @property
 @brief 是否连接设备
 */
@property (nonatomic, assign) BOOL isConnected;
/*!
 @property
 @brief 笔记的总页数
 */
@property (nonatomic, assign) int TotalPage;
/*!
 @property
 @brief 笔记所在的当前页
 */
@property (nonatomic, assign) int CurrentPage;
/*!
 @property
 @brief 图片的旋转角度
 */
@property (nonatomic, assign) int romate;
/*!
 @property
 @brief 图片的视图
 */
@property (nonatomic, strong) RobotPhotoImageView *PhotoImgV;
/*!
 @property
 @brief 笔记名称Label
 */
@property (nonatomic, strong) UILabel *titleLb;
/*!
 @property
 @brief 页码信息Label
 */
@property (nonatomic, strong) UILabel *pageLb;
/*!
 @property
 @brief 是否保存笔记截图，默认为NO
 */
@property (nonatomic, assign) BOOL isSaveScreenShot;

@property (nonatomic, strong) NSMutableDictionary *tagDict;
@property (nonatomic, strong) NSMutableDictionary *tagPointDict;


#pragma mark 设置类方法
/** --------------------------------------设置类--------------------------------------------------*/

/*!
 @method
 @abstract 设置画板显示大小
 @param frame fame
 */
- (void)setSceneSize:(CGRect)frame;

/*!
 @method
 @abstract 设置画板显示大小
 @param size size
 */
- (void)setupSceneSize: (CGSize)size;

/*!
 @method
 @abstract 设置设备类型
 @param deviceType 设备类型
 */
- (void)setDeviceType:(DeviceType)deviceType;

/*!
 @method
 @abstract 设置画板方向，1：横屏 0：竖屏，默认为竖屏
 @param isHorizontal 是否是横屏
 */
- (void)setIsHorizontal:(int)isHorizontal;

/*!
 @method
 @abstract 设置输入模式 0：手模式 1：笔模式
 @param Type 类型
 */
- (void)SetDrawType:(DrawType)Type;

/*!
 @method
 @abstract 设置图片编辑模式 YES:编辑模式 NO:非编辑模式
 @param enblePhotoEdit 布尔值
 */
- (void)setPhotoEdit:(BOOL)enblePhotoEdit;

/*!
 @method
 @abstract 管理页码信息
 @param page 当前页码
 */
- (void)setManagePageWithPage:(int)page;
/*!
 @methodzi
 @abstract 设置自动调整
 @param open 是否开启，默认开启。
 */
- (void)setAutomaticallyAdjusts:(BOOL)open;
/** ************************画板UI设置*************************/

/*!
 @method
 @abstract 根据路径设置画板背景图片（平铺)
 @param path 图片路径
 */
- (void)setBgPhoto:(NSString *)path;

/*!
 @method
 @abstract 根据int颜色设置画板背景颜色
 @param intColor 色值
 */
- (void)setBgIntColor:(int)intColor;

/*!
 @method
 @abstract 根据颜色设置画板背景颜色
 @param color 颜色
 */
- (void)setBgColor:(UIColor *)color;

/*!
 @method
 @abstract  设置 画笔图标
 @param image 图片
 */
- (void)setPenIcon:(UIImage *)image;

/*!
 @method
 @abstract 设置 不可书写图标 (仅用于笔模式，笔模式下手写提示)
 @param image 图片
 */
- (void)setPenModleBanIcon:(UIImage *)image;

/*!
 @method
 @abstract 设置图片编辑框的颜色
 @param color 默认为透明
 */
- (void)setPhotoEditColor:(UIColor *)color;

/*!
 @method
 @abstract 设置获取截图开关
 @param openGetImage 是否获取截图
 @param realTime 是否实时获取截图，否:则抬笔时获取
 */
- (void)setOpenGetWhiteBoardImage:(BOOL)openGetImage andOpenRealTime:(BOOL)realTime;

/*!
 @method
 @abstract 根据图片裁剪图片,主要用于实时笔记裁剪
 @param type 数据类型  默认0：原始点 1：转换点 2：场景点
 @param startpoint 裁剪起始点
 @param width 裁剪长度
 @param height 裁剪高度
 */
- (void)setWhiteBoardScreenshotWithType:(int)type andStartPoint:(CGPoint)startpoint andWidth:(int)width andHeight:(int)height;

/*!
 @method
 @abstract  设置截图误差范围
 例：入参：-1，-1，2，2 表示起始点像左上角偏移1，1 的位置，截图宽、高分别增加 2
 @param toX 起始点X偏移量
 @param toY 起始点Y偏移量
 @param toW 宽度偏移量
 @param toH 高度偏移量
 */
- (void)setMeasurementOfWhiteBoardScreenshotWithToX:(int)toX ToY:(int)toY ToW:(int)toW ToH:(int)toH;
#pragma mark 获取类方法
/** --------------------------------------获取类--------------------------------------------------*/

/*!
 @method
 @abstract 获取画板设备类型
 @result 返回结果
 */
- (DeviceType)getDeviceType;

/*!
 @method
 @abstract 获取画板方向
 @result 返回结果
 */
- (int)getIsHorizontal;

/*!
 @method
 @abstract 是否是笔记第一页
 @result 返回结果
 */
- (BOOL)GetIsFirstPage;

/*!
 @method
 @abstract 是否是笔记最后一页
 @result 返回结果
 */
- (BOOL)GetIsLastPage;

/*!
 @method
 @abstract 获取当前页的页码
 @result 返回结果
 */
- (int)getCurrentPage;

/*!
 @method
 @abstract 获取笔记总页数
 @result 返回结果
 */
- (int)getTotalPage;

/*!
 @method
 @abstract 删除某一页
 @param page 要删除的页
 @param success 删除成功回调
 @param failure 删除失败回调
 */
- (void)deletePage: (int)page Success:(void (^)(id responseObject))success Failure:(void (^)(NSError *error))failure;

/*!
 @method
 @abstract 获取当前页面的Block
 @result 返回结果
 */
- (NSString *)getCurrentBlock;

/*!
 @method
 @abstract 获取上个页面的Block
 @result 返回结果
 */
- (nullable NSString *)getPreviousBlock;

/*!
 @method
 @abstract 获取下个页面的Block
 @result 返回结果
 */
- (nullable NSString *)getNextBlock;

/*!
 @method
 @abstract 获取当前是否是图片编辑状态
 @result 返回结果
 */
- (BOOL)getIsPhotoEdit;

/*!
 @method
 @abstract 获取当前页是否有图片
 @result 返回结果
 */
- (BOOL)GetIsPhoto;

/*!
 @method
 @abstract 获取输入模式（手模式或笔模式）
 @result 返回结果
 */
- (DrawType)GetDrawType;

/*!
 @method
 @abstract 获取并保存画布截图
 @result 返回结果
 */
- (UIImage *)saveSnapshot;

/*!
 @method
 @abstract 获取是否是输入状态
 @result 返回结果
 */
- (BOOL)GetIsDrawing;

/*!
 @method
 @abstract 获取当前页笔记的最后更新时间
 @result 返回结果
 */
-(long)GetEndTime;

/*!
 @method
 @abstract 根据图片裁剪图片,主要用于离线笔记裁剪
 @param baseImage 原图
 @param startpoint 裁剪起始点（相对于图片）
 @param width 裁剪长度
 @param height 裁剪高度
 @result 返回结果
 */
- (UIImage *)getScreenshotImageWithBaseImage:(UIImage *)baseImage andStartPoint:(CGPoint)startpoint andWidth:(int)width andHeight:(int)height;

/*!
 @method
 @abstract 获取当前画板页面截图
 @result 返回结果
 */
- (UIImage *)getWhiteBoardImage;

/*!
 @method
 @abstract 获取当前画板的大小
 @result 返回结果
 */
- (CGSize)getWhiteBoardSceneSize;

#pragma mark 使用类方法
/** --------------------------------------使用类--------------------------------------------------*/

/*!
 @method
 @abstract 根据原始点画线方法
 @param penPoint 原始点
 */
- (void)drawLine:(RobotPenPoint *)penPoint;

/*!
 @method
 @abstract 根据优化点画线方法
 @param penpoint 优化点
 */
- (void)drawLineWithUtilPoint:(RobotPenUtilPoint *)penpoint;

/*!
 @method
 @abstract 根据轨迹画线
 @param trails 轨迹
 */
-(void)drawWithTrails:(NSArray <RobotTrails *> *)trails;
/*!
 @method
 @abstract 刷新画板
 */
- (void)RefreshAll;

/*!
 @method
 @abstract 翻页-->下一页
 */
- (void)nextPage;

/*!
 @method
 @abstract  翻页-->上一页
 */
- (void)frontPage;

/*!
 @method
 @abstract 在当前页插入下一页（新建页）
 */
- (void)NewNextPage;

/*!
 @method
 @abstract 根据页码跳转到指定页面
 @param page 页码（显示的页码）
 */
- (void)turnToPageWithPage:(int)page;

/*!
 @method
 @abstract 根据路径插入图片

 @param path 路径
 */
- (void)insterPhotoWithPath:(NSString *)path;
/*!
 @method
 @abstract 根据路径数组插入图片
 @discussion 自动创建页码，获取失败的图片会自动过滤
 @param pathArray 路径数组
 */
- (void)insterPhotoWithPathArray:(NSArray *)pathArray;

/*!
 @method
 @abstract 根据链接数组（URL）插入多页图片
 @discussion 自动创建页码，获取失败的图片会自动过滤
 @param  urlsArray 链接数组（URLL）
 */
- (void)insterPhotoWithUrls:(NSArray *)urlsArray;

/*!
 @method
 @abstract 根据链接数组（URL）设置多页图片 PS:尽量使用insterPhotoWithUrls函数
 @discussion 自动创建页码，获取失败的图片会自动过滤
 @param urlsArray 链接数组（URL）
 */
- (void)insterLivePhotoWithUrls:(NSArray *)urlsArray;

/*!
 @method
 @abstract 设置图片的显示默认模式
 @param type 类型
 */
- (void)setDefaultPhotoScaleType:(ScaleType)type;

/*!
 @method
 @abstract 设置图片的显示模式
 @param type 类型
 */
- (void)setPhotoScaleType:(ScaleType)type;

/*!
 @method
 @abstract 顺时针旋转图片,每次旋转90°
 */
- (void)currPhotoRotate90;

/*!
 @method
 @abstract 清空画板内容
 */
- (void)cleanScreen;

/*!
 @method
 @abstract 清除画板图片
 */
- (void)cleanPhoto;

/*!
 @method
 @abstract  清除画板笔记内容
 */
- (void)cleanTrail;

/*!
 @method
 @abstract 删除当前页
 */
- (void)delCurrPage;

/*!
 @method
 @abstract 根据截图名称保存笔记截图(每个笔记只有一张)
 路径为NSString *path = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES) firstObject] stringByAppendingString:[NSString stringWithFormat:@"/Robot/NoteSnaps"]] ;
 @param Key 截图名称.
 */
- (void)saveNoteSnapshotWith:(NSString *)Key;

/*!
 @method
 @abstract 根据截图Key和blockKey保存笔记截图（每个笔记的每页最多一张), 路径为NSString *path = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES) firstObject] stringByAppendingString:[NSString stringWithFormat:@"/Robot/NoteShareSnaps/%@",Key"]] ;
 path/blockKey
 @param Key 截图名称
 */
- (void)saveNoteShareSnapshotWith:(NSString *)Key andBlockKey:(NSString *)blockKey;

/*!
 @method
 @abstract 根据手势画线
 @param pan pan
 */
- (void)drawByHand:(UIPanGestureRecognizer *)pan;

/*!
 @method
 @abstract 根据手势移动图片
 @param pinch pinch
 */
- (void)handlePinches:(UIPinchGestureRecognizer *)pinch;

/*!
 @method
 @abstract 刷新当前页笔记数据
 */
- (void)RefreshNote;


#pragma mark 其他类方法
/** --------------------------------------其他类--------------------------------------------------*/
/*!
 @method
 @abstract 初始化页码管理信息（T9A）
 */
-(void)initPageManageInfo;

/*!
 @method
 @abstract 设置设备点击事件
 @param Type 设备点击事件
 */
- (void)getDeviceEvent:(DeviceEventType)Type;


/*!
 @method
 @abstract 保存图片到数据库
 @param photo 图片模型
 */
- (void)SaveImageNoteSql:(RobotPhotoImage *)photo;

/*!
 @method
 @abstract 保存笔记数据到数据库
 @param tag 标签
 @param isFull 布尔值
 */
- (void)saveSQLWithTag:(NSString *)tag ForFull:(BOOL)isFull;

/*!
 @method
 @abstract 设置播放笔记的笔迹数据
 @param model 笔迹
 */
-(void)SetLiveTrailsWith:(RobotTrails *)model;

/*!
 @method
 @abstract 设置直播笔记的图片数据
 @param model 笔迹
 */
-(void)SetLiveImageWith:(RobotTrails *)model;

/*!
 @method
 @abstract 设置白板屏幕点的偏移
 @param offset 偏移量
 */
-(void)setPointOffSet:(CGPoint)offset;


/**
 设置笔记宽度变化幅度

 @param max 最大幅度
 @param min 最小幅度
 */
-(void)setNoteWidthRangeWithMaxVaule:(CGFloat) max MinValue:(CGFloat)min;

@end

