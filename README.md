# pid_simulation
PID control algorithm and simple simulation

Simulation is written in C++ & Qt framework (Qt 5.7.0).

pid.c and pid.h files can be used stand-alone; outside of simulation.

Usage:

1- (initially) create a _pid_controller_t instance:

    pid_controller *create_pid(float set_point, float kp, float kd, float ki, float period)
    
2- (optional) refresh PID parameters:

    void pid_set_parameters(pid_controller*ptrPid, float kp, float kd, float ki)
    
3- (if needed) reset pid controller when parameters are changed

    void pid_reset(pid_controller*, float set_point)
    
4- (if needed) start auto-tuning

    void pid_start_tuning(pid_controller*)
    
4- (periodically) calculate PID output for a given process value

    float pid_calculate_output(pid_controller*, float process_value)
