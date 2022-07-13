//
//  DatePickerController.swift
//  TMD Sample Project
//
//  Created by Kyrill Cousson on 16/08/2019.
//  Copyright © 2019 moprim. All rights reserved.
//

import UIKit

class DatePickerController: UIViewController {
    
    @IBOutlet weak var datePicker: UIDatePicker!
    
    var date:Date?
    weak var delegate:DatePickerDelegate?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        if let date = self.date {
            datePicker.date = date
        }
        datePicker.maximumDate = Date()
    }
    @IBAction func didPickDate(_ sender: Any) {
        self.date = datePicker.date
        delegate?.didPickDate(date: self.date!)
    }
    
}

protocol DatePickerDelegate: AnyObject {
    func didPickDate(date:Date)
}
