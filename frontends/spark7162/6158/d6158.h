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
// �ļ�������	ter 6158
//
/******************************************************************************/

#ifndef __D6158_H
#define __D6158_H

/********************************  �ļ�����************************************/

#include "nim_panic6158.h"

#ifdef __cplusplus
extern "C" {
#endif


/********************************  ��������************************************/

/********************************  ���ݽṹ************************************/

/********************************  �� �� ��************************************/

#if defined(MODULE)
#define printf printk
#endif

/********************************  ��������************************************/

/********************************  ��������************************************/

/********************************  ��������************************************/

YW_ErrorType_T demod_d6158_Open(U8 Handle);
YW_ErrorType_T demod_d6158_Close(U8 Index);
YW_ErrorType_T demod_d6158_IsLocked(U8 Handle, BOOL *IsLocked);
#if !defined(MODULE)
YW_ErrorType_T demod_d6158_Identify(IOARCH_Handle_t IOHandle, U8 ucID, U8 *
pucActualID);
#endif

YW_ErrorType_T demod_d6158_Repeat(IOARCH_Handle_t				DemodIOHandle, /*demod
io ??��*/
									IOARCH_Handle_t				TunerIOHandle, /*??? io ??��*/
									TUNER_IOARCH_Operation_t Operation,
									unsigned short SubAddr,
									unsigned char *Data,
									unsigned int TransferSize,
									unsigned int Timeout);
YW_ErrorType_T demod_d6158_GetSignalInfo(U8 Handle,
										unsigned int  *Quality,
										unsigned int  *Intensity,
										unsigned int  *Ber);

YW_ErrorType_T demod_d6158_ScanFreqDVB(struct dvb_frontend_parameters *p,
	                                            struct nim_device *dev,UINT8   System);
YW_ErrorType_T demod_d6158earda_ScanFreq(struct dvb_frontend_parameters *p,
	                                            struct nim_device *dev,UINT8   System);
void nim_config_EARDATEK11658(struct COFDM_TUNER_CONFIG_API *Tuner_API_T, UINT32 i2c_id, UINT8 idx);
/********************************  ��������************************************/



#ifdef __cplusplus
}
#endif


#endif  /* __D6158_H */
/* EOF------------------------------------------------------------------------*/

/* BOL-------------------------------------------------------------------*/
//$Log$
/* EOL-------------------------------------------------------------------*/

