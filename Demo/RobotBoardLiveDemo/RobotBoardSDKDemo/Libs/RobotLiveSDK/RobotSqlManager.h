//
//  RobotSqlManager.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//


/*!
 @enum
 @abstract 笔迹消息类型
 */
typedef enum {
    /**轨迹数据**/
    TRACK_DATA,
    /**图像数据**/
    IMG_DATA,
    /**翻页**/
    PAGE_TURN,
    /**背景**/
    BACKGROUND_IMG,
    /**清屏**/
    CLS = 10,
    /**清除图片**/
    ALL_IMG_DEL,
    /**清除图形**/
    SHAPE_DEL,
    /**清除笔迹**/
    TRACK_DEL,
    /**删除图片**/
    IMG_DEL = 21,
}TrailType;

#ifdef DEBUG

#define RobotSqlLog(fmt, ...) NSLog((@"RobotSql Log :   %s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);

#else

#define RobotSqlLog(...)

#endif


#import <Foundation/Foundation.h>

@class RobotVideo;
@class RobotNote;
@class RobotTrails;
@class RobotTrailBlock;


@interface RobotSqlManager : NSObject


/*!
 @method
 @abstract 检查数据库
 */
+ (void)checkRobotSqlManager;


#pragma mark  -----------------------------------------------------笔记相关操作-----------------------------------------------------
#pragma mark 笔记创建
/*!
 @method 创建一本完整的笔记
 @abstract 创建一本笔记，默认带有一个分页。
 */
+ (void)BuildNote:(RobotNote *)NoteObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**!
 @method 创建笔记头
 @abstract 创建一本笔记头，不含有分页，需手动添加分页（非必要情况下不建议使用本方法）
 @param NoteObj NoteObj
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)BuildNoteHeader:(RobotNote *)NoteObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

#pragma mark 笔记删除
/*!
 @method 删除指定笔记
 @abstract 根据笔记的唯一标识（NoteKey），删除该笔记
 @param NoteKey NoteKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteNoteWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 删除所有笔记
 @abstract 删除笔记列表全部笔记
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteAllNoteSuccess:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 删除指定页笔记 （暂时无效）
 @abstract 根据传入的页码值，删除笔记列表中该页的全部笔记
 @param Page 页码
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteNoteWithPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

#pragma mark 笔记修改

/*!
 @method 修改笔记名称
 @abstract 根据笔记的唯一标识（NoteKey）和新的笔记名称，修改笔记名称
 @param NoteKey NoteKey
 @param TagertTitle 新笔记名称
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)ChangeNameWithNoteKey:(NSString *)NoteKey TagertTitle:(NSString *)TagertTitle Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


#pragma mark 笔记查询
/*!
 @method 查询笔记是否存在
 @abstract 根据笔记唯一标识（NoteKey）查询笔记是否存在。
 @param NoteKey NoteKey
 @result 返回结果
 */
+ (BOOL)checkNoteWithNoteKey:(NSString *)NoteKey;

/*!
 @method 获取笔记头信息
 @abstract 根据笔记唯一标识（NoteKey）获取笔记头信息
 @param NoteKey NoteKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetNoteListInfoWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


#pragma mark 笔记列表相关
/*!
 @method 获取指定页的笔记列表
 @abstract 根据传入的页码值获取该页笔记列表，返回该页的笔记列表数据
 @param Page page >=0
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetAllNoteListWithPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 获取指定页之前的所有笔记列表
 @abstract 根据传入的页码值获取Page页之前所有笔记列表，返回0 - Page页的所有笔记列表数据
 @param Page page >=0
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetAllNoteListBeforePage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


#pragma mark 临时笔记相关

/*!
 @method 保存临时笔记
 @abstract 保存临时笔记
 @param NoteKey NoteKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)SaveTempNote:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 设置临时笔记的设备类型
 @abstract 设置临时笔记的设备类型
 @param DeviceType 设备类型
 */
+ (void)ChangeTempNoteDeviceType:(int)DeviceType;

