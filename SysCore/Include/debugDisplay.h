#ifndef __DEBUG_DISPLAY_H_
#define __DEBUG_DISPLAY_H_

extern void debugClrScr(const unsigned short c);
extern void debugPutS(char *str);
extern int debugPrintf(const char* str,...);
extern unsigned debugSetColor(const unsigned c);
extern void debugGoToXY(unsigned x,unsigned y);


#endif
