#include "main.h"

u8 GetChioce(void)
{
	u8 Local_u8_PressedKey = 0;
	do
	{
		Local_u8_PressedKey = KPD_u8GetPressedKey();
		if (Local_u8_PressedKey != 0)
		{
			return Local_u8_PressedKey;
		}


	} while (1);
}


void SendInstruction(u8 Copy_pu8Instruction, u8 Copy_pu8SlaveSelect)
{
	switch (Copy_pu8SlaveSelect)
	{
	case 0:

		UART_voidSendData(Copy_pu8Instruction);
		break;
	}
}

u8 Receive(void)
{
	u8 Copy_u8Value = 0;
	while(1)
	{
		Copy_u8Value = UART_u8ReceiveData();
		if (Copy_u8Value != 0)
			return Copy_u8Value;
	}
}

