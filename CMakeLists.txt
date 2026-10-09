cmake_minimum_required(VERSION 3.0.0)
project(WOOTANG C)
add_executable(wootang.exe wootang.c)

target_include_directories(wootang.exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(wooting_analog_sdk SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lib/wooting_analog_sdk_dist.dll)
set_target_properties(wooting_analog_sdk PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/wooting_analog_sdk_dist.dll
)
target_link_libraries(wootang.exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/wooting_analog_sdk_dist.dll.lib)