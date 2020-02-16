#ifndef PD_MAIN_H
#define PD_MAIN_H

#include <pd_stdinc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
pdlvl_writeheader - write level header to file
    @param stream   pointer to a FILE object that identifies a stream
    @param lvl      pointer to level data
    @return         1 (true) on success, 0 (false) on failure
*/
extern int pdlvl_writeheader(FILE* stream, const Level* lvl);

/*
pdlvl_writeAREA - write an AREA block to file
    @param stream   pointer to a FILE object that identifies a stream
    @param lvl      pointer to level data
    @param idx      subdivision number (>= 0, < number of divs)
    @return         1 (true) on success, 0 (false) on failure
*/
extern int pdlvl_writeAREA(FILE* stream, const Level* lvl, size_t idx);

/*
pdlvl_writelevel - write level data, sans the header, to data stream
    @param stream   pointer to a FILE object that identifies a stream
    @param lvl      pointer to level data
    @return         number of bytes successfully written or -1 on error.
                    Use get_error to retrieve the error message.
*/
extern int pdlvl_writelevel(FILE* stream, const Level* lvl);

/*
pdlvl_readheader - read header from stream
    @param stream   pointer to a FILE object that identifies a stream
    @param lvl      pointer to level data, whose header is filled with data from stream
    @return         1 (true) on success, 0 (false) on failure
*/
extern int pdlvl_readheader(FILE* stream, Level* lvl);

/*
pdlvl_readAREA - reads AREA block from stream
    @param stream   pointer to a FILE object that identifies a stream
    @param subdiv   a pointer to the sub-division of size *blksize*
    @param blksize  size of the block in bytes
*/
extern int pdlvl_readAREA(FILE* stream, SubArea* const subdiv, size_t blksize);

/*
pdlvl_readlevel - read data blocks from stream into level structure
    @param stream   pointer to a FILE object that identifies a stream
    @param lvl      pointer to a level structure, for which sub-divisions are allocated
    @return         1 (true) on success, 0 (false) on failure
                    if the return value is 1, memory is allocated internally
*/
extern int pdlvl_readlevel(FILE* stream, Level* lvl);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_MAIN_H */
