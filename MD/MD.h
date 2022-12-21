#ifndef MD_H_
#define MD_H_

class MD
{
public:
    virtual ~MD(){}
    virtual void drive(double) = 0;
    virtual void brake(double) = 0;
    virtual void free() = 0;
};

#endif