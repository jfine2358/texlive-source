/*
   kanji.h: Handling 2byte char, and so on.
*/
#ifndef KANJI_H
#define KANJI_H
#include "cpascal.h"
#include <ptexenc/ptexenc.h>
#ifdef epTeX
#include <ptexenc/unicode.h>
#define getintone(w) ((w).cint1)
#define setintone(w,a) ((w).cint1=(a))
#endif

#define KANJI

#if !defined(WIN32)
extern int sjisterminal;
#endif

/* functions */
#define Hi(x) (((x) >> 8) & 0xff)
#define Lo(x) ((x) & 0xff)

extern int check_kanji (integer c);
#define checkkanji check_kanji
extern boolean is_kanji (integer c);
#define iskanji is_kanji
extern boolean is_char_ascii (integer c);
#define ischarascii is_char_ascii
extern boolean is_wchar_ascii (integer c);
#define iswcharascii is_wchar_ascii
extern boolean ismultiprn (integer c);
extern integer calc_pos (integer c);
#define calcpos calc_pos
extern integer kcatcodekey (integer c);
extern void initdefaultkanji (void);

#ifndef PRESERVE_PUTC
#undef putc
#define putc(c,fp) putc2(c,fp)
#endif /* !PRESERVE_PUTC */

#ifdef PBIBTEX
#define inputline2(fp,buff,pos,size,ptr) input_line2(fp,buff,pos,size,ptr)
#else
#define inputline2(fp,buff,pos,size) input_line2(fp,buff,pos,size,NULL)
#endif

#endif /* not KANJI_H */
