//
//  TMDStatusName.h
//  MOPRIMTmdSdk
//
//  Created by Kyrill Cousson on 01/02/2022.
//  Copyright © 2022 Julien Mineraud. All rights reserved.
//

/// Enum of the possible TMDStatusNames
typedef NS_ENUM(NSInteger, TMDStatusName) {
    /// At Tmd init, before the services start
    TMDEventNotRunning,
    
    /// TMD is active and monitoring motion
    TMDEventIdle,
    
    /// TMD is recording
    TMDEventRecording,
    
    /// TMD has stopped because location permission changed
    TMDEventStoppedCauseInsufficientPermission,
    
    /// TMD has been stopped manually via [TMD stop];
    TMDEventStoppedManually,
    
    /// TMD could not start because of a problem with Motion & Fitness service availability/permissions
    TMDEventStartFailedCauseInsufficientMotionFitnessServices,
    
    /// TMD could not start because of a problem with Location service availability/permissions
    TMDEventStartFailedCauseInsufficientLocationServices,
    
    /// Application was killed
    TMDEventAppKilled,
    
    /// Application was not running and the reason for that is unkown
    TMDEventAppNotRunningCauseUnknown,

    /// Unkown event
    TMDEventUnknown
};
