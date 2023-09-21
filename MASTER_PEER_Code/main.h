#ifndef MAIN_H
#define MAIN_H

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "LIB/BIT_Math.h"
#include "LIB/STD_Types.h"

#include "MCAL/DIO/DIO.h"
#include "MCAL/UART/UART.h"
#include "MCAL/I2C/I2C.h"

#include "HAL/LCD/LCD.h"
#include "HAL/KEYPAD/KEYPAD.h"
#include "HAL/EEPROM/EEPROM.h"

#include "MENU.h"

#define PSWD_ADD 100
#define SLAVE    0

#endif
