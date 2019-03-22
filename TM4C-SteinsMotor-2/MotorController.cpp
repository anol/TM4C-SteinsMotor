/*
 * MotorController.cpp
 *
 *  Created on: 22. mar. 2019
 *      Author: Drift
 */

#include <stdbool.h>
#include <stdint.h>
#include <System.h>
#include <Console.h>
#include <PwmGenerator.h>
#include <PidController.h>
#include <MotorController.h>

MotorController::MotorController(System& system, Console& console) :
        system(system), console(console)
{

}

MotorController::~MotorController()
{

}

int MotorController::Start(float target, bool flag)
{
    PwmGenerator pwmGenerator;
    pwmGenerator.Initialize();
    pwmGenerator.Enable();
    pwmGenerator.Invert(flag);
    GetAntallPulser();
    GetElapsedMilliseconds();
    for (uint32_t count = 0; count < 20; count++)
    {
        float error = target - GetAntallPulser();
        float dt = GetElapsedMilliseconds();
        float spenningUt = pid.Input(error, dt);
        SetSpenningUt(spenningUt);
        // console.Print("% 4d: v=%.3f, e=%.3f, dt=%.3f \n", (int) count, spenningUt, error, dt);
        system.Sleep(100);
    }
    SetSpenningUt(0.0);
    return 0;
}

float MotorController::GetElapsedMilliseconds()
{
    float dt = 1;
    return dt;
}

float MotorController::GetAntallPulser()
{
    float antall = 1;
    return antall;
}

void MotorController::SetSpenningUt(float spenning)
{
}
