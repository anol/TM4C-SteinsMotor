/*
 * PwmGenerator.cpp
 *
 *  Created on: 21. mar. 2019
 *      Author: Drift
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include <PwmGenerator.h>

PwmGenerator::PwmGenerator()
{
    // TODO Auto-generated constructor stub

}

PwmGenerator::~PwmGenerator()
{
    // TODO Auto-generated destructor stub
}

void PwmGenerator::Initialize()
{
    // Set the clocking to run directly from the external crystal/oscillator.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    // Set the PWM clock to the system clock.
    SysCtlPWMClockSet (SYSCTL_PWMDIV_1);
}

void PwmGenerator::Invert(bool invert)
{
    PWMOutputInvert(PWM0_BASE, PWM_OUT_0_BIT, invert);
}

void PwmGenerator::SetPulseWidth(int percent)
{
    uint32_t ui32Width = PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) * percent / 100;
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, ui32Width);
}

void PwmGenerator::Enable()
{
    // The PWM peripheral must be enabled for use.
    SysCtlPeripheralEnable (SYSCTL_PERIPH_PWM0);
    // For this example PWM0 is used with PortB Pin6.  The actual port and
    // pins used may be different on your part, consult the data sheet for
    // more information.
    // GPIO port B needs to be enabled so these pins can be used.
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOB);
    // Configure the GPIO pin muxing to select PWM00 functions for these pins.
    // This step selects which alternate function is available for these pins.
    // This is necessary if your part supports GPIO pin function muxing.
    // Consult the data sheet to see which functions are allocated per pin.
    GPIOPinConfigure (GPIO_PB6_M0PWM0);
    // Configure the PWM function for this pin.
    // Consult the data sheet to see which functions are allocated per pin.
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
    // Configure the PWM0 to count up/down without synchronization.
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    // Set the PWM period to 250Hz.  To calculate the appropriate parameter
    // use the following equation: N = (1 / f) * SysClk.  Where N is the
    // function parameter, f is the desired frequency, and SysClk is the
    // system clock frequency.
    // In this case you get: (1 / 250Hz) * 16MHz = 64000 cycles.  Note that
    // the maximum period you can set is 2^16.
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 64000);
    SetPulseWidth(25);
    // Enable the PWM0 Bit0 (PD0) output signal.
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
    // Enable the PWM generator block.
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
}
