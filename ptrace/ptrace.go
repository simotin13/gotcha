package ptrace

// #cgo CFLAGS: -I./libptrace
// #cgo LDFLAGS: -L./libptrace -lptrace
// #include "libptrace.h"
// #include <stdlib.h>
import "C"
import (
	"fmt"
	"unsafe"
)

type Reg_X64 struct {
	R15      uint64
	R14      uint64
	R13      uint64
	R12      uint64
	Rbp      uint64
	Rbx      uint64
	R11      uint64
	R10      uint64
	R9       uint64
	R8       uint64
	RAX      uint64
	RCX      uint64
	RDX      uint64
	RSI      uint64
	RDI      uint64
	ORIG_RAX uint64
	RIP      uint64
	CS       uint64
	EFLAGS   uint64
	RSP      uint64
	SS       uint64
	FS_BASE  uint64
	GS_BASE  uint64
	DS       uint64
	ES       uint64
	FS       uint64
	GS       uint64
}

func ForkTarget(target string, argv []string) int {
	// TODO pass argvs
	if 0 < len(argv) {
		fmt.Println(len(argv))
		//c_args := make([]*C.char, len(argv))
		//c_argv = (**C.char)(&c_args[0])
	}
	c_target := C.CString(target)
	var c_argv **C.char = nil
	c_pid := C.fork_target(c_target, c_argv)
	C.free(unsafe.Pointer(c_target))
	return int(c_pid)
}

// wait target
func WaitTarget(pid int, wstatus *int) {
	c_pid := C.int(pid)
	c_wstatus := (*C.int)(unsafe.Pointer(&wstatus))
	C.wait_target(c_pid, c_wstatus)
}

// continue
func Continue(pid int) {
	c_pid := C.int(pid)
	C.ptrace_continue(c_pid)
}

// set breakpoint
func SetBreakpoint(pid int, addr uintptr) {
	c_pid := C.int(pid)
	c_ptr := unsafe.Pointer(addr)
	C.ptrace_set_sw_breakpoint(c_pid, c_ptr)
}

// delete breakpoint
func DeleteBreakpoint(pid int, addr *uint64, org_text uint32) {
	c_pid := C.int(pid)
	c_ptr := unsafe.Pointer(addr)
	c_org_text := C.uint32_t(org_text)
	C.ptrace_delete_breakpoint(c_pid, c_ptr, c_org_text)
}

// write register
func WriteRegisters(pid int, reg *Reg_X64) {
	c_pid := C.int(pid)
	c_reg := unsafe.Pointer(reg)
	C.ptrace_write_regs(c_pid, c_reg)
}

// read register
func ReadRegisters(pid int, reg *Reg_X64) {
	c_pid := C.int(pid)
	c_reg := unsafe.Pointer(reg)
	C.ptrace_read_regs(c_pid, c_reg)
}
