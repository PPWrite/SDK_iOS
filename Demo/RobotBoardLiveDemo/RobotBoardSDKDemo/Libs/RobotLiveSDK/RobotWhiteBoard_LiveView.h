//
//  RobotPenLiveToolHeader.h
//  PPWrite
//
//  Created by JMS on 2017/11/13.
//  Copyright © 2017年 Robot. All rights reserved.
//

#import "RobotWhiteBoardView.h"
#import "RobotPenLiveHeader.h"
#import "RobotLiveStudioModel.h"
@protocol WhiteBoardLiveViewDelegate <NSObject>

@required

/*!
 @method
 @abstract 设置书写权限
 @result 返回结果
 */
- (BOOL)GetIsLiveWrite;
/*!
 @method
 @abstract 设置是否是房主
 @result 返回结果
 */
- (BOOL)GetIsOwner;

/*!
 @method
 @abstract 设置直播间LiveID
 @result 返回结果
 */
- (NSString *)GetLiveId;

@end  

@interface RobotWhiteBoard_LiveView : RobotWhiteBoardView

@property (nonatomic, weak) id<WhiteBoardLiveViewDelegate> WBLiveDelegate;


/*!
 @method  处理直播白板数据
 @abstract 处理直播白板数据
 @param dataType 数据类型
 @param data 数据
 */
- (void)manageLiveDataMessageType:(LiveDataMessageType)dataType data:(RobotTrails *)data;

/*!
 @method  创建直播笔记
 @abstract 创建直播笔记
 @param model 直播间信息模型
 @param notekey 笔记
 @param isNote 是否创建新笔记，否则创建笔记头
 */
-(void)BuildNoteWithLiveModel:(RobotLiveStudioModel *)model NoteKey:(NSString *)notekey IsNote:(BOOL)isNote;


@end
