add_executable(server.out server.cpp)
add_executable(client.out client.cpp)
target_link_libraries(server.out PRIVATE ft_irc)
target_link_libraries(client.out PRIVATE ft_irc)