#ifndef PD_TYPES_H
#define PD_TYPES_H

#include <pd_stdinc.h>
#include <pd_stddef.h>
#include <pd_pubtypes.h>

struct SubArea {
    uint32_t id;
    uint8_t width;
    uint8_t height;
    Tile* tiles;
};

struct Level {
    LevelHeader header;
    SubArea* divs;
};

#define SIZEOF_SubArea(ptr) \
	((size_t) ((sizeof(Tile) * ((ptr)->width * (ptr)->height)) + 6U)) /* structure plus tile array */

#endif /* PD_TYPES_H */
