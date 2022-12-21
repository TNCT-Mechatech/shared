#ifndef G_CODE_READER_H_
#define G_CODE_READER_H_

#include <shared/Movement/Movement.h>

#include <Dense.h>

#include <vector>
#include <string>
#include <iostream>

class GCodeReader
{
public:
	GCodeReader(Eigen::Vector3d *current_position, Eigen::Vector3d *target_position);
	virtual ~GCodeReader(){}

	void read_g_code(const std::string &g_code);

	std::vector<std::string> split_space(const std::string &str);
	std::vector<std::string> split(const std::string &str, char sep);
protected:

	Eigen::Vector3d *_current_position;
	Eigen::Vector3d *_target_position;

private:

	void _function_g_00(const std::vector<std::string> &strings);
	void _function_g_04(const std::vector<std::string> &strings);
};

#endif
