CC=gcc
CCPP=g++

RES_DIR= ../Resources/adafruit

TARGETS= bicolor8x8 \
bicolor8x8.opp \
$(RES_DIR)/HT16K33/Adafruit_LEDBackpack.opp \
$(RES_DIR)/Adafruit-GFX-Library/Adafruit_GFX.opp \
$(RES_DIR)/Adafruit-GFX-Library/glcdfont.o

all: $(TARGETS)

clean: 
	clear
	rm -f $(TARGETS)

bicolor8x8: bicolor8x8.opp $(RES_DIR)/HT16K33/Adafruit_LEDBackpack.opp $(RES_DIR)/Adafruit-GFX-Library/Adafruit_GFX.opp
	$(CCPP) $^ -o $@

$(RES_DIR)/HT16K33/Adafruit_LEDBackpack.opp: $(RES_DIR)/Adafruit-GFX-Library/Adafruit_GFX.opp $(RES_DIR)/Adafruit-GFX-Library/glcdfont.o

%.o: %.c
	$(CC) -c $< -o $@

%.opp: %.cpp
	$(CCPP) -c $< -o $@


