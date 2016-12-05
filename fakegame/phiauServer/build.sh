#!/bin/sh
g++ -I /usr/local/include/ -I /usr/phiau/code/fakegame/ -L /usr/local/lib server_event.cpp ../phiauProto/lm.helloworld.pb.cc ../phiauProto/zone.test.pb.cc -lprotoc -levent -o server
