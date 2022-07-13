//
//  TMDUserApiDelegate.h
//  MOPRIMTmdSdk
//
//  Created by Kyrill Cousson on 15/07/2021.
//  Copyright © 2021 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol TMDUserApiDelegate <NSObject>
- (void)shouldDeleteUserData;
- (void)userDidSignIn;
- (void)userDidSignOut;
- (void)userSessionDidExpire;
@end
