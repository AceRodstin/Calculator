//
// Created by Ace Rodstin on 15 Nov 2022.
//

#include "../../include/SourceManager/SourceManager.h"
#include <filesystem>
#include "../../include/Ace.h"

string SourceManager::read(string file_path) {
	string result;

	if (is_valid_extension(file_path)) {
		file_manager.open_file(file_path, FileManager::OpenOption::read);
		result = file_manager.read();
		file_manager.close_file();
	} else {
		throw invalid_argument("Invalid file extension");
	}

	return result;
}

bool SourceManager::is_valid_extension(string file_path) {
	auto extension = filesystem::path(file_path).extension();
	return Ace::file_extensions.contains(extension);
}