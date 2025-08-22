cmake_minimum_required(VERSION 3.22)

# Project name
project(candlesdk-win-driver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

add_executable(candlesdk-win-driver main.cpp)


set(LIBWDI_INCLUDE ${CMAKE_SOURCE_DIR}/libwdi/libwdi)
set(LIBWDI_LIB ${LIBWDI_INCLUDE}/.libs/libwdi.a)

target_include_directories(candlesdk-win-driver PUBLIC ${LIBWDI_INCLUDE})

target_link_libraries(candlesdk-win-driver ${LIBWDI_LIB} setupapi -static)
