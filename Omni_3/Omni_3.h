#ifndef OMNI_3_H_
#define OMNI_3_H_

#include <shared/Movement/Movement.h>
#include <shared/Wheel/Wheel.h>

class Omni_3 : public Movement
{
public:
    enum
    {
        F,
        L,
        R,
        NUM
    };
    
    Omni_3(MD *md[NUM]);
    Omni_3(MD *md_F, MD *md_L, MD *md_R);
    Omni_3(Wheel *wheel[NUM]);
    virtual ~Omni_3(){};
    
    virtual void move(double x, double y, double yaw);
    
    
private:
    Wheel *_wheel[NUM];

};

#endif

