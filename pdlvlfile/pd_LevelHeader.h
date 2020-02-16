#ifndef PD_LEVELHEADER_H
#define PD_LEVELHEADER_H

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

struct LevelHeader {
    char bgBottom[BGBOTTOM_LENGTH];
    char bgTop[BGTOP_LENGTH];
    char tileset[TILESET_LENGTH];
    char music[MUSIC_LENGTH];
    uint16_t numdivs;
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_LEVELHEADER_H */
