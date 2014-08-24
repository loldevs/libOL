### Configuration
cmake_minimum_required(VERSION 2.8)

project(libOL)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror -Wextra -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")

if("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wno-deprecated-declarations")
endif()

include_directories("${PROJECT_SOURCE_DIR}/src")

### libOL
set(LIBOL_SOURCES
  src/libOL/Blowfish/Blowfish.cpp
  src/libOL/ChunkHeader.cpp
  src/libOL/Chunks.cpp
  src/libOL/Header.cpp
  src/libOL/PayloadHeader.cpp
  src/libOL/Rofl.cpp
  src/libOL/Keyframe.cpp
  src/libOL/Blocks/Block.cpp
  src/libOL/Blocks/KeyframeHeader.cpp
  src/libOL/Blocks/PlayerHeader.cpp
  src/libOL/Blocks/SummonerData.cpp
  src/libOL/Blocks/Inventory.cpp
  src/libOL/Blocks/PlayerStats.cpp
  src/libOL/Blocks/Ability.cpp
)

if(CMAKE_GENERATOR MATCHES "Xcode")
  FILE(GLOB_RECURSE LIBOL_INC "src/libOL/*.h")
  SET(LIBOL_SOURCES ${LIBOL_SOURCES} ${LIBOL_INC})
endif()

add_library(OL ${LIBOL_SOURCES})

### zlib
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
  include_directories(${ZLIB_INCLUDE_DIRS})
  target_link_libraries(OL ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)

### OpenSSL
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIRS})
  target_link_libraries(OL ${OPENSSL_LIBRARIES})
endif(OPENSSL_FOUND)

### Test libOL
set(LIBOL_TEST_SOURCES
  src/libOL_test/main.cpp
)

if(CMAKE_GENERATOR MATCHES "Xcode")
  FILE(GLOB_RECURSE LIBOL_TEST_INC "src/libOL_test/*.h")
  SET(LIBOL_TEST_SOURCES ${LIBOL_TEST_SOURCES} ${LIBOL_TEST_INC})
endif()

add_executable(libOL_test ${LIBOL_TEST_SOURCES})
target_link_libraries(libOL_test OL)

