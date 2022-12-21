#ifndef QEI_H_
#define QEI_H_

#include <mbed.h>

#define M_PI 3.14159265358979323846

class QEI
{
public:
	QEI(int edge_per_revolution);
	virtual ~QEI(){};
	
	int read();
	
	double get_ang();
	double get_ang_vel();
	
	void write(int32_t);
	void reset();
	
protected:
    virtual int32_t _read() = 0;
    virtual void _write(int32_t set_count) = 0;
    virtual double _get_pps() = 0; 

private:
    int _edge_per_revolution;
};

#endif
