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

class PwmConfiguration
{
public:
    PwmConfiguration(std::string tag, uint32_t periph_pwm, uint32_t periph_gpio, uint32_t gpio_pwm_pin, uint32_t gpio_base, uint32_t gpio_pin,
                     uint32_t pwm_base, uint32_t pwm_gen, uint32_t pwm_out, uint32_t pwm_out_bit) :
            m_tag(tag), m_periph_pwm(periph_pwm), m_periph_gpio(periph_gpio), m_gpio_pwm_pin(gpio_pwm_pin), m_gpio_base(gpio_base), m_gpio_pin(
                    gpio_pin), m_pwm_base(pwm_base), m_pwm_gen(pwm_gen), m_pwm_out(pwm_out), m_pwm_out_bit(pwm_out_bit)
    {

    }
    std::string m_tag;
    uint32_t m_periph_pwm;
    uint32_t m_periph_gpio;
    uint32_t m_gpio_pwm_pin;
    uint32_t m_gpio_base;
    uint32_t m_gpio_pin;
    uint32_t m_pwm_base;
    uint32_t m_pwm_gen;
    uint32_t m_pwm_out;
    uint32_t m_pwm_out_bit;
};

const PwmConfiguration Configurations[] =

{ { "Red", SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOF, GPIO_PF1_M1PWM5, GPIO_PORTF_BASE, GPIO_PIN_1, PWM1_BASE, PWM_GEN_2, PWM_OUT_5, PWM_OUT_5_BIT },
  { "Blue", SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOF, GPIO_PF2_M1PWM6, GPIO_PORTF_BASE, GPIO_PIN_2, PWM1_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT },

  { "Green", SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOF, GPIO_PF3_M1PWM7, GPIO_PORTF_BASE, GPIO_PIN_3, PWM1_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT },
  { "PD0", SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOD, GPIO_PD0_M1PWM0, GPIO_PORTD_BASE, GPIO_PIN_0, PWM1_BASE, PWM_GEN_0, PWM_OUT_0, PWM_OUT_0_BIT },
  { "PD1", SYSCTL_PERIPH_PWM1, SYSCTL_PERIPH_GPIOD, GPIO_PD1_M1PWM1, GPIO_PORTD_BASE, GPIO_PIN_1, PWM1_BASE, PWM_GEN_0, PWM_OUT_1, PWM_OUT_1_BIT },
  { "PB6", SYSCTL_PERIPH_PWM0, SYSCTL_PERIPH_GPIOB, GPIO_PB6_M0PWM0, GPIO_PORTB_BASE, GPIO_PIN_6, PWM0_BASE, PWM_GEN_3, PWM_OUT_6, PWM_OUT_6_BIT },
  { "PB7", SYSCTL_PERIPH_PWM0, SYSCTL_PERIPH_GPIOB, GPIO_PB7_M0PWM1, GPIO_PORTB_BASE, GPIO_PIN_7, PWM0_BASE, PWM_GEN_3, PWM_OUT_7, PWM_OUT_7_BIT } };

const PwmConfiguration* p_conf = 0;

PwmGenerator::PwmGenerator(const std::string& name)
{
    for (int gpc = 0; gpc < sizeof(Configurations) / sizeof(PwmConfiguration); gpc++)
    {
        if (0 == name.compare(Configurations[gpc].m_tag))
        {
            p_conf = &Configurations[gpc];
            break;
        }
    }
    SysCtlPeripheralEnable(p_conf->m_periph_pwm);
    SysCtlPeripheralEnable(p_conf->m_periph_gpio);
}
PwmGenerator::~PwmGenerator()
{
}
void PwmGenerator::Initialize()
{
    GPIOPinConfigure(p_conf->m_gpio_pwm_pin);
    GPIOPinTypePWM(p_conf->m_gpio_base, p_conf->m_gpio_pin);
    PWMGenConfigure(p_conf->m_pwm_base, p_conf->m_pwm_gen, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(p_conf->m_pwm_base, p_conf->m_pwm_gen, 64000);
    PWMPulseWidthSet(p_conf->m_pwm_base, p_conf->m_pwm_out, 0);
    PWMOutputState(p_conf->m_pwm_base, p_conf->m_pwm_out_bit, true);
    PWMGenEnable(p_conf->m_pwm_base, p_conf->m_pwm_gen);
}
void PwmGenerator::Invert(bool invert)
{
    PWMOutputInvert(p_conf->m_pwm_base, p_conf->m_pwm_out_bit, invert);
}
void PwmGenerator::SetPulseWidth(int percent)
{
    uint32_t ui32Width = PWMGenPeriodGet(p_conf->m_pwm_base, p_conf->m_pwm_gen) * percent / 100;
    PWMPulseWidthSet(p_conf->m_pwm_base, p_conf->m_pwm_out, ui32Width);
}
void PwmGenerator::Enable()
{
}
