#if 0
static unsigned long long      TimeOfStart;
static unsigned long long      BasePts;
static unsigned long long      LastPts;
#endif

/************************************************************************
Copyright (C) 2006 STMicroelectronics. All Rights Reserved.

This file is part of the Player2 Library.

Player2 is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License version 2 as published by the
Free Software Foundation.

Player2 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with player2; see the file COPYING.  If not, write to the Free Software
Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

The Player2 Library may alternatively be licensed under a proprietary
license from ST.

Source file name : collator_pes.cpp
Author :           Nick

Implementation of the pes collator class for player 2.


Date        Modification                                    Name
----        ------------                                    --------
20-Nov-06   Created                                         Nick

************************************************************************/

// /////////////////////////////////////////////////////////////////////
//
//      Include any component headers

#include "collator_pes.h"

// /////////////////////////////////////////////////////////////////////////
//
// Locally defined constants
//
// /////////////////////////////////////////////////////////////////////////
//
// Locally defined structures
//

// /////////////////////////////////////////////////////////////////////////
//
//      The Constructor function
//

Collator_Pes_c::Collator_Pes_c( void )
{
    if( InitializationStatus != CollatorNoError )
	return;

#if 0
report( severity_info, "New Collator\n" );
TimeOfStart   = INVALID_TIME;
BasePts       = INVALID_TIME;
LastPts       = INVALID_TIME;
#endif
    Reset();
}

// /////////////////////////////////////////////////////////////////////////
//
//      The Destructor function
//

Collator_Pes_c::~Collator_Pes_c(        void )
{
    Halt();
    Reset();
}


// /////////////////////////////////////////////////////////////////////////
//
//      The Halt function, give up access to any registered resources
//

CollatorStatus_t   Collator_Pes_c::Halt(        void )
{
    StoredPesHeader     = NULL;
    StoredPaddingHeader = NULL;
    RemainingData       = NULL;

    return Collator_Base_c::Halt();
}


// /////////////////////////////////////////////////////////////////////////
//
//      The Reset function release any resources, and reset all variable
//

CollatorStatus_t   Collator_Pes_c::Reset(       void )
{

    SeekingPesHeader            = true;
    GotPartialHeader		= false;	// New style most video
    GotPartialZeroHeader        = false;	// Old style used by divx only
    GotPartialPesHeader         = false;
    GotPartialPaddingHeader     = false;
    Skipping                    = 0;
    RemainingLength             = 0;
    PlaybackTimeValid           = false;
    DecodeTimeValid             = false;
    UseSpanningTime             = false;
    SpanningPlaybackTimeValid   = false;
    SpanningDecodeTimeValid     = false;

    PesPacketLength             = 0;

    return Collator_Base_c::Reset();
}


// /////////////////////////////////////////////////////////////////////////
//
//      The discard all accumulated data function
//

CollatorStatus_t   Collator_Pes_c::DiscardAccumulatedData(      void )
{
CollatorStatus_t        Status;

//

    AssertComponentState( "Collator_Pes_c::DiscardAccumulatedData", ComponentRunning );

//

    Status                      = Collator_Base_c::DiscardAccumulatedData();
    if( Status != CodecNoError )
	return Status;

    SeekingPesHeader            = true;
    GotPartialHeader		= false;	// New style most video
    GotPartialZeroHeader        = false;	// Old style used by divx only
    GotPartialPesHeader         = false;
    GotPartialPaddingHeader     = false;
    Skipping                    = 0;
    UseSpanningTime             = false;
    SpanningPlaybackTimeValid   = false;
    SpanningDecodeTimeValid     = false;

    return Status;
}


// /////////////////////////////////////////////////////////////////////////
//
//      The discard all accumulated data function
//

CollatorStatus_t   Collator_Pes_c::InputJump(   bool                      SurplusDataInjected,
						bool                      ContinuousReverseJump )
{
CollatorStatus_t        Status;

//

    AssertComponentState( "Collator_Pes_c::InputJump", ComponentRunning );

//

    Status                      = Collator_Base_c::InputJump( SurplusDataInjected, ContinuousReverseJump );
    if( Status != CodecNoError )
	return Status;

    PlaybackTimeValid           = false;
    DecodeTimeValid             = false;
    UseSpanningTime             = false;
    SpanningPlaybackTimeValid   = false;
    SpanningDecodeTimeValid     = false;

    SeekingPesHeader		= true;

    return Status;
}

