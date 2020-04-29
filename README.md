SDK服务分为四种服务：设备服务（RobotPenSDK）、白板服务（RobotBoardSDK）、录课服务（RobotRecordSDK）和直播服务（RobotLiveSDK）。   

设备服务为基础服务，白板服务、录课服务、直播服务创建在设备服务之上。其中前者包含数据库服务。
举例：使用录课服务需要导入RobotPenSDK、RobotBoardSDK和RobotRecordSDK。

SDK文档分为四个文档：笔文档（RobotPenSDK参考手册）、白板文档（RobotBoardSDK参考手册）、录课文档（RobotRecordSDK参考手册）和数据库文档（RobotSqlManager参考手册）。
与SDK服务统一，故使用录课服务需参考全部文档，使用白板服务需参考白板文档和笔文档，如有数据库需要参考数据库文档。

## 注意

**从 4.2.9 起设备服务和白板服务 SDK 为动态库，请按照动态库方式接入**

为了能让 SDK 可以跑在模拟器上，所有的动态库中都包含了 x86_64 和 i386 架构，所有在上架前需要移除掉 x86_64 和 i386 架构，不然无法提交 APP。

如果您的应用不需要运行在模拟器，可以在下载 SDK 后使用以下命令删除  x86_64 和 i386：

```
lipo -remove "i386" xxxx.framework/xxxx -o xxxx
mv xxxx xxxx.framework/xxxx

lipo -remove "x86_64" xxxx.framework/xxxx -o xxxx
mv xxxx xxxx.framework/xxxx
```

如果您的应用需要在模拟器运行，那么可以使用 Xcode 的 `Run Script` 来移除，步骤如下：

1. 开发 Xcode 工程配置，并选中对应的 Targets.
2. 打开 `build Phases` 点击 `+` 按钮，选择 `New Run Script Phases` 创建 `Run Script`
3. 新创建的 `Run Script` 在列表最下面，打开它，然后在脚本输入框中填入以下脚本：

```
APP_PATH="${TARGET_BUILD_DIR}/${WRAPPER_NAME}"

# This script loops through the frameworks embedded in the application and
# removes unused architectures.
find "$APP_PATH" -name '*.framework' -type d | while read -r FRAMEWORK
do
    FRAMEWORK_EXECUTABLE_NAME=$(defaults read "$FRAMEWORK/Info.plist" CFBundleExecutable)
    FRAMEWORK_EXECUTABLE_PATH="$FRAMEWORK/$FRAMEWORK_EXECUTABLE_NAME"
    echo "Executable is $FRAMEWORK_EXECUTABLE_PATH"

    EXTRACTED_ARCHS=()

    for ARCH in $ARCHS
    do
        echo "Extracting $ARCH from $FRAMEWORK_EXECUTABLE_NAME"
        lipo -extract "$ARCH" "$FRAMEWORK_EXECUTABLE_PATH" -o "$FRAMEWORK_EXECUTABLE_PATH-$ARCH"
        EXTRACTED_ARCHS+=("$FRAMEWORK_EXECUTABLE_PATH-$ARCH")
    done

    echo "Merging extracted architectures: ${ARCHS}"
    lipo -o "$FRAMEWORK_EXECUTABLE_PATH-merged" -create "${EXTRACTED_ARCHS[@]}"
    rm "${EXTRACTED_ARCHS[@]}"

    echo "Replacing original executable with thinned version"
    rm "$FRAMEWORK_EXECUTABLE_PATH"
    mv "$FRAMEWORK_EXECUTABLE_PATH-merged" "$FRAMEWORK_EXECUTABLE_PATH"

done

```

## 修改记录

情况仓库的 ChangedLog.md 文件