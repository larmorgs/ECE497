CC=gcc

TARGETS=test \
test.o

all: $(TARGETS)

clean: 
	clear
	rm -f $(TARGETS)

test: test.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@


