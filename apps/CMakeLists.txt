add_executable(table.out Table.cpp)
target_link_libraries(table.out PRIVATE ft_irc)

add_executable(parser.out parser.cpp)
target_link_libraries(parser.out PRIVATE ft_irc)

add_executable(echo_server server.cpp)
add_executable(echo_client client.cpp)
add_executable(server multiserver.cpp)
add_executable(irc irc.cpp)

target_link_libraries(echo_server PRIVATE ft_irc)
target_link_libraries(echo_client PRIVATE ft_irc)
target_link_libraries(server PRIVATE ft_irc)
target_link_libraries(irc PRIVATE ft_irc)


add_executable(infinite_loop.out infinite_loop.cpp)
add_executable(stop_loop.out stop_loop.cpp)

add_executable(tcpStream.out tcpStream.cpp)
target_link_libraries(tcpStream.out  PRIVATE ft_irc)