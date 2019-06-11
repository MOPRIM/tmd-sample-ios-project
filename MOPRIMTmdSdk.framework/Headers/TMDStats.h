//
//  TMDStats.h
//  MOPRIMTmdSdk
//
//  Created by Julien Mineraud on 27/11/2018.
//  Copyright © 2018 Julien Mineraud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TMDStatsValue : NSObject

/// The activity name
@property (nonatomic, strong) NSString *activity;

/// The amount of CO2 (in grams) generated during the activity
@property (assign) double co2;

/// The distance in meters covered in the activity
@property (assign) double distance;

/// The duration in seconds of the activity
@property (assign) NSTimeInterval duration;

- (instancetype)initWithActivity:(NSString *)activity co2:(double)co2 distance:(double)distance duration:(NSTimeInterval)duration;

@end

/** TMDStats contains information about a list of statistics for each type of activity and during a specific time period
  * (weekend vs. weekdays and last X days vs. overall.
  * For each value we provide the combined sum of CO2 emissions, the distance and duration of these activities. */
@interface TMDStats : NSObject

@property (nonatomic, strong) NSArray<TMDStatsValue *> *lastPeriodWeekDaysStats;
@property (nonatomic, strong) NSArray<TMDStatsValue *> *lastPeriodWeekendStats;
@property (nonatomic, strong) NSArray<TMDStatsValue *> *overallWeekDaysStats;
@property (nonatomic, strong) NSArray<TMDStatsValue *> *overallWeekendStats;

- (instancetype)init;
- (instancetype)initWithLastPeriodWeekDaysStats:(NSArray<TMDStatsValue *> *)lastPeriodWeekDaysStats
                     lastPeriodWeekendStats:(NSArray<TMDStatsValue *> *)lastPeriodWeekendStats
                       overallWeekDaysStats:(NSArray<TMDStatsValue *> *)overallWeekDaysStats
                        overallWeekendStats:(NSArray<TMDStatsValue *> *)overallWeekendStats;

+ (TMDStats *)fromJsonData:(NSData *)jsonData error:(NSError * _Nullable *)error;
+ (TMDStats *)fromDictionary:(NSDictionary *)stats error:(NSError * _Nullable *)error;
+ (NSDictionary *)toDictionary:(TMDStats *)stats error:(NSError * _Nullable *)error;

@end

NS_ASSUME_NONNULL_END
