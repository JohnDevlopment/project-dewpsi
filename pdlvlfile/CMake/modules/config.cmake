set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD_REQUIRED OFF)

# library type; suggest attribute string; source files
set (TYPE shared CACHE STRING "must be shared, module, or static")
set (SUGGEST_ATTR "" CACHE STRING "if defined, adds -Wsuggest-attribute=arg to commandline")
set (FILES "pd_endian.c;pd_error.c;pd_file.c;pd_main.c;pd_memory.c" CACHE STRING "list of source files")

# mandoc files
set (temp "")
foreach (_file "pdlvl_error.3;pdlvl_new.3;pdlvl_writeheader.3")
	string (APPEND temp "${PROJECT_ROOT_DIR}/docs/${_file}")
endif ()
set (MANDOCS ${temp} CACHE INTERNAL "list of man files to be installed")
unset (temp)

# public headers to be installed
set (PUBLIC_HEADERS "")
foreach (_file ${FILES})
	string (REPLACE ".c" ".h" _file ${_file})
	string (APPEND PUBLIC_HEADERS "${_file};")
endforeach ()
unset (_file)
string (APPEND PUBLIC_HEADERS "pd_LevelHeader.h;pd_pubtypes.h;pd_stdinc.h;pdlvlfile.h;pd_stddef.h;pd_Tile.h;endian/${PLATFORM_DIR}/_pd_endian.h")

# debug configuration; keep swap functions
option (DEBUG "debug configuration" FALSE)
option (KEEP "implement swap functions" FALSE)

message ("${TYPE} library")
message (STATUS "debug configuration ${DEBUG}")
message (STATUS "keep swap functions ${KEEP}")
message (STATUS "SUGGEST_ATTR = ${SUGGEST_ATTR}")
