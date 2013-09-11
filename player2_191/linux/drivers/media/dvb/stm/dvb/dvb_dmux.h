/************************************************************************
Copyright (C) 2003 STMicroelectronics. All Rights Reserved.

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

Source file name : dvb_dmux.h - demux device definitions
Author :           Julian

Date        Modification                                    Name
----        ------------                                    --------
01-Nov-06   Created                                         Julian

************************************************************************/

#ifndef H_DVB_DEMUX
#define H_DVB_DEMUX

#include "dvbdev.h"
#include <dvb_demux.h>

#if 0
int DmxWrite   (struct dmx_demux*       Demux,
                const char*             Buffer,
                size_t                  Count);
#endif
int StartFeed  (struct dvb_demux_feed*  Feed);
int StopFeed   (struct dvb_demux_feed*  Feed);

#ifdef __TDT__ 
int WriteToDecoder (struct dvb_demux_feed *Feed, const u8 *buf, size_t count);
#endif

#endif
