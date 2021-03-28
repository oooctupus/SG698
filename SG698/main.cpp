#define _SGCOM_H_
#include "SG698.h"
#include "SGCOM.h" 
#include "iostream"

uint16 DA2P(DA1 trans_DA1, DA2 trans_DA2)
{
	if (trans_DA1 == 0 && trans_DA2 == 0)
	{
		return 0;
	}
	else
	{
		uint16 temp_DA1V = 1;
		uint16 temp_DA2V = 0;
		uint16 temp_copy_DA1V = trans_DA1;
		while (temp_copy_DA1V != 1 && temp_copy_DA1V != 0)
		{
			temp_copy_DA1V = temp_copy_DA1V >> 1;
			temp_DA1V++;
		}
		temp_DA2V = trans_DA2;
		return 8 * (temp_DA2V - 1) + temp_DA1V;
	}
}

uint16 DT2F(DT1 trans_DT1, DT2 trans_DT2)
{
	uint16 temp_DT1V = 1;
	uint16 temp_DT2V = 0;
	uint16 temp_copy_DT1V = trans_DT1;
	while (temp_copy_DT1V != 1 && temp_copy_DT1V != 0)
	{
		temp_copy_DT1V = temp_copy_DT1V >> 1;
		temp_DT1V++;
	}
	temp_DT2V = trans_DT2;
	return 8 * temp_DT2V + temp_DT1V;
}

int main(){
	/*
	p_u16_TempMaskPoint=(uint16*)&st_SciCRxLengthDomain;
	*(u16_SciCRxBuff + 1) = 252;
	*(u16_SciCRxBuff + 2) = 3;
	*p_u16_TempMaskPoint = *(u16_SciCRxBuff + 1) | (*(u16_SciCRxBuff + 2) << 8);
	//st_SciCRxLengthDomain.bit.u14_length = 255;
	//st_SciCRxLengthDomain.bit.u2_status = LEN_DISABLE;
	std::cout << *p_u16_TempMaskPoint << std::endl<< 
		st_SciCRxLengthDomain.bit.u14_length<< std::endl<< st_SciCRxLengthDomain.bit.u2_status<< std::endl;
	//p_uch_TempMaskPoint
	p_uch_TempMaskPoint = (uchar*)&st_SciCRxLengthDomain;
	*(u16_SciCTxBuff + 1) = *p_uch_TempMaskPoint++;
	*(u16_SciCTxBuff + 2) = *p_uch_TempMaskPoint;
	std::cout << *(u16_SciCTxBuff + 1) << std::endl << *(u16_SciCTxBuff + 2);
	*/
	std::cout << DA2P(DA1_0, DA2_0);
	return 0;
}

void domain_init()
{
	p_u16_TempMaskPoint = (uint16*)&st_SciCRxLengthDomain;
	*p_u16_TempMaskPoint = u16_SciCRxBuff[length_head] | (u16_SciCRxBuff[length_head+1] << 8);	//长度域装载

	u16_SciCRxLength = st_SciCRxLengthDomain.bit.u14_length;									//读取用户数据区长度，保存为局部变量

	p_u8_TempMaskPoint = (uchar*)&st_SciCRxControlDomain;
	*p_u8_TempMaskPoint = u16_SciCRxBuff[control_head];										//控制域装载

	p_u8_TempMaskPoint = (uchar*)&st_SciCRxSEQDomain;
	*p_u8_TempMaskPoint = u16_SciCRxBuff[SEQ_head];											//帧序列域装载

	p_u8_TempMaskPoint = (uchar*)&st_SciCRxAUXDomain;
	u16_SciCRxAUXHead = u16_SciCRxLength + control_head - 8;
	for (int i = 0;i < 8; i++)
	{
		*p_u8_TempMaskPoint++ = u16_SciCRxBuff[u16_SciCRxAUXHead + i];								//附加信息域装载
	}

	u16_SciCRxCSHead = u16_SciCRxAUXHead + 8;											//校验和域装载
	u8_SciCRxCSDomain = u16_SciCRxBuff[u16_SciCRxCSHead];

	u16_SciCRxSumCheck = 0;
	for (int i = 0;i < u16_SciCRxLength;i++)
	{
		u16_SciCRxSumCheck = u16_SciCRxSumCheck ^ u16_SciCRxBuff[control_head + i];		//输入校验和计算 
	}

}

