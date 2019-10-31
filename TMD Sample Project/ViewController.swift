//
//  ViewController.swift
//  Demo
//
//  Created by Kyrill Cousson on 11/06/2019.
//  Copyright © 2019 MOPRIM. All rights reserved.
//

import UIKit
import MOPRIMTmdSdk

class ViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, TMDDelegate {
    
    // MARK: - Parameters
    
    let dateFormatter = DateFormatter()
    private var activities: [TMDActivity] = []
    private let refreshControl = UIRefreshControl()
    private var timer: Timer = Timer()
    private var currentDate: Date = Date()
    private let pickerData = ["stationary",
                              "non-motorized/pedestrian/walk",
                              "non-motorized/pedestrian/run",
                              "non-motorized/bicycle",
                              "motorized/road/bus",
                              "motorized/road/car",
                              "motorized/rail/metro",
                              "motorized/rail/tram",
                              "motorized/rail/train",
                              "motorized/water/ferry",
                              "motorized/air/plane"]
    
    @IBOutlet weak var tmdSwitch: UISwitch!
    @IBOutlet weak var tmdStatusLabel: UILabel!
    @IBOutlet var tableview: UITableView!
    @IBOutlet weak var dateButton: UIButton!
    
    // MARK: - IBActions
    
    @IBAction func switchValueChanged(sender: UISwitch) {
        NSLog(sender.isOn ? "Switch On" : "Switch Off")
        if (sender.isOn) {
            TMD.start()
        }
        else {
            TMD.stop()
        }
    }
    
    @IBAction func today(sender: UIBarButtonItem) {
        updateDate(Date())
    }
    
    @IBAction func previousDay(sender: UIBarButtonItem) {
        updateDate(self.currentDate.addingTimeInterval(-60 * 60 * 24))
    }
    
    @IBAction func nextDay(sender: UIBarButtonItem) {
        updateDate(self.currentDate.addingTimeInterval(60 * 60 * 24))
    }
    
    func updateDate(_ newDate:Date){
        self.currentDate = newDate
        dateButton.setTitle(dateFormatter.string(from: self.currentDate), for: .normal)
        NSLog("Go to day: %@", dateFormatter.string(from: self.currentDate))
        updateViewForCurrentDate()
    }
    
    @IBAction func showDatePicker(_ sender: Any) {
        if let datePickerController = self.storyboard!.instantiateViewController(withIdentifier: "DatePickerController") as? DatePickerController {
            datePickerController.delegate = self
            datePickerController.date = self.currentDate
            datePickerController.modalPresentationStyle = .popover
            datePickerController.preferredContentSize = CGSize(width: 270, height: 140)
            if let popover = datePickerController.popoverPresentationController{
                popover.delegate = self
                popover.permittedArrowDirections = .up
                popover.sourceView = self.dateButton!
                popover.sourceRect = CGRect(x: self.dateButton!.frame.width/2, y: self.dateButton!.frame.height, width: 0, height: 0)
            }
            self.present(datePickerController, animated: true, completion: nil)
        }
    }
    @IBAction func uploadData(sender: UIBarButtonItem) {
        NSLog("Uploading data")
        TMDCloudApi.uploadData().continueWith { (task) -> Any? in
            DispatchQueue.main.async {
                let alert : UIAlertController
                if let error = task.error {
                    NSLog("Error while uploading: %@", error.localizedDescription)
                    alert = UIAlertController.init(title: "Upload Error", message: error.localizedDescription, preferredStyle: .alert)
                }
                else if let metadata = task.result {
                    if (metadata.nbLocations + metadata.nbTmdSequences == 0) {
                        NSLog("Nothing to upload")
                        alert = UIAlertController.init(title: "Nothing to upload", message: nil, preferredStyle: .alert)
                    }
                    else {
                        alert = UIAlertController.init(title: "Upload success", message: nil, preferredStyle: .alert)
                        NSLog("Successfully uploading: %@", metadata.description())
                    }
                }
                else {
                    alert = UIAlertController.init(title: "Upload Error", message: "No metadata was returned", preferredStyle: .alert)
                }
                alert.addAction(UIAlertAction.init(title: "OK", style: .default, handler: nil))
                self.present(alert, animated: true, completion: nil)
            }
            return nil;
        }
    }
    
