# TMD Sample project (iOS)

This is a Sample project that shows how the iOS TMD SDK can be integrated into a Swift application project.
For more information, read the [SDK documentation](http://www-tmd-sdk-documentation.s3-website.eu-central-1.amazonaws.com/ios/).

## Installation

- Download the AWS XCFrameworks from [this link](https://github.com/aws-amplify/aws-sdk-ios/releases/download/2.26.3/aws-sdk-ios-carthage.framework.zip).
- Move the following XCFrameworks into `XCFrameworks/AWS_XCFrameworks`:

```
AWSCore.xcframeworkAWSS3.xcframeworkAWSCognitoIdentityProviderASF.xcframeworkAWSCognitoIdentityProvider.xcframeworkAWSAPIGateway.xcframework
```

- Run `pod install` from the root directory.
- Open the **.xcworkspace** file.
- Set `myKey` and `myEndpoint` in **AppDelegate.swift**.
- You're good to go!

## Usage

### 1. Requesting location access

Start by tapping the "Request Location Access" button, and give access to your location "While Using the app" and then agree to also share your location "Always".

![Allow Location Access](/images/AllowLocationAccess.png)

Note that you can also start the TMD first, and it will take care of asking the necessary permissions, but in your own app that will use the TMD SDK, you ideally want to request the user for the location access before starting the TMD.

This allows you to have better control of how the permission is asked to the user, and it gives you the opportunity to explain to the user why they need to share their location.

You can see an example of how this is done in this project in the `requestLocationAccess(_ sender: Any)` method of **ViewController.swift**.

### 2. Starting the TMD

- Toggle the switch to start or stop the TMD service.
- See the related code in the `switchValueChanged(sender: UISwitch)` method of **ViewController.swift**.
- You can also observe in the console the logs printed by the TMDDelegate methods.
Go to **`MARK: - TMDDelegate methods`** in **ViewController.swift** to see the related code.

### 3. Viewing the data

The detected transport modes will be displayed in the TableView.

![Viewing Data](/images/ViewingData.png)


#### Choosing a day:
- You can tap the current date to show the DatePicker and fetch data for a particular day.
- You can also use the bottom left and bottom right arrows to navigate to the previous or following day.
- You can tap the "Today" button to go back to the current day.
- And you can use the Refresh button to refresh the data for the selected date.
- Go to **`MARK: - Updating view for selected date`** in **ViewController.swift** to see the related code.


### 4. Uploading data
- Data uploads are handled automatically by the TMD SDK, but you can also force an upload by taping the upload button.
- See the related code in the `uploadData(sender: UIBarButtonItem)` method of **ViewController.swift**.



## More information
You will find more information about the TMD SDK and how to use it in our [TMD SDK documentation](http://www-tmd-sdk-documentation.s3-website.eu-central-1.amazonaws.com/ios/).

You got here by mistake, and you want to know more about MOPRIM or our Transport Mode Detection SDK?
Check our [company website](https://www.moprim.com).
