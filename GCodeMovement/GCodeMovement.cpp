#include "GCodeMovement.h"

GCodeMovement::GCodeMovement(AutomaticMovement *automatic_movement, Eigen::Vector3d *current_position, Eigen::Vector3d *target_position)
	: _automatic_movement(automatic_movement), GCodeReader(current_position, target_position)
{}

Eigen::Vector3d GCodeMovement::move_g_code(Eigen::Vector3d current_position)
{
	Eigen::Vector3d speed_move;
	Eigen::Vector3d difference;

	*GCodeReader::_current_position = current_position;

	if(_g_code_list.size() == 0)
		_g_code_list.push(std::string("g0"));

	read_g_code(_g_code_list.front());

	difference = *GCodeReader::_target_position - *GCodeReader::_current_position;

	if( (difference.array().abs() < _near_position.array()).all() )
		_g_code_list.pop();

	speed_move = _automatic_movement->move_automatic(*GCodeReader::_target_position, *GCodeReader::_current_position);

	return speed_move;
}

void GCodeMovement::push_g_code(const std::string g_code)
{
	_g_code_list.push(g_code);
}

void GCodeMovement::reset_g_code()
{
	while(!_g_code_list.empty())
		_g_code_list.pop();
}

void GCodeMovement::set_near_position(const Eigen::Vector3d &near_position)
{
	_near_position = near_position;
}
