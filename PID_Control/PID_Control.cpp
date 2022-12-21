#include "PID_Control.h"

PID_Control::PID_Control(double kp, double ki, double kd, double kf)
{
    set_PID(kp, ki, kd, kf);
}

PID_Control::PID_Control(double ku, double pu)
{
	set_PID_ZN(ku, pu);
}

double PID_Control::PID(double present, double target, double interval)
{
    _diff[PAST] = _diff[PRESENT];
    _diff[PRESENT] = target - present;
    _integral += ((_diff[PRESENT] + _diff[PAST]) / 2.0) * interval;
    _ff = _kf*target;
    _p = _kp * _diff[PRESENT];
    _i = _ki * _integral;
    _d = _kd * (_diff[PRESENT] - _diff[PAST]) / interval;
    return _p + _i + _d + _ff;
}

void PID_Control::reset()
{
    _diff[PAST] = 0.0;
    _diff[PRESENT] = 0.0;
    _integral = 0.0;
}

void PID_Control::set_PID(double kp, double ki, double kd, double kf)
{
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _kf = kf;
    reset();
}

void PID_Control::set_PID_ZN(double ku, double pu)
{
	double ti,td;

	ti = 0.5 * pu;
	td = 0.125 * pu;

	_kp = ku * 0.6;
	_ki = _kp / ti;
	_kd = _kp * td;
    reset();
}
