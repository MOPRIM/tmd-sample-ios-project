//
//  TMDCloudApi.h
//  MOPRIMTmdSdk
//
//  Created by Julien Mineraud on 27/11/2018.
//  Copyright © 2018 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "TMDTask.h"
#import "TMDActivity.h"
#import "TMDStats.h"
#import "TMDTrip.h"
#import "TMDStatus.h"
#import "TMDCloudMetadata.h"
#import "TMDUploadMetadata.h"
#import "TMDUploadDelegate.h"

NS_ASSUME_NONNULL_BEGIN

/// This class offers static functions to interact with the Moprim Cloud. Most common use cases are fetching data and metadata and uploading data to the sync.
@interface TMDCloudApi : NSObject


/*! @brief Fetch TMD activity data from the Moprim Cloud for the defined date
 * @param date the date (only the day, month, year components are relevant)
 * @param offset Number of minutes after midnight that indicates the start of the day. (example: if you want data for the day and consider that days should be separated at 4AM instead of midnight, set this parameter to 240.0.
 * Set this parameter to 0.0 if you want days to be separated at midnight.
 * @return A list of TMD activities if successful, an error otherwise.
 */
+ (TMDTask<NSArray<TMDActivity *> *> *) fetchData:(NSDate *)date minutesOffset:(double)offset;

/*! @brief Fetch TMD activity data from the Moprim Cloud between two timestamps
 * @param start the start time (timestamp in ms)
 * @param end the end time (timestamp in ms)
 * @return A list of TMD activities if successful, an error otherwise.
 */
+ (TMDTask<NSArray<TMDActivity *> *> *) fetchDataWithStart:(long long)start withEnd:(long long)end;

/** Fetch TMD activity data from the cache for the defined date
 *
 * Use this method if you wish not to request data from the cloud
 * @param date the date (only the day, month, year components are relevant)
 * @param offset Number of minutes after midnight that indicates the start of the day. (example: if you want data for the day and consider that days should be separated at 4AM instead of midnight, set this parameter to 240.0.
 * Set this parameter to 0.0 if you want days to be separated at midnight.
 * @return A list of TMD activities if successful, an error otherwise.
 */
+ (TMDTask<NSArray<TMDActivity *> *> *) fetchDataFromCache:(NSDate *)date minutesOffset:(double)offset NS_SWIFT_NAME(fetchDataFromCache(_:minutesOffset:));

/** Fetch TMD activity data from the cache between two timestamps
 *
 * Use this method if you wish not to request data from the cloud
 * @param start the start time (timestamp in ms)
 * @param end the end time (timestamp in ms)
 * @return A list of TMD activities if successful, an error otherwise.
*/
+ (TMDTask<NSArray<TMDActivity *> *> *) fetchDataFromCacheWithStart:(long long)start withEnd:(long long)end;

/** Fetch the last TMD Trip from the Moprim Cloud.
 * @return The last TMD Trip if successful, an error otherwise.
*/
+ (TMDTask <TMDTrip *> *) fetchLastTrip;

/** Fetch the last TMD Trips from the Moprim Cloud.
 * @param count the number of TMD Trips you wish to receive
 * @return A list of TMD Trips if successful, an error otherwise.
*/
+ (TMDTask <NSArray<TMDTrip *> *> *) fetchLastTrips:(int)count;

/*! @brief Fetch TMD Trips from the Moprim Cloud between two timestamps.
 * @param start the start time (timestamp in ms)
 * @param end the end time (timestamp in ms)
 * @return A list of TMD Trips if successful, an error otherwise.
 */
+ (TMDTask <NSArray<TMDTrip *> *> *) fetchTripsWithStart:(long long)start withEnd: (long long)end;

/*! @brief Fetch TMD Trips from the Moprim Cloud for the defined date.
 * @param date the date (only the day, month, year components are relevant)
 * @param offset Number of minutes after midnight that indicates the start of the day. (example: if you want data for the day and consider that days should be separated at 4AM instead of midnight, set this parameter to 240.0.
 * Set this parameter to 0.0 if you want days to be separated at midnight.
 * @return A list of TMD Trips if successful, an error otherwise.
 */
