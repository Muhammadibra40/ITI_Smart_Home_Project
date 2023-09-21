#include "main.h"

u8 Global_u8Trails = 0;

u8 HELPER_u8CheckMemory(u8 Copy_u8PSWD_ADD)
{
    u8 HELPER_u8Index, HELPER_u8Data, HELPER_u8PSWDFlag = 0;

    for (HELPER_u8Index = 0; HELPER_u8Index < 8; ++HELPER_u8Index)//To check if eeprom is empty
	{
		HELPER_u8Data = EEPROM_u8ReadDataByte(Copy_u8PSWD_ADD + HELPER_u8Index);

		if (HELPER_u8Data != 0xFF)
		{
			HELPER_u8PSWDFlag = 1;//not first time// there's a password
            break;
		}
	}

    return (HELPER_u8PSWDFlag);
}

void HELPER_voidSetPSWD(void)
{
	u8 HELPER_u8Index, HELPER_u8Data;

	LCD_voidSendString("Set Admin's");
	LCD_voidSetLocation(LCD_LINE2, 0);
	LCD_voidSendString("password: ");

	for (HELPER_u8Index = 0; HELPER_u8Index < 4; ++HELPER_u8Index)
	{
		HELPER_u8Data = KPD_u8GetPressedKey();
		while (HELPER_u8Data == KPD_CHECK_PRESSED_OR_NOT)
		{
			HELPER_u8Data = KPD_u8GetPressedKey();
		}

		if (HELPER_u8Data!= KPD_CHECK_PRESSED_OR_NOT)
		{
			LCD_voidSendString("*");

			EEPROM_voidWriteDataByte(PSWD_ADD + HELPER_u8Index, HELPER_u8Data);
			_delay_ms(100);
		}
	}

	LCD_voidSendCommand(CLEAR);
	_delay_ms(2);

	LCD_voidSendString("Set guest's");
	LCD_voidSetLocation(LCD_LINE2, 0);
	LCD_voidSendString("password: ");

	for (HELPER_u8Index = 4; HELPER_u8Index < 8; ++HELPER_u8Index)
	{
		HELPER_u8Data = KPD_u8GetPressedKey();
		while (HELPER_u8Data == KPD_CHECK_PRESSED_OR_NOT)
		{
			HELPER_u8Data = KPD_u8GetPressedKey();
		}

		if (HELPER_u8Data!= KPD_CHECK_PRESSED_OR_NOT)
		{
			LCD_voidSendString("*");

			EEPROM_voidWriteDataByte(PSWD_ADD + HELPER_u8Index, HELPER_u8Data);
			_delay_ms(100);
		}
	}
	LCD_voidSendCommand(CLEAR);
	_delay_ms(2);

}

