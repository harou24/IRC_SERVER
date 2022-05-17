#!/bin/bash

echo "------------------Running password tests------------------"
./build/apps/irc_password_test.out &
wait $!

#echo "------------------Running connect many users tests------------------"
./build/apps/irc_connect_many_test.out &
wait $!

#echo "------------------Running basic tests------------------"
./build/apps/irc_basic_test.out &
wait $!

#echo "------------------Running basic tests------------------"
./build/apps/irc_basic_test.out &
wait $!

#echo "------------------Running messaging tests------------------"
./build/apps/irc_messaging_test.out &
wait $!

#echo "------------------Running channel tests------------------"
./build/apps/irc_channel_test.out &
wait $!

echo "------------------Running topic tests------------------"
./build/apps/irc_topic_test.out &
wait $!