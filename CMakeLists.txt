cmake_minimum_required(VERSION 3.17)
project(CLinkedList C)

set(CMAKE_C_STANDARD 11)

add_executable(CLinkedList clinkedlist.h error.h main.c)