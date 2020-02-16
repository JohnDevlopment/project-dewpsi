# description of binary target pdlvlfile
if (${TYPE} MATCHES shared)
	add_library(pdlvlfile SHARED ${FILES})
elseif (${TYPE} MATCHES module)
	add_library(pdlvlfile MODULE ${FILES})
elseif (${TYPE} MATCHES static)
	add_library(pdlvlfile STATIC ${FILES})
else ()
	message (FATAL_ERROR "add_Library type ${TYPE} not valid; can be shared, static, or module")
endif ()

# target properties
set_target_properties (
	pdlvlfile
	  PROPERTIES
	    FRAMEWORK TRUE
	    FRAMEWORK_VERSION C
	    PUBLIC_HEADER "${PUBLIC_HEADERS}"
	    SOVERSION ${pdlvlfileP_VERSION}
	    VERSION ${pdlvlfileP_VERSION}
)

# configuration options
if (${DEBUG})
# debug build
	target_compile_options (
		pdlvlfile
		  PRIVATE
		    "SHELL:-Og"
		    "SHELL:-g"
	)
else ()
# release build
	target_compile_options (
		pdlvlfile
		  PRIVATE
		    "SHELL:-O2"
		    $<$<BOOL:${SUGGEST_ATTR}>:"SHELL:-Wsuggest-attribute=${SUGGEST_ATTR}">
	)
	target_compile_definitions (
		pdlvlfile
		  PRIVATE
		    $<$<BOOL:${KEEP}>:KEEP_SWAP_FUNCTIONS=1>
	)
endif ()

# all builds
target_compile_options (
	pdlvlfile
	  PRIVATE
	    "SHELL:-Wbool-compare"
	    "SHELL:-Wfloat-equal"
	    "SHELL:-Wattributes"
	    "SHELL:-Wunused"
)
target_compile_definitions (
	pdlvlfile
	  PRIVATE
	    $<$<BOOL:${KEEP}>:KEEP_SWAP_FUNCTIONS=1>
	    $<UPPER_CASE:${TYPE}>
	    $<$<NOT:$<BOOL:${DEBUG}>>:NDEBUG>
)

# global options
set_os_compiler_defines (pdlvlfile)
target_include_directories (
	  pdlvlfile
	    PRIVATE
	      ${PROJECT_ROOT_DIR}
	)

#  installation
install (
	TARGETS
	  pdlvlfile
	  LIBRARY
	    DESTINATION ${CMAKE_INSTALL_LIBDIR}
	    PUBLIC_HEADER
	      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pdlvlfile
)
