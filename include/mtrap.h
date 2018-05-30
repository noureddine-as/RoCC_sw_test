#ifndef _RISCV_MTRAP_H
#define _RISCV_MTRAP_H

#include "encoding.h"

#ifdef __riscv_atomic
# define MAX_HARTS 8 // arbitrary
#else
# define MAX_HARTS 1
#endif

#ifndef __ASSEMBLER__

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#define read_const_csr(reg) ({ unsigned long __tmp; \
  asm ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

static inline int supports_extension(char ext)
{
  return read_const_csr(misa) & (1 << (ext - 'A'));
}

static inline int xlen()
{
  return read_const_csr(misa) < 0 ? 64 : 32;
}

//#define assert(x) ({ if (!(x)) die("assertion failed: %s", #x); })
//#define die(str, ...) ({ printm("%s:%d: " str "\n", __FILE__, __LINE__, ##__VA_ARGS__); poweroff(-1); })

static inline void wfi()
{
  asm volatile ("wfi" ::: "memory");
}

#endif // !__ASSEMBLER__

#define MTIMECMP_BASE       	0x02004000
#define MTIME_BASE        		0x0200bff8

#define IPI_SOFT       0x1
#define IPI_FENCE_I    0x2
#define IPI_SFENCE_VMA 0x4
#define IPI_HALT       0x8

#define MACHINE_STACK_SIZE RISCV_PGSIZE
#define MENTRY_HLS_OFFSET (INTEGER_CONTEXT_SIZE + SOFT_FLOAT_CONTEXT_SIZE)
#define MENTRY_FRAME_SIZE (MENTRY_HLS_OFFSET + HLS_SIZE)
#define MENTRY_IPI_OFFSET (MENTRY_HLS_OFFSET)
#define MENTRY_IPI_PENDING_OFFSET (MENTRY_HLS_OFFSET + REGBYTES)

#ifdef __riscv_flen
# define SOFT_FLOAT_CONTEXT_SIZE 0
#else
# define SOFT_FLOAT_CONTEXT_SIZE (8 * 32)
#endif
#define HLS_SIZE 64
#define INTEGER_CONTEXT_SIZE (32 * REGBYTES)

#endif
