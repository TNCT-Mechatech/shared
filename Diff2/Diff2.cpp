#include "Diff2.h"

Diff2::Diff2(MD *md[NUM])
{
    wheel[L] = new Wheel( md[L],  M_PI / 2.0,  M_PI);
    wheel[R] = new Wheel( md[R], -M_PI / 2.0,  0.0);
}

Diff2::Diff2(MD *md_L, MD *md_R)
{
    wheel[L] = new Wheel( md_L,  M_PI / 2.0,  M_PI);
    wheel[R] = new Wheel( md_R, -M_PI / 2.0,  0.0);
}

Diff2::Diff2(Wheel *wheel[NUM])
{
    for(int i = 0; i < NUM; i++){
        this->wheel[i] = wheel[i];
    }
}

void Diff2::move(double x, double y, double yaw)
{
    double move_angle, move_radius;
    double duty[NUM];
    double max_duty, limit_duty = 1.0;
    
    move_angle = atan2(y, x);
    move_radius = sqrt( y * y + x * x );
    
    for(int i = 0; i < NUM; i++)
        duty[i] = wheel[i]->set_wheel_vel(move_angle, move_radius, yaw);

    // 平行移動と回転のうち、大きい方をmax_dutyに格納
    if(move_radius > fabs(yaw))
    	max_duty = move_radius;
    else
    	max_duty = fabs(yaw);

	up_limit_balance(duty, NUM, max_duty);
	down_limit_balance(duty, NUM, limit_duty);
    
    for(int i = 0; i < NUM; i++){
        wheel[i]->drive(duty[i]);
    }
}