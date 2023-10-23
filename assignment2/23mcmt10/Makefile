CC = gcc
CFLAGS = -Wall -Werror
SRCDIR = src
BINDIR = bin

# List of source files
SRC = $(SRCDIR)/main.c $(SRCDIR)/execmd.c $(SRCDIR)/get_location.c

# List of object files derived from source files
OBJ = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SRC))

# Name of the executable
TARGET = RFShell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)/*.o $(TARGET)

.PHONY: all clean
