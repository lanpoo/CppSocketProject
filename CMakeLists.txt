cmake_minimum_required(VERSION 3.15)

PROJECT(socket)
#PROJECT(HELLO)
#set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11")
#AUX_SOURCE_DIRECTORY(. SRC_LIST)
#ADD_EXECUTABLE(hello ${SRC_LIST})


add_executable(client client.cpp)
add_executable(hospitalA hospitalA.cpp)
add_executable(hospitalB hospitalB.cpp)
add_executable(hospitalC hospitalC.cpp)
add_executable(scheduler scheduler.cpp)
find_package(Threads)

target_link_libraries(client ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(hospitalA ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(hospitalB ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(hospitalC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(scheduler ${CMAKE_THREAD_LIBS_INIT})