configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/cxxopts-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cxxopts-download)
if (result)
    message(FATAL_ERROR "CMake step for libcxxopts failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cxxopts-download)
if (result)
    message(FATAL_ERROR "Build step for libcxxopts failed: ${result}")
endif ()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/cxxopts-src
        ${CMAKE_CURRENT_BINARY_DIR}/cxxopts-build
        EXCLUDE_FROM_ALL)
