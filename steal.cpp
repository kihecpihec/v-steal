#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <string>

void listFiles(const std::string &directoryPath) {
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir(directoryPath.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
				std::string newPath = directoryPath + "/" + std::string(ent->d_name);
				std::cout << "Directory: " << newPath << std::endl;
				listFiles(newPath);
			} else if (ent->d_type == DT_REG) {
				std::cout << "File: " << directoryPath << "/" << ent->d_name << std::endl;
			}
		}
		closedir(dir);
	} else {
		std::cerr << "Could not open directory " << directoryPath << std::endl;
	}
}

int main() {
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		std::cout << "Current working directory: " << cwd << std::endl;
		listFiles(cwd);
	} else {
		std::cerr << "Error getting current directory" << std::endl;
		return 1;
	}
	return 0;
}