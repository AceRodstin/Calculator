//
// Created by Ace Rodstin on 25 Nov 2022.
//

#include <vector>
#include <sstream>
#include "../../include/lib/FileManager.h"

void FileManager::open_file(string path, OpenOption open_option) {
	if (file.is_open()) {
		FileManager::close_file();
	}

	ios::openmode mode;

	switch (open_option) {
		case FileManager::OpenOption::read:
			mode = ios::in;
			break;
		case FileManager::OpenOption::write:
			mode = ios::out;
			break;
		case FileManager::OpenOption::append:
			mode = ios::app;
			break;
	}

	file = fstream(path, mode);
}

void FileManager::write(string text) {
	file << text;
}

string FileManager::read() {
	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

void FileManager::close_file() {
	file.close();
}
