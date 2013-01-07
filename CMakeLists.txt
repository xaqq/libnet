cmake_minimum_required (VERSION 2.6)
PROJECT (libnet)

SET(CMAKE_CXX_FLAGS "-W -Wall -std=c++11")
INCLUDE_DIRECTORIES("includes")

SET(SRCS src/ServerFactory.cpp
src/UnixTcpServer.cpp
src/UnixTcpSocket.cpp
src/UnixUdpServer.cpp
src/RingBuffer.cpp)

ADD_LIBRARY (net SHARED ${SRCS})
