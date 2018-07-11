#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "iap.h"
#include "usart.h"
extern void Config_Init(void);
extern u16 USART_RX_STA;  /*接收状态标记*/
extern u16 USART_RX_CNT;  /*接收的字节数*/
extern u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//ALIENTEK miniSTM32开发板实验1
//跑马灯实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
int main(void)
{	
	  u8 t;
		u8 k = 1;
		u16 oldcount=0;	//老的串口接收数据值
		u16 applenth=0;	//接收到的app代码长度
		u8 clearflag=0;
		delay_init();	    	 //延时函数初始化	  
		Config_Init ();
		LED_Init();		  	//初始化与LED连接的硬件接口
		//KEY_Init();				//按键初始化
	  printf(" *******************************************************************\r\n");
	  printf(" *******************************************************************\r\n");
    printf(" *********              bootloader测试_v1.0            *************\r\n");
    printf(" *******************************************************************\r\n");
    printf(" *******************************************************************\r\n");	
		while(1)
		{
				/**********************************************************************************/	
				if(USART_RX_CNT)
				{
							if(oldcount == USART_RX_CNT)//新周期内,没有收到任何数据,认为本次数据接收完成.
							{
									if(k == 1)
									{
										k = 0;
										applenth = USART_RX_CNT;
										oldcount = 0;
										USART_RX_CNT = 0;									 
										printf("用户程序接收完成!\r\n");
										printf("代码长度:%dBytes\r\n",applenth);
									}	
							}
							else 
							{
									oldcount = USART_RX_CNT;
                   								
		          }		
				}
				/**********************************************************************************/
				
				/**********************************************************************************/
				t++;
				delay_ms(10);
				if(t==30)
				{
						LED0=!LED0;
					 // printf("boot\r\n");
						t=0;
						if(clearflag)
						{
								clearflag--;
								//if(clearflag==0)  LCD_Fill(60,210,240,210+16,WHITE);//清除显示
						}
				}	 
				/**********************************************************************************/    			
				//key = KEY_Scan(0);
				/**********************************************************************************/
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 0)
				{
						if(applenth)
						{
								printf("开始更新固件...\r\n");	
								//LCD_ShowString(60,210,200,16,16,"Copying APP2FLASH...");
								if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
								{	 
										iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//更新FLASH代码   
										delay_ms(100);
										//LCD_ShowString(60,210,200,16,16,"Copy APP Successed!!");
										printf("固件更新完成!\r\n");	
								}
								else 
								{
										//LCD_ShowString(60,210,200,16,16,"Illegal FLASH APP!  ");	   
										printf("非FLASH应用程序!\r\n");
								}
						}
						else 
					 {
					printf("没有可以更新的固件!\r\n");
					//LCD_ShowString(60,210,200,16,16,"No APP!");
					 }
				clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示									 
			}
			/******************************************************************************************/
			
			
			/*******************************************************************************************/
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)
			{
				if(applenth)
				{																	 
					printf("固件清除完成!\r\n");    
					//LCD_ShowString(60,210,200,16,16,"APP Erase Successed!");
					applenth=0;
				}else 
				{
					printf("没有可以清除的固件!\r\n");
					//LCD_ShowString(60,210,200,16,16,"No APP!");
				}
				clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示									 
			}
			/*********************************************************************************************/
			
			/*********************************************************************************************/
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)== 0)
			{
				printf("开始执行FLASH用户代码!!\r\n");
				if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
				{	 
					iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
				}
				else 
				{
					printf("非FLASH应用程序,无法执行!\r\n");  
				}									 
				clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示	  
			}
			/**********************************************************************************************/
			
			/**********************************************************************************************/
//			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6) ==0)
//			{
//					printf("开始执行SRAM用户代码!!\r\n");
//					if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x20000000)//判断是否为0X20XXXXXX.
//					{	 
//							iap_load_app(0X20001000);//SRAM地址
//					}
//					else 
//					{
//							printf("非SRAM应用程序,无法执行!\r\n");
//					}									 
//					clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示	 
//			}				   
	 }   	   
 }

