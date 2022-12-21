#ifndef DIFF2_PID_H_
#define DIFF2_PID_H_

#include <shared/Movement/Movement.h>
#include <shared/Wheel_PID/Wheel_PID.h>

class Diff2_PID : public Movement
{
public:
    enum
    {
        L,
        R,
        NUM
    };

    /*注意　Diff2クラスとは違い、引数はWheel_PIDクラスしか受け取れない*/
    Diff2_PID(Wheel_PID *wheel_pid[NUM]);

    virtual void move(double x, double y, double yaw);

private:
    Wheel_PID *wheel_pid[NUM];
};

#endif