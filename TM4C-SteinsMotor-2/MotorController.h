/*
 * MotorController.h
 *
 *  Created on: 22. mar. 2019
 *      Author: Drift
 */

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#include <PwmGenerator.h>
#include <PulsCounter.h>

class MotorController
{
public:
    MotorController(System& system, Console& console);
    virtual ~MotorController();
    void Initialize();
    int Start(float target, bool flag);
    float GetElapsedMilliseconds();
    uint32_t GetAntallPulser();
    void SetSpenningUt(float spenning);
private:
    uint32_t old_count;
    PidController pid;
    System& system;
    Console& console;
    PwmGenerator pwmGenerator;
    PulsCounter pulsCounter;
};

#endif /* MOTORCONTROLLER_H_ */
