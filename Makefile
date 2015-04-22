CC ?= gcc
PREFIX ?= /usr/local/bin

all:
	$(CC) -o d daemonize.c

install: all
	cp d $(PREFIX)
