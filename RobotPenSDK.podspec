
Pod::Spec.new do |s|

  s.name         = "RobotPenSDK"
  s.version      = "3.2.4"
  s.summary      = "A SDK for RobotPenServer."
  s.description  = "A SDK for RobotServer.RobotPenServer、RobotBoardSDK、RobotRecordSDK"
  s.homepage     = "https://github.com/PPWrite/SDK_iOS"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "OneQuietCat" => "onequietcat@gmail.com" }
  s.platform     = :ios, "8.0"
  s.ios.deployment_target = "8.0"
  s.source       = { :git => "https://github.com/PPWrite/SDK_iOS.git", :tag => "#{s.version}" }
  s.requires_arc = true



  s.subspec 'RobotPenSDK' do |ss|
  ss.source_files  = "SDK/RobotPenSDK/*.a"
 # robotPenSDK.public_header_files  = "SDK/RobotPenSDK/RobotPenSDK/**/*.h"
    ss.subspec 'Header' do |sss|
      sss.source_files = "SDK/RobotPenSDK/RobotPenSDK/**/*"
    end 
  end
  s.subspec 'RobotBoardSDK' do |ss|
  ss.source_files  = "SDK/RobotBoardSDK/*.a"
  ss.dependency 'RobotPenSDK/RobotPenSDK'
  #robotBoardSDK.public_header_files  = "SDK/RobotBoardSDK/RobotBoardSDK/**/*.h"
    ss.subspec 'Header' do |sss|
      sss.source_files = "SDK/RobotBoardSDK/RobotBoardSDK/**/*"
    end
  end
  s.subspec 'RobotRecordSDK' do |ss|
  ss.source_files  = "SDK/RobotRecordSDK/*.a"
  ss.dependency 'RobotPenSDK/RobotBoardSDK'
  #robotRecordSDK.public_header_files  = "SDK/RobotRecordSDK/RobotRecordSDK/**/*.h"
    ss.subspec 'Header' do |sss|
      sss.source_files = "SDK/RobotRecordSDK/RobotRecordSDK/**/*"
    end
  end

end
