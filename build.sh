git pull
sleep 5
g++ testClient.cpp ./Commons/*.cpp ./Client/TCPClient.cpp ./Protobuf/message.pb.cc  -o client -std=c++11 `pkg-config --cflags --libs protobuf`
g++ testServer.cpp ./Commons/*.cpp ./Server/TCPServer.cpp ./Protobuf/message.pb.cc  -o server -std=c++11 `pkg-config --cflags --libs protobuf`
