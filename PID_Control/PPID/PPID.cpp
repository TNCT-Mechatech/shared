#include "PPID.h"

double PPID::_get_control()
{
    return PID::_pid_state.k * (_p + _i + _d);
}
void PPID::_calc_p()
{
    _update(_diff, PID::_pid_state.target - PID::_pid_state.current);
    _p = _diff[1];
}
void PPID::_calc_i()
{
    _integral += (_diff[0] + _diff[1]) / 2;
    _i = _integral;
}
void PPID::_calc_d()
{
    _d = _diff[1] - _diff[0];
}
void PPID::_reset()
{
    _p = _i = _d = 0;
    _diff[0] = _diff[1] = 0;
    _integral = 0;
}
