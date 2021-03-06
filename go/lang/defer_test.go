package test

import (
	"sync"
	"testing"
)

var m sync.Mutex

func call() {
	m.Lock()
	m.Unlock()
}

func deferCall() {
	m.Lock()
	defer m.Unlock()
}

func BenchmarkCall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		call()
	}
}

func BenchmarkDeferCall(b *testing.B) {
	for i := 0; i < b.N; i++ {
		deferCall()
	}
}

/*
go test -bench=".*" defer_test.go
BenchmarkCall-4        	100000000	        19.2 ns/op
BenchmarkDeferCall-4   	20000000	        63.5 ns/op
PASS
ok  	command-line-arguments	3.283s
*/
