#include "OnOffMovement.h"

OnOffMovement::OnOffMovement(Movement *movement) : AutomaticMovement(movement)
{}

Eigen::Vector3d OnOffMovement::move_automatic(Eigen::Vector3d current_position)
{
	Eigen::Vector3d position_difference, speed_move;
	position_difference = _target_position - current_position;

	for(int i = 0; i < 3; i++){
		if(fabs(position_difference(i)) < _near_distance(i))
			speed_move(i) = 0;
		else
			speed_move(i) = position_difference(i)
							/ fabs(position_difference(i))
							* _speed(i);
	}

	EigenCalculation::rotate_coordinate(&speed_move, -current_position(Movement::Yaw));

	_movement->move(speed_move);

	return speed_move;
}

void OnOffMovement::set_near_distance(Eigen::Vector3d near_distance)
{
	_near_distance = near_distance;
}

void OnOffMovement::set_speed(Eigen::Vector3d speed)
{
	_speed = speed;
}
