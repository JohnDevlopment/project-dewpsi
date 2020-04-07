#include "pdlvlfile.h"
#include "pd_types.h"
#include "pd_internal.h"
#include "pd_stdinc.h"
#include "pd_memory.h"

int pdlvl_writeheader(FILE* stream, const Level* lvl)
{
    int written;
    const LevelHeader* blk;
    
    blk = pdlvl_cheader(lvl);
    
    /* write PDLV tag */
    rewind(stream);
    written = pdlvl_writebe32(stream, PDLV);
    if (written)
    {
        /* write strings in header */
        clearerr(stream);
        written = pdlvl_writebytes(stream, blk, COUNT_LENGTH);
        if (written)
        {
            /* write number of divisions */
            clearerr(stream);
            written = pdlvl_writele16(stream, blk->numdivs);
        }
    }
    
    return written;
}

int pdlvl_writeAREA(FILE* stream, const Level* lvl, size_t idx)
{
    int w, h, numtiles;
    const SubArea* div = NULL;
    const Tile* ptiles = NULL;
    
    /* null parameters */
    if (! stream)
    {
        pdlvl_badparam("stream");
        return false;
    }
    if (! lvl)
    {
        pdlvl_badparam("lvl");
        return false;
    }
    
    /* index outside range */
    if (idx >= (size_t) pdlvl_numdivs(lvl))
    {
        pdlvl_seterror("index %u out of range, max: %u", idx, (size_t) pdlvl_numdivs(lvl)-1);
        return false;
    }
    
    /* get data about subdivision */
    div = pdlvl_csubdiv(lvl, idx, &w, &h, &ptiles);
    
    /* write AREA tag and block size to stream */
    if (! pdlvl_writebe32(stream, AREA))
        return false;
    if (! pdlvl_writele32(stream, SIZEOF_SubArea(div)))
        return false;
    
    /* write unique ID number to stream */
    if (! pdlvl_writele32(stream, div->id))
        return false;

    /* write width and height to stream */
    if (! pdlvl_write8(stream, w))
        return false;
    if (! pdlvl_write8(stream, h))
        return false;
    
    /* write tile array to file */
    numtiles = w * h;
    for (int x = 0; x < numtiles; ++x)
    {
        if (! pdlvl_write8(stream, ptiles->gfx))
            return false;
        if (! pdlvl_write8(stream, ptiles->code))
            return false;
        ++ptiles;
    }
    
    return true;
}

int pdlvl_writelevel(FILE* stream, const Level* lvl)
{
    int count;
    
    /* bad parameters */
    if (! stream)
    {
        pdlvl_badparam("stream");
        return false;
    }
    if (! lvl)
    {
        pdlvl_badparam("lvl");
        return false;
    }
    
    /* seek to place after header */
    fseek(stream, sizeof(LevelHeader)+4, SEEK_SET);
    
    /* number of divisions in the level */
    count = pdlvl_numdivs(lvl);
    if (count < 1)
    {
        pdlvl_seterror("%d subdivisions in level", count);
        return false;
    }
    
    /* write every AREA block to file */
    for (int x = 0; x < count; ++x)
    {
        if (! pdlvl_writeAREA(stream, lvl, x))
            return false;
    }
    
    return true;
}

int pdlvl_readheader(FILE* stream, Level* lvl)
{
    int code;
    LevelHeader* header = NULL;
    
    /* bad parameters */
    if (! stream)
    {
        pdlvl_badparam("stream");
        return false;
    }
    if (! lvl)
    {
        pdlvl_badparam("lvl");
        return false;
    }
    
    /* header pointer */
    header = pdlvl_header(lvl);
    
    /* free 'divs' array if non-null */
    pdlvl_freedivs(lvl->divs, header->numdivs);
    header->numdivs = 0;
    
    /* read "magic" four-byte identifier */
    rewind(stream);
    if (pdlvl_readbe32(stream, &code) != PDLV)
    {
        if (code)
            pdlvl_seterror("PDLV identifier not found in header");
        return false;
    }
    
    /* read strings into header */
    clearerr(stream);
    pdlvl_readbytes(stream, header, COUNT_LENGTH, &code);
    if (! code)
        return false;
    
    /* read number of divisions */
    clearerr(stream);
    header->numdivs = pdlvl_readle16(stream, &code);
    if (! code)
        return false;
    
    return true;
}

