#include "GCodeReader.h"
GCodeReader::GCodeReader(Eigen::Vector3d *current_position, Eigen::Vector3d *target_position)
	: _current_position(current_position), _target_position(target_position)
{}

void GCodeReader::read_g_code(const std::string &g_code)
{
	Eigen::Vector3d target_position;
	std::vector<std::string> strings;

	strings = split_space(g_code);

	switch(strings[0][0]){
	case 'g':
	case 'G':
		int code_num;
		std::stringstream ss;

		ss.str("");
		ss.clear(std::stringstream::goodbit);
		ss << strings[0];
		ss.ignore();
		ss >> code_num;

		switch(code_num){
		case 0:
			_function_g_00(strings);
			break;
		case 4:
			_function_g_04(strings);
			break;
		}
		break;
	}
}

void GCodeReader::_function_g_00(const std::vector<std::string> &strings)
{
	double value;
	std::stringstream ss;
	for(int i = 1; i < strings.size(); i++){

		ss.str("");
		ss.clear(std::stringstream::goodbit);
		ss << strings[i];
		ss.ignore();
		ss >> value;

		switch(strings[i][0]){
		case 'x':
		case 'X':
			(*_target_position)(Movement::X) = value;
			break;
		case 'y':
		case 'Y':
			(*_target_position)(Movement::Y) = value;
			break;
		case 'z':
		case 'Z':
			(*_target_position)(Movement::Yaw) = value * M_PI;
			break;
		}
	}
}

void GCodeReader::_function_g_04(const std::vector<std::string> &strings)
{
	double value;
	std::stringstream ss;
	ss.str("");
	ss.clear(std::stringstream::goodbit);
	ss << strings[1];
	ss.ignore();
	ss >> value;

	switch(strings[1][0]){
	case 'x':
	case 'X':
		thread_sleep_for(value*1000);
		break;
	case 'p':
	case 'P':
        thread_sleep_for(value);
		//wait(value * 0.001);
		break;
	}
}

std::vector<std::string> GCodeReader::split_space(const std::string &str)
{
    return split(str, ' ');
}


std::vector<std::string> GCodeReader::split(const std::string &str, char sep)
{
    std::vector<std::string> strings;
    std::stringstream ss(str);
    std::string buffer;
    while( std::getline(ss, buffer, sep) ) {
        strings.push_back(buffer);
    }
    return strings;
}
