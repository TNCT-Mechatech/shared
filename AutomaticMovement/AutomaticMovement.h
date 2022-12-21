#ifndef AUTOMATIC_MOVEMENT_H_
#define AUTOMATIC_MOVEMENT_H_

#include <shared/Movement/Movement.h>
#include <shared/EigenCalculation/EigenCalculation.h>

class AutomaticMovement
{
public:
	AutomaticMovement(Movement *movement);
	virtual ~AutomaticMovement(){}

	virtual Eigen::Vector3d move_automatic(Eigen::Vector3d current_position) = 0;
	Eigen::Vector3d move_automatic(Eigen::Vector3d target_position, Eigen::Vector3d current_position);

	virtual void set_target_position(Eigen::Vector3d target_position);

protected:
	Movement *_movement;

	Eigen::Vector3d _target_position;
};

#endif
