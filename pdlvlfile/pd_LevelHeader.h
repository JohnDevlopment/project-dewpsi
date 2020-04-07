#ifndef PD_LEVELHEADER_H
#define PD_LEVELHEADER_H

/**
*   @file   pd_LevelHeader.h
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <pd_stdinc.h>

#ifndef BGBOTTOM_LENGTH
 #define BGBOTTOM_LENGTH    31
 #define BGTOP_LENGTH       31
 #define TILESET_LENGTH     11
 #define MUSIC_LENGTH       17
#endif

/*! A struct that defines a level header */
struct LevelHeader {
    char bgBottom[BGBOTTOM_LENGTH]; /// Name of a file containing image data. Used for loading the bottom-layer background image.
    char bgTop[BGTOP_LENGTH];       /// Name of a file containing image data. Used for loading the top-layer background image.
    char tileset[TILESET_LENGTH];   /// Name of a file containing image data. Used for loading the tileset.
    char music[MUSIC_LENGTH];       /// Name of a file containing audio data. Used for loading the background music.
    uint16_t numdivs;               /// Number of sub-areas in the level. Must be >= 1.
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_LEVELHEADER_H */
