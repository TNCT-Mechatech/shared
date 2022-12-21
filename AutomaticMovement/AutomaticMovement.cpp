#include "AutomaticMovement.h"

AutomaticMovement::AutomaticMovement(Movement *movement)
:_movement(movement)
{}

Eigen::Vector3d AutomaticMovement::move_automatic(Eigen::Vector3d target_position, Eigen::Vector3d current_position)
{
	set_target_position(target_position);
	return move_automatic(current_position);
}

void AutomaticMovement::set_target_position(Eigen::Vector3d target_position)
{
	_target_position = target_position;
}
