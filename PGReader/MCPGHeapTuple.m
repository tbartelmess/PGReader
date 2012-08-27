//
//  MCPGHeapTuple.m
//  PGReader
//
//  Created by Thomas Bartelmess on 12-08-26.
//  Copyright (c) 2012 marketcircle. All rights reserved.
//

#import "MCPGHeapTuple.h"
@interface MCPGHeapTuple()
- (void)readTuple:(NSData *)data;
@end
@implementation MCPGHeapTuple
- (id)initWithData:(NSData *)data {
    self = [self init];
    if (self) {
        [self readTuple:data];
    }
    return self;
}
- (void)readTuple:(NSData *)data {
    NSUInteger currentPos = 0;
    [data getBytes:&_t_xmin range:NSMakeRange(currentPos,sizeof(TransactionId))];
    currentPos += sizeof(TransactionId);
    [data getBytes:&_t_cmin range:NSMakeRange(currentPos,sizeof(CommandId))];
    currentPos += sizeof(CommandId);
    [data getBytes:&_t_xmax range:NSMakeRange(currentPos,sizeof(TransactionId))];
    currentPos += sizeof(TransactionId);
    [data getBytes:&_t_cmax range:NSMakeRange(currentPos,sizeof(CommandId))];
    currentPos += sizeof(CommandId);
    [data getBytes:&_t_ctid range:NSMakeRange(currentPos,sizeof(ItemPointerData))];
    currentPos += sizeof(ItemPointerData);
    [data getBytes:&_t_natts range:NSMakeRange(currentPos,sizeof(int16_t))];
    currentPos += sizeof(int16_t);
    [data getBytes:&_t_infomask range:NSMakeRange(currentPos,sizeof(uint16))];
    currentPos += sizeof(uint16);
    [data getBytes:&_t_hoff range:NSMakeRange(currentPos,sizeof(uint8))];
    currentPos += sizeof(uint8);
}
@end
