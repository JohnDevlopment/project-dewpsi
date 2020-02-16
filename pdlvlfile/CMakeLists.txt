if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message (FATAL_ERROR "Prevented a build inside the source tree. Please create a build directory outside the source code.")
endif ()

cmake_minimum_required(VERSION 3.14)
project (pdlvlfileP DESCRIPTION "Library to write/read Project Dewpsi levels from files" LANGUAGES C)

set (PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set (pdlvlfileP_BINARY_DIR ${CMAKE_BINARY_DIR})
set (pdlvlfileP_MAJOR_VERSION 1)
set (pdlvlfileP_MINOR_VERSION 0)
set (pdlvlfileP_PATCH_VERSION 0)
set (pdlvlfileP_VERSION ${pdlvlfileP_MAJOR_VERSION}.${pdlvlfileP_MINOR_VERSION}.${pdlvlfileP_PATCH_VERSION})

# modules included with CMake
include (GNUInstallDirs)

# user-defined modules
set (CMAKE_MODULE_PATH ${PROJECT_ROOT_DIR}/modules)
include (os)
include (config)
include (buildset)
