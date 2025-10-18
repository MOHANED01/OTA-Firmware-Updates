/*AUTHOR : MO'MEN AHMED & MOHANED HOSSAM
 *
 * DATE  : 14/8/2023
 *
 * DESCRIPTION : RECEIVER MICROCONTROLLER main file */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/RCC/RCC_int.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "APP/HEX_PARSER/HEX_PARSER_Interface.h"
#include "MCAL/SYSTICK/SYSTICK_int.h"
#include "MCAL/SCB/SCB_Interface.h"
#include "MCAL/UART/UART_Interface.h"

#define MC1_READY   0x55
#define MC2_READY   0x66

#define CHARACTER_SENT  0X10

#define RECORD_OK      0x05


volatile u8 TimeoutFlag = 0;
u8 ReceiveBuffer[50]={0};
u8 ReceiveCounter = 0;
u8 EraseFlag = 0;  //ONE WAY FLAG , SET ONLY ONCE

//MAKING NEW DATATYPE FOR A POINTER TO FUNCTION
typedef void (*funtion_ptr)(void);

//DECLARING A POINTER TO FUNCTION FOR APP PROJECT
funtion_ptr App_Project;

void Systick_CallBack(void)
{
  TimeoutFlag = 1;

  MSCB_vSetResetVectAddress(0x08004000);

  App_Project = *(funtion_ptr*)(0x08004004);

  App_Project();
}

int main(void)
{

	MRCC_vInit();
	MRCC_vEnableClock(RCC_AHB1, RCC_GPIO_A);
	MRCC_vEnableClock(RCC_APB2, RCC_USART1);

	MSTK_vInit();
	MSTK_vSetIntervalSingle(50000,Systick_CallBack);
	MUART_vInit(UART1);

	MGPIO_Config_t led={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin1
	};

	MGPIO_vInit(&led);

	MGPIO_Config_t led2={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin2
	};

	MGPIO_vInit(&led2);

	MGPIO_Config_t led3={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin3
	};

	MGPIO_vInit(&led3);

	MGPIO_Config_t led4={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin4
	};

	MGPIO_vInit(&led4);

	MGPIO_Config_t led5={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin5
	};

	MGPIO_vInit(&led5);

	MGPIO_Config_t led6={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin6
	};

	MGPIO_vInit(&led6);

	MGPIO_Config_t led7={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin7
	};

	MGPIO_vInit(&led7);


	u8 receivedByte = MUART_u8ReceiveByteSynchNonBlocking(UART1);

	while (receivedByte != MC1_READY)
	{
		receivedByte = MUART_u8ReceiveByteSynchNonBlocking(UART1);
	}

	MGPIO_vSetPin(led.Port_ID, led.Pin_ID, LOGIC_ONE);

	MUART_vTransmitByteSynch(UART1, MC2_READY);
	u8 recOk[5] = {0};
	while(recOk[0] != 'O' && recOk[1] != 'K')
	{
		MUART_vReceiveStringSynchNonBlocking(UART1,recOk,3);
	}
//	MGPIO_vSetPin(led3.Port_ID, led3.Pin_ID, 1);


	u8 Local_u8UARTRxStatus = 0;
	while(TimeoutFlag == 0)
	{
//	   Local_u8UARTRxStatus = MUART_u8ReceiveByteAsych_(UART1,&ReceiveBuffer[ReceiveCounter]);
		MUART_vTransmitByteSynch(UART1,CHARACTER_SENT);
		while(MUART_u8ReceiveByteSynchBlocking(UART1) != CHARACTER_SENT);
		ReceiveBuffer[ReceiveCounter] = MUART_u8ReceiveByteSynchBlocking(UART1);
//		//CHECK IF I HAVE RECEIVED SOMETHING ON UART OR NOT
//	   if(Local_u8UARTRxStatus == 1)
//	   {
		   if (EraseFlag == 0)
		   {
			   EraseFlag = 1;
			   HexEraseAppArea();

		   }
		   else{
		   }
		   //I RECEIVED BYTE , STOP THE TIMER
		   MSTK_vStopTimer();

		   //CHECK IF THE RECORD HAS BEEN FINISHED OR NOT
		   if(ReceiveBuffer[0] == ':' && ReceiveBuffer[1] == '0' && ReceiveBuffer[2] == '2'
				 &&  ReceiveBuffer[3] == '0' && ReceiveBuffer[4] == '0' && ReceiveBuffer[5] == '0' )
		   {
//			   MGPIO_vSetPin(led4.Port_ID, led4.Pin_ID, 1);
		   }

			   if(ReceiveBuffer[ReceiveCounter] == '\0')
			   {
				   MGPIO_vSetPin(led5.Port_ID, led5.Pin_ID, 1);
				   HexParser_vParseData(ReceiveBuffer);
				   ReceiveCounter = 0;
//				   MGPIO_vSetPin(led5.Port_ID, led5.Pin_ID, 1);
//				   MUART_vTransmitString(UART1,"OK");
//				   while(MUART_u8ReceiveByteSynchBlocking(UART1) != RECORD_OK);

				   MUART_vTransmitByteSynch(UART1,RECORD_OK);
			   }
			   else
			   {
				   ReceiveCounter ++;
			   }

		   //CHECK IF IT IS THE END OF FILE OR NOT
		   if(ReceiveBuffer[8] == '1')
		   {
			   MGPIO_vSetPin(led6.Port_ID, led6.Pin_ID, 1);
			   Systick_CallBack();
		   }
//	   }
//	   else
//	   {
//	   }

	}
}
