#include "EigenCalculation.h"

void EigenCalculation::invert_matrix(Eigen::Matrix3d *matrix3d)
{
	Eigen::FullPivLU< Eigen::Matrix3d > lu(*matrix3d);
	(*matrix3d) = lu.inverse();
}

void EigenCalculation::yawling_correct(Eigen::Vector3d *vector3d)
{
	Eigen::Vector3d vector_arc;
	double arc, vector_angle, radius;
	double x, y, yaw;

	x	= (*vector3d)(EigenCalculation::X);
	y	= (*vector3d)(EigenCalculation::Y);
	yaw = (*vector3d)(EigenCalculation::Yaw);

	if(yaw == 0.0)
		return;

	arc = sqrt(x * x + y * y);
	vector_angle = atan2(y, x);

	radius = arc / yaw;

	vector_arc(EigenCalculation::X) = radius * (1.0 - cos(yaw));
	vector_arc(EigenCalculation::Y) = radius * sin(yaw);
	vector_arc(EigenCalculation::Yaw) = yaw;

	rotate_coordinate( &vector_arc, -(0.5 * M_PI - vector_angle) );

	(*vector3d) = vector_arc;
}

void EigenCalculation::rotate_coordinate(Eigen::Vector3d *vector3d, double yaw)
{
	Eigen::Vector3d rotated_vector;
	Eigen::Vector3d axis; axis << 0,0,1;
	Eigen::Matrix3d rotation3d; rotation3d = Eigen::AngleAxisd(yaw, axis);

	rotated_vector = rotation3d * (*vector3d);

	(*vector3d) = rotated_vector;
}
