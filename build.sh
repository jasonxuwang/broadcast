git pull
sleep 3
g++ testClient.cpp ./Commons/*.cpp ./Client/TCPClient.cpp ./Protobuf/message.pb.cc  -o cli -std=c++11 `pkg-config --cflags --libs protobuf`
g++ testServer.cpp ./Commons/*.cpp ./Server/TCPServer.cpp ./Protobuf/message.pb.cc  -o serv -std=c++11 `pkg-config --cflags --libs protobuf`



