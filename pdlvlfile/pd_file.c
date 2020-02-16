#include "pd_file.h"
#include "pd_endian.h"

/* ===== write functions ===== */

size_t pdlvl_writebytes(FILE* stream, const void* bytes, size_t count)
{
    size_t written;

    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
        return false;
    }
    if (! bytes)
    {
        bad_param("bytes");
        return false;
    }

    written = fwrite(bytes, 1, count, stream);
    if (ferror(stream))
        write_error();

    return written;
}

int pdlvl_write8(FILE* stream, uint8_t x)
{
    int written;

    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
        return false;
    }

    /* write a character to stream */
    written = fputc((int) x, stream);
    if (ferror(stream))
    {
        write_error();
    }

    return (written != EOF) ? true : false;
}

int pdlvl_writele16(FILE* stream, uint16_t x)
{
    uint16_t swapped = pdlvl_ntole16(x);
    char written;

    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
        return false;
    }

    written = (char) fwrite(&swapped, 2, 1, stream);
    if (ferror(stream))
        write_error();

    return (int) written;
}

int pdlvl_writele32(FILE* stream, uint32_t x)
{
    uint32_t swapped = pdlvl_ntole32(x);
    char written;

    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
        return false;
    }

    written = (char) fwrite(&swapped, 4, 1, stream);
    if (ferror(stream))
        write_error();

    return (int) written;
}

int pdlvl_writebe32(FILE* stream, uint32_t x)
{
    uint32_t swapped = pdlvl_ntobe32(x);
    char written;

    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
        return false;
    }

    written = (char) fwrite(&swapped, 4, 1, stream);
    if (ferror(stream))
        write_error();

    return (int) written;
}

/* ===== read functions ===== */

size_t pdlvl_readbytes(FILE* stream, void* ptr, size_t count, int* code)
{
    size_t written;
    char result = 0;
    
    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
        return 0;
    }
    if (! ptr)
    {
        bad_param("ptr");
        return 0;
    }
    if (! count)
    {
        bad_param("count");
        return 0;
    }
    
    /* reads bytes to pointer */
    written = fread(ptr, 1, count, stream);
    if (ferror(stream))
    {
        write_error();
        result = false;
    }
    else if (feof(stream))
    {
        pdlvl_seterror("end of file reached");
        result = false;
    }
    else
    {
        result = true;
    }
    
    if (code)
        *code = (int) result;
    
    return written;
}

uint8_t pdlvl_read8(FILE* stream, int* code)
{
    int result = 0;
    char ccode = true;
    
    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
    }
    else {
        /* get character */
        clearerr(stream);
        result = fgetc(stream);
        /* error */
        if (feof(stream))
        {
            pdlvl_seterror("end of file reached");
            ccode = false;
        }
        else if (ferror(stream))
        {
            write_error();
            ccode = false;
        }
    }
    
    /* return code */
    if (code)
        *code = (int) ccode;
    
    return (result != EOF) ? result : 0;
}

uint16_t pdlvl_readle16(FILE* stream, int* code)
{
    uint16_t val = 0;
    char result = 0;
    
    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
        goto skip;
    }
    
    /* read value */
    result = (char) fread(&val, 2, 1, stream);
    if (ferror(stream))
    {
        write_error();
    }
    else if (feof(stream))
    {
        pdlvl_seterror("end of file reached");
    }
    
skip:
    if (code) *code = (int) result;
    
    return (val) ? pdlvl_le16ton(val) : 0;
}

uint32_t pdlvl_readle32(FILE* stream, int* code)
{
    uint32_t val = 0;
    char result = 0;

    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
    }
    else
    {
        /* read value */
        result = (char) fread(&val, 4, 1, stream);
        if (ferror(stream))
        {
            write_error();
        }
        else if (feof(stream))
        {
            pdlvl_seterror("end of file reached");
        }
    }
    
    if (code)
        *code = (int) result;

    return pdlvl_le32ton(val);
}

uint32_t pdlvl_readbe32(FILE* stream, int* code)
{
    uint32_t val = 0;
    char result = 0;

    /* bad parameters */
    if (! stream)
    {
        bad_param("stream");
        goto skip;
    }
    
    /* read value */
    result = (char) fread(&val, 4, 1, stream);
    if (ferror(stream))
    {
        write_error();
    }
    else if (feof(stream))
    {
        pdlvl_seterror("end of file reached");
    }

skip:
    if (code)
        *code = (int) result;

    return pdlvl_be32ton(val);
}
