#include "pdlvlfile.h"
#include "pd_string.h"
#include "pd_memory.h"
#include "pd_types.h"
#include "pd_stdinc.h"
#include "pd_internal.h"
#include "pd_config.h"
#include "stdarg.h"

void* pdlvl_malloc(size_t size)
{
    /* allocate memory */
    void* result = malloc(size);
    if (! result)
    {
        pdlvl_outofmemory();
    }
    
    return result;
}

void* pdlvl_calloc(size_t count, size_t size)
{
    /* allocate memory */
    void* result = calloc(count, size);
    if (! result)
    {
        pdlvl_outofmemory();
    }
    
    return result;
}

Level* pdlvl_newempty(void)
{
    /* allocate empty structure */
    Level* result = (Level*) malloc(sizeof(Level));
    if (! result)
    {
        pdlvl_outofmemory();
    }
    else
    {
        zero_outp(result);
    }

    return result;
}

Level* pdlvl_new(const char* dims)
{
    size_t length = 0;
    Level* result = NULL;
    int* idims = NULL;
    char* buffer = NULL;
    char prev = 0, c;
    
    if (! dims)
    {
        pdlvl_badparam("dims");
        return NULL;
    }
    
    /* number of elements in the list-string */
    for (const char* ptr = dims; *ptr != '\0'; ++ptr)
    {
        c = *ptr;
        if (c == ' ')
        {
            if (prev != ' ')
                ++length;
        }
        else if (! pdlvl_isdigit(c))
        {
            pdlvl_seterror("Non-digit and non-space character found: %c", (unsigned char) c);
            return NULL;
        }
        prev = c;
    }
    ++length;
    
    if (length & 1)
    {
        pdlvl_seterror("Odd number of integers in list-string.");
        return NULL;
    }
    
    idims = (int*) alloca(sizeof(int) * length);
    
    /* string buffer */
    length = pdlvl_strlen(dims);
    buffer = (char*) alloca(length);
    pdlvl_strcpy(buffer, dims);
    
    {
        int index = 0;
        char* token = pdlvl_strtok(buffer, " ");
        
        while (token)
        {
            idims[index++] = pdlvl_atoi(token);
            token = pdlvl_strtok(NULL, " ");
            idims[index++] = pdlvl_atoi(token);
            token = pdlvl_strtok(NULL, " ");
        }
    }
    
    return pdlvl_new_i(length / 2, idims);
}

Level* pdlvl_new_i(size_t numdivs, const int* pdims)
{
    size_t cnt;
    Level* result;

    /* bad parameters */
    if (! numdivs)
    {
        pdlvl_badparam("numdivs");
        return NULL;
    }
    if (! pdims)
    {
        pdlvl_badparam("pdims");
        return NULL;
    }

    /* allocate Level pointer */
    result = pdlvl_newempty();
    if (! result)
        return NULL;

    /* initialize default values */
    result->header.numdivs = numdivs;

    /* allocate SubArea pointer inside Level */
    result->divs = (SubArea*) pdlvl_calloc(numdivs, sizeof(SubArea));
    if (! result->divs)
    {
        pdlvl_free(result);
        return NULL;
    }

    /* start reading arguments */
    cnt = numdivs * 2;
    for (size_t i = 0; i < cnt; i += 2)
    {
        int w, h;
        SubArea* curdiv = &result->divs[i>>1]; /* 'i>>1' divides i by 2 */
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
        curdiv->tiles = pdlvl_calloc((size_t) w*h, sizeof(Tile));
        if (! curdiv->tiles)
        {
            pdlvl_free(result);
            return NULL;
        }
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
            ++curdiv;
        }
        free(divs);
#ifndef NDEBUG
        divs = NULL;
        curdiv = NULL;
#endif
    }
}

FILE* pdlvl_open(const char* file, const char* mode)
{
    char mmode[5];
    char * ptr;
    FILE * handle = NULL;

    /* append 'b' to mode */
    memset(mmode, 0, 5);
    strcpy(mmode, mode);
    ptr = pdlvl_strchr(mmode, '+');

    if (ptr)
    {
        *ptr = 'b';
        ++ptr;
        *ptr = '+';
    }
    else
        pdlvl_strcat(mmode, "b");
    
    /* open file */
    handle = fopen(file, mode);
    /* on error */
    if (! handle)
    {
        pdlvl_writeerror();
    }

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
        pdlvl_badparam("ptr");
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
    
    /* bad parameters */
    if (! lvl)
    {
        pdlvl_badparam("lvl");
        return NULL;
    }
    if (idx >= lvl->header.numdivs)
    {
        pdlvl_seterror("invalid index %u, level only has %u subdivisions", idx, (size_t) lvl->header.numdivs);
        return NULL;
    }

    /* no sub-divisions in level */
    if (! lvl->divs)
    {
        pdlvl_seterror("no sub-divisions in level");
        return NULL;
    }

    /* pointer to sub-division */
    div = &lvl->divs[idx];
    
    /* other information about the sub-division */
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
    Level * lvl2 = (Level*) lvl;
    Tile** pptiles2 = (Tile**) pptiles;
    return (const SubArea*) pdlvl_subdiv(lvl2, idx, pw, ph, pptiles2);
}
