#ifndef ODOMETRY3_H_
#define ODOMETRY3_H_

#include <shared/OdometryWheel/OdometryWheel.h>
#include <Dense.h>
#include <shared/EigenCalculation/EigenCalculation.h>

class Odometry3
{
public:
	static const int NUM = 3;
	Odometry3(OdometryWheel *wheel[NUM]);
	virtual ~Odometry3(){};

	Eigen::Vector3d read_position();

	void write_position(const Eigen::Vector3d& set_position);
	void reset_position();

	Eigen::Vector3d get_velocity();

	void set_coefficient_matrix();

	enum VectorElements{
		X,
		Y,
		Yaw
	};

private:
	Eigen::Vector3d _read_velocity();
	void _set_coefficient_matrix();

	OdometryWheel *_wheel[NUM];
	Eigen::Matrix3d _coefficient_matrix;
	Eigen::Vector3d _position;
	Eigen::Vector3d _velocity;
};

#endif
