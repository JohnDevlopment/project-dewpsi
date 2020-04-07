# cache help strings
set (CONFIG_DOCSTRING "Build configuration, options are: None Debug Release RelWithDebInfo")
set (CMAKE_BUILD_TYPE_DOCSTRING "Choose the type of build, options are: None Debug Release RelWithDebInfo")

# C standard
set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD_REQUIRED OFF)

### Build configuration section

# build configuration type
set (CONFIG Release CACHE STRING "${CONFIG_DOCSTRING}")
if (NOT CMAKE_BUILD_TYPE OR NOT ${CMAKE_BUILD_TYPE} MATCHES "${CONFIG}")
	set (CMAKE_BUILD_TYPE ${CONFIG} CACHE STRING "${CMAKE_BUILD_TYPE_DOCSTRING}" FORCE)
endif ()
# if Debug: CMAKE_C_FLAGS_DEBUG, CMAKE_C_EXTRA_FLAGS_DEBUG
# if Release: CMAKE_C_FLAGS_RELEASE, CMAKE_C_EXTRA_FLAGS_RELEASE

### Target-related options

# library type
set (TYPE shared CACHE STRING "Type of library to build, can be: shared module static")

# source files
set (temp pd_endian.c pd_error.c pd_file.c pd_main.c pd_memory.c)
list_prefix (SOURCE_FILES "${PROJECT_ROOT_DIR}" "${temp}")

# header files
set (temp pd_endian.h pd_error.h pd_file.h
    pd_internal.h pd_LevelHeader.h pdlvlfile.h pd_main.h
    pd_memory.h pd_pubtypes.h pd_stddef.h pd_stdinc.h pd_Tile.h pd_types.h)
list_prefix (PUBLIC_HEADERS "${PROJECT_ROOT_DIR}" "${temp}")
list (APPEND PUBLIC_HEADERS "${PROJECT_ROOT_DIR}/endian/${PLATFORM_DIR}/_pd_endian.h")

# free variables
unset_list (CONFIG_DOCSTRING CMAKE_BUILD_TYPE_DOCSTRING temp)
