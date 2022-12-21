#include "Odometry2.h"

Odometry2::Odometry2(OdometryWheel *wheel[NUM])
{
    for (int i = 0; i < NUM; i++)
        _wheel[i] = wheel[i];
}

void Odometry2::get_velocity(double vel[])
{
    for (int i = 0; i < 3; i++)
        vel[i] = _vel[i];
}

void Odometry2::_read_velocity() {
    double rL = _wheel[L]->_position_radius;
    double rR = _wheel[R]->_position_radius;
    //double alpha = _wheel[L]._position_angle - _wheel[R]._position_angle;
    double vel_L = _wheel[L]->read_wheel_velocity(); //左車輪の回転速度[m/s]
    double vel_R = _wheel[R]->read_wheel_velocity(); //右車輪の回転速度[m/s]
    double tread = rL + rR; //車輪間距離[m]
    //double tread = sqrt(rL * rL + rR * rR - 2 * rL * rR * cos(alpha));

    _vel[X] = (vel_L + vel_R) / 2;
    _vel[Y] = 0.0;
    _vel[Yaw] = (vel_L - vel_R) / tread;
}