#include "Logger.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>

class LoggerTest : public ::testing::Test {
protected:
  void SetUp() override {
    std::cout.rdbuf(buffer_cout.rdbuf());
    std::cerr.rdbuf(buffer_cerr.rdbuf());
  }

  std::stringstream buffer_cout;
  std::stringstream buffer_cerr;
  std::streambuf *cout_backup = std::cout.rdbuf();
  std::streambuf *cerr_backup = std::cerr.rdbuf();
};

TEST_F(LoggerTest, LogMassage) {
  Logger::log("Test log massage");
  EXPECT_EQ(buffer_cout.str(), "[LOG] Test log message\n");
}

TEST_F(LoggerTest, ErrorMessage) {
    Logger::error("Test error message");
    EXPECT_EQ(buffer_cerr.str(), "[ERROR] Test error message\n");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}