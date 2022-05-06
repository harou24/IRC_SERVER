add_executable(table.out ./utils/Table.cpp)
target_link_libraries(table.out PRIVATE ft_irc)

add_executable(parser.out ./parser/parser.cpp)
target_link_libraries(parser.out PRIVATE ft_irc)

add_executable(echo_server ./server/tcp_acceptor.cpp)
target_link_libraries(echo_server PRIVATE ft_irc)

add_executable(echo_client ./client/tcp_connector.cpp)
target_link_libraries(echo_client PRIVATE ft_irc)

add_executable(server ./server/server.cpp)
target_link_libraries(server PRIVATE ft_irc)

add_executable(irc_server ./irc/irc_server.cpp)
target_link_libraries(irc_server PRIVATE ft_irc)

add_executable(infinite_loop.out ./experiment/infinite_loop.cpp)
add_executable(stop_loop.out ./experiment/stop_loop.cpp)


if(TEST)
    add_executable(test_server_start_stop.out ./server/test_server_start_stop.cpp)
    target_link_libraries(test_server_start_stop.out PRIVATE ft_irc)

    add_executable(test_server_messaging.out ./server/test_server_messaging.cpp)
    target_link_libraries(test_server_messaging.out PRIVATE ft_irc)

    add_executable(irc_server_test.out ./irc/irc_server_test.cpp)
    target_link_libraries(irc_server_test.out PRIVATE ft_irc)
endif()
