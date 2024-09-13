# Pipex

## Project Description

Pipex is a project aimed at deepening your understanding of UNIX pipelines by replicating the behavior of the shell pipe command (`|`). Through this project, we will explore the mechanisms that allow for inter-process communication via pipes in UNIX-like systems.

## Mandatory Features

The program is executed as follows:

```bash
./pipex file1 cmd1 cmd2 file2
```

It behaves exactly like the following shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

Where:

- `file1` is the input file.
- `cmd1` and `cmd2` are the commands to be executed.
- `file2` is the output file.

### Example Usage

```bash
./pipex infile "ls -l" "wc -l" outfile
```

This is equivalent to:

```bash
< infile ls -l | wc -l > outfile
```

## Compilation

To compile the project, run:

```bash
make
```

To clean up object files:

```bash
make clean
```

To remove all compiled files, including the program:

```bash
make fclean
```

To recompile everything from scratch:

```bash
make re
```
