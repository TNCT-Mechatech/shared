#ifndef ODOMETRY2_H_
#define ODOMETRY2_H_

#include <shared/OdometryWheel/OdometryWheel.h>
#include <math.h>

class Odometry2 
{
public:
    enum Wheel
    {
        L,
        R,
        NUM
    };

    Odometry2(OdometryWheel *wheel[NUM]);
    virtual ~Odometry2(){};

    /*
    Eigen::Vector3d read_position();

    void write_position(const Eigen::Vector3d &set_position);
    void reset_position();
    void set_coefficient_matrix();
    */

    void get_velocity(double vel[]);

    enum VectorElements
    {
        X,
        Y,
        Yaw
    };

private:
    //Timer _tim;
    void _read_velocity();
    //void _set_coefficient_matrix();

    OdometryWheel *_wheel[NUM];
    double _vel[3];
    /*
    Eigen::Matrix3d _coefficient_matrix;
    Eigen::Vector3d _position;
    Eigen::Vector3d _last_velocity;
    */
};

#endif