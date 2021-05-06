list(APPEND UNIX_BUILD_TYPES_CLANG_FLAGS
  "-std=c++17"
  "-Werror"
  "-pedantic-errors"
  "-Wall"
  "-Wextra"
  "-Wconversion"
  "-Wsign-conversion"
  "-Wshadow-all"
  "-Wunreachable-code"
  "-Wuninitialized"
  "-Wold-style-cast"
  "-Wfloat-equal"
  "-Wcast-align"
  "-Winvalid-constexpr"
  )

list(APPEND WIN_BUILD_TYPES_CLANG_FLAGS
  "/std:c++17"
  "/WX"
  "/permissive-"
  "/W4"
  )

# Choose c++ compiler flags based on the compiler available or exit with error if no known compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
    list(APPEND ALL_CXX_FLAGS "${WIN_BUILD_TYPES_CLANG_FLAGS}")
  elseif("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "GNU")
    list(APPEND ALL_CXX_FLAGS "${UNIX_BUILD_TYPES_CLANG_FLAGS}")
  else()
    message(FATAL_ERROR "CMAKE_CXX_COMPILER_FRONTEND_VARIANT: ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}(Unrecognized)")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL AppleClang)
  list(APPEND ALL_CXX_FLAGS "${UNIX_BUILD_TYPES_CLANG_FLAGS}")# "${CMAKE_CXX_FLAGS}"
else()
  message(FATAL_ERROR "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}(Unrecognized)")
endif()

message(STATUS "ALL_CXX_FLAGS: ${ALL_CXX_FLAGS}")

target_sources(udpserver
  PUBLIC
    include/InstanceCounter.h

	PRIVATE
    src/main.cpp
  )

set(MAIN_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_definitions(udpserver PRIVATE $<UPPER_CASE:$<CONFIG>>)
target_compile_options(udpserver PRIVATE ${ALL_CXX_FLAGS})
target_link_libraries(udpserver PUBLIC ndt fmt)
target_include_directories(udpserver PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)