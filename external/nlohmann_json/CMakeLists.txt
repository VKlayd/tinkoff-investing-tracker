configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt.in ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download)
if (result)
    message(FATAL_ERROR "CMake step for libnlohmann_json failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download)
if (result)
    message(FATAL_ERROR "Build step for libnlohmann_json failed: ${result}")
endif ()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src
        ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-build
        EXCLUDE_FROM_ALL)
