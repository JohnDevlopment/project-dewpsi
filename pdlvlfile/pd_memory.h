#ifndef PD_MEMORY_H
#define PD_MEMORY_H

/**
*   @file       pd_memory.h
*   Header that contains memory manipulation functions.
*
*   @defgroup   memory      Memory functions
*   Includes functions to allocate and free blocks of memory.
*   Also includes function to interact with the level data
*   structures.
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <pd_stdinc.h>
#include <pd_stddef.h>

/** Allocates a block of memory.
*
*   @param  size    How many bytes to allocate.
*   @return         A pointer to a block allocated memory or @c NULL on failure.
*                   In case of error, obtain the error message with pdlvl_geterror().
*   @warning        It must be freed later with free().
*   @ingroup        memory
*/
extern void* pdlvl_malloc(size_t size);

/** Allocates an array of blocks of memory @a size bytes long.
*
*   @param  count   Number of blocks to allocate.
*   @param  size    Bytes that each block takes.
*   @return         A pointer to the allocated blocks of memory or @c NULL on failure.
*                   In case of error, obtain the error message with pdlvl_geterror().
*   @warning        The pointer returned must be freed later with free().
*   @ingroup        memory
*/
extern void* pdlvl_calloc(size_t count, size_t size);

/** Allocates an empty level structure.
*
*   @return     A pointer to an empty level structure or @c NULL upon failure.
*   @warning    The pointer returned must be freed later with pdlvl_free().
*   @ingroup        memory
*/
extern Level* pdlvl_newempty(void);

/** Allocates a level structure with sub-divisions.
*
*   @param  dims    A string with an even number of space-separated
*                   decimal numbers. Each pair defines the width and
*                   height of a sub-area, counting from ID 0 and onwards.
*   @return         A pointer to a newly created level structure with @a numdivs
*                   sub-areas or @c NULL on failure. Retrieve the error message with
*                   pdlvl_geterror().
*   @warning        The pointer returned by the function must be freed later with
*                   pdlvl_free().
*   @ingroup        memory
*/
extern Level* pdlvl_new(const char* dims);

/** Allocates a level structure with a number of sub-divisions.
*
*   @param  numdivs The number of divisions in the level.
*   @param  pdims   A pointer to an array of integers arranged in pairs.
*                   The first of each pair is the width of a sub-area, and the
*                   second is the height.
*   @return         A pointer to a newly created level structure with @a numdivs
*                   sub-areas or @c NULL on failure. Retrieve the error message with
*                   pdlvl_geterror().
*   @warning        The pointer returned by the function must be freed later with
*                   pdlvl_free().
*   @ingroup        memory
*/
extern Level* pdlvl_new_i(size_t numdivs, const int* pdims);

/** Frees a level structure from memory.
*
*   @param  ptr A pointer to a level structure.
*   @ingroup        memory
*/
extern void pdlvl_free(Level* ptr);

/** Frees a sub-area array from memory.
*
*   @param  divs    An array of sub-areas.
*   @param  numdivs How many sub-divisions are in the array.
*   @ingroup        memory
*/
extern void pdlvl_freedivs(SubArea* divs, size_t numdivs);

/** Opens a binary file for read or write.
*
*   @param  file    A path to the file to load.
*   @param  mode    A string specifying the file operations to enable.
*                   @a Mode can be one of the following:
*                       - w
*                           - Binary write, truncate the file if it exists.
*                       - w+
*                           - Binary write/read, truncate the file if it exists.
*                       - r
*                           - Binary read, the file must already exist.
*                       - r+
*                           - Binary read/write, the file must already exist.
*                       - a
*                           - Binary append, create a new file if needed. All
*                             output operations are tacked onto the end of the file.
*                       - a+
*                           - Binary append/read, create a new file if needed.
*                             Read operations can take place anywhere in the file,
*                             but the output operations are still done at the end
*                             of the file.
*   @return         A pointer to a @c FILE object that identifies a stream, or @c NULL
*                   on failure. Use pdlvl_geterror() to retrieve the error message.
*   @warning        The stream opened by this function should be closed later with pdlvl_close().
*/
extern FILE* pdlvl_open(const char* file, const char* mode);

/** Closes a stream.
*
*   @param  handle  A pointer to a @c FILE object that was previously returned
*                   by pdlvl_open().
*/
extern void pdlvl_close(FILE* handle);

/** Returns the number of sub-divisions in the level.
*
*   @param  ptr A pointer to a level structure.
*/
extern int pdlvl_numdivs(const Level* ptr);

/** Returns a reference to the level header from a level structure.
*
*   @param  ptr A pointer to a level structure.
*   @return     A pointer to the header located inside @a ptr or @c NULL if the parameter is @c NULL.
*/
extern LevelHeader* pdlvl_header(Level* ptr) ATTR_CONST;

/** Returns a constant reference to the level header.
*
*   @param  ptr A valid pointer to a level structure.
*   @return     A read-only reference to a level header, or @c NULL if the parameter is @c NULL.
*/
extern const LevelHeader* pdlvl_cheader(const Level* ptr) ATTR_CONST;

/** Retrieves information about a level sub-area.
*
*   @param[in]  lvl     A pointer to a level structure.
*   @param[in]  idx     Sub-area number (starting from 0).
*   @param[out] pw      A pointer that, if set, is filled with the width of the sub-area.
*   @param[out] ph      A pointer that, if set, is filled with the height of the sub-area.
*   @param[out] pptiles A pointer that, if set, is filled with the address to an array of tiles.
*   @return             A pointer to the requested sub-area or @c NULL if @a lvl is @c NULL,
*                       @a idx is invalid, or the level structure has no sub-areas.
*/
extern SubArea* pdlvl_subdiv(Level* lvl, size_t idx, int* pw, int* ph, Tile** pptiles);

/** Retrieves information about a level sub-area.
*
*   @param[in]  lvl     A pointer to a level structure.
*   @param[in]  idx     Sub-area number (starting from 0).
*   @param[out] pw      A pointer that, if set, is filled with the width of the sub-area.
*   @param[out] ph      A pointer that, if set, is filled with the height of the sub-area.
*   @param[out] pptiles A pointer that, if set, is filled with the address to an array of tiles.
*   @return             A pointer to the requested sub-area or @c NULL if @a lvl is @c NULL,
*                       @a idx is invalid, or the level structure has no sub-areas.
*   @remark             The pointer returned by this function, and the pointer referenced by
*                       @a pptiles, are read only. The memory pointed to by these pointers
*                       cannot be modified.
*/
extern const SubArea* pdlvl_csubdiv(const Level* lvl, size_t idx, int* pw, int* ph, const Tile** pptiles);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_MEMORY_H */
