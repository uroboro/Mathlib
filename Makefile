CC=gcc
CFLAGS=-c -g -Wall
LDFLAGS=-g
SOURCES=$(wildcard *.c)
HEADERS=$(wildcard *.h)
OBJS=$(SOURCES:.c=.o)
EXE=main.x

$(EXE): $(OBJS)
	@echo "linking $(EXE) with $(OBJS)"
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c Makefile
	@echo "compiling $@"
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	@echo "deleting files"
	@rm -f $(OBJS) $(EXE)
