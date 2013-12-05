//
//  ChasseTaupiqueurAppController.h
//  ChasseTaupiqueur
//
//  Created by 계명대학교  on 13. 12. 3..
//  Copyright __MyCompanyName__ 2013년. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

