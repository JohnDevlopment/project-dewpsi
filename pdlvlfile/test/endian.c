#include "main.h"
#include "pd_stdinc.h"
#include "pd_string.h"
#include <pdlvlfile.h>

typedef struct {
    uint32_t (*ui32func)(uint32_t);
    uint16_t (*ui16func)(uint16_t);
    const char* str;
} endianCommand;

extern const char* arg0;

static const char _str1[] = "from native to little endian";
static const char _str2[] = "from little endian to native byte order";
static const char _str3[] = "from big endian to native byte order";
static const char _str4[] = "from native to big endian";

int testEndian(int argc, const char* argv[], cmdlineInfo* info)
{
    endianCommand cmd = {
        pdlvl_ntole32, pdlvl_ntole16, _str1
    };
    unsigned int uiVal = 0;
    char cBit = 32;
    
    /* not enough arguments */
    if (argc < 2)
    {
        fprintf(stderr, "Not enough arguments: should be %s %s\n", info->cmd, info->opt);
        return 1;
    }
    
#ifndef NDEBUG
    printf("-- %d arguments: ", argc);
    for (int x = 0; x < argc; ++x)
    {
        printf("%s ", argv[x]);
    }
    putchar('\n');
    
    printf("-- functions: pdlvl_be32ton (%p), pdlvl_ntobe32(%p)\n", pdlvl_be32ton, pdlvl_ntobe32);
    printf("-- functions: pdlvl_le32ton (%p), pdlvl_le16ton(%p)\n", pdlvl_le32ton, pdlvl_le16ton);
    printf("-- functions: pdlvl_ntole32 (%p), pdlvl_ntole16(%p)\n", pdlvl_ntole32, pdlvl_ntole16);
#endif
    
#if 0
    return 0;
#endif
    
    /* parse arguments */
    while (argc > 0)
    {
        char cSkip = false;
        
#ifndef NDEBUG
        printf("-- argc = %d, argv[0] = %s\n", argc, argv[0]);
#endif
        
        /* process each commandline option */
        switch (makeHash(argv[0]))
        {
            case 0x0088cec8:
            {
                /* --size */
                int iTemp = 0;
                no_arg(argc, "--size");
                
                /* convert string to integer */
                iTemp = pd_atoi(argv[1]);
                if (! iTemp)
                {
                    fprintf(stderr, "Failed to convert integer\n");
                    return 1;
                }
                
                /* set value, skip, advance arguments */
                cBit = (char) iTemp;
                cSkip = true;
                adv_arg2(argc, argv);
                break;
            }
            
            case 0x0090d45b:
            {
                /* --beton */
                cmd.ui32func = pdlvl_be32ton;
                cmd.ui16func = NULL;
                cmd.str = _str3;
                break;
            }
            
            case 0x0093586b:
            {
                /* --ntobe */
                cmd.ui32func = pdlvl_ntobe32;
                cmd.ui16func = NULL;
                cmd.str = _str4;
                break;
            }
            
            case 0x00935f66:
            {
                /* --leton */
                cmd.ui32func = pdlvl_le32ton;
                cmd.ui16func = pdlvl_le16ton;
                cmd.str = _str2;
                break;
            }
            
            case 0x00949df1:
            {
                /* --ntole */
                cmd.ui32func = pdlvl_ntole32;
                cmd.ui16func = pdlvl_ntole16;
                cmd.str = _str1;
                break;
            }
            
            default: break;
        }
        
        /* skip iteration */
        if (cSkip)
        {
            continue;
        }
        
        /* last option should be an integer */
        if (argc == 1)
        {
            uiVal = string_strtoul(argv[0], NULL);
            if (errno)
                return 1;
        }
        
        /* shift argument list */
        adv_arg(argc, argv);
    }
    
#ifndef NDEBUG
    printf("Done processing arguments\n");
#endif
    
    /* actions based on bit size */
    switch (cBit)
    {
        case 32:
        {
            if (cmd.ui32func)
            {
                
#ifndef NDEBUG
                printf("-- function: cmd.ui32func (%p)\n", cmd.ui32func);
#endif
                printf("0x%08x converted %s: 0x%08x\n", uiVal, cmd.str, cmd.ui32func(uiVal));
            }
            break;
        }
        
        case 16:
        {
            if (cmd.ui16func)
            {
#ifndef NDEBUG
                printf("-- function: cmd.ui16func (%p)\n", cmd.ui16func);
#endif
                printf("0x%04x converted %s: 0x%04x\n", uiVal, cmd.str, cmd.ui16func(uiVal));
            }
            break;
        }
        
        case 8:
            printf("Printing 8 bit integer %02x\n", uiVal);
            break;

        default:
            fprintf(stderr, "Incorrect bit size %d\n", (int) cBit);
            return 1;
            break;
    }
    
    return 0;
}
