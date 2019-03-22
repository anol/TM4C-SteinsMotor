/*
 * System.cpp
 *
 *  Created on: 21. mar. 2019
 *      Author: Drift
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/fpu.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include <System.h>

System::System()
{
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    FPULazyStackingEnable();
    // Set the clocking to run directly from the crystal.
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
}

System::~System()
{
    // TODO Auto-generated destructor stub
}

void System::Delay(int seconds)
{
    // This function provides a means of generating a constant length
    // delay.  The function delay (in cycles) = 3 * parameter.
    SysCtlDelay((SysCtlClockGet() * seconds) / 3);
}

void System::Sleep(int milliseconds)
{
    // This function provides a means of generating a constant length
    // delay.  The function delay (in cycles) = 3 * parameter.
    SysCtlDelay((SysCtlClockGet() * milliseconds) / 3000);
}
