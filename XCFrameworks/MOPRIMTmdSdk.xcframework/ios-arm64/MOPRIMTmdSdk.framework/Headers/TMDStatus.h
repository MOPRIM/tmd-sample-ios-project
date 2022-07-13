//
//  TMDStatus.h
//  MOPRIMTmdSdk
//
//  Created by Kyrill Cousson on 25/09/2020.
//  Copyright © 2020 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TMDStatusName.h"

NS_ASSUME_NONNULL_BEGIN

/** TMDStatus objects indicate the status of the TMD between two timestamps.
 *
 * See TMDStatusName for the list of possible status names.
 *
 * See TMDCloudApi for methods to fetch TMDStatus objects.
 */
@interface TMDStatus : NSObject

@property (assign) long long tmdStatusId;
@property (assign) long long timestampStart;
@property (assign) long long timestampEnd;
@property (nonatomic, strong) NSString *label;
@property BOOL syncedWithCloud;

- (instancetype)initWithId:(long long)tmdStatusId
        withTimestampStart:(long long)timestampStart
         withTimestampStop:(long long)timestampStop
                 withLabel:(NSString *)label
                withSynced:(BOOL)syncedWithCloud;

- (NSTimeInterval)duration;

+ (NSString*) tmdStatusNameToString:(TMDStatusName) tmdStatusName;

/// See TMDStatusName for a list of possible values.
- (TMDStatusName) tmdStatusName;

@end

NS_ASSUME_NONNULL_END
