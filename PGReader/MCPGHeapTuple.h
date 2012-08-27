//
//  MCPGHeapTuple.h
//  PGReader
//
//  Created by Thomas Bartelmess on 12-08-26.
//  Copyright (c) 2012 marketcircle. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef uint16 OffsetNumber;

/*
 * BlockId:
 *
 * this is a storage type for BlockNumber.	in other words, this type
 * is used for on-disk structures (e.g., in HeapTupleData) whereas
 * BlockNumber is the type on which calculations are performed (e.g.,
 * in access method code).
 *
 * there doesn't appear to be any reason to have separate types except
 * for the fact that BlockIds can be SHORTALIGN'd (and therefore any
 * structures that contains them, such as ItemPointerData, can also be
 * SHORTALIGN'd).  this is an important consideration for reducing the
 * space requirements of the line pointer (ItemIdData) array on each
 * page and the header of each heap or index tuple, so it doesn't seem
 * wise to change this without good reason.
 */
typedef struct BlockIdData
{
	uint16		bi_hi;
	uint16		bi_lo;
} BlockIdData;

/*
 * ItemPointer:
 *
 * This is a pointer to an item within a disk page of a known file
 * (for example, a cross-link from an index to its parent table).
 * blkid tells us which block, posid tells us which entry in the linp
 * (ItemIdData) array we want.
 *
 * Note: because there is an item pointer in each tuple header and index
 * tuple header on disk, it's very important not to waste space with
 * structure padding bytes.  The struct is designed to be six bytes long
 * (it contains three int16 fields) but a few compilers will pad it to
 * eight bytes unless coerced.	We apply appropriate persuasion where
 * possible, and to cope with unpersuadable compilers, we try to use
 * "SizeOfIptrData" rather than "sizeof(ItemPointerData)" when computing
 * on-disk sizes.
 */
typedef struct ItemPointerData
{
	BlockIdData ip_blkid;
	OffsetNumber ip_posid;
} ItemPointerData;


typedef uint32 TransactionId;
typedef uint32 CommandId;

@interface MCPGHeapTuple : NSObject
- (id)initWithData:(NSData *)data;

@property (nonatomic, readwrite) TransactionId t_xmin; //insert XID stamp
@property (nonatomic, readwrite) CommandId t_cmin; //insert CID stamp
@property (nonatomic, readwrite) TransactionId t_xmax; //delete XID stamp
@property (nonatomic, readwrite) CommandId t_cmax; //delete CID stamp (overlays with t_xvac)
@property (nonatomic, readwrite) TransactionId t_xvac; // XID for VACUUM operation moving a row version
@property (nonatomic, readwrite) ItemPointerData t_ctid;
@property (nonatomic, readwrite) int16_t t_natts;
@property (nonatomic, readwrite) uint16 t_infomask;
@property (nonatomic, readwrite) uint8 t_hoff;
@end
