#ifndef _GLOBAL_DEFINES_H_
#define _GLOBAL_DEFINES_H_

#define MAX_WORKERS_COUNT 4

#define SAFE_DELETE_OBJ(obj) \
    if(obj != nullptr){\
        delete obj;    \
        obj = nullptr; \
    }

#endif
