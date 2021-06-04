# Gavin lyons 06-2021 
# Makefile to build example program for SSD1306_OLED_RPI library.
# URL: https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI

# ************************************************
# User SRC directory Option Section
# pick on example "SRC" dir and ONE ONLY.
# Comment out the other 5. #

SRC=HELLO_WORLD
#SRC=BITMAP
#SRC=CLOCK_DEMO
#SRC=OLED_FUNCTIONS
#SRC=SPEED_TEST
#SRC=TEXT_GRAPHICS
#SRC=HELLO_WORLD_128_32
# ************************************************

CC=g++
LDFLAGS= -lbcm2835 -lrt -lSSD1306_OLED_RPI 
CFLAGS = -Iinclude/ -c -Wall 
MD=mkdir
OBJ=obj
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp,  $(OBJ)/%.o, $(SRCS))
BIN=./bin
TARGET=$(BIN)/test

all: clean pre-build $(TARGET) 

pre-build:
	@echo '*******'
	@echo '[START!]'
	$(MD) -vp $(BIN)
	$(MD) -vp $(OBJ)


$(TARGET): $(OBJS) $(OBJ)
	@echo '[MAKE EXE FILE!]'
	$(CC)  $(OBJS) -o $@ $(LDFLAGS)
	@echo '[DONE!]'

$(OBJ)/%.o :  $(SRC)/%.cpp   $(OBJ) 
	@echo '[MAKE OBJECT FILE!]'
	$(CC) $(CFLAGS) $< -o  $@ 

clean:
	@echo '*******'
	@echo '[CLEANUP!]'
	rm -vf $(OBJS) $(TARGET)
	rmdir -v $(BIN) $(OBJ)
	@echo '[DONE!]'
