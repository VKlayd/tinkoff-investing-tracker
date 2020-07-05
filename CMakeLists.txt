project(TinkoffWatcher)
cmake_minimum_required(VERSION 3.16)

option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(external/libcurlpp)
add_subdirectory(external/nlohmann_json)
add_subdirectory(external/cxxopts)
add_subdirectory(libs/HttpClient)

add_executable(tinkoff_watcher main.cpp)
target_link_libraries(tinkoff_watcher PRIVATE http_client)
target_link_libraries(tinkoff_watcher PRIVATE nlohmann_json::nlohmann_json cxxopts)
target_compile_features(tinkoff_watcher PUBLIC cxx_std_20)
set_target_properties(tinkoff_watcher PROPERTIES CXX_EXTENSIONS OFF)

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
    set_target_properties(tinkoff_watcher PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