/*!
 @method 设置临时笔记的画板方向
 @abstract 设置临时笔记的画板方向
 @param isHorizontal YES:横屏 NO:竖屏
 */
+ (void)ChangeTempNoteIsHorizontal:(BOOL)isHorizontal;


#pragma mark  -----------------------------------------------------页码相关操作-----------------------------------------------------

#pragma mark 页码新建
/*!
 @method 查询新建下一页页码信息
 @abstract 按笔记页码当前顺序向下新建一页，并返回新页码唯一标识BlockKey
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @result 返回结果
 */
+ (NSString *)getNextWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;

/*!
 @method 查询新建上一页页码信息
 @abstract 按笔记页码当前顺序向上新建一页，并返回新页码唯一标识BlockKey
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @result 返回结果
 */
+ (NSString *)getFrontWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;

/*!
 @method 插页
 @abstract 在当前页和后一页之间插入新页并返回Blockkey
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @result 返回结果
 */
+ (NSString *)GetNewNextWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;

/*!
 @method 新建笔记页码
 @abstract 按传入的页码标识顺序新建页码
 @param blockKey 目标页页码标识
 @param NextBlockKey 下一页标识
 @param NoteKey 笔记标识
 */
+ (void)BuildBlockWithBlockKey:(NSString *)blockKey NextBlockKey:(NSString *)NextBlockKey NoteKey:(NSString *)NoteKey;

#pragma mark 页码删除

/*!
 @method 删除当前页码
 @abstract 根据页码唯一标识（BlockKey）删除指定页
 @param ActivityBlockKey 当前页的blockKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

#pragma mark 页码修改
/*!
 @method 设置当前页的下一页页码
 @abstract 设置当前页的下一页的Block, 修改block指向用于更换页码顺序
 @param nextBlockKey 目标页的BlockKey
 @param blockKey 当前页的BlockKey
 @param Notekey Notekey
 */
+ (void)SetNextBlockKey:(NSString *)nextBlockKey BlockKey:(NSString *)blockKey :(NSString *)Notekey;

/*!
 @method 设置当前页的上一页页码
 @abstract 设置当前页的上一页的Block, 修改block指向用于更换页码顺序
 @param blockKey 目标也的BlockKey
 @param nextBlockKey 当前页的BlockKey
 @param Notekey Notekey
 */
+ (void)SetBlockKey:(NSString *)blockKey NextBlockKey:(NSString *)nextBlockKey :(NSString *)Notekey;

#pragma mark 页码查询
/*!
 @method 获取当前笔记的页码信息
 @abstract 根据笔记的唯一标识（NoteKey），获取当前笔记页码信息,总页码 当前页 活动页
 @param NoteKey NoteKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetPageInfosWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 获取上一页的页码唯一标识
 @abstract 根据笔记的唯一标识（NoteKey），获取上一页的BlockKey
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @result 返回结果
 */
+ (NSString *)GetFront:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;

/*!12
 @method 获取下一页的页码唯一标识
 @abstract  根据笔记的唯一标识（NoteKey），获取下一页的BlockKey
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @result 返回结果
 */
+ (NSString *)getNext:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;



/*!
 @method  获取当前页是否存在
 @abstract 根据笔记的唯一标识（NoteKey），获取当前页是否存在
 @param NoteKey Notekey
 @param ActivityBlockKey 当前页的BlockKey
 @result 返回结果
 */
+ (BOOL)IsExist:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;



