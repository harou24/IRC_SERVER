#!/bin/bash

echo "------------------Running basic tests------------------"
./build/apps/irc_basic_test.out &
wait $!

echo "------------------Running messaging tests------------------"
./build/apps/irc_messaging_test.out &
wait $!

echo "------------------Running channel tests------------------"
./build/apps/irc_channel_test.out &
wait $!