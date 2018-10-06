---
title: Golang Tools
author: Dominik Honnef
---

# gofmt

Formats your code according to the only acceptable way of formatting it.

# go vet

Analysing Go code and finding common mistakes:

** Useless assignments
** Common mistakes when using sync/atomic
** Invalid +build tags
** Using composite literals without keyed fields
** Passing locks by value
** Comparing functions with nil
** Using wrong printf format specifiers
** Closing over loop variables the wrong way
** Struct tags that do not follow the canonical format
** Unreachable code
** Misuse of unsafe.Pointer
** Mistakes invoking boolean operators

# go lint

Checks your code for style violations.

# errcheck

Running errcheck on a package will report all function calls that have unchecked
errors.

# go tool cover

Code coverage reports provide a quick and easy way of finding untested code.

# benchcmp

# prettybench

# benchviz

Generates graphical output, it depends on benchcmp and uses bar charts to show
positive and negative changes.

# go generate

Replace various uses of makefiles and shell scripts in Go packages.

# stringer

# impl

Given an interface, will create method stubs for implementing that interface.

# goimports

It removes unused imports and adds missing imports, as long as doing so is not
ambiguous. If multiple packages with the same name, such as text/template and
html/template can be used to make the code compile, then goimports errs on the
side of safety and imports neither.

# goreturns

Fills in incomplete return statements with zero values.

# godef

# gocode

Provides context-sensitive auto completion and uses a client/server
architecture, where the server is a caching daemon, and the clients are a
command line utility as well as all popular editors.

# guru (once called oracle)

The Go guru is a source analysis tool capable of answering a multitude of
questions about Go programs, such as:

** What is the type of this expression? What are its methods?
** What's the value of this constant expression?
** Where is the definition of this identifier?
** What are the exported members of this imported packages?
** What are the free variables of the selected block of code?
** What interfaces does this type satisfy?
** Which concrete types implements this interface?
** What are the possible callees of this dynamic call?
** What are the possible callers of this function?
** What objects might this pointer point to?
** Where are the corresponding sends/receives of this channel receive/send?
** Which statements could update this filed/local/global/map/array/etc?
** Which functions might be called indirectly from this one?

# gorename

# godepgraph

A tool for generating dependency graphs (in Graphviz format) for Go packages.