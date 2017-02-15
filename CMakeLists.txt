cmake_minimum_required(VERSION 2.8)

#Disable in source compilation
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

project(Touche_Coule CXX)

set(CMAKE_CXX_FLAGS "-g -Wall -pthread -O0 -fprofile-arcs -ftest-coverage -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# Set files
file(GLOB source_files src/*.cpp src/*.h)
file(GLOB tu_files tu/*.cpp tu/*.h)

#creation de la lib
set(LIBRARY_OUTPUT_PATH lib)
set(TU_NAME tu_touche_coule)
include_directories(src)
add_library(tc_lib STATIC ${source_files})

# Create exe
add_executable(${PROJECT_NAME} ${source_files})
add_executable(${TU_NAME} ${tu_files})

# Link libraries
link_directories(${pwd}/../lib)
target_link_libraries(${TU_NAME} tc_lib)
target_link_libraries(${TU_NAME} cppunit)
target_link_libraries(${TU_NAME} pthread)

