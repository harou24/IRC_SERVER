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

    add_executable(irc_basic_test.out ./irc/irc_basic_test.cpp)
    target_link_libraries(irc_basic_test.out PRIVATE ft_irc)

    add_executable(irc_messaging_test.out ./irc/irc_messaging_test.cpp)
    target_link_libraries(irc_messaging_test.out PRIVATE ft_irc)

    add_executable(irc_channel_test.out ./irc/irc_channel_test.cpp)
    target_link_libraries(irc_channel_test.out PRIVATE ft_irc)

    add_executable(irc_topic_test.out ./irc/irc_topic_test.cpp)
    target_link_libraries(irc_topic_test.out PRIVATE ft_irc)

    add_executable(irc_mode_operator_test.out ./irc/irc_mode_operator_test.cpp)
    target_link_libraries(irc_mode_operator_test.out PRIVATE ft_irc)

    add_executable(irc_password_test.out ./irc/irc_password_test.cpp)
    target_link_libraries(irc_password_test.out PRIVATE ft_irc)
    
    add_executable(irc_connect_test.out ./irc/irc_connect_test.cpp)
    target_link_libraries(irc_connect_test.out PRIVATE ft_irc)

    add_executable(irc_connect_many_test.out ./irc/irc_connect_many_test.cpp)
    target_link_libraries(irc_connect_many_test.out PRIVATE ft_irc)
endif()
