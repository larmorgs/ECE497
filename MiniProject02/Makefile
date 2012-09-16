CC=gcc
CCPP=g++

RES_DIR= ../Resources/adafruit/HT1632

TARGETS=main \
main.opp \
$(RES_DIR)/HT1632.opp \
$(RES_DIR)/glcdfont.o

all: $(TARGETS)

clean: 
	clear
	rm -f $(TARGETS)

main: main.opp $(RES_DIR)/HT1632.opp $(RES_DIR)/glcdfont.o
	$(CCPP) $^ -o $@

main.opp: $(RES_DIR)/HT1632.opp
$(RES_DIR)/HT1632.opp: $(RES_DIR)/glcdfont.o

%.o: %.c
	$(CC) -c $< -o $@

%.opp: %.cpp
	$(CCPP) -c $< -o $@


