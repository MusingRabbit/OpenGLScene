#ifndef UTIL_H
#define UTIL_H

#include<iostream>
#include<fstream>
#include<string>
#include <vector>

class Util
{
public:
	Util();
	~Util();

	static std::string LoadFile(const std::string & filePath);
	static std::vector<std::string> SplitString(const std::string &s, char delim);
};


#endif // !UTIL_H
