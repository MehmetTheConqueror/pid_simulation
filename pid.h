/*
 * PID library Alpha version
 * 29.10.2019
 * @ Mehmet Fatih Atalay
 *
*/

#ifndef PID_H
#define PID_H

#include <stdlib.h>

struct _pid_controller_t {
    float kp;
    float kd;
    float ki;
    float period;
    float set_point;
    float prev_error;
    float integral_sum;
    int isTuning;
    int tuning_phase;
    float tuning_time;
};

typedef struct _pid_controller_t pid_controller;

pid_controller *create_pid(float set_point, float kp, float kd, float ki, float period);
float pid_calculate_output(pid_controller*, float process_value);
void pid_reset(pid_controller*, float set_point);
void pid_start_tuning(pid_controller*);
void pid_set_parameters(pid_controller*ptrPid, float kp, float kd, float ki);

#endif // PID_H
