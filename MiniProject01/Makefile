CC=gcc
TARGETS=main.o

all: $(TARGETS)

clean: 
	rm $(TARGETS)

%.o: %.c
	$(CC) $< -o $@

