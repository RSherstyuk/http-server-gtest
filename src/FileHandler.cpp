#include "FileHandler.h"
#include "Logger.h"

#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

std::string FileHandler::read_file(const std::string &path) {
  std::fstream file(path, std::ios::binary);
  if (!file) {
    Logger::error("Failed to open file " + path);
  }
  return std::string((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
};

bool FileHandler::whrite_file(const std::string &path, std::string &content) {
  std::ofstream file(path, std::ios::binary);
  if (!file) {
    Logger::error("Failed to open file " + path);
    return false;
  }
  file << content;
  return true;
};

bool FileHandler::delete_file(const std::string& path) {
  if (!boost::filesystem::remove(path)){
    Logger::error("File dosent not remove ");
    return false;
  };
  return true;
}
