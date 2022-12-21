#include "Wheel_PID.h"

Wheel_PID::Wheel_PID(MD_PID *md_pid, double wheel_radius, double wheel_angle, double position_radius, double position_angle)
    : _md_pid(md_pid), 
      _wheel_radius(wheel_radius), _wheel_angle(wheel_angle), 
      _position_radius(position_radius), _position_angle(position_angle){}

/*
Wheel_PID::Wheel_PID(MD_PID *md_pid, double wheel_radius, double wheel_angle, double position_x, double position_y)
    : _md_pid(md_pid),
      _wheel_radius(wheel_radius), _wheel_angle(wheel_angle),
      set_position(position_x, position_y){}
*/

void Wheel_PID::set_position(double position_x, double position_y)
{
    _position_radius = sqrt(position_y * position_y + position_x * position_x);
    _position_angle = atan2(position_y, position_x);
}

double Wheel_PID::set_wheel_vel(double move_angle, double move_radius, double yaw)
{
    //X, Y, Yaw方向の速度指令から、ホイールの回転速度を算出
    double speed;
    double moving, rotating;
    
    while(move_angle > M_PI)
        move_angle -= 2.0 * M_PI;
    
    moving = cos(_wheel_angle - move_angle) * move_radius;
    
    rotating = sin(_wheel_angle - _position_angle) * yaw * _position_radius;
    
    speed = moving + rotating;
    
    return speed;
}

double Wheel_PID::get_wheel_vel()
{
    return _wheel_radius * _md_pid->get_vel();
}

void Wheel_PID::drive(double vel)
{
    double ang_vel = vel / _wheel_radius; //ホイールの速度[m/s]から角速度[rad/s]を算出
    _md_pid->drive(ang_vel); //速度PID
}
