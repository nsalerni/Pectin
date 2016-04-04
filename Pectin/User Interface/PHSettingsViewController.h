//
//  PHSettingsViewController.h
//  Pectin
//
//  Created by Nick Salerni on 2016-03-01.
//  Copyright © 2016 Nick Salerni. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PHMediaConfiguration;

@interface PHSettingsViewController : UITableViewController

@property (nonatomic, strong) PHMediaConfiguration *settings;

@end
