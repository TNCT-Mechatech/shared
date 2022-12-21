#ifndef ODMETRYWHEEL_H_
#define ODMETRYWHEEL_H_

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include <shared/QEI/QEI.h>

#define EIGEN_NO_DEBUG // コード内のassertを無効化．
#include <Core.h>

#define M_PI 3.14159265358979323846

class OdometryWheel
{
public:
	OdometryWheel(QEI *qei, double wheel_angle, double wheel_radius, double position_angle, double position_radius);
	virtual ~OdometryWheel(){};

	virtual Eigen::Vector3d get_coefficient_elements();
	virtual double read_wheel_velocity();

	enum CoefficientElements{
		X,
		Y,
		Yaw
	};

	double _wheel_angle, _wheel_radius, _position_angle, _position_radius;

private:
	void _calculate_coefficient_elements();

	QEI *_qei;
	Eigen::Vector3d _coefficient_elements;
};

#endif
