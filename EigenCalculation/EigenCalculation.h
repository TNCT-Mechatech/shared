#ifndef EIGEN_CALCULATION_H_
#define EIGEN_CALCULATION_H_

#include <Dense.h>
#include <LU.h>
#include <math.h>

namespace EigenCalculation
{
	enum{
		X,
		Y,
		Yaw
	};

	void invert_matrix(Eigen::Matrix3d *matrix3d);
	void yawling_correct(Eigen::Vector3d *vector3d);
	void rotate_coordinate(Eigen::Vector3d *vector3d, double yaw);
}



#endif
