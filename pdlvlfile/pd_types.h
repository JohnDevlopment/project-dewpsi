#ifndef PD_TYPES_H
#define PD_TYPES_H

#include <pd_stdinc.h>
#include <pd_stddef.h>
#include <pd_pubtypes.h>

/*! A struct that represents a sub-area.
*
*   Written to file in what's known as an AREA block.
*   It's marked by a 32 bit tag that shows as "AREA" when
*   the file is read in text mode, followed by the size of
*   the block (represented as a 32 bit little endian integer).
*/
struct SubArea {
    uint32_t id;    /*!< The ID of the block */
    uint8_t width;  /*!< The width of the sub-area in tiles */
    uint8_t height; /*!< The height of the sub-area in tiles */
    Tile* tiles;    /*!< The tile array (count: width x height) */
};

/*! Struct representing the entire level in file.
*   The header contains a small list of strings denoting the names
*   of files that are to be used by the level. It also contains the
*   number of divisions in the level, which member divs depends on.
*/
struct Level {
    LevelHeader header; /*!< The header of the level */
    SubArea* divs;      /*!< Array of sub-divisions (count: header->numdivs) */
};

#define SIZEOF_SubArea(ptr) \
	((size_t) ((sizeof(Tile) * ((ptr)->width * (ptr)->height)) + 6U)) /* structure plus tile array */

#endif /* PD_TYPES_H */
