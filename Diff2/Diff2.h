#ifndef DIFF2_H_
#define DIFF2_H_

#include <shared/Movement/Movement.h>
#include <shared/Wheel/Wheel.h>

class Diff2 : public Movement
{
public:
    enum
    {
        L,
        R,
        NUM
    };

    Diff2(MD *md[NUM]);
    Diff2(MD *md_L, MD *md_R);
    Diff2(Wheel *wheel[NUM]);

    virtual void move(double x, double y, double yaw);

private:
    Wheel *wheel[NUM];
}; 

#endif