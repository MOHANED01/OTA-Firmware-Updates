/*
 * HEX_PARSER_prog.c
 *
 *  Created on: Sep 2, 2023
 *      Author: Dell
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "HEX_PARSER_Interface.h"

u16 Buffer[100];

static u8 HexParser_u8Ascii2Hex (u8 A_u8AsciiChar)
{
	u8 Local_u8HexChar ;
	if(A_u8AsciiChar >= '0' && A_u8AsciiChar <= '9')
	{
		Local_u8HexChar = A_u8AsciiChar - '0';
	}
	else if(A_u8AsciiChar >= 'A' && A_u8AsciiChar <= 'F')
	{
		Local_u8HexChar = A_u8AsciiChar - 'A' + 10;
	}
	return Local_u8HexChar;
}

void HexParser_vParseData (u8 * Data)
{
	//FIRST TAKE THE CC (CHARACTER COUNT) FROM THE RECORD (INDEX 1,2)
	u8 CC_Low, CC_High, CC;
	CC_Low  = HexParser_u8Ascii2Hex(Data[2]);
	CC_High = HexParser_u8Ascii2Hex(Data[1]);
	CC = CC_Low | (CC_High << 4);

	//THEN TAKE THE LOW ADDRESS FROM THE RECORD (INDEX 3,4,5,6)
	u8 digit0_Add, digit1_Add, digit2_Add, digit3_Add;
	u16 LowAddress;
	u32 ActualAddress;
	digit3_Add = HexParser_u8Ascii2Hex(Data[3]);
	digit2_Add = HexParser_u8Ascii2Hex(Data[4]);
	digit1_Add = HexParser_u8Ascii2Hex(Data[5]);
	digit0_Add = HexParser_u8Ascii2Hex(Data[6]);
    LowAddress = digit0_Add | (digit1_Add << 4) |
    	                      (digit2_Add << 8) | (digit3_Add << 12);

    ActualAddress = LowAddress | FLASH_BASE_ADDRESS;

    //LOOPING ON THE DATA AND SAVING IT INTO A BUFFER TO SEND IT TO FLASH
    //INDEX : 9 TILL 9 + 4*(CC/2)
    u8 digit0_Data, digit1_Data, digit2_Data, digit3_Data;
    for(u8 i = 0; i< (CC/2); i++)
    {
       digit3_Data = HexParser_u8Ascii2Hex(Data[9  + 4*i]);
       digit2_Data = HexParser_u8Ascii2Hex(Data[10 + 4*i]);
       digit1_Data = HexParser_u8Ascii2Hex(Data[11 + 4*i]);
       digit0_Data = HexParser_u8Ascii2Hex(Data[12 + 4*i]);

       Buffer[i] = (digit0_Data<<8) | (digit1_Data << 12) |
    		                     (digit2_Data << 0) | (digit3_Data << 4);
    }

    FMI_WriteOperationData WriteData = {
    		.StartAddress = ActualAddress, .PSize = FMI_HalfWord,
			.DataSize = (CC/2), .Data = Buffer
    };

    MFMI_vFlashWrite(&WriteData);
}

void HexEraseAppArea(void)
{
	MFMI_vEraseAppArea(FMI_SEC1);
}



