#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include <System.h>
#include <Console.h>
#include <PidController.h>
#include <MotorController.h>
#include <PwmGenerator.h>

//*****************************************************************************
//
//! \addtogroup pwm_examples_list
//! <h1>PWM Invert (invert)</h1>
//!
//! This example shows how to setup PWM0 using the inverted output function.
//! This feature allows you to invert the polarity of the PWM output.  This
//! example is setup to invert a 25% duty cycle to get a 75% duty cycle every
//! 5 seconds.
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - GPIO Port B peripheral (for PWM0 pin)
//! - PWM0 - PB6
//!
//! The following UART signals are configured only for displaying console
//! messages for this example.  These are not required for operation of the
//! PWM.
//! - UART0 peripheral
//! - GPIO Port A peripheral (for UART0 pins)
//! - UART0RX - PA0
//! - UART0TX - PA1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//
//*****************************************************************************

// Configure PWM0 for a 25% duty cycle signal running at 250Hz.  This example
// also shows how to invert the PWM signal every 5 seconds for 5 seconds.
int main(void)
{
    System system;
    Console console;
    MotorController motor(system, console);
    console.Initialize();
    console.Print("Steins motor\n");
    while (1)
    {
        console.Print("Normal\n");
        motor.Start(10.0, true);
        console.Print("Inverted\n");
        motor.Start(10.0, false);
    }
}
