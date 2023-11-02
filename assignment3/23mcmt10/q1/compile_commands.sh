#!/bin/bash

# Set the compiler and flags
CC=gcc
CFLAGS="-Wall -Werror"
SRCDIR=src/commands
BINDIR=bin/commands

# Create the commands directory if it doesn't exist
mkdir -p $BINDIR

# Compile each command C file
for file in $SRCDIR/*.c; do
    # Extract the command name from the file name
    command_name=$(basename -s .c $file)

    # Compile the command
    $CC $CFLAGS $file -o $BINDIR/$command_name
done

echo "Compilation of commands completed."
