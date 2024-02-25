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

We need to copy that data into some data structure representing the table. SQLite uses a B-tree for fast lookups, inserts and deletes. 
We’ll start with something simpler. Like a B-tree, it will group rows into pages, but instead of arranging those pages as a tree it will arrange them as an array.

We’re going to start small by putting a lot of limitations on our database. For now, it will:
- support two operations: inserting a row and printing all rows
- reside only in memory (no persistence to disk)
- support a single, hard-coded table

### Peristence to disk
Components - 
Table - Maintains file handle that persists data in raw bytes and uses a pager to hold pages.
Pager - Tracks number of pages, serializes/deserializes the row data in raw bytes and writes them to disk.
