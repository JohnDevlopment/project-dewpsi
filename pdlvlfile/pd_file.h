/** @file pd_file.h
*   @brief Header file with functions for writing unformatted binary data to file.
*
*   @defgroup   file    File IO Functions
*   Functions that write unformatted binary data to file.
*   This file contains functions to write to file:
*       - Byte arrays
*       - Single bytes
*       - 16 and 32 bit integers
*           - in little endian
*           - in big endian
*/
#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <pdlvlfile.h>

/* If using C++, wrap prototypes in a block that treats them as C functions */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Writes an array of bytes to stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  bytes   An array of @b count bytes long.
*   @param  count   Number of bytes to write to stream.
*   @return         Number of bytes written to stream, @b count if successful.
*/
extern size_t pdlvl_writebytes(FILE* stream, const void* bytes, size_t count);

/** Writes a single byte to stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  x       Byte to write to stream.
*   @return         1 on success or 0 on failure.
*/
extern int pdlvl_write8(FILE* stream, uint8_t x);

/** Writes a little endian integer to stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  x       Integer in native byte order.
*   @return         1 on success or 0 on failure.
*/
extern int pdlvl_writele16(FILE* stream, uint16_t x);

/** Writes a 32 bit little endian integer to stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  x       Integer in native byte order.
*   @return         1 on success or 0 on failure.
*/
extern int pdlvl_writele32(FILE* stream, uint32_t x);

/** Writes a big endian 32 bit integer to stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  x       Integer in native byte order.
*   @return         1 on success or 0 on failure.
*/
extern int pdlvl_writebe32(FILE* stream, uint32_t x);

/** Reads a number of bytes from stream.
    @param[in]  stream   Pointer to a FILE object that identifies a stream.
    @param[out] ptr      Filled with the bytes from stream.
    @param[in]  count    Number of bytes to read from stream.
    @param[out] code     If not @c NULL, is filled with a success code (1 on success, 0 on failure).
    @return              Number of bytes read from stream.
*/
extern size_t pdlvl_readbytes(FILE* stream, void* ptr, size_t count, int* code);

/** Reads a single byte from stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  code    If not @c NULL, is filled with a success code (1 on success, 0 on failure).
*   @return         If successful, the integer from file; otherwise 0.
*/
extern uint8_t pdlvl_read8(FILE* stream, int* code);

/** Reads a little endian 16 bit integer from stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  code    If not @c NULL, is filled with a success code (1 on success, 0 on failure).
*   @return         If successful, the integer from file; otherwise 0.
*/
extern uint16_t pdlvl_readle16(FILE* stream, int* code);

/** Reads a little endian 32 bit integer from stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  code    If not @c NULL, is filled with a success code (1 on success, 0 on failure).
*   @return         If successful, the integer from file; otherwise 0.
*/
extern uint32_t pdlvl_readle32(FILE* stream, int* code);

/** Reads a big endian 32 bit integer from stream.
*
*   @param  stream  Pointer to a FILE object that identifies the stream.
*   @param  code    If not @c NULL, is filled with a success code (1 on success, 0 on failure).
*   @return         If successful, the integer from file; otherwise 0.
*/
extern uint32_t pdlvl_readbe32(FILE* stream, int* code);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FILE_H_INCLUDED */
