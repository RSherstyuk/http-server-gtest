#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
  public:
    static std::string read_file(const std::string& path);
    static bool whrite_file(const std::string& path, std::string& content);
    static bool delete_file(const std::string& path);
};

#endif