#
#  File name: makefile
#
#  Author: 2023/2024 P1, Fall Semester AED Team
#
#  Release date: 2023/09/20
#
#  Description: Makefile for the individual evaluation laboratory
#
#  Usage:
#     1) To generate the executable file for the program p2-pub, run
#         $ make p2
#
#     2) To clean all object files and the executable file, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -O3 -Wall -std=c99

#  Sources
SOURCES = $(shell ls ./*.c)

#  Objects
OBJECTS = $(SOURCES:%.c=%.o)

tileblaster: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(OBJECTS): $(SOURCES)

clean::
	rm -f $(OBJECTS) tileblaster