### Configuration
cmake_minimum_required(VERSION 2.8)

project(LibOL)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

include_directories("${PROJECT_SOURCE_DIR}/src")

### LibOL
set(LIBOL_SOURCES
  src/libol/Blowfish/blowfish.cpp
  src/libol/ChunkHeader.cpp
  src/libol/File.cpp
  src/libol/Header.cpp
  src/libol/PayloadHeader.cpp
)

if(CMAKE_GENERATOR MATCHES "Xcode")
  FILE(GLOB_RECURSE LIBOL_INC "src/libol/*.h")
  SET(LIBOL_SOURCES ${LIBOL_SOURCES} ${LIBOL_INC})
endif()

add_library(OL ${LIBOL_SOURCES})

### zlib
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
  include_directories(${ZLIB_INCLUDE_DIRS})
  target_link_libraries(OL ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)

### Test LibOL
set(LIBOL_TEST_SOURCES
  src/libol_test/main.cpp
)

if(CMAKE_GENERATOR MATCHES "Xcode")
  FILE(GLOB_RECURSE LIBOL_TEST_INC "src/libol_test/*.h")
  SET(LIBOL_TEST_SOURCES ${LIBOL_TEST_SOURCES} ${LIBOL_TEST_INC})
endif()

add_executable(testLibOL ${LIBOL_TEST_SOURCES})
target_link_libraries(testLibOL OL)

