#include "OdometryWheel.h"

OdometryWheel::OdometryWheel(QEI *qei, double wheel_angle, double wheel_radius, double position_angle, double position_radius)
	:_qei(qei), _wheel_angle(wheel_angle), _wheel_radius(wheel_radius), _position_angle(position_angle), _position_radius(position_radius)
{
	_calculate_coefficient_elements();
}

Eigen::Vector3d OdometryWheel::get_coefficient_elements()
{
	return _coefficient_elements;
}

double OdometryWheel::read_wheel_velocity()
{
	double velocity;
	velocity = _qei->get_ang_vel() * _wheel_radius;
	return velocity;
}

void OdometryWheel::_calculate_coefficient_elements()
{
	_coefficient_elements(X) = cos(_wheel_angle);
	_coefficient_elements(Y) = sin(_wheel_angle);
	_coefficient_elements(Yaw) = sin(_wheel_angle - _position_angle) * (_position_radius);
}
