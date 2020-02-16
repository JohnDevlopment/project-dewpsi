#include "pdlvlfile.h"
#include "pd_memory.h"
#include "pd_types.h"
#include "pd_stdinc.h"
#include "pd_internal.h"

void* pdlvl_malloc(size_t size)
{
    void* result = malloc(size);
    if (! result)
    {
        out_of_memory();
    }
    
    return result;
}

void* pdlvl_calloc(size_t count, size_t size)
{
    void* result = calloc(count, size);
    if (! result)
    {
        out_of_memory();
    }
    
    return result;
}

Level* pdlvl_newempty(void)
{
    Level* result = (Level*) malloc(sizeof(Level));
    if (! result)
    {
        out_of_memory();
    }
    else
    {
        zero_outp(result);
    }

    return result;
}

Level* pdlvl_new(size_t numdivs, const int* pdims)
{
    size_t cnt;
    Level* result;

    /* bad parameters */
    if (! numdivs)
    {
        bad_param("numdivs");
        return NULL;
    }
    if (! pdims)
    {
        bad_param("pdims");
        return NULL;
    }

    /* allocate Level pointer */
    result = pdlvl_newempty();

    /* initialize default values */
    result->header.numdivs = numdivs;

    /* allocate SubArea pointer inside Level */
    result->divs = (SubArea*) calloc(numdivs, sizeof(SubArea));
    if (! result->divs)
    {
        out_of_memory();
        pdlvl_free(result);
        return NULL;
    }
    /*memset(result->divs, 0, sizeof(SubArea)*numdivs);*/

    /* start reading arguments */
    cnt = numdivs * 2;
    for (size_t i = 0; i < cnt; i += 2)
    {
        int w, h;
        SubArea* curdiv = &result->divs[i>>1]; /* i>>i divides i by 2 */
        w = pdims[i];
        h = pdims[i+1];
        /* invalid width and height */
        if (w <= 0 || h <= 0)
        {
            pdlvl_seterror("width and/or height paramters are <= 0");
            pdlvl_free(result);
            return NULL;
        }
        curdiv->width = w;
        curdiv->height = h;
        /* array of tiles */
        curdiv->tiles = allocm(Tile, (size_t) w*h);
        if (! curdiv->tiles)
        {
            out_of_memory();
            pdlvl_free(result);
            return NULL;
        }
        memset(curdiv->tiles, 0, sizeof(Tile)*(w*h));
    }

    return result;
}

void pdlvl_free(Level* ptr)
{
    if (ptr)
    {
        pdlvl_freedivs(pdlvl_subdiv(ptr, 0, NULL, NULL, NULL), pdlvl_numdivs(ptr));
        free(ptr);
    }
}

void pdlvl_freedivs(SubArea* divs, size_t numdivs)
{
    if (divs)
    {
        SubArea* curdiv = divs;
        for (size_t i = 0; i < numdivs; ++i)
        {
            free(curdiv->tiles);
            curdiv->tiles = NULL;
        }
        free(divs);
        divs = NULL;
    }
}

/*
pdlvl_open - open a binary file for read or write or both
    @param file     file to load
    @param mode     w, w+, r, r+, a, a+ (fopen mode parameter)
    @return         a pointer to a FILE object that identifies a file stream or NULL on failure
pdlvl_close - close the file
    @param handle   a pointer to a FILE object that identifies a stream
*/
FILE* pdlvl_open(const char* file, const char* mode)
{
    char mmode[5];
    char * ptr;
    FILE * handle = NULL;

    /* append 'b' to mode */
    memset(mmode, 0, 5);
    strcpy(mmode, mode);
    ptr = strchr(mmode, '+');

    if (ptr)
    {
        *ptr = 'b';
        ++ptr;
        *ptr = '+';
    }
    else
        strcat(mmode, "b");

    handle = fopen(file, mode);

    /* on error */
    if (! handle)
        write_error();

    return handle;
}
void pdlvl_close(FILE* handle)
{
    fclose(handle);
}

int pdlvl_numdivs(const Level* ptr)
{
    if (! ptr)
    {
        bad_param("ptr");
        return -1;
    }
    return (int) ptr->header.numdivs;
}

LevelHeader* pdlvl_header(Level* ptr)
{
    LevelHeader* result = NULL;
    
    if (ptr)
        result = &ptr->header;
    
    return result;
}
const LevelHeader* pdlvl_cheader(const Level* ptr)
{
    const LevelHeader* result = NULL;
    
    if (ptr)
        result = &ptr->header;
    
    return result;
}

SubArea* pdlvl_subdiv(Level* lvl, size_t idx, int* pw, int* ph, Tile** pptiles)
{
    SubArea* div;

    if (! lvl)
    {
        bad_param("lvl");
        return NULL;
    }

    if (idx >= lvl->header.numdivs)
    {
        pdlvl_seterror("invalid index %u, level only has %u subdivisions", idx, (size_t) lvl->header.numdivs);
        return NULL;
    }

    div = &lvl->divs[idx];

    if (pw)
        *pw = (int) div->width;

    if (ph)
        *ph = (int) div->height;

    if (pptiles)
        *pptiles = div->tiles;

    return div;
}

const SubArea* pdlvl_csubdiv(const Level* lvl, size_t idx, int* pw, int* ph, const Tile** pptiles)
{
    const SubArea* div;

    if (! lvl)
    {
        bad_param("lvl");
        return NULL;
    }

    if (idx >= lvl->header.numdivs)
    {
        pdlvl_seterror("invalid index %u, level only has %u subdivisions", idx, (size_t) lvl->header.numdivs);
        return NULL;
    }

    div = &lvl->divs[idx];

    if (pw)
        *pw = (int) div->width;

    if (ph)
        *ph = (int) div->height;

    if (pptiles)
        *pptiles = div->tiles;

    return div;
}
