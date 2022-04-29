# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(ft_irc LANGUAGES CXX)

option(TEST "TEST" OFF)

# require C++ 98
if(TEST)
    set(CMAKE_CXX_STANDARD 11)
    message("TEST ENABLED c++ version is 11")
else()
    set(CMAKE_CXX_STANDARD 98)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -fsanitize=address")

# include header files
include_directories(include)
include_directories(src/utils/Table)

include_directories(src/tcp)
include_directories(src/server)
include_directories(src/multi_client_handler)
include_directories(src/client)
include_directories(src/irc_server)
include_directories(src/connectable_client)
include_directories(src/commands)
include_directories(src/parser)
include_directories(src/cmd_controller)
include_directories(src/message)

# example library
add_library(ft_irc src/utils/Table/Row.cpp
                    src/utils/Table/Table.cpp
                    src/tcp/tcp_acceptor.cpp
                    src/tcp/tcp_connector.cpp
                    src/tcp/tcp_stream.cpp
                    src/multi_client_handler/multi_client_handler.cpp
                    src/message/message.cpp
                    src/server/server.cpp
                    src/parser/parser.cpp
                    src/client/client.cpp
                    src/irc_server/irc_server.cpp
                    src/connectable_client/connectable_client.hpp
                    src/commands/nick.cpp
                    src/commands/ping.cpp
                    src/commands/welcome.cpp
                    src/commands/user.cpp
                    src/commands/unknown.cpp
                    src/cmd_controller/cmd_controller.cpp
)

# add programs
add_subdirectory(apps)

# for unitests
if(TEST)
	message("running tests")
	include(CTest)
	include(FetchContent)
	add_subdirectory(tests)
endif()
