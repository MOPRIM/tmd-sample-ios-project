//
//  TMDNotifications.h
//  Demo
//
//  Created by Kyrill Cousson on 20/04/2021.
//  Copyright © 2021 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>

/// This class offers static functions to get the names of NSNotifications that can be registered to.
@interface TMDNotifications : NSObject

/** By registering to NSNotifications with that name, you will get a NSNotification containing a dictionary of TMDTripNotification arrays indicating the trips that have been updated into the local cache.
 Keys of the dictionary are insertedTripsKey, updatedTripsKey, and deletedTripsKey. */
+ (NSString*)didUpdateTripsNotificationName;

/** By registering to NSNotifications with that name, you will get a NSNotification containing a dictionary of TMDActivity arrays indicating the activities that have been updated into the local cache.
 Keys of the dictionary are insertedActivitiesKey, updatedActivitiesKey, and deletedActivitiesKey. */
+ (NSString*)didUpdateActivitiesNotificationName;

/// This key can be used with the dictionary gotten from the didUpdateTripsNotificationName notification to get the list of inserted trips.
+ (NSString*)insertedTripsKey;
/// This key can be used with the dictionary gotten from the didUpdateTripsNotificationName notification to get the list of updated trips.
+ (NSString*)updatedTripsKey;
/// This key can be used with the dictionary gotten from the didUpdateTripsNotificationName notification to get the list of deleted trips.
+ (NSString*)deletedTripsKey;

/// This key can be used with the dictionary gotten from the didUpdateActivitiesNotificationName notification to get the list of inserted activities.
+ (NSString*)insertedActivitiesKey;
/// This key can be used with the dictionary gotten from the didUpdateActivitiesNotificationName notification to get the list of updated activities.
+ (NSString*)updatedActivitiesKey;
/// This key can be used with the dictionary gotten from the didUpdateActivitiesNotificationName notification to get the list of deleted activities.
+ (NSString*)deletedActivitiesKey;

@end
