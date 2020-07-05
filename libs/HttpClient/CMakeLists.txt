project(HttpClient)

if (${BUILD_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif ()

add_library(http_client src/HttpClient/HttpClient.cpp src/HttpClient/HttpClientImplementation.cpp src/HttpClient/HttpClientBuilderImplementation.cpp)

target_link_libraries(http_client PRIVATE curlpp_static)
target_include_directories(http_client PUBLIC include)
target_compile_features(http_client PUBLIC cxx_std_20)
set_target_properties(http_client PROPERTIES CXX_EXTENSIONS OFF)

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
    set_target_properties(http_client PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
