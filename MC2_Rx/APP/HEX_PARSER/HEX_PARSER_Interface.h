/*
 * HEX_PARSER_Interface.h
 *
 *  Created on: Sep 2, 2023
 *      Author: Dell
 */

#ifndef APP_HEX_PARSER_HEX_PARSER_INTERFACE_H_
#define APP_HEX_PARSER_HEX_PARSER_INTERFACE_H_

#include "../../MCAL/FMI/FMI_Interface.h"

#define FLASH_BASE_ADDRESS 0x08000000

//THIS FUNCTION TAKES ONE RECORD OF HEX FILE
void HexParser_vParseData (u8 * Data);
void HexEraseAppArea(void);


#endif /* APP_HEX_PARSER_HEX_PARSER_INTERFACE_H_ */
