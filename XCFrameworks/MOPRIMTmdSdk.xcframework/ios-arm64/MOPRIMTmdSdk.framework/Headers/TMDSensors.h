//
//  TMDSensors.h
//  Demo
//
//  Created by Kyrill Cousson on 28/07/2020.
//  Copyright © 2020 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>

/// This class offers static functions to get the possible names of TMDSensors used by TMD.checkForMissingSensors().
@interface TMDSensors : NSObject

+ (NSString*)locationSensor;
+ (NSString*)accelerometerSensor;
+ (NSString*)gyroscopeSensor;
+ (NSString*)magnetometerSensor;
+ (NSString*)altimeterSensor;
+ (NSString*)gravitySensor;
+ (NSString*)pedometerSensor;
+ (NSString*)motionActivitySensor;

@end
