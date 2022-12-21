#ifndef DAMY_MOVEMENT_H_
#define DAMY_MOVEMENT_H_

#include <shared/Movement/Movement.h>

class DamyMovement : public Movement
{
public:
	virtual ~DamyMovement(){}
	virtual void move(double x, double y, double yaw)
	{
		Eigen::Vector3d speed_move;
		speed_move << x, y, yaw;
		_speed_move = speed_move;
	}
	Eigen::Vector3d get_speed_move()
	{
		return _speed_move;
	}
private:
	Eigen::Vector3d _speed_move;
};

#endif
