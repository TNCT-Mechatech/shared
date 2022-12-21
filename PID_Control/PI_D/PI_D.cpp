#include "PI_D.h"

double PI_D::_get_control()
{
    return PID::_pid_state.k * (_p + _i - _d);
}
void PI_D::_calc_p()
{
    _update(_diff, PID::_pid_state.target - PID::_pid_state.current);
    _update(_measure, PID::_pid_state.target);
    _p = _diff[1];
}
void PI_D::_calc_i()
{
    _integral += (_diff[0] + _diff[1]) / 2;
    _i = _integral;
}
void PI_D::_calc_d()
{
    _d = _measure[1] - _measure[0];
}
void PI_D::_reset()
{
    _p = _i = _d = 0;
    _diff[0] = _diff[1] = 0;
    _integral = 0;
    _measure[0] = _measure[1] = 0;
}
