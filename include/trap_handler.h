#ifndef _TRAP_HANDLER_H
#define _TRAP_HANDLER_H

extern void __attribute__((noreturn)) tohost_exit(uintptr_t code);

const static char* exceptions_txt[] = {
        [CAUSE_MISALIGNED_FETCH] = "misaligned fetch",
        [CAUSE_FETCH_ACCESS] = "fetch access",
        [CAUSE_ILLEGAL_INSTRUCTION] = "illegal instruction",
        [CAUSE_BREAKPOINT] = "breakpoint",
        [CAUSE_MISALIGNED_LOAD] = "misaligned load",
        [CAUSE_LOAD_ACCESS] = "load access",
        [CAUSE_MISALIGNED_STORE] = "misaligned store",
        [CAUSE_STORE_ACCESS] = "store access",
        [CAUSE_USER_ECALL] = "user_ecall",
        [CAUSE_SUPERVISOR_ECALL] = "supervisor_ecall",
        [CAUSE_HYPERVISOR_ECALL] = "hypervisor_ecall",
        [CAUSE_MACHINE_ECALL] = "machine_ecall",
        [CAUSE_FETCH_PAGE_FAULT] = "fetch page fault",
        [CAUSE_LOAD_PAGE_FAULT] = "load page fault",
        [CAUSE_STORE_PAGE_FAULT] = "store page fault",
  };

const static char* interrupts_txt[] = {
        [CAUSE_USER_SOFTWARE_INTERRUPT] = "user software interrupt",
        [CAUSE_SUPERVISOR_SOFTWARE_INTERRUPT] = "supervisor software interrupt",
        [CAUSE_HYPERVISOR_SOFTWARE_INTERRUPT] = "hypervisor software interrupt",
        [CAUSE_MACHINE_SOFTWARE_INTERRUPT] = "machine software interrupt",

        [CAUSE_USER_TIMER_INTERRUPT] = "user timer interrupt",
        [CAUSE_SUPERVISOR_TIMER_INTERRUPT] = "supervisor timer interrupt",
        [CAUSE_HYPERVISOR_TIMER_INTERRUPT] = "hypervisor timer interrupt",
        [CAUSE_MACHINE_TIMER_INTERRUPT] = "machine timer interrupt",

        [CAUSE_USER_EXTERNAL_INTERRUPT] = "user external interrupt",
        [CAUSE_SUPERVISOR_EXTERNAL_INTERRUPT] = "supervisor external interrupt",
        [CAUSE_HYPERVISOR_EXTERNAL_INTERRUPT] = "hypervisor external interrupt",
        [CAUSE_MACHINE_EXTERNAL_INTERRUPT] = "machine external interrupt"
  };

void dump_tf(uintptr_t cause, uintptr_t epc, uintptr_t regs[32]);
void handle_trap(uintptr_t cause, uintptr_t epc, uintptr_t regs[32]);


#endif /* _TRAP_HANDLER_H */