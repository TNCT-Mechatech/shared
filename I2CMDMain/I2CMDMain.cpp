#include "I2CMDMain.h"

#include <math.h>

I2CMDMain::I2CMDMain(I2C *i2c_bus, int i2c_address, int motor_id, int retries)
    : _i2c_bus(i2c_bus),_i2c_address(i2c_address),_motor_id(motor_id)
	, _retries(retries), _error(true)
{
	for(int i = 0; i < 4; i++)
		send_data[i] = 0;
	send_flg = 0;
	send_length = 0;
}

void I2CMDMain::drive(double strength)
{
    uint8_t dir;
    char data[2];

    if(signbit(strength)) {
        dir = 1;
    } else {
        dir = 0;
    }

    data[0] = dir;
    data[1] = conv_strength_to_duty_u8(strength);

    i2c_write('D', data, 2);
}

void I2CMDMain::brake(double strength)
{
    char data[1];
    data[0] = conv_strength_to_duty_u8(strength);
    i2c_write('B', data, 1);
}

void I2CMDMain::free()
{
    char data[1] = {0};
    i2c_write('F', data, 1);
}

void I2CMDMain::set_retries(int retries)
{
	_retries = retries;
}

bool I2CMDMain::get_error()
{
	return _error;
}

bool I2CMDMain::i2c_send()
{
	bool error = true;
	if(send_flg){
	    for(int i = 0; i < _retries && error; i++) {
	    	error = _i2c_bus->write(_i2c_address, send_data, send_length);
	    }
		_error = error;
		send_flg = 0;
	}
    thread_sleep_for(1);
	return error;
}

bool I2CMDMain::i2c_write(int command, char *data, int length)
{
    send_length = 2 + length;
    int error = 0;

    send_data[0] = _motor_id;
    send_data[1] = command;
    for(int i = 0; i < length; i++) {
        send_data[i + 2] = data[i];
    }
    send_flg = 1;

    return (bool)error;
}

uint8_t I2CMDMain::conv_strength_to_duty_u8(double strength)
{
    double duty;
    uint8_t duty_u8;

    duty = fabs(strength);
    if(duty > 1.0) {
        duty = 1.0;
    }
    duty_u8 = floor(duty * 255);

    return duty_u8;
}
