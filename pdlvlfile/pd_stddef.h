/*! \file   pd_stddef.h
*   \brief  Header that includes several macros and struct declarations.
*
*   Macros defined herein are for implementing function attributes in compilers
*   that support them.
*
*   Struct declarations make the types LevelHeader, SubArea,
*   Level, and Tile visible to the rest of the library and
*   to external programs.
*/
#ifndef PD_STDDEF_H_INCLUDED
#define PD_STDDEF_H_INCLUDED

#if _cplusplus
    #define __PD_BEGIN_DECLS    extern "C" {
    #define __PD_END_DECLS      }
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*! Makes functions "pure". */
#ifndef ATTR_PURE
    #if defined(__GNUC__)
        #define ATTR_PURE __attribute__ ((pure))
    #else
        #define ATTR_PURE
    #endif
#endif

/*! Makes functions "constant".
*   A constant function cannot refer to variables outside its scope
*   (AKA, global variables or those passed by pointer/reference).
*/
#ifndef ATTR_CONST
    #if defined(__GNUC__)
        #define ATTR_CONST __attribute__ ((const))
    #else
        #define ATTR_CONST
    #endif
#endif

#ifndef LevelHeader_Defined
    #define LevelHeader_Defined 1
struct LevelHeader;
typedef struct LevelHeader LevelHeader;
#endif /* LevelHeader_Defined */

#ifndef SubArea_Defined
    #define SubArea_Defined 1
struct SubArea;
typedef struct SubArea SubArea;
#endif /* SubArea_Defined */

#ifndef Level_Defined
    #define Level_Defined 1
struct Level;
typedef struct Level Level;
#endif /* Level_Defined */

#ifndef Tile_Defined
    #define Tile_Defined 1
struct Tile;
typedef struct Tile Tile;
#endif /* Tile_Defined */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_STDDEF_H_INCLUDED */
