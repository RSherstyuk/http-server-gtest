#include "Logger.h"

#include <string>
#include <iostream>

void Logger::log(const std::string& message) { 
    std::cout << "[LOG] " << message << std::endl;
}

void Logger::error(const std::string& massage) {
  std::cerr << "[ERROR] " << error << std::endl;
}