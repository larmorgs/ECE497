CC=gcc
CCPP=g++

RES_DIR= ../Resources/adafruit/HT1632

TARGETS=main.opp \
$(RES_DIR)/HT1632.opp \
$(RES_DIR)/serialio.o \
$(RES_DIR)/glcdfont.o

all: $(TARGETS)

clean: 
	rm -f $(TARGETS)

main.opp: $(RES_DIR)/HT1632.opp
$(RES_DIR)/HT1632.opp: $(RES_DIR)/serialio.o $(RES_DIR)/glcdfont.o

%.o: %.c
	$(CC) -c $< -o $@

%.opp: %.cpp
	$(CCPP) -c $< -o $@