/*!
 @method 获取当前笔记的所有Block
 @abstract 根据笔记的唯一标识（NoteKey），获取当前笔记的所有Block
 @param NoteKey NoteKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetAllBlockWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


#pragma mark  -----------------------------------------------------笔迹相关操作-----------------------------------------------------

#pragma mark 笔记保存
/*!
 @method 保存笔迹数据
 @abstract 根据笔迹模型，保存笔迹数据
 @param TrailsObj 笔迹数据
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)SaveTrails:(RobotTrails *)TrailsObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;



#pragma mark 笔迹删除

/*!
 @method 删除指定笔迹数据
 @abstract 根据笔迹数据模型，删除指定笔迹数据
 @param TrailsObj 笔迹数据模型
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteTrails:(RobotTrails *)TrailsObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 删除指定页码中的所有笔迹数据
 @abstract 页码唯一标识（BlockKey），删除指定页笔迹数据
 @param ActivityBlockKey 指定页的blockKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DelNoteTrailsWithBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/*!
 @method 删除指定页的图片数据
 @abstract  页码唯一标识（BlockKey），删除指定页图片数据
 @param ActivityBlockKey 指定页的blockKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DelNoteImgsWithBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/*!
 @method 删除指定页的所有数据（笔迹和图片数据）
 @abstract 页码唯一标识（BlockKey），删除指定页所有的数据
 @param ActivityBlockKey 指定页的blockKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DelNoteWithBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

#pragma mark 笔迹修改
/*!
 @method 向前合并笔迹
 @abstract 根据目标页码唯一标识（BlockKey）、笔迹时间节点和当前页码唯一标识，合并笔迹到前一个页上。
 @param Blockkey 目标Blockkey（上一页）
 @param endTime 笔迹时间
 @param ActivityBlockKey 当前页Blockkey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)MergeTrailsWithBlockKey:(NSString *)Blockkey WithEndTime:(long long)endTime WithActivityBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 向后分离笔迹
 @abstract 根据目标页码唯一标识（BlockKey）、笔迹时间节点和当前页码唯一标识，分离笔迹到下一个页上。
 @param Blockkey 目标Blockkey（下一页）
 @param endTime 笔迹时间
 @param ActivityBlockKey 当前页Blockkey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)SeparateTrailsWithBlockKey:(NSString *)Blockkey WithEndTime:(long long)endTime WithActivityBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 更新分页的更新时间
 @abstract 根据笔记的唯一标识（NoteKey）和分页唯一标识（BlockKey）更新笔记分页的UpdateTime
 @param NoteKey NoteKey
 @param BlockKey BlockKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)UpdateNoteWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)BlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


#pragma mark 笔迹查询

/*!
 @method 获取当前页的所有笔迹
 @abstract 根据当前页码唯一标识（BlockKey），获取当前页的笔迹数据
 @param ActivityBlockKey 当前页的blockKey
 @param SuccessTrails 笔迹数据
 @param SuccessImages 图片数据
 @param Failure 失败结果返回
 */
+ (void)GetNoteTrailsWithBlockKey:(NSString *)ActivityBlockKey SuccessTrails:(void (^)(id responseObject))SuccessTrails SuccessImages:(void (^)(id responseObject))SuccessImages Failure:(void (^)(NSError *error))Failure;


/*!
 @method 获取指定页的所有笔迹
 @abstract 根据笔记的唯一标识（NoteKey）和指定页页码唯一标识（BlockKey），获取指定页的笔迹数据
 @param NoteKey NoteKey
 @param BlockKey BlockKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetAllTrailsWithNoteKey:(NSString *)NoteKey WithBlockKey:(NSString *)BlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 获取指定页的所有图片（目前只有一张）
 @abstract  根据笔记的唯一标识（NoteKey）和指定页页码唯一标识（BlockKey），获取指定页的所有图片
 @param NoteKey NoteKey
 @param BlockKey BlockKey
 @param Success 成功结果返回
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        @param Failure 失败结果返回
 */
+ (void)GetAllImageOfTrailsWithNoteKey:(NSString *)NoteKey WithBlockKey:(NSString *)BlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 获取指定页的最后五张图片
 @abstract 根据当前页页码唯一标识（BlockKey）查询画板中的最后五张图片
 @param ActivityBlockKey 当前页的blockKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetFiveImageWith:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;



#pragma mark  -----------------------------------------------------白板截图相关操作-----------------------------------------------------
#pragma mark 白板截图相关

