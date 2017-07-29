//
//  RobotSqlManager.h
//  PPNote
//
//  Created by JMS on 2017/4/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

//笔迹消息类型
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


/**
 检查数据库
 */
+ (void)checkRobotSqlManager;



/**
 创建笔记
 
 @param NoteObj <#NoteObj description#>
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)BulidNote:(RobotNote *)NoteObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 创建直播笔记
 
 @param NoteObj <#NoteObj description#>
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)BulidLiveNote:(RobotNote *)NoteObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**
 保存笔记
 
 @param NoteObj <#NoteObj description#>
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)SaveNote:(RobotNote *)NoteObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;
/**
 保存页码识别离线笔记
 PS:页码识别准用
 @param NoteObj <#NoteObj description#>
 @param Page <#Page description#>
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)SaveTANote:(RobotNote *)NoteObj andPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;
/**
 更新笔记的UpdateTime
 
 @param NoteKey NoteKey
 @param BlockKey BlockKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)UpdateNoteWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)BlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取单页笔记列表，返回page页的数据
 
 @param Page page >=0
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetAllNoteListWithPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**
 获取page之前所有笔记列表，返回0 - page页的数据
 
 @param Page page >=0
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetAllNoteListBeforePage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取列表笔记单个信息
 
 @param NoteKey NoteKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetNoteListInfoWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取当前笔记页码信息
 总页码 当前页 活动页
 
 @param NoteKey NoteKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetPageInfosWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取下一页的BlockKey（没有则新建）
 
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @return <#return value description#>
 */
+ (NSString *)getNextWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;


/**
 获取上一页的BlockKey（没有则新建）
 
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @return <#return value description#>
 */
+ (NSString *)getFrontWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;


/**
 在当前页和后一页之间插入新页并返回Blockkey
 
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @return <#return value description#>
 */
+ (NSString *)GetNewNextWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;


/**
 获取上一页的BlockKey
 
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @return <#return value description#>
 */
+ (NSString *)GetFront:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;

/**
 获取下一页的BlockKey
 
 @param NoteKey NoteKey
 @param ActivityBlockKey 当前页的BlockKey
 @return <#return value description#>
 */
+ (NSString *)getNext:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;


/**
 设置当前页的下一页的Block
 修改block指向用于更换页码顺序
 @param nextBlockKey 下一页的BlockKey
 @param blockKey 当前页的BlockKey
 @param Notekey Notekey
 */
+ (void)SetNextBlockKey:(NSString *)nextBlockKey BlockKey:(NSString *)blockKey :(NSString *)Notekey;

/**
 修改block指向用于更换页码顺序
 
 @param blockKey 当前页的BlockKey
 @param nextBlockKey 下一页的BlockKey
 @param Notekey Notekey
 */
+ (void)SetBlockKey:(NSString *)blockKey NextBlockKey:(NSString *)nextBlockKey :(NSString *)Notekey;

/**
 获取前后页是否存在
 
 @param NoteKey Notekey
 @param ActivityBlockKey 当前页的BlockKey
 @return <#return value description#>
 */
+ (BOOL)IsExist:(NSString *)NoteKey BlockKey:(NSString *)ActivityBlockKey;


/**
 检查笔记是否存在
 
 @param NoteKey NoteKey
 @return <#return value description#>
 */
+ (BOOL)checkNoteWithNoteKey:(NSString *)NoteKey;


/**
 获取笔记的所有Block
 
 @param NoteKey NoteKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetAllBlockWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**
 创建新的blockKey（页）
 
 @param blockKey blockKey
 @param NextBlockKey 下一页的blockKey
 @param NoteKey NoteKey
 */
+ (void)BulidBlockWithBlockKey:(NSString *)blockKey NextBlockKey:(NSString *)NextBlockKey NoteKey:(NSString *)NoteKey;


