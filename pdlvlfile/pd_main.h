/** @file   pd_main.h
*   @author John Russell
*   @date   Feburary 24, 2020 (8:23 PM CST)
*   
*   @brief  Header with functions to read and write level data to file.
*
*   These functions rely on the standard C IO functions, which uses FILE objects
*   and functions declared in stdio.h.
*/
#ifndef PD_MAIN_H
#define PD_MAIN_H

#include <pd_stdinc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Writes a level header to stream.
*   @param  stream  Pointer to a FILE object that identifies a stream
*   @param  lvl     Pointer to a level structure
*   @return         1 on success or 0 on failure. If the function returns 0,
*                   you can call @b pdlvl_geterror() to retrieve the error message.
*
*   @remark         In the case of failure, call @b pdlvl_geterror() to retrieve the error string.
*/
extern int pdlvl_writeheader(FILE* stream, const Level* lvl);

/** Writes an AREA block to file.
*   @param  stream  Pointer to a FILE object that identifies a stream
*   @param  lvl     Pointer to a level structure
*   @param  idx     Sub-division number (>= 0, < number of divs)
*   @return         1 on success or 0 on failure. If the function returns 0,
*                   you can call @b pdlvl_geterror() to retrieve the error message.
*/
extern int pdlvl_writeAREA(FILE* stream, const Level* lvl, size_t idx);

/** Writes a level structure to file.
*
*   This function does not call pdlvl_writeheader(); you must do so yourself.
*   Call this function when you want to comprehensively write every block to file.
*   Procedurally, what this function does is it seeks to the place just after the
*   header, and then it writes every block to file, starting with the AREA blocks.
*
*   @param  stream  Pointer to a FILE object that identifies a stream
*   @param  lvl     Pointer to a level structure
*   @return         Number of bytes written or -1 on failure. Failure conditions include
*                   errors writing to the stream, parameters stream or lvl being @c NULL,
*                   or there being no sub-divisions in the level.
*                   In the case of failure, call @b pdlvl_geterror() to retrieve the error message.
*/
extern int pdlvl_writelevel(FILE* stream, const Level* lvl);

/** Reads a level header from stream.
*   
*   @param[in]  stream  Pointer to a FILE object that identifies a stream
*   @param[out] lvl     Pointer to a level structure whose header is filled with data from the stream
*   @return             1 on success and 0 on failure. In the case of failure, call @b pdlvl_geterror()
*                       to retrieve the error message.
*
*   @remark             Internally, the function frees memory associated with the sub-divisions in the
*                       level after checking the parameters. So assuming you don't get any errors from that,
*                       or you get no errors at all, then it should be assumed that there are no sub-divisions
*                       in the level structure after this call.
*   @todo               Tell the user whether sub-divisions have been freed or not.
*/
extern int pdlvl_readheader(FILE* stream, Level* lvl);

/** Reads an AREA block into a sub-division block.
*
*   @param[in]  stream  Pointer to a FILE object that identifies a stream
*   @param[out] subdiv  Filled with the information from the stream
*   @param[in]  blksize Size of the block to read
*   @return             1 on success and 0 on failure. In case of error, call
*                       @b pdlvl_geterror() to retrieve the error message.
*/
extern int pdlvl_readAREA(FILE* stream, SubArea* subdiv, size_t blksize);

/** Reads data blocks from stream into the level structure.
*
*   @param[in]  stream  Pointer to a FILE object that identifies a stream
*   @param[out] lvl     Filled with the information extracted from stream.
*   @return             Number of bytes read from file. If this value doesn't
*                       match the size of the level structure, then an error
*                       has occurred, in which case @b pdlvl_geterror() should be called.
*   @remark             If the function returns a non-zero value, then that is an indication
*                       that sub-divisions have been allocated inside the level structure.
*                       But that doesn't neccessarily mean that all the sub-divisions are valid,
*                       since this function can return a non-zero value even if it fails to read
*                       enough bytes to fill the entire array.
*   @remark             It is an error for any of the parameters to be @c NULL.
*   @todo               Check size of level structure and match it with the number of bytes read.
*/
extern size_t pdlvl_readlevel(FILE* stream, Level* lvl);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_MAIN_H */
