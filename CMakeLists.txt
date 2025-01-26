cmake_minimum_required(VERSION 3.18)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск Boost
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Добавляем Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

include_directories(/usr/include) # Для Linux


# Добавляем все исходные файлы из src
file(GLOB SRC_SOURCES src/*.cpp)

# Добавляем основную программу
add_executable(app ${SRC_SOURCES})

# Добавляем все исходные файлы из test
file(GLOB TEST_SOURCES test/*.cpp)

# Добавляем тесты
add_executable(tests ${TEST_SOURCES})

# Линкуем Google Test к тестам
target_link_libraries(tests PRIVATE gtest_main)

# Линкуем Boost к основному приложению и тестам
target_link_libraries(app PRIVATE Boost::filesystem Boost::system)
target_link_libraries(tests PRIVATE Boost::filesystem Boost::system)

# Линкуем основную программу и тесты к вашему коду
target_include_directories(app PRIVATE include)
target_include_directories(tests PRIVATE include)