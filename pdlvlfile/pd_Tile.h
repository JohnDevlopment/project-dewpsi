#ifndef PD_TILE_H
#define PD_TILE_H

#include <pd_stdinc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*! Struct representing a tile. */
struct Tile {
    uint8_t gfx;    /*!< Graphics index. */
    uint8_t code;   /*!< Code index. */
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_TILE_H */
