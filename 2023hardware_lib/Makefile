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

all : directory main
	# $(CC) -o $(exe) $(obj) $(FL)=$(lib_dir)
	# $(MAKE) clean

directory : 
	mkdir -p $(OBJ)
	mkdir -p $(BIN)
main : LEDController_umb.o LEDController.o OFController.o main.o
	$(CC) -o $(BIN)/main \
		$(OBJ)/main.o \
		$(OBJ)/LEDController.o \
		$(OBJ)/LEDController_umb.o \
		$(OBJ)/OFController.o \
		-Wl,-rpath=lib \
		$(LIB)/libws2811.so \
		$(CFLAGS) $(CINCS) $(CLIBS)
		# -L$(LIB) -lws2811 \

main.o :
	# $(CC) -c $(SRC)/LEDmain.cpp -o $(OBJ)/main.o \
	#	$(CFLAGS) $(CINCS)
	# $(CC) -c $(SRC)/OFmain.cpp -o $(OBJ)/main.o \
	# 	$(CFLAGS) $(CINCS)
	$(CC) -c $(SRC)/main.cpp -o $(OBJ)/main.o \
	 	$(CFLAGS) $(CINCS)


LEDController.o : 
	$(CC) -c $(SRC)/LEDController.cpp -o $(OBJ)/LEDController.o \
		$(CFLAGS) $(CINCS)

LEDController_umb.o :
	$(CC) -c $(SRC)/LEDController_umb.cpp -o $(OBJ)/LEDController_umb.o \
		$(CFLAGS) $(CINCS)

OFController.o :
	$(CC) -c $(SRC)/OFController.cpp -o $(OBJ)/OFController.o \
		$(CFLAGS) $(CINCS)


# %.o:$(src_dir)/%.cpp
# 	$(CC) -c $(WSHEADERFL) $(lib_dir) $^ -o $@

.PHONY:clean

clean:
	rm *.o
