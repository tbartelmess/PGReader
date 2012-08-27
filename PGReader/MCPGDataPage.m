//
//  MCPGDataPage.m
//  PGReader
//
//  Created by Thomas Bartelmess on 12-08-26.
//  Copyright (c) 2012 marketcircle. All rights reserved.
//

#import "MCPGDataPage.h"
#import "MCPGHeapTuple.h"
@implementation MCPGDataPage
- (id)initWithData:(NSData *)data {
    self = [self init];
    if (self) {
        
        // Reading the header
        
        NSUInteger currentPos = 0;
        [data getBytes:&_pd_lsn_xlogid range:NSMakeRange(currentPos,sizeof(uint32))];
        currentPos += sizeof(uint32);
        [data getBytes:&_pd_lsn_xlogid range:NSMakeRange(currentPos,sizeof(uint32))];
        currentPos += sizeof(uint32);
        [data getBytes:&_timeLineID range:NSMakeRange(currentPos,sizeof(uint32))];
        currentPos += sizeof(uint32);
        [data getBytes:&_pd_tli range:NSMakeRange(currentPos, sizeof(uint16))];
        currentPos += sizeof(uint16);
        [data getBytes:&_pd_flags range:NSMakeRange(currentPos, sizeof(uint16))];
        currentPos += sizeof(uint16);
        [data getBytes:&_pd_lower range:NSMakeRange(currentPos, sizeof(LocationIndex))];
        currentPos += sizeof(LocationIndex);
        [data getBytes:&_pd_upper range:NSMakeRange(currentPos, sizeof(LocationIndex))];
        currentPos += sizeof(LocationIndex);
        [data getBytes:&_pd_special range:NSMakeRange(currentPos, sizeof(LocationIndex))];
        currentPos += sizeof(LocationIndex);
        [data getBytes:&_pd_pagesize_version range:NSMakeRange(currentPos, sizeof(uint16))];
        currentPos += sizeof(uint16);
        [data getBytes:&_transactionID range:NSMakeRange(currentPos, sizeof(LocationIndex))];
        currentPos += sizeof(uint32);
        NSLog(@"%u", self.transactionID);
        
        // Reading item data id's
        ItemIdData * next4Bytes = malloc(sizeof(ItemIdData));
        
        [data getBytes:next4Bytes range:NSMakeRange(currentPos, sizeof(ItemIdData))];
        
       
        while (next4Bytes->lp_len != 0) {
             NSLog (@"start: %u length: %u bytes", next4Bytes->lp_off, next4Bytes->lp_len);
            MCPGHeapTuple * heapTuple = [[MCPGHeapTuple alloc] initWithData:[data subdataWithRange:NSMakeRange(next4Bytes->lp_off, next4Bytes->lp_len)]];
            NSData * heapData = [data subdataWithRange:NSMakeRange(next4Bytes->lp_off, next4Bytes->lp_len)];
            NSLog(@"%@", [[NSString alloc] initWithData:heapData encoding:NSASCIIStringEncoding]);
            
            [data getBytes:next4Bytes range:NSMakeRange(currentPos, sizeof(ItemIdData))];
            currentPos += sizeof(ItemIdData);
            
        }
        
    }
    return self;
}

- (NSNumber *) ui_transactionID {
    return [NSNumber numberWithUnsignedInt:self.transactionID];
}
@end
