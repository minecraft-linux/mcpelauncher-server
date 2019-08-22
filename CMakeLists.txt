cmake_minimum_required (VERSION 2.6)

project(mcpelauncher-server LANGUAGES CXX)

add_executable(mcpelauncher-server src/main.cpp src/stub_key_provider.h src/server_minecraft_app.h src/server_properties.h src/console_reader.cpp src/console_reader.h src/v8_platform.cpp src/v8_platform.h)
target_link_libraries(mcpelauncher-server logger mcpelauncher-core properties-parser argparser)

install(TARGETS mcpelauncher-server RUNTIME DESTINATION bin)
include(CPackSettings.cmake)
