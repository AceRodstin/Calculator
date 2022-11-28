//
// Created by Ace Rodstin on 25 Nov 2022.
//

#ifndef ACE_FILEMANAGER_H
#define ACE_FILEMANAGER_H


#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

class FileManager {
public:
	enum class OpenOption {
		read,
		write,
		append
	};

	void open_file(string path, OpenOption open_option);
	void write(string text);
	string read();
	void close_file();

private:
	fstream file;
};


#endif //ACE_FILEMANAGER_H
