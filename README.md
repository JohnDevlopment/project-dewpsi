<a id="project-dewpsi"></a>
# project-dewpsi
Libraries and programs associated with Project Dewpsi

So far in this repository, there is only the `pdlvlfile` library, which is
located in the "pdlvlfile" folder.

## Table of contents

1. [How to build a project](#How to build a project)
  * [Instructions](#How to build a project_Instructions)
  * [Options](#How to build a project_Options)
  * [Notes](#How to build a project_Notes)

- - -

<a id="S1"></a>
<a id="How to build a project"></a>
# How to build a project
The programs and libraries contained by this repository are built using
CMake. Here is how to use CMake to build the projects herein.

<a id="How to build a project_Instructions"></a>
## Instructions
Go into the "build" directory. Use the `cmake` command to generate the makefiles.

First form: `cmake -S path -B path [options...]`

Second form: `cmake path [options...]`

The first form specifies both a source path and a binary path, whereas the second form
specifies the source path and the binary path is presumed to be the current working
directory.

The _source path_ or the _source directory_ is where the `CMakeLists.txt` file is located.
It is also the root directory for the file structure where the source code is found.
So in those terms, the file "/main.c" refers to the main.c file that is in the same directory
as `CMakeLists.txt`.

The _binary path_ or the _binary directory_ refers to the location where CMake generates the
makefiles and where the target itself is built. It is important to note: _the binary directory_
_and the source directory cannot be the same!_ My `CMakeLists.txt` files were written specifically
to disallow that.

Both the source path and the binary path can be relative.

<a id="How to build a project_Options"></a>
## Options

### Main options

* -S
  * Path to the source directory (where `CMakeLists.txt` is located). Sets the *CMAKE\_SOURCE\_DIR* variable
    within the cmake file.
* -B
  * Path to the binary directory, which defines the top level of the build tree.
    By convention, I like to make the binary path point to a directory called "build"
    underneath the source directory. But that is not strictly necessary.
* -D_var=value_
  * Define a cache variable named _var_ with the value _value_. For each project, a list
    of variables that are used will be listed.

<a id="How to build a project_Notes"></a>
## Notes
It is important to know some things about how I sort my files here. For starters, all my CMake modules
are located in "/CMake/modules" (relative to the source directory).

- - -

[Return to top](#project-dewpsi)
