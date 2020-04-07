#ifndef PD_INTERNAL_H_INCLUDED
#define PD_INTERNAL_H_INCLUDED

#define PDLV                0x50444C56 /* file identifier */
#define AREA                0x41524541 /* AREA block identifier */

#define EOF_ERROR           "end of file was reached"
#define alloc(ptr, type)    (type*) pdlvl_malloc(sizeof(type));
#define allocm(type, n)     (type*) pdlvl_calloc(n, sizeof(type));
#define zero_outp(ptr)      memset(ptr, 0, sizeof(*ptr));

#ifdef BGBOTTOM_LENGTH
static const int COUNT_LENGTH = BGBOTTOM_LENGTH + BGTOP_LENGTH + TILESET_LENGTH + MUSIC_LENGTH;
#endif

#endif /* PD_INTERNAL_H_INCLUDED */
