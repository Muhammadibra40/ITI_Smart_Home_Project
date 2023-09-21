#include "main.h"
									/* Master */
int main(void)
{
	u8 Local_u8PSWDFlag = 0, Local_u8Mode;
	u8 Local_u8Data = 0, Local_u8MenuFlag = 0;

	LCD_voidInit();
	KPD_voidInit();

	UART_voidInit();
	TWI_voidMasterInit();
	_delay_ms(1000);

	DIO_voidSetPinDirection(DIO_PORTD, PIN0, DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTD, PIN1, DIO_OUTPUT);

	LCD_voidSetLocation(LCD_LINE1, 6);
	LCD_voidSendString("Hi");
	_delay_ms(1000);

	Local_u8PSWDFlag = HELPER_u8CheckMemory(PSWD_ADD);

	LCD_voidSendCommand(CLEAR);
	_delay_ms(2);

	if (!Local_u8PSWDFlag)//0//no password
	{
		HELPER_voidSetPSWD();
		LCD_voidSendCommand(CLEAR);
		_delay_ms(2);
	}

	while (1)
	{
		if(Local_u8MenuFlag == 0)
		{
			Local_u8Mode = HELPER_u8CheckPSWD();
		}

		if (Local_u8Mode == 1) //admin
		{
			Local_u8Data = HELPER_u8AdminMenu();
		}
		else if (Local_u8Mode == 2) //guest
		{
			Local_u8Data = HELPER_u8GuestMenu();
		}

		SendInstruction(Local_u8Data, SLAVE);

		Local_u8Data = HELPER_u8SendData(Local_u8Data, Local_u8Mode);

		SendInstruction(Local_u8Data, SLAVE);

		Local_u8MenuFlag = HELPER_u8MenuFlag();
	}

	return 0;
}
