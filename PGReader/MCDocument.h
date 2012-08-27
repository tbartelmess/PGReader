//
//  MCDocument.h
//  PGReader
//
//  Created by Thomas Bartelmess on 12-08-26.
//  Copyright (c) 2012 marketcircle. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@class MCPGDataFile;
@interface MCDocument : NSDocument
@property (nonatomic, strong) MCPGDataFile * dataFile;
@end
