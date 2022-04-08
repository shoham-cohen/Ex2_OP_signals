CC = gcc
FLAGS= -Wall -Werror -g

all: Signals

Signals: signals.c
	$(CC)  signals.c -o signals

clean:
	rm signals
.PHONY: all