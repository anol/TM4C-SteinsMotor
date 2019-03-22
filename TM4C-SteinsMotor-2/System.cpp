/*
 * System.cpp
 *
 *  Created on: 21. mar. 2019
 *      Author: Drift
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include <System.h>

System::System()
{
    // TODO Auto-generated constructor stub

}

System::~System()
{
    // TODO Auto-generated destructor stub
}

void System::Delay(int seconds){
    // This function provides a means of generating a constant length
    // delay.  The function delay (in cycles) = 3 * parameter.
    SysCtlDelay((SysCtlClockGet() * seconds) / 3);
}

void System::Sleep(int milliseconds){
    // This function provides a means of generating a constant length
    // delay.  The function delay (in cycles) = 3 * parameter.
    SysCtlDelay((SysCtlClockGet() * milliseconds) / 3000);
}
