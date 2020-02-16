#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <pdlvlfile.h>

/* If using C++, wrap prototypes in a block that treats them as C functions */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
pdlvl_writebytes - writes a number of bytes to stream
    @param stream   pointer to FILE object that identifies the stream
    @param bytes    pointer to the data to write
    @param count    how many bytes to write to stream
    @return         the number of bytes written to stream, *count* if successful
*/
extern size_t pdlvl_writebytes(FILE* stream, const void* bytes, size_t count);

/*
pdlvl_write8 - write a single character to stream
    @param stream   pointer to FILE object that identifies the stream
    @param x        character to write to stream
    @return         1 (true) on success, 0 (false) on failure
*/
extern int pdlvl_write8(FILE* stream, uint8_t x);

/*
pdlvl_writele16 - writes a 16-bit integer to stream in little-endian format
    @param stream   pointer to FILE object that identifies the stream
    @param x        written to stream
    @return         1 (true) on success, 0 (false) on failure
*/
extern int pdlvl_writele16(FILE* stream, uint16_t x);

/*
pdlvl_writele32 - writes a 32-bit integer to stream in little-endian format
    @param stream   pointer to FILE object that identifies the stream
    @param x        written to stream
    @return         1 (true) on success, 0 (false) on failure
*/
extern int pdlvl_writele32(FILE* stream, uint32_t x);

/*
pdlvl_writebe32 - writes a 32-bit integer to stream in big-endian format
    @param stream   pointer to FILE object that identifies the stream
    @param x        written to stream
    @return         1 (true) on success, 0 (false) on failure
*/
extern int pdlvl_writebe32(FILE* stream, uint32_t x);

/*
pdlvl_read8 - read a byte from stream
    @param stream   a pointer to a FILE object that identifies a stream
    @param code     if not null, filled with 1 (true) on success or 0 (false) on failure
    @return         a byte read from stream
*/
extern uint8_t pdlvl_read8(FILE* stream, int* code);

/*
pdlvl_readbytes - reads a number of bytes from stream
    @param stream   a pointer to a FILE object that identifies a stream
    @param ptr      filled with the bytes from stream
    @param count    number of bytes to read from stream
    @param code     if not null, filled with 1 (true) on success or 0 (false) on failure
    @return         number of bytes read from stream
*/
extern size_t pdlvl_readbytes(FILE* stream, void* ptr, size_t count, int* code);

/*
pdlvl_readle16 - reads a little-endian 16-bit integer from stream
    @param stream   a pointer to a FILE object that identifies a stream
    @param code     if not null, filled with 1 (true) on success or 0 (false) on failure
    @return         value read from stream converted to native byte order
*/
extern uint16_t pdlvl_readle16(FILE* stream, int* code);

/*
pdlvl_readle32 - reads a little-endian 32-bit integer from stream
    @param stream   pointer to FILE object that identifies the stream
    @param code     if not null, filled with 1 (true) for success or 0 (false) for failure
    @return         value read from stream converted to native byte order
*/
extern uint32_t pdlvl_readle32(FILE* stream, int* code);

/*
pdlvl_readbe32 - reads a big-endian 32-bit integer from stream
    @param stream   pointer to FILE object that identifies the stream
    @param code     if not null, filled with 1 (true) for success or 0 (false) for failure
    @return         value read from stream converted to native byte order
*/
extern uint32_t pdlvl_readbe32(FILE* stream, int* code);

/* End block of C function prototypes */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FILE_H_INCLUDED */
