#ifndef MD_PID_H_
#define MD_PID_H_

#include <shared/MD/MD.h>
#include <shared/QEI/QEI.h>
#include "PID.h"
#include "PPID.h"
#include "PI_D.h"

class MD_PID
{
public:
    MD_PID(MD *md, QEI *qei,
           double k = 0, double ti = 0, double td = 0,
           double max_speed = 0,
           double max_duty = 1.0,
           bool dir = true);
    //virtual void drive(double target, double interval);
    virtual void drive(double target);
    virtual void brake(double target);
    virtual void free();
    void reset();
    void set_max_speed(double max_speed);
    void set_max_duty(double max_duty);
    void set_direction(bool dir);

    double get_duty();
    double get_vel();

private:
    MD *_md;
    QEI *_qei;
    PID *_pid;
    bool _dir;
    double _duty;
    double _max_speed;
    double _max_duty;

    double read_vel();
};

#endif