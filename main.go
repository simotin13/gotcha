package main

import (
	"fmt"
	"gotcha/ptrace"
	"os"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "input target file")
		os.Exit(1)
	}

	var argv = []string{}
	fmt.Println(len(argv))
	if 3 < len(os.Args) {
		argv = os.Args[2:]
	}
	target := os.Args[1]
	pid := ptrace.ForkTarget(target, argv)
	fmt.Println(pid)
}
