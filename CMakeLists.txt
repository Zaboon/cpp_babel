cmake_minimum_required(VERSION 3.3)
project(cpp_babel)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Project2/Linux/LinuxMutex.hpp
    Project2/Linux/LinuxThread.hpp
    Project2/Linux/main.cpp
    Project2/IMutex.hpp
    Project2/ISocket.h
    Project2/IThread.hpp
    Project2/MutexVault.hpp Project2/Packet.h
    Project2/Linux/LinuxSocket.cpp
    Project2/Linux/LinuxSocket.h Project2/MutexVault.cpp.cpp Project2/MutexVault.cpp.h Babel/BabelServer.cpp Babel/BabelServer.hpp)

add_executable(cpp_babel ${SOURCE_FILES})