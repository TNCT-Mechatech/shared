#include "Odometry3.h"

Odometry3::Odometry3(OdometryWheel *wheel[3])
{
	for(int i = 0; i < NUM; i++)
		_wheel[i] = wheel[i];
	reset_position();
	_set_coefficient_matrix();
}

Eigen::Vector3d Odometry3::read_position()
{
	Eigen::Vector3d velocity = _read_velocity();

	EigenCalculation::yawling_correct(&velocity);
	EigenCalculation::rotate_coordinate(&velocity, _position(Odometry3::Yaw));

	_position += velocity;
	return _position;
}

void Odometry3::write_position(const Eigen::Vector3d& set_position)
{
	_position = set_position;
}

void Odometry3::reset_position()
{
	_position = Eigen::Vector3d::Zero();
}

Eigen::Vector3d Odometry3::get_velocity()
{
	return _velocity;
}

Eigen::Vector3d Odometry3::_read_velocity()
{
	Eigen::Vector3d velocity;
	Eigen::Vector3d wheel_velocity;

	for(int i =0; i < NUM; i++)
		wheel_velocity(i) = _wheel[i]->read_wheel_velocity();

	velocity = _coefficient_matrix * wheel_velocity;

	_velocity = velocity;

	return velocity;
}

void Odometry3::_set_coefficient_matrix()
{
	for(int i = 0; i < NUM; i++)
		_coefficient_matrix.row(i) = _wheel[i]->get_coefficient_elements();

	EigenCalculation::invert_matrix(&_coefficient_matrix);
}
