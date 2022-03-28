add_executable(echo_server server.cpp)
add_executable(echo_client client.cpp)
add_executable(multiserver multiserver.cpp)

target_link_libraries(echo_server PRIVATE ft_irc)
target_link_libraries(echo_client PRIVATE ft_irc)
target_link_libraries(multiserver PRIVATE ft_irc)


add_executable(infinite_loop.out infinite_loop.cpp)
add_executable(stop_loop.out stop_loop.cpp)
