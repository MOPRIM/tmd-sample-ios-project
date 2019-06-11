//
//  TMD.h
//  MOPRIMTmdSdk
//
//  Created by Julien Mineraud on 09/11/2018.
//  Copyright © 2018 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import "TMDTask.h"
#import "TMDDelegate.h"

NS_ASSUME_NONNULL_BEGIN

/** Use this class to initialize the TMD with initWithKey:withEndpoint: as soon as possible in your AppDelegate's didFinishLaunchingWithOptions method.*/
@interface TMD : NSObject

/** Initialize the Moprim TMD.
 * 
 * The call to this method should be placed as soon as possible in your AppDelegate's didFinishLaunchingWithOptions method.
 * @param key your API key
 * @param endpoint your API endpoint
 * @param launchOptions the launchOptions you get from your AppDelegate's didFinishLaunchingWithOptions method. Pass nil if launchOptions is not available.
 * The launchOptions parameter can be used to wake up the TMD when your app is being launched in the background (for example after a significant location change event).*/
+ (TMDTask *)initWithKey:(NSString *)key withEndpoint:(NSString *)endpoint withLaunchOptions:(NSDictionary* _Nullable)launchOptions;

/// \returns TRUE if the TMD has been properly initialized
+ (BOOL) isInitialized;

/// \returns TRUE if the TMD service is active and analysing mobility
+ (BOOL) isRunning;

/// \returns TRUE if the TMD service is active, and no mobility has been detected
+ (BOOL) isIdle;

/// \returns TRUE if the TMD service is active (can be in idle or running state)
+ (BOOL) isOn;

/// \returns TRUE if the TMD service is disabled
+ (BOOL) isOff;

/// \returns the time in seconds that the TMD has been recording data
+ (NSTimeInterval) getRunningTime;

/// Get the unique user id associated with this installation
+ (NSString *) getUUID;

/// Set a unique user id to gather data from multiple installations
/// @param uuid the unique user id
+ (void) setUUID:(nullable NSString *)uuid;

/** Retrieve the unique application installation id of application using the SDK
 * \returns a TMDTask object containing the unique installation id*/
+ (TMDTask<NSString *> *) getInstallationId;

/** Starts the TMD service
 * The state of the TMD after this call will be On, and either idle or running. */
+ (void) start;

/** Stops the TMD service
 * The state of the TMD after this call will be Off. */
+ (void) stop;

/** Use this methods from your AppDelegate's performFetchWithCompletionHandler method in order for the app to update its data regularly in the background.
 *
 * Use the returned value to make a UIBackgroundFetchResult value to pass to the completionHandler.
 * If you have to make your own background fetch as well, it is your responsibility to pass a suitable UIBackgroundFetchResult to the completion handler that would combine your background fetch result with the TMD's background fetch result.
 * \returns a NSNumber containing an integer representing the UIBackgroundFetchResult rawValue */
+ (TMDTask<NSNumber*> *) backgroundFetch;

/// Set an object which adopts the TMDDelegate protocol as a delegate in order to receive events from the TMD.
+ (void) setDelegate:(id<TMDDelegate> _Nullable)delegate;

@end

NS_ASSUME_NONNULL_END
