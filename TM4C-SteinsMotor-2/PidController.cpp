/*
 * PidController.cpp
 *
 *  Created on: 22. mar. 2019
 *      Author: Drift
 */

#include <PidController.h>

PidController::PidController()
{
    integral = 0.0;
    old_error = 0.0;
    kP = 5.0;
    kI = 1.1;
    kD = 1.01;
    oMax = 5.0;
    oMin = 0.0;
}

PidController::~PidController()
{

}

float PidController::Input(float error, float dt)
{
    integral += error * dt;
    float derived = (error - old_error) / dt;
    float output = kP * error + kI * integral + kD * derived;
    old_error = error;
    if (output > oMax)
        output = oMax;
    if (output < oMin)
        output = oMin;
    return output;
}
