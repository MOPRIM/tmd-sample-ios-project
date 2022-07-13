//
//  TMDTravelChain.h
//  MOPRIMTmdSdk
//
//  Created by Kyrill Cousson on 04/03/2021.
//  Copyright © 2021 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TMDActivity.h"

NS_ASSUME_NONNULL_BEGIN

/// This class includes all information pertaining to the TMD trip collected from the Moprim Cloud.
@interface TMDTrip : NSObject

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
 * The distance of the trip in meters
 * Returns the distance of the trip
 */
@property (assign) double distance;

/**
 * The co2 produced during this trip
 * Returns the co2 produced in grams
 */
@property (assign) double co2;

/**
 * The name of the origin for the trip
 * Returns the origin of the trip
 */
@property (nonatomic, strong) NSString *origin;

/**
 * The destination of the trip
 * Returns the destination
 */
@property (nonatomic, strong) NSString *destination;

/**
 * The reason for the trip
 * Returns the reason for the trip
 */
@property (nonatomic, strong) NSString *reason;

/**
 * The metadata for the trip
 * Returns the metadata for the trip
 */
@property (nonatomic, strong) NSString *metadata;

/// The checksum of the trip
@property (nonatomic, strong) NSString *checksum;

/**
 * Get the list of legs for this trip
 * Returns the list of legs for this trip
 */
@property (nonatomic, strong) NSArray<TMDActivity *> *legs;

/// Returns the main mode of the trip
@property (nonatomic, strong) NSString *mainMode;

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
                      legs:(NSArray<TMDActivity*> *)legs
                  mainMode:(NSString *)mainMode
                       co2:(double)co2
                  distance:(double)distance
                    origin:(NSString *)origin
               destination:(NSString *)destination
                    reason:(NSString *)reason
                  metadata:(NSString *)metadata
                  checksum:(NSString *)checksum
               isValidated:(BOOL)isValidated
               isCompleted:(BOOL)isCompleted
                    synced:(BOOL)syncedWithCloud;

/// Returns a leg from the list of legs for this trip
- (TMDActivity*)getLegAt:(int)position;

/// Returns the duration in seconds of the trip
- (NSTimeInterval)duration;

/**
 * Check whether the trip has legs
 * Returns true if the trip has legs, false otherwise
 */
- (bool)hasLegs;

/**
 * The size of the trip
 * Returns the number of legs in the trip
 */
- (int)size;

/** Returns TRUE if the trip has same start and stop timestamp than 'other'
 *
 * Trips are usually compared with their timestamps.*/
- (BOOL)hasSameTimestampsThanTrip:(TMDTrip *)other;

/// Returns TRUE if the timestamps of both trips overlap
- (BOOL)overlapsWithTrip:(TMDTrip *)other isInclusive:(BOOL)isInclusive;

/// Compares 2 TMDTrip objects, ignoring tripId, timestampDownload, timestampModified and syncedWithCloud
- (BOOL)hasSameDataThanTrip:(TMDTrip *)other;


@end

NS_ASSUME_NONNULL_END