/*!
 @method  获取缩略图保存的完整路径
 @abstract 根据笔记的唯一标识（NoteKey），获取笔记缩略图路径（用于笔记缩略图）
 @result 返回结果
 */
+ (NSString *)GetNoteImagePathWithKey:(NSString *)Key;

/*!
 @method 获取笔记指定页的截图保存的完整路径
 @abstract 根据笔记的唯一标识（NoteKey）和页码唯一标识（BlockKey），获取笔记指定页的截图
 @result 返回结果
 */
+ (NSString *)GetNoteShareImagePathWithKey:(NSString *)Key andBlockKey:(NSString *)blockkey;

/*!
 @method 获取新的截图保存完整路径
 @abstract 获取新的截图保存完整路径，后可将图片写入该路径
 */
+ (void)SaveImageKeySuccess:(void (^)(id responseObject))Success
                    Failure:(void (^)(NSError *error))Failure;
/*!
 @method 获取指定页保存截图列表的相对路径
 @abstract 根据指定页码信息，获取Page页的截图列表数据。
 @param Page 页码
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetImagesArrayWithPage:(int)Page Success:(void (^)(id responseObject))Success
                       Failure:(void (^)(NSError *error))Failure;

/*!
 @method 删除指定截图图片
 @abstract 根据传入的图片保存相对路径Key数组，删除图片
 @param KeyArray 图片相对路径数组（可参考GetImagesArrayWithPage返回值）
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteImageWithKeyArray:(NSArray *)KeyArray Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 获取截图图片总数
 @abstract 获取截图图片总数
 @result 返回结果
 */
+ (long)GetImageNumber;

/*!
 @method 获取截图存储完整路径
 @abstract 根据截图的相对路径获取截图图片存储完整路径
 @param Key 图片相对路径数组（可参考GetImagesArrayWithPage返回值）
 @result 返回结果
 */
+ (NSString *)GetImagePathWithKey:(NSString *)Key;
#pragma mark  -----------------------------------------------------录课相关操作-----------------------------------------------------
#pragma mark  录课创建
/*!
 @method 创建录课文件
 @abstract 根据视频唯一标识（NameKey）创建视频文件
 @param NameKey 视频NameKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)BuildVideoWithNameKey:(NSString *)NameKey Success:(void (^)(id responseObject))Success
                      Failure:(void (^)(NSError *error))Failure;

#pragma mark 录课删除
/*!
 @method 删除指定视频
 @abstract 根据视频唯一标识（NameKey），删除指定视频
 @param NameKey 视频NameKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteVideoWithNameKey:(NSString *)NameKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 删除视频列表所有视频
 @abstract 删除视频列表所有视频
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteAllVideoSuccess:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 删除视频列表中指定页的所有视频（暂时无效）
 @abstract 根绝页码值，删除视频列表中指定页的所有视频（
 @param Page 页码
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)DeleteAllVideoWithPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


#pragma mark  录课修改
/*!
 @method 更新视频信息
 @abstract 根据视频头模型（RobotVideo）更新视频信息
 @param Video 视频信息
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)PerfectVideoInfosWithVideo:(RobotVideo *)Video Success:(void (^)(id responseObject))Success
                           Failure:(void (^)(NSError *error))Failure;

/*!
 @method 更新视频名称
 @abstract 根据视频唯一标识（NameKey）和新视频名称更改视频名称
 @param NameKey 视频NameKey
 @param Alias 视频名称
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)ChangeVideoWithNameKey:(NSString *)NameKey Alias:(NSString *)Alias Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 更新视频标签状态
 @abstract 根据视频唯一标识（NameKey）和新视频标签，更新视频标签（可作为状态判断）
 @param NameKey 视频NameKey
 @param IsOnLine 视频状态
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)SetOnLineWithNameKey:(NSString *)NameKey IsOnLine:(int)IsOnLine Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/*!
 @method 更新视频MD5值
 @abstract 根据视频唯一标识（NameKey）和新视频MD5值，更新MD5信息
 @param NameKey 视频NameKey
 @param Md5Str MD5
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)SaveMd5StrWithNameKey:(NSString *)NameKey Md5Str:(NSString *)Md5Str Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

#pragma mark  录课查询

/*!
 @method 根据NameKey获取视频信息
 @abstract 根据视频唯一标识（NameKey），获取视频信息
 @param NameKey 视频NameKey
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetVideoInfoWithNameKey:(NSString *)NameKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 根据MD5获取视频信息
 @abstract 根据MD5值获取视频信息
 @param Md5Str MD5
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetNoteInfoWithMd5Str:(NSString *)Md5Str Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 根据NameKey获取视频路径
 @abstract 获取视频路径
 @param NameKey 视频NameKey
 @result 返回结果
 */
