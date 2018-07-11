#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "iap.h"
#include "usart.h"
extern void Config_Init(void);
extern u16 USART_RX_STA;  /*����״̬���*/
extern u16 USART_RX_CNT;  /*���յ��ֽ���*/
extern u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//ALIENTEK miniSTM32������ʵ��1
//�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
int main(void)
{	
	  u8 t;
		u8 k = 1;
		u16 oldcount=0;	//�ϵĴ��ڽ�������ֵ
		u16 applenth=0;	//���յ���app���볤��
		u8 clearflag=0;
		delay_init();	    	 //��ʱ������ʼ��	  
		Config_Init ();
		LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
		//KEY_Init();				//������ʼ��
	  printf(" *******************************************************************\r\n");
	  printf(" *******************************************************************\r\n");
    printf(" *********              bootloader����_v1.0            *************\r\n");
    printf(" *******************************************************************\r\n");
    printf(" *******************************************************************\r\n");	
		while(1)
		{
				/**********************************************************************************/	
				if(USART_RX_CNT)
				{
							if(oldcount == USART_RX_CNT)//��������,û���յ��κ�����,��Ϊ�������ݽ������.
							{
									if(k == 1)
									{
										k = 0;
										applenth = USART_RX_CNT;
										oldcount = 0;
										USART_RX_CNT = 0;									 
										printf("�û�����������!\r\n");
										printf("���볤��:%dBytes\r\n",applenth);
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
								//if(clearflag==0)  LCD_Fill(60,210,240,210+16,WHITE);//�����ʾ
						}
				}	 
				/**********************************************************************************/    			
				//key = KEY_Scan(0);
				/**********************************************************************************/
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) == 0)
				{
						if(applenth)
						{
								printf("��ʼ���¹̼�...\r\n");	
								//LCD_ShowString(60,210,200,16,16,"Copying APP2FLASH...");
								if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
								{	 
										iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//����FLASH����   
										delay_ms(100);
										//LCD_ShowString(60,210,200,16,16,"Copy APP Successed!!");
										printf("�̼��������!\r\n");	
								}
								else 
								{
										//LCD_ShowString(60,210,200,16,16,"Illegal FLASH APP!  ");	   
										printf("��FLASHӦ�ó���!\r\n");
								}
						}
						else 
					 {
					printf("û�п��Ը��µĹ̼�!\r\n");
					//LCD_ShowString(60,210,200,16,16,"No APP!");
					 }
				clearflag=7;//��־��������ʾ,��������7*300ms�������ʾ									 
			}
			/******************************************************************************************/
			
			
			/*******************************************************************************************/
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)
			{
				if(applenth)
				{																	 
					printf("�̼�������!\r\n");    
					//LCD_ShowString(60,210,200,16,16,"APP Erase Successed!");
					applenth=0;
				}else 
				{
					printf("û�п�������Ĺ̼�!\r\n");
					//LCD_ShowString(60,210,200,16,16,"No APP!");
				}
				clearflag=7;//��־��������ʾ,��������7*300ms�������ʾ									 
			}
			/*********************************************************************************************/
			
			/*********************************************************************************************/
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)== 0)
			{
				printf("��ʼִ��FLASH�û�����!!\r\n");
				if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
				{	 
					iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
				}
				else 
				{
					printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");  
				}									 
				clearflag=7;//��־��������ʾ,��������7*300ms�������ʾ	  
			}
			/**********************************************************************************************/
			
			/**********************************************************************************************/
//			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6) ==0)
//			{
//					printf("��ʼִ��SRAM�û�����!!\r\n");
//					if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x20000000)//�ж��Ƿ�Ϊ0X20XXXXXX.
//					{	 
//							iap_load_app(0X20001000);//SRAM��ַ
//					}
//					else 
//					{
//							printf("��SRAMӦ�ó���,�޷�ִ��!\r\n");
//					}									 
//					clearflag=7;//��־��������ʾ,��������7*300ms�������ʾ	 
//			}				   
	 }   	   
 }

