#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "uartstdio.h"

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

void InitConsole(void)
{
    // Enable GPIO port A which is used for UART0 pins.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    // Enable UART0 so that we can configure the clock.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    // Select the alternate (UART) function for these pins.
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);
}
// Configure PWM0 for a 25% duty cycle signal running at 250Hz.  This example
// also shows how to invert the PWM signal every 5 seconds for 5 seconds.
int main(void)
{
    // Set the clocking to run directly from the external crystal/oscillator.
    SysCtlClockSet(
            SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN
                    | SYSCTL_XTAL_16MHZ);
    // Set the PWM clock to the system clock.
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    // Set up the serial console to use for displaying messages.  This is
    // just for this example program and is not needed for Timer operation.
    InitConsole();
    // Display the setup on the console.
    UARTprintf("PWM ->\n");
    UARTprintf("  Module: PWM0\n");
    UARTprintf("  Pin: PD0\n");
    UARTprintf("  Configured Duty Cycle: 25%%\n");
    UARTprintf("  Inverted Duty Cycle: 75%%\n");
    UARTprintf("  Features: PWM output inversion every 5 seconds.\n\n");
    UARTprintf("Generating PWM on PWM0 (PD0) -> State = ");
    // The PWM peripheral must be enabled for use.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    // For this example PWM0 is used with PortB Pin6.  The actual port and
    // pins used may be different on your part, consult the data sheet for
    // more information.
    // GPIO port B needs to be enabled so these pins can be used.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    // Configure the GPIO pin muxing to select PWM00 functions for these pins.
    // This step selects which alternate function is available for these pins.
    // This is necessary if your part supports GPIO pin function muxing.
    // Consult the data sheet to see which functions are allocated per pin.
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    // Configure the PWM function for this pin.
    // Consult the data sheet to see which functions are allocated per pin.
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
    // Configure the PWM0 to count up/down without synchronization.
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
                    PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    // Set the PWM period to 250Hz.  To calculate the appropriate parameter
    // use the following equation: N = (1 / f) * SysClk.  Where N is the
    // function parameter, f is the desired frequency, and SysClk is the
    // system clock frequency.
    // In this case you get: (1 / 250Hz) * 16MHz = 64000 cycles.  Note that
    // the maximum period you can set is 2^16.
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 64000);
    // Set PWM0 to a duty cycle of 25%.  You set the duty cycle as a function
    // of the period.  Since the period was set above, you can use the
    // PWMGenPeriodGet() function.  For this example the PWM will be high for
    // 25% of the time or 16000 clock ticks (64000 / 4).
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                     PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
    // Enable the PWM0 Bit0 (PD0) output signal.
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT, true);
    // Enable the PWM generator block.
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    // Loop forever while the PWM signals are generated.
    while (1)
    {
        // Print out that the level of PWM is normal.
        UARTprintf("Normal  \b\b\b\b\b\b\b\b");
        // This function provides a means of generating a constant length
        // delay.  The function delay (in cycles) = 3 * parameter.  Delay
        // 5 seconds arbitrarily.
        SysCtlDelay((SysCtlClockGet() * 5) / 3);
        // Invert PWM0 signal.
        PWMOutputInvert(PWM0_BASE, PWM_OUT_0_BIT, true);
        // Print out that the level of PWM is inverted.
        UARTprintf("Inverted\b\b\b\b\b\b\b\b");
        // This function provides a means of generating a constant length
        // delay.  The function delay (in cycles) = 3 * parameter.  Delay
        // 5 seconds arbitrarily.
        SysCtlDelay((SysCtlClockGet() * 5) / 3);
        // Switch PWM0 signal back to regular operation.
        PWMOutputInvert(PWM0_BASE, PWM_OUT_0_BIT, false);
    }
}
