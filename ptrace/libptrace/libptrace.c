#include <stdint.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
static void DPRINT(const char *fmt, ...)
{
 	va_list args;
	FILE* fp = fopen("debug.log", "a");
    va_start(args, fmt);
	vfprintf(fp, fmt, args);
	va_end(args);
	fprintf(fp, "\n");
	fclose(fp);
}

pid_t fork_target(char *target, char **argv) {
	int ret;
	char *argvs[] = {NULL};
	char *execenvp[] = {NULL};
	int i = 0;
    pid_t pid = fork();
	if (pid < 0) {
		return -1;
    }
	if (pid != 0){
		return pid;
	}

	// child proc from here
	DPRINT("PTRACE_TRACEME");
	ret = ptrace(PTRACE_TRACEME, 0, 0, 0);
	if (ret != 0) {
		return -1;
	}
	DPRINT("Execve");
	ret = execve(target, argvs, execenvp);
	if (ret != 0) {
		return -1;
	}
	return pid;
}

int wait_target(pid_t pid, int *pWstatus) {
	return waitpid(pid, pWstatus, WUNTRACED);
}

// continue
int ptrace_continue(pid_t pid) {
	return ptrace(PTRACE_CONT, pid, 0, 0);
}

// set breakpoint
int ptrace_set_sw_breakpoint(pid_t pid, int *addr)
{
	uint32_t org_text;
	org_text = ptrace(PTRACE_POKEDATA, pid, addr, NULL);

	// set int3(0xCC)
	ptrace(PTRACE_POKEDATA, pid, addr, ((org_text & 0xFFFFFFFFFFFFFF00) | 0xCC));
	return org_text;
}

// delete breakpoint
int ptrace_delete_breakpoint(pid_t pid, void *addr, uint32_t org_text) {
	return ptrace(PTRACE_POKEDATA, pid, addr, org_text);
}

// write registers
int ptrace_write_regs(pid_t pid, void *regs) {
	return ptrace(PTRACE_SETREGS, pid, 0, regs);
}

// read registers
int ptrace_read_regs(pid_t pid, void *regs) {
	 return ptrace(PTRACE_GETREGS, pid, 0, regs);
}

// for debug
#if 0
int main(int argc, char **argv){
	char *target = "fffff";
	DLOG("target:[%s]\n", target);
}
#endif