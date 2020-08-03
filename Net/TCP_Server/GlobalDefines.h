#ifndef _GLOBAL_DEFINES_H_
#define _GLOBAL_DEFINES_H_

#define MAX_WORKERS_COUNT 20

#define SAFE_DELETE_OBJ(obj) \
    if(obj != nullptr){\
        delete obj;    \
        obj = nullptr; \
    }

#define SAFE_DELETE_ARR(arr) \
    if(arr != nullptr){\
        delete[] arr;    \
        arr = nullptr; \
    }


#endif

