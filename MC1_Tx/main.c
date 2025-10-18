/*AUTHOR : MO'MEN AHMED & MOHANED HOSSAM
 *
 * DATE  : 14/8/2023
 *
 * DESCRIPTION : TRANSMITTER MICROCONTROLLER main file */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/RCC/RCC_int.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/SYSTICK/SYSTICK_int.h"

extern u8 HexFile[][45];

#define MC1_READY   0x55
#define MC2_READY   0x66

#define CHARACTER_SENT  0X10

#define RECORD_OK      0x05

u8 num_records_sent=0;

int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClock(RCC_AHB1,RCC_GPIO_A);
	MRCC_vEnableClock(RCC_APB2, RCC_USART1);

//	MSTK_vInit();

	MGPIO_Config_t led={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin2
	};

	MGPIO_vInit(&led);

	MGPIO_Config_t ledRec1={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin0
	};

	MGPIO_vInit(&ledRec1);

	MGPIO_Config_t ledRec2={
			.mode = Digital_output, .output_speed = Low,
			.output_type = Push_pull, .Port_ID = GPIO_Port_A,
			.Pin_ID = GPIO_Pin1
	};

	MGPIO_vInit(&ledRec2);


	MUART_vInit(UART1);

	MUART_vTransmitByteSynch(UART1, MC1_READY);

	u8 RecByte = MUART_u8ReceiveByteSynchBlocking(UART1);

	while(RecByte != MC2_READY)
	{
		RecByte = MUART_u8ReceiveByteSynchBlocking(UART1);
	}
	MGPIO_vSetPin(led.Port_ID, led.Pin_ID, LOGIC_ONE);

	MUART_vTransmitString(UART1,"OK");

	u8 i = 0;
	u8 j=0;
	for (; i<225; i++)
	{

		for ( ;HexFile[i][j] != '\0'; j++)
		{
			//SYNCH
			while(MUART_u8ReceiveByteSynchBlocking(UART1) != CHARACTER_SENT);
			MUART_vTransmitByteSynch(UART1,CHARACTER_SENT);
			MUART_vTransmitByteSynch(UART1,HexFile[i][j]);
		}
		j=0;
		while(MUART_u8ReceiveByteSynchBlocking(UART1) != CHARACTER_SENT);
		MUART_vTransmitByteSynch(UART1,CHARACTER_SENT);
		MUART_vTransmitByteSynch(UART1,'\0');

//		}
		while(MUART_u8ReceiveByteSynchBlocking(UART1) != RECORD_OK);

//		MGPIO_vSetPin(ledRec1.Port_ID, ledRec1.Pin_ID, LOGIC_ONE);
	}
	while(1)
	{

	}

}
