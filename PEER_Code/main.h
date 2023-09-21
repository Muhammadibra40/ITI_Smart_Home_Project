#ifndef MAIN_H
#define MAIN_H

#define F_CPU       8000000UL
#define Trigger_pin	PD4

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "LIB/BIT_Math.h"
#include "LIB/STD_Types.h"

#include "MCAL/INT/INT.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/UART/UART.h"

#include "HELPER.h"

#endif
