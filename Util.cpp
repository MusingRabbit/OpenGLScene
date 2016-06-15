#include "Util.h"

Util::Util()
{
}


Util::~Util()
{
}

std::vector<std::string> Util::SplitString(const std::string &s, char delim) {
	std::vector<std::string> result;

	const char* cstr = s.c_str();
	unsigned int strLength = s.length();
	unsigned int start = 0;
	unsigned int end = 0;

	while (end <= strLength) 
	{
		while (end <= strLength)
		{
			if (cstr[end] == delim)
				break;

			end++;
		}
		result.push_back(s.substr(start, end - start));
		start = end + 1;
		end = start;
	}

	return result;
}

std::string Util::LoadFile(const std::string& filePath)
{
	std::string sResult = "";
	std::string sCurrLine = "";

	std::ifstream file;
	file.open(filePath.c_str());

	if (file.is_open()) 
	{
		while (file.good())
		{
			std::getline(file, sCurrLine);
			sResult.append(sCurrLine+"\n");
		}
	}
	else 
	{
		std::cerr << "File load exception! Unable to load file at " + filePath << std::endl;
		throw "File load exception! Unable to load file at " + filePath;
	}

	return sResult;
}

//std::string Util::LoadFile(const std::string& filePath) {
//	//Use C's fopen to open, and find the file size
//	FILE* f = fopen(filePath.c_str(), "r");
//	fseek(f, 0, SEEK_END);
//	size_t size = ftell(f);
//
//	std::ifstream file(filePath);
//	std::streambuf* buffer = file.rdbuf();
//	char * block = new char[size];
//	buffer->sgetn(block, size);
//	
//	std::string result(block);
//	delete[] block;
//
//	return result;
//}