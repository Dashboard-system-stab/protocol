#ifndef MICROJET_H
#define MICROJET_H

#include "stdarg.h"
#include "memory.h"
#include "stdio.h"
#include "stdbool.h"
#include "stddef.h"
#include "microjet_def.h"

#include "mjdriver_interface.h"
#if UINTPTR_MAX == 0xFF
    typedef uint8_t mj_ptr_t;
#elif UINTPTR_MAX == 0xFFFF
    typedef uint16_t mj_ptr_t;
#elif UINTPTR_MAX == 0xFFFFFFFF
    typedef uint32_t mj_ptr_t;
#elif UINTPTR_MAX == 0xFFFFFFFFFFFFFFFF
    typedef uint64_t mj_ptr_t;
#else
    #error "microjet.h - unsupported platform"
#endif

#if __GNUC__
#define OPTIMIZE __attribute__((optimize("O2")))
#else
#define OPTIMIZE
#endif

#define MJ_HEADER_SIZE (sizeof(mj_msg_header_t))

/** Send mcast join msg each 2500 ms */
#define MJ_IPMCAST_PERIOD_TICK 10000

#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
}
#endif
#endif /* MICROJET_H */