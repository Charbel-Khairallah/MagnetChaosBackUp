#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class File {
public:
	static std::vector<std::string> Read(std::string path);
	static void Write(std::string path, std::vector<std::string> data);
};
