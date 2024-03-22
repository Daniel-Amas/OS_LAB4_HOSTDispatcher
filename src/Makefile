CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = src/dispatcher.c src/process.c src/queue.c src/resource.c src/memory.c

all: dispatcher

dispatcher: $(SRC)
	$(CC) $(CFLAGS) -o dispatcher $(SRC)

clean:
	rm -f dispatcher
