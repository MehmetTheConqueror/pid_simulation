#include "pid.h"

pid_controller* create_pid(float set_point, float kp, float kd, float ki, float period)
{
    pid_controller* ptrPid = malloc(sizeof(pid_controller));
    ptrPid->kp = kp;
    ptrPid->kd = kd;
    ptrPid->ki = ki;
	
    if (period > 0)
    	ptrPid->period = period;
    else
        ptrPid->period = 1;

    ptrPid->set_point = set_point;

    ptrPid->integral_sum = 0;
    ptrPid->prev_error = 0;
    ptrPid->isTuning = 0;

    return ptrPid;
}

void pid_set_parameters(pid_controller* ptrPid, float kp, float kd, float ki)
{
    ptrPid->kp = kp;
    ptrPid->kd = kd;
    ptrPid->ki = ki;
}

float pid_calculate_output(pid_controller *pid,  float process_value)
{
    if (pid->isTuning){ // with Ziegler–Nichols method
        if (pid->tuning_phase == 0){
            if (process_value < pid->set_point){
                pid->kp += 1;
            }
            else{
                pid->tuning_phase = 1;
            }
        }
        else if (pid->tuning_phase == 1){
            if (process_value < pid->set_point){
                pid->tuning_phase = 2;
            }
            pid->tuning_time += pid->period;
        }
        else if (pid->tuning_phase == 2){
            if (process_value >= pid->set_point){
                pid->isTuning = 0;

                pid->ki = 1.2 * pid->kp / pid->tuning_time;
                pid->kd = 0.075 * pid->kp * pid->tuning_time;
                pid->kp = pid->kp * 0.6;
            }
            pid->tuning_time += pid->period;
        }
    }

    float error = pid->set_point - process_value;
    float derivative = pid->kd * (error - pid->prev_error) / pid->period;
    float integral = pid->ki * error * pid->period;
    pid->integral_sum += integral;
    float proportional = pid->kp * error;

    pid->prev_error = error;
    float power = derivative + pid->integral_sum + proportional;

    if (power > 100)
        power = 100;
    else if (power < 0)
        power = 0;
    return power;
}

void pid_reset(pid_controller *pid, float set_point)
{
    pid->integral_sum = 0;
    pid->prev_error = 0;
    pid->set_point = set_point;
}

void pid_start_tuning(pid_controller *pid)
{
    pid->isTuning = 1;

    pid->tuning_phase = 0;
    pid->tuning_time = 0;
    pid->integral_sum = 0;
    pid->prev_error = 0;
    pid->kd = 0;
    pid->ki = 0;
    pid->kp = 1;
}

