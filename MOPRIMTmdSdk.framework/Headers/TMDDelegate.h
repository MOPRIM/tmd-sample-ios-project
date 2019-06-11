//
//  TMDUploadCallback.h
//  Demo
//
//  Created by Julien Mineraud on 22/11/2018.
//  Copyright © 2018 Julien Mineraud. All rights reserved.
//
#import <Foundation/Foundation.h>

/// Use the TMDDelegate to be notified of success or failure after starting or stopping the TMD.
@protocol TMDDelegate <NSObject>

@optional

/// Indicates that the TMD service started without errors
- (void)didStart;

/// Indicates that the TMD service could not start because of an error
- (void)didNotStartWithError:(NSError *)error;

/// Indicates that the TMD service stopped without errors
- (void)didStop;

/// Indicates that the TMD service stopped with an error
- (void)didStopWithError:(NSError *)error;

@end