/**
 保存笔迹数据
 
 @param TrailsObj 笔迹数据
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)SaveTrails:(RobotTrails *)TrailsObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**
 删除笔迹数据
 
 @param TrailsObj 笔迹数据
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DeleteTrails:(RobotTrails *)TrailsObj Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取笔记数据
 
 @param ActivityBlockKey 当前页的blockKey
 @param SuccessTrails 笔迹数据
 @param SuccessImages 图片数据
 @param Failure <#Failure description#>
 */
+ (void)GetNoteTrailsWithBlockKey:(NSString *)ActivityBlockKey SuccessTrails:(void (^)(id responseObject))SuccessTrails SuccessImages:(void (^)(id responseObject))SuccessImages Failure:(void (^)(NSError *error))Failure;


/**
 查询画板中的最后五张图片
 
 @param ActivityBlockKey 当前页的blockKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetFiveImageWith:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 删除图片
 
 @param ActivityBlockKey 当前页的blockKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DelNoteImgsWithBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**
 删除笔迹数据
 
 @param ActivityBlockKey 当前页的blockKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DelNoteTrailsWithBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 删除当前页所有的数据
 
 @param ActivityBlockKey 当前页的blockKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DelNoteWithBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;



/**
 删除当前页
 
 @param ActivityBlockKey 当前页的blockKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DeleteBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 修改临时笔记设备类型
 
 @param DeviceType 设备类型
 */
+ (void)ChangeTempNoteDeviceType:(int)DeviceType;

/**
 修改临时笔记画板方向
 
 @param mark yes:横屏 no:竖屏
 */
+ (void)ChangeTempNoteIsHorizontal:(BOOL)mark;


/**
 保存临时笔记
 
 @param NoteKey NoteKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)SaveTempNote:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**
 修改笔记名称
 
 @param NoteKey NoteKey
 @param TagertTitle 名称
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)ChangeNameWithNoteKey:(NSString *)NoteKey TagertTitle:(NSString *)TagertTitle Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 删除笔迹
 
 @param NoteKey NoteKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DeleteNoteWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 根据页码删除笔记（当前为全部删除）
 
 @param Page <#Page description#>
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DeleteNoteWithPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


////获取所有轨迹
//+ (void)GetAllTrailsWithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 根据BlockKey获取某一页的所有笔迹
 
 @param NoteKey NoteKey
 @param BlockKey BlockKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetAllTrailsWithNoteKey:(NSString *)NoteKey WithBlockKey:(NSString *)BlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 根据BlockKey获取某一页的所有图片
 
 @param NoteKey NoteKey
 @param BlockKey BlockKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetAllImageOfTrailsWithNoteKey:(NSString *)NoteKey WithBlockKey:(NSString *)BlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


////新建下一页
//+ (void)NextNewPage:(int)OldPage WithNoteKey:(NSString *)NoteKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 合并笔迹
 
 @param Blockkey 目标Blockkey
 @param endTime 笔迹时间
 @param ActivityBlockKey 当前页Blockkey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)MergeTrailsWithBlockKey:(NSString *)Blockkey WithEndTime:(long long)endTime WithActivityBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 分离笔迹
 
 @param Blockkey 目标Blockkey
 @param endTime 笔迹时间
 @param ActivityBlockKey 当前页Blockkey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)SeparateTrailsWithBlockKey:(NSString *)Blockkey WithEndTime:(long long)endTime WithActivityBlockKey:(NSString *)ActivityBlockKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取截图图片(笔记缩略图)路径（用于笔记缩略图）
 */
+ (NSString *)GetNoteImagePathWithKey:(NSString *)Key;
/**
 获取笔记分享截图图片(白板截图)路径（用于每页笔记截图）
 */
+ (NSString *)GetNoteShareImagePathWithKey:(NSString *)Key andBlockKey:(NSString *)blockkey;

/**
 保存截图信息
 */
+ (void)SaveImageKeySuccess:(void (^)(id responseObject))Success
                    Failure:(void (^)(NSError *error))Failure;
/**
 获取截图
 */
+ (void)GetImagesArrayWithPage:(int)Page Success:(void (^)(id responseObject))Success
                       Failure:(void (^)(NSError *error))Failure;
/**
 获取截图图片路径（用于主动截图，key为时间戳）
 */
