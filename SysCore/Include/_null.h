#ifndef __NULL_H_
#define __BULL_H_

#ifdef NULL
#undef NULL
#endif

// In C NULL is not 0
#define NULL (void *)0


#endif