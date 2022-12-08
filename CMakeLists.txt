cmake_minimum_required(VERSION 3.23)
project(Sharlin C)

set(CMAKE_C_STANDARD 23)

add_executable(Sharlin main.c utilsfun.h utilsfun.c vec.h vec.c pcardlib.h pcardlib.c playerlib.h playerlib.c gameterminallib.h gameterminallib.c libgenericgame.h)