    @IBAction func refreshData(sender: UIBarButtonItem) {
        NSLog("Refresh")
        self.refreshControl.beginRefreshing()
        updateViewForCurrentDate()
        self.refreshControl.endRefreshing()
    }
    
    // MARK: - View lifecycle
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.dateFormatter.dateStyle = DateFormatter.Style.medium
        self.dateFormatter.timeStyle = DateFormatter.Style.none
        
        self.tableview.delegate = self
        self.tableview.dataSource = self
        
        NSLog(TMD.isOn() ? "TMD is ON" : "TMD is OFF")
        TMD.setDelegate(self)

        self.tmdSwitch.setOn(!TMD.isOff(), animated: true)
        if (TMD.isOn()){ // TMD is already running, update the UI accordingly
            self.didStart()
        }
        // Add Refresh Control to Table View
        if #available(iOS 10.0, *) {
            self.tableview.refreshControl = refreshControl
        } else {
            self.tableview.addSubview(refreshControl)
        }
        // Configure Refresh Control
        self.refreshControl.addTarget(self, action: #selector(refreshTableData(_:)), for: .valueChanged)
        dateButton.setTitle(dateFormatter.string(from: self.currentDate), for: .normal)

        if (TMD.isInitialized()){
            updateViewForCurrentDate()
        }
        else {
            let appDelegate = UIApplication.shared.delegate as! AppDelegate
            NotificationCenter.default.addObserver(self, selector: #selector(self.didInitTMD(notification:)), name: appDelegate.didInitializeTMD, object: nil)
        }
    }
    
    @objc func didInitTMD(notification: Notification){
        NSLog("didInitTMD")
        updateViewForCurrentDate()
    }
    
    // MARK: -
    
    func secondsToString(seconds: Double) -> String {
        
        if (seconds.isNaN) {
            return "Nan"
        }
        let isNegative = seconds < 0;
        
        let s = Int(seconds.rounded()) % 60;
        var m = Int(seconds.rounded()) / 60;
        let h = m / 60;
        m = m % 60;
        if (h != 0) {
            return String.init(format: "%@%dh%02dm%02ds", isNegative ? "-" : "", h, m, s);
        } else if (m != 0) {
            return String.init(format: "%@%dm%02ds", isNegative ? "-" : "", m, s);
        } else {
            return String.init(format: "%@%ds", isNegative ? "-" : "", s);
        }
    }
    
    // MARK: - TableView
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.activities.count;
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "ModalityCell", for: indexPath)
        let activity = self.activities[indexPath.row]
        let dateFormatterGet = DateFormatter()
        dateFormatterGet.dateFormat = "HH:mm"
        let ts = Double(activity.timestampStart) / 1000.0
        let date = dateFormatterGet.string(from: Date(timeIntervalSince1970: TimeInterval(ts)))
        cell.textLabel?.text = String(format: "%@ (%@) - %@",
                                      date,
                                      secondsToString(seconds: activity.duration()),
                                      String(activity.activity().split(separator: "/").last ?? "n.a.").uppercased())
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        tableView.deselectRow(at: indexPath, animated: true)
        if let cell = tableView.cellForRow(at: indexPath) as? PickerTableViewCell {
            cell.delegate = self
            cell.dataSource = self
            if !cell.isFirstResponder {
                _ = cell.becomeFirstResponder()
            }
        }
    }
    
    // MARK: - ActivityPicker
    
    @objc private func refreshTableData(_ sender: Any) {
        updateViewForCurrentDate()
        self.refreshControl.endRefreshing()
    }
    
    func updateSwitchState(_ enable:Bool) {
        if (enable && !self.tmdSwitch.isOn) {
            self.tmdSwitch.setOn(true, animated: true)
        }
        else if (!enable && self.tmdSwitch.isOn) {
            self.tmdSwitch.setOn(false, animated: true)
            self.tableview.reloadData()
        }
    }
    
    func updateViewForCurrentDate() {
        if (TMD.isInitialized() == false) {
            return
        }
        var cachedActivities: [TMDActivity] = [];
        TMDCloudApi.fetchDataFromCache(self.currentDate, minutesOffset: 0.0).continueOnSuccessWith { (cacheTask) -> Any? in
            NSLog("Fetched cached activities")
            if let arr = cacheTask.result {
                cachedActivities = (arr as! [TMDActivity])
            }
            return cacheTask;
            }.continueOnSuccessWith { (task) -> Any? in
                TMDCloudApi.fetchData(self.currentDate, minutesOffset: 0.0).continueWith { (task) -> Any? in
                    DispatchQueue.main.async{
                        self.activities.removeAll()
                        if let arr = task.result {
                            for activity in (arr as! [TMDActivity]) {
                                self.activities.append(activity)
                            }
                        }
                        else if task.error != nil {
                            for activity in cachedActivities {
                                self.activities.append(activity)
                            }
                        }
                        
                        NSLog("We got %d activities for date: %@", self.activities.count,
                              self.dateFormatter.string(from: self.currentDate))
                        self.tableview.reloadData()
                    }
                    return task;
                }
        }
        
    }
    
    @objc func updateTmdStatusLabel() {
        if TMD.isOff() {
            tmdStatusLabel.text = "TMD is off"
        }
        else if TMD.isIdle() {
            tmdStatusLabel.text = "TMD is idle"
        }
        else if TMD.isRunning() {
            tmdStatusLabel.text = String(format: "TMD is running for %@",
                                         secondsToString(seconds: TMD.getRunningTime()))
        }
    }
    
    func didStart() {
        NSLog("TMD service started")
        updateSwitchState(true)
        if timer.isValid {
            timer.invalidate();
        }
        timer = Timer.scheduledTimer(timeInterval: 1,
                                     target: self,
                                     selector: #selector(self.updateTmdStatusLabel),
                                     userInfo: nil, repeats: true)
    }
    
    func didStop() {
        NSLog("TMD service stopped")
        if timer.isValid {
            timer.invalidate();
        }
        updateSwitchState(false)
        updateTmdStatusLabel()
    }
    
    func didNotStartWithError(_ error: Error!) {
        NSLog("TMD service could not start with error %@", error.localizedDescription)
        updateSwitchState(false)
        updateTmdStatusLabel()
    }
    
    func didStopWithError(_ error: Error!) {
        NSLog("TMD service stopped with error %@", error.localizedDescription)
        updateSwitchState(false)
        updateTmdStatusLabel()
    }
    
}

