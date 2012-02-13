Boolean Logic Simulator
=======================

This project provides a simulator for algorithms used in [Boolean Logic][1]
which is intended to be a helpful learning tool for computer science students.


Supported Algorithms
--------------------

- [satisfiability][6]
  - by [resolution][7]


Installation Instructions
=========================

Dependencies
------------

Make sure your system has the following (required) dependencies installed:

- [glib2][2]
- [cmake][3] to build the project

Optionally you will need:

- [git][4] to retrieve the latest source code by cloning the git repository

Building and Installing
-----------------------

Retrieve a copy of the source code, e.g. clone the git repository:

```
$ git clone git://github.com/wookietreiber/tautolomator.git
```

Then you can build the project:

```
$ cd tautolomator
$ cmake -DCMAKE_INSTALL_PREFIX="~" -DCMAKE_C_FLAGS="-O2" .
$ make install
```

This will compile the project with some compiler optimizations switched on
("-O2") and install the binary to a subdirectory called "bin" into your home
directory ("~"). If your `PATH` contains "~/bin" you can directly use the
binary in your shell:

```
$ tautolomator --help
```

Usage
-----

Tautolomator is currently "just" a command line tool. You can input an
expression in one of the following ways:

- `tautolomator` - will ask you to input an expression (stdin)
- `tautolomator -i <expression>` - specify the expression on the command line
- `tautolomator -f </path/to/file>` - point to a file which contains the
  expression

The expression currently has to be a [conjunctive normal form (CNF)][5], e.g.
`A^(Bv-C)`, where `^` denotes a logical and, `v` denotes a logical or and `-`
denotes a logical not.

You may also retrieve full command line usage help by executing:

```
$ tautolomator --help
```


[1]: http://en.wikipedia.org/wiki/Boolean_logic
[2]: http://developer.gnome.org/glib/
[3]: http://www.cmake.org/
[4]: http://git-scm.com/
[5]: http://en.wikipedia.org/wiki/Conjunctive_normal_form
[6]: http://en.wikipedia.org/wiki/Boolean_satisfiability_problem
[7]: http://en.wikipedia.org/wiki/Resolution_(logic)

