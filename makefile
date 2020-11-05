g++ testServer.cpp ./Server/TCPServer.cpp ./Commons/Epoll.cpp ./Commons/TCPSocket.cpp ./Protobuf/message.pb.cc -o server -std=c++11 `pkg-config --cflags --libs protobuf`

g++ testClient.cpp ./Client/TCPClient.cpp ./Commons/Epoll.cpp ./Commons/TCPSocket.cpp ./Protobuf/message.pb.cc -o client -std=c++11 `pkg-config --cflags --libs protobuf`
