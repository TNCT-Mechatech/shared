#ifndef PID_CONTROL_H_
#define PID_CONTROL_H_


//ZNはジーグラ・ニコルス法の略である。
class PID_Control
{
public:
    enum
    {
        PAST,
        PRESENT,
        NUM
    };

    PID_Control(double kp = 0, double ki = 0, double kd = 0, double kf = 0);
    PID_Control(double ku = 0, double pu = 0);
    
    double PID(double present, double target, double interval);

    void reset();
    void set_PID(double kp, double ki, double kd, double kf);
    void set_PID_ZN(double ku, double pu);
        
private:
    
    double _diff[NUM];
    double _integral;
    double _p, _i, _d, _ff;
    double _kp, _ki, _kd,
           _kf; 
};

#endif
