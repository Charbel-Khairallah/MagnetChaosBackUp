#pragma once
#include "File.h"

//----------------------------------------- Read --------------------------------------//

std::vector<std::string> File::Read(std::string Path) {
	std::string Line;
	std::vector<std::string> Data;
	std::fstream In(Path, std::ios::in);
	while (getline(In, Line)) {
		Data.push_back(Line);
	}
	In.close();
	return Data;
}

//----------------------------------------- Write --------------------------------------//

void File::Write(std::string Path, std::vector<std::string> Data) {
	std::fstream Out(Path, std::ios::out);
	for (std::string Line : Data) {
		Out << Line << std::endl;
	}
	Out.close();
}