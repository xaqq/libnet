cmake_minimum_required (VERSION 2.6)
PROJECT (libnet)

IF (UNIX)
SET(CMAKE_CXX_FLAGS "-W -Wall -std=c++11")
ENDIF (UNIX)
INCLUDE_DIRECTORIES("includes")

IF (WIN32)
SET(SRCS src/ServerFactory.cpp
src/RingBuffer.cpp
src/WinTcpServer.cpp
src/WinTcpSocket.cpp
src/WinUdpServer.cpp)
ENDIF (WIN32)
IF (UNIX)
SET(SRCS src/ServerFactory.cpp
src/UnixTcpServer.cpp
src/UnixTcpSocket.cpp
src/UnixUdpServer.cpp
src/RingBuffer.cpp)
ENDIF (UNIX)
ADD_LIBRARY (net STATIC ${SRCS})

