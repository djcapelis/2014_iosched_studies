//
//  MainViewController.h
//  test
//
//  Created by D J Capelis on 1/9/14.
//  Copyright (c) 2014 D J Capelis. All rights reserved.
//

#import "FlipsideViewController.h"

#import <CoreData/CoreData.h>

@interface MainViewController : UIViewController <FlipsideViewControllerDelegate>

@property (strong, nonatomic) NSManagedObjectContext *managedObjectContext;

@end