+ (NSString *)GetImagePathWithKey:(NSString *)Key;

/**
 获取截图图片总数
 */
+ (long)GetImageNumber;

/**
 删除图片
 */
+ (void)DeleteImageWithKeyArray:(NSArray *)KeyArray Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;



/**
 创建视频文件

 @param NameKey 视频NameKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)BulidVideoWithNameKey:(NSString *)NameKey Success:(void (^)(id responseObject))Success
                      Failure:(void (^)(NSError *error))Failure;


/**
 更新视频信息

 @param Video 视频信息
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)PerfectVideoInfosWithVideo:(RobotVideo *)Video Success:(void (^)(id responseObject))Success
                           Failure:(void (^)(NSError *error))Failure;

/**
 更改视频名称

 @param NameKey 视频NameKey
 @param Alias 视频名称
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)ChangeVideoWithNameKey:(NSString *)NameKey Alias:(NSString *)Alias Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 视频标签（可作为状态判断）

 @param NameKey 视频NameKey
 @param IsOnLine 视频状态
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)SetOnLineWithNameKey:(NSString *)NameKey IsOnLine:(int)IsOnLine Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 绑定MD5信息

 @param NameKey 视频NameKey
 @param Md5Str MD5
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)SaveMd5StrWithNameKey:(NSString *)NameKey Md5Str:(NSString *)Md5Str Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 根据Md5获取视频信息

 @param Md5Str Md5Str
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetNoteInfoWithMd5Str:(NSString *)Md5Str Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 根据Md5获取视频路径

 @param Md5Str Md5Str
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetVideoPathWithMd5Str:(NSString *)Md5Str  Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取视频信息

 @param NameKey 视频NameKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetVideoInfoWithNameKey:(NSString *)NameKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取单页视频列表，返回当前page页的所有数据

 @param Page page >= 0
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetVideoListWithPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**
 获取page之前的所有视频列表，返回0-page页的所有数据
 
 @param Page page >= 0
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)GetAllVideoListBeforePage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;

/**
  获取视频总个数

 @return <#return value description#>
 */
+ (long)GetVideoTotalNum;


/**
 删除视频

 @param NameKey 视频NameKey
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DeleteVideoWithNameKey:(NSString *)NameKey Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 根据页码删除所有视频 （目前删除所有)

 @param Page <#Page description#>
 @param Success <#Success description#>
 @param Failure <#Failure description#>
 */
+ (void)DeleteAllVideoWithPage:(int)Page Success:(void (^)(id responseObject))Success Failure:(void (^)(NSError *error))Failure;


/**
 获取视频路径

 @param NameKey 视频NameKey
 @return <#return value description#>
 */
+ (NSString *)GetVideoPathWithNameKey:(NSString *)NameKey;



/**
 获取当前时间戳
 
 @return <#return value description#>
 */
+ (NSTimeInterval)GetTimeInterval;

/**
 创建一个新的Key
 
 @return <#return value description#>
 */
+ (NSString *)GetNewKey;


/**
 更改默认拉取条数

 @param page <#page description#>
 */
+ (void)SetNumberOfPageWith:(int)page;




/**-----------------------------------页码检测专用---------------------------------**/


/**
 根据页码信息获取Blockkey，为空则新建
 PS:页码检测专用
 @param Notekey Notekey
 @param Page 页码
 @return <#return value description#>
 */
+ (NSString *)getOrBuildBlockKeyWithNoteKey:(NSString *)Notekey PageNumber:(int)Page;

/**
 根据页码信息获取Blockkey
 PS:页码检测专用
 @param Notekey Notekey
 @param Page 页码
 @return <#return value description#>
 */
+ (NSString *)getBlockKeyWithNoteKey:(NSString *)Notekey PageNumber:(int)Page;

/**
 根据BlockKey获取PageNumber
 PS:页码检测专用
 
 @param NoteKey <#NoteKey description#>
 @param BlockKey <#BlockKey description#>
 @return <#return value description#>
 */
+ (int)getPageNumberWithNoteKey:(NSString *)NoteKey BlockKey:(NSString *)BlockKey;




@end
