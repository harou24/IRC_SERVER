# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(ft_irc LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -fsanitize=address")

# include header files
include_directories(include)
include_directories(src/utils/Table)

include_directories(src/parser)
include_directories(src/tcp)
include_directories(src/Server)
include_directories(src/MultiClientHandler)

# example library
add_library(ft_irc src/utils/Table/Row.cpp
                    src/utils/Table/Table.cpp
                    src/tcp/TcpAcceptor.cpp
                    src/tcp/TcpConnector.cpp
                    src/tcp/TcpStream.cpp
                    src/MultiClientHandler/MultiClientHandler.cpp
                    src/Server/Server.cpp
                    src/parser/parser.cpp)

# add programs
add_subdirectory(apps)

# for unitests
option(TEST "TEST" OFF)
if(TEST)
	message("running tests")
	include(CTest)
	include(FetchContent)
	add_subdirectory(tests)
endif()
