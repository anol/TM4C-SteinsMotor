/*
 * PidController.h
 *
 *  Created on: 22. mar. 2019
 *      Author: Drift
 */

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

class PidController
{
public:
    PidController();
    virtual ~PidController();
    float Input(float error, float dt);
    float integral;
    float old_error;
    float kP;
    float kI;
    float kD;
    float oMax;
    float oMin;
};

#endif /* PIDCONTROLLER_H_ */
