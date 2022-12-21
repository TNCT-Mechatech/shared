#ifndef WHEEL_PID_H_
#define WHEEL_PID_H_

#include <mbed.h>
#include <shared/MD_PID/MD_PID.h>

class Wheel_PID
{
public:
    /*注意 Wheelクラスとは異なり、ホイールの半径を必須とする*/
    Wheel_PID(MD_PID *md_pid, double wheel_radius, double wheel_angle, double position_radius, double position_angle);
    //Wheel_PID(MD_PID *md_pid, double wheel_radius, double wheel_angle, double position_x, double position_y);
    
    void set_position(double position_x, double position_y);
    
    double set_wheel_vel(double move_angle, double move_radius, double yaw);
    double get_wheel_vel();

    void drive(double vel);
private:
    MD_PID *_md_pid;

    double _position_radius, _position_angle;
    double _wheel_radius, _wheel_angle;
};
    
#endif

#ifndef M_PI
#define M_PI 3.1415926535
#endif
