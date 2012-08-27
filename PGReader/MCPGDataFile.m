//
//  MCPGDataFile.m
//  PGReader
//
//  Created by Thomas Bartelmess on 12-08-26.
//  Copyright (c) 2012 marketcircle. All rights reserved.
//

#import "MCPGDataFile.h"
#import "MCPGDataPage.h"
@interface MCPGDataFile()

@end

@implementation MCPGDataFile
- (id)initWithData:(NSData *)data {
    self = [self init];
    if (self) {
        [self readPages:data];
    }
    return self;
}

- (void)readPages:(NSData *)data {
    int numberOfPages = [data length] / (8 * 1024);
    NSAssert([data length] % (8 * 1024) == 0, @"Invalid data file");
    NSLog(@"File contains %d pages", numberOfPages);
    
    NSMutableArray * pages = [NSMutableArray array];
    
    int pagesRead = 0;
    
    for (pagesRead = 0; pagesRead < numberOfPages; pagesRead ++) {
        NSData * pageData = [data subdataWithRange:NSMakeRange(pagesRead * 8 * 1024, 8 *1024)];
        [pages addObject:[[MCPGDataPage alloc] initWithData:pageData]];
        
    }
    self.pages = pages;
}
@end
