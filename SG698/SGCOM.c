#define _SGCOM_H_
#include "HEADERS.h"
/*******************************************************************************
 ** 函数名称: uint16 Dat_SciC_Receive(void)
 ** 功能描述: SCIC通信协议函数
 *******************************************************************************/
uint16 Dat_SciC_Receive(void)
{
    //新定义一个ch_BDCRxBuff数组接受数据
        //--------------------------------------------------------------
        // step 1: 接收超时处理
        //--------------------------------------------------------------
        if(st_SystemTimer.bTimer1ms == 1)
        {
            if(p_u16_SciCRxBuffPoint != u16_SciCRxBuff) // 接收数组非空
            {
                if(++u16_SciCReceicePerCnt1ms >= 4) // 两帧之间时间间隔大于4字符
                {
                    u16_SciCReceicePerCnt1ms = 0;
                    st_SciC_Com.bit.bFRAMERECEIVE= 1;
                }
            }
        }

        //--------------------------------------------------------------
        // step 2: 如果数据准备就绪，接收数据
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
        while(p_SciC_Regs->SCIFFRX.bit.RXFFST != 0) // 已经准备好从BUFFER中读取字符
        {
            u16_SciCReceicePerCnt1ms = 0;
            if(p_u16_SciCRxBuffPoint - u16_SciCRxBuff< SCIC_RX_BUFF_SIZE)  // 接收数组未满
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
 ** 函数名称: uint16 Dat_SciC_Process(void)
 ** 功能描述: SCIC通信协议函数
 *******************************************************************************/
uint16 Dat_SciC_Process(void)
{
}

/*******************************************************************************
 ** 函数名称: uint16 Dat_SciC_Send(void)
 ** 功能描述: SCIC通信协议函数
 ** 输　     入: 无
 ** 输　     出: 无
 ** 最后修改: 2020年02月27日
 *******************************************************************************/
uint16 Dat_SciC_Send(void)
{
        //--------------------------------------------------------------
        // step 1: 缓冲区不满时进行填充
        //--------------------------------------------------------------
            if(p_SciC_Regs->SCIFFTX.bit.TXFFST < 4)  //判断发送缓冲区准备好标志位
            {
                if(p_u16_SciCTxBuffPoint-u16_SciCTxBuff<26+2*u16_SciCTxCount) //判断是否超出发送缓冲区
                {
                    p_SciC_Regs->SCITXBUF = *p_u16_SciCTxBuffPoint++;  //传送数据
                }
                else
                {
                    
                }
            }
            return 0;

        //--------------------------------------------------------------
}



/*******************************************************************************
 ** 函数名称: void App_SciC_Protocol(void)
 ** 功能描述: SCIC协议处理
 ** 输　     入: 无
 ** 输　     出: 无
 ** 最后修改: 2020年02月27日
 *******************************************************************************/
void App_SciC_Protocol(void)
{
    switch (st_SciC_Com.bit.u2_SciCCOMSTATE)
    {
    case SciCRECEIVE:
        if (st_SciC_Com.bit.bFRAMERECEIVE != 1)                  // 判断是否接收一帧数据
        {
            Dat_SciC_Receive();                                     // 数据接收
        }
        else
        {
            st_SciC_Com.bit.bFRAMERECEIVE = 0;                  // 清接收标志
            st_SciC_Com.bit.u2_SciCCOMSTATE = SciCPROCESS;            // 置为处理状态
        }
        break;
    case SciCPROCESS:
        if (st_SciC_Com.bit.bFRAMEPROCESSED != 1)                     // 判断是否处理一帧数据
        {
            Dat_SciC_Process();                                     // 调用协议处理
        }
        else
        {
            st_SciC_Com.bit.bFRAMEPROCESSED = 0;                       // 清处理完标志
            if (st_SciC_Com.bit.bFRAMEERROR != 1)
            {
                st_SciC_Com.bit.u2_SciCCOMSTATE = SciCWAITSEND;       // 置为发送状态

            }
            else
            {
                st_SciC_Com.bit.bFRAMEERROR = 0;
                p_u16_SciCRxBuffPoint = u16_SciCRxBuff;
                st_SciC_Com.bit.u2_SciCCOMSTATE = SciCRECEIVE;        // 重新处于接收状态
            }

        }
        break;
    case SciCWAITSEND:
        if (st_SystemTimer.bTimer1ms == 1)
        {
            if (++u16_SciCCntPer1ms >= 2)                             // 2ms发送准备
            {
                u16_SciCCntPer1ms = 0;
                p_u16_SciCTxBuffPoint = u16_SciCTxBuff;             // 发送缓冲区指针复位


                st_SciC_Com.bit.u2_SciCCOMSTATE = SciCSEND;
            }
        }
        break;
    case SciCSEND:
        if (st_SciC_Com.bit.bFRAMESEND != 1)                       // 判断是否发送完一帧数据
        {
            Dat_SciC_Send();                                           // 调用发送函数
        }
        else
        {
            st_SciC_Com.bit.bFRAMESEND = 0;                          // 清发送完标志
            p_u16_SciCRxBuffPoint = u16_SciCRxBuff;
            st_SciC_Com.bit.u2_SciCCOMSTATE = SciCRECEIVE;            // 置为接收状态
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
    // step 1: 协议处理
    //--------------------------------------------------------------
    {
        App_SciC_Protocol();       //从机模式协议处理
    }
}

/*******************************************************************************
 ** 函数名称: void   App_SciC_Init(void)
 ** 功能描述: SCIC通信协议初始化
 ** 输　     入: 无
 ** 输　     出: 无
 ** 最后修改: 2020年02月27日
 *******************************************************************************/
void App_SciC_Init(void)
{
}
