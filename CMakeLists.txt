project(argshandler)
cmake_minimum_required(VERSION 3.8)
set(CMAKE_C_STANDARD 90)

add_executable(argshandler
	example/main.c
	argshandler/argshandler.c
	argshandler/argshandler.h
)
