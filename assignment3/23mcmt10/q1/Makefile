CC = gcc
CFLAGS = -Wall -Werror
LIBS = -lreadline
SRCDIR = src
BINDIR = bin


# List of source files
SRC = $(wildcard $(SRCDIR)/*.c)

# List of object files derived from source files
OBJ = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRC))

# Name of the executable
TARGET = ShellKhan

all: compile_commands $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

compile_commands: chmod_script
	./compile_commands.sh

chmod_script:
	chmod +x $(CURDIR)/compile_commands.sh

clean:
	rm -f $(BINDIR)/*.o $(TARGET)

.PHONY: all clean compile_commands chmod_script
