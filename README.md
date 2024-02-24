Database - design and implementation
==

### Components

### REPL
Set up REPL which is like the front end for the database.
This receievs commands from the user using the standard input.
It should run infinitely until user gives command to exit.

### Compiler and VM
The "front-end" of sqlite is a SQL compiler that parses a string and outputs an internal representation called bytecode.
This bytecode is passed to the virtual machine, which executes it.

Breaking things into two steps like this has a couple advantages:
- Reduces the complexity of each part (e.g. virtual machine does not worry about syntax errors)
- Allows compiling common queries once and caching the bytecode for improved performance
