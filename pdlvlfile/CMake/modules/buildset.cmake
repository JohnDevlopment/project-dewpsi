# Build rules for pdlvlfile
#--------------------------

# description of binary target pdlvlfile
if (${TYPE} MATCHES shared)
	add_library(pdlvlfile SHARED ${SOURCE_FILES})
elseif (${TYPE} MATCHES module)
	add_library(pdlvlfile MODULE ${SOURCE_FILES})
elseif (${TYPE} MATCHES static)
	add_library(pdlvlfile STATIC ${SOURCE_FILES})
else ()
	message (FATAL_ERROR "add_Library type ${TYPE} not valid; can be shared, static, or module")
endif ()

# target properties
set_target_properties (
	pdlvlfile
	  PROPERTIES
	    PUBLIC_HEADER "${PUBLIC_HEADERS}"
	    SOVERSION ${pdlvlfileP_VERSION}
	    VERSION ${pdlvlfileP_VERSION}
)

# global options
set_os_compiler_defines (pdlvlfile)
target_include_directories (
	  pdlvlfile
	    PRIVATE
	      ${PROJECT_ROOT_DIR}
)

# precompile headers and use them for the source files
target_precompile_headers (pdlvlfile PRIVATE ${PROJECT_ROOT_DIR}/pd_stdinc.h)

### Installation rules

# install primary target and headers
install (
	TARGETS
	  pdlvlfile
	  LIBRARY
	    DESTINATION ${CMAKE_INSTALL_LIBDIR}
	    PUBLIC_HEADER
	      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pdlvlfile
)

### Post-build rules and targets

# uninstall rule
configure_file (${PROJECT_ROOT_DIR}/CMake/cmake_uninstall.cmake ${pdlvlfileP_BINARY_DIR}/cmake_uninstall.cmake @ONLY)
add_custom_target (uninstall COMMAND ${CMAKE_COMMAND} -P ${pdlvlfileP_BINARY_DIR}/cmake_uninstall.cmake)
