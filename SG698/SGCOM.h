#ifdef _SGCOM_H_
#define _EXTERN_DEF_ 
#else
#define _EXTERN_DEF_ extern
#endif

#include "SG698.h"

#define SCIC_RX_BUFF_SIZE   200
#define SCIC_TX_BUFF_SIZE   200

_EXTERN_DEF_ volatile un_SciCCOM st_SciC_Com;
//_EXTERN_DEF_ volatile struct SCI_REGS *p_SciC_Regs;

_EXTERN_DEF_ uint16 u16_SciCRxBuff[SCIC_RX_BUFF_SIZE]; // SG698接收缓冲区
_EXTERN_DEF_ uint16 u16_SciCTxBuff[SCIC_TX_BUFF_SIZE]; // SG698发送缓冲区

_EXTERN_DEF_ void   Dat_SciC(void); // 主MCU与LCD通信处理

_EXTERN_DEF_ void   App_SciC_Init(void);


#ifdef _SGCOM_H_

//volatile struct SCI_REGS *p_SciC_Regs = &ScicRegs;

uint16 u16_SciCCntPer1ms;
uint16 u16_SciCReceicePerCnt1ms;
uint16 u16_SciCLostPerCnt1ms;   // 错误帧计数
	
uint16 u16_SciCTxCount; // 发送计数
	
uint16 *p_u16_SciCRxBuffPoint = u16_SciCRxBuff; // SCIC接收缓冲区指针
uint16 *p_u16_SciCTxBuffPoint = u16_SciCTxBuff; // SCIC发送缓冲区指针

uint16 u16_SciCRxLength;
uint16 u16_SciCTxLength;

uint16 u16_SciCRxAUXHead;
uint16 u16_SciCTxAUXHead;

uint16 u16_SciCRxCSHead;
uint16 u16_SciCTxCSHead;

uint16 u16_SciCRxSumCheck;
uint16 u16_SciCTxSumCheck;


un_length_domain st_SciCRxLengthDomain;
un_length_domain st_SciCTxLengthDomain;

un_control_domain st_SciCRxControlDomain;
un_control_domain st_SciCTxControlDomain;

un_AFN_domain st_SciCRxAFNDomain;
un_AFN_domain st_SciCTxAFNDomain;

un_SEQ_domain st_SciCRxSEQDomain;
un_SEQ_domain st_SciCTxSEQDomain;

un_DADT_domain st_SciCRxDADTDomain;
un_DADT_domain st_SciCTxDADTDomain;


un_AUX_domain st_SciCRxAUXDomain;
un_AUX_domain st_SciCTxAUXDomain;

uchar u8_SciCRxCSDomain;
uchar u8_SciCTxCSDomain;

uint16* p_u16_TempMaskPoint;
uchar* p_u8_TempMaskPoint;
  
	//----------------------函数---------------------------------
	
void App_SciC_Protocol(void);
uint16 Dat_SciC_Send(void);
uint16 Dat_SciC_Process(void);
uint16 Dat_SciC_Receive(void);

uint16 DA2P();
uint16 DT2F();
void domain_init();

	

#endif

#undef _SGCOM_H_
#undef _EXTERN_DEF_
