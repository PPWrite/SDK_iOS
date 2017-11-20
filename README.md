SDK服务分为三种服务：笔服务（RobotPenManager）、白板服务（RobotBoard）和录课服务（RobotBoard_Micro）。
录课服务包括其他两种服务，白板服务包含笔服务，所以使用录课服务不需要再倒入其他服务，以此类推。
另数据库包含在每个服务中，不需要单独倒入。

SDK文档分为四个文档：笔文档（RobotPenManager参考手册）、白板文档（RobotBoard参考手册）、录课文档（RobotBoard_Micro参考手册）和数据库文档（RobotSqlManager参考手册）。
与SDK服务统一，故使用录课服务需参考全部文档，使用白板服务需参考白板文档和笔文档，如有数据库需要参考数据库文档。
