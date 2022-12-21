#ifndef G_CODE_MOVEMENT_H_
#define G_CODE_MOVEMENT_H_

#include <shared/AutomaticMovement/AutomaticMovement.h>
#include <shared/GCodeReader/GCodeReader.h>
#include <queue>

class GCodeMovement : public GCodeReader
{
public:
	GCodeMovement(AutomaticMovement *automatic_movement, Eigen::Vector3d *current_position, Eigen::Vector3d *target_position);
	virtual ~GCodeMovement(){}

	Eigen::Vector3d move_g_code(Eigen::Vector3d current_position);

	void push_g_code(const std::string g_code);
	void reset_g_code();
	void set_near_position(const Eigen::Vector3d &near_position);

private:
	AutomaticMovement *_automatic_movement;
	std::queue<std::string> _g_code_list;
	Eigen::Vector3d _near_position;

};
#endif