u8 HELPER_u8CheckPSWD(void)
{
 u8 HELPER_u8Mode, HELPER_u8Index, HELPER_u8Data;
 u8 HELPER_u8Flag = 0, HELPER_u8Digit;

 if (Global_u8Trails == 3)
 {
  LCD_voidSendString("0 Trials Left");
  _delay_ms(500);

  LCD_voidSendCommand(CLEAR);
  _delay_ms(2);

  for (HELPER_u8Index = 10; HELPER_u8Index > 0; HELPER_u8Index--)
  {
   LCD_voidSendString("Please wait");
   LCD_voidSetLocation(LCD_LINE2, 0);
   LCD_voidSendNumber(HELPER_u8Index);
   LCD_voidSendString(" Seconds Left");
   _delay_ms(300);

   LCD_voidSendCommand(CLEAR);
   _delay_ms(2);
  }

  Global_u8Trails = 0;

  return (HELPER_u8CheckPSWD());
 }

 LCD_voidSendString("Choose your mode:");
 LCD_voidSetLocation(LCD_LINE2, 0);
 LCD_voidSendString("1-Admin 2-Guest");

 HELPER_u8Mode = KPD_u8GetPressedKey();
 while (HELPER_u8Mode == KPD_CHECK_PRESSED_OR_NOT)
 {
  HELPER_u8Mode = KPD_u8GetPressedKey();
 }

 LCD_voidSendCommand(CLEAR);
 _delay_ms(2);

 if (HELPER_u8Mode == '1')
 {
  LCD_voidSetLocation(LCD_LINE1, 3);
  LCD_voidSendString("Admin Mode");
  LCD_voidSetLocation(LCD_LINE2, 0);
  LCD_voidSendString("password: ");

  for (HELPER_u8Index = 0; HELPER_u8Index < 4; ++HELPER_u8Index)
  {
   HELPER_u8Digit = KPD_u8GetPressedKey();
   while (HELPER_u8Digit == KPD_CHECK_PRESSED_OR_NOT)
   {
    HELPER_u8Digit = KPD_u8GetPressedKey();
   }

   if (HELPER_u8Digit!= KPD_CHECK_PRESSED_OR_NOT)
   {
    LCD_voidSendString("*");
    _delay_ms(200);
    HELPER_u8Data = EEPROM_u8ReadDataByte(PSWD_ADD + HELPER_u8Index);
    _delay_ms(200);

    if (HELPER_u8Data != HELPER_u8Digit)
    {
     HELPER_u8Flag = 1;
    }
   }
  }

  LCD_voidSendCommand(CLEAR);
  _delay_ms(2);

  if (HELPER_u8Flag)
  {
   LCD_voidSendString("Wrong password!");
   _delay_ms(300);
   LCD_voidSendCommand(CLEAR);
   _delay_ms(2);

   Global_u8Trails++;

   return (HELPER_u8CheckPSWD());
  }

  else
  {
   Global_u8Trails = 0;
   return (1);
  }
 }

 if (HELPER_u8Mode == '2')
 {
  LCD_voidSetLocation(LCD_LINE1, 3);
  LCD_voidSendString("Guest Mode");
  LCD_voidSetLocation(LCD_LINE2, 0);
  LCD_voidSendString("password: ");

  for (HELPER_u8Index = 4; HELPER_u8Index < 8; ++HELPER_u8Index)
  {
   HELPER_u8Digit = KPD_u8GetPressedKey();
   while (HELPER_u8Digit == KPD_CHECK_PRESSED_OR_NOT)
   {
    HELPER_u8Digit = KPD_u8GetPressedKey();
   }

   if (HELPER_u8Digit!= KPD_CHECK_PRESSED_OR_NOT)
   {
    LCD_voidSendString("*");
    _delay_ms(200);
    HELPER_u8Data = EEPROM_u8ReadDataByte(PSWD_ADD + HELPER_u8Index);
    _delay_ms(200);

    if (HELPER_u8Data != HELPER_u8Digit)
    {
     HELPER_u8Flag = 1;
    }
   }
  }

  LCD_voidSendCommand(CLEAR);
  _delay_ms(2);

  if (HELPER_u8Flag)
  {
   LCD_voidSendString("Wrong password!");
   _delay_ms(300);
   LCD_voidSendCommand(CLEAR);
   _delay_ms(2);

   Global_u8Trails++;

   return (HELPER_u8CheckPSWD());
  }

  else
  {
   Global_u8Trails = 0;
   return (2);
  }
 }
 else
 {
  LCD_voidSendCommand(CLEAR);
  _delay_ms(2);

  LCD_voidSetLocation(LCD_LINE1, 3);
  LCD_voidSendString("Wrong Mode!");
  _delay_ms(300);
  LCD_voidSendCommand(CLEAR);
  _delay_ms(2);
  return (HELPER_u8CheckPSWD());
 }
}

u8 HELPER_u8AdminMenu(void)
{
    u8 HELPER_u8Data;

    LCD_voidSendString("Welcome Home");
    _delay_ms(1000);

    LCD_voidSendCommand(CLEAR);
    _delay_ms(2);

    LCD_voidSetLocation(LCD_LINE1, 0);
    LCD_voidSendString("1:Room1");
    LCD_voidSetLocation(LCD_LINE1, 8);
    LCD_voidSendString("2:Room2");
    LCD_voidSetLocation(LCD_LINE2, 0);
    LCD_voidSendString("3:Room3");
    LCD_voidSetLocation(LCD_LINE2, 8);
    LCD_voidSendString("4:AC");

    HELPER_u8Data = KPD_u8GetPressedKey();
    while (HELPER_u8Data == KPD_CHECK_PRESSED_OR_NOT)
    {
        HELPER_u8Data = KPD_u8GetPressedKey();
    }

    LCD_voidSendCommand(CLEAR);
    _delay_ms(2);

    return (HELPER_u8Data);
}

u8 HELPER_u8GuestMenu(void)
{
    u8 HELPER_u8Data;

    LCD_voidSetLocation(LCD_LINE1, 0);
	LCD_voidSendString("Welcome To Our");
	LCD_voidSetLocation(LCD_LINE2, 4);
	LCD_voidSendString("House");
    _delay_ms(1000);

    LCD_voidSendCommand(CLEAR);
    _delay_ms(2);

    LCD_voidSetLocation(LCD_LINE1, 0);
    LCD_voidSendString("1:Room1");
    LCD_voidSetLocation(LCD_LINE1, 8);
    LCD_voidSendString("2:Room2");
    LCD_voidSetLocation(LCD_LINE2, 0);
    LCD_voidSendString("3:Room3");

    HELPER_u8Data = KPD_u8GetPressedKey();
    while (HELPER_u8Data == KPD_CHECK_PRESSED_OR_NOT)
    {
        HELPER_u8Data = KPD_u8GetPressedKey();
    }

    LCD_voidSendCommand(CLEAR);
    _delay_ms(2);

    return (HELPER_u8Data);
}

