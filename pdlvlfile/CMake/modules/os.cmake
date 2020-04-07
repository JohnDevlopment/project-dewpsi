# 32 or 64 bit system
set (SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})
if (SIZEOF_VOID_P EQUAL 8)
	set (ARCH_64 TRUE)
	set (PROCESSOR_ARCH "x64")
else ()
	set (ARCH_64 FALSE)
	set (PROCESSOR_ARCH "x86")
endif ()

# platform OS
if (WIN32)
	if (NOT WINDOWS)
		set (WINDOWS TRUE)
		set (PLATFORM_DIR "windows")
	endif()
# $UNIX can include $APPLE and $CYGWIN, so make sure it is Linux
elseif (UNIX AND NOT APPLE)
	if (${CMAKE_SYSTEM_NAME} MATCHES ".*Linux")
		set (LINUX TRUE)
		set (PLATFORM_DIR "linux")
	endif ()
else ()
	message (FATAL_ERROR "This operating system, ${CMAKE_SYSTEM_NAME}, is not supported.")
endif ()

# compiler
if (WINDOWS)
	# Microsoft Virtual C++ compiler
	if (MSVC)
		# MSVC_VERSION == 1900, MSVC_VERSION from 1910 to 1919, or MSVC_VERSION from 1920-1929
		if (${MSVC_VERSION} EQUAL 1900 OR ${MSVC_VERSION} GREATER 1900)
			if (${MSVC_VERSION} EQUAL 1900)
				message (STATUS "Using Microsoft Virtual C++ compiler version 14.0")
			elseif (${MSVC_VERSION} LESS 1920)
				message (STATUS "Using Microsoft Virtual C++ compiler version 15.0")
			else ()
				message (STATUS "Using Microsoft Virtual C++ compiler version 16.0")
			endif ()
		else ()
			message (FATAL_ERROR "Invalid version of Microsoft Virtual C++ compiler, minimum version 14.0 required")
		endif ()
	# GNU C/C++ compiler
	elseif (CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
		message (STATUS "Using GNU C/C++ compiler")
	endif ()
endif ()

# set macro definitions for the platform
function (set_os_compiler_defines target)
	if (WINDOWS)
		target_compile_definitions (
		${target}
			PUBLIC WIN32
#			PUBLIC _WIN32
#			PUBLIC _WINDOWS
#			PUBLIC UNICODE
#			PUBLIC _CRT_SECURE_NO_WARNINGS
#			PUBLIC _SCL_SECURE_NO_WARNINGS
		)
		if (${ARCH_64})
			message (STATUS "Compiling under Microsoft Windows 64 bit")
		else ()
			message (STATUS "Compiling under Microsoft Windows 32 bit")
		endif ()
	elseif (LINUX)
		target_compile_definitions (${target} PUBLIC LINUX)
		target_compile_definitions (${target} PUBLIC _GNU_SOURCE)
		if (${ARCH_64})
			message (STATUS "Compiling under Linux 64 bit")
		else ()
			message (STATUS "Compiling under Linux 32 bit")
		endif ()
	endif ()
endfunction ()
