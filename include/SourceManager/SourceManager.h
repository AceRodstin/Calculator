//
// Created by Ace Rodstin on 15 Nov 2022.
//

#ifndef SOURCEMANAGER_SOURCEMANAGER_H
#define SOURCEMANAGER_SOURCEMANAGER_H


#include <string>
#include "../lib/FileManager.h"

using namespace std;

class SourceManager {
public:
	string read(string file_path);

private:
	FileManager file_manager;

	bool is_valid_extension(string file_path);
};


#endif //SOURCEMANAGER_SOURCEMANAGER_H
