#ifndef I2CMDMAIN_H_
#define I2CMDMAIN_H_

#include <mbed.h>
#include <shared/MD/MD.h>

class I2CMDMain : public MD
{
public:
    I2CMDMain(I2C *i2c_bus, int i2c_address, int motor_id, int retries = 10);
    virtual void drive(double);
    virtual void brake(double);
    virtual void free();

    void set_retries(int);
    bool get_error();

    bool i2c_send();

private:
    bool i2c_write(int command, char *data, int length);
    uint8_t conv_strength_to_duty_u8(double);

    I2C *_i2c_bus;
    int _i2c_address;
    int _motor_id;

    int _retries;
    bool _error;

    char send_data[4];
    int send_length;
    bool send_flg;
};

#endif
