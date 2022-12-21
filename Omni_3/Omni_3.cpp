#include "Omni_3.h"

Omni_3::Omni_3(MD *md[NUM])
{
    _wheel[F] = new Wheel( md[F],  3.0 * M_PI / 3.0,  3.0 * M_PI / 6.0 );
    _wheel[L] = new Wheel( md[L],  -1.0 * M_PI / 3.0, -5.0 * M_PI / 6.0 );
    _wheel[R] = new Wheel( md[R],  1.0 * M_PI / 3.0, -1.0 * M_PI / 6.0 );
}

Omni_3::Omni_3(MD *md_F, MD *md_L, MD *md_R)
{
    _wheel[F] = new Wheel( md_F,  0.0 * M_PI / 3.0,  3.0 * M_PI / 6.0 );
    _wheel[L] = new Wheel( md_L,  2.0 * M_PI / 3.0, -5.0 * M_PI / 6.0 );
    _wheel[R] = new Wheel( md_R, -2.0 * M_PI / 3.0, -1.0 * M_PI / 6.0 );
}

Omni_3::Omni_3(Wheel *wheel[NUM])
{
	for(int i = 0; i < NUM; i++)
		_wheel[i] = wheel[i];
}

void Omni_3::move(double x, double y, double yaw)
{
    double move_angle, move_radius;
    double duty[NUM];
    double max_duty, limit_duty = 1.0;
    
    move_angle = atan2(y, x);
    move_radius = sqrt( y * y + x * x );
    
    for(int i = 0; i < NUM; i++)
        duty[i] = _wheel[i]->set_wheel_vel(move_angle, move_radius, yaw);

    // 蟷ｳ陦檎ｧｻ蜍輔→蝗櫁ｻ｢縺ｮ縺�縺｡縲∝､ｧ縺阪＞譁ｹ繧知ax_duty縺ｫ譬ｼ邏�
    if(move_radius > fabs(yaw))
    	max_duty = move_radius;
    else
    	max_duty = fabs(yaw);

	up_limit_balance(duty, NUM, max_duty);
	down_limit_balance(duty, NUM, limit_duty);
    
    for(int i = 0; i < NUM; i++){
        _wheel[i]->drive(duty[i]);
    }
}
