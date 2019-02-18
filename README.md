SDK服务分为四种服务：笔服务（RobotPenSDK）、白板服务（RobotBoardSDK）、录课服务（RobotRecordSDK）和直播服务（RobotLiveSDK）。   

笔服务为基础服务，白板服务、录课服务、直播服务为插件形式存在。其中前者包含数据库服务，后三者服务存在向前依赖关系。
举例：使用录课服务需要导入RobotPenSDK、RobotBoardSDK和RobotRecordSDK。

    笔服务、白板服务、录课服务支持Cocoapods导入，直播服务暂不支持。
    笔服务：pod 'RobotPenSDK/RobotPenSDK'
    白板服务：pod 'RobotPenSDK/RobotBoardSDK'
    录课服务：pod 'RobotPenSDK/RobotRecordSDK' 或 pod 'RobotPenSDK'
    Tips:使用Cocoapods导入，只需要拉取相应的服务即可自动配置所包含的其他服务。

SDK文档分为四个文档：笔文档（RobotPenSDK参考手册）、白板文档（RobotBoardSDK参考手册）、录课文档（RobotRecordSDK参考手册）和数据库文档（RobotSqlManager参考手册）。
与SDK服务统一，故使用录课服务需参考全部文档，使用白板服务需参考白板文档和笔文档，如有数据库需要参考数据库文档。
