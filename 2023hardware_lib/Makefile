CC = g++

SRC = src
INC = include
LIB = lib

OBJ = obj
BIN = bin

# CLINKER = -Wl,-rpath
CFLAGS = -std=c++14
CINCS = -I$(INC)
CLIBS = 

all : main
	@mkdir -o $(bin) $(obj)
	# $(CC) -o $(exe) $(obj) $(FL)=$(lib_dir)
	# $(MAKE) clean

main : main.o LEDController.o
	$(CC) -o $(BIN)/main \
		$(OBJ)/main.o \
		$(OBJ)/LEDController.o \
		-L$(LIB) -lws2811 \
		$(CFLAGS) $(CINCS) $(CLIBS)

main.o :
	$(CC) -c $(SRC)/main.cpp -o $(OBJ)/main.o \
		$(CFLAGS) $(CINCS)

LEDController.o :
	$(CC) -c $(SRC)/LEDController.cpp -o $(OBJ)/LEDController.o \
		$(CFLAGS) $(CINCS)


# %.o:$(src_dir)/%.cpp
# 	$(CC) -c $(WSHEADERFL) $(lib_dir) $^ -o $@

.PHONY:clean

clean:
	rm *.o
