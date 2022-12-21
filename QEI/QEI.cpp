#include "QEI.h"

QEI::QEI(int edge_per_revolution)
	:_edge_per_revolution(edge_per_revolution)
{}

int QEI::read()
{
	return _read();
}

void QEI::write(int32_t count)
{
	_write(count);
}

void QEI::reset()
{
	_write(0);
}

double QEI::get_ang()
{
	return ((double)read() / (double)_edge_per_revolution) * (2 * M_PI); //[rad]
}

double QEI::get_ang_vel(){
	return (_get_pps() / (double)_edge_per_revolution) * (2 * M_PI); //[rad/s]
}