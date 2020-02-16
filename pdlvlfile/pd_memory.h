#ifndef PD_MEMORY_H
#define PD_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <pd_stdinc.h>
#include <pd_stddef.h>

/*
pdlvl_malloc - allocate a block of memory
    @param size     size of the block in bytes
    @return         a pointer to the allocated memory or NULL if it runs out
pdlvl_calloc - allocate an array of memory
    @param count    how many elements to allocate
    @param size     size of a single element in bytes
    @return         a pointer to the allocated memory or NULL if it runs out
*/
extern void* pdlvl_malloc(size_t size);
extern void* pdlvl_calloc(size_t count, size_t size);

/*
pdlvl_newempty - create an empty level structure
pdlvl_new - initialize a level structure with sub-divisions
    @param numdivs  how many sub-divisions to allot the level
    @param pdims    pointer to an array of pairs, width and height
                    for each sub-division; thus, array size should be
                    *numdivs* multiplied by 2
pdlvl_free - free level
*/
extern Level* pdlvl_newempty(void);
extern Level* pdlvl_new(size_t numdivs, const int* pdims);
extern void pdlvl_free(Level* ptr);
extern void pdlvl_freedivs(SubArea* divs, size_t numdivs); /* TODO add to man page */

/*
pdlvl_open - open a binary file for read or write or both
    @param file     file to load
    @param mode     w, w+, r, r+, a, a+ (fopen mode parameter)
    @return         a pointer to a FILE object that identifies a file stream or NULL on failure
pdlvl_close - close the file
    @param handle   a pointer to a FILE object that identifies a stream
*/
extern FILE* pdlvl_open(const char* file, const char* mode);
extern void pdlvl_close(FILE* handle);

/*
pdlvl_numdivs - return the number of divisions in the level
    @return number of divisions in level or -1 if the argument is NULL
*/
extern int pdlvl_numdivs(const Level* ptr);

extern LevelHeader* pdlvl_header(Level* ptr) ATTR_CONST;
extern const LevelHeader* pdlvl_cheader(const Level* ptr) ATTR_CONST;

extern SubArea* pdlvl_subdiv(Level* lvl, size_t idx, int* pw, int* ph, Tile** pptiles);
extern const SubArea* pdlvl_csubdiv(const Level* lvl, size_t idx, int* pw, int* ph, const Tile** pptiles);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_MEMORY_H */
