# Compiler Construction course at VU Amsterdam

## Getting Started

Run `./run.py` to start the course's docker environment.
The contents of this directory are shared with the docker
environment, so you can freely edit them with a normal
machine and run commands in the docker at the same time.

## Grading

The primary purpose of the framework is grading your work.
You can do this by running `./grade` in the course's docker shell.

Run `./grade -a 1.1` to grade assignment 1's task 1. See `./grade --help` for other options.

You can only run a certain set of tests by passing a filter.
The filter is a simple string and only tests that have that
filter string in their name will be executed.
For example, `./grade -a 1.1 -f expr` will only run tests that
have 'expr' in their name, such as `global-expr.c`.

## Submitting Your Work

Run `./handin -a 1` in the docker container
to create a zip archive with your assignment 1
work. The same goes for assignments 2, 3 and 4.
You still have to manually submit your work to Canvas.