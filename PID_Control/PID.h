#ifndef PID_H_
#define PID_H_

#include "mbed.h"

class PID
{
public:
    PID(): _pid_state()
    {}
    ~PID()
    {
        _tick_i.detach();
        _tick_d.detach();
    }
    
    double get_control();
    void set_state(double target, double current);
    
    void set_PID(double k, double Ti, double Td);
    void reset();
protected: 
    typedef struct pid_con_s{
        double k;
        double Ti;
        double Td;
        double current;
        double target;
    }pid_con_t;
    
    pid_con_t _pid_state;
    
    virtual double _get_control() = 0;
    virtual void _calc_p() = 0;
    virtual void _calc_i() = 0;
    virtual void _calc_d() = 0;
    virtual void _reset() = 0;
private:
    Ticker _tick_i, _tick_d;
    
    void _on_isr_i();
    void _on_isr_d();
};

#endif
