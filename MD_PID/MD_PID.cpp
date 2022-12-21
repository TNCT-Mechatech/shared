#include "MD_PID.h"

MD_PID::MD_PID(MD *md, QEI *qei,
               double k, double ti, double td,
               double max_speed,
               double max_duty,
               bool dir)
    : _md(md), _qei(qei), _pid(new PI_D(k, ti, td))
{
    _duty = 0.0;
    set_max_speed(max_speed);
    set_max_duty(max_duty);
    set_direction(dir);
}

//void MD_PID::drive(double target_vel, double interval)
void MD_PID::drive(double target_vel)
{
    double present_vel = read_vel();

    if (fabs(target_vel) > _max_speed)
    {
        if (target_vel >= 0)
            target_vel = _max_speed;
        else
            target_vel = -_max_speed;
    }
    //PID_Control::PID(present_vel, target_vel, interval);
    //PID_Control::VPID(present_vel, target_vel, interval);
    //PID::PI_D(present_vel, target_vel, interval);
    _pid->set_state(present_vel, target_vel);

    if(!_dir)
        _duty = -1 * _pid->get_control();
    else
        _duty = _pid->get_control();

    if (fabs(_duty) > 1)
        _duty /= fabs(_duty);

    _md->drive(_duty);
    //printf("presnet_vel:\t%lf\tduty:\t%lf\r\n", present_vel, _duty);
}

double MD_PID::get_duty()
{
    return _duty;
}

double MD_PID::get_vel()
{
    return read_vel();
}

void MD_PID::brake(double target)
{
}

void MD_PID::free()
{
}

void MD_PID::reset()
{
    _pid->reset();
}

void MD_PID::set_max_speed(double max_speed)
{
    _max_speed = max_speed;
}

void MD_PID::set_max_duty(double max_duty)
{
    _max_duty = max_duty;
}

void MD_PID::set_direction(bool dir)
{
    _dir = dir;
}

double MD_PID::read_vel()
{
    return _qei->get_ang_vel();
}