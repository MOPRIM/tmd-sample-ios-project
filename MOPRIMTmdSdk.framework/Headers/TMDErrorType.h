//
//  TMDErrorType.h
//  MOPRIMTmdSdk
//
//  Created by Kyrill Cousson on 29/04/2019.
//  Copyright © 2019 Julien Mineraud. All rights reserved.
//

/// Enum of the possible errors
typedef NS_ENUM(NSInteger, TMDErrorType) {
    /// Triggered when the network operation was not successful
    TMDCouldNotConnectToTheInternet,
    
    /// Triggered the SDK key is invalid
    TMDSdkKeyInvalid,
    
    /// The SDK endpoint is invalid, in this condition the SDK cannot operate
    TMDSdkEndpointInvalid,
    
    /// The MOPRIM TMD ID is invalid. In this condition, the communications with the Cloud API cannot work
    TMDIdInvalid,
    
    /// Unknown Error found
    TMDUnknownError,
    
    /// Triggered if one starts the TMD service without a successful initialisation
    TMDNotInitialized,
    
    /// Triggered when one starts a long lasting operation on the main thread
    TMDNetworkOperationOnMainThread,
    
    /// Triggered when start/stop parameters include a two big gap. Current max 2 days
    TMDCloudFetchTooLong,
    
    /// Triggered when JSON object was not parsable
    TMDJsonParsingError,
    
    /// Triggered when an unexpected nil value was found
    TMDNilValueError,
    
    /// Triggered when JSON object was not parsable at a specified path
    TMDJsonParsingErrorForPath,
    
    /// Triggered when Cloud returned an error for a specified request path
    TMDRequestErrorForPath,
    
    /// Triggered when the Cloud is not responsive or has internal error
    TMDCloudStatusCodeNotOk,
    
    /// Triggered when the I/O operation could not be achieved
    TMDCloudCouldNotReadStream,
    
    /// Triggered when a given parameter is invalid
    TMDInvalidParameter,
    
    /// Triggered if one start and the TMD is already started
    TMDAlreadyStarted,
    
    /// Triggered if one start and the TMD is already stopped
    TMDAlreadyStopped,
    
    /// Triggered when the user does not allow sufficient access to location service (i.e., AuthorizedAlways)
    TMDLocationServicePermissionUnsufficient
};
