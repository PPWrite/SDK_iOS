Pod::Spec.new do |s|

  s.name         = "RobotPenSDK"
  s.version      = "4.2.6"
  s.summary      = "A SDK for RobotPenServer."
  s.description  = "A SDK for RobotServer.RobotPenServer、RobotBoardServer、RobotRecordServer."
  s.homepage     = "https://github.com/PPWrite/SDK_iOS"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "OneQuietCat" => "onequietcat@gmail.com" }
  s.platform     = :ios, "8.0"
  s.ios.deployment_target = "8.0"
  s.source       = { :git => "https://github.com/PPWrite/SDK_iOS.git", :tag => "#{s.version}" }
  s.requires_arc = true


  s.subspec 'RobotPenSDK' do |pen|
    pen.source_files  = "SDK/RobotPenSDK/RobotPenSDKHeader/*.h"
    pen.public_header_files  = "SDK/RobotPenSDK/RobotPenSDKHeader/*.h"
    pen.vendored_libraries =  'SDK/RobotPenSDK/Libraries/*.a'
    pen.libraries = 'sqlite3'
  end

  s.subspec 'RobotBoardSDK' do |board|
    board.source_files  = "SDK/RobotBoardSDK/RobotBoardSDKHeader/*.h"
    board.public_header_files  = "SDK/RobotBoardSDK/RobotBoardSDKHeader/*.h"
    board.vendored_libraries =  'SDK/RobotBoardSDK/Libraries/*.a'
    board.libraries = 'z'
    board.frameworks = 'UIKit','Foundation'
    board.dependency 'RobotPenSDK/RobotPenSDK'
  end

  s.subspec 'RobotRecordSDK' do |record|
    record.source_files  = "SDK/RobotRecordSDK/RobotRecordSDKHeader/*.h"
    record.public_header_files  = "SDK/RobotRecordSDK/RobotRecordSDKHeader/*.h"
    record.vendored_libraries =  'SDK/RobotRecordSDK/Libraries/*.a'
    record.frameworks = 'AudioToolbox','CoreTelephony'
    record.dependency 'RobotPenSDK/RobotBoardSDK'
  end

end
