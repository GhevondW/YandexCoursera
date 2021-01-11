#ifndef _DEFINES_H_
#define _DEFINES_H_

#ifndef SIZE
#define SIZE(array) sizeof(array)/sizeof(array[0])
#endif /* SIZE */

#ifndef MIN
#define MIN(a, b) (((a)<(b))?(a):(b))
#endif /* MIN */
#ifndef MAX
#define MAX(a, b) (((a)>(b))?(a):(b))
#endif  /* MAX */

#endif