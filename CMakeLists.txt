cmake_minimum_required(VERSION 3.16.0)
project(CppUtilityToolkit)

# Library implemented in C/C++
enable_language(C)
enable_language(CXX)



# Include project headers
include_directories("${CMAKE_SOURCE_DIR}/include")

# Implementation files
set(CUT_CPP "${CMAKE_SOURCE_DIR}/src/excepts/assertexcept.cpp"
            "${CMAKE_SOURCE_DIR}/src/excepts/nullptrexcept.cpp"
            "${CMAKE_SOURCE_DIR}/src/excepts/boundsexcept.cpp"
            "${CMAKE_SOURCE_DIR}/src/time/timestamp.cpp"
            "${CMAKE_SOURCE_DIR}/src/time/timer.cpp"
            "${CMAKE_SOURCE_DIR}/src/log/log.cpp"
            "${CMAKE_SOURCE_DIR}/src/algo/minheap.cpp"
            "${CMAKE_SOURCE_DIR}/src/algo/adjlist/badjlist.cpp"
            "${CMAKE_SOURCE_DIR}/src/algo/adjlist/adjlist.cpp"
            "${CMAKE_SOURCE_DIR}/src/algo/adjlist/cadjlist.cpp"
)


# Create the library
add_library(cut STATIC ${CUT_CPP})
set_target_properties(cut PROPERTIES CXX_STANDARD 11)



# Option to build sample applications
option(BUILD_SAMPLES "Build sample applications for testing and how-to." OFF)

# Install
install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/cut"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/cut/include")
install(TARGETS cut
        LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/cut/lib"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/cut/lib"
        RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/cut/bin")



if (BUILD_SAMPLES)

    # Test applications
    add_executable(TestExceptions "${CMAKE_SOURCE_DIR}/src/tests/excepts.cpp")
    target_link_libraries(TestExceptions cut)

    add_executable(TestAlloc "${CMAKE_SOURCE_DIR}/src/tests/allocation.cpp")
    target_link_libraries(TestAlloc cut)

    add_executable(TestTime "${CMAKE_SOURCE_DIR}/src/tests/time.cpp")
    target_link_libraries(TestTime cut)

    add_executable(TestLog "${CMAKE_SOURCE_DIR}/src/tests/log.cpp")
    target_link_libraries(TestLog cut)

    add_executable(TestMinheap "${CMAKE_SOURCE_DIR}/src/tests/minheap.cpp")
    target_link_libraries(TestMinheap cut)

    add_executable(TestAdjlist "${CMAKE_SOURCE_DIR}/src/tests/adjlist.cpp")
    target_link_libraries(TestAdjlist cut)

endif()