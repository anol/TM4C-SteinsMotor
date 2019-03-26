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
        pid(), system(system), console(console), pwmGenerator("PD0"), pulsCounter("PB6")
{

}
MotorController::~MotorController()
{

}
void MotorController::Initialize()
{
    pulsCounter.Initialize();
    pwmGenerator.Initialize();
    pwmGenerator.Enable();
}
int MotorController::Start(float target, bool flag)
{
    pwmGenerator.Invert(flag);
    GetAntallPulser();
    GetElapsedMilliseconds();
    for (uint32_t count = 0; count < 20; count++)
    {
        float error = target - GetAntallPulser();
        float dt = GetElapsedMilliseconds();
        float spenningUt = pid.Input(error, dt);
        SetSpenningUt(spenningUt);
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
uint32_t MotorController::GetAntallPulser()
{
    uint32_t new_count = pulsCounter.GetCount();
    uint32_t antall = new_count - old_count;
    old_count = new_count;
    return antall;
}
void MotorController::SetSpenningUt(float spenning)
{
}