+ (TMDTask <NSArray<TMDTrip *> *> *) fetchTripsForDate:(NSDate *)date minutesOffset:(double)offset;

/** Fetch the last TMD Trip from the cache.
 * @return The last TMD Trip if successful, an error otherwise.
*/
+ (TMDTask <TMDTrip *> *) fetchLastTripFromCache;

/** Fetch the last TMD Trips from the cache.
 * @param count the number of TMD Trips you wish to receive
 * @return A list of TMD Trips if successful, an error otherwise.
*/
+ (TMDTask <NSArray<TMDTrip *> *> *) fetchLastTripsFromCache:(int)count;

/*! @brief Fetch TMD Trips from the cache between two timestamps.
 * @param start the start time (timestamp in ms)
 * @param end the end time (timestamp in ms)
 * @return A list of TMD Trips if successful, an error otherwise.
 */
+ (TMDTask <NSArray<TMDTrip *> *> *) fetchTripsFromCacheWithStart:(long long)start withEnd: (long long)end;

/*! @brief Fetch TMD Trips from the cache for the defined date.
 * @param date the date (only the day, month, year components are relevant)
 * @param offset Number of minutes after midnight that indicates the start of the day. (example: if you want data for the day and consider that days should be separated at 4AM instead of midnight, set this parameter to 240.0.
 * Set this parameter to 0.0 if you want days to be separated at midnight.
 * @return A list of TMD Trips if successful, an error otherwise.
 */
+ (TMDTask <NSArray<TMDTrip *> *> *) fetchTripsFromCacheForDate:(NSDate *)date minutesOffset:(double)offset;


/*! @brief Fetch TMD Statuses related to errors for the defined date.
 * @param date the date (only the day, month, year components are relevant)
 * @param offset Number of minutes after midnight that indicates the start of the day. (example: if you want data for the day and consider that days should be separated at 4AM instead of midnight, set this parameter to 240.0.
 * Set this parameter to 0.0 if you want days to be separated at midnight.
 * @param statusDuration minimum duration of the requested statuses.
 * @return A list of TMDStatus that indicate an error.
 */
+ (TMDTask <NSArray<TMDStatus *> *> *)fetchTmdErrorStatusesFromCache:(NSDate *)date
                                                       minutesOffset:(double)offset
                                           withMinimumStatusDuration:(NSTimeInterval)statusDuration;

/*! @brief Fetch TMD Statuses related to errors between two timestamps.
 * @param start the start time (timestamp in ms)
 * @param end the end time (timestamp in ms)
 * @param statusDuration minimum duration of the requested statuses.
 * @return A list of TMDStatus that indicate an error.
 */
+ (TMDTask<NSArray<TMDStatus *> *> *) fetchTmdErrorStatusesFromCacheWithStart:(long long)start
                                                                      withEnd:(long long)end
                                                    withMinimumStatusDuration:(NSTimeInterval)statusDuration;

/*! @brief Fetch the last TMD Status indicating the app was killed between two timestamps.
 * @param start the start time (timestamp in ms)
 * @param end the end time (timestamp in ms)
 * @param statusDuration minimum duration of the status.
 * @return A TMDStatus that indicates that the app was killed, or a nil object if there nothing to return.
 */+ (TMDTask<TMDStatus *> *) fetchLastAppKilledTmdStatusFromCacheBetweenStart:(long long)start
                                                                     andEnd:(long long)end
                                                  withMinimumStatusDuration:(NSTimeInterval)statusDuration;

/*!
 * @brief Fetching stats from the Moprim cloud.
 * @param nbDays the number of days to compute the statistics for (e.g. 30 for the last 30 days)
 * @return A TMDStats object containing the statistics.
 */
+ (TMDTask<TMDStats *> *) fetchStatsForLast: (NSInteger) nbDays;

