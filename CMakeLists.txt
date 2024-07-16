cmake_minimum_required(VERSION 3.10)

project(Hexennacht)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
include_directories(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

add_executable(hexennacht 
  src/main.cpp
  src/Hexdumper.cpp
  src/MetadataFetcher.cpp
)

target_include_directories(hexennacht PUBLIC src)

install(TARGETS hexennacht DESTINATION bin)
install(FILES src/Hexdumper.hpp DESTINATION include)
install(FILES src/MetadataFetcher.hpp DESTINATION include)
