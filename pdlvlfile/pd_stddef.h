#ifndef PD_STDDEF_H_INCLUDED
#define PD_STDDEF_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef ATTR_PURE
    #if defined(__GNUC__)
        #define ATTR_PURE __attribute__ ((pure))
    #else
        #define ATTR_PURE
    #endif
#endif

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
