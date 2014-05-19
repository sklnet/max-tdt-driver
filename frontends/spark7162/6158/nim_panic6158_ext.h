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
// ����ʱ�䣺	2013.12.16
//
// �����£�	$Date$
//
//				$Author$
//
//				$Revision$
//
//				$State$
//
// �ļ�������	nim panic6158 ext
//
/******************************************************************************/

#ifndef __NIM_PANIC6158_EXT_H
#define __NIM_PANIC6158_EXT_H

/********************************  �ļ�����************************************/


#ifdef __cplusplus
extern "C" {
#endif


/********************************  ��������************************************/

/********************************  ���ݽṹ************************************/

/********************************  �� �� ��************************************/

/********************************  ��������************************************/

/********************************  ��������************************************/

/********************************  ��������************************************/

INT32 nim_panic6158_channel_change(struct nim_device *dev, struct NIM_Channel_Change *param);
INT32 nim_panic6158_open(struct nim_device *dev);
INT32 nim_panic6158_close(struct nim_device *dev);
INT32 nim_panic6158_get_lock(struct nim_device *dev, UINT8 *lock);
INT32 nim_panic6158_get_SNR(struct nim_device *dev, UINT8 *snr);
INT32 nim_panic6158_get_BER(struct nim_device *dev, UINT32 *ber);
INT32 nim_panic6158_get_AGC(struct nim_device *dev, UINT8 *agc);
INT32 nim_panic6158_get_AGC_301(struct nim_device *dev, UINT8 *agc);
INT32 nim_panic6158_get_AGC_603(struct nim_device *dev, UINT8 *agc);
INT32 nim_panic6158_attach(UINT8 Handle, PCOFDM_TUNER_CONFIG_API pConfig,TUNER_OpenParams_T *OpenParams);
YW_ErrorType_T tuner_mxl301_Identify(IOARCH_Handle_t	*i2c_adap);
INT32 nim_panic6158_channel_change_earda(struct nim_device *dev, struct NIM_Channel_Change *param);
INT32 nim_panic6158_ioctl_earda(struct nim_device *dev, INT32 cmd, UINT32 param);
INT32 nim_panic6158_attach_earda(UINT8 Handle, PCOFDM_TUNER_CONFIG_API pConfig, TUNER_OpenParams_T *OpenParams);

INT32 DMD_TCB_WriteRead(void* nim_dev_priv, UINT8	tuner_address , UINT8* wdata , int wlen , UINT8* rdata , int rlen);

/********************************  ��������************************************/




#ifdef __cplusplus
}
#endif


#endif  /* __NIM_PANIC6158_EXT_H */
/* EOF------------------------------------------------------------------------*/

/* BOL-------------------------------------------------------------------*/
//$Log$
/* EOL-------------------------------------------------------------------*/

