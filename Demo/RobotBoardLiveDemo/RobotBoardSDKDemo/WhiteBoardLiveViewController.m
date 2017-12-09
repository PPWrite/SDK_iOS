//
//  WhiteBoardLiveViewController.m
//  RobotBoardSDKDemo
//
//  Created by JMS on 2017/2/22.
//  Copyright © 2017年 JMS. All rights reserved.
//

#import "WhiteBoardLiveViewController.h"
#import "SDKManager.h"
#import "WhiteBoardLiveStudioViewController.h"
@interface WhiteBoardLiveViewController ()

@property (weak, nonatomic) IBOutlet UIButton *BackButton;

@property (weak, nonatomic) IBOutlet UITextField *userIDTF;

@property (weak, nonatomic) IBOutlet UITextField *userSessionTF;

@property (weak, nonatomic) IBOutlet UITextField *liveIDTF;

@property (weak, nonatomic) IBOutlet UITextField *passwordTF;

@property (weak, nonatomic) IBOutlet UIButton *EnterButton;
@end

@implementation WhiteBoardLiveViewController



-(void)BackButtonPressed:(UIButton *)sender
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(void)EnterButtonPressed:(UIButton *)sender
{
    WhiteBoardLiveStudioViewController *LiveWB = [[WhiteBoardLiveStudioViewController alloc] init];
    
    LiveWB.userIDStr = _userIDTF.text;
    LiveWB.userSessionStr = _userSessionTF.text;
    LiveWB.liveIDStr = _liveIDTF.text;
    LiveWB.passwordStr = _passwordTF.text;
    
    [self presentViewController:LiveWB animated:YES completion:nil];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _userIDTF.placeholder = @"10025";
    _userSessionTF.placeholder = @"ddaf98f60442ded1c3e44d27629d78da";
    _liveIDTF.placeholder = @"15";
    _passwordTF.placeholder = @"";
    
    [_BackButton addTarget:self action:@selector(BackButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_EnterButton addTarget:self action:@selector(EnterButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    // Do any additional setup after loading the view from its nib.

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
