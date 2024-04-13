#ifndef _BSP_DMA_MTP_H
#define _BSP_DMA_MTP_H

#include "stm32f10x.h"                  // Device header
#include "bsp_usart.h"

// 要发送的数据大小
#define SENDBUFF_SIZE     50000

#define DMA_MTP_CLK					RCC_AHBPeriph_DMA1
#define DMA_MTP_CHANNEL				DMA1_Channel4
// 传输完成标志
#define USART_TX_DMA_FLAG_TC     	DMA1_FLAG_TC4


//外设寄存器地址
#define USART_DR_ADDRESS		(USART1_BASE+0x04)

void USARTx_DMA_Config(void);


#endif /*_BSP_DMA_MTP_H*/
