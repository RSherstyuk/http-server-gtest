#include "Fact.h"
#include "Server.h"
#include <exception>
#include <iostream>

int main() {
  try {
    Server server("0.0.0.0", 8080);
    server.run();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}