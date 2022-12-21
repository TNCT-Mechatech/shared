#include "Diff2_PID.h"

Diff2_PID::Diff2_PID(Wheel_PID *wheel_pid[NUM])
{
    for(int i = 0; i < NUM; i++){
        this->wheel_pid[i] = wheel_pid[i];
    }
}

void Diff2_PID::move(double x, double y, double yaw)
{
    double move_angle, move_radius;
    double vel[NUM];
    
    move_angle = atan2(y, x);
    move_radius = sqrt( y * y + x * x );
    
    for(int i = 0; i < NUM; i++)
        vel[i] = wheel_pid[i]->set_wheel_vel(move_angle, move_radius, yaw);

    /*
    // 平行移動と回転のうち、大きい方をmax_dutyに格納
    if(move_radius > fabs(yaw))
    	max_duty = move_radius;
    else
    	max_duty = fabs(yaw);

	up_limit_balance(duty, NUM, max_duty);
	down_limit_balance(duty, NUM, limit_duty);
    */
    
    for(int i = 0; i < NUM; i++){
        wheel_pid[i]->drive(vel[i]);
    }
}