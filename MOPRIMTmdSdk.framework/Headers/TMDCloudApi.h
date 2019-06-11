//
//  TMDCloudApi.h
//  MOPRIMTmdSdk
//
//  Created by Julien Mineraud on 27/11/2018.
//  Copyright © 2018 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TMDTask.h"
#import "TMDActivity.h"
#import "TMDStats.h"
#import "TMDCloudMetadata.h"
#import "TMDUploadMetadata.h"

NS_ASSUME_NONNULL_BEGIN

/// This class offers static functions to interact with the Moprim Cloud. Most common use cases are fetching data and metadata and uploading data to the sync.
@interface TMDCloudApi : NSObject


/*! @brief Fetch TMD activity data from the Moprim Cloud for the defined date
 * @param date the date
 * @return A list of TMD activities if successful, an error otherwise.
 */
+ (TMDTask<NSArray<TMDActivity *> *> *) fetchData:(NSDate *)date;

/*! @brief Fetch TMD activity data from the Moprim Cloud between two timestamps
 * @param start the start time (timestamp in ms)
 * @param end the end time (timestamp in ms)
 * @return A list of TMD activities if successful, an error otherwise.
 */
+ (TMDTask<NSArray<TMDActivity *> *> *) fetchDataWithStart:(long long)start withEnd:(long long)end;

/** Fetch TMD activity data from the cache for the defined date
 *
 * Use this method if you wish not to request data from the cloud
 * @param date the date
 * @return A list of TMD activities if successful, an error otherwise.
 */
+ (TMDTask<NSArray<TMDActivity *> *> *) fetchDataFromCache:(NSDate *)date NS_SWIFT_NAME(fetchDataFromCache(_:));

/** Fetch TMD activity data from the cache between two timestamps
 *
 * Use this method if you wish not to request data from the cloud
 * @param start the start time (timestamp in ms)
 * @param end the end time (timestamp in ms)
 * @return A list of TMD activities if successful, an error otherwise.
*/
+ (TMDTask<NSArray<TMDActivity *> *> *) fetchDataFromCacheWithStart:(long long)start withEnd:(long long)end;


/*! @brief Fetching stats from the Moprim cloud.
 * @param last the number of days to compute the statistics (e.g. 30 for the last month)
 * @return A TMDStats object containing the statistics.
 */
+ (TMDTask<TMDStats *> *) fetchStats: (NSInteger) last;

/*!
 * @brief Fetching stats from the local cache
 * @return A TMDStats object containing the statistics.
 */
+ (TMDTask<TMDStats *> *) fetchStatsFromCache;

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

@end

NS_ASSUME_NONNULL_END
