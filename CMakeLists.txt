cmake_minimum_required(VERSION 3.16.0)
project(CppUtilityToolkit LANGUAGES C CXX)


# Include header files
include_directories("${CMAKE_SOURCE_DIR}/include")


# Exceptions library
add_library(CUTExcepts STATIC   "${CMAKE_SOURCE_DIR}/src/excepts/nullptrexcept.cpp"
                                "${CMAKE_SOURCE_DIR}/src/excepts/assertexcept.cpp"
                                "${CMAKE_SOURCE_DIR}/src/excepts/boundsexcept.cpp")

# Time library
add_library(CUTTime STATIC  "${CMAKE_SOURCE_DIR}/src/time/timestamp.cpp"
                            "${CMAKE_SOURCE_DIR}/src/time/timer.cpp")
target_link_libraries(CUTTime CUTExcepts)

# Logging library
add_library(CUTLog STATIC "${CMAKE_SOURCE_DIR}/src/log/log.cpp")
target_link_libraries(CUTLog CUTExcepts CUTTime)

# Algorithms & data structures library
add_library(CUTAlgo STATIC "${CMAKE_SOURCE_DIR}/src/algo/minheap.cpp")
target_link_libraries(CUTAlgo CUTExcepts)




# Test applications
add_executable(TestExceptions "${CMAKE_SOURCE_DIR}/src/tests/excepts.cpp")
target_link_libraries(TestExceptions CUTExcepts)

add_executable(TestAlloc "${CMAKE_SOURCE_DIR}/src/tests/allocation.cpp")
target_link_libraries(TestAlloc CUTExcepts)

add_executable(TestTime "${CMAKE_SOURCE_DIR}/src/tests/time.cpp")
target_link_libraries(TestTime CUTTime)

add_executable(TestLog "${CMAKE_SOURCE_DIR}/src/tests/log.cpp")
target_link_libraries(TestLog CUTLog)

add_executable(TestAlgo "${CMAKE_SOURCE_DIR}/src/tests/algo.cpp")
target_link_libraries(TestAlgo CUTAlgo)