# git pull
# sleep 1

# cd ./Protobuf
# protoc --cpp_out=./ message.proto
# cd ..

#export LD_LIBRARY_PATH=/usr/local/lib
#export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig


g++ testClient.cpp ./Commons/*.cpp ./Client/TCPClient.cpp ./Protobuf/message.pb.cc  -o cli -std=c++11 `pkg-config --cflags --libs protobuf`
g++ testServer.cpp ./Commons/*.cpp ./Server/TCPServer.cpp ./Protobuf/message.pb.cc  -o serv -std=c++11 `pkg-config --cflags --libs protobuf`
# g++ testGate.cpp ./Commons/*.cpp ./Server/*.cpp ./Protobuf/message.pb.cc  -o gate -std=c++11 `pkg-config --cflags --libs protobuf`
