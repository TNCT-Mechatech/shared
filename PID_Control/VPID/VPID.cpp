#include "VPID.h"

double VPID::_get_control()
{
    return _ctrl;
}
void VPID::_calc_p()
{
    _update(_diff, PID::_pid_state.target - PID::_pid_state.current);
    _p = _diff[1];
    _update(_dctrl, PID::_pid_state.k * (_p + _i + _d));
    _ctrl += (_dctrl[1] - _dctrl[0]) / _tim.read();
    _tim.reset();
}
void VPID::_calc_i()
{
    _integral += (_diff[0] + _diff[1]) / 2;
    _i = _integral;
}
void VPID::_calc_d()
{
    _d = _diff[1] - _diff[0];
}
void VPID::_reset()
{
    _p = _i = _d = 0;
    _diff[0] = _diff[1] = 0;
    _integral = 0;
    _ctrl = _dctrl[0] = _dctrl[1] = 0;
}
