//
//  TMDTripNotification.h
//  Demo
//
//  Created by Kyrill Cousson on 11/05/2021.
//  Copyright © 2021 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TMDTrip.h"
#import "TMDTask.h"

NS_ASSUME_NONNULL_BEGIN

/// This class includes basic information about TMDTrip objects that have been updated into the cache (See TMDNotifications).
@interface TMDTripNotification : NSObject

/// The unique id of the trip when stored in the local cache
@property (assign) long long tripId;

/// The UTC timestamp (in ms) of the last download of the TMD trip
@property long long timestampDownload;

/// The UTC timestamp (in ms) of the last modification of the TMD trip
@property (assign) long long timestampModified;

/// Returns the UTC timestamp (in ms) of the start of the TMD trip
@property long long timestampStart;

/// Returns the UTC timestamp (in ms) of the end of the TMD trip
@property long long timestampEnd;

/**
 * This field is important for reporting
 * Returns true if the trip has been validated by the user
 */
@property BOOL isValidated;

/**
 * This fields tells if the trip is completed and thus, may be not be modified without the user's input
 * Returns true if the trip is completed.
 */
@property BOOL isCompleted;

/// Indicates whether change made manually on the trip have been synced with the cloud
@property BOOL syncedWithCloud;



- (instancetype)initWithId:(long long)tripId
         timestampDownload:(long long)timestampDownload
            timestampStart:(long long)timestampStart
              timestampEnd:(long long)timestampEnd
         timestampModified:(long long)timestampModified
               isValidated:(BOOL)isValidated
               isCompleted:(BOOL)isCompleted
                    synced:(BOOL)syncedWithCloud;


/// Returns the trip from the local database
- (TMDTask <TMDTrip*> *)getTrip;

@end

NS_ASSUME_NONNULL_END
