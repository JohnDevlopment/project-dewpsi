#include "pd_endian.h"
#include <limits.h>

#if !defined(LINUX) || defined(KEEP_SWAP_FUNCTIONS)
static int get_endian(void)
{
    static short int _endian = 0;
    union
    {
        uint32_t value;
        uint8_t data[4];
    } number;

    /* set the variable's value on the first call */
    if (! _endian)
    {
        number.data[0] = 1;
        number.data[1] = 2;
        number.data[2] = 3;
        number.data[3] = 4;

        switch (number.value)
        {
            case 0x04030201:
                _endian = LITTLE_ENDIAN;
                break;

            case 0x01020304:
                _endian = BIG_ENDIAN;
                break;

            default:
                _endian = UNKNOWN_ENDIAN;
                break;
        }

        /* abort if unknown endianness  */
        if (_endian == UNKNOWN_ENDIAN)
        {
            fprintf(stderr, "unknown byte order, not big or little endian\n");
            abort();
        }
    }

    return (int) _endian;
}
#endif /* LINUX */

/* These functions swap values */

#if !defined(LINUX) || defined(KEEP_SWAP_FUNCTIONS)
uint16_t _pdlvl_swap16(uint16_t x)
{
    union
    {
        uint16_t value;
        uint8_t bytes[2];
    } number;

    /* swap bytes in integer */
    number.bytes[0] = ((uint8_t*) &x)[1];
    number.bytes[1] = ((uint8_t*) &x)[0];

    return number.value;
}
#endif /* LINUX */

#if !defined(LINUX) || defined(KEEP_SWAP_FUNCTIONS)
uint32_t _pdlvl_swap32(uint32_t x)
{
    union
    {
        uint32_t value;
        uint8_t bytes[4];
    } number;

    /* swap bytes in integer */
    number.bytes[0] = ((uint8_t*) &x)[3];
    number.bytes[1] = ((uint8_t*) &x)[2];
    number.bytes[2] = ((uint8_t*) &x)[1];
    number.bytes[3] = ((uint8_t*) &x)[0];

    return number.value;
}
#endif

/* conditionally swap values from native to a specific endianness */

uint16_t pdlvl_ntole16(uint16_t x)
{
#ifdef LINUX
    return htole16(x);
#else
    if (get_endian() == LITTLE_ENDIAN)
        return x;

    return pdlvl_swap16(x);
#endif /* LINUX */
}

uint32_t pdlvl_ntole32(uint32_t x)
{
#ifdef LINUX
    return htole32(x);
#else
    if (get_endian() == LITTLE_ENDIAN)
        return x;

    return pdlvl_swap32(x);
#endif
}

uint32_t pdlvl_ntobe32(uint32_t x)
{
#ifdef LINUX
    return htobe32(x);
#else
    if (get_endian() == BIG_ENDIAN)
        return x;

    return pdlvl_swap32(x);
#endif
}

/* conditionally swap values from an endianness to the native byte order */

uint16_t pdlvl_le16ton(uint16_t x)
{
#ifdef LINUX
    return le16toh(x);
#else
    if (get_endian() != LITTLE_ENDIAN)
        return pdlvl_swap16(x);
    
    return x;
#endif
}

uint32_t pdlvl_le32ton(uint32_t x)
{
#ifdef LINUX
    return le32toh(x);
#else
    if (get_endian() != LITTLE_ENDIAN)
        return pdlvl_swap32(x);

    return x;
#endif
}

uint32_t pdlvl_be32ton(uint32_t x)
{
#ifdef LINUX
    return be32toh(x);
#else
    if (get_endian() != BIG_ENDIAN)
        return pdlvl_swap32(x);

    return x;
#endif
}
