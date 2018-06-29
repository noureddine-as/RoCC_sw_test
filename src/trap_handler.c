/*======================================================================*/
/* TIMA LABORATORY                                                      */
/*======================================================================*/
#include <stdint.h>
#include "encoding.h"
#include "util.h"
#include "trap_handler.h"

void dump_tf(uintptr_t cause, uintptr_t epc, uintptr_t regs[32])
{
  static const char* regnames[] = {
    "z ", "ra", "sp", "gp", "tp", "t0",  "t1",  "t2",
    "s0", "s1", "a0", "a1", "a2", "a3",  "a4",  "a5",
    "a6", "a7", "s2", "s3", "s4", "s5",  "s6",  "s7",
    "s8", "s9", "sA", "sB", "t3", "t4",  "t5",  "t6"
  };

  //regs[0] = 0;

  for(int i = 0; i < 32; i+=4)
  {
    for(int j = 0; j < 4; j++)
      printf("%s %lx%c",regnames[i+j], regs[i+j],j < 3 ? '\t' : '\n');
  }
  printf("pc %lx\n", epc);
}

static void handle_misaligned_fetch(uintptr_t cause, uintptr_t epc, uintptr_t regs[32])
{
  dump_tf(cause, epc, regs);
  printf("Misaligned instruction access!\n");
}

static void handle_illegal_instruction(uintptr_t cause, uintptr_t epc, uintptr_t regs[32])
{
  dump_tf(cause, epc, regs);
  printf("An illegal instruction was executed!\n");
}

static void handle_breakpoint(uintptr_t cause, uintptr_t epc, uintptr_t regs[32])
{
  dump_tf(cause, epc, regs);
  printf("Breakpoint!\n");
}

static void handle_misaligned_store(uintptr_t cause, uintptr_t epc, uintptr_t regs[32])
{
  dump_tf(cause, epc, regs);
  printf("Misaligned AMO!\n");
}

static void handle_interrupt(uintptr_t cause, uintptr_t epc, uintptr_t regs[32]) 
{
  // If you're here, it's likely a Software or External interrupt.
  printf("This was an interruption .. clearing SIP_S{E|S|T}IP and getting back to code!\n");
  clear_csr(mip, MIP_MSIP | MIP_MEIP);// | MIP_MTIP | MIP_MEIP);
}

void handle_trap(uintptr_t cause, uintptr_t epc, uintptr_t regs[32])
{

  if (cause & 0x8000000000000000){
      uint64_t int_code = cause & ~0x8000000000000000;

      printf("[general_trap_handler] - Interrupt - Cause = %llx : %s .. Executing interrupt_handler\n", cause, interrupts_txt[cause]);

      handle_interrupt(int_code, epc, regs);

      return;
  }

  printf("[general_trap_handler] - Exception - Cause = %llx : %s .. Executing trap_handler\n", (intptr_t)cause, exceptions_txt[cause]);

  typedef void (*trap_handler)(uintptr_t, uintptr_t, uintptr_t*);

  const static trap_handler trap_handlers[] = {
    [CAUSE_MISALIGNED_FETCH] = handle_misaligned_fetch,
    //[CAUSE_FETCH_PAGE_FAULT] = handle_fault_fetch,
    [CAUSE_ILLEGAL_INSTRUCTION] = handle_illegal_instruction,
    //[CAUSE_USER_ECALL] = handle_syscall,
    [CAUSE_BREAKPOINT] = handle_breakpoint,
    [CAUSE_MISALIGNED_STORE] = handle_misaligned_store,
    //[CAUSE_LOAD_PAGE_FAULT] = handle_fault_load,
    //[CAUSE_STORE_PAGE_FAULT] = handle_fault_store
  };

  if(cause < ARRAY_SIZE(trap_handlers) && trap_handlers[cause])
    trap_handlers[cause](cause, epc, regs);
  
  tohost_exit(1337);
}




