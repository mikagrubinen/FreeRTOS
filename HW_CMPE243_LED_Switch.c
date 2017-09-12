Venkat Raja Iyer & Miroslav Grubic

period_callbacks.cpp at SW Board

#include <stdint.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "eint.h"
#include "gpio.hpp"

const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);
const uint32_t PERIOD_MONITOR_TASK_STACK_SIZE_BYTES = (512 * 3);


SemaphoreHandle_t buttonPress = NULL;

GPIO myPinInput(P2_2);
GPIO myPinOutput(P2_0);


void my_button_press_isr(void)
{
    long yield = 0;
    xSemaphoreGiveFromISR(buttonPress, &yield);
    portYIELD_FROM_ISR(yield);
}

bool period_init(void)
{
	myPinInput.setAsInput();
	myPinOutput.setAsOutput();

	buttonPress = xSemaphoreCreateBinary();
	eint3_enable_port2(2, eint_rising_edge, my_button_press_isr);
    return true; // Must return true upon success
}

bool period_reg_tlm(void)
{
    return true; // Must return true upon success
}

void period_10Hz(uint32_t count)
{
	static uint32_t counter;
	if (xSemaphoreTake(buttonPress, 0))
	{
		counter = count;
		LE.on(1);
		myPinOutput.setHigh();
	}
	if(counter+5 == count)
	{
		LE.off(1);
		myPinOutput.setLow();
	}
}


period_callbacks.cpp at LED Board

#include <stdint.h>
#include "io.hpp"
#include "periodic_callback.h"
#include "gpio.hpp"

GPIO myPinInput(P2_0);
GPIO myPinOutput(P2_1);

const uint32_t PERIOD_TASKS_STACK_SIZE_BYTES = (512 * 4);
const uint32_t PERIOD_DISPATCHER_TASK_STACK_SIZE_BYTES = (512 * 3);

bool period_init(void)
{
	myPinInput.setAsInput();
	myPinOutput.setAsOutput();
    return true; // Must return true upon success
}

bool period_reg_tlm(void)
{
    return true; // Must return true upon success
}

void period_100Hz(void)
{
	if(myPinInput.read())
		myPinOutput.setLow();
	else
		myPinOutput.setHigh();
}
