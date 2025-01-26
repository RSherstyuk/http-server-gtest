#include "FileHandler.h"
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>
#include <string>

namespace fs = boost::filesystem;

class FileHandlerTest : public ::testing::Test {
protected:
  void SetUp() override {
    test_file_path = "test_file.txt";
    test_content = "Test content";
  }

  void TearDown() override {
    if (fs::exists(test_file_path)) {
      fs::remove(test_file_path);
    }
  }

  std::string test_file_path;
  std::string test_content;
};

TEST_F(FileHandlerTest, WriteAndReadFile) {
  EXPECT_TRUE(FileHandler::whrite_file(test_file_path, test_content));

  std::string content = FileHandler::read_file(test_file_path);
  EXPECT_EQ(content, test_content);
}

TEST_F(FileHandlerTest, ReadNonExistentFile) {
  std::string content = FileHandler::read_file("nonexistent.txt");
  EXPECT_TRUE(content.empty());
}

TEST_F(FileHandlerTest, DeleteFile) {
  EXPECT_TRUE(FileHandler::whrite_file(test_file_path, test_content));

  EXPECT_TRUE(FileHandler::delete_file(test_file_path));
  
  EXPECT_FALSE(fs::exists(test_file_path));
}

TEST_F(FileHandlerTest, DeleteNonExistentFile) {

  EXPECT_FALSE(FileHandler::delete_file("nonexistent.txt"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
