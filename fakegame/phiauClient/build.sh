#!/bin/sh
g++ -I /usr/local/include/ -I /usr/phiau/code/fakegame -L /usr/local/lib client.cc ../phiauProto/lm.helloworld.pb.cc ../phiauProto/zone.test.pb.cc -DIS_CLIENT -lprotoc -levent -o client 
