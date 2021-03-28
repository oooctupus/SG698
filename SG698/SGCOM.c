#define _SGCOM_H_
#include "HEADERS.h"
/*******************************************************************************
 ** ��������: uint16 Dat_SciC_Receive(void)
 ** ��������: SCICͨ��Э�麯��
 *******************************************************************************/
uint16 Dat_SciC_Receive(void)
{
    //�¶���һ��ch_BDCRxBuff�����������
        //--------------------------------------------------------------
        // step 1: ���ճ�ʱ����
        //--------------------------------------------------------------
        if(st_SystemTimer.bTimer1ms == 1)
        {
            if(p_u16_SciCRxBuffPoint != u16_SciCRxBuff) // ��������ǿ�
            {
                if(++u16_SciCReceicePerCnt1ms >= 4) // ��֮֡��ʱ��������4�ַ�
                {
                    u16_SciCReceicePerCnt1ms = 0;
                    st_SciC_Com.bit.bFRAMERECEIVE= 1;
                }
            }
        }

        //--------------------------------------------------------------
        // step 2: �������׼����������������
        //--------------------------------------------------------------
       /* while(p_ch_BDRxBuffPoint == ch_BDRxBuff)
        {
            if(p_SciC_Regs->SCIFFRX.bit.RXFFST != 0)
                u16_SciCReceicePerCnt1ms = 0;
            *p_ch_BDRxBuffPoint = p_SciC_Regs->SCIRXBUF.bit.RXDT;
            if(*p_ch_BDRxBuffPoint=='$')
                p_ch_BDRxBuffPoint++;
        }
    */
        while(p_SciC_Regs->SCIFFRX.bit.RXFFST != 0) // �Ѿ�׼���ô�BUFFER�ж�ȡ�ַ�
        {
            u16_SciCReceicePerCnt1ms = 0;
            if(p_u16_SciCRxBuffPoint - u16_SciCRxBuff< SCIC_RX_BUFF_SIZE)  // ��������δ��
            {
                *p_u16_SciCRxBuffPoint++ = p_SciC_Regs->SCIRXBUF.bit.RXDT;
            }
            else
            {
                p_SciC_Regs->SCIRXBUF.bit.RXDT;
            }
        }
        return 0;

        //--------------------------------------------------------------
}

/*******************************************************************************
 ** ��������: uint16 Dat_SciC_Process(void)
 ** ��������: SCICͨ��Э�麯��
 *******************************************************************************/
uint16 Dat_SciC_Process(void)
{
}

/*******************************************************************************
 ** ��������: uint16 Dat_SciC_Send(void)
 ** ��������: SCICͨ��Э�麯��
 ** �䡡     ��: ��
 ** �䡡     ��: ��
 ** ����޸�: 2020��02��27��
 *******************************************************************************/
uint16 Dat_SciC_Send(void)
{
        //--------------------------------------------------------------
        // step 1: ����������ʱ�������
        //--------------------------------------------------------------
            if(p_SciC_Regs->SCIFFTX.bit.TXFFST < 4)  //�жϷ��ͻ�����׼���ñ�־λ
            {
                if(p_u16_SciCTxBuffPoint-u16_SciCTxBuff<26+2*u16_SciCTxCount) //�ж��Ƿ񳬳����ͻ�����
                {
                    p_SciC_Regs->SCITXBUF = *p_u16_SciCTxBuffPoint++;  //��������
                }
                else
                {
                    
                }
            }
            return 0;

        //--------------------------------------------------------------
}



/*******************************************************************************
 ** ��������: void App_SciC_Protocol(void)
 ** ��������: SCICЭ�鴦��
 ** �䡡     ��: ��
 ** �䡡     ��: ��
 ** ����޸�: 2020��02��27��
 *******************************************************************************/
void App_SciC_Protocol(void)
{
    switch (st_SciC_Com.bit.u2_SciCCOMSTATE)
    {
    case SciCRECEIVE:
        if (st_SciC_Com.bit.bFRAMERECEIVE != 1)                  // �ж��Ƿ����һ֡����
        {
            Dat_SciC_Receive();                                     // ���ݽ���
        }
        else
        {
            st_SciC_Com.bit.bFRAMERECEIVE = 0;                  // ����ձ�־
            st_SciC_Com.bit.u2_SciCCOMSTATE = SciCPROCESS;            // ��Ϊ����״̬
        }
        break;
    case SciCPROCESS:
        if (st_SciC_Com.bit.bFRAMEPROCESSED != 1)                     // �ж��Ƿ���һ֡����
        {
            Dat_SciC_Process();                                     // ����Э�鴦��
        }
        else
        {
            st_SciC_Com.bit.bFRAMEPROCESSED = 0;                       // �崦�����־
            if (st_SciC_Com.bit.bFRAMEERROR != 1)
            {
                st_SciC_Com.bit.u2_SciCCOMSTATE = SciCWAITSEND;       // ��Ϊ����״̬

            }
            else
            {
                st_SciC_Com.bit.bFRAMEERROR = 0;
                p_u16_SciCRxBuffPoint = u16_SciCRxBuff;
                st_SciC_Com.bit.u2_SciCCOMSTATE = SciCRECEIVE;        // ���´��ڽ���״̬
            }

        }
        break;
    case SciCWAITSEND:
        if (st_SystemTimer.bTimer1ms == 1)
        {
            if (++u16_SciCCntPer1ms >= 2)                             // 2ms����׼��
            {
                u16_SciCCntPer1ms = 0;
                p_u16_SciCTxBuffPoint = u16_SciCTxBuff;             // ���ͻ�����ָ�븴λ


                st_SciC_Com.bit.u2_SciCCOMSTATE = SciCSEND;
            }
        }
        break;
    case SciCSEND:
        if (st_SciC_Com.bit.bFRAMESEND != 1)                       // �ж��Ƿ�����һ֡����
        {
            Dat_SciC_Send();                                           // ���÷��ͺ���
        }
        else
        {
            st_SciC_Com.bit.bFRAMESEND = 0;                          // �巢�����־
            p_u16_SciCRxBuffPoint = u16_SciCRxBuff;
            st_SciC_Com.bit.u2_SciCCOMSTATE = SciCRECEIVE;            // ��Ϊ����״̬
        }
        break;
    default:
        st_SciC_Com.bit.u2_SciCCOMSTATE = SciCRECEIVE;
        break;
    }
}

void Dat_SciC(void)
{
    //--------------------------------------------------------------
    // step 1: Э�鴦��
    //--------------------------------------------------------------
    {
        App_SciC_Protocol();       //�ӻ�ģʽЭ�鴦��
    }
}

/*******************************************************************************
 ** ��������: void   App_SciC_Init(void)
 ** ��������: SCICͨ��Э���ʼ��
 ** �䡡     ��: ��
 ** �䡡     ��: ��
 ** ����޸�: 2020��02��27��
 *******************************************************************************/
void App_SciC_Init(void)
{
}
