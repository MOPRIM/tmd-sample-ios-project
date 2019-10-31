//
//  TMDCloudMetadata.h
//  MOPRIMTmdSdk
//
//  Created by Julien Mineraud on 27/11/2018.
//  Copyright © 2018 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// TMD metadata contains information about the information that our cloud knows about a user:
@interface TMDCloudMetadata : NSObject

/// The first timestamp (in milliseconds) that we received data (i.e., start of the first recognized activity)
@property (assign) long long firstTimestamp;

/// The last timestamp (in milliseconds) that we received data
@property (assign) long long lastTimestamp;

/// The last timestamp of an uploaded TMD activity
@property (assign) long long lastTmdTimestamp;

/// The last timestamp of an uploaded location
@property (assign) long long lastLocationTimestamp;

/// The last timestamp when TMD was synced with the cloud
@property (assign) long long lastUploadedTmdTimestamp;

/// The last timestamp when location was synced with the cloud
@property (assign) long long lastUploadedLocationTimestamp;

/// The average daily co2 value for the community
@property (assign) double communityDailyCo2;

/// The average daily distance value for the community
@property (assign) double communityDailyDistance;

/// The average daily duration value for the community
@property (assign) double communityDailyDuration;

- (instancetype)initWithFirstTimestamp:(long long) firstTimestamp
                         lastTimestamp:(long long) lastTimestamp
                      lastTmdTimestamp:(long long) lastTmdTimestamp
                 lastLocationTimestamp:(long long) lastLocationTimestamp
              lastUploadedTmdTimestamp:(long long) lastUploadedTmdTimestamp
         lastUploadedLocationTimestamp:(long long) lastUploadedLocationTimestamp
                     communityDailyCo2:(double) communityDailyCo2
                communityDailyDistance:(double) communityDailyDistance
                communityDailyDuration:(double) communityDailyDuration;

/// JSON description of the object.
- (NSString*) description;

@end

NS_ASSUME_NONNULL_END
