cmake_minimum_required (VERSION 2.6)
PROJECT (libnet) 

SET(CMAKE_CXX_FLAGS "-W -Wall")

SET(SRCS main.cpp)

ADD_LIBRARY (net SHARED ${SRCS})
