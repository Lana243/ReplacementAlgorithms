cmake_minimum_required(VERSION 3.19)
project(ReplacementAlgorithms)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)

add_executable(ReplacementAlgorithms src/main.cpp include/replacement_algorithms.h include/fifo.h include/lru.h include/clock.h include/opt.h include/rand.h)