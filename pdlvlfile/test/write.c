#include "main.h"
#include "pd_string.h"
#include "memory.h"

#include <unistd.h>
#include <pdlvlfile.h>

static int testWriteData(int, const char*[], cmdlineInfo*);
static int testWriteLevel(int, const char*[], cmdlineInfo*);

extern const char* arg0;

int testWrite(int argc, const char* argv[], cmdlineInfo* info)
{
    int (*f)(int, const char*[], cmdlineInfo*) = NULL;
    
    /* not enough arguments */
    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments: should be %s %s\n", info->cmd, info->opt);
        return 1;
    }
    
    /* subcommand function */
    if (pd_strcmp(argv[1], "data") == 0)
    {
        f = testWriteData;
    }
    else if (pd_strcmp(argv[1], "level") == 0)
    {
        f = testWriteLevel;
    }
    
    /* invalid subcommand */
    if (! f)
    {
        fprintf(stderr, "invalid option '%s'\n", argv[1]);
        return 1;
    }
    
    adv_arg2(argc, argv);
    
    return f(argc, argv, info);
}

static int _dummy_writeu16(FILE* fs, uint16_t v)
{
    return true;
}

int testWriteData(int argc, const char* argv[], cmdlineInfo* info)
{
    struct
    {
        char dir[3];
        char value[11];
        char size[4];
    } args;
    
    /* pointers to pdlvlfile write functions */
    struct
    {
        int (*u8func)(FILE*, uint8_t);
        int (*u16func)(FILE*, uint16_t);
        int (*u32func)(FILE*, uint32_t);
    } writeFuncs;
    
    /* stream to file */
    FILE* fs = stdout;
    
    /* bit length */
    char cBit = 0;
    
    /* initialize memory */
    pd_fillzero(args);
    
    writeFuncs.u8func = pdlvl_write8;
    writeFuncs.u16func = pdlvl_writele16;
    writeFuncs.u32func = pdlvl_writele32;
    
    /* not enough arguments */
    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments: should be %s %s %s\n", arg0, info->cmd, info->opt);
        return 1;
    }
    
#if 1
    /* open file */
    fs = pdlvl_open(argv[0], "w");
    if (! fs)
    {
        fprintf(stderr, "error opening %s : %s\n", argv[1], pdlvl_geterror());
        return 1;
    }
#endif
    
    adv_arg(argc, argv);
    
    /* process lists of values */
    for (int x = 0; x < argc; ++x)
    {
        char caArg[30];
        size_t szHash = 0;
        uint32_t uiVal = 0;
        const char* token = NULL;  
        
        /* copy list argument to buffer */
        pd_strncpy(caArg, argv[x], 29);
        caArg[29] = '\0';
        
        /* a single value */
        if (! string_strcnt(caArg, ','))
        {
            pd_strncpy(args.value, caArg, 10);
            pd_strcpy(args.size, "32");
            pd_strcpy(args.dir, "le");
        }
        /* one or two commas */
        else
        {
            /* first token is a direction option */
            token = pd_strtok(caArg, ",");
            pd_strncpy(args.dir, token, 2);
            
            /* second is the value */
            token = pd_strtok(NULL, ",");
            pd_strncpy(args.value, token, 10);
            
            /* third, if present, is the bit length */
            token = pd_strtok(NULL, ",");
            if (token)
                pd_strncpy(args.size, token, 3);
            else
                pd_strcpy(args.size, "32");
        }
        
#ifndef NDEBUG
        printf("-- options:\n  -- value: %s\n  -- endian: %s\n  -- bit length: %s\n", args.value, args.dir, args.size);
#endif
        
        /* convert strings into usable values */
        uiVal = string_strtoul(args.value, NULL);
        cBit = string_strtol(args.size, NULL);
        if (cBit < 0)
        {
            cBit = -cBit;
        }
        szHash = makeHash(args.dir);
        
        /* what functions to call based on desired endianness */
        switch (szHash)
        {
            case 0: break;
            
            case 0X0072D288:
                /* be */
                writeFuncs.u16func = _dummy_writeu16;
                writeFuncs.u32func = pdlvl_writebe32;
                break;
            
            
            case 0X007A73A8:
                /* le */
                writeFuncs.u16func = pdlvl_writele16;
                writeFuncs.u32func = pdlvl_writele32;
                break;
            
            default:
            {
                fprintf(stderr, "invalid option \"%s\", defaulting to le", args.dir);
                writeFuncs.u16func = pdlvl_writele16;
                writeFuncs.u32func = pdlvl_writele32;
                break;
            }
        }
        
        /* write data to file */
        switch (cBit)
        {
            case 8:
                writeFuncs.u8func(fs, uiVal);
                break;
                
            case 16:
                writeFuncs.u16func(fs, uiVal);
                break;
            
            case 32:
                writeFuncs.u32func(fs, uiVal);
                break;
            
            default:
                fprintf(stderr, "Invalid bit length %d, can be 8 16 or 32.\n", (int) cBit);
                break;
        }
    }
    
#if 1
    /* close the file */
    pdlvl_close(fs);
#endif
    
    return 0;
}

