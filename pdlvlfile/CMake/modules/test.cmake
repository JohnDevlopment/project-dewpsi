# rules to make a test executable that uses this library

# source files
file (GLOB SOURCE_FILES "${PROJECT_ROOT_DIR}/test/*.c")
add_executable (libtest EXCLUDE_FROM_ALL ${SOURCE_FILES})

# import a static library
#add_library (memory STATIC IMPORTED)
#set_target_properties (memory PROPERTIES IMPORTED_LOCATION "${PROJECT_ROOT_DIR}/test/libmemory.a")

# dependencies for the target
add_dependencies (libtest pdlvlfile)
target_include_directories (libtest PRIVATE ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pdlvlfile)
target_precompile_headers (libtest PRIVATE "${PROJECT_ROOT_DIR}/test/pd_stdinc.h")

# link libraries
target_link_libraries (libtest pdlvlfile)
