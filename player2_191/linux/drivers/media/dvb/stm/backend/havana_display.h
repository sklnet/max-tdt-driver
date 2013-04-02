/************************************************************************
Copyright (C) 2005 STMicroelectronics. All Rights Reserved.

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

Source file name : havana_display.h derived from havana_player_factory.h
Author :           Julian

Definition of the implementation of havana player module for havana.


Date        Modification                                    Name
----        ------------                                    --------
05-Sep-07   Created                                         Julian

************************************************************************/

#ifndef H_HAVANA_DISPLAY
#define H_HAVANA_DISPLAY

#define FACTORY_ANY_ID                  "*"

#if defined(__TDT__)

#if defined(FORTIS_HDBOX) || defined(TF7700) || defined(UFS922) || defined(UFC960) || defined(HL101) || \
    defined(VIP1_V2) || defined(VIP2_V1) || defined(UFS912) || defined(SPARK) || \
    defined(SPARK7162) || defined(OCTAGON1008) || \
    defined(ATEVIO7500) || defined(HS7810A) || defined(HS7110) || defined(WHITEBOX) || defined(IPBOX9900) || defined(IPBOX99) || \
    defined(IPBOX55) || defined(ADB_BOX) || defined(CUBEREVO) || \
    defined(CUBEREVO_MINI2) || defined(CUBEREVO_MINI) || defined(CUBEREVO_250HD) || \
    defined(CUBEREVO_2000HD) || defined(CUBEREVO_9500HD) || defined(CUBEREVO_MINI_FTA) || defined(UFS913)
#define AUDIO_BUFFER_MEMORY                     0x00180000
#else
#define AUDIO_BUFFER_MEMORY                     0x00100000       // 1 mb
#endif

#else
#define AUDIO_BUFFER_MEMORY                     0x00080000       // 1/2   mb
#endif

#define PRIMARY_VIDEO_BUFFER_MEMORY             PLAYER2_PRIMARY_VIDEO_BUFFER_MEMORY       // ~3mb per full image HD 4:2:0, ~1.32mb in 720p
#define SECONDARY_VIDEO_BUFFER_MEMORY           PLAYER2_SECONDARY_VIDEO_BUFFER_MEMORY
#define AVR_VIDEO_BUFFER_MEMORY                 PLAYER2_AVR_VIDEO_BUFFER_MEMORY
#define MAX_VIDEO_DECODE_BUFFERS                32

/*      Debug printing macros   */
#ifndef ENABLE_DISPLAY_DEBUG
#define ENABLE_DISPLAY_DEBUG            0
#endif

#define DISPLAY_DEBUG(fmt, args...)      ((void) (ENABLE_DISPLAY_DEBUG && \
                                            (report(severity_note, "HavanaDisplay_c::%s: " fmt, __FUNCTION__, ##args), 0)))

/* Output trace information off the critical path */
#define DISPLAY_TRACE(fmt, args...)     (report(severity_note, "HavanaDispla_c::%s: " fmt, __FUNCTION__, ##args))
/* Output errors, should never be output in 'normal' operation */
#define DISPLAY_ERROR(fmt, args...)     (report(severity_error, "HavanaDisplay_c::%s: " fmt, __FUNCTION__, ##args))


/// Display wrapper class responsible for managing manifestors.
class HavanaDisplay_c
{
private:
    DeviceHandle_t              DisplayDevice;

    class Manifestor_c*         Manifestor;
    PlayerStreamType_t          PlayerStreamType;

public:

                                HavanaDisplay_c                (void);
                               ~HavanaDisplay_c                (void);

    HavanaStatus_t              GetManifestor                  (class HavanaPlayer_c*   HavanaPlayer,
                                                                char*                   Media,
                                                                char*                   Encoding,
                                                                unsigned int            SurfaceId,
                                                                class Manifestor_c**    Manifestor);

    class Manifestor_c*         ReferenceManifestor             (void) {return Manifestor;};
};

/*{{{  doxynote*/
/*! \class      HavanaDisplay_c
    \brief      Controls access to and initialisation of the manifestor

*/

/*! \fn class Manifestor_c* HavanaDisplay_c::GetManifestor( void );
\brief Create and initialise a manifestor.

    Create a manifestor and initialise it based on the input parameters.

\param HavanaPlayer     Parent class
\param Media            Video or Audio
\param Encoding         Content type - determines some layout characteristic
\param SurfaceId        Where we are going to display the stream
\param Manifestor       Created manifestor

\return Havana status code, HavanaNoError indicates success.
*/

/*! \fn class Manifestor_c* HavanaDisplay_c::ReferenceManifestor( void );
\brief Use the manifestor that this class holds.

    Use the current manifestor, without perturbing it (ie setting parameters encoding etc...).

\return a pointer to a manifestor class instance.
*/



/*}}}*/

#endif

