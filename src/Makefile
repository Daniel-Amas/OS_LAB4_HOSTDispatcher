# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99

# Source files
SRCS = dispatcher.c process.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = dispatcher

# Default target
all: $(EXEC)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)