static intArray _aOptParse(const char* arg, LevelHeader* hd, intArray vals)
{
    char caBuffer[50];
    intArray result = vals;
    size_t szNumDims, x;
    char* token;
    
    result.code = false;
    
    /* copy argument to buffer */
    pd_strncpy(caBuffer, arg, 49);
    caBuffer[49] = '\0';
    
    /* retrieve the first token */
    token = pd_strtok(caBuffer, ", ");
    if (! token)
    {
        fprintf(stderr, "Failed to tokenize string \"%s\"\n", arg);
        goto skip;
    }
    
    /* conversion to integer */
    szNumDims = string_strtoul(token, NULL);
    if (errno)
    {
        goto skip;
    }
    
    /* allocate array of integers */
    szNumDims *= 2;
    
    if (result.szLen < szNumDims)
    {
        int* ipDims = (int*) pdlvl_calloc(szNumDims, sizeof(int));
        free(result.ipVals);
        result.ipVals = ipDims;
        result.szLen = szNumDims;
    }
    
    /* split list into tokens and convert to integer */
    for (x = 0; x < szNumDims; ++x)
    {
        /* get next token */
        token = pd_strtok(NULL, ", ");
        if (! token) break;
        
        /* convert token into integer */
        result.ipVals[x] = string_strtol(token, NULL);
        if (errno)
        {
            fprintf(stderr, "Failed to convert \"%s\" to integer\n", token);
            goto skip;
        }
    }
    
    /* too few elements */
    if (x < szNumDims)
    {
        fprintf(stderr, "List argument \"%s\" is too short, should be %u length\n",
                arg, szNumDims+1);
        goto skip;
    }
    
    /* update header */
    hd->numdivs = szNumDims / 2;
    
    /* result code */
    result.code = true;
    
skip:
    
    return result;
}

int testWriteLevel(int argc, const char* argv[], cmdlineInfo* info)
{
    int iOpt = 0;
    char** args = (char**) argv;
    
    /* not enough arguments */
    if (argc < 5)
    {
        fprintf(stderr, "wrong number of arguments: should be %s write level FILE -a LIST -t FILE [-m FILE]\
 [-b FILE] [-B FILE]\n", arg0);
        return 1;
    }
    
    /* file argument */
    pd_fillzero(info->hd);
    pd_fillzero(info->vals);
    info->file = argv[0];
    adv_arg(argc, argv);
    
    /* process all options */
    optind = 0;
    while ((iOpt = getopt(argc, args, "t:b:B:a:")) > 0)
    {
        print_int(optind);
        
        /* which option? */
        switch ((char) iOpt)
        {
            case 't':
                pd_strncpy(info->hd.tileset, optarg, TILESET_LENGTH-1);
                break;
            
            case 'b':
                pd_strncpy(info->hd.bgBottom, optarg, BGBOTTOM_LENGTH-1);
                break;
            
            case 'B':
                pd_strncpy(info->hd.bgTop, optarg, BGTOP_LENGTH-1);
                break;
            
            case 'a':
                /* parse string */
                info->vals = _aOptParse(optarg, &info->hd, info->vals);
                if (! info->vals.code)
                {
                    delCmdInfo(info);
                    return 1;
                }
#ifndef NDEBUG
                for (size_t x = 0; x < (info->hd.numdivs*2); ++x)
                {
                    printf("-- argv[%u] = %d\n", x, info->vals.ipVals[x]);
                }
#endif
                break;
            
            case '?':
                printf("error returned from getopt\n");
                break;
            
            default:
                break;
        }
    }
    
    /* error if no integer array */
    if (! info->vals.ipVals)
    {
        fprintf(stderr, "missing 'a' option\n");
        return 1;
    }
    
    /* build level structure */
    print_uint(info->hd.numdivs*2);
    print_uint(info->hd.numdivs);
    assert((info->hd.numdivs*2) == info->vals.szLen);
    
    info->lvl = pdlvl_new_i(info->hd.numdivs, info->vals.ipVals);
    if (! info->lvl)
    {
        fprintf(stderr, "Failed to create level structure: %s\n", pdlvl_geterror());
        delCmdInfo(info);
        return 1;
    }
    
    {
        LevelHeader* phd = pdlvl_header(info->lvl);
        size_t szDivs = phd->numdivs;
        *phd = info->hd;
        phd->numdivs = szDivs;
    }
    
    /* open level file */
    info->fs = pdlvl_open(info->file, "w");
    if (! info->fs)
    {
        fprintf(stderr, "Failed to open %s : %s\n", info->file, pdlvl_geterror());
        delCmdInfo(info);
        return 1;
    }
    
    /* write header to file */
    if (! pdlvl_writeheader(info->fs, info->lvl))
    {
        fprintf(stderr, "Failed to write header to file: %s\n", pdlvl_geterror());
        delCmdInfo(info);
        return 1;
    }
    
    /* write level blocks to file */
    if (pdlvl_writelevel(info->fs, info->lvl) < 0)
    {
        fprintf(stderr, "Failed to write level blocks to file: %s\n", pdlvl_geterror());
        delCmdInfo(info);
        return 1;
    }
    
    /* free memory */
    delCmdInfo(info);
    
    return 0;
}
