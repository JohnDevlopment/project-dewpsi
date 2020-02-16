<a id="S1"></a>
# pdlvlfile
A library that writes to and reads from, files that contain level data for the purposes of Project Dewpsi.

<a id="S1_SS1"></a>
## Table of contents

1. [Top](#S1)
2. [Building the project](#S2)
  * [Examples](#S2_SS1)
  * [Options](#S2_SS2)

- - -

[1]: /README.md#S1 "How to build a project"

<a id="S2"></a>
# Building the project
Follow the instructions outlined in [the root folder readme][1]. To customize the build, CMake provides
an option, `-D`, which sets CACHE variables to the values you provide. Use this option to alter the
behavior of CMake when building projects

After CMake generates the buildsystem, as long as there are no errors, you can type `make` on
the commandline to build the project, then `make install` to install the library and to the standard
library path. Headers needed to access the functions and types are installed to the standard header
locations under a directory called "pdlvlfile". If you use `make install/local` instead, the local prefix is used
instead of the systemwide prefix.

<a id="S2_SS1"></a>
## Examples

`$ cmake -DTYPE=shared -DDEBUG=OFF`  
Generates a buildsystem for a shared library in the Release configuration.

`$ cmake -DTYPE=static -DDEBUG=ON -DKEEP=TRUE`  
Generates a buildsystem for a static library in the Debug configuration that
keeps functions that might otherwise not be included in the library.

<a id="S2_SS2"></a>
## Options
These options can be modified with the '-D' option \(see [this readme][1]\).

* TYPE
  * The type of library to build. Can be one of shared, module, or static.
    *The default value is "shared"*.
* FILES
  * This option is not meant to be modified by the user, but it can be. It is a space- or semicolon-separated
    list of the source files that get compiled into the library.
* SUGGEST_ATTR
  * If this option is specified, an option is added to the commandline for compiling source files:
    in GCC, this option is "-Wsuggest-attribute". *The default value is an empty string*.
* DEBUG
  * If set to `ON` or `TRUE`, compiles the source code to have debugging symbols, so that debuggers
    such as GDB will work properly. *The default value is `OFF` or `FALSE`*.
* KEEP
  * A boolean option: specify "TRUE" or "ON" to turn on this option. If this option is turned on,
    then functions **pdlvl\_swap16** and **pdlvl\_swap32** are enabled.  
    By default, these functions are not included in the library on Linux systems, as Linux
    systems already have functions for swapping bytes.&mdash;See **endian**\(3).
