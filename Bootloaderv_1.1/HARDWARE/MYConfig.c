#include "sys.h"

/*********************************************************************************************************
*                                          全局变量
*********************************************************************************************************/



/*********************************************************************************************************
*                                          函数声明
*********************************************************************************************************/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART1_Configuration(void);
void TIM3_Configuration(void);
void TIM4_Configuration(void);
void TIM5_Configuration(void);
void TIM6_Configuration(void);
void EXTI_Configuration(void);
void TIM7_Configuration(void);

/*********************************************************************************************************
* 名    称 ：Config_Init 
* 功能描述 : 初始化应用配置函数
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 :（日期、修改人名、修改原因）
* 特殊说明 : 
*********************************************************************************************************/
void Config_Init (void)
{
	  RCC_Configuration();
	  GPIO_Configuration();
	  NVIC_Configuration();
	  USART1_Configuration();		//串口打印	   
//	TIM1_Configuration();		
	  TIM4_Configuration();		 //pwm
// 	TIM5_Configuration();
// 	TIM6_Configuration();		//定时更新姿态
//	TIM7_Configuration();		//精确延时
	  EXTI_Configuration();
}

/*********************************************************************************************************
* 名    称 ：RCC_Configuration
* 功能描述 : 初始化系统时钟
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);外部中断，需要使能 AFIO 时钟
*********************************************************************************************************/
void RCC_Configuration(void){

  SystemInit(); 

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM6|RCC_APB1Periph_TIM7
  						, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB
  						| RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOD| RCC_APB2Periph_GPIOE
						| RCC_APB2Periph_GPIOE| RCC_APB2Periph_USART1, ENABLE);
}
/*********************************************************************************************************
* 名    称 ：GPIO_Configuration
* 功能描述 : 
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/ 
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			 //通用推挽输出模式
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			 //通用推挽输出模式
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);
  
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			 //通用推挽输出模式
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			 //通用推挽输出模式
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);				    
}

/*********************************************************************************************************
* 名    称 ：USART1_Configuration
* 功能描述 : 初始化串口1
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void USART1_Configuration()
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;              /*PA.9*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       /*复用推挽输出*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 /*初始化GPIOA.9*/
   
	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             /*PA10*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  /*浮空输入*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 /*初始化GPIOA.10*/  

	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = 115200;           /*串口波特率*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;      /*字长为8位数据格式*/
	USART_InitStructure.USART_StopBits = USART_StopBits_1;           /*一个停止位*/
	USART_InitStructure.USART_Parity = USART_Parity_No;              /*无奇偶校验位*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  /*无硬件数据流控制*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                 /*收发模式*/

	USART_Init(USART1, &USART_InitStructure);     /*初始化串口1*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);/*开启串口接受中断*/
	USART_Cmd(USART1, ENABLE);                    /*使能串口1*/ 
}

/*********************************************************************************************************
* 名    称 ：TIM4_Configuration
* 功能描述 : 初始化定时器
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void TIM4_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 10000;					 /*f（pwm）=(72Mhz/200000)=360hz频率*/
	TIM_TimeBaseStructure.TIM_Prescaler = (15-1);	 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
	TIM_OCInitStructure.TIM_Pulse = 5000;						            
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	      /*高电平*/

	TIM_OC2Init(TIM4, &TIM_OCInitStructure);	
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);			          /*使能或者失能TIMx在CCR1上的预装载寄存器*/

	TIM_ARRPreloadConfig(TIM4, ENABLE);  
	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);
}
/*********************************************************************************************************
* 名    称 ：TIM5_Configuration
* 功能描述 : 初始化定时器
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void TIM5_Configuration(void)
{
	
}
/*********************************************************************************************************
* 名    称 ：TIM6_Configuration
* 功能描述 : 初始化定时器
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void TIM6_Configuration(void)
{
	
}
/*********************************************************************************************************
* 名    称 ：TIM7_Configuration
* 功能描述 : 初始化定时器
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 5000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	TIM_PrescalerConfig(TIM7, 7200-1, TIM_PSCReloadMode_Immediate);
	 
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, ENABLE);		
}
/*********************************************************************************************************
* 名    称 ：NVIC_Configuration
* 功能描述 : 初始化中断优先级
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
}
/*********************************************************************************************************
* 名    称 ：NVIC_Configuration
* 功能描述 : 初始化中断优先级
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	     /*由于使用FreeRTOS，所以必须配置为组4*/   
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;               /*USB_LP_CAN1_RX0_IRQn;	CAN1 RX0中断*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		    /*抢占优先级0*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			        /*子优先级为0*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
//	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;		   
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

}
