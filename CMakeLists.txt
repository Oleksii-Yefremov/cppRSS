# Sets the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Sets the project name and the language
project(RSS_Telegram_Bot LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This creates your .exe. It tells CMake: 
# "Take main.cpp and turn it into an executable named BotApp"
add_executable(cppRSS main.cpp)