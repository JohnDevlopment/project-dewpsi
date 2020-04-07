#include "pd_stdinc.h"
#include "main.h"
#include "memory.h"
#include <stdarg.h>

#define getCmdInfo(i, s)            s.cmd = _Cmdline[i*3]; \
                                    s.opt = _Cmdline[i*3+1];

#define getCmdInfop(i, s)           s->cmd = _Cmdline[i*3]; \
                                    s->opt = _Cmdline[i*3+1];

enum {
    IDX_ENDIAN = 0,
    IDX_HASH,
    IDX_WRITE
};

int testEndian(int, const char*[], cmdlineInfo*);
int testWrite(int argc, const char* argv[], cmdlineInfo*);

static const char _CmdEndian[] = "endian";
static const char _OptEndian[] = "[--size 32|16|8] [--ntole|--leton|--beton] integer";
static const char _HlpEndian[] = "Defaults: --size=32 ; --ntole";

static const char _CmdHash[] = "hash";
static const char _OptHash[] = "string_to_hash";

static const char _CmdWrite[] = "write";
static const char _OptWrite[] = "data FILE LIST [LIST ...]\n\
        level FILE args...";
static const char _HlpWrite[] = "LIST = DIR,VALUE,SIZE | DIR,VALUE | VALUE";

static const char _Empty[] = " ";

static const char* _Cmdline[] = {
    _CmdEndian, _OptEndian, _HlpEndian,
    _CmdHash,   _OptHash,   _Empty,
    _CmdWrite,  _OptWrite,  _HlpWrite
};

const int NumTests = 3;

const char* arg0 = NULL;

static void quit(void)
{
    arg0 = NULL;
    freeMemory(0);
}

static int usage()
{
    printf("Usage:\n");
    for (int x = 0; x < NumTests; ++x)
    {
        const char** pptr = &_Cmdline[x*3];
        printf("  %s %s %s\n    %s\n", arg0, pptr[0], pptr[1], pptr[2]);
    }
    
    return 1;
}

static int testHash(int argc, const char* argv[], cmdlineInfo* info)
{
    uint32_t uiHash;
    
    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments: should be %s %s\n", info->cmd, info->opt);
        return 1;
    }
    
    while (argc > 1)
    {
        uiHash = makeHash(argv[1]);
        printf("The hash of \"%s\" is 0x%08x\n", argv[1], uiHash);
        adv_arg(argc, argv);
    }
    
    return 0;
}

int main(int argc, const char* argv[])
{
    int (*f)(int, const char*[], cmdlineInfo*) = NULL;
    cmdlineInfo* info = pdlvl_malloc(sizeof(cmdlineInfo));
    
    /* register cleanup function */
    pd_atexit(quit);
    freeMemory(1, info);
    
    /* initialize allocated memory */
    pd_memset(info, 0, sizeof(cmdlineInfo));
    
    /* name of application */
    arg0 = pd_strrchr(argv[0], '/') + 1;
    
    /* two few arguments */
    if (argc < 2)
    {
        fprintf(stderr, "No arguments given. Usage: %s command [options]\n", arg0);
        return 1;
    }
    
    /* process <command> argument */
    switch (makeHash(argv[1]))
    {
        case 0x00a87b82:
        {
            /* hash */
            f = testHash;
            getCmdInfop(IDX_HASH, info);
            break;
        }
        
        case 0x00a9c108:
        {
            /* help */
            printf("Printing help message\n");
            usage();
            return 0;
            break;
        }
        
        case 0x00c5d7c8:
        {
            /* endian */
            f = testEndian;
            getCmdInfop(IDX_ENDIAN, info);
            break;
        }
        
        case 0x00ca54e0:
        {
            /* write */
            f = testWrite;
            getCmdInfop(IDX_WRITE, info);
            break;
        }
        
        default:
        {
            fprintf(stderr, "Invalid command '%s'\n", argv[1]);
            return usage();
        }
    }
    
    /* advance argument list */
    adv_arg(argc, argv);
    
    return f(argc, argv, info);
}

uint32_t makeHash(const char* str)
{
    const uint16_t uiMult = 50000U;
    uint32_t uiHash = 0;
    size_t szLen = pd_strlen(str);
    
    for (size_t x = 0; x < szLen; ++x)
    {
        uiHash += cast(uint32_t, ((str[x] * uiMult) + ((x + 1) * uiMult)) / (x + 1));
    }
    
    return uiHash;
}

void freeMemory(int count, ...)
{
    va_list args;
    static void** vppAddr = NULL;
    static int iCount = 0;
    
    /* if count is zero, frees all saved pointers */
    if (count <= 0)
    {
        for (int x = 0; x < iCount; ++x)
        {
            free(vppAddr[x]);
        }
        free(vppAddr);
        vppAddr = NULL;
        iCount = 0;
    }
    /* append to list of pointers */
    else if (count >= 1)
    {
        void** temp = (void**) pdlvl_calloc(count+iCount, sizeof(void**));
        
        /* copy old array to new array */
        for (int x = 0; x < iCount; ++x)
        {
            temp[x] = vppAddr[x];
            vppAddr[x] = NULL;
        }
        
        /* free and replace old pointer */
        free(vppAddr);
        vppAddr = temp;
        temp = NULL;
        
        /* add pointer arguments to list */
        va_start(args, count);
        
        for (int x = iCount; x < (count+iCount); ++x)
        {
            vppAddr[x] = va_arg(args, void*);
        }
        iCount += count;
        
        va_end(args);
    }
}

void delCmdInfo(cmdlineInfo* const info)
{
    if (! info)
    {
        fprintf(stderr, "NULL parameter \"info\"\n");
    }
    else
    {
        pdlvl_close(info->fs);
        pdlvl_free(info->lvl);
        free(info->vals.ipVals);
        pd_memset(info, 0, sizeof(cmdlineInfo));
    }
}
