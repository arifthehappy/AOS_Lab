CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lreadline
SRCDIR = src
BINDIR = bin

# List of source files
SRC = $(SRCDIR)/main.c $(SRCDIR)/execmd.c $(SRCDIR)/get_location.c $(SRCDIR)/initialize.c $(SRCDIR)/open_help.c $(SRCDIR)/own_cmd_handler.c $(SRCDIR)/parse_pipe.c $(SRCDIR)/process_string.c $(SRCDIR)/take_input.c

# List of object files derived from source files
OBJ = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRC))

# Name of the executable
TARGET = ShellKhan

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)/*.o $(TARGET)

.PHONY: all clean
