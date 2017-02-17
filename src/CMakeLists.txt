# group files
file(GLOB source_files *.cpp *.h)

# Use lcov
add_definitions ("-fprofile-arcs -ftest-coverage")

# Create lib for tu
add_library(tc_lib STATIC ${source_files})

# Create exe
add_executable(${PROJECT_NAME} ${source_files})

# Link library for lcov
target_link_libraries(${PROJECT_NAME} -lgcov)
