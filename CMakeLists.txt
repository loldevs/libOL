### Configuration
cmake_minimum_required (VERSION 2.6)

project (LibOL)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  endif()
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} does not seem to support C++11.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")

include_directories ("${PROJECT_SOURCE_DIR}/include")

### LibOL
add_library(LibOL
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
    target_link_libraries(LibOL ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)
