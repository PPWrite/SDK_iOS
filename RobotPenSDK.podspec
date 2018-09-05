
Pod::Spec.new do |s|

  s.name         = "RobotPenSDK"
  s.version      = "0.0.1"
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
  ss.source_files  = "SDK/RobotPenSDK/*.a","SDK/RobotPenSDK/RobotPenSDK"
  end
  s.subspec 'RobotBoardSDK' do |ss|
  ss.source_files  = "SDK/RobotBoardSDK/*.a","SDK/RobotBoardSDK/RobotBoardSDK"
  end
  s.subspec 'RobotRecordSDK' do |ss|
  ss.source_files  = "SDK/RobotRecordSDK/*.a","SDK/RobotRecordSDK/RobotRecordSDK"
  end

end
