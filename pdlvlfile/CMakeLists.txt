if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message (FATAL_ERROR "Prevented an in-source build. Build tree must be outside the source tree.")
endif ()

cmake_minimum_required(VERSION 3.16)
project (pdlvlfileP DESCRIPTION "Library to write/read Project Dewpsi levels from files" LANGUAGES C)

set (PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set (pdlvlfileP_BINARY_DIR ${CMAKE_BINARY_DIR})
set (pdlvlfileP_MAJOR_VERSION 1)
set (pdlvlfileP_MINOR_VERSION 0)
set (pdlvlfileP_PATCH_VERSION 5)
set (pdlvlfileP_VERSION ${pdlvlfileP_MAJOR_VERSION}.${pdlvlfileP_MINOR_VERSION}.${pdlvlfileP_PATCH_VERSION})

set (PD_STDC_EXTRA_FUNCTIONS fprintf abort)

# modules included with CMake
include (GNUInstallDirs)
include (CMakePrintHelpers)

# user-defined modules
set (CMAKE_MODULE_PATH ${PROJECT_ROOT_DIR}/CMake/modules)
include (macros)
include (os)
include (config)
set (PD_MAKE_CONFIG TRUE)
set (PD_CONFIG_DIR "${PROJECT_ROOT_DIR}")
set (PD_STDC_FUNCTIONS fprintf ferror feof vsprintf malloc calloc free strlen strchr strtok strlen strcpy strcat)
set (PD_STDC_INCLUDES stdio.h stdlib.h string.h)
set (PD_STDC_SYMBOLS "endian.h,htole16" "endian.h,htole32" "endian.h,htobe32"
	 "endian.h,le16toh" "endian.h,le32toh" "endian.h,be32toh" "ctype.h,ispunct"
	 "ctype.h,isdigit" "stdlib.h,atoi" "alloca.h,alloca")
include (checks)
include (buildset)
include (test)

# mark advanced cache variables

# output messages
message (STATUS "Target is a ${TYPE} library under the ${CMAKE_BUILD_TYPE} configuration")
