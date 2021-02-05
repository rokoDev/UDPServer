set(cmake_version 3.18.3)

cmake_minimum_required(VERSION ${cmake_version})

set(ProjectName "UDPServer")

project(${ProjectName} 
		VERSION 0.1.0
		LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/VersionHelper")
include(VersionInfoUtils)
set(ServerNS "server")
m_generate_version_info(PROJECT_NAME ${ProjectName}
	                    CPP_NAMESPACE ${ServerNS}
	                    BUILD_TYPES Debug Release)

message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_FRONTEND_VARIANT: ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}")

list(APPEND UNIX_BUILD_TYPES_CLANG_FLAGS
	"-std=c++17"
	"-Werror"
	"-pedantic-errors"
	"-Wall"
	"-Wextra"
	"-Wconversion"
	"-Wsign-conversion"
	"-Wshadow"
	"-Wunreachable-code"
	"-Wuninitialized"
	"-Wold-style-cast"
	"-Wfloat-equal"
	)

list(APPEND WIN_BUILD_TYPES_CLANG_FLAGS
	"/std:c++17"
	"/WX"
	"/permissive-"
	"/W4"
	)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /WX /permissive- /W4")
  elseif(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL AppleClang)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow")
endif()

set(MAIN_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

set(INCLUDE_DIRS
	${MAIN_INCLUDE_DIR}
	${CMAKE_CURRENT_LIST_DIR}/fmt/include
	)
set(HEADERS 
	${MAIN_INCLUDE_DIR}/InstanceCounter.h
	)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories("${INCLUDE_DIRS}")

if(NOT TARGET fmt)
  add_subdirectory(fmt)
endif()

add_subdirectory(ndt)

# Setup testing
enable_testing()
add_subdirectory(googletest)
add_subdirectory(tests)

# Create application
set(ExecutableName "udpserver")
add_executable(${ExecutableName} ${SOURCE_DIR}/main.cpp ${HEADERS})
target_link_libraries(${ExecutableName} PUBLIC "${ServerNS}_versionInfo" fmt ndt)
target_compile_definitions(${ExecutableName} PUBLIC $<UPPER_CASE:$<CONFIG>>)
target_compile_options(${ExecutableName} PRIVATE ${ALL_CXX_FLAGS})
