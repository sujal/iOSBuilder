//
//  SingleTargetAppDelegate.h
//  SingleTarget
//
//  Created by Sujal Shah on 2/11/11.
//  Copyright 2011 Sujal Shah. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SingleTargetViewController;

@interface SingleTargetAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    SingleTargetViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet SingleTargetViewController *viewController;

@end

