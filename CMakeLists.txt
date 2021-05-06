set(cmake_version 3.18.3)

cmake_minimum_required(VERSION ${cmake_version})

set(ProjectName "UDPServer")

project(${ProjectName} 
		VERSION 0.1.0
		LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# To organize targets into groups when using IDE like XCode or VisualStudio, etc.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Create executable
add_executable(udpserver "")

# Add dependencies
add_subdirectory(deps)

# Add sources, definitions, link dependencies, etc.
add_subdirectory(sources)

# Create groups in the IDE which mirrors directory structure on the hard disk
get_target_property(udpserver_sources udpserver SOURCES)
source_group(
  TREE   ${CMAKE_CURRENT_SOURCE_DIR}/sources
  FILES  ${udpserver_sources}
)

# Things typically only needed if we are the top level project
if(TEST_UDP_SERVER OR CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  # Setup testing
  add_subdirectory(tests)
endif()
