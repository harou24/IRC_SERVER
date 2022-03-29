add_executable(echo_server server.cpp)
add_executable(echo_client client.cpp)
target_link_libraries(echo_server PRIVATE ft_irc)
target_link_libraries(echo_client PRIVATE ft_irc)