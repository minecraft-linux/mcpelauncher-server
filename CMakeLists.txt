cmake_minimum_required (VERSION 2.6)

project(mcpelauncher-server LANGUAGES CXX)

add_executable(mcpelauncher-server src/main.cpp src/server_properties.h)
target_link_libraries(mcpelauncher-server logger mcpelauncher-core properties-parser)