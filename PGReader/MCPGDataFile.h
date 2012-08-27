//
//  MCPGDataFile.h
//  PGReader
//
//  Created by Thomas Bartelmess on 12-08-26.
//  Copyright (c) 2012 marketcircle. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MCPGDataFile : NSObject
- (id)initWithData:(NSData *)data;
@property (nonatomic, strong) NSArray * pages;
@end
