
#ifndef ODOMETRY4_H_
#define ODOMETRY4_H_

#include <shared/OdometryWheel/OdometryWheel.h>
#include <Dense.h>
#include <LU.h>
#include <shared/EigenCalculation/EigenCalculation.h>

typedef Eigen::Matrix<double, 4, 3> Matrix43d;
typedef Eigen::Matrix<double, 3, 4> Matrix34d;

class Odometry4
{
public:
	static const int NUM = 4;
	Odometry4(OdometryWheel *wheel[NUM]);
	virtual ~Odometry4(){};

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
	Eigen::Vector3d _coefficient[NUM];
	Matrix34d _coefficient_matrix;
	Eigen::Vector3d _position;
	Eigen::Vector3d _velocity;
};



#endif