/*!
* @brief Fetching stats from the cloud
* @param startDate the start date in ISO format "yyyy-MM-dd"
* @param endDate the end date in ISO format "yyyy-MM-dd"
* @return A TMDStats object containing the statistics between startDate and endDate (including those dates).
*/
+ (TMDTask <TMDStats *> *) fetchStatsWithStartDate :(NSString*)startDate withEnd: (NSString*)endDate;

/*!
 * @brief Fetching stats from the local cache
 * @param nbDays the number of days to compute the statistics for (e.g. 30 for the last 30 days)
 * @return A TMDStats object containing the statistics.
 */
+ (TMDTask <TMDStats *> *) fetchStatsFromCacheForLast: (NSInteger) nbDays;

/*!
* @brief Fetching stats from the local cache
* @param startDate the start date in ISO format "yyyy-MM-dd"
* @param endDate the end date in ISO format "yyyy-MM-dd"
* @return A TMDStats object containing the statistics between startDate and endDate (including those dates).
*/
+ (TMDTask <TMDStats*> *) fetchStatsFromCacheWithStartDate :(NSString*)startDate withEnd: (NSString*)endDate;

/** Fetch the metadata from the Cloud.
 *
 * This function is usually called when one wants to know what data can be fetched from the Cloud
 * @return The cloud metadata.
 */
+ (TMDTask<TMDCloudMetadata *> *) fetchMetadata;

/** Fetch the metadata from the cache.
 *
 * This function is usually called when one wants to know what data can be fetched from the Cloud
 * @return The cloud metadata.
 */
+ (TMDTask<TMDCloudMetadata *> *) fetchMetadataFromCache;

/*!
 * @brief Upload the collected data to the cloud pro-actively
 * @return A TMDUploadMetadata object indicating how much data was sent.
 */
+ (TMDTask<TMDUploadMetadata *> *) uploadData;

/*!
* @brief Upload the collected data to the cloud pro-actively and notifies the delegate when the upload starts and ends
* @return A TMDUploadMetadata object indicating how much data was sent.
*/
+ (TMDTask <TMDUploadMetadata *> *) uploadDataWithDelegate:(id<TMDUploadDelegate> _Nullable)delegate;


/*!
 * @brief Correct the label of activity
 * @param activity the activity to correct
 * @param correctedLabel the new label
 * @return The corrected activity object.
 */
+ (TMDTask<TMDActivity*>*) correctActivity:(TMDActivity*)activity withLabel:(NSString*)correctedLabel NS_SWIFT_NAME(correctActivity(_:withLabel:));

/*!
 * @brief Annotate the activity with metadata
 * @param activity the activity to annotate
 * @param metadata the metadata
 * @return The annotated activity object.
 */
+ (TMDTask<TMDActivity *> *) annotateActivity:(TMDActivity *)activity withMetadata: (NSString *)metadata;

/*!
 * @brief Update the label and metadata of the activity
 * @param activity the activity to update
 * @param correctedLabel the new label
 * @param metadata the metadata
 * @return The updated activity object.
 */
+ (TMDTask<TMDActivity *> *) updateActivity:(TMDActivity *)activity
                                   withLabel:(NSString *)correctedLabel
                               withMetadata:(NSString *)metadata NS_SWIFT_NAME(updateActivity(_:withLabel:withMetadata:));


/*!
 * @brief Validates the trip
 * @param trip the trip to validate
 * @return The updated trip object.
 */
+ (TMDTask <TMDTrip *> *) validateTrip:(TMDTrip *)trip NS_SWIFT_NAME(validateTrip(_:));

/*!
 * @brief Update the reason and metadata of the trip
 * @param trip the trip to update
 * @param reason the reason of the trip
 * @param metadata the metadata
 * @return The updated trip object.
 */
+ (TMDTask <TMDTrip *> *) updateTrip:(TMDTrip *)trip
                         withReason:(NSString*)reason
                        withMetadata:(NSString*)metadata NS_SWIFT_NAME(updateTrip(_:withReason:withMetadata:));
@end

NS_ASSUME_NONNULL_END
