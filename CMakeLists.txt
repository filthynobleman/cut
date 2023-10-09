cmake_minimum_required(VERSION 3.16.0)
project(CppUtilityToolkit LANGUAGES C CXX)


# Include header files
include_directories("${CMAKE_SOURCE_DIR}/include")


# Exceptions library
add_library(CUTExcepts STATIC   "${CMAKE_SOURCE_DIR}/src/excepts/nullptrexcept.cpp"
                                "${CMAKE_SOURCE_DIR}/src/excepts/assertexcept.cpp"
                                "${CMAKE_SOURCE_DIR}/src/excepts/boundsexcept.cpp")





# Test applications
add_executable(TestExceptions "${CMAKE_SOURCE_DIR}/src/tests/excepts.cpp")
target_link_libraries(TestExceptions CUTExcepts)