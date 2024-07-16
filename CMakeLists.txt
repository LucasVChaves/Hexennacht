cmake_minimum_required(VERSION 3.10)

project(MetaFetch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
include_directories(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(metafetch 
  src/main.cpp
  src/Hexdumper.cpp
  src/MetadataFetcher.cpp
  src/Hexeditor.cpp
  lib/rope/rope.c
)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(metafetch ${CURSES_LIBRARIES})
target_include_directories(metafetch PUBLIC src)

install(TARGETS metafetch DESTINATION bin)
install(FILES src/Hexdumper.hpp DESTINATION include)
install(FILES src/MetadataFetcher.hpp DESTINATION include)
install(FILES src/Hexeditor.hpp DESTINATION include)
