//
//  AppDelegate.swift
//  TMD Sample Project
//
//  Created by Kyrill Cousson on 11/06/2019.
//  Copyright © 2019 MOPRIM. All rights reserved.
//

import UIKit
import MOPRIMTmdSdk

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?
    let didInitializeTMD = NSNotification.Name(rawValue: "TMD.didInitialize")

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        
        // Fetch data as soon as possible
        UIApplication.shared.setMinimumBackgroundFetchInterval(UIApplication.backgroundFetchIntervalMinimum)
        
        let myKey = ""
        let myEndpoint = ""
        
        NSLog("My key, %@", myKey)
        NSLog("My endpoint, %@", myEndpoint)
        
        TMD.initWithKey(myKey, withEndpoint: myEndpoint, withLaunchOptions: launchOptions).continueWith (block: { (task) -> Any? in
            
            if let error = task.error {
                NSLog("Error at TMD init:%@", error.localizedDescription)
            } else if let result = task.result {
                NSLog("Successfully initialized the TMD with id %@", result as! String)
                NotificationCenter.default.post(name: self.didInitializeTMD, object: nil)
            }
            return task;
        })
        
        return true
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }

    
    // Called by the application UIBackgroundFetch process
    func application(_ application: UIApplication, performFetchWithCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
        // Run our background operations
        TMD.backgroundFetch().continueWith (block: { (task) -> Void in
            let tmdFetchResult:UIBackgroundFetchResult = UIBackgroundFetchResult(rawValue: (task.result!.uintValue))!
            
            // Call the completion handler with the UIBackgroundFetchResult returned by TMD.backgroundFetch(), or with your own background fetch result
            completionHandler(tmdFetchResult)
        })
    }

    func application(_ application: UIApplication, handleEventsForBackgroundURLSession identifier: String, completionHandler: @escaping () -> Void) {
        TMD.application(application, handleEventsForBackgroundURLSession: identifier, completionHandler: completionHandler)
    }
}