int pdlvl_readAREA(FILE* stream, SubArea* subdiv, size_t blksize)
{
    int code;
    uint16_t numtiles;
    
    /* bad parameters */
    if (! stream)
    {
        pdlvl_badparam("stream");
        return false;
    }
    if (! subdiv)
    {
        pdlvl_badparam("subdiv");
        return false;
    }
    if (! blksize)
    {
        pdlvl_badparam("blksize");
        return false;
    }
    
    /* read ID number of block */
    subdiv->id = pdlvl_readle32(stream, &code);
    if (code)
    {
        /* read width and height */
        for (int x = 0; x < 2; ++x)
        {
            ((uint8_t*) &subdiv->width)[x] = pdlvl_read8(stream, &code);
            if (! code)
                return false;
        }
    }
    
    /* zero width or height */
    if (! subdiv->width)
    {
        pdlvl_seterror("sub-division %u zero width", subdiv->id);
    }
    else if (! subdiv->height)
    {
        pdlvl_seterror("sub-division %u zero height", subdiv->id);
    }
    else
    {
        /* allocate tile array */
        numtiles = subdiv->width * subdiv->height;
        subdiv->tiles = pdlvl_calloc(numtiles, sizeof(Tile));
        if (subdiv->tiles)
        {
            /* read and swap tile bytes */
            pdlvl_readbytes(stream, subdiv->tiles, sizeof(Tile)*numtiles, &code);
        }
    }
    
    return code;
}

size_t pdlvl_readlevel(FILE* stream, Level* lvl)
{
    size_t numdivs, i = 0, read = 0;
    SubArea* divs = NULL;
    
    /* bad parameters */
    if (! stream)
    {
        pdlvl_badparam("stream");
        return false;
    }
    if (! lvl)
    {
        pdlvl_badparam("lvl");
        return false;
    }
    
    /* number of divisions invalid? */
    numdivs = (size_t) pdlvl_numdivs(lvl);
    if (! numdivs)
    {
        pdlvl_seterror("zero sub-divisions");
        return false;
    }
    
    /* allocate an array of sub-divisions */
    divs = (SubArea*) pdlvl_calloc(numdivs, sizeof(SubArea));
    if (! divs)
        return false;
    
    /* read blocks of data */
    while (1)
    {
        uint32_t magic, blksize;
        int code;
        
        /* read "magic" integer */
        magic = pdlvl_readbe32(stream, &code);
        if (! code) break;
        read += 4;
        
        /* read block size */
        blksize = pdlvl_readle32(stream, &code);
        if (! code) break;
        read += 4;
        
        /* branch according to block type */
        switch (magic)
        {
            case AREA:
            {
                /* difference between current and start of the array */
                if (i >= numdivs)
                {
                    fseek(stream, (long int) blksize, SEEK_CUR);
                    break;
                }
                code = pdlvl_readAREA(stream, &divs[i++], blksize);
                break;
            }
            
            default:
            {
                fseek(stream, (long int) blksize, SEEK_CUR);
                code = true;
                break;
            }
        }
        
        /* failed to read data block */
        if (! code)
        {
            read = 0;
            break;
        }
    }
    
    /* free data if incomplete */
    if (! read)
    {
        pdlvl_freedivs(divs, numdivs);
        lvl->header.numdivs = 0;
    }
    else
    {
        lvl->divs = divs;
    }
    
#ifndef NDEBUG
    /* clear data */
    divs = NULL;
    numdivs = 0;
#endif
    
    return read;
}
