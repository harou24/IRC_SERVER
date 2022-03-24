# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(serverclient LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -fsanitize=address")

# include header files
include_directories(include)
include_directories(src/tcp)

# example library
add_library(ft_irc src/tcp/TcpConnector.cpp src/tcp/TcpAcceptor.cpp src/tcp/TcpStream.cpp)

# add programs
add_subdirectory(apps)

# for unitests
include(CTest)
include(FetchContent)
add_subdirectory(tests)