static inline
unsigned char *FindStartCode(const unsigned char *d, int len)
{
	union {
		unsigned int n;
		const unsigned char *c;
		int *i;
	} p, end, alend;

	int n;

	p.c = d;
	end.c = p.c + (len-3);
	alend.n = end.n & ~3;

	/* check any unaligned values at the start of the block */
	while (p.n & 3 && p.n < end.n) {
		if (0 == p.c[0] && 0 == p.c[1] && 1 == p.c[2]) {
			return const_cast<unsigned char *>(p.c);
		}

		p.c++;
	}

	while (p.n < end.n) {
		/* perform an accelerated scan until we find what we are
		 * looking for or we are about to run off the end
		 */
#ifdef __SH4__
		asm (
		       "mov.l   @%[p]+, %[n]\n"
		"1:\n"
		"       cmp/str %[n], %[zero]\n"
		"       bt/s    2f\n"
		"       cmp/hi  %[p], %[alend]\n"
		"       bt/s    1b\n"
		"       mov.l   @%[p]+, %[n]\n"
		"2:"
			: [p] "+r" (p.n), [n] "=&r" (n)
			: [alend] "r" (alend.n), [zero] "r" (0));

		p.i--;
#else
		while (p.n < alend.n) {
			n = *p.i++;
			if ((n - 0x01010101) & ~n & 0x80808080) {
				p.i--;
				break;
			}
		}
#endif

		/* we have (up to) four possible candidates to be
		 * tested before resuming an accelerated scan.
		 */
		for (int i=0; i<4 && p.n < end.n; i++) {
			if (0 == p.c[0] && 0 == p.c[1] && 1 == p.c[2]) {
				return const_cast<unsigned char *>(p.c);
			}

			p.c++;
		}
	}

	return 0;
}

// /////////////////////////////////////////////////////////////////////////
//
//      Protected - Find the next start code (apart from any one at offset 0)
//

CollatorStatus_t   Collator_Pes_c::FindNextStartCode(
					unsigned int             *CodeOffset )
{
unsigned int    i;
unsigned char   IgnoreLower;
unsigned char   IgnoreUpper;
unsigned char  *StartCode;
int             DataLeft;
    //
    // If less than 4 bytes we do not bother
    //

    if( RemainingLength < 4 )
	return CollatorError;

    UseSpanningTime             = false;
    SpanningPlaybackTimeValid   = false;
    SpanningDecodeTimeValid     = false;

    IgnoreLower                 = Configuration.IgnoreCodesRangeStart;
    IgnoreUpper                 = Configuration.IgnoreCodesRangeEnd;

#if WYPLAY_OPTIMIZE
    StartCode = &RemainingData[0];
    DataLeft  = RemainingLength;

    do
    {
      unsigned char *NextCode = FindStartCode(StartCode, DataLeft);
      unsigned int   Offset   = NextCode - RemainingData;

      if (!NextCode)
	return CollatorError;

      if (!inrange(NextCode[3], IgnoreLower, IgnoreUpper))
      {
	*CodeOffset = Offset;
	return CollatorNoError;
      }

      DataLeft  = ((int)RemainingLength) - (Offset + 1);
      StartCode = &NextCode[1];

    } while (DataLeft > 3);

#else
    //
    // Check in body
    //

    for( i=2; i<(RemainingLength-3); i+=3 )
	if( RemainingData[i] <= 1 )
	{
	    if( RemainingData[i-1] == 0 )
	    {
		if( (RemainingData[i-2] == 0) && (RemainingData[i] == 0x1) )
		{
		    if( inrange(RemainingData[i+1], IgnoreLower, IgnoreUpper) )
			continue;

		    *CodeOffset         = i-2;
		    return CollatorNoError;
		}
		else if( (RemainingData[i+1] == 0x1) && (RemainingData[i] == 0) )
		{
		    if( inrange(RemainingData[i+2], IgnoreLower, IgnoreUpper) )
			continue;

		    *CodeOffset         = i-1;
		    return CollatorNoError;
		}
	    }
	    if( (RemainingData[i+1] == 0) && (RemainingData[i+2] == 0x1) && (RemainingData[i] == 0) )
	    {
		if( inrange(RemainingData[i+3], IgnoreLower, IgnoreUpper) )
		    continue;

		*CodeOffset             = i;
		return CollatorNoError;
	    }
	}

    //
    // Check trailing conditions
    //

    if( RemainingData[RemainingLength-4] == 0 )
    {
	if( (RemainingData[RemainingLength-3] == 0) && (RemainingData[RemainingLength-2] == 1) )
	{
	    if( !inrange(RemainingData[RemainingLength-1], IgnoreLower, IgnoreUpper) )
	    {
		*CodeOffset                     = RemainingLength-4;
		return CollatorNoError;
	    }
	}
	else if( (RemainingLength >= 5) && (RemainingData[RemainingLength-5] == 0) && (RemainingData[RemainingLength-3] == 1) )
	{
	    if( !inrange(RemainingData[RemainingLength-2], IgnoreLower, IgnoreUpper) )
	    {
		*CodeOffset                     = RemainingLength-5;
		return CollatorNoError;
	    }
	}
    }
#endif
    //
    // No matches
    //

    return CollatorError;
}


// /////////////////////////////////////////////////////////////////////////
//
//      Protected - Find the next start code (apart from any one at offset 0)
//

#define MarkerBits( n, v ) 	if( Bits.Get((n)) != (v) )                                                                      \
                                {                                                                                               \
                                    report( severity_error, "Collator_Pes_c::ReadPesHeader - Invalid marker bits value %d.\n", __LINE__ );   \
				    report_dump_hex( severity_info, StoredPesHeader, 32, 16, NULL ); \
				    PlaybackTimeValid           = SpanningPlaybackTimeValid;					\
				    PlaybackTime                = SpanningPlaybackTime;						\
				    DecodeTimeValid             = SpanningDecodeTimeValid;					\
				    DecodeTime                  = SpanningDecodeTime;     					\
				    SpanningPlaybackTimeValid	= false;							\
				    SpanningDecodeTimeValid	= false;							\
                                    return CollatorError;                                                 		        \
                                }

#define MarkerBit( v ) 		MarkerBits( 1, v )
				

CollatorStatus_t   Collator_Pes_c::ReadPesHeader(               void )
{
unsigned int    Flags;

    //
    // Here we save the current pts state for use only in any
    // picture start code that spans this pes packet header.
    //

    SpanningPlaybackTimeValid   = PlaybackTimeValid;
    SpanningPlaybackTime        = PlaybackTime;
    SpanningDecodeTimeValid     = DecodeTimeValid;
    SpanningDecodeTime          = DecodeTime;
    UseSpanningTime             = true;

    // We have 'consumed' the old values by transfering them to the spanning values.
    PlaybackTimeValid           = false;
    DecodeTimeValid             = false;

    //
    // Read the length of the payload (which for video packets within transport stream may be zero)
    //
    PesPacketLength = (StoredPesHeader[4] << 8) + StoredPesHeader[5];
    if( PesPacketLength )
    {
	PesPayloadLength = PesPacketLength - StoredPesHeader[8] - 3 - Configuration.ExtendedHeaderLength;
    }
    else
    {
	PesPayloadLength = 0;
    }
    COLLATOR_DEBUG("PesPacketLength %d; PesPayloadLength %d\n", PesPacketLength, PesPayloadLength);

    //
    // Bits 0xc0 of byte 6 determine PES or system stream, for PES they are always 0x80,
    // for system stream they are never 0x80 (may be a number of other values).
    //

    if( (StoredPesHeader[6] & 0xc0) == 0x80 )
    {
	Bits.SetPointer( StoredPesHeader + 9 );         // Set bits pointer ready to process optional fields

	//
	// Check not scrambled
	//

	if( (StoredPesHeader[6] & 0x20) == 0x20 )
	{
	    report( severity_error, "Collator_Pes_c::ReadPesHeader - Packet scrambled.\n" );
	    PlaybackTimeValid           = SpanningPlaybackTimeValid;				// Pop the spanning values back into the main ones
	    PlaybackTime                = SpanningPlaybackTime;
	    DecodeTimeValid             = SpanningDecodeTimeValid;
	    DecodeTime                  = SpanningDecodeTime;
	    SpanningPlaybackTimeValid	= false;
	    SpanningDecodeTimeValid	= false;
	    return CollatorError;
	}

	//
	// Commence header parsing, moved initialization of bits class here,
	// because code has been added to parse the other header fields, and
	// this assumes that the bits pointer has been initialized.
	//

	if( (StoredPesHeader[7] & 0x80) == 0x80 )
	{
	    //
	    // Read the PTS
	    //

#if 0
	    MarkerBits( 4, (StoredPesHeader[7] >> 6) );
#else
	    // Older version of user software give invalid value for these 4 bits so we don't check them
	    Bits.FlushUnseen( 4 );
#endif
	    PlaybackTime         = (unsigned long long)(Bits.Get( 3 )) << 30;
	    MarkerBit( 1 );
	    PlaybackTime        |= Bits.Get( 15 ) << 15;
	    MarkerBit( 1 );
	    PlaybackTime        |= Bits.Get( 15 );
	    MarkerBit( 1 );
	    PlaybackTimeValid    = true;
#if 0
{
unsigned long long Now;
unsigned int MilliSeconds;
bool            M0;
long long       T0;
bool            M1;
long long       T1;

    if( BasePts == INVALID_TIME )
    {
	BasePts         = PlaybackTime;
	LastPts         = PlaybackTime;
    }

    Now                 = OS_GetTimeInMicroSeconds();
    if( TimeOfStart == INVALID_TIME )
	TimeOfStart     = Now;

    MilliSeconds        = (unsigned int)((Now - TimeOfStart) / 1000);

    M0                  = PlaybackTime < BasePts;
    T0                  = M0 ? (BasePts - PlaybackTime) : (PlaybackTime - BasePts);
    M1                  = PlaybackTime < LastPts;
    T1                  = M0 ? (LastPts - PlaybackTime) : (PlaybackTime - LastPts);

report( severity_info, "Collator PTS %d - %2d:%02d:%02d.%03d - %016llx - %c%lld - %c%lld\n", 
	Configuration.GenerateStartCodeList,
	(MilliSeconds / 3600000),
	((MilliSeconds / 60000) % 60), 
	((MilliSeconds / 1000) % 60), 
	(MilliSeconds % 1000), 
	PlaybackTime,
	(M0 ? '-' : ' '),
	((T0 * 300) / 27),
	(M1 ? '-' : ' '),
	((T1 * 300) / 27) );

    LastPts             = PlaybackTime;
}
#endif
	}
	if( (StoredPesHeader[7] & 0xC0) == 0xC0 )
	{
	    //
	    // Read the DTS
	    //

#if __TDT__
	    // It seems that for BibleTV these 4 bits are set incorecctly
	    // So lets ignore it like above for PTS
	    Bits.FlushUnseen( 4 );
#else
	    MarkerBits( 4, 1 );
#endif
	    DecodeTime           = (unsigned long long)(Bits.Get( 3 )) << 30;
	    MarkerBit( 1 );
	    DecodeTime          |= Bits.Get( 15 ) << 15;
	    MarkerBit( 1 );
	    DecodeTime          |= Bits.Get( 15 );
	    MarkerBit( 1 );

	    DecodeTimeValid      = true;
	}
	else if( (StoredPesHeader[7] & 0xC0) == 0x40 )
	{
	    report( severity_error, "Collator_Pes_c::ReadPesHeader - Malformed pes header contains DTS without PTS.\n" );
	}
	// The following code aims at verifying if the Pes packet sub_stream_id is the one required by the collator...
	if (IS_PES_START_CODE_EXTENDED_STREAM_ID(StoredPesHeader[3]))
	{
	  // skip the escr data  if any
	  if ( (StoredPesHeader[7] & 0x20) == 0x20 )
	  {
	      Bits.FlushUnseen(48);
	  }

	  // skip the es_rate data if any
	  if ( (StoredPesHeader[7] & 0x10) == 0x10 )
	  {
	      Bits.FlushUnseen(24);
	  }

	  // skip the dsm trick mode data if any
	  if ( (StoredPesHeader[7] & 0x8U) == 0x8U )
	  {
	      Bits.FlushUnseen(8);
	  }

	  // skip the additional_copy_info data data if any
	  if ( (StoredPesHeader[7] & 0x4) == 0x4 )
	  {
	      Bits.FlushUnseen(8);
	  }

	  // skip the pes_crc data data if any
	  if ( (StoredPesHeader[7] & 0x2) == 0x2 )
	  {
	      Bits.FlushUnseen(16);
	  }

	  // handle the pes_extension
	  if ( (StoredPesHeader[7] & 0x1) == 0x1 )
	  {
	    int PesPrivateFlag = Bits.Get(1);
	    int PackHeaderFieldFlag = Bits.Get(1);
	    int PrgCounterFlag = Bits.Get(1);
	    int PstdFlag = Bits.Get(1);
	    Bits.FlushUnseen(3);
	    int PesExtensionFlag2 = Bits.Get(1);
	    Bits.FlushUnseen((PesPrivateFlag?128:0) + (PackHeaderFieldFlag?8:0) + (PrgCounterFlag?16:0) + (PstdFlag?16:0));

	    if (PesExtensionFlag2)
	    {
	      Bits.FlushUnseen(8);
	      int StreamIdExtFlag = Bits.Get(1);
	      if (!StreamIdExtFlag)
	      {
		int SubStreamId = Bits.Get(7);
		if ((SubStreamId & Configuration.SubStreamIdentifierMask) != Configuration.SubStreamIdentifierCode)
		{
		  COLLATOR_DEBUG("Rejected Pes packet of type extended_stream_id with SubStreamId: %x\n",SubStreamId);
		  // Get rid of this packet !
		  PlaybackTimeValid           = SpanningPlaybackTimeValid;				// Pop the spanning values back into the main ones
		  PlaybackTime                = SpanningPlaybackTime;
		  DecodeTimeValid             = SpanningDecodeTimeValid;
		  DecodeTime                  = SpanningDecodeTime;
		  SpanningPlaybackTimeValid	= false;
		  SpanningDecodeTimeValid	= false;
		  return (CollatorError);
		}
	      }
	    }
	  }
	}
    }

    //
    // Alternatively read a system stream
    //

    else
    {
	Bits.SetPointer( StoredPesHeader + 6 );
	while( Bits.Show(8) == 0xff )
	    Bits.Flush(8);

	if( Bits.Show(2) == 0x01 )
	{
	    Bits.Flush(2);
	    Bits.FlushUnseen(1);                // STD scale
	    Bits.FlushUnseen(13);               // STD buffer size
	}

	Flags   = Bits.Get(4);
	if( (Flags == 0x02) || (Flags == 0x03) )
	{
	    PlaybackTime         = (unsigned long long)(Bits.Get( 3 )) << 30;
	    Bits.FlushUnseen(1);
	    PlaybackTime        |= Bits.Get( 15 ) << 15;
	    Bits.FlushUnseen(1);
	    PlaybackTime        |= Bits.Get( 15 );
	    Bits.FlushUnseen(1);

	    PlaybackTimeValid    = true;
	}
	if( Flags == 0x03 )
	{
	    Bits.FlushUnseen(4);
	    DecodeTime           = (unsigned long long)(Bits.Get( 3 )) << 30;
	    Bits.FlushUnseen(1);
	    DecodeTime          |= Bits.Get( 15 ) << 15;
	    Bits.FlushUnseen(1);
	    DecodeTime          |= Bits.Get( 15 );
	    Bits.FlushUnseen(1);

	    DecodeTimeValid      = true;
	}
    }


//    if (PlaybackTimeValid)
//        report(severity_error,"Playbacktime = %lld\n",PlaybackTime);

    //
    // We either save it to be loaded at the next buffer, or if we 
    // have not started picture aquisition we use it immediately.
    //

    if( AccumulatedDataSize == 0 )
    {
	CodedFrameParameters->PlaybackTimeValid = PlaybackTimeValid;
	CodedFrameParameters->PlaybackTime      = PlaybackTime;
	PlaybackTimeValid                       = false;
	CodedFrameParameters->DecodeTimeValid   = DecodeTimeValid;
	CodedFrameParameters->DecodeTime        = DecodeTime;
	DecodeTimeValid                         = false;
    }

//

    return CollatorNoError;
}

