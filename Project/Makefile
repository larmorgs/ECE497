CC=gcc

TARGETS=main \
main.o \
radio_config.o \
cc112x_spi.o \
hal_spi_rf_trxeb.o

all: $(TARGETS)

clean: 
	clear
	rm -f $(TARGETS)

main: main.o cc112x_spi.o hal_spi_rf_trxeb.o radio_config.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< -o $@


