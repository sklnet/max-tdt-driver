/*$Source$*/
/*****************************�ļ�ͷ��ע��*************************************/
//
//			Copyright (C), 2013-2018, AV Frontier Tech. Co., Ltd.
//
//
// �� �� ����	$RCSfile$
//
// �� �� �ߣ�	D26LF
//
// ����ʱ�䣺	2013.12.11
//
// �����£�	$Date$
//
//				$Author$
//
//				$Revision$
//
//				$State$
//
// �ļ�������	d6158 inner
//
/******************************************************************************/

#ifndef __D6158_INNER_H
#define __D6158_INNER_H

/********************************  �ļ�����************************************/

#include <sys_config.h>
#include <retcode.h>
#include <types.h>
#include <osal/osal.h>
#include <api/libc/alloc.h>
#include <api/libc/printf.h>
#include <api/libc/string.h>
#include <hal/hal_gpio.h>
#include <bus/i2c/i2c.h>
#include <hld/hld_dev.h>
#include <hld/nim/nim_dev.h>
#include <hld/nim/nim.h>

#include <hld/nim/nim_tuner.h>
#include <bus/tsi/tsi.h>
#if !defined(MODULE)
#include <stdio.h>
#endif

typedef UINT32 OSAL_ID;

#include "nim_panic6158.h"


#ifdef __cplusplus
extern "C" {
#endif


/********************************  ��������************************************/

#define QAM0 1
#define QAM4 2
#define QAM8 3
#define QAM16 4
#define QAM32 5
#define QAM64 6
#define QAM128 7
#define QAM256 8
#define PANASONIC_DEMODULATOR 1

#define SUCCESS         0       /* Success return */

#define OSAL_INVALID_ID				0
#define RET_SUCCESS		((INT32)0)
#define ERR_FAILUE		-9


#define ERR_NO_DEV      -8      /* Device not exist on PCI */
#define HLD_DEV_TYPE_NIM		0x01050000	/* NIM (Demodulator + tuner) */
#define ERR_NO_MEM      -1      /* Not enough memory error */
#define ERR_ID_FULL     -21     /* No more ID available */
#define HLD_DEV_STATS_UP		0x01000001	/* Device is up */
#define HLD_DEV_STATS_RUNNING	0x01000002	/* Device is running */

/********************************  ���ݽṹ************************************/

/********************************  �� �� ��************************************/

#define dev_alloc(s, Type, Size)	YWOS_Malloc(Size)
#define dev_free(p)				YWOS_Free(p)
#define dev_register(dev)		SUCCESS
#define MALLOC(Size)			YWOS_Malloc(Size)
#define FREE(p)					YWOS_Free(p)
#define MEMCPY					YWLIB_Memcpy
#define MEMSET					YWLIB_Memset
#define osal_flag_delete(flag_id)

/********************************  ��������************************************/

/********************************  ��������************************************/

/********************************  ��������************************************/

void osal_task_sleep(U32 ms);
OSAL_ID osal_mutex_create(void);
#define osal_mutex_lock(osalid, time)
#define osal_mutex_unlock(osalid)
#define osal_mutex_delete(osalid)

/********************************  ��������************************************/




#ifdef __cplusplus
}
#endif


#endif  /* __D6158_INNER_H */
/* EOF------------------------------------------------------------------------*/

/* BOL-------------------------------------------------------------------*/
//$Log$
/* EOL-------------------------------------------------------------------*/