// MARK: - PickerTableCellDataSource
extension ViewController: PickerTableCellDataSource {
    
    public func numberOfComponents(in pickerView: UIPickerView, forCell cell: PickerTableViewCell) -> Int {
        return 1
    }
    
    public func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int, forCell cell: PickerTableViewCell) -> Int {
        return pickerData.count
    }
    
}

// MARK: - PickerTableCellDelegate
extension ViewController: PickerTableCellDelegate {
    
    func onPickerOpen(_ cell: PickerTableViewCell) {}
    
    func onPickerClose(_ cell: PickerTableViewCell) {}
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int, forCell cell: PickerTableViewCell) -> String? {
        return String(pickerData[row].split(separator: "/").last ?? "unknown").uppercased()
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int, forCell cell: PickerTableViewCell) {
        let cellRow = self.tableview.indexPath(for: cell)?.row ?? -1
        NSLog("Picked %@", String(pickerData[row].split(separator: "/").last ?? "unknown").uppercased())
        TMDCloudApi.correctActivity(activities[cellRow], withLabel: pickerData[row]).continueOnSuccessWith { (task) -> Any? in
            DispatchQueue.main.async{
                if let activity = task.result {
                    NSLog("Activity %@", activity.activity())
                    self.activities[cellRow] = activity
                    self.tableview.reloadData()
                }
            }
            return task
        }
        self.view.endEditing(true)
    }
}

// MARK: - DatePicker Delegates
extension ViewController: DatePickerDelegate {
    func didPickDate(date: Date) {
        updateDate(date)
    }
}
extension ViewController: UIPopoverPresentationControllerDelegate{
    func adaptivePresentationStyle(for controller: UIPresentationController) -> UIModalPresentationStyle {
        return UIModalPresentationStyle.none
    }
}

