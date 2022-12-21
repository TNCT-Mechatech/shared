#include "PID.h"

double PID::get_control()
{
    _calc_p();
    return _get_control();
}

void PID::set_state(double target, double current)
{
    _pid_state.target = target;
    _pid_state.current = current;
}

void PID::set_PID(double k, double Ti, double Td)
{
    _pid_state.k = k;
    _pid_state.Ti = Ti;
    _pid_state.Td = Td;
    reset();
}

void PID::reset()
{
    _reset();
    if(_pid_state.Ti != 0)
        _tick_i.attach(callback(this, &PID::_on_isr_i), _pid_state.Ti);
    if(_pid_state.Td != 0)
        _tick_d.attach(callback(this, &PID::_on_isr_d), _pid_state.Td);
}

void PID::_on_isr_i()
{
    _calc_p();
    _calc_i();
}

void PID::_on_isr_d()
{
    _calc_p();
    _calc_d();
}
