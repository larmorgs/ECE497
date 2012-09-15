CC=gcc
TARGETS=main.o

all: $(TARGETS)

clean: 
	rm -f $(TARGETS)

%.o: %.c
	$(CC) $< -o $@