u8 HELPER_u8SendData(u8 Copy_u8Data, u8 Copy_u8Mode)
{
    u8 HELPER_u8Data = 0, HELPER_u8ACMode, HELPER_u8Digit;

    switch(Copy_u8Data)
    {
        case '1':
            LCD_voidSetLocation(LCD_LINE1, 0);
            LCD_voidSendString("Room 1");
            LCD_voidSetLocation(LCD_LINE2, 0);
            LCD_voidSendString("5: ON");
            LCD_voidSetLocation(LCD_LINE2, 7);
            LCD_voidSendString("6: OFF");

            HELPER_u8Data = KPD_u8GetPressedKey();
            while (HELPER_u8Data == KPD_CHECK_PRESSED_OR_NOT)
            {
                HELPER_u8Data = KPD_u8GetPressedKey();
            }
            break;
        case '2':
            LCD_voidSetLocation(LCD_LINE1, 0);
            LCD_voidSendString("Room 2");
            LCD_voidSetLocation(LCD_LINE2, 0);
            LCD_voidSendString("5: ON");
            LCD_voidSetLocation(LCD_LINE2, 7);
            LCD_voidSendString("6: OFF");

            HELPER_u8Data = KPD_u8GetPressedKey();
            while (HELPER_u8Data == KPD_CHECK_PRESSED_OR_NOT)
            {
                HELPER_u8Data = KPD_u8GetPressedKey();
            }
            break;
        case '3':
            LCD_voidSetLocation(LCD_LINE1, 0);
            LCD_voidSendString("Room 3");
            LCD_voidSetLocation(LCD_LINE2, 0);
            LCD_voidSendString("5: ON");
            LCD_voidSetLocation(LCD_LINE2, 7);
            LCD_voidSendString("6: OFF");

            HELPER_u8Data = KPD_u8GetPressedKey();
            while (HELPER_u8Data == KPD_CHECK_PRESSED_OR_NOT)
            {
                HELPER_u8Data = KPD_u8GetPressedKey();
            }
            break;
        case '4':
            if (Copy_u8Mode == 1)
            {
                LCD_voidSetLocation(LCD_LINE1, 0);
                LCD_voidSendString("AC");
                LCD_voidSetLocation(LCD_LINE2, 0);
                LCD_voidSendString("5: ON");
                LCD_voidSetLocation(LCD_LINE2, 7);
                LCD_voidSendString("6: OFF");

                HELPER_u8ACMode = KPD_u8GetPressedKey();
                while (HELPER_u8ACMode == KPD_CHECK_PRESSED_OR_NOT)
                {
                    HELPER_u8ACMode= KPD_u8GetPressedKey();
                }

                LCD_voidSendCommand(CLEAR);
				_delay_ms(2);

                if (HELPER_u8ACMode == '5')
                {
                    LCD_voidSetLocation(LCD_LINE1, 0);
                    LCD_voidSendString("Set Temperature:");
                    LCD_voidSetLocation(LCD_LINE2, 2);
                    LCD_voidSendString("C");
                    LCD_voidSetLocation(LCD_LINE2, 0);//27

                    HELPER_u8Digit = KPD_u8GetPressedKey();
                    while (HELPER_u8Digit == KPD_CHECK_PRESSED_OR_NOT)
                    {
                        HELPER_u8Digit = KPD_u8GetPressedKey();
                    }//'2'
                    LCD_voidSendChar(HELPER_u8Digit);
                    HELPER_u8Data = (HELPER_u8Digit - '0')*(10);//20 '2' - '0'

                    HELPER_u8Digit= KPD_u8GetPressedKey();
                    while (HELPER_u8Digit == KPD_CHECK_PRESSED_OR_NOT)
                    {
                        HELPER_u8Digit = KPD_u8GetPressedKey();
                    }
                    LCD_voidSendChar(HELPER_u8Digit);
                    HELPER_u8Data += (HELPER_u8Digit - '0');//20+7
					_delay_ms(500);
                }

                else if (HELPER_u8ACMode == '6')
                {
                    HELPER_u8Data = 255;
                }
            }
            break;
    }
    LCD_voidSendCommand(CLEAR);
    _delay_ms(2);

    return (HELPER_u8Data);
}

u8 HELPER_u8MenuFlag(void)
{
    u8 HELPER_u8Data = 0, HELPER_u8Flag = 0;

    LCD_voidSetLocation(LCD_LINE1, 0);
    LCD_voidSendString("1:Previous Menu");
    LCD_voidSetLocation(LCD_LINE2, 0);
    LCD_voidSendString("2:Log Out");

    HELPER_u8Data = KPD_u8GetPressedKey();
    while (HELPER_u8Data == KPD_CHECK_PRESSED_OR_NOT)
    {
        HELPER_u8Data = KPD_u8GetPressedKey();
    }

    LCD_voidSendCommand(CLEAR);
    _delay_ms(2);

    if(HELPER_u8Data == '1')
    {
        HELPER_u8Flag = 1;
    }
    else if(HELPER_u8Data == '2')
    {
        HELPER_u8Flag = 0;
    }

    LCD_voidSendCommand(CLEAR);
    _delay_ms(2);

    return (HELPER_u8Flag);
}

