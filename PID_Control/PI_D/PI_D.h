#ifndef PI_D_H_
#define PI_D_H_

#include "PID.h"

class PI_D : public PID
{
public:
    PI_D(double k = 0, double Ti = 0, double Td = 0, double target = 0, double current = 0)
    {
        PID::set_PID(k, Ti, Td);
        set_state(target, current);
    }
    ~PI_D(){}
    
protected: 
    
    virtual double _get_control();
    virtual void _calc_p();
    virtual void _calc_i();
    virtual void _calc_d();
    virtual void _reset();

private:

    inline void _update(double *array, double present)
    {
        array[0] = array[1];
        array[1] = present;
    }
    double _p, _i, _d;
    double _diff[2];
    double _integral;
    double _measure[2];
};

#endif