+ (NSString *)GetVideoPathWithNameKey:(NSString *)NameKey;
/*!
 @method  根据Md5获取视频路径
 @abstract 根据Md5获取视频路径
 @param Md5Str MD5
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetVideoPathWithMd5Str:(NSString *)Md5Str  Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;





#pragma mark 录课列表获取
/*!
 @method 获取指定页视频列表中的所有视频
 @abstract 根据传入的页码值获取Page页的所有视频列表，返回当前视频列表age页的所有数据
 @param Page page >= 0
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetVideoListWithPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 获取视频列表中指定页之前的所有视频
 @abstract 根据传入的页码值获取Page页之前所有视频列表，返回0 - Page页的所有笔记列表数据
 @param Page page >= 0
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)GetAllVideoListBeforePage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/*!
 @method 获取视频列表中的视频总数
 @abstract 获取视频列表中的视频总数
 @result 返回结果
 */
+ (long)GetVideoTotalNum;





#pragma mark  -----------------------------------------------------页码检测专用-----------------------------------------------------


/*!
 @method 获取或新建页码笔记本中的指定页的唯一标识
 @abstract 根据笔记的唯一标识（NoteKey）和页码（Page）获取该分页的Blockkey，为空则新建一个分页,PS:页码检测专用
 @param Notekey Notekey
 @param Page 页码
 @result 返回结果
 */
+ (NSString *)getOrBuildBlockKeyWithNoteKey:(NSString *)Notekey PageNumber:(int)Page;

/*!
 @method 获取页码笔记本中的指定页的唯一标识
 @abstract  根据笔记的唯一标识（NoteKey）和页码（Page）获取该分页的Blockkey，不会新建,PS:页码检测专用
 @param Notekey Notekey
 @result 返回结果
 */
+ (NSString *)getBlockKeyWithNoteKey:(NSString *)Notekey PageNumber:(int)Page;

/*!
 @method 获取页码笔记的页码编号
 @abstract 根据笔记的唯一标识（NoteKey）和页码唯一标识（BlockKey）获取该页的页码编号（PageNumber）,PS:页码检测专用
 @param NoteKey NoteKey
 @param BlockKey BlockKey
 @result 返回结果
 */
+ (int)getPageNumberWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)BlockKey;

/*!
 @method 页码识别设备专用离线笔记保存方法
 @abstract 根据笔记头信息(RobotNote)和页码信息（Page）保存页码识别离线笔记,PS:页码识别专用
 @param NoteObj 笔记头信息
 @param Page 页码
 @param Success 成功结果返回
 @param Failure 失败结果返回
 */
+ (void)SaveTANote:(RobotNote *)NoteObj andPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


#pragma mark  -----------------------------------------------------其他-----------------------------------------------------

/*!
 @method 获取当前时间戳
 @abstract 根据系统时间获取当前时间戳
 @result 返回结果
 */
+ (NSTimeInterval)GetTimeInterval;

/*!
 @method 获取一个新的NoteKey
 @abstract 根据时间戳创建一个新的NoteKey
 @result 返回结果
 */
+ (NSString *)GetNewKey;

/*!
 @method 设置列表默认拉取拉取条数
 @abstract 设置列表默认拉取拉取条数
 @param page 页码
 */
+ (void)SetNumberOfPageWith:(int)page;

@end

