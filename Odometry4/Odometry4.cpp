#include "Odometry4.h"

Odometry4::Odometry4(OdometryWheel *wheel[NUM]){
	for (int i = 0; i < NUM; i++)
		_wheel[i] = wheel[i];
	reset_position();
	_set_coefficient_matrix();
}

Eigen::Vector3d Odometry4::read_position() {

	 Eigen::Vector3d velocity = _read_velocity();

	 EigenCalculation::yawling_correct(&velocity);
	 EigenCalculation::rotate_coordinate(&velocity, _position(Odometry4::Yaw));

	 _position += velocity;
	 return _position;
}

void Odometry4::write_position(const Eigen::Vector3d& set_position) {
	_position = set_position;
}

void Odometry4::reset_position() {
	_position = Eigen::Vector3d::Zero();
}

Eigen::Vector3d Odometry4::get_velocity() {
	return _velocity;
}

Eigen::Vector3d Odometry4::_read_velocity() {
	Eigen::Vector3d velocity;
	Eigen::Vector4d wheel_velocity;

	for (int i = 0; i < NUM; i++)
		wheel_velocity(i) = _wheel[i]->read_wheel_velocity();

	velocity = _coefficient_matrix * wheel_velocity;
	_velocity = velocity;

	return velocity;
}

void Odometry4::_set_coefficient_matrix() {
	Matrix43d coefficient_matrix;
	Matrix34d invert_coefficient_matrix;
	for (int i = 0; i < NUM; i++)
		_coefficient[i] = _wheel[i]->get_coefficient_elements();

	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < 3; j++) {
			coefficient_matrix(i, j) = _coefficient[i](j);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < NUM; j++) {
			if (i == 2)
				invert_coefficient_matrix(i, j) = 1.0
						/ (2.0 * _coefficient[j](i));
			else
				invert_coefficient_matrix(i, j) = _coefficient[j](i);
		}
	}
	_coefficient_matrix = invert_coefficient_matrix / 2.0;

}


