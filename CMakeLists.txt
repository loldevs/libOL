### Configuration
cmake_minimum_required (VERSION 2.8)

project (LibOL)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

include_directories ("${PROJECT_SOURCE_DIR}/include")

### LibOL
add_library(OL
  libol/Blowfish/blowfish.cpp
  libol/ChunkHeader.cpp
  libol/File.cpp
  libol/Header.cpp
  libol/main.cpp
  libol/PayloadHeader.cpp
)

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(OL ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)
