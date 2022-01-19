#ifndef _LIB_PTRACE_H_
#define _LIB_PTRACE_H_
#include <stdint.h>
#include <unistd.h>

extern pid_t fork_target(char *target, char **argv);                            // fork target
extern int wait_target(pid_t pid, int *pWstatus);                               // wait target
extern int ptrace_continue(pid_t pid);                                          // continue
extern int ptrace_set_sw_breakpoint(pid_t pid, void *addr);                     // set breakpoint
extern int ptrace_delete_breakpoint(pid_t pid, void *addr, uint32_t org_text);  // delete breakpoint
extern int ptrace_write_regs(pid_t pid, void *regs);                            // write registers
extern int ptrace_read_regs(pid_t pid, void *regs);                             // read registers

#endif  // _LIB_PTRACE_H_