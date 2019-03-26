/*
 * PulsCounter.cpp
 *
 *  Created on: 25. mar. 2019
 *      Author: Drift
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include <PulsCounter.h>
#include "uartstdio.h"

class CounterConfiguration
{
public:
    CounterConfiguration(std::string tag, uint32_t periph_timer, uint32_t periph_gpio, uint32_t gpio_timer_pin, uint32_t gpio_base, uint32_t gpio_pin,
                         uint32_t timer_base, uint32_t timer_gen, uint32_t timer_cfg) :
            m_tag(tag), m_periph_timer(periph_timer), m_periph_gpio(periph_gpio), m_gpio_timer_pin(gpio_timer_pin), m_gpio_base(gpio_base), m_gpio_pin(
                    gpio_pin), m_timer_base(timer_base), m_timer_gen(timer_gen), m_timer_cfg(timer_cfg)
    {

    }
    std::string m_tag;
    uint32_t m_periph_timer;
    uint32_t m_periph_gpio;
    uint32_t m_gpio_timer_pin;
    uint32_t m_gpio_base;
    uint32_t m_gpio_pin;
    uint32_t m_timer_base;
    uint32_t m_timer_gen;
    uint32_t m_timer_cfg;
};

// TIMER_CFG_A_CAP_COUNT - Half-width edge count capture
// TIMER_CFG_A_CAP_COUNT_UP - Half-width edge count capture that counts up
// TIMER_CFG_A_CAP_TIME - Half-width edge time capture
// TIMER_CFG_A_CAP_TIME_UP - Half-width edge time capture that counts up

const CounterConfiguration Configurations[] =
{
{ "PD0", SYSCTL_PERIPH_WTIMER2, SYSCTL_PERIPH_GPIOD, GPIO_PD0_WT2CCP0, GPIO_PORTD_BASE, GPIO_PIN_0, WTIMER2_BASE, TIMER_A, TIMER_CFG_A_CAP_COUNT },
  { "PD1", SYSCTL_PERIPH_WTIMER2, SYSCTL_PERIPH_GPIOD, GPIO_PD1_WT2CCP1, GPIO_PORTD_BASE, GPIO_PIN_1, WTIMER2_BASE, TIMER_B, TIMER_CFG_B_CAP_COUNT },
  { "PB6", SYSCTL_PERIPH_TIMER0, SYSCTL_PERIPH_GPIOB, GPIO_PB6_T0CCP0, GPIO_PORTB_BASE, GPIO_PIN_6, TIMER0_BASE, TIMER_A, TIMER_CFG_A_CAP_COUNT_UP },
  { "PB7", SYSCTL_PERIPH_TIMER0, SYSCTL_PERIPH_GPIOB, GPIO_PB7_T0CCP1, GPIO_PORTB_BASE, GPIO_PIN_7, TIMER0_BASE, TIMER_B, TIMER_CFG_B_CAP_COUNT } };

const CounterConfiguration* p_puls = 0;

PulsCounter::PulsCounter(const std::string& name)
{
    for (int gpc = 0; gpc < sizeof(Configurations) / sizeof(CounterConfiguration); gpc++)
    {
        if (0 == name.compare(Configurations[gpc].m_tag))
        {
            p_puls = &Configurations[gpc];
            break;
        }
    }
}
PulsCounter::~PulsCounter()
{
    // TODO Auto-generated destructor stub
}
void PulsCounter::Initialize()
{
    SysCtlPeripheralEnable(p_puls->m_periph_timer);
    SysCtlPeripheralEnable(p_puls->m_periph_gpio);
    GPIOPinTypeTimer(p_puls->m_gpio_base, p_puls->m_gpio_pin);
    GPIOPinConfigure(p_puls->m_gpio_timer_pin);
    GPIOPadConfigSet(p_puls->m_gpio_base, p_puls->m_gpio_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    TimerConfigure(p_puls->m_timer_base, (p_puls->m_timer_cfg | TIMER_CFG_SPLIT_PAIR));
    TimerControlEvent(p_puls->m_timer_base, p_puls->m_timer_gen, TIMER_EVENT_BOTH_EDGES);
    TimerEnable(p_puls->m_timer_base, p_puls->m_timer_gen);
}
uint32_t PulsCounter::GetCount()
{
    uint32_t count = TimerValueGet(p_puls->m_timer_base, p_puls->m_timer_gen);
    UARTprintf("C=%d\n", count);
    return count;
}
