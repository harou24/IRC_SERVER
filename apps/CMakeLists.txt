add_executable(table.out ./table/Table.cpp)
target_link_libraries(table.out PRIVATE ft_irc)

add_executable(parser.out ./parser/parser.cpp)
target_link_libraries(parser.out PRIVATE ft_irc)

add_executable(echo_server ./server/server.cpp)
add_executable(echo_client ./client/client.cpp)
add_executable(server ./server/multiserver.cpp)
add_executable(irc ./irc/irc.cpp)

target_link_libraries(echo_server PRIVATE ft_irc)
target_link_libraries(echo_client PRIVATE ft_irc)
target_link_libraries(server PRIVATE ft_irc)
target_link_libraries(irc PRIVATE ft_irc)


add_executable(infinite_loop.out ./experiment/infinite_loop.cpp)
add_executable(stop_loop.out ./experiment/stop_loop.cpp)


add_executable(serverTest.out ./server/serverTest.cpp)
target_link_libraries(serverTest.out PRIVATE ft_irc)