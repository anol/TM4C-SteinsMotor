/*
 * MotorController.h
 *
 *  Created on: 22. mar. 2019
 *      Author: Drift
 */

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

class MotorController
{
public:
    MotorController(System& system, Console& console);
    virtual ~MotorController();
    int Start(float target, bool flag);
    float GetElapsedMilliseconds();
    float GetAntallPulser();
    void SetSpenningUt(float spenning);
private:
    PidController pid;
    System& system;
    Console& console;
};

#endif /* MOTORCONTROLLER_H_ */
