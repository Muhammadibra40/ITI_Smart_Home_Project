#include "main.h"

u16 Global_u16TimerOverflow = 0;
u8 Global_u8RcvData = 0;

int main(void)
{
	u8 Local_u8Room = 0, Local_u8SetTemp = 0;
	u8  *Local_ptru8Room, *Local_ptru8SetTemp;

	u16 Local_u16DigitalValueTorch, Local_u16AnalogValueTorch;
	u16 Local_u16DigitalValueTemp, Local_u16AnalogValueTemp,Local_u16ValueTemp;

	Local_ptru8Room = &Local_u8Room;
	Local_ptru8SetTemp = &Local_u8SetTemp;

//ultrasonic
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN3, DIO_OUTPUT);
	DIO_voidSetPinValue(DIO_PORTA, DIO_PIN3, DIO_LOW);
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
	DIO_voidSetPortValue(DIO_PORTD, 0xFF);
//uart
	DIO_voidSetPinDirection(DIO_PORTD, PIN0, DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTD, PIN1, DIO_OUTPUT);
//motor
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_OUTPUT);
	DIO_voidSetPinValue(DIO_PORTD, DIO_PIN2, DIO_LOW);
//buzzer
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN3, DIO_OUTPUT);
	DIO_voidSetPinValue(DIO_PORTD, DIO_PIN3, DIO_LOW);
//emergency lamp
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN4, DIO_OUTPUT);
//lamps
	DIO_voidSetPinDirection(DIO_PORTC, PIN0, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC, PIN1, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC, PIN2, DIO_OUTPUT);

    ADC_voidInit(ADC_DIV_64);
    UART_voidInit();
    sei();

    TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
    TCCR1A = 0;

    while (1)
    {
		Local_u16DigitalValueTorch = ADC_u16GetDigitalValue(ADC_Channel_0);
        Local_u16AnalogValueTorch = ((Local_u16DigitalValueTorch * 5000UL) / 1023);

		Local_u16DigitalValueTemp = ADC_u16GetDigitalValue(ADC_Channel_1);
        Local_u16AnalogValueTemp = ((Local_u16DigitalValueTemp * 5000UL) / 1023);
        Local_u16ValueTemp = Local_u16AnalogValueTemp / 10;

        HELPER_voidUSOperation(&Global_u16TimerOverflow);
        HELPER_voidBuzzerOperation(Local_u16ValueTemp);
        HELPER_voidLDROperation(Local_u16AnalogValueTorch);

		if(Local_u8Room == 4)
		{
			HELPER_voidACOperation(Global_u8RcvData, Local_ptru8Room,
								   Local_ptru8SetTemp, Local_u16ValueTemp);
		}
		if(Local_u8SetTemp > Local_u16ValueTemp)
		{
			DIO_voidSetPinValue(DIO_PORTD, PIN2, DIO_LOW);
		}

		HELPER_voidOptions(Global_u8RcvData, Local_ptru8Room);
	}
    return 0;
}

ISR(USART_RXC_vect)
{
    Global_u8RcvData = UDR;
}

ISR(TIMER1_OVF_vect)
{
	Global_u16TimerOverflow++;	/* Increment Timer Overflow count */
}
