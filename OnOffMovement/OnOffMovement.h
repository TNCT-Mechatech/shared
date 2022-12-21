#ifndef ONOFFMOVEMENT_H_
#define ONOFFMOVEMENT_H_

#include <shared/AutomaticMovement/AutomaticMovement.h>

class OnOffMovement : public AutomaticMovement
{
public:
	OnOffMovement(Movement *movement);
	virtual ~OnOffMovement(){}

	virtual Eigen::Vector3d move_automatic(Eigen::Vector3d current_position);

	void set_near_distance(Eigen::Vector3d near_distance);
	void set_speed(Eigen::Vector3d speed);

private:

	Eigen::Vector3d _near_distance;
	Eigen::Vector3d _speed;
};

#endif
