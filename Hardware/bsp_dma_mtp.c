#include "bsp_dma_mtp.h"


								
/* 定义DMA传输目标存储器
 * 存储在内部的SRAM中																		
 */
									
uint8_t SendBuff[SENDBUFF_SIZE];

void USARTx_DMA_Config(void){
	
	//声明结构体
	DMA_InitTypeDef DMA_InitStructure_MTP;
	
	//使能DMA的时钟
	RCC_AHBPeriphClockCmd(DMA_MTP_CLK,ENABLE);
	
	//配置DMA参数
	//源数据地址
	DMA_InitStructure_MTP.DMA_PeripheralBaseAddr =  USART_DR_ADDRESS;
	//存储器地址(传入SendBuff的地址)
	DMA_InitStructure_MTP.DMA_MemoryBaseAddr = (uint32_t)SendBuff;
	//传输方向
	DMA_InitStructure_MTP.DMA_DIR = DMA_DIR_PeripheralDST;
	
	
	//传输数目
	DMA_InitStructure_MTP.DMA_BufferSize = SENDBUFF_SIZE;
	
	
	//外设地址增量(使用串口数据寄存器，不用递增)
	DMA_InitStructure_MTP.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//外设数据宽度
	DMA_InitStructure_MTP.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	// 内存地址递增
	DMA_InitStructure_MTP.DMA_MemoryInc = DMA_MemoryInc_Enable;
    // 内存数据宽度
	DMA_InitStructure_MTP.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	

	//DMA模式（一次或循环模式）
	DMA_InitStructure_MTP.DMA_Mode = DMA_Mode_Normal;
	//通道优先级
	DMA_InitStructure_MTP.DMA_Priority = DMA_Priority_High;
	//不使能M TO M模式
	DMA_InitStructure_MTP.DMA_M2M = DMA_M2M_Disable;
	
	//初始化DMA
	DMA_Init(DMA_MTP_CHANNEL,&DMA_InitStructure_MTP);
	//清除DMA数据流传输完成标志位
    DMA_ClearFlag(USART_TX_DMA_FLAG_TC);
	//使能DMA
	DMA_Cmd(DMA_MTP_CHANNEL, ENABLE);

}


/**
  * 判断指定长度的两个数据源是否完全相等，
  * 如果完全相等返回1，只要其中一对数据不相等返回0
  */
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* 数据长度递减 */
  while(BufferLength--)
  {
    /* 判断两个数据源是否对应相等 */
    if(*pBuffer != *pBuffer1)
    {
      /* 对应数据源不相等马上退出函数，并返回0 */
      return 0;
    }
    /* 递增两个数据源的地址指针 */
    pBuffer++;
    pBuffer1++;
  }
  /* 完成判断并且对应数据相对 */
  return 1;  
}
