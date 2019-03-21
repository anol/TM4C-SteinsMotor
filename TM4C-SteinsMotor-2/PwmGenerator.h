/*
 * PwmGenerator.h
 *
 *  Created on: 21. mar. 2019
 *      Author: Drift
 */

#ifndef PWMGENERATOR_H_
#define PWMGENERATOR_H_

class PwmGenerator
{
public:
    PwmGenerator();
    virtual ~PwmGenerator();
    void Initialize();
    void Enable();
    void Invert(bool invert);
    void SetPulseWidth(int percent);
private:
    void PmEnable(uint32_t periph_pwm, uint32_t periph_gpio, uint32_t gpio_pwm_pin, uint32_t gpio_base,
                  uint32_t gpio_pin, uint32_t pwm_base, uint32_t pwm_gen, uint32_t pwm_out_bit);
};

#endif /* PWMGENERATOR_H_ */
