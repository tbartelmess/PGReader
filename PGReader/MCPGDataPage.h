//
//  MCPGDataPage.h
//  PGReader
//
//  Created by Thomas Bartelmess on 12-08-26.
//  Copyright (c) 2012 marketcircle. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 * location (byte offset) within a page.
 *
 * note that this is actually limited to 2^15 because we have limited
 * ItemIdData.lp_off and ItemIdData.lp_len to 15 bits.
 */
typedef uint16 LocationIndex;

/*
 * An item pointer (also called line pointer) on a buffer page
 *
 * In some cases an item pointer is "in use" but does not have any associated
 * storage on the page.  By convention, lp_len == 0 in every item pointer
 * that does not have storage, independently of its lp_flags state.
 */
typedef struct ItemIdData
{
	unsigned	lp_off:15,		/* offset to tuple (from start of page) */
lp_flags:2,		/* state of item pointer, see below */
lp_len:15;		/* byte length of tuple */
} ItemIdData;




@interface MCPGDataPage : NSObject

// Header
@property (nonatomic, readwrite) uint32 pd_lsn_xlogid; /* log file #, 0 based */
@property (nonatomic, readwrite) uint32 pd_lsn_recoff; /* byte offset of location in log file */
@property (nonatomic, readwrite) uint16 pd_tli;		   /* least significant bits of the TimeLineID
                             * containing the LSN */
@property (nonatomic, readwrite) uint16 pd_flags;      /* flag bits, see below */
@property (nonatomic, readwrite) LocationIndex pd_lower;      /* offset to start of free space */
@property (nonatomic, readwrite) LocationIndex pd_upper;      /* offset to end of free space */
@property (nonatomic, readwrite) LocationIndex pd_special;    /* offset to start of special space */
@property (nonatomic, readwrite) uint16 pd_pagesize_version;
@property (nonatomic, readwrite) uint32 transactionID;       /* oldest prunable XID, or zero if none */

/*
 * TimeLineID (TLI) - identifies different database histories to prevent
 * confusion after restoring a prior state of a database installation.
 * TLI does not change in a normal stop/restart of the database (including
 * crash-and-recover cases); but we must assign a new TLI after doing
 * a recovery to a prior state, a/k/a point-in-time recovery.  This makes
 * the new WAL logfile sequence we generate distinguishable from the
 * sequence that was generated in the previous incarnation.
 */

@property (nonatomic, readwrite) uint32 timeLineID;

/*
 * location (byte offset) within a page.
 *
 * note that this is actually limited to 2^15 because we have limited
 * ItemIdData.lp_off and ItemIdData.lp_len to 15 bits (see itemid.h).
 */
@property (nonatomic, readwrite) uint16 locationIndex;

- (id)initWithData:(NSData *)data;
@end
