#include <mbed.h>
#include <shared/Mbed_MD/Mbed_MD.h>

Mbed_MD::Mbed_MD(PinName pwmPin,PinName dirPin): _pwmOut(pwmPin), _dirOut(dirPin)
{
    _pwmOut.period(0.0005);
    //_pwmOut.period(0.0001);
}

void Mbed_MD::drive(double duty)
{
    if(duty >= 0){   
        _pwmOut.write(duty);
        _dirOut = 0;
    }else
    if(duty < 0){    
        _pwmOut.write(-duty);
        _dirOut = 1;
    }
}

void Mbed_MD::brake(double duty)
{
}

void Mbed_MD::free()
{
    _pwmOut.write(0);
    _dirOut = 0;
}