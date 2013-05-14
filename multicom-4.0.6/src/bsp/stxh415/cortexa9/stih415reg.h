/**************************************************************
 * Copyright (C) 2010   STMicroelectronics. All Rights Reserved.
 * This file is part of the latest release of the Multicom4 project. This release 
 * is fully functional and provides all of the original MME functionality.This 
 * release  is now considered stable and ready for integration with other software 
 * components.

 * Multicom4 is a free software; you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation 
 * version 2.

 * Multicom4 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with Multicom4; 
 * see the file COPYING.  If not, write to the Free Software Foundation, 59 Temple Place - 
 * Suite 330, Boston, MA 02111-1307, USA.

 * Written by Multicom team at STMicroelectronics in November 2010.  
 * Contact multicom.support@st.com. 
**************************************************************/

/*
 */

#ifndef __STIH415REG_H
#define __STIH415REG_H

#include "sh4regtype.h"

/*----------------------------------------------------------------------------*/

/*
 * Base addresses for control register banks.
 */


/* STiH415 control registers */
#ifndef STIH415_SYSCONF_BANK0_REGS_BASE
#define STIH415_SYSCONF_BANK0_REGS_BASE 0xfd320000
#endif

/*----------------------------------------------------------------------------*/

#include "st40reg.h"

/*
 * STiH415 SYSCFG control registers
 */

#define STIH415_SYSCONF_SYS_CFG00 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x0004)
#define STIH415_SYSCONF_SYS_CFG01 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x0008)
#define STIH415_SYSCONF_SYS_CFG02 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x000c)
#define STIH415_SYSCONF_SYS_CFG03 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x0010)
#define STIH415_SYSCONF_SYS_CFG04 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x0014)
#define STIH415_SYSCONF_SYS_CFG05 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x0018)
#define STIH415_SYSCONF_SYS_CFG06 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x001c)
#define STIH415_SYSCONF_SYS_CFG07 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x0020)
#define STIH415_SYSCONF_SYS_CFG08 SH4_DWORD_REG(STIH415_SYSCONF_BANK0_REGS_BASE + 0x0024)

#endif /* __STIH415REG_H */
