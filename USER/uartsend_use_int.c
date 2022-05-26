#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "string.h"
#include "timer.h"
#include "test.h"

#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)   (sizeof(a) / sizeof(*(a)))      //表示数组a中元素的个数 

#ifndef true 
#define true 1
#endif

#ifndef false 
#define false 0
#endif	

typedef unsigned char uint8_t ; 
uint8_t TxBuffer1[] = "USART Interrupt Example: This is USART1 DEMO,SUCCESS\n";
uint8_t RxBuffer1[RxBufferSize1],rec_f;
uint8_t TxCounter1 = 0x00;
uint8_t RxCounter1 = 0x00;
uint8_t NbrOfDataToTransfer1 = TxBufferSize1;
uint8_t NbrOfDataToRead1 = RxBufferSize1;

#define DEBUG_STRING "HELLO_WORLD\n"

#ifndef TRUE
#define TRUE 1U
#endif
#ifndef FALSE
#define FALSE 0U
#endif

//#define USE_NONBLOCK_USART
#ifndef USE_NONBLOCK_USART
//#define USE_BLOCK_USART
#endif


#define BAUDRATE_115200 115200U

typedef struct
{
	u8 UartSendData_Indixcation;
	u8 local_uart_transmit_buf[50];
	
}G_UART_Context_Var_t;

G_UART_Context_Var_t  G_UART_Context_Var = {0};

void Set_UartSendData_Indixcation(u8 status);
u8 Get_UartSendData_Indixcation(void);


void Set_UartSendData_Indixcation(u8 status)
{
	G_UART_Context_Var.UartSendData_Indixcation = status;
}

u8 Get_UartSendData_Indixcation(void)
{
	return G_UART_Context_Var.UartSendData_Indixcation;
}

void bsp_init(u32 uart_baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	//1 gpio init
		/* Enable USART1, GPIOA, GPIOD and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		   //USART1 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);			//A端口
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			   //USART1 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//复用开漏输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);				 //A端口

	//2 open clock
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//ÇÀÕ¼ÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//×ÓÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷


	//3 init usart1
	/* Enable USART1, GPIOA, GPIOD and AFIO clocks */
	if((uart_baudrate) == 115200)
		USART_InitStructure.USART_BaudRate = uart_baudrate;
	else
		USART_InitStructure.USART_BaudRate = 		USART_InitStructure.USART_BaudRate = uart_baudrate;

	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No; 	 //设置奇校验时，通信出现错误
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	 /* Configure the USART1 */
	USART_Init(USART1, &USART_InitStructure);
	 /* Enable the USART Transmoit interrupt: this interrupt is generated when the
	USART1 transmit data register is empty */ 
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	 /* Enable the USART Receive interrupt: this interrupt is generated when the
	  USART1 receive data register is not empty */
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//Usart1 NVIC ÅäÖÃ
  
	
	
	 /* Enable USART1 */
	USART_Cmd(USART1, ENABLE);
					

}

void SoftTimer_Init(void)
{

}


/*串口中断服务程序*/
//void USART1_IRQHandler(void)
//{
//  //unsigned int i;
//  /*接收中断*/
//#if 0
//  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//  {   
//    /* Read one byte from the receive data register */
//    RxBuffer1[RxCounter1++] = USART_ReceiveData(USART1);
//    if(RxCounter1 == NbrOfDataToRead1)  //接收数据达到需要长度，则将数据复制到发送数组中，并置标志
//    {                     
//      /* Disable the USART1 Receive interrupt */
//      //USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
//        for(i=0; i< RxCounter1; i++) TxBuffer1[i]  = RxBuffer1[i];
//        rec_f=1;
//        RxCounter1=0;
//        TxCounter1=0;
//        USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  //打开发送中断，这句是关键
//    }
//  }
//#endif
//	
//  /*发送中断*/
//  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
//  {  
//#if 1
//    USART_SendData(USART1, TxBuffer1[TxCounter1++]);
//	Set_UartSendData_Indixcation(true);
//
// 
//    if(TxCounter1 == NbrOfDataToTransfer1)//发送数据完成
//    {   
//			TxCounter1 = 0;
//			Set_UartSendData_Indixcation(false);
//			//memset(TxBuffer1,0x0,sizeof(TxBuffer1));
//      USART_ITConfig(USART1, USART_IT_TXE, DISABLE); //关闭发送中断
//    }
//#endif		
//  }   
//} 

#ifdef USE_BLOCK_USART
void Send_DebugData(char *p)
{	
	while((*p != '\0'))
	{
		while (!(USART1->SR & USART_FLAG_TXE))          // wait for TX buffer to empty
		continue;                           		// also either WDOG() or swap()
		USART_SendData(USART1,*p);
		while((USART1->SR&0X40)==0);
		p++;
	}		
}
#endif

void Send_DebugData_UseNoBlock(char *p,u8 length)
{
	if((NULL == p) && (length > 50))
	{
		return;
	}

	if((TxCounter1 == 0) && (false == Get_UartSendData_Indixcation()))
	{
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
	else
	{
		
		return;
	}
}


int main(void)
{
 unsigned char cnt = 0;
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 //bsp_init(BAUDRATE_115200);
 delay_init();
 //Set_UartSendData_Indixcation(FALSE);
 LED_Init();
 TIM3_Int_Init(5000,7199);
 //test_uart_init();
 test_init();
 test_printf(1,"UART SEND use interrupt and ringbuffer V0\r\n");

 while (1)
 {
 #ifdef USE_NONBLOCK_USART
	Send_DebugData_UseNoBlock(TxBuffer1,sizeof(TxBuffer1));
 	delay_ms(1000); 
 #endif

 #ifdef USE_BLOCK_USART
	 delay_ms(5000);

	 if(FALSE == Get_UartSendData_Indixcation())
	 {
		Send_DebugData(DEBUG_STRING);
		delay_ms(10000);
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		Set_UartSendData_Indixcation(TRUE);		
	 }
#endif
	 delay_ms(500);
	 LED0 = !LED0;
	 if(cnt++ >= 65535)
	 {
		cnt = 0;
	 }
	 
	 test_printf(1,"DEBUG INFO:cnt = %d\r\n",cnt); 
	 __asm("nop");
 }
}















