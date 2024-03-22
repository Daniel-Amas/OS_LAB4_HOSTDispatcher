CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)

all: dispatcher

dispatcher: $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f dispatcher